#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include "EditorState.h"

#include "Engine/GfxApi.h"
#include "Engine/ResourceManager.h"
#include "Engine/ShaderResource.h"

#include <Navi/NaviMgr.h>
#include <Navi/NaviProvider.h>

#include "imgui.h"
#include <random>
#include <vector>

#include "Engine/Input.h"
#include "Engine/Service.h"
#include "Engine/Logger.h"

#include <math.h>
#include <vector>

#include <algorithm>
#include <unordered_set>
#include <glm/gtx/matrix_decompose.hpp>

#include "Application.h"

#include "LgbViewer.h"
#include "Service.h"
#include <algorithm>
#include <cctype>

#include "Common.h"
#include "PreparedResultSet.h"

#include <Navi/NaviProvider.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "commonshader.h"
#include "imgui_internal.h"
#include "datReader/DatCategories/bg/lgb.h"
#include "datReader/GameData.h"
#include "datReader/DatCategories/bg/LgbTypes.h"

extern Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;


LgbViewer::LgbViewer()
{
}

LgbViewer::~LgbViewer()
{
  clearMapTexture();
  cleanupNavmeshRendering();
  cleanupObjModel();

  if( m_navmeshShader )
  {
    glDeleteProgram( m_navmeshShader );
    m_navmeshShader = 0;
  }

  if( m_objShader )
  {
    glDeleteProgram( m_objShader );
    m_objShader = 0;
  }
}

void LgbViewer::init()
{
  initializeCache();
  initializeNavmeshRendering();
}

void LgbViewer::initializeCache()
{
  auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();

  // Get all zone IDs once
  m_zoneIds = exdD.getIdList< Excel::TerritoryType >();

  // Cache all zone data
  m_cachedZones.clear();
  m_cachedZones.reserve( m_zoneIds.size() );

  for( const auto& id : m_zoneIds )
  {
    auto zoneRow = exdD.getRow< Excel::TerritoryType >( id );
    if( !zoneRow ) continue;

    auto cachedZone = std::make_unique< CachedZoneInfo >();
    cachedZone->id = id;
    cachedZone->data = zoneRow->data();
    cachedZone->name = zoneRow->getString( cachedZone->data.Name );
    cachedZone->lvb = zoneRow->getString( cachedZone->data.LVB );

    auto placeNameRow = exdD.getRow< Excel::PlaceName >( cachedZone->data.Area );
    if( placeNameRow )
      cachedZone->placeName = placeNameRow->getString( placeNameRow->data().Text.SGL );

    // Pre-compute display strings
    cachedZone->displayText = std::to_string( id ) + " - " + cachedZone->name + " - " + cachedZone->placeName;
    cachedZone->searchText = cachedZone->displayText;
    std::transform( cachedZone->searchText.begin(), cachedZone->searchText.end(),
                    cachedZone->searchText.begin(), ::tolower );

    m_cachedZones[ id ] = std::move( cachedZone );
  }

  // Initialize filtered list with all zones
  updateSearchFilter();
  m_needsRefresh = false;
}

void LgbViewer::updateSearchFilter()
{
  std::string searchTerm = std::string( m_searchBuffer );
  std::transform( searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower );

  // Only update if search term changed
  if( searchTerm == m_lastSearchTerm ) return;
  m_lastSearchTerm = searchTerm;

  m_filteredZones.clear();

  for( const auto& id : m_zoneIds )
  {
    auto it = m_cachedZones.find( id );
    if( it == m_cachedZones.end() ) continue;

    auto& zone = it->second;
    if( searchTerm.empty() || zone->searchText.find( searchTerm ) != std::string::npos )
    {
      m_filteredZones.push_back( zone.get() );
    }
  }
}

// Add a separate method to clean up just the geometry, not the whole rendering system
void LgbViewer::cleanupNavmeshGeometry()
{
  if( m_navmeshVAO )
  {
    glDeleteVertexArrays( 1, &m_navmeshVAO );
    m_navmeshVAO = 0;
  }

  if( m_navmeshVBO )
  {
    glDeleteBuffers( 1, &m_navmeshVBO );
    m_navmeshVBO = 0;
  }

  if( m_navmeshEBO )
  {
    glDeleteBuffers( 1, &m_navmeshEBO );
    m_navmeshEBO = 0;
  }

  m_navmeshIndexCount = 0;
  m_currentNavmeshZoneId = 0;

  printf( "Cleaned up navmesh geometry\n" );
}

void LgbViewer::cleanupNavmeshRendering()
{
  // Clean up geometry
  cleanupNavmeshGeometry();

  // Clean up shader
  if( m_navmeshShader )
  {
    glDeleteProgram( m_navmeshShader );
    m_navmeshShader = 0;
  }

  // Clean up framebuffer resources
  if( m_navmeshFBO )
  {
    glDeleteFramebuffers( 1, &m_navmeshFBO );
    m_navmeshFBO = 0;
  }

  if( m_navmeshTexture )
  {
    glDeleteTextures( 1, &m_navmeshTexture );
    m_navmeshTexture = 0;
  }

  if( m_navmeshDepthBuffer )
  {
    glDeleteRenderbuffers( 1, &m_navmeshDepthBuffer );
    m_navmeshDepthBuffer = 0;
  }

  printf( "Cleaned up all navmesh rendering resources\n" );
}


bool LgbViewer::loadLgbData( std::string lgbPath, std::vector< LGB_GROUP >& groups, std::string& name )
{
  auto& gameData = Engine::Service< xiv::dat::GameData >::ref();

  std::vector< char > data_section;
  if( !gameData.doesFileExist( lgbPath ) )
    return true;
  auto bg_file = gameData.getFile( lgbPath );
  data_section = bg_file->access_data_sections().at( 0 );

  groups.clear();
  LGB_FILE bgLgb( &data_section[ 0 ], "bg" );
  name = bgLgb.m_name;
  for( auto& group : bgLgb.groups )
  {
    groups.push_back( group );
  }
  return false;
}

void LgbViewer::onSelectionChanged()
{
  if( m_selectedZone )
  {
    // Load heavy data here
    const auto& data = m_selectedZone->data;

    // Load map texture if available
    if( data.Map > 0 )
    {
      loadMapTexture( data.Map );
      m_zoomLevel = -1.0f;
    }


    auto& naviMgr = Engine::Service< Sapphire::Common::Navi::NaviMgr >::ref();
    auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();
    auto zoneRow = exdD.getRow< Excel::TerritoryType >( m_selectedZone->id );
    if( zoneRow )
    {
      std::string lvb = zoneRow->getString( zoneRow->data().LVB );

      if( naviMgr.setupTerritory( lvb, m_selectedZone->id ) )
      {
        m_pNaviProvider = naviMgr.getNaviProvider( lvb, m_selectedZone->id );
        m_needsNavmeshRebuild = true;
        buildNavmeshGeometry();

        // Check if there's an OBJ file for this zone
        checkForObjFile();
      }
      else
        m_pNaviProvider = nullptr;


      std::string strippedPath;
      auto pos = lvb.find_last_of( "/" );
      if( pos != std::string::npos )
      {
        strippedPath = lvb.substr( 0, pos + 1 );
      }

      std::string lgbPath = "bg/" + strippedPath;
      std::vector< LGB_GROUP > groups;

      try
      {
        loadLgbData( lgbPath + "bg.lgb", bgGroups, bgGroupsName );
        loadLgbData( lgbPath + "planmap.lgb", planmapGroups, planmapName );
        loadLgbData( lgbPath + "planevent.lgb", planeventGroups, planeventName );
        loadLgbData( lgbPath + "planlive.lgb", planliveGroups, planliveName );
        loadLgbData( lgbPath + "planner.lgb", plannerGroups, plannerName );
      } catch( ... )
      {
        return;
      }
    }
  }
}

void LgbViewer::showGroupsWindow()
{
  ImGui::Begin( "LGB Groups", nullptr, ImGuiWindowFlags_None );

  // Search/filter functionality
  static char searchBuffer[ 256 ] = "";
  ImGui::Text( "Search:" );
  ImGui::SameLine();
  if( ImGui::InputText( "##GroupSearch", searchBuffer, sizeof( searchBuffer ) ) )
  {
    // Update search filter when text changes
  }

  ImGui::Separator();

  // Statistics summary
  int totalGroups = bgGroups.size() + planeventGroups.size() +
                    planliveGroups.size() + planmapGroups.size() + plannerGroups.size();
  ImGui::Text( "Total Groups: %d", totalGroups );

  ImGui::Separator();

  // Create a child window for scrolling
  ImGui::BeginChild( "GroupsScrollRegion", ImVec2( 0, 0 ), true );

  // Helper lambda to display a group category
  auto displayGroupCategory = [&]( const char *categoryName,
                                   const std::vector< LGB_GROUP >& groups,
                                   const ImVec4& headerColor,
                                   std::string& name )
  {
    if( groups.empty() ) return;

    ImGui::PushStyleColor( ImGuiCol_Text, headerColor );
    bool categoryOpen = ImGui::CollapsingHeader(
      ( name + " (" + std::to_string( groups.size() ) + ")" ).c_str(),
      ImGuiTreeNodeFlags_DefaultOpen
    );
    ImGui::PopStyleColor();

    if( categoryOpen )
    {
      ImGui::Indent();

      for( size_t i = 0; i < groups.size(); ++i )
      {
        const auto& group = groups[ i ];

        // Filter by search if needed
        std::string searchStr = searchBuffer;
        std::transform( searchStr.begin(), searchStr.end(), searchStr.begin(), ::tolower );
        std::string groupName = group.name;
        std::transform( groupName.begin(), groupName.end(), groupName.begin(), ::tolower );

        if( !searchStr.empty() && groupName.find( searchStr ) == std::string::npos )
          continue;

        // Create unique ID for this group
        ImGui::PushID( ( categoryName + std::to_string( i ) ).c_str() );

        // Group header with entry count
        std::string groupHeaderText = group.name + " (" +
                                      std::to_string( group.entries.size() ) + " entries)";

        bool groupOpen = ImGui::TreeNode( groupHeaderText.c_str() );

        // Right-click context menu for group
        if( ImGui::BeginPopupContextItem() )
        {
          if( ImGui::MenuItem( "Copy Group Name" ) )
          {
            ImGui::SetClipboardText( group.name.c_str() );
          }
          if( ImGui::MenuItem( "Export Group Info" ) )
          {
            // Add export functionality
          }
          ImGui::EndPopup();
        }

        if( groupOpen )
        {
          ImGui::Indent();

          // Group metadata
          ImGui::Text( "Layer ID: %u", group.header.LayerID );
          if( group.header.InstanceObject_Count > 0 )
          {
            ImGui::Text( "Layer Set References: %d", ( int ) group.refs.size() );

            // Show layer set info if available
            if( !group.refs.empty() )
            {
              if( ImGui::TreeNode( "Layer Sets" ) )
              {
                for( const auto& ref : group.refs )
                {
                  ImGui::BulletText( "Layer Set ID: %u", ref.LayerSetID );
                }
                ImGui::TreePop();
              }
            }
          }

          ImGui::Separator();

          if( !group.entries.empty() )
          {
            ImGui::Text( "Entries (%zu):", group.entries.size() );
            ImGui::Separator();

            // Create UNIQUE table name using category and group index
            std::string uniqueTableName = std::string( categoryName ) + "_Group" + std::to_string( i ) +
                                          "_EntriesTable";

            // Set a minimum height for the table to prevent 1-pixel height issue
            float tableHeight = ImGui::GetTextLineHeightWithSpacing() *
                                std::min( ( int ) group.entries.size() + 1, 10 ); // Show max 10 rows + header
            // Get available space and reserve some minimum height
            ImVec2 availableSize = ImGui::GetContentRegionAvail();
            float minTableHeight = 200.0f; // Minimum height for the table
            float tableHeight1 = std::max( minTableHeight, availableSize.y - 20.0f ); // Leave some padding

            // Ensure we have enough space for the table
            if( availableSize.y < minTableHeight )
            {
              tableHeight1 = minTableHeight;
            }


            if( ImGui::BeginTable( "EntriesTable", 6,
                                   ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY |
                                   ImGuiTableFlags_Resizable |
                                   ImGuiTableFlags_SizingFixedFit,
                                   ImVec2( 0.0f, tableHeight )
            ) )
            {
              // Set up table headers
              ImGui::TableSetupColumn( "ID", ImGuiTableColumnFlags_WidthFixed, 60.0f );
              ImGui::TableSetupColumn( "Name", ImGuiTableColumnFlags_WidthStretch );
              ImGui::TableSetupColumn( "Type", ImGuiTableColumnFlags_WidthFixed, 120.0f );
              ImGui::TableSetupColumn( "Position", ImGuiTableColumnFlags_WidthFixed, 180.0f );
              ImGui::TableSetupColumn( "Focus", ImGuiTableColumnFlags_WidthFixed, 60.0f );
              ImGui::TableSetupColumn( "View", ImGuiTableColumnFlags_WidthFixed, 60.0f );
              ImGui::TableHeadersRow();

              // Table content
              for( size_t i = 0; i < group.entries.size(); ++i )
              {
                auto& entry = group.entries[ i ];

                ImGui::TableNextRow();

                // ID column
                ImGui::TableSetColumnIndex( 0 );
                ImGui::Text( "%u", entry->header.InstanceID );

                // Name column
                ImGui::TableSetColumnIndex( 1 );
                if( entry->getType() == eAssetType::SharedGroup )
                {
                  auto sharedGroup = dynamic_cast< SharedGroupEntry* >( entry.get() );
                  std::string sharedGroupName = sharedGroup->AssetPath;
                  ImGui::Text( "%s", sharedGroupName.c_str() );
                }
                else if( entry->getType() == eAssetType::BG )
                {
                  auto sharedGroup = dynamic_cast< BGEntry* >( entry.get() );
                  std::string modelName = sharedGroup->modelFileName;
                  ImGui::Text( "%s", modelName.c_str() );
                }
                else
                  ImGui::Text( "%s", entry->name.c_str() );

                // Type column
                ImGui::TableSetColumnIndex( 2 );
                ImGui::Text( "%s", getEntryTypeString( entry->getType() ).c_str() );

                // Position column
                ImGui::TableSetColumnIndex( 3 );
                ImGui::Text( "%.1f, %.1f, %.1f",
                             entry->header.Transformation.Translation.x,
                             entry->header.Transformation.Translation.y,
                             entry->header.Transformation.Translation.z );

                // Focus button column
                ImGui::TableSetColumnIndex( 4 );
                std::string focusButtonId = "Focus##" + std::to_string( entry->header.InstanceID );
                if( ImGui::SmallButton( focusButtonId.c_str() ) )
                {
                  focusOn3DPosition( entry->header.Transformation.Translation );
                }

                // View button column
                ImGui::TableSetColumnIndex( 5 );
                std::string viewButtonId = "View##" + std::to_string( entry->header.InstanceID );
                if( ImGui::SmallButton( viewButtonId.c_str() ) )
                {
                  openEntryViewWidget( entry );
                }

                // Handle row selection and context menu
                if( ImGui::IsItemClicked() || ImGui::TableGetHoveredRow() == ( int ) i + 1 )
                {
                  onEntrySelected( entry.get() );
                }

                // Right-click context menu (keeping existing functionality)
                if( ImGui::BeginPopupContextItem() )
                {
                  if( ImGui::MenuItem( "Focus in 3D View" ) )
                  {
                    focusOn3DPosition( entry->header.Transformation.Translation );
                  }
                  if( ImGui::MenuItem( "View Details" ) )
                  {
                    openEntryViewWidget( entry );
                  }
                  ImGui::EndPopup();
                }
              }

              ImGui::EndTable();
            }
          }
          else
          {
            ImGui::TextDisabled( "No entries in this group" );
          }

          ImGui::Unindent();
          ImGui::TreePop();
        }

        ImGui::PopID();
      }

      ImGui::Unindent();
    }
  };

  // Display each category with different colors
  displayGroupCategory( "BG Groups", bgGroups, ImVec4( 0.2f, 0.8f, 0.2f, 1.0f ), bgGroupsName ); // Green
  displayGroupCategory( "Plan Event Groups", planeventGroups, ImVec4( 0.8f, 0.2f, 0.2f, 1.0f ), planeventName ); // Red
  displayGroupCategory( "Plan Live Groups", planliveGroups, ImVec4( 0.2f, 0.2f, 0.8f, 1.0f ), planliveName ); // Blue
  displayGroupCategory( "Plan Map Groups", planmapGroups, ImVec4( 0.8f, 0.8f, 0.2f, 1.0f ), planmapName ); // Yellow
  displayGroupCategory( "Planner Groups", plannerGroups, ImVec4( 0.8f, 0.2f, 0.8f, 1.0f ), plannerName ); // Magenta

  ImGui::EndChild();
  ImGui::End();
}

std::string LgbViewer::getEntryTypeString( eAssetType type )
{
  switch( type )
  {
    case eAssetType::BG: return "BgParts";
    case eAssetType::Attribute: return "Attribute";
    case eAssetType::LayLight: return "LayLight";
    case eAssetType::VFX: return "VFX";
    case eAssetType::PositionMarker: return "PositionMarker";
    case eAssetType::SharedGroup: return "SharedGroup";
    case eAssetType::Sound: return "Sound";
    case eAssetType::EventNPC: return "EventNPC";
    case eAssetType::BattleNPC: return "BattleNPC";
    case eAssetType::RoutePath: return "RoutePath";
    case eAssetType::Character: return "Character";
    case eAssetType::Aetheryte: return "Aetheryte";
    case eAssetType::EnvSet: return "EnvSet";
    case eAssetType::Gathering: return "Gathering";
    case eAssetType::HelperObject: return "HelperObject";
    case eAssetType::Treasure: return "Treasure";
    case eAssetType::Clip: return "Clip";
    case eAssetType::ClipCtrlPoint: return "ClipCtrlPoint";
    case eAssetType::ClipCamera: return "ClipCamera";
    case eAssetType::ClipLight: return "ClipLight";
    case eAssetType::ClipReserve00: return "ClipReserve00";
    case eAssetType::ClipReserve01: return "ClipReserve01";
    case eAssetType::ClipReserve02: return "ClipReserve02";
    case eAssetType::ClipReserve03: return "ClipReserve03";
    case eAssetType::ClipReserve04: return "ClipReserve04";
    case eAssetType::ClipReserve05: return "ClipReserve05";
    case eAssetType::ClipReserve06: return "ClipReserve06";
    case eAssetType::ClipReserve07: return "ClipReserve07";
    case eAssetType::ClipReserve08: return "ClipReserve08";
    case eAssetType::ClipReserve09: return "ClipReserve09";
    case eAssetType::ClipReserve10: return "ClipReserve10";
    case eAssetType::ClipReserve11: return "ClipReserve11";
    case eAssetType::ClipReserve12: return "ClipReserve12";
    case eAssetType::ClipReserve13: return "ClipReserve13";
    case eAssetType::ClipReserve14: return "ClipReserve14";
    case eAssetType::CutAssetOnlySelectable: return "CutAssetOnlySelectable";
    case eAssetType::Player: return "Player";
    case eAssetType::Monster: return "Monster";
    case eAssetType::Weapon: return "Weapon";
    case eAssetType::PopRange: return "PopRange";
    case eAssetType::ExitRange: return "ExitRange";
    case eAssetType::LVB: return "LVB";
    case eAssetType::MapRange: return "MapRange";
    case eAssetType::NaviMeshRange: return "NaviMeshRange";
    case eAssetType::EventObject: return "EventObject";
    case eAssetType::DemiHuman: return "DemiHuman";
    case eAssetType::EnvLocation: return "EnvLocation";
    case eAssetType::ControlPoint: return "ControlPoint";
    case eAssetType::EventRange: return "EventRange";
    case eAssetType::RestBonusRange: return "RestBonusRange";
    case eAssetType::QuestMarker: return "QuestMarker";
    case eAssetType::Timeline: return "Timeline";
    case eAssetType::ObjectBehaviorSet: return "ObjectBehaviorSet";
    case eAssetType::Movie: return "Movie";
    case eAssetType::ScenarioEXD: return "ScenarioEXD";
    case eAssetType::ScenarioText: return "ScenarioText";
    case eAssetType::CollisionBox: return "CollisionBox";
    case eAssetType::DoorRange: return "DoorRange";
    case eAssetType::LineVFX: return "LineVFX";
    case eAssetType::SoundEnvSet: return "SoundEnvSet";
    case eAssetType::CutActionTimeline: return "CutActionTimeline";
    case eAssetType::CharaScene: return "CharaScene";
    case eAssetType::CutAction: return "CutAction";
    case eAssetType::EquipPreset: return "EquipPreset";
    case eAssetType::ClientPath: return "ClientPath";
    case eAssetType::ServerPath: return "ServerPath";
    case eAssetType::GimmickRange: return "GimmickRange";
    case eAssetType::TargetMarker: return "TargetMarker";
    case eAssetType::ChairMarker: return "ChairMarker";
    case eAssetType::ClickableRange: return "ClickableRange";
    case eAssetType::PrefetchRange: return "PrefetchRange";
    case eAssetType::FateRange: return "FateRange";
    case eAssetType::PartyMember: return "PartyMember";
    case eAssetType::KeepRange: return "KeepRange";
    case eAssetType::SphereCastRange: return "SphereCastRange";
    case eAssetType::IndoorObject: return "IndoorObject";
    case eAssetType::OutdoorObject: return "OutdoorObject";
    case eAssetType::EditGroup: return "EditGroup";
    case eAssetType::StableChocobo: return "StableChocobo";
    default: return "Unknown(" + std::to_string( static_cast< uint32_t >( type ) ) + ")";
  }
}

std::string LgbViewer::getEntryName( InstanceObjectEntry *entry )
{
  // You'll need to cast to appropriate types and extract names
  // This depends on your LGB entry structure
  return "Entry_" + std::to_string( entry->header.InstanceID );
}

void LgbViewer::onEntrySelected( InstanceObjectEntry *entry )
{
  // Handle when an entry is selected
  // Update properties panel, focus camera, etc.
}

void LgbViewer::focusOn3DPosition( const vec3& position )
{
  // Focus 3D camera on the given position
  m_navCameraTarget = glm::vec3( position.x, position.y, position.z );

  // Position the camera at a reasonable distance from the target
  float distance = 25.0f; // Default viewing distance
  float pitch = 30.0f * ( 3.1415926f / 180.0f ); // 30 degrees down in radians
  float yaw = 0.0f; // Facing forward

  // Calculate camera position based on spherical coordinates
  m_navCameraPos.x = m_navCameraTarget.x + distance * cos( pitch ) * sin( yaw );
  m_navCameraPos.y = m_navCameraTarget.y + distance * sin( pitch );
  m_navCameraPos.z = m_navCameraTarget.z + distance * cos( pitch ) * cos( yaw );

  // Update camera parameters
  m_navCameraDistance = distance;
  m_navCameraYaw = yaw * ( 180.0f / 3.1415926f ); // Convert back to degrees
  m_navCameraPitch = 30.0f; // 30 degrees down

  // Ensure navmesh window is visible when focusing
  m_showNavmeshWindow = true;

  // Also focus the position in the 2D map view
  m_showMapWindow = true;

  // Convert world position to 2D map coordinates for centering
  // Using the map scale and offset to center the view on the position
  float mapCenterX = position.x / ( m_mapScale / 100.0f ) - m_mapOffset.x;
  float mapCenterY = position.z / ( m_mapScale / 100.0f ) - m_mapOffset.y; // Note: using Z for Y coordinate

  // Store the focus position for the map view to use during rendering
  m_focusWorldPos = glm::vec3( position.x, position.y, position.z );
  m_shouldFocusOnMap = true;

  // Set a reasonable zoom level for the map view
  m_zoomLevel = 2.0f; // Zoom in to show more detail around the focused position
}

// First, let's add a method to check for an .obj file alongside the navmesh
std::string LgbViewer::getObjFilePath()
{
  if( !m_selectedZone || !m_pNaviProvider )
  {
    return "";
  }

  // The path is based on the current zone and LVB name
  auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();
  auto zoneRow = exdD.getRow< Excel::TerritoryType >( m_selectedZone->id );
  if( !zoneRow )
  {
    return "";
  }


  std::string lvb = zoneRow->getString( zoneRow->data().Name );

  // Construct the path to check
  // We're assuming the OBJ file might be in the same folder as the navmesh
  auto objPath = std::filesystem::path( m_pNaviProvider->getNaviPath() ) / lvb / ( lvb + ".obj" );
  return objPath.string();
}

void LgbViewer::checkForObjFile()
{
  // Clean up any existing OBJ data
  cleanupObjModel();
  m_objLoaded = false;
  m_showObjModel = false;

  // Get the potential OBJ file path
  std::string objPath = getObjFilePath();
  if( objPath.empty() )
  {
    return;
  }

  // Check if the file exists
  std::ifstream file( objPath );
  if( !file.good() )
  {
    printf( "No OBJ file found at: %s\n", objPath.c_str() );
    return;
  }

  // File exists, attempt to load it
  if( loadObjModel( objPath ) )
  {
    m_objLoaded = true;
    m_currentObjPath = objPath;
    printf( "Successfully loaded OBJ model from: %s\n", objPath.c_str() );
  }
}

void LgbViewer::renderObjModel()
{
  if( !m_objModel.loaded || !m_showObjModel )
  {
    return;
  }

  // Use exactly the same matrices as navmesh
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           ( float ) m_navmeshTextureWidth / ( float ) m_navmeshTextureHeight,
                                           0.1f, 10000.0f );

  // Identity matrix - no transformation since navmesh uses same coordinates
  glm::mat4 model = glm::mat4( 1.0f );

  // Enable proper depth testing for shaded rendering
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );

  glUseProgram( m_objShader );

  // Set matrices
  GLint modelLoc = glGetUniformLocation( m_objShader, "model" );
  GLint viewLoc = glGetUniformLocation( m_objShader, "view" );
  GLint projectionLoc = glGetUniformLocation( m_objShader, "projection" );

  if( modelLoc != -1 )
    glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
  if( viewLoc != -1 )
    glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
  if( projectionLoc != -1 )
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, glm::value_ptr( projection ) );

  // Set height range for coloring (use the same as navmesh if available)
  GLint minHeightLoc = glGetUniformLocation( m_objShader, "minHeight" );
  GLint maxHeightLoc = glGetUniformLocation( m_objShader, "maxHeight" );

  if( minHeightLoc != -1 )
    glUniform1f( minHeightLoc, m_navmeshMinHeight );
  if( maxHeightLoc != -1 )
    glUniform1f( maxHeightLoc, m_navmeshMaxHeight );

  glBindVertexArray( m_objModel.vao );

  // Render filled triangles with shading
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glDrawElements( GL_TRIANGLES, m_objModel.indexCount, GL_UNSIGNED_INT, 0 );

  glBindVertexArray( 0 );
  glUseProgram( 0 );
}

bool LgbViewer::loadObjModel( const std::string& filepath )
{
  printf( "Loading OBJ model: %s\n", filepath.c_str() );

  // Clear existing model data
  cleanupObjModel();

  // Open file
  std::ifstream file( filepath );
  if( !file.is_open() )
  {
    printf( "Failed to open OBJ file: %s\n", filepath.c_str() );
    return false;
  }

  std::vector< glm::vec3 > positions;
  std::vector< unsigned int > indices;

  std::string line;
  while( std::getline( file, line ) )
  {
    if( line.empty() || line[ 0 ] == '#' ) continue;

    std::istringstream iss( line );
    std::string prefix;
    iss >> prefix;

    if( prefix == "v" )
    {
      // Vertex position
      glm::vec3 pos;
      iss >> pos.x >> pos.y >> pos.z;
      positions.push_back( pos );
    }
    else if( prefix == "f" )
    {
      // Face - only handle triangles, convert to 0-based indexing
      std::string vertex1, vertex2, vertex3;
      iss >> vertex1 >> vertex2 >> vertex3;

      // Extract just the position index (before any '/' character)
      auto getIndex = []( const std::string& str ) -> unsigned int
      {
        size_t slashPos = str.find( '/' );
        std::string indexStr = ( slashPos != std::string::npos ) ? str.substr( 0, slashPos ) : str;
        return std::stoi( indexStr ) - 1; // Convert to 0-based
      };

      indices.push_back( getIndex( vertex1 ) );
      indices.push_back( getIndex( vertex2 ) );
      indices.push_back( getIndex( vertex3 ) );
    }
  }
  file.close();

  if( positions.empty() )
  {
    printf( "No vertices found in OBJ file\n" );
    return false;
  }

  // Convert positions to ObjVertex format
  m_objModel.vertices.clear();
  m_objModel.vertices.reserve( positions.size() );

  // Calculate bounds and update the global height range
  glm::vec3 minPos = positions[ 0 ];
  glm::vec3 maxPos = positions[ 0 ];

  for( const auto& pos : positions )
  {
    ObjVertex vertex;
    vertex.position = pos;
    m_objModel.vertices.push_back( vertex );

    minPos = glm::min( minPos, pos );
    maxPos = glm::max( maxPos, pos );
  }

  // Update global height range for consistent coloring with navmesh
  m_navmeshMinHeight = std::min( m_navmeshMinHeight, minPos.y );
  m_navmeshMaxHeight = std::max( m_navmeshMaxHeight, maxPos.y );

  m_objModel.indices = indices;

  // Print model info
  glm::vec3 size = maxPos - minPos;
  glm::vec3 center = ( minPos + maxPos ) * 0.5f;
  printf( "Loaded %zu vertices, %zu indices\n", m_objModel.vertices.size(), m_objModel.indices.size() );
  printf( "Bounds: min(%.2f,%.2f,%.2f) max(%.2f,%.2f,%.2f)\n",
          minPos.x, minPos.y, minPos.z, maxPos.x, maxPos.y, maxPos.z );
  printf( "Size: (%.2f,%.2f,%.2f) Center: (%.2f,%.2f,%.2f)\n",
          size.x, size.y, size.z, center.x, center.y, center.z );

  // Create OpenGL objects
  glGenVertexArrays( 1, &m_objModel.vao );
  glGenBuffers( 1, &m_objModel.vbo );
  glGenBuffers( 1, &m_objModel.ebo );

  // Upload data
  glBindVertexArray( m_objModel.vao );

  glBindBuffer( GL_ARRAY_BUFFER, m_objModel.vbo );
  glBufferData( GL_ARRAY_BUFFER,
                m_objModel.vertices.size() * sizeof( ObjVertex ),
                m_objModel.vertices.data(),
                GL_STATIC_DRAW );

  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_objModel.ebo );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                m_objModel.indices.size() * sizeof( unsigned int ),
                m_objModel.indices.data(),
                GL_STATIC_DRAW );

  // Set up vertex attributes (only position)
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( ObjVertex ), ( void * ) 0 );
  glEnableVertexAttribArray( 0 );

  glBindVertexArray( 0 );

  // Create enhanced shader with height-based coloring
  if( m_objShader == 0 )
  {
    const char *vertexShader = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float minHeight;
uniform float maxHeight;

out vec3 FragPos;
out vec3 WorldPos;
out vec4 vertexColor;

void main() {
    WorldPos = (model * vec4(aPos, 1.0)).xyz;
    FragPos = WorldPos;
    gl_Position = projection * view * vec4(WorldPos, 1.0);

    // Calculate normalized height (0.0 to 1.0) - same as navmesh
    float heightNormalized = (WorldPos.y - minHeight) / (maxHeight - minHeight);

    // Generate base color from height gradient (green to red) - same as navmesh
    vec3 baseColor = vec3(heightNormalized, 1.0 - heightNormalized, 0.0);

    vertexColor = vec4(baseColor, 1.0);
}
)";

    const char *fragmentShader = R"(
#version 330 core
in vec3 FragPos;
in vec3 WorldPos;
in vec4 vertexColor;

out vec4 FragColor;

void main() {
    // Calculate normal from derivatives for lighting (flat shading)
    vec3 dFdxPos = dFdx(WorldPos);
    vec3 dFdyPos = dFdy(WorldPos);
    vec3 normal = normalize(cross(dFdxPos, dFdyPos));

    // Simple lighting - same as navmesh
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
    float normalShading = max(dot(normal, lightDir), 0.3); // 0.3 is ambient light level

    // Apply lighting to the height-based color
    vec3 finalColor = vertexColor.rgb * normalShading;

    FragColor = vec4(finalColor, 0.9); // Slightly transparent
}
)";

    m_objShader = createShaderProgram( vertexShader, fragmentShader );
    if( m_objShader == 0 )
    {
      printf( "Failed to create enhanced OBJ shader\n" );
      return false;
    }
  }

  m_objModel.indexCount = m_objModel.indices.size();
  m_objModel.loaded = true;

  printf( "OBJ model loaded successfully with height-based coloring!\n" );
  return true;
}

void LgbViewer::cleanupObjModel()
{
  if( m_objModel.vao != 0 )
  {
    glDeleteVertexArrays( 1, &m_objModel.vao );
    glDeleteBuffers( 1, &m_objModel.vbo );
    glDeleteBuffers( 1, &m_objModel.ebo );

    m_objModel.vao = 0;
    m_objModel.vbo = 0;
    m_objModel.ebo = 0;
  }

  m_objModel.vertices.clear();
  m_objModel.indices.clear();
  m_objModel.indexCount = 0;
  m_objModel.loaded = false;
}


void LgbViewer::updateNavmeshCamera()
{
  float radYaw = glm::radians( m_navCameraYaw );
  float radPitch = glm::radians( m_navCameraPitch );

  m_navCameraPos.x = m_navCameraTarget.x + m_navCameraDistance * cos( radPitch ) * cos( radYaw );
  m_navCameraPos.y = m_navCameraTarget.y + m_navCameraDistance * sin( radPitch );
  m_navCameraPos.z = m_navCameraTarget.z + m_navCameraDistance * cos( radPitch ) * sin( radYaw );
}


void LgbViewer::onSelectionCleared()
{
  clearMapTexture();
  // Clear other loaded data
}

void LgbViewer::show()
{
  if( m_needsRefresh )
  {
    initializeCache();
  }

  ImGui::Begin( "Lgb Viewer" );

  showZoneList();
  ImGui::Separator();
  showZoneDetails();

  ImGui::End();

  // Show map window if needed
  if( m_showMapWindow )
  {
    showMapWindow();
  }

  if( m_showNavmeshWindow )
  {
    showNavmeshWindow();
  }

  showGroupsWindow();

  // Render individual entry view widgets
  for( auto& widget : m_entryViewWidgets )
  {
    showEntryViewWidget( widget );
  }

  // Clean up closed widgets
  m_entryViewWidgets.erase(
    std::remove_if( m_entryViewWidgets.begin(), m_entryViewWidgets.end(),
                    []( const EntryViewWidget& widget ) { return !widget.isOpen; } ),
    m_entryViewWidgets.end()
  );
}


void LgbViewer::buildNavmeshGeometry()
{
  if( !m_pNaviProvider || !m_selectedZone )
  {
    return;
  }

  // Get navmesh from provider
  const dtNavMesh *navMesh = m_pNaviProvider->getNavMesh();
  if( !navMesh )
  {
    return;
  }

  std::vector< float > vertices;
  std::vector< unsigned int > indices;

  printf( "Processing navmesh for zone %u...\n", m_selectedZone->id );
  printf( "Max tiles in navmesh: %d\n", navMesh->getMaxTiles() );

  int totalPolygons = 0;
  int totalTriangles = 0;

  float minHeight = std::numeric_limits< float >::max();
  float maxHeight = std::numeric_limits< float >::lowest();


  // Process ALL tiles, not just a limited number
  for( int i = 0; i < navMesh->getMaxTiles(); ++i )
  {
    const dtMeshTile *tile = navMesh->getTile( i );
    if( !tile || !tile->header || !tile->dataSize ) continue;

    //printf( "Processing tile %d: %d polygons\n", i, tile->header->polyCount );
    totalPolygons += tile->header->polyCount;

    for( int j = 0; j < tile->header->polyCount; ++j )
    {
      const dtPoly *poly = &tile->polys[ j ];

      // Process all polygon types, not just GROUND
      if( poly->vertCount < 3 ) continue; // Skip invalid polygons

      // Fan triangulation from vertex 0
      for( int k = 1; k < poly->vertCount - 1; ++k )
      {
        // Triangle: 0, k, k+1
        for( int l = 0; l < 3; ++l )
        {
          int vertIndex;
          if( l == 0 ) vertIndex = 0;
          else if( l == 1 ) vertIndex = k;
          else vertIndex = k + 1;

          if( vertIndex >= poly->vertCount )
          {
            printf( "Invalid vertex index: %d >= %d\n", vertIndex, poly->vertCount );
            continue;
          }

          const float *v = &tile->verts[ poly->verts[ vertIndex ] * 3 ];

          minHeight = std::min( minHeight, v[ 1 ] );
          maxHeight = std::max( maxHeight, v[ 1 ] );

          // Position
          vertices.push_back( v[ 0 ] );
          vertices.push_back( v[ 1 ] );
          vertices.push_back( v[ 2 ] );

          // Normal (will be calculated later)
          vertices.push_back( 0.0f );
          vertices.push_back( 1.0f );
          vertices.push_back( 0.0f );
        }

        // Add indices for this triangle
        unsigned int baseIndex = ( vertices.size() / 6 ) - 3;
        indices.push_back( baseIndex );
        indices.push_back( baseIndex + 1 );
        indices.push_back( baseIndex + 2 );
        totalTriangles++;
      }
    }
  }

  m_navmeshMinHeight = minHeight;
  m_navmeshMaxHeight = maxHeight;


  printf( "Total polygons processed: %d\n", totalPolygons );
  printf( "Total triangles generated: %d\n", totalTriangles );
  printf( "Vertices: %zu, Indices: %zu\n", vertices.size() / 6, indices.size() );

  if( vertices.empty() || indices.empty() )
  {
    printf( "No navmesh geometry found for zone %u\n", m_selectedZone->id );
    return;
  }

  // Calculate proper normals for all triangles
  printf( "Calculating normals...\n" );
  for( size_t i = 0; i < indices.size(); i += 3 )
  {
    if( i + 2 >= indices.size() ) break;

    unsigned int i0 = indices[ i ] * 6;
    unsigned int i1 = indices[ i + 1 ] * 6;
    unsigned int i2 = indices[ i + 2 ] * 6;

    if( i0 + 5 >= vertices.size() || i1 + 5 >= vertices.size() || i2 + 5 >= vertices.size() )
    {
      continue;
    }

    glm::vec3 v0( vertices[ i0 ], vertices[ i0 + 1 ], vertices[ i0 + 2 ] );
    glm::vec3 v1( vertices[ i1 ], vertices[ i1 + 1 ], vertices[ i1 + 2 ] );
    glm::vec3 v2( vertices[ i2 ], vertices[ i2 + 1 ], vertices[ i2 + 2 ] );

    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 normal = glm::cross( edge1, edge2 );

    float length = glm::length( normal );
    if( length > 0.0001f )
    {
      normal = normal / length;
    }
    else
    {
      normal = glm::vec3( 0, 1, 0 ); // Default up vector
    }

    // Set normal for all three vertices
    vertices[ i0 + 3 ] = normal.x;
    vertices[ i0 + 4 ] = normal.y;
    vertices[ i0 + 5 ] = normal.z;
    vertices[ i1 + 3 ] = normal.x;
    vertices[ i1 + 4 ] = normal.y;
    vertices[ i1 + 5 ] = normal.z;
    vertices[ i2 + 3 ] = normal.x;
    vertices[ i2 + 4 ] = normal.y;
    vertices[ i2 + 5 ] = normal.z;
  }

  // Clean up existing buffers
  //  cleanupNavmeshRendering();

  // Create VAO, VBO, EBO
  glGenVertexArrays( 1, &m_navmeshVAO );
  glGenBuffers( 1, &m_navmeshVBO );
  glGenBuffers( 1, &m_navmeshEBO );

  printf( "Created buffers: VAO=%u, VBO=%u, EBO=%u\n", m_navmeshVAO, m_navmeshVBO, m_navmeshEBO );

  // Bind VAO
  glBindVertexArray( m_navmeshVAO );

  // Upload vertex data
  glBindBuffer( GL_ARRAY_BUFFER, m_navmeshVBO );
  glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( float ), vertices.data(), GL_STATIC_DRAW );

  // Upload index data
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_navmeshEBO );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned int ), indices.data(), GL_STATIC_DRAW );

  // Set vertex attributes
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void * ) 0 );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void * ) ( 3 * sizeof( float ) ) );
  glEnableVertexAttribArray( 1 );

  // Unbind VAO
  glBindVertexArray( 0 );

  m_navmeshIndexCount = indices.size();
  m_currentNavmeshZoneId = m_selectedZone->id;

  // Check for OpenGL errors
  GLenum error = glGetError();
  if( error != GL_NO_ERROR )
  {
    printf( "OpenGL error after creating navmesh geometry: %d\n", error );
  }
  else
  {
    printf( "Successfully created navmesh geometry with %d triangles\n", m_navmeshIndexCount / 3 );
  }
}

// Also add a simplified version for testing
void LgbViewer::buildSimpleNavmeshTest()
{
  // Create a simple test triangle
  std::vector< float > vertices = {
    // Triangle vertices (position + normal)
    -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, // vertex 0
    10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, // vertex 1
    0.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f // vertex 2
  };

  std::vector< unsigned int > indices = { 0, 1, 2 };

  // Clean up existing buffers
  cleanupNavmeshRendering();

  // Create VAO, VBO, EBO
  glGenVertexArrays( 1, &m_navmeshVAO );
  glGenBuffers( 1, &m_navmeshVBO );
  glGenBuffers( 1, &m_navmeshEBO );

  // Bind VAO
  glBindVertexArray( m_navmeshVAO );

  // Upload vertex data
  glBindBuffer( GL_ARRAY_BUFFER, m_navmeshVBO );
  glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( float ), vertices.data(), GL_STATIC_DRAW );

  // Upload index data
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_navmeshEBO );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned int ), indices.data(), GL_STATIC_DRAW );

  // Set vertex attributes
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void * ) 0 );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void * ) ( 3 * sizeof( float ) ) );
  glEnableVertexAttribArray( 1 );

  // Unbind VAO
  glBindVertexArray( 0 );

  m_navmeshIndexCount = indices.size();

  GLenum error = glGetError();
  if( error != GL_NO_ERROR )
  {
    printf( "OpenGL error after creating test triangle: %d\n", error );
  }
  else
  {
    printf( "Successfully created test triangle\n" );
  }
}

void LgbViewer::initializeNavmeshRendering()
{
  // Create shaders (same as before)
  const char *vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normal;   // Add normal input


    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform float minHeight;
    uniform float maxHeight;

    out vec4 vertexColor;

    void main()
    {
      gl_Position = projection * view * model * vec4(position, 1.0);

      // Calculate normalized height (0.0 to 1.0)
      float heightNormalized = (position.y - minHeight) / (maxHeight - minHeight);

      // Calculate basic lighting - we'll use a light from above and slightly to the side
      vec3 lightDir = normalize(vec3(0.5, 1.0, 0.3));
      float normalShading = max(dot(normal, lightDir), 0.3); // 0.3 is ambient light level

      // Generate base color from height gradient (green to red)
      vec3 baseColor = vec3(heightNormalized, 1.0 - heightNormalized, 0.0);

      // Apply normal shading to the base color
      vertexColor = vec4(baseColor * normalShading, 1.0);

    }
  )";


  const char *fragmentShaderSource = R"(
    #version 330 core
    in vec4 vertexColor;
    out vec4 FragColor;

    void main()
    {
      FragColor = vertexColor;
    }
  )";


  m_navmeshShader = createShaderProgram( vertexShaderSource, fragmentShaderSource );

  // Create framebuffer for rendering to texture
  createNavmeshFramebuffer();

  if( m_navmeshShader && m_navmeshFBO )
  {
    printf( "Navmesh rendering initialized successfully\n" );
  }
  else
  {
    printf( "Failed to initialize navmesh rendering\n" );
  }
}

// Helper function to project 3D world position to 2D screen coordinates
glm::vec2 LgbViewer::worldTo3DScreen( const glm::vec3& worldPos, const ImVec2& imageSize )
{
  // Set up the same matrices as used in 3D rendering
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           imageSize.x / imageSize.y,
                                           0.1f, 10000.0f );
  glm::mat4 mvp = projection * view;

  // Transform world position to screen space
  glm::vec4 clipSpace = mvp * glm::vec4( worldPos, 1.0f );

  // Perspective divide
  if( clipSpace.w <= 0.0f )
  {
    return glm::vec2( -1, -1 ); // Behind camera
  }

  glm::vec3 ndc = glm::vec3( clipSpace ) / clipSpace.w;

  // Check if point is outside clip space
  if( ndc.x < -1.0f || ndc.x > 1.0f || ndc.y < -1.0f || ndc.y > 1.0f || ndc.z < -1.0f || ndc.z > 1.0f )
  {
    return glm::vec2( -1, -1 ); // Outside view
  }

  // Convert to screen coordinates
  glm::vec2 screenPos;
  screenPos.x = ( ndc.x + 1.0f ) * 0.5f * imageSize.x;
  screenPos.y = ( 1.0f - ndc.y ) * 0.5f * imageSize.y; // Flip Y

  return screenPos;
}

void LgbViewer::renderNavmesh()
{
  if( !m_navmeshTexture )
  {
    ImGui::Text( "No navmesh texture available" );
    return;
  }

  // Render navmesh to our texture
  renderNavmeshToTexture();

  // Display the texture in ImGui
  ImVec2 contentRegion = ImGui::GetContentRegionAvail();

  // Maintain aspect ratio
  float aspectRatio = ( float ) m_navmeshTextureWidth / ( float ) m_navmeshTextureHeight;
  ImVec2 imageSize;

  if( contentRegion.x / aspectRatio <= contentRegion.y )
  {
    imageSize.x = contentRegion.x;
    imageSize.y = contentRegion.x / aspectRatio;
  }
  else
  {
    imageSize.y = contentRegion.y;
    imageSize.x = contentRegion.y * aspectRatio;
  }

  // Center the image
  ImVec2 cursorPos = ImGui::GetCursorPos();
  ImVec2 offset = ImVec2( ( contentRegion.x - imageSize.x ) * 0.5f, ( contentRegion.y - imageSize.y ) * 0.5f );
  ImGui::SetCursorPos( ImVec2( cursorPos.x + offset.x, cursorPos.y + offset.y ) );

  // Get the screen position of the image
  ImVec2 imageScreenPos = ImGui::GetCursorScreenPos();

  // Display the texture
  ImGui::Image( ImTextureRef( m_navmeshTexture ), imageSize, ImVec2( 0, 1 ), ImVec2( 1, 0 ) );

  // Handle mouse interaction over the image (camera controls only)
  if( ImGui::IsItemHovered() )
  {
    ImGuiIO& io = ImGui::GetIO();


    // Right click for world editing
    if( ImGui::IsMouseClicked( ImGuiMouseButton_Right ) )
    {
      ImVec2 mousePos = ImGui::GetMousePos();
      mousePos.x -= imageScreenPos.x;
      mousePos.y -= imageScreenPos.y;

      // Cast ray to find world position
      Ray ray = screenToWorldRay( mousePos, imageSize );
      RayHit hit = castRayToGeometry( ray );

      if( hit.hit )
      {
        m_lastClickWorldPos = hit.position;
        m_showClickMarker = true;

        printf( "Clicked world position: (%.2f, %.2f, %.2f)\n",
                hit.position.x, hit.position.y, hit.position.z );
        printf( "Surface normal: (%.2f, %.2f, %.2f)\n",
                hit.normal.x, hit.normal.y, hit.normal.z );

        // Here you can add your world editing logic
        onWorldClick( hit );
      }
    }


    // Left mouse button - rotate camera (only if not clicking on BNPC)
    if( io.MouseDown[ 0 ] )
    {
      if( !m_navMouseDragging )
      {
        m_navMouseDragging = true;
        m_navLastMousePos = io.MousePos;
        m_navCameraControlActive = true;
      }
      else
      {
        ImVec2 delta = ImVec2( io.MousePos.x - m_navLastMousePos.x,
                               io.MousePos.y - m_navLastMousePos.y );

        m_navCameraYaw += delta.x * 0.5f;
        m_navCameraPitch -= delta.y * 0.5f;

        // Clamp pitch
        m_navCameraPitch = glm::clamp( m_navCameraPitch, -89.0f, 89.0f );

        m_navLastMousePos = io.MousePos;
      }
    }
    else
    {
      if( m_navMouseDragging )
      {
        m_navMouseDragging = false;
        m_navCameraControlActive = false;
      }
    }

    // Middle mouse button - pan camera
    if( io.MouseDown[ 2 ] )
    {
      if( !m_navMousePanning )
      {
        m_navMousePanning = true;
        m_navLastMousePos = io.MousePos;
        m_navCameraControlActive = true;
      }
      else
      {
        ImVec2 delta = ImVec2( io.MousePos.x - m_navLastMousePos.x,
                               io.MousePos.y - m_navLastMousePos.y );

        glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );

        glm::vec3 cameraRight = glm::vec3( view[ 0 ][ 0 ], view[ 1 ][ 0 ], view[ 2 ][ 0 ] );
        glm::vec3 cameraUp = glm::vec3( view[ 0 ][ 1 ], view[ 1 ][ 1 ], view[ 2 ][ 1 ] );

        float panSensitivity = 1;

        glm::vec3 panMovement = cameraRight * ( -delta.x * panSensitivity ) +
                                cameraUp * ( delta.y * panSensitivity );

        m_navCameraTarget += panMovement;

        m_navLastMousePos = io.MousePos;
      }
    }
    else
    {
      if( m_navMousePanning )
      {
        m_navMousePanning = false;
        m_navCameraControlActive = false;
      }
    }

    // Handle mouse wheel for zoom
    if( io.MouseWheel != 0.0f )
    {
      glm::vec3 forward = glm::normalize( m_navCameraTarget - m_navCameraPos );

      float moveSpeed = 20.0f;
      float moveAmount = io.MouseWheel * moveSpeed;

      m_navCameraPos += forward * moveAmount;
      m_navCameraTarget += forward * moveAmount;
    }
  }
  else
  {
    // Reset mouse states when not hovering
    if( m_navMouseDragging )
    {
      m_navMouseDragging = false;
      m_navCameraControlActive = false;
    }
    if( m_navMousePanning )
    {
      m_navMousePanning = false;
      m_navCameraControlActive = false;
    }
  }

  // Update camera position
  updateNavmeshCamera();

  // Display info below the image
  ImGui::SetCursorPos( ImVec2( cursorPos.x, cursorPos.y + contentRegion.y - 100 ) );
  ImGui::Text( "Navmesh: %d triangles", m_navmeshIndexCount / 3 );
  ImGui::Text( "Camera: dist=%.1f yaw=%.1f pitch=%.1f",
               m_navCameraDistance, m_navCameraYaw, m_navCameraPitch );
  ImGui::Text( "Target: (%.1f, %.1f, %.1f)",
               m_navCameraTarget.x, m_navCameraTarget.y, m_navCameraTarget.z );
  ImGui::Text( "Controls: LMB=rotate, MMB=pan, wheel=zoom, click markers=select" );
}

void LgbViewer::renderNavmeshToTexture()
{
  if( !m_navmeshFBO )
  {
    printf( "No framebuffer for navmesh rendering\n" );
    return;
  }

  // Bind our framebuffer
  glBindFramebuffer( GL_FRAMEBUFFER, m_navmeshFBO );

  // Set viewport to match texture size
  glViewport( 0, 0, m_navmeshTextureWidth, m_navmeshTextureHeight );

  // Clear the framebuffer
  glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // Check which rendering mode to use
  if( m_showObjModel && m_objModel.loaded )
  {
    //printf( "Rendering OBJ model to texture\n" );
    renderObjModel();
  }
  else if( m_navmeshShader && m_navmeshVAO && m_navmeshIndexCount > 0 )
  {
    // Original navmesh rendering code
    //printf( "Rendering navmesh to texture\n" );

    // Set up matrices
    glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
    glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                             ( float ) m_navmeshTextureWidth / ( float ) m_navmeshTextureHeight,
                                             0.1f, 10000.0f );
    glm::mat4 model = glm::mat4( 1.0f );

    // Set OpenGL state
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glDisable( GL_BLEND );


    // Use shader
    glUseProgram( m_navmeshShader );

    // Set uniforms with correct names
    GLint modelLoc = glGetUniformLocation( m_navmeshShader, "model" );
    GLint viewLoc = glGetUniformLocation( m_navmeshShader, "view" );
    GLint projectionLoc = glGetUniformLocation( m_navmeshShader, "projection" );
    GLint minHeightLoc = glGetUniformLocation( m_navmeshShader, "minHeight" );
    GLint maxHeightLoc = glGetUniformLocation( m_navmeshShader, "maxHeight" );

    if( modelLoc != -1 )
      glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
    if( viewLoc != -1 )
      glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
    if( projectionLoc != -1 )
      glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
    if( minHeightLoc != -1 )
      glUniform1f( minHeightLoc, m_navmeshMinHeight );
    if( maxHeightLoc != -1 )
      glUniform1f( maxHeightLoc, m_navmeshMaxHeight );

    static bool showWireframe = false;
    GLint wireframeLoc = glGetUniformLocation( m_navmeshShader, "wireframe" );
    if( wireframeLoc != -1 )
    {
      glUniform1i( wireframeLoc, showWireframe ? 1 : 0 );
    }

    if( showWireframe )
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glLineWidth( 1.0f );
    }
    else
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    glBindVertexArray( m_navmeshVAO );
    glDrawElements( GL_TRIANGLES, m_navmeshIndexCount, GL_UNSIGNED_INT, 0 );

    GLenum err = glGetError();
    if( err != GL_NO_ERROR )
    {
      printf( "OpenGL error during navmesh rendering: 0x%x\n", err );
    }

    glBindVertexArray( 0 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glUseProgram( 0 );
  }
  else
  {
    //printf( "Nothing to render: showObj=%d, objLoaded=%d, navmeshShader=%u, navmeshVAO=%u, navmeshIndexCount=%d\n",
    //        m_showObjModel, m_objModel.loaded, m_navmeshShader, m_navmeshVAO, m_navmeshIndexCount );
  }

  // Unbind framebuffer (back to default)
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

glm::vec2 LgbViewer::worldToNavmeshScreen( float worldX, float worldY, float worldZ, ImVec2 imageSize )
{
  // Set up the same matrices as used in rendering
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           imageSize.x / imageSize.y,
                                           0.1f, 10000.0f );
  glm::mat4 model = glm::mat4( 1.0f );
  glm::mat4 mvp = projection * view * model;

  // Transform world position to screen space
  glm::vec4 worldPos( worldX, worldY, worldZ, 1.0f );
  glm::vec4 clipSpace = mvp * worldPos;

  // Perspective divide
  if( clipSpace.w == 0.0f )
  {
    return glm::vec2( -1, -1 ); // Invalid
  }

  glm::vec3 ndc = glm::vec3( clipSpace ) / clipSpace.w;

  // Check if point is behind camera or outside clip space
  if( clipSpace.w < 0.0f || ndc.x < -1.0f || ndc.x > 1.0f || ndc.y < -1.0f || ndc.y > 1.0f )
  {
    return glm::vec2( -1, -1 ); // Outside view
  }

  // Convert to screen coordinates
  glm::vec2 screenPos;
  screenPos.x = ( ndc.x + 1.0f ) * 0.5f * imageSize.x;
  screenPos.y = ( 1.0f - ndc.y ) * 0.5f * imageSize.y; // Flip Y

  return screenPos;
}

void LgbViewer::createNavmeshFramebuffer()
{
  // Clean up existing framebuffer
  if( m_navmeshFBO )
  {
    glDeleteFramebuffers( 1, &m_navmeshFBO );
    glDeleteTextures( 1, &m_navmeshTexture );
    glDeleteRenderbuffers( 1, &m_navmeshDepthBuffer );
  }

  // Create framebuffer
  glGenFramebuffers( 1, &m_navmeshFBO );
  glBindFramebuffer( GL_FRAMEBUFFER, m_navmeshFBO );

  // Create color texture
  glGenTextures( 1, &m_navmeshTexture );
  glBindTexture( GL_TEXTURE_2D, m_navmeshTexture );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, m_navmeshTextureWidth, m_navmeshTextureHeight,
                0, GL_RGB, GL_UNSIGNED_BYTE, nullptr );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

  // Attach color texture to framebuffer
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_navmeshTexture, 0 );

  // Create depth buffer
  glGenRenderbuffers( 1, &m_navmeshDepthBuffer );
  glBindRenderbuffer( GL_RENDERBUFFER, m_navmeshDepthBuffer );
  glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_navmeshTextureWidth, m_navmeshTextureHeight );
  glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_navmeshDepthBuffer );

  // Check framebuffer completeness
  if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
  {
    printf( "Navmesh framebuffer not complete!\n" );
  }

  // Unbind framebuffer
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );

  printf( "Created navmesh framebuffer: FBO=%u, Texture=%u, Depth=%u (%dx%d)\n",
          m_navmeshFBO, m_navmeshTexture, m_navmeshDepthBuffer,
          m_navmeshTextureWidth, m_navmeshTextureHeight );
}

void LgbViewer::showNavmeshWindow()
{
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar |
                                  ImGuiWindowFlags_NoScrollWithMouse;

  if( !ImGui::Begin( "Navmesh Viewer", &m_showNavmeshWindow, window_flags ) )
  {
    ImGui::End();
    return;
  }

  // Auto-build navmesh when window is opened and zone is selected
  if( m_needsNavmeshRebuild || ( m_selectedZone && m_currentNavmeshZoneId != m_selectedZone->id && m_navmeshIndexCount
                                 == 0 ) )
  {
    if( m_selectedZone )
    {
      buildNavmeshGeometry();
      m_needsNavmeshRebuild = false;
    }
  }

  ImGui::SameLine();

  // Disable the button if no zone is selected or no navi provider
  bool canBuildNavmesh = m_selectedZone && m_pNaviProvider;
  if( !canBuildNavmesh )
  {
    ImGui::BeginDisabled();
  }

  if( !canBuildNavmesh )
  {
    ImGui::EndDisabled();
    if( !m_selectedZone )
    {
      ImGui::SameLine();
      ImGui::TextColored( ImVec4( 1.0f, 0.5f, 0.0f, 1.0f ), "(No zone selected)" );
    }
    else if( !m_pNaviProvider )
    {
      ImGui::SameLine();
      ImGui::TextColored( ImVec4( 1.0f, 0.5f, 0.0f, 1.0f ), "(No NaviProvider)" );
    }
  }

  // Add some debug info
  ImGui::Separator();
  ImGui::Text( "Current zone: %s", m_selectedZone ? m_selectedZone->name.c_str() : "None" );
  ImGui::Text( "Zone ID: %u", m_selectedZone ? m_selectedZone->id : 0 );
  ImGui::Text( "NavMesh available: %s", m_pNaviProvider && m_pNaviProvider->getNavMesh() ? "Yes" : "No" );

  // Add OBJ model info with more detailed status
  if( m_objLoaded )
  {
    ImGui::TextColored( ImVec4( 0.0f, 1.0f, 0.0f, 1.0f ), "OBJ Model loaded: %s",
                        m_currentObjPath.c_str() );
    ImGui::Text( "Model stats: %zu vertices, %d indices",
                 m_objModel.vertices.size(), m_objModel.indexCount );
  }
  else
  {
    ImGui::TextColored( ImVec4( 1.0f, 0.5f, 0.0f, 1.0f ), "No OBJ Model available" );
  }

  // Add radio buttons to switch between navmesh and OBJ model
  if( m_objLoaded )
  {
    ImGui::Separator();
    ImGui::Text( "Visualization Mode:" );

    // Store old state to detect changes
    bool oldShowObj = m_showObjModel;

    // Clearer radio button labels
    if( ImGui::RadioButton( "Show NavMesh", !m_showObjModel ) )
    {
      m_showObjModel = false;
    }
    ImGui::SameLine();
    if( ImGui::RadioButton( "Show 3D Model", m_showObjModel ) )
    {
      m_showObjModel = true;
    }

    // If we changed modes, force a redraw
    if( oldShowObj != m_showObjModel )
    {
      printf( "Switched visualization mode: showObjModel = %d\n", m_showObjModel );
    }

    // Add a refresh button
    if( ImGui::Button( "Refresh Visualization" ) )
    {
      // Force rebuild of the appropriate geometry
      if( m_showObjModel )
      {
        cleanupObjModel();
        checkForObjFile();
      }
      else
      {
        cleanupNavmeshGeometry();
        buildNavmeshGeometry();
      }
    }
  }

  // Add world editing controls
  if( ImGui::CollapsingHeader( "World Editing" ) )
  {
    ImGui::Checkbox( "World Editing Mode", &m_worldEditingMode );

    if( m_showClickMarker )
    {
      ImGui::Text( "Last click: (%.2f, %.2f, %.2f)",
                   m_lastClickWorldPos.x, m_lastClickWorldPos.y, m_lastClickWorldPos.z );

      if( ImGui::Button( "Clear Marker" ) )
      {
        m_showClickMarker = false;
      }

      ImGui::SameLine();
      if( ImGui::Button( "Copy Position" ) )
      {
        std::string posStr = fmt::format( "{:.2f}, {:.2f}, {:.2f}",
                                          m_lastClickWorldPos.x, m_lastClickWorldPos.y, m_lastClickWorldPos.z );
        ImGui::SetClipboardText( posStr.c_str() );
      }
    }

    ImGui::Text( "Right-click on geometry to get world position" );
  }


  // Camera controls - only update sliders if not actively using mouse controls
  if( ImGui::CollapsingHeader( "Camera Controls" ) )
  {
    // Disable sliders when mouse controls are active
    if( m_navCameraControlActive )
    {
      ImGui::BeginDisabled();
    }

    if( ImGui::SliderFloat( "Distance", &m_navCameraDistance, 1.0f, 500.0f ) )
    {
      m_navCameraDistance = glm::clamp( m_navCameraDistance, 1.0f, 500.0f );
      updateNavmeshCamera();
    }

    if( ImGui::SliderFloat( "Yaw", &m_navCameraYaw, -180.0f, 180.0f ) )
    {
      // Keep yaw in range
      while( m_navCameraYaw > 180.0f ) m_navCameraYaw -= 360.0f;
      while( m_navCameraYaw < -180.0f ) m_navCameraYaw += 360.0f;
      updateNavmeshCamera();
    }

    if( ImGui::SliderFloat( "Pitch", &m_navCameraPitch, -89.0f, 89.0f ) )
    {
      m_navCameraPitch = glm::clamp( m_navCameraPitch, -89.0f, 89.0f );
      updateNavmeshCamera();
    }

    if( m_navCameraControlActive )
    {
      ImGui::EndDisabled();
    }

    // Target position controls
    ImGui::Text( "Target Position:" );
    bool targetChanged = false;
    targetChanged |= ImGui::SliderFloat( "Target X", &m_navCameraTarget.x, -1000.0f, 1000.0f );
    targetChanged |= ImGui::SliderFloat( "Target Y", &m_navCameraTarget.y, -100.0f, 100.0f );
    targetChanged |= ImGui::SliderFloat( "Target Z", &m_navCameraTarget.z, -1000.0f, 1000.0f );

    if( targetChanged )
    {
      updateNavmeshCamera();
    }

    if( ImGui::Button( "Reset Camera" ) )
    {
      m_navCameraDistance = 100.0f;
      m_navCameraYaw = 0.0f;
      m_navCameraPitch = -30.0f;
      m_navCameraTarget = glm::vec3( 0.0f, 0.0f, 0.0f );
      m_navCameraControlActive = false;
      updateNavmeshCamera();
    }

    if( ImGui::Button( "Top View" ) )
    {
      m_navCameraYaw = 0.0f;
      m_navCameraPitch = -89.0f;
      m_navCameraDistance = 200.0f;
      m_navCameraControlActive = false;
      updateNavmeshCamera();
    }

    ImGui::SameLine();

    if( ImGui::Button( "Side View" ) )
    {
      m_navCameraYaw = 90.0f;
      m_navCameraPitch = 0.0f;
      m_navCameraDistance = 100.0f;
      m_navCameraControlActive = false;
      updateNavmeshCamera();
    }

    // Reset mouse control flag after a short time of inactivity
    static float lastMouseTime = 0.0f;
    if( m_navCameraControlActive )
    {
      lastMouseTime = ImGui::GetTime();
    }
    else if( ImGui::GetTime() - lastMouseTime > 0.5f )
    {
      // Half second delay
      m_navCameraControlActive = false;
    }
  }

  // Get available content region
  ImVec2 contentRegion = ImGui::GetContentRegionAvail();
  if( contentRegion.x > 0 && contentRegion.y > 0 )
  {
    // Create child window for 3D rendering
    if( ImGui::BeginChild( "NavmeshRender", contentRegion, true, ImGuiWindowFlags_NoScrollbar |
                                                                 ImGuiWindowFlags_NoScrollWithMouse ) )
    {
      renderNavmesh();
    }
    ImGui::EndChild();
  }

  ImGui::End();

  // If window was just closed, clean up geometry to free memory
  if( !m_showNavmeshWindow )
  {
    cleanupNavmeshGeometry();
    if( m_objLoaded )
    {
      cleanupObjModel();
    }
  }
}

void LgbViewer::showZoneList()
{
  // Search input
  ImGui::Text( "Search Zones:" );
  ImGui::SetNextItemWidth( -1 );
  if( ImGui::InputText( "##ZoneSearch", m_searchBuffer, sizeof( m_searchBuffer ) ) )
  {
    updateSearchFilter();
  }

  ImGui::Separator();

  // Zone list
  if( ImGui::BeginChild( "ZoneList", ImVec2( 0, 300 ), true, ImGuiWindowFlags_HorizontalScrollbar ) )
  {
    for( int i = 0; i < static_cast< int >( m_filteredZones.size() ); ++i )
    {
      const auto& zone = m_filteredZones[ i ];

      bool isSelected = ( m_selectedZoneId == zone->id );
      if( ImGui::Selectable( zone->displayText.c_str(), isSelected ) )
      {
        int oldSelectedIndex = m_selectedIndex;
        uint32_t oldSelectedId = m_selectedZoneId;

        m_selectedIndex = i;
        m_selectedZoneId = zone->id;
        m_selectedZone = zone;

        // Only trigger selection changed if it actually changed
        if( oldSelectedId != m_selectedZoneId )
        {
          onSelectionChanged();
        }
      }

      // Tooltip
      if( ImGui::IsItemHovered() )
      {
        ImGui::BeginTooltip();
        ImGui::Text( "Zone ID: %u", zone->id );
        ImGui::Text( "Name: %s", zone->name.c_str() );
        ImGui::Text( "Region: %u", zone->data.Region );
        ImGui::Text( "Area: %u", zone->data.Area );
        ImGui::EndTooltip();
      }
    }
  }
  ImGui::EndChild();
}

void LgbViewer::showZoneDetails()
{
  if( !m_selectedZone )
  {
    ImGui::TextDisabled( "No zone selected - Click on a zone from the list above" );
    return;
  }

  const auto& zone = *m_selectedZone;
  const auto& data = zone.data;

  ImGui::Text( "Selected Zone Details:" );
  ImGui::Separator();

  if( ImGui::BeginChild( "ZoneDetails", ImVec2( 0, 0 ), false, ImGuiWindowFlags_HorizontalScrollbar ) )
  {
    // Basic Information
    if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
    {
      ImGui::Indent();
      ImGui::Text( "Zone ID: %u", zone.id );
      ImGui::Text( "Name: %s", zone.name.c_str() );
      ImGui::Text( "LVB: %s", zone.lvb.c_str() );
      ImGui::Unindent();
    }

    // Geographic Information
    if( ImGui::CollapsingHeader( "Geographic", ImGuiTreeNodeFlags_DefaultOpen ) )
    {
      ImGui::Indent();
      ImGui::Text( "Region: %u", data.Region );
      ImGui::Text( "Sub Region: %u", data.SubRegion );
      ImGui::Text( "Area: %u", data.Area );
      ImGui::Text( "Map: %u", data.Map );
      ImGui::Unindent();
    }

    // Visual/Audio
    if( ImGui::CollapsingHeader( "Visual & Audio" ) )
    {
      ImGui::Indent();
      ImGui::Text( "Region Icon: %d", data.RegionIcon );
      ImGui::Text( "Area Icon: %d", data.AreaIcon );
      ImGui::Text( "BGM: %u", data.BGM );
      ImGui::Unindent();
    }

    // Game Mechanics
    if( ImGui::CollapsingHeader( "Game Mechanics" ) )
    {
      ImGui::Indent();
      ImGui::Text( "Event Handler: %u", data.EventHandler );
      ImGui::Text( "Aetheryte: %d", data.Aetheryte );
      ImGui::Text( "Fixed Time: %d", data.FixedTime );
      ImGui::Text( "Weather Rate: %u", data.WeatherRate );
      ImGui::Text( "Quest Battle: %u", data.QuestBattle );
      ImGui::Unindent();
    }

    // Zone Properties
    if( ImGui::CollapsingHeader( "Zone Properties" ) )
    {
      ImGui::Indent();
      ImGui::Text( "Battalion Mode: %u", data.BattalionMode );
      ImGui::Text( "Exclusive Type: %u", data.ExclusiveType );
      ImGui::Text( "Intended Use: %u", data.IntendedUse );
      ImGui::Text( "Breath: %u", data.Breath );
      ImGui::Text( "Resident: %u", data.Resident );
      ImGui::Text( "Treasure Obtained Flag: %d", data.TreasureObtainedFlag );
      ImGui::Text( "Achievement Index: %d", data.AchievementIndex );
      ImGui::Unindent();
    }

    // Flags & Settings
    if( ImGui::CollapsingHeader( "Flags & Settings" ) )
    {
      ImGui::Indent();
      ImGui::Text( "PvP Action: %s", data.IsPvPAction ? "Yes" : "No" );
      ImGui::Text( "Mount Allowed: %s", data.Mount ? "Yes" : "No" );
      ImGui::Text( "Stealth: %s", data.Stealth ? "Yes" : "No" );
      ImGui::Text( "PC Search: %s", data.PCSearch ? "Yes" : "No" );
      ImGui::Unindent();
    }

    // Unknown/Debug Fields
    if( ImGui::CollapsingHeader( "Debug/Unknown Fields" ) )
    {
      ImGui::Indent();
      ImGui::Text( "Unknown1: %u", data.Unknown1 );
      ImGui::Text( "Unknown2: %u", data.Unknown2 );
      ImGui::Text( "Unknown3: %u", data.Unknown3 );
      ImGui::Text( "Unknown4: %u", data.Unknown4 );
      ImGui::Unindent();
    }

    ImGui::Separator();

    if( ImGui::Button( "Show Map" ) )
    {
      if( data.Map > 0 )
      {
        m_showMapWindow = true;
      }
    }
    ImGui::SameLine();
    if( ImGui::Button( "Clear Selection" ) )
    {
      m_selectedIndex = -1;
      m_selectedZoneId = 0;
      m_selectedZone = nullptr;
      onSelectionCleared();
    }
    ImGui::SameLine();

    if( ImGui::Button( "Show Navmesh" ) )
    {
      m_showNavmeshWindow = true;
    }
    ImGui::SameLine();
  }
  ImGui::EndChild();
}


void LgbViewer::showMapWindow()
{
  if( !m_showMapWindow || m_mapTextureId == 0 )
    return;

  ImGui::Begin( "Map Viewer", &m_showMapWindow, ImGuiWindowFlags_MenuBar );

  // Menu bar with map info and controls
  if( ImGui::BeginMenuBar() )
  {
    ImGui::Text( "Map ID: %u | Size: %dx%d", m_currentMapId, m_mapWidth, m_mapHeight );
    ImGui::Separator();

    if( ImGui::Button( "Reset Zoom" ) )
    {
      m_zoomLevel = 1.0f;
    }
    if( ImGui::Button( "Fit to Window" ) )
    {
      m_zoomLevel = -1.0f;
    }
    ImGui::EndMenuBar();
  }

  // Get available content region
  ImVec2 contentRegion = ImGui::GetContentRegionAvail();

  // Calculate image size first
  ImVec2 imageSize;
  if( m_zoomLevel <= 0.0f )
  {
    // Fit to window mode
    float scaleX = contentRegion.x / static_cast< float >( m_mapWidth );
    float scaleY = contentRegion.y / static_cast< float >( m_mapHeight );
    float scale = std::min( scaleX, scaleY );
    imageSize = ImVec2( m_mapWidth * scale, m_mapHeight * scale );
  }
  else
  {
    // Manual zoom mode
    imageSize = ImVec2( m_mapWidth * m_zoomLevel, m_mapHeight * m_zoomLevel );
  }

  // Determine if we need scrollbars
  bool needsScrollbars = ( imageSize.x > contentRegion.x || imageSize.y > contentRegion.y );

  // Use a child region - only add scrollbars if actually needed
  ImGuiWindowFlags childFlags = ImGuiWindowFlags_NoScrollWithMouse;
  if( needsScrollbars )
  {
    childFlags |= ImGuiWindowFlags_HorizontalScrollbar;
  }

  if( ImGui::BeginChild( "MapScrollRegion", contentRegion, false, childFlags ) )
  {
    // Store the current scroll position for zoom centering
    float oldScrollX = ImGui::GetScrollX();
    float oldScrollY = ImGui::GetScrollY();
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 childPos = ImGui::GetWindowPos();

    // Handle focus request - center view on the focused position
    if( m_shouldFocusOnMap )
    {
      // Convert world position to map coordinates
      glm::vec2 mapPos = get2dPosFrom3d( m_focusWorldPos.x, m_focusWorldPos.z, m_mapScale );

      // Convert map coordinates to normalized coordinates (0.0 to 1.0)
      float normalizedX = mapPos.x / 2048.0f;
      float normalizedY = mapPos.y / 2048.0f;

      // Convert to image pixel coordinates
      float imagePixelX = normalizedX * imageSize.x;
      float imagePixelY = normalizedY * imageSize.y;

      // Get the child window content size
      ImVec2 childContentSize = ImGui::GetContentRegionAvail();

      // Calculate scroll position to center the focus point
      float targetScrollX = imagePixelX - ( childContentSize.x * 0.5f );
      float targetScrollY = imagePixelY - ( childContentSize.y * 0.5f );

      // Clamp scroll values to valid range
      float maxScrollX = std::max( 0.0f, imageSize.x - childContentSize.x );
      float maxScrollY = std::max( 0.0f, imageSize.y - childContentSize.y );

      targetScrollX = std::max( 0.0f, std::min( targetScrollX, maxScrollX ) );
      targetScrollY = std::max( 0.0f, std::min( targetScrollY, maxScrollY ) );

      // Apply the scroll
      ImGui::SetScrollX( targetScrollX );
      ImGui::SetScrollY( targetScrollY );

      // Clear the focus flag
      m_shouldFocusOnMap = false;
    }

    // Handle zoom controls - only when mouse is over the child window
    if( ImGui::IsWindowHovered() )
    {
      float wheel = ImGui::GetIO().MouseWheel;
      if( wheel != 0.0f )
      {
        float oldZoom = m_zoomLevel;
        m_zoomLevel += wheel * 0.1f;
        m_zoomLevel = std::max( 0.1f, std::min( m_zoomLevel, 10.0f ) );

        // If zoom actually changed, recalculate image size and adjust scroll to zoom toward mouse
        if( oldZoom != m_zoomLevel && m_zoomLevel > 0.0f )
        {
          // Recalculate image size with new zoom
          ImVec2 newImageSize = ImVec2( m_mapWidth * m_zoomLevel, m_mapHeight * m_zoomLevel );

          // Calculate mouse position relative to the old image
          ImVec2 mouseRelativeToChild = ImVec2( mousePos.x - childPos.x, mousePos.y - childPos.y );
          ImVec2 mouseRelativeToImage = ImVec2(
            ( mouseRelativeToChild.x + oldScrollX ) / imageSize.x,
            ( mouseRelativeToChild.y + oldScrollY ) / imageSize.y
          );

          // Update image size for next frame
          imageSize = newImageSize;

          // Calculate new scroll position to keep mouse point consistent
          float newScrollX = ( mouseRelativeToImage.x * newImageSize.x ) - mouseRelativeToChild.x;
          float newScrollY = ( mouseRelativeToImage.y * newImageSize.y ) - mouseRelativeToChild.y;

          // Apply scroll on next frame
          ImGui::SetScrollX( std::max( 0.0f, newScrollX ) );
          ImGui::SetScrollY( std::max( 0.0f, newScrollY ) );
        }
      }
    }

    // Center the image if it's smaller than the content region
    ImVec2 availableSize = ImGui::GetContentRegionAvail();
    ImVec2 cursorPos = ImGui::GetCursorPos();

    if( imageSize.x < availableSize.x )
    {
      cursorPos.x += ( availableSize.x - imageSize.x ) * 0.5f;
    }
    if( imageSize.y < availableSize.y )
    {
      cursorPos.y += ( availableSize.y - imageSize.y ) * 0.5f;
    }
    ImGui::SetCursorPos( cursorPos );

    // Store image position for BNPC icon drawing
    ImVec2 imagePos = ImGui::GetCursorScreenPos();

    // Display the map image
    ImGui::Image( reinterpret_cast< void * >( static_cast< intptr_t >( m_mapTextureId ) ), imageSize );

    // Check if mouse is hovering over the image
    bool mouseOverImage = ImGui::IsItemHovered();

    // Draw focus marker if we have a focus position
    if( m_focusWorldPos != glm::vec3( 0.0f ) )
    {
      // Convert world position to screen position for drawing the marker
      glm::vec2 mapPos = get2dPosFrom3d( m_focusWorldPos.x, m_focusWorldPos.z, m_mapScale );

      // Convert to normalized coordinates
      float normalizedX = mapPos.x / 2048.0f;
      float normalizedY = mapPos.y / 2048.0f;

      // Convert to screen position
      ImVec2 markerScreenPos = ImVec2(
        imagePos.x + normalizedX * imageSize.x,
        imagePos.y + normalizedY * imageSize.y
      );

      // Draw the focus marker
      ImDrawList *drawList = ImGui::GetWindowDrawList();
      float markerSize = 8.0f;

      // Draw a cross marker
      drawList->AddLine(
        ImVec2( markerScreenPos.x - markerSize, markerScreenPos.y ),
        ImVec2( markerScreenPos.x + markerSize, markerScreenPos.y ),
        IM_COL32( 255, 0, 0, 255 ), 2.0f
      );
      drawList->AddLine(
        ImVec2( markerScreenPos.x, markerScreenPos.y - markerSize ),
        ImVec2( markerScreenPos.x, markerScreenPos.y + markerSize ),
        IM_COL32( 255, 0, 0, 255 ), 2.0f
      );

      // Draw a circle around it
      drawList->AddCircle( markerScreenPos, markerSize + 2.0f, IM_COL32( 255, 255, 255, 255 ), 12, 2.0f );
    }

    // Handle panning (drag to move when zoomed in)
    if( ImGui::IsItemHovered() && ImGui::IsMouseDragging( ImGuiMouseButton_Left ) )
    {
      ImVec2 delta = ImGui::GetIO().MouseDelta;
      ImGui::SetScrollX( ImGui::GetScrollX() - delta.x );
      ImGui::SetScrollY( ImGui::GetScrollY() - delta.y );
    }

    // Display nav mesh warning if no nav provider is loaded
    if( !m_pNaviProvider )
    {
      // Get draw list for drawing overlay text
      ImDrawList *drawList = ImGui::GetWindowDrawList();

      // Get the child window bounds for clipping
      ImVec2 childWindowPos = ImGui::GetWindowPos();
      ImVec2 childWindowSize = ImGui::GetWindowSize();

      // Calculate visible area of the image (intersection with child window)
      ImVec2 visibleImageMin = ImVec2(
        std::max( imagePos.x, childWindowPos.x ),
        std::max( imagePos.y, childWindowPos.y )
      );

      ImVec2 visibleImageMax = ImVec2(
        std::min( imagePos.x + imageSize.x, childWindowPos.x + childWindowSize.x ),
        std::min( imagePos.y + imageSize.y, childWindowPos.y + childWindowSize.y )
      );

      // Only draw if there's a visible area
      if( visibleImageMin.x < visibleImageMax.x && visibleImageMin.y < visibleImageMax.y )
      {
        // Position text at the top-center of the visible image area
        ImVec2 textPos = ImVec2(
          ( visibleImageMin.x + visibleImageMax.x ) * 0.5f,
          visibleImageMin.y + 20.0f
        );

        // Warning text
        const char *warningText = "No nav mesh found!";
        ImVec2 textSize = ImGui::CalcTextSize( warningText );

        // Center the text horizontally
        textPos.x -= textSize.x * 0.5f;

        // Ensure text stays within visible bounds
        if( textPos.y + textSize.y > visibleImageMax.y )
        {
          textPos.y = visibleImageMax.y - textSize.y - 5.0f;
        }

        // Draw background rectangle for better visibility
        ImVec2 rectMin = ImVec2( textPos.x - 10.0f, textPos.y - 5.0f );
        ImVec2 rectMax = ImVec2( textPos.x + textSize.x + 10.0f, textPos.y + textSize.y + 5.0f );
        drawList->AddRectFilled( rectMin, rectMax, IM_COL32( 0, 0, 0, 180 ) ); // Semi-transparent black background
        drawList->AddRect( rectMin, rectMax, IM_COL32( 255, 0, 0, 255 ), 2.0f ); // Red border

        // Draw the warning text in red
        drawList->AddText( textPos, IM_COL32( 255, 0, 0, 255 ), warningText );
      }
    }

    // Display cursor position information when hovering over the image
    if( mouseOverImage )
    {
      ImDrawList *drawList = ImGui::GetWindowDrawList();

      // Get the child window bounds
      ImVec2 childWindowPos = ImGui::GetWindowPos();
      ImVec2 childWindowSize = ImGui::GetWindowSize();

      // Calculate mouse position relative to the image
      ImVec2 mouseRelativeToImage = ImVec2(
        mousePos.x - imagePos.x,
        mousePos.y - imagePos.y
      );

      // Convert to normalized coordinates (0.0 to 1.0)
      float normalizedX = mouseRelativeToImage.x / imageSize.x;
      float normalizedY = mouseRelativeToImage.y / imageSize.y;

      // Convert to map coordinates (assuming 2048x2048 map)
      float mapX = normalizedX * 2048.0f;
      float mapY = normalizedY * 2048.0f;

      // Convert to estimated world coordinates using your existing function
      // Note: This is the inverse of get2dPosFrom3d
      float worldX = ( mapX - 1024.0f ) / ( m_mapScale / 100.0f );
      float worldZ = ( mapY - 1024.0f ) / ( m_mapScale / 100.0f );

      // Format the position strings
      char mapPosText[ 128 ];
      char worldPosText[ 128 ];
      snprintf( mapPosText, sizeof( mapPosText ), "Map: %.1f, %.1f", mapX, mapY );
      snprintf( worldPosText, sizeof( worldPosText ), "World: %.1f, %.1f", worldX, worldZ );

      if( m_pNaviProvider )
      {
        auto p1 = m_pNaviProvider->findNearestPosition( worldX, worldZ );

        snprintf( worldPosText, sizeof( worldPosText ), "World-Est: %.1f, %.1f, %.1f", p1.x, p1.y, p1.z );
      }

      // Calculate text sizes
      ImVec2 mapTextSize = ImGui::CalcTextSize( mapPosText );
      ImVec2 worldTextSize = ImGui::CalcTextSize( worldPosText );
      float maxTextWidth = std::max( mapTextSize.x, worldTextSize.x );
      float totalTextHeight = mapTextSize.y + worldTextSize.y + 5.0f; // 5px spacing

      // Position in top-right corner of visible area
      ImVec2 visibleImageMin = ImVec2(
        std::max( imagePos.x, childWindowPos.x ),
        std::max( imagePos.y, childWindowPos.y )
      );

      ImVec2 visibleImageMax = ImVec2(
        std::min( imagePos.x + imageSize.x, childWindowPos.x + childWindowSize.x ),
        std::min( imagePos.y + imageSize.y, childWindowPos.y + childWindowSize.y )
      );

      // Position text in top-right corner of visible image
      ImVec2 textPos = ImVec2(
        visibleImageMax.x - maxTextWidth - 20.0f, // 20px margin from right edge
        visibleImageMin.y + 10.0f // 10px margin from top edge
      );

      // Ensure text doesn't go outside visible bounds
      if( textPos.x < visibleImageMin.x )
        textPos.x = visibleImageMin.x + 10.0f;
      if( textPos.y + totalTextHeight > visibleImageMax.y )
        textPos.y = visibleImageMax.y - totalTextHeight - 10.0f;

      // Draw background rectangle
      ImVec2 rectMin = ImVec2( textPos.x - 8.0f, textPos.y - 5.0f );
      ImVec2 rectMax = ImVec2( textPos.x + maxTextWidth + 8.0f, textPos.y + totalTextHeight + 5.0f );
      drawList->AddRectFilled( rectMin, rectMax, IM_COL32( 0, 0, 0, 200 ) ); // Semi-transparent black background
      drawList->AddRect( rectMin, rectMax, IM_COL32( 100, 100, 100, 255 ), 1.0f ); // Gray border

      // Draw the text
      drawList->AddText( ImVec2( textPos.x, textPos.y ), IM_COL32( 255, 255, 255, 255 ), mapPosText );
      drawList->AddText( ImVec2( textPos.x, textPos.y + mapTextSize.y + 5.0f ), IM_COL32( 255, 255, 255, 255 ),
                         worldPosText );
    }
  }
  ImGui::EndChild();

  // Show zoom level and controls in bottom-left corner
  ImVec2 windowPos = ImGui::GetWindowPos();
  ImVec2 windowSize = ImGui::GetWindowSize();
  ImGui::SetCursorPos( ImVec2( 10, windowSize.y - 80 ) );

  if( m_zoomLevel > 0.0f )
  {
    ImGui::Text( "Zoom: %.1fx", m_zoomLevel );
  }
  else
  {
    ImGui::Text( "Zoom: Fit to Window" );
  }
  ImGui::Text( "Mouse wheel: Zoom | Left drag: Pan" );

  ImGui::End();
}

std::vector< uint8_t > LgbViewer::decompressDXT1( const uint8_t *compressedData, int width, int height )
{
  std::vector< uint8_t > decompressed( width * height * 4 ); // RGBA output

  const int blockCountX = ( width + 3 ) / 4;
  const int blockCountY = ( height + 3 ) / 4;

  for( int by = 0; by < blockCountY; ++by )
  {
    for( int bx = 0; bx < blockCountX; ++bx )
    {
      const uint8_t *block = compressedData + ( by * blockCountX + bx ) * 8;

      // Read color endpoints (little endian)
      uint16_t color0 = block[ 0 ] | ( block[ 1 ] << 8 );
      uint16_t color1 = block[ 2 ] | ( block[ 3 ] << 8 );
      uint32_t indices = block[ 4 ] | ( block[ 5 ] << 8 ) | ( block[ 6 ] << 16 ) | ( block[ 7 ] << 24 );

      // Convert RGB565 to RGB888
      uint8_t r0 = ( ( color0 >> 11 ) & 0x1F ) << 3; // 5 bits -> 8 bits
      uint8_t g0 = ( ( color0 >> 5 ) & 0x3F ) << 2; // 6 bits -> 8 bits
      uint8_t b0 = ( color0 & 0x1F ) << 3; // 5 bits -> 8 bits

      uint8_t r1 = ( ( color1 >> 11 ) & 0x1F ) << 3;
      uint8_t g1 = ( ( color1 >> 5 ) & 0x3F ) << 2;
      uint8_t b1 = ( color1 & 0x1F ) << 3;

      // Generate color palette (4 colors)
      uint8_t colors[ 4 ][ 4 ]; // [color_index][rgba]
      colors[ 0 ][ 0 ] = r0;
      colors[ 0 ][ 1 ] = g0;
      colors[ 0 ][ 2 ] = b0;
      colors[ 0 ][ 3 ] = 255;
      colors[ 1 ][ 0 ] = r1;
      colors[ 1 ][ 1 ] = g1;
      colors[ 1 ][ 2 ] = b1;
      colors[ 1 ][ 3 ] = 255;

      if( color0 > color1 )
      {
        // 4-color mode (opaque)
        colors[ 2 ][ 0 ] = ( 2 * r0 + r1 ) / 3;
        colors[ 2 ][ 1 ] = ( 2 * g0 + g1 ) / 3;
        colors[ 2 ][ 2 ] = ( 2 * b0 + b1 ) / 3;
        colors[ 2 ][ 3 ] = 255;

        colors[ 3 ][ 0 ] = ( r0 + 2 * r1 ) / 3;
        colors[ 3 ][ 1 ] = ( g0 + 2 * g1 ) / 3;
        colors[ 3 ][ 2 ] = ( b0 + 2 * b1 ) / 3;
        colors[ 3 ][ 3 ] = 255;
      }
      else
      {
        // 3-color mode (with transparency)
        colors[ 2 ][ 0 ] = ( r0 + r1 ) / 2;
        colors[ 2 ][ 1 ] = ( g0 + g1 ) / 2;
        colors[ 2 ][ 2 ] = ( b0 + b1 ) / 2;
        colors[ 2 ][ 3 ] = 255;

        colors[ 3 ][ 0 ] = 0;
        colors[ 3 ][ 1 ] = 0;
        colors[ 3 ][ 2 ] = 0;
        colors[ 3 ][ 3 ] = 0; // Transparent
      }

      // Decode 16 pixels in this 4x4 block
      for( int py = 0; py < 4 && ( by * 4 + py ) < height; ++py )
      {
        for( int px = 0; px < 4 && ( bx * 4 + px ) < width; ++px )
        {
          // Each pixel uses 2 bits for color index
          int pixelIndex = ( py * 4 + px ) * 2;
          int colorIndex = ( indices >> pixelIndex ) & 0x3;

          // Calculate output position
          int outputX = bx * 4 + px;
          int outputY = by * 4 + py;
          int outputIndex = ( outputY * width + outputX ) * 4;

          // Write RGBA pixel
          decompressed[ outputIndex + 0 ] = colors[ colorIndex ][ 0 ]; // R
          decompressed[ outputIndex + 1 ] = colors[ colorIndex ][ 1 ]; // G
          decompressed[ outputIndex + 2 ] = colors[ colorIndex ][ 2 ]; // B
          decompressed[ outputIndex + 3 ] = colors[ colorIndex ][ 3 ]; // A
        }
      }
    }
  }

  return decompressed;
}

ImVec2 LgbViewer::worldToScreenPos( float worldX, float worldZ, const ImVec2& imagePos, const ImVec2& imageSize )
{
  // Convert 3D world position to 2D map coordinates using your existing function
  glm::vec2 mapPos = get2dPosFrom3d( worldX, worldZ, m_mapScale );

  // Convert map coordinates to screen coordinates
  // Assuming map coordinates are in range [0, 2048] for a 2048x2048 map
  float normalizedX = mapPos.x / 2048.0f;
  float normalizedY = mapPos.y / 2048.0f;

  // Convert to screen position relative to the image
  ImVec2 screenPos;
  screenPos.x = imagePos.x + ( normalizedX * imageSize.x );
  screenPos.y = imagePos.y + ( normalizedY * imageSize.y );

  return screenPos;
}

void LgbViewer::loadMapTexture( uint32_t mapId )
{
  auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();
  auto mapEntry = exdD.getRow< Excel::Map >( mapId );
  if( !mapEntry )
    return;
  auto mapData = mapEntry->data();

  m_mapScale = mapData.Scale;
  auto mapPath = mapEntry->getString( mapData.Path );
  std::string file = mapPath;
  file.erase( std::remove( file.begin(), file.end(), '/' ), file.end() );
  file += "_m.tex";

  auto& gameData = Engine::Service< xiv::dat::GameData >::ref();

  auto mapFile = gameData.getFile( "ui/map/" + mapPath + "/" + file );
  if( !mapFile )
    return;

  // Get header and data sections separately
  auto headerData = mapFile->access_data_sections().at( 0 );
  auto dxtData = mapFile->access_data_sections().at( 1 );

  if( headerData.size() < 16 || dxtData.empty() )
    return;

  const uint8_t *header = reinterpret_cast< const uint8_t * >( headerData.data() );

  // Parse header information (adjust these offsets based on your actual header format)
  uint32_t width = *reinterpret_cast< const uint16_t * >( header + 8 );
  uint32_t height = *reinterpret_cast< const uint16_t * >( header + 10 );
  uint32_t format = *reinterpret_cast< const uint32_t * >( header + 12 ); // Should indicate DXT1

  // Validate dimensions
  if( width == 0 || height == 0 || width > 4096 || height > 4096 )
    return;

  // Calculate expected DXT1 size
  size_t expectedSize = ( ( width + 3 ) / 4 ) * ( ( height + 3 ) / 4 ) * 8; // 8 bytes per 4x4 block
  if( dxtData.size() < expectedSize )
    return;

  // Get raw DXT1 data
  const uint8_t *compressedData = reinterpret_cast< const uint8_t * >( dxtData.data() );

  // Decompress DXT1 to RGBA
  auto decompressedData = decompressDXT1( compressedData, width, height );

  // Clean up previous texture
  clearMapTexture();

  // Create OpenGL texture
  glGenTextures( 1, &m_mapTextureId );
  glBindTexture( GL_TEXTURE_2D, m_mapTextureId );

  // Set texture parameters
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

  // Upload texture data
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, decompressedData.data() );

  glBindTexture( GL_TEXTURE_2D, 0 );

  m_mapWidth = width;
  m_mapHeight = height;
  m_currentMapId = mapId;
  m_showMapWindow = true;

  // Optional: Debug output
  Engine::Logger::info( "Loaded map texture: {}x{}, format: {}, compressed size: {}, decompressed size: {}",
                        width, height, format, dxtData.size(), decompressedData.size() );
}

void LgbViewer::clearMapTexture()
{
  if( m_mapTextureId != 0 )
  {
    glDeleteTextures( 1, &m_mapTextureId );
    m_mapTextureId = 0;
  }
}

SGB_FILE* LgbViewer::getCachedSgbFile( const std::string& assetPath )
{
  // Check if already cached
  auto it = m_cachedSgbFiles.find( assetPath );
  if( it != m_cachedSgbFiles.end() )
  {
    return it->second.get();
  }

  // Load and cache the SGB file
  auto& gameData = Engine::Service< xiv::dat::GameData >::ref();
  auto file = gameData.getFile( assetPath );
  if( file )
  {
    auto sections = file->get_data_sections();
    if( !sections.empty() && !sections.at( 0 ).empty() )
    {
      auto dataSection = &sections.at( 0 )[ 0 ];
      try
      {
        auto sgbFile = std::make_unique< SGB_FILE >( &dataSection[ 0 ] );
        SGB_FILE* result = sgbFile.get();
        m_cachedSgbFiles[ assetPath ] = std::move( sgbFile );
        return result;
      }
      catch( const std::exception& e )
      {
        // Handle error
        return nullptr;
      }
    }
  }
  return nullptr;
}

void LgbViewer::refresh()
{
  m_needsRefresh = true;
  m_zoneIds.clear();
  m_cachedZones.clear();
  m_filteredZones.clear(); // For search results
  initializeCache();
  m_lastSearchTerm = "N/A";
}

// Convert screen coordinates to world ray
LgbViewer::Ray LgbViewer::screenToWorldRay( const ImVec2& screenPos, const ImVec2& imageSize )
{
  // Convert screen coordinates to normalized device coordinates (-1 to 1)
  float x = ( 2.0f * screenPos.x ) / imageSize.x - 1.0f;
  float y = 1.0f - ( 2.0f * screenPos.y ) / imageSize.y; // Flip Y axis

  // Create matrices (same as used in rendering)
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           imageSize.x / imageSize.y,
                                           0.1f, 10000.0f );

  // Create inverse matrices
  glm::mat4 invProjection = glm::inverse( projection );
  glm::mat4 invView = glm::inverse( view );

  // Convert NDC to view space
  glm::vec4 rayClip = glm::vec4( x, y, -1.0, 1.0 );
  glm::vec4 rayEye = invProjection * rayClip;
  rayEye = glm::vec4( rayEye.x, rayEye.y, -1.0, 0.0 ); // Set Z to -1 for direction, W to 0

  // Convert to world space
  glm::vec4 rayWorld = invView * rayEye;
  glm::vec3 rayDirection = glm::normalize( glm::vec3( rayWorld ) );

  Ray ray;
  ray.origin = m_navCameraPos;
  ray.direction = rayDirection;

  return ray;
}

// Ray-triangle intersection using Möller-Trumbore algorithm with backface culling
bool LgbViewer::rayTriangleIntersect( const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
                                      float& distance, glm::vec3& normal )
{
  const float EPSILON = 0.0000001f;

  glm::vec3 edge1 = v1 - v0;
  glm::vec3 edge2 = v2 - v0;
  glm::vec3 h = glm::cross( ray.direction, edge2 );
  float a = glm::dot( edge1, h );

  if( a > -EPSILON && a < EPSILON )
  {
    return false; // Ray is parallel to triangle
  }

  float f = 1.0f / a;
  glm::vec3 s = ray.origin - v0;
  float u = f * glm::dot( s, h );

  if( u < 0.0f || u > 1.0f )
  {
    return false;
  }

  glm::vec3 q = glm::cross( s, edge1 );
  float v = f * glm::dot( ray.direction, q );

  if( v < 0.0f || u + v > 1.0f )
  {
    return false;
  }

  // Calculate distance
  float t = f * glm::dot( edge2, q );

  if( t > EPSILON )
  {
    // Ray intersection
    distance = t;

    // Calculate triangle normal
    normal = glm::normalize( glm::cross( edge1, edge2 ) );

    // Backface culling: only accept hits from the front side
    // If dot product is positive, ray is hitting the back of the triangle
    float backfaceCheck = glm::dot( ray.direction, normal );
    if( backfaceCheck > 0.0f )
    {
      return false; // Hit backface, reject
    }

    return true;
  }

  return false;
}

// Cast ray to navmesh geometry
LgbViewer::RayHit LgbViewer::castRayToNavmesh( const Ray& ray )
{
  RayHit hit;

  if( !m_pNaviProvider || m_navmeshIndexCount == 0 )
  {
    return hit;
  }

  // Get navmesh data from provider
  const dtNavMesh *navMesh = m_pNaviProvider->getNavMesh();
  if( !navMesh )
  {
    return hit;
  }

  float closestDistance = FLT_MAX;
  glm::vec3 closestNormal;
  int closestTriangle = -1;

  // Test against all navmesh triangles
  for( int i = 0; i < navMesh->getMaxTiles(); ++i )
  {
    const dtMeshTile *tile = navMesh->getTile( i );
    if( !tile || !tile->header || !tile->dataSize ) continue;

    for( int j = 0; j < tile->header->polyCount; ++j )
    {
      const dtPoly *poly = &tile->polys[ j ];
      if( poly->vertCount < 3 ) continue;

      // Fan triangulation
      for( int k = 1; k < poly->vertCount - 1; ++k )
      {
        const float *v0 = &tile->verts[ poly->verts[ 0 ] * 3 ];
        const float *v1 = &tile->verts[ poly->verts[ k ] * 3 ];
        const float *v2 = &tile->verts[ poly->verts[ k + 1 ] * 3 ];

        glm::vec3 vert0( v0[ 0 ], v0[ 1 ], v0[ 2 ] );
        glm::vec3 vert1( v1[ 0 ], v1[ 1 ], v1[ 2 ] );
        glm::vec3 vert2( v2[ 0 ], v2[ 1 ], v2[ 2 ] );

        float distance;
        glm::vec3 normal;

        if( rayTriangleIntersect( ray, vert0, vert1, vert2, distance, normal ) )
        {
          if( distance < closestDistance )
          {
            closestDistance = distance;
            closestNormal = normal;
            closestTriangle = j; // Store polygon index
            hit.hit = true;
          }
        }
      }
    }
  }

  if( hit.hit )
  {
    hit.position = ray.origin + ray.direction * closestDistance;
    hit.normal = closestNormal;
    hit.distance = closestDistance;
    hit.triangleIndex = closestTriangle;
  }

  return hit;
}

// Cast ray to OBJ model geometry
LgbViewer::RayHit LgbViewer::castRayToObjModel( const Ray& ray )
{
  RayHit hit;

  if( !m_objModel.loaded || m_objModel.vertices.empty() || m_objModel.indices.empty() )
  {
    return hit;
  }

  float closestDistance = FLT_MAX;
  glm::vec3 closestNormal;
  int closestTriangle = -1;

  // Test against all triangles in the OBJ model
  for( size_t i = 0; i < m_objModel.indices.size(); i += 3 )
  {
    if( i + 2 >= m_objModel.indices.size() ) break;

    const glm::vec3& v0 = m_objModel.vertices[ m_objModel.indices[ i ] ].position;
    const glm::vec3& v1 = m_objModel.vertices[ m_objModel.indices[ i + 1 ] ].position;
    const glm::vec3& v2 = m_objModel.vertices[ m_objModel.indices[ i + 2 ] ].position;

    float distance;
    glm::vec3 normal;

    if( rayTriangleIntersect( ray, v0, v1, v2, distance, normal ) )
    {
      if( distance < closestDistance )
      {
        closestDistance = distance;
        closestNormal = normal;
        closestTriangle = static_cast< int >( i / 3 );
        hit.hit = true;
      }
    }
  }

  if( hit.hit )
  {
    hit.position = ray.origin + ray.direction * closestDistance;
    hit.normal = closestNormal;
    hit.distance = closestDistance;
    hit.triangleIndex = closestTriangle;
  }

  return hit;
}

// Unified ray casting method
LgbViewer::RayHit LgbViewer::castRayToGeometry( const Ray& ray )
{
  RayHit bestHit;

  if( m_showObjModel && m_objModel.loaded )
  {
    // Use OBJ model if it's being displayed
    bestHit = castRayToObjModel( ray );
  }
  else
  {
    // Use navmesh
    bestHit = castRayToNavmesh( ray );
  }

  return bestHit;
}

// Add world position marker rendering
void LgbViewer::renderWorldMarker( const glm::vec3& worldPos )
{
  if( !m_showClickMarker ) return;

  // Simple marker implementation - draw a small cross at the clicked position
  // You can expand this to draw a more sophisticated marker

  // For now, we'll just store the position and optionally print it
  // The actual rendering could be added to your existing rendering pipeline
}

// Callback for world clicking - implement your editing logic here
void LgbViewer::onWorldClick( const RayHit& hit )
{
}

void LgbViewer::openEntryViewWidget( std::shared_ptr< InstanceObjectEntry > entry )
{
  // Check if this entry is already open
  for( auto& widget : m_entryViewWidgets )
  {
    if( widget.entry->header.InstanceID == entry->header.InstanceID )
    {
      // Already open, just focus it
      widget.isOpen = true;
      return;
    }
  }

  // Create new widget
  m_entryViewWidgets.emplace_back( entry );
}

void LgbViewer::showEntryViewWidget( EntryViewWidget& widget )
{
  if( !widget.isOpen )
    return;

  ImGui::SetNextWindowSize( ImVec2( 400, 600 ), ImGuiCond_FirstUseEver );

  if( ImGui::Begin( widget.windowTitle.c_str(), &widget.isOpen, ImGuiWindowFlags_MenuBar ) )
  {
    // Menu bar with actions
    if( ImGui::BeginMenuBar() )
    {
      if( ImGui::MenuItem( "Focus in 3D View" ) )
      {
        focusOn3DPosition( widget.entry->header.Transformation.Translation );
      }
      ImGui::EndMenuBar();
    }

    // Show type-specific view
    switch( widget.entry->getType() )
    {
      case eAssetType::SharedGroup:
        showSGEntryView( dynamic_cast< SharedGroupEntry * >( widget.entry.get() ) );
        break;
      case eAssetType::EventObject:
        showEObjEntryView( dynamic_cast< EventObjectEntry * >( widget.entry.get() ) );
        break;
      case eAssetType::ExitRange:
        showExitRangeEntryView( dynamic_cast< ExitRangeEntry* >( widget.entry.get() ) );
        break;
      case eAssetType::PopRange:
        showPopRangeEntryView( dynamic_cast< PopRangeEntry* >( widget.entry.get() ) );
        break;
      case eAssetType::CollisionBox:
        showCollisionBoxEntryView( dynamic_cast< CollisionBoxEntry* >( widget.entry.get() ) );
        break;
      default:
        showUnimplementedEntryView( widget.entry.get() );
        break;
    }
  }
  ImGui::End();
}


void LgbViewer::showSGEntryView( SharedGroupEntry *entry )
{
  ImGui::Text( "Shared Group Entry" );
  ImGui::Separator();

  // Basic information
  if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Instance ID: %u", entry->header.InstanceID );
    ImGui::Text( "Name: %s", entry->name.c_str() );
    ImGui::Text( "Type: %s", getEntryTypeString( entry->getType() ).c_str() );
  }

  // Transform information
  if( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Position: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Translation.x,
                 entry->header.Transformation.Translation.y,
                 entry->header.Transformation.Translation.z );
    ImGui::Text( "Rotation: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Rotation.x,
                 entry->header.Transformation.Rotation.y,
                 entry->header.Transformation.Rotation.z );
    ImGui::Text( "Scale: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Scale.x,
                 entry->header.Transformation.Scale.y,
                 entry->header.Transformation.Scale.z );
  }

  // SG-specific data
  if( ImGui::CollapsingHeader( "Shared Group Data", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Gimmick File: %s", entry->AssetPath.c_str() );

    ImGui::Spacing();
    ImGui::Text( "Extended SGData Fields:" );
    ImGui::Separator();

    // Use the cached SGB file instead of loading it fresh each time
    SGB_FILE* sgbFile1 = getCachedSgbFile( entry->AssetPath );

    if( sgbFile1 )
    {
      auto& sgbFile = *sgbFile1;

      try
      {

        // SGB File Header Information
        if( ImGui::CollapsingHeader( "SGB File Header", ImGuiTreeNodeFlags_DefaultOpen ) )
        {
          ImGui::Text( "Magic: %.4s", sgbFile.header.magic );
          ImGui::Text( "File Size: %u", sgbFile.header.fileSize );
          ImGui::Text( "Chunk ID: %.4s", sgbFile.header.ChunkID );
          ImGui::Text( "Chunk Size: %d", sgbFile.header.ChunkSize );
        }

        // Scene Information
        if( ImGui::CollapsingHeader( "Scene", ImGuiTreeNodeFlags_DefaultOpen ) )
        {
          ImGui::Text( "Layer Group Count: %d", sgbFile.layerGroup.Layer_Count );
          ImGui::Text( "Timeline Count: %d", sgbFile.sgTimelineFolder.SGTimeline_Count );
        }

        // Scene Settings
        if( ImGui::CollapsingHeader( "Scene Settings", ImGuiTreeNodeFlags_DefaultOpen ) )
        {
          ImGui::Text( "Is Partial Output: %s", sgbFile.sceneSettings.IsPartialOutput ? "Yes" : "No" );
          ImGui::Text( "Contains Layer Set Ref: %s", sgbFile.sceneSettings.ContainsLayerSetRef ? "Yes" : "No" );
          ImGui::Text( "Is Dungeon: %s", sgbFile.sceneSettings.IsDungeon ? "Yes" : "No" );
          ImGui::Text( "Exists Grass Data: %s", sgbFile.sceneSettings.ExistsGrassData ? "Yes" : "No" );
          ImGui::Text( "Camera Far Clip Distance: %.3f", sgbFile.sceneSettings.CameraFarClipDistance );
          ImGui::Text( "Main Light Orbit Curve: %.3f", sgbFile.sceneSettings.MainLightOrbitCurve );
          ImGui::Text( "Main Light Orbit Clamp: %.3f", sgbFile.sceneSettings.MainLightOrbitClamp );
          ImGui::Text( "Shadow Far Distance: %.3f", sgbFile.sceneSettings.ShadowFarDistance );
          ImGui::Text( "Shadow Distance Fade: %.3f", sgbFile.sceneSettings.ShadowDistanceFade );
          ImGui::Text( "BG Sky Visibility: %.3f", sgbFile.sceneSettings.BGSkyVisibility );
          ImGui::Text( "Terrain Occlusion Rain Enabled: %s", sgbFile.sceneSettings.TerrainOcclusionRainEnabled ? "Yes" : "No" );
          ImGui::Text( "Terrain Occlusion Dust Enabled: %s", sgbFile.sceneSettings.TerrainOcclusionDustEnabled ? "Yes" : "No" );
          ImGui::Text( "Constant Time Mode Enabled: %s", sgbFile.sceneSettings.ConstantTimeModeEnabled ? "Yes" : "No" );
          if( sgbFile.sceneSettings.ConstantTimeModeEnabled )
          {
            ImGui::Text( "Constant Time: %.3f", sgbFile.sceneSettings.ConstantTime );
          }
        }

        // Timelines
        if( ImGui::CollapsingHeader( "Timelines" ) && !sgbFile.timelines.empty() )
        {
          for( size_t i = 0; i < sgbFile.timelines.size(); ++i )
          {
            const auto& timeline = sgbFile.timelines[i];
            const auto& timelineName = i < sgbFile.timelineNames.size() ? sgbFile.timelineNames[i] : "Unknown";

            if( ImGui::TreeNode( ( "Timeline " + std::to_string( i ) + ": " + timelineName ).c_str() ) )
            {
              ImGui::Text( "Member ID: %u", timeline.MemberID );
              ImGui::Text( "Timeline ID: %u", timeline.TimelineID );
              ImGui::Text( "Auto Play: %s", timeline.AutoPlay ? "Yes" : "No" );
              ImGui::Text( "Loop Playback: %s", timeline.LoopPlayback ? "Yes" : "No" );
              ImGui::Text( "Binder Count: %d", timeline.Binder_Count );
              ImGui::Text( "Binary Count: %d", timeline.Binary_Count );

              // Collision State
              const char* collisionStateStr = "Unknown";
              switch( timeline.CollisionState )
              {
                case eTimelineCollisionState::NoChange: collisionStateStr = "No Change"; break;
                case eTimelineCollisionState::On: collisionStateStr = "On"; break;
                case eTimelineCollisionState::Off: collisionStateStr = "Off"; break;
              }
              ImGui::Text( "Collision State: %s", collisionStateStr );

              ImGui::TreePop();
            }
          }
        }

        // Layers
        if( ImGui::CollapsingHeader( "Layers" ) && !sgbFile.layers.empty() )
        {
          for( size_t i = 0; i < sgbFile.layers.size(); ++i )
          {
            const auto& layer = sgbFile.layers[i];

            if( ImGui::TreeNode( ( "Layer " + std::to_string( i ) + " (ID: " + std::to_string( layer.LayerID ) + ")" ).c_str() ) )
            {
              ImGui::Text( "Layer ID: %u", layer.LayerID );
              ImGui::Text( "Instance Object Count: %d", layer.InstanceObject_Count );
              ImGui::Text( "Festival ID: %u", layer.FestivalID );
              ImGui::Text( "Festival Phase ID: %u", layer.FestivalPhaseID );
              ImGui::Text( "Version Mask: 0x%04X", layer.VersionMask );

              // Show instance objects in this layer
              auto it = sgbFile.layerInstanceObjects.find( layer.LayerID );
              if( it != sgbFile.layerInstanceObjects.end() && !it->second.empty() )
              {
                ImGui::Text( "Instance Objects (%zu):", it->second.size() );

                // Create table for instance objects
                if( ImGui::BeginTable( ( "InstanceObjectsTable_" + std::to_string( layer.LayerID ) ).c_str(), 7,
                                     ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY,
                                     ImVec2( 0, 300 ) ) )
                {
                  // Table headers
                  ImGui::TableSetupColumn( "ID", ImGuiTableColumnFlags_WidthFixed, 60.0f );
                  ImGui::TableSetupColumn( "Type", ImGuiTableColumnFlags_WidthFixed, 100.0f );
                  ImGui::TableSetupColumn( "Position", ImGuiTableColumnFlags_WidthFixed, 150.0f );
                  ImGui::TableSetupColumn( "Rotation", ImGuiTableColumnFlags_WidthFixed, 150.0f );
                  ImGui::TableSetupColumn( "Scale", ImGuiTableColumnFlags_WidthFixed, 150.0f );
                  ImGui::TableSetupColumn( "Asset Path", ImGuiTableColumnFlags_WidthStretch );
                  ImGui::TableSetupColumn( "View", ImGuiTableColumnFlags_WidthFixed, 60.0f );
                  ImGui::TableSetupScrollFreeze( 0, 1 ); // Freeze header row
                  ImGui::TableHeadersRow();

                  // Table rows
                  for( size_t objIdx = 0; objIdx < it->second.size(); ++objIdx )
                  {
                    const auto& obj = it->second[objIdx];

                    ImGui::TableNextRow();

                    // Instance ID
                    ImGui::TableSetColumnIndex( 0 );
                    ImGui::Text( "%u", obj->header.InstanceID );

                    // Object type
                    ImGui::TableSetColumnIndex( 1 );
                    std::string type = getEntryTypeString( static_cast< eAssetType >( obj->header.AssetType ) );

                    ImGui::Text( "%s", type.c_str() );

                    // Position
                    ImGui::TableSetColumnIndex( 2 );
                    ImGui::Text( "%.2f, %.2f, %.2f",
                                 obj->header.Transformation.Translation.x,
                                 obj->header.Transformation.Translation.y,
                                 obj->header.Transformation.Translation.z );

                    // Rotation
                    ImGui::TableSetColumnIndex( 3 );
                    ImGui::Text( "%.2f, %.2f, %.2f",
                                 obj->header.Transformation.Rotation.x,
                                 obj->header.Transformation.Rotation.y,
                                 obj->header.Transformation.Rotation.z );

                    // Scale
                    ImGui::TableSetColumnIndex( 4 );
                    ImGui::Text( "%.2f, %.2f, %.2f",
                                 obj->header.Transformation.Scale.x,
                                 obj->header.Transformation.Scale.y,
                                 obj->header.Transformation.Scale.z );

                    // Asset Path (only for BG and SharedGroup types)
                    ImGui::TableSetColumnIndex( 5 );
                    auto entryCopy = *obj;
                    if( obj->header.AssetType == eAssetType::BG )
                    {
                      // Cast to BGEntry and get asset path
                      auto bgEntry = std::dynamic_pointer_cast< BGEntry >( obj );
                      if( bgEntry )
                      {
                        ImGui::Text( "%s", bgEntry->collisionFileName.c_str() );
                      }
                      else
                      {
                        ImGui::Text( "N/A" );
                      }
                    }
                    else if( obj->header.AssetType == eAssetType::SharedGroup )
                    {
                      // Cast to SharedGroupEntry and get asset path
                      auto sgEntry = std::dynamic_pointer_cast< SharedGroupEntry >( obj );
                      if( sgEntry )
                      {
                        ImGui::Text( "%s", sgEntry->AssetPath.c_str() );
                      }
                      else
                      {
                        ImGui::Text( "N/A" );
                      }
                    }
                    else
                    {
                      ImGui::Text( "-" );
                    }
                    // View button
                    ImGui::TableSetColumnIndex( 6 );
                    std::string viewButtonId = "View##SGB_" + std::to_string( layer.LayerID ) + "_" + std::to_string( obj->header.InstanceID );
                    if( ImGui::SmallButton( viewButtonId.c_str() ) )
                    {
                      openEntryViewWidget( obj );
                    }

                  }

                  ImGui::EndTable();
                }
              }

              ImGui::TreePop();
            }
          }
        }

      }
      catch( const std::exception& e )
      {
        ImGui::TextColored( ImVec4( 1.0f, 0.3f, 0.3f, 1.0f ), "Error parsing SGB file: %s", e.what() );
      }
    }
    // Original SGData fields (keeping for compatibility)
    ImGui::Spacing();
    ImGui::Text( "Original SGData Fields:" );
    ImGui::Separator();

    ImGui::Text( "Asset Path Offset: %d", entry->header.AssetPath );
    ImGui::Text( "Initial Door State: %d", ( int ) entry->header.InitialDoorState );
    ImGui::Text( "Overridden Members: %d", entry->header.OverriddenMembers );
    ImGui::Text( "Overridden Member Count: %d", entry->header.OverriddenMember_Count );
    ImGui::Text( "Initial Rotation State: %d", ( int ) entry->header.InitialRotationState );
    ImGui::Text( "Initial Transform State: %d", ( int ) entry->header.InitialTransformState );
    ImGui::Text( "Initial Color State: %d", ( int ) entry->header.InitialColorState );
    ImGui::Text( "Random Timeline Auto Play: %s", entry->header.RandomTimelineAutoPlay ? "Yes" : "No" );
    ImGui::Text( "Random Timeline Loop Playback: %s", entry->header.RandomTimelineLoopPlayback ? "Yes" : "No" );
    ImGui::Text( "Collision Controllable Without EObj: %s", entry->header.IsCollisionControllableWithoutEObj ? "Yes" : "No" );
    ImGui::Text( "Bound Client Path Instance ID: %u", entry->header.BoundClientPathInstanceID );
    ImGui::Text( "Move Path Settings: %d", entry->header.MovePathSettings );
    ImGui::Text( "Not Create Navimesh Door: %s", entry->header.NotCreateNavimeshDoor ? "Yes" : "No" );
  }
}

void LgbViewer::showEObjEntryView( EventObjectEntry* entry )
{
  ImGui::Text( "Event Object Entry" );
  ImGui::Separator();

  // Basic information
  if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Instance ID: %u", entry->header.InstanceID );
    ImGui::Text( "Name: %s", entry->name.c_str() );
    ImGui::Text( "Type: %s", getEntryTypeString( entry->getType() ).c_str() );
  }

  // Transform information
  if( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Position: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Translation.x,
                 entry->header.Transformation.Translation.y,
                 entry->header.Transformation.Translation.z );
    ImGui::Text( "Rotation: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Rotation.x,
                 entry->header.Transformation.Rotation.y,
                 entry->header.Transformation.Rotation.z );
    ImGui::Text( "Scale: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Scale.x,
                 entry->header.Transformation.Scale.y,
                 entry->header.Transformation.Scale.z );
  }

  // EObj-specific data
  if( ImGui::CollapsingHeader( "Event Object Data", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Base ID: %u", entry->header.BaseId );
    ImGui::Text( "Bound Instance ID: %u", entry->header.BoundInstanceID );
    ImGui::Text( "Linked Instance ID: %u", entry->header.LinkedInstanceID );
    ImGui::Text( "Reserved 1: %u", entry->header.Reserved1 );
    ImGui::Text( "Reserved 2: %u", entry->header.Reserved2 );
  }
}

void LgbViewer::showExitRangeEntryView( ExitRangeEntry *entry )
{
  ImGui::Text( "Exit Range Entry" );
  ImGui::Separator();

  // Basic information
  if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Instance ID: %u", entry->header.InstanceID );
    ImGui::Text( "Name: %s", entry->name.c_str() );
    ImGui::Text( "Type: %s", getEntryTypeString( entry->getType() ).c_str() );
  }

  // Transform information
  if( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Position: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Translation.x,
                 entry->header.Transformation.Translation.y,
                 entry->header.Transformation.Translation.z );
    ImGui::Text( "Rotation: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Rotation.x,
                 entry->header.Transformation.Rotation.y,
                 entry->header.Transformation.Rotation.z );
    ImGui::Text( "Scale: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Scale.x,
                 entry->header.Transformation.Scale.y,
                 entry->header.Transformation.Scale.z );
  }

  // Trigger Box information
  if( ImGui::CollapsingHeader( "Trigger Box", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    const char *shapeNames[ ] = { "Unknown", "Box", "Sphere", "Cylinder", "Board", "Mesh", "BoardBothSides" };
    int shapeIndex = ( int ) entry->header.triggerBoxType.triggerBoxShape;
    const char *shapeName = ( shapeIndex >= 0 && shapeIndex < 7 ) ? shapeNames[ shapeIndex ] : "Unknown";

    ImGui::Text( "Shape: %s (%d)", shapeName, shapeIndex );
    ImGui::Text( "Priority: %d", entry->header.triggerBoxType.priority );
    ImGui::Text( "Enabled: %s", entry->header.triggerBoxType.enabled ? "Yes" : "No" );
  }

  // Exit-specific data
  if( ImGui::CollapsingHeader( "Exit Data", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Exit Type: %u", entry->header.exitType );
    ImGui::Text( "Zone ID: %u", entry->header.zoneId );
    ImGui::Text( "Dest Territory Type: %u", entry->header.destTerritoryType );
    ImGui::Text( "Index: %d", entry->header.index );
    ImGui::Text( "Dest Instance Object ID: %u", entry->header.destInstanceObjectId );
    ImGui::Text( "Return Instance Object ID: %u", entry->header.returnInstanceObjectId );
    ImGui::Text( "Direction: %.3f", entry->header.direction );
  }
}

void LgbViewer::showPopRangeEntryView( PopRangeEntry* entry )
{
  ImGui::Text( "Pop Range Entry" );
  ImGui::Separator();

  // Basic information
  if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Instance ID: %u", entry->header.InstanceID );
    ImGui::Text( "Type: %s", getEntryTypeString( entry->getType() ).c_str() );
  }

  // Transform information
  if( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Position: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Translation.x,
                 entry->header.Transformation.Translation.y,
                 entry->header.Transformation.Translation.z );
    ImGui::Text( "Rotation: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Rotation.x,
                 entry->header.Transformation.Rotation.y,
                 entry->header.Transformation.Rotation.z );
    ImGui::Text( "Scale: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Scale.x,
                 entry->header.Transformation.Scale.y,
                 entry->header.Transformation.Scale.z );
  }

  // Pop Range specific data
  if( ImGui::CollapsingHeader( "Pop Range Data", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    const char *popTypeNames[ ] = { "Unknown", "PC", "NPC/BNPC", "Content" };
    int popTypeIndex = ( int ) entry->header.popType;
    const char *popTypeName = ( popTypeIndex >= 0 && popTypeIndex < 4 ) ? popTypeNames[ popTypeIndex ] : "Unknown";

    ImGui::Text( "Pop Type: %s (%u)", popTypeName, ( uint32_t ) entry->header.popType );
    ImGui::Text( "Inner Radius Ratio: %.3f", entry->header.innerRadiusRatio );
    ImGui::Text( "Index: %u", entry->header.index );

    ImGui::Text( "Relative Positions:" );
    ImGui::Indent();
    ImGui::Text( "Position: %d", entry->header.relativePositions.Pos );
    ImGui::Text( "Count: %d", entry->header.relativePositions.PosCount );
    ImGui::Unindent();
  }
}

void LgbViewer::showCollisionBoxEntryView( CollisionBoxEntry* entry )
{
  ImGui::Text( "Collision Box Entry" );
  ImGui::Separator();

  // Basic information
  if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    std::cout << "Instance ID: " << entry->header.InstanceID << std::endl;

    ImGui::Text( "Instance ID: %u", entry->header.InstanceID );
    ImGui::Text( "Name: %s", entry->name.c_str() );
    ImGui::Text( "Type: %s", getEntryTypeString( entry->getType() ).c_str() );
  }

  // Transform information
  if( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Position: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Translation.x,
                 entry->header.Transformation.Translation.y,
                 entry->header.Transformation.Translation.z );
    ImGui::Text( "Rotation: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Rotation.x,
                 entry->header.Transformation.Rotation.y,
                 entry->header.Transformation.Rotation.z );
    ImGui::Text( "Scale: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Scale.x,
                 entry->header.Transformation.Scale.y,
                 entry->header.Transformation.Scale.z );
  }

  // Collision Box specific data
  if( ImGui::CollapsingHeader( "Collision Box Data", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    // Trigger Box Shape
    const char* shapeStr = "Unknown";
    switch( entry->header.triggerBoxShape )
    {
      case TriggerBoxShapeBox: shapeStr = "Box"; break;
      case TriggerBoxShapeSphere: shapeStr = "Sphere"; break;
      case TriggerBoxShapeCylinder: shapeStr = "Cylinder"; break;
      case TriggerBoxShapeBoard: shapeStr = "Board"; break;
      case TriggerBoxShapeMesh: shapeStr = "Mesh"; break;
      case TriggerBoxShapeBoardBothSides: shapeStr = "Board Both Sides"; break;
      default: shapeStr = "Unknown"; break;
    }
    ImGui::Text( "Trigger Box Shape: %s (%d)", shapeStr, static_cast< int32_t >( entry->header.triggerBoxShape ) );

    ImGui::Text( "Priority: %d", entry->header.priority );
    ImGui::Text( "Enabled: %s", entry->header.enabled ? "Yes" : "No" );

    ImGui::Separator();

    // Collision attributes
    ImGui::Text( "Attribute: 0x%08X", entry->header.m_attribute );
    ImGui::Text( "Attribute Mask: 0x%08X", entry->header.m_attributeMask );
    ImGui::Text( "Resource ID: %u", entry->header.m_resourceId );
    ImGui::Text( "Push Player Out: %s", entry->header.m_pushPlayerOut ? "Yes" : "No" );

    ImGui::Spacing();

    // Display attribute bits in a more readable format
    if( ImGui::CollapsingHeader( "Attribute Bits" ) )
    {
      ImGui::Text( "Attribute (0x%08X):", entry->header.m_attribute );
      for( int i = 0; i < 32; ++i )
      {
        if( entry->header.m_attribute & ( 1u << i ) )
        {
          ImGui::Text( "  Bit %d: Set", i );
        }
      }

      ImGui::Spacing();

      ImGui::Text( "Attribute Mask (0x%08X):", entry->header.m_attributeMask );
      for( int i = 0; i < 32; ++i )
      {
        if( entry->header.m_attributeMask & ( 1u << i ) )
        {
          ImGui::Text( "  Bit %d: Set", i );
        }
      }
    }

    // Additional debug information
    if( ImGui::CollapsingHeader( "Debug Information" ) )
    {
      ImGui::Text( "Padding: 0x%02X", entry->header.padding );
      ImGui::Text( "Reserved: 0x%08X", entry->header.reserved );
    }
  }

}

void LgbViewer::showUnimplementedEntryView( InstanceObjectEntry *entry )
{
  ImGui::Text( "Entry Viewer - Not Implemented" );
  ImGui::Separator();

  // Show warning
  ImGui::PushStyleColor( ImGuiCol_Text, ImVec4( 1.0f, 0.8f, 0.0f, 1.0f ) ); // Yellow warning color
  ImGui::Text( "⚠ Warning: Detailed view for this entry type is not yet implemented" );
  ImGui::PopStyleColor();

  ImGui::Spacing();

  // Basic information that's available for all entries
  if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Instance ID: %u", entry->header.InstanceID );
    ImGui::Text( "Type: %s", getEntryTypeString( entry->getType() ).c_str() );
    ImGui::Text( "Name Offset: %u", entry->header.Name );
  }

  // Transform information
  if( ImGui::CollapsingHeader( "Transform", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    ImGui::Text( "Position: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Translation.x,
                 entry->header.Transformation.Translation.y,
                 entry->header.Transformation.Translation.z );
    ImGui::Text( "Rotation: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Rotation.x,
                 entry->header.Transformation.Rotation.y,
                 entry->header.Transformation.Rotation.z );
    ImGui::Text( "Scale: %.3f, %.3f, %.3f",
                 entry->header.Transformation.Scale.x,
                 entry->header.Transformation.Scale.y,
                 entry->header.Transformation.Scale.z );
  }

  ImGui::Spacing();
  ImGui::Text( "To request implementation for this entry type," );
  ImGui::Text( "please contact the development team with:" );
  ImGui::BulletText( "Entry Type: %s", getEntryTypeString( entry->getType() ).c_str() );
  ImGui::BulletText( "Type ID: %u", static_cast< uint32_t >( entry->getType() ) );
}
