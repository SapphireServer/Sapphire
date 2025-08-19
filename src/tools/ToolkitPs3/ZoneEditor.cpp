#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include "ExdData.h"
#include <datReaderPs3/Exd/Structs.h>

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

#include "ZoneEditor.h"
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

extern Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;


ZoneEditor::ZoneEditor()
{
}

ZoneEditor::~ZoneEditor()
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

void ZoneEditor::init()
{
  initializeCache();
  initializeNavmeshRendering();
}

void ZoneEditor::initializeCache()
{
  auto& exdD = Engine::Service< Data::ExdData >::ref();

  // Get all zone IDs once
  m_zoneIds = exdD.getIdList< Excel::TerritoryType >();

  // Cache all zone data
  m_cachedZones.clear();
  m_cachedZones.reserve( m_zoneIds.size() );

  for( const auto& id : m_zoneIds )
  {
    auto zoneRow = exdD.getRow< Excel::Ps3::TerritoryType >( id );
    if( !zoneRow ) continue;

    auto cachedZone = std::make_unique< CachedZoneInfo >();
    cachedZone->id = id;
    cachedZone->data = zoneRow->data();
    cachedZone->name = zoneRow->getString( cachedZone->data.Name );
    cachedZone->lvb = zoneRow->getString( cachedZone->data.LVB );

    auto placeNameRow = exdD.getRow< Excel::Ps3::PlaceName >( cachedZone->data.Area );
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

void ZoneEditor::updateSearchFilter()
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

void ZoneEditor::updateBnpcSearchFilter()
{
  std::string searchTerm = std::string( m_bnpcSearchBuffer );
  std::transform( searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower );

  // Only update if search term changed
  if( searchTerm == m_lastBnpcSearchTerm )
    return;
  m_lastBnpcSearchTerm = searchTerm;

  m_filteredBnpcs.clear();

  for( auto& bnpc : m_bnpcs )
  {
    if( searchTerm.empty() )
    {
      m_filteredBnpcs.push_back( bnpc.get() );
    }
    else
    {
      // Search in name and other relevant fields
      std::string bnpcName = bnpc->bnpcName;
      std::transform( bnpcName.begin(), bnpcName.end(), bnpcName.begin(), ::tolower );

      std::string instanceIdStr = std::to_string( bnpc->instanceId );
      std::string baseIdStr = std::to_string( bnpc->BaseId );

      if( bnpcName.find( searchTerm ) != std::string::npos ||
          instanceIdStr.find( searchTerm ) != std::string::npos ||
          baseIdStr.find( searchTerm ) != std::string::npos )
      {
        m_filteredBnpcs.push_back( bnpc.get() );
      }
    }
  }
}

void ZoneEditor::showBnpcWindow()
{
  if( !m_showBnpcWindow ) return;

  ImGui::Begin( "BNPC Information", &m_showBnpcWindow, ImGuiWindowFlags_MenuBar );

  // Menu bar
  if( ImGui::BeginMenuBar() )
  {
    ImGui::Text( "Total BNPCs: %zu | Filtered: %zu", m_bnpcs.size(), m_filteredBnpcs.size() );
    if( ImGui::Button( "Refresh" ) )
    {
      loadBnpcs();
      updateBnpcSearchFilter();
    }
    ImGui::EndMenuBar();
  }

  // Search input
  ImGui::Text( "Search BNPCs:" );
  ImGui::SetNextItemWidth( -1 );
  if( ImGui::InputText( "##BnpcSearch", m_bnpcSearchBuffer, sizeof( m_bnpcSearchBuffer ) ) )
  {
    updateBnpcSearchFilter();
    m_selectedBnpcIndex = -1; // Clear selection when searching
  }

  ImGui::Separator();

  // Split into two panes: list on left, details on right
  if( ImGui::BeginChild( "BnpcList", ImVec2( 350, 0 ), true ) )
  {
    // BNPC list
    for( int i = 0; i < static_cast< int >( m_filteredBnpcs.size() ); ++i )
    {
      const auto& bnpc = m_filteredBnpcs[ i ];


      // Create display text
      std::string displayText = fmt::format( "{} - {} (BaseID: {})",
                                             bnpc->instanceId, bnpc->nameString, bnpc->BaseId );

      bool isSelected = ( m_selectedBnpcIndex == i );
      if( ImGui::Selectable( displayText.c_str(), isSelected ) )
      {
        m_selectedBnpcIndex = i;
      }

      // Tooltip with basic info
      if( ImGui::IsItemHovered() )
      {
        ImGui::BeginTooltip();
        ImGui::Text( "Instance ID: %u", bnpc->instanceId );
        ImGui::Text( "Name: %s", bnpc->bnpcName.c_str() );
        ImGui::Text( "Base ID: %u", bnpc->BaseId );
        ImGui::Text( "Position: %.2f, %.2f, %.2f", bnpc->x, bnpc->y, bnpc->z );
        ImGui::Text( "Level: %u", bnpc->Level );
        ImGui::EndTooltip();
      }
    }
  }
  ImGui::EndChild();

  ImGui::SameLine();

  // Details pane
  if( ImGui::BeginChild( "BnpcDetails", ImVec2( 0, 0 ), true ) )
  {
    if( m_selectedBnpcIndex >= 0 && m_selectedBnpcIndex < static_cast< int >( m_filteredBnpcs.size() ) )
    {
      const auto& bnpc = m_filteredBnpcs[ m_selectedBnpcIndex ];

      ImGui::Text( "BNPC Details" );
      ImGui::Separator();

      // Basic Information
      if( ImGui::CollapsingHeader( "Basic Information", ImGuiTreeNodeFlags_DefaultOpen ) )
      {
        ImGui::Indent();
        ImGui::Text( "Instance ID: %u", bnpc->instanceId );
        ImGui::Text( "Name: %s", bnpc->bnpcName.c_str() );
        ImGui::Text( "Base ID: %u", bnpc->BaseId );
        ImGui::Text( "Name ID: %u", bnpc->NameId );
        ImGui::Text( "Level: %u", bnpc->Level );
        ImGui::Text( "Territory Type: %u", bnpc->territoryType );
        ImGui::Unindent();
      }

      // Position & Movement
      if( ImGui::CollapsingHeader( "Position & Movement", ImGuiTreeNodeFlags_DefaultOpen ) )
      {
        ImGui::Indent();
        ImGui::Text( "Position: %.2f, %.2f, %.2f", bnpc->x, bnpc->y, bnpc->z );
        ImGui::Text( "Rotation: %.2f", bnpc->rotation );
        ImGui::Text( "Move AI: %u", bnpc->MoveAI );
        ImGui::Text( "Normal AI: %u", bnpc->NormalAI );
        ImGui::Text( "Wandering Range: %u", bnpc->WanderingRange );
        ImGui::Text( "Route: %u", bnpc->Route );
        ImGui::Text( "Server Path ID: %u", bnpc->ServerPathId );
        ImGui::Unindent();
      }

      // Spawn Information
      if( ImGui::CollapsingHeader( "Spawn Information" ) )
      {
        ImGui::Indent();
        ImGui::Text( "Pop Weather: %u", bnpc->PopWeather );
        ImGui::Text( "Pop Time: %u - %u", bnpc->PopTimeStart, bnpc->PopTimeEnd );
        ImGui::Text( "Pop Interval: %u", bnpc->PopInterval );
        ImGui::Text( "Pop Rate: %u", bnpc->PopRate );
        ImGui::Text( "Pop Event: %u", bnpc->PopEvent );
        ImGui::Text( "Active Type: %u", bnpc->ActiveType );
        ImGui::Text( "Repop ID: %u", bnpc->RepopId );
        ImGui::Text( "Horizontal Pop Range: %.2f", bnpc->HorizontalPopRange );
        ImGui::Text( "Vertical Pop Range: %.2f", bnpc->VerticalPopRange );
        ImGui::Unindent();
      }

      // Combat & Interaction
      if( ImGui::CollapsingHeader( "Combat & Interaction" ) )
      {
        ImGui::Indent();
        ImGui::Text( "Sense Range Rate: %.2f", bnpc->SenseRangeRate );
        ImGui::Text( "Drop Item: %u", bnpc->DropItem );
        ImGui::Text( "Event Group: %u", bnpc->EventGroup );
        ImGui::Text( "BNPC Rank ID: %u", bnpc->BNPCRankId );
        ImGui::Text( "Equipment ID: %u", bnpc->EquipmentID );
        ImGui::Text( "Customize ID: %u", bnpc->CustomizeID );
        ImGui::Unindent();
      }

      // Linking & Grouping
      if( ImGui::CollapsingHeader( "Linking & Grouping" ) )
      {
        ImGui::Indent();
        ImGui::Text( "Link Group: %u", bnpc->LinkGroup );
        ImGui::Text( "Link Family: %u", bnpc->LinkFamily );
        ImGui::Text( "Link Range: %u", bnpc->LinkRange );
        ImGui::Text( "Link Count Limit: %u", bnpc->LinkCountLimit );
        ImGui::Text( "Link Parent: %d", bnpc->LinkParent );
        ImGui::Text( "Link Override: %d", bnpc->LinkOverride );
        ImGui::Text( "Link Reply: %d", bnpc->LinkReply );
        ImGui::Unindent();
      }

      // Special Properties
      if( ImGui::CollapsingHeader( "Special Properties" ) )
      {
        ImGui::Indent();
        ImGui::Text( "Territory Range: %u", bnpc->TerritoryRange );
        ImGui::Text( "Bound Instance ID: %u", bnpc->BoundInstanceID );
        ImGui::Text( "Fate Layout Label ID: %u", bnpc->FateLayoutLabelId );
        ImGui::Text( "Nonpop Init Zone: %d", bnpc->NonpopInitZone );
        ImGui::Text( "Invalid Repop: %d", bnpc->InvalidRepop );
        ImGui::Text( "Nonpop: %d", bnpc->Nonpop );
        ImGui::Unindent();
      }

      ImGui::Separator();

      // Action buttons
      if( ImGui::Button( "Show on Map" ) )
      {
        // This would highlight the BNPC on the map if map is open
        if( !m_showMapWindow && m_currentMapId > 0 )
        {
          m_showMapWindow = true;
        }
        // TODO: Add map marker/highlight functionality
      }
      ImGui::SameLine();
      if( ImGui::Button( "Copy Position" ) )
      {
        std::string posStr = fmt::format( "{:.2f}, {:.2f}, {:.2f}", bnpc->x, bnpc->y, bnpc->z );
        ImGui::SetClipboardText( posStr.c_str() );
      }
    }
    else
    {
      ImGui::TextDisabled( "No BNPC selected - Click on a BNPC from the list" );
    }
  }
  ImGui::EndChild();

  ImGui::End();
}

void ZoneEditor::loadBnpcs()
{
  auto& db = g_charaDb;
  auto stmt = db.getPreparedStatement( Sapphire::Db::ZoneDbStatements::ZONE_SEL_BNPCS_BY_TERI );
  stmt->setUInt( 1, m_selectedZoneId );
  auto res = db.query( stmt );

  m_bnpcs.clear();

  while( res->next() )
  {
    auto bnpc = std::make_shared< CachedBnpc >();

    bnpc->territoryType = res->getInt( 1 );
    bnpc->bnpcName = res->getString( 3 );
    bnpc->instanceId = res->getInt( 4 );
    bnpc->x = res->getFloat( 5 );
    bnpc->y = res->getFloat( 6 );
    bnpc->z = res->getFloat( 7 );
    bnpc->BaseId = res->getInt( 8 );
    bnpc->PopWeather = res->getInt( 9 );
    bnpc->PopTimeStart = res->getInt( 10 );
    bnpc->PopTimeEnd = res->getInt( 11 );
    bnpc->MoveAI = res->getInt( 12 );
    bnpc->WanderingRange = res->getInt( 13 );
    bnpc->Route = res->getInt( 14 );
    bnpc->EventGroup = res->getInt( 15 );
    bnpc->NameId = res->getInt( 16 );
    bnpc->DropItem = res->getInt( 17 );
    bnpc->SenseRangeRate = res->getFloat( 18 );
    bnpc->Level = res->getInt( 19 );
    bnpc->ActiveType = res->getInt( 20 );
    bnpc->PopInterval = res->getInt( 21 );
    bnpc->PopRate = res->getInt( 22 );
    bnpc->PopEvent = res->getInt( 23 );
    bnpc->LinkGroup = res->getInt( 24 );
    bnpc->LinkFamily = res->getInt( 25 );
    bnpc->LinkRange = res->getInt( 26 );
    bnpc->LinkCountLimit = res->getInt( 27 );
    bnpc->NonpopInitZone = res->getInt( 28 );
    bnpc->InvalidRepop = res->getInt( 29 );
    bnpc->LinkParent = res->getInt( 30 );
    bnpc->LinkOverride = res->getInt( 31 );
    bnpc->LinkReply = res->getInt( 32 );
    bnpc->HorizontalPopRange = res->getFloat( 33 );
    bnpc->VerticalPopRange = res->getFloat( 34 );
    bnpc->BNpcBaseData = res->getInt( 35 );
    bnpc->RepopId = res->getInt( 36 );
    bnpc->BNPCRankId = res->getInt( 37 );
    bnpc->TerritoryRange = res->getInt( 38 );
    bnpc->BoundInstanceID = res->getInt( 39 );
    bnpc->FateLayoutLabelId = res->getInt( 40 );
    bnpc->NormalAI = res->getInt( 41 );
    bnpc->ServerPathId = res->getInt( 42 );
    bnpc->EquipmentID = res->getInt( 43 );
    bnpc->CustomizeID = res->getInt( 44 );
    bnpc->rotation = res->getFloat( 45 );
    bnpc->Nonpop = res->getInt( 46 );

    //int groupId = res->getInt( 47 );

    bnpc->nameString = bnpc->bnpcName;
    auto& exdD = Engine::Service< Data::ExdData >::ref();

    std::string bnpcName = bnpc->bnpcName;
    auto bnpcNameEntry = exdD.getRow< Excel::Ps3::BNpcName >( bnpc->NameId );
    if( bnpcNameEntry )
    {
      bnpc->nameString = bnpcNameEntry->getString( bnpcNameEntry->data().Text.SGL );
    }

    m_bnpcs.push_back( bnpc );
  }
}

// Add a separate method to clean up just the geometry, not the whole rendering system
void ZoneEditor::cleanupNavmeshGeometry()
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

void ZoneEditor::cleanupNavmeshRendering()
{
  // Clean up geometry
  cleanupNavmeshGeometry();
  cleanupBnpcMarkerRendering();

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


void ZoneEditor::onSelectionChanged()
{
  if( m_selectedZone )
  {
    // Load heavy data here
    const auto& data = m_selectedZone->data;

    // Load map texture if available
    if( data.Map > 0 )
    {
      loadMapTexture( data.Map );
    }

    loadBnpcs();
    // Reset BNPC window state when zone changes
    m_selectedBnpcIndex = -1;
    m_filteredBnpcs.clear();
    m_lastBnpcSearchTerm = "N/A";
    memset( m_bnpcSearchBuffer, 0, sizeof( m_bnpcSearchBuffer ) );
    updateBnpcSearchFilter();
    m_lastBnpcSearchTerm = "";

    auto& naviMgr = Engine::Service< Sapphire::Common::Navi::NaviMgr >::ref();
    auto& exdD = Engine::Service< Data::ExdData >::ref();
    auto zoneRow = exdD.getRow< Excel::Ps3::TerritoryType >( m_selectedZone->id );
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
    }
  }
}

// First, let's add a method to check for an .obj file alongside the navmesh
std::string ZoneEditor::getObjFilePath()
{
  if( !m_selectedZone || !m_pNaviProvider )
  {
    return "";
  }

  // The path is based on the current zone and LVB name
  auto& exdD = Engine::Service< Data::ExdData >::ref();
  auto zoneRow = exdD.getRow< Excel::Ps3::TerritoryType >( m_selectedZone->id );
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

void ZoneEditor::checkForObjFile()
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

void ZoneEditor::renderObjModel()
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

bool ZoneEditor::loadObjModel( const std::string& filepath )
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

void ZoneEditor::cleanupObjModel()
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


void ZoneEditor::updateNavmeshCamera()
{
  float radYaw = glm::radians( m_navCameraYaw );
  float radPitch = glm::radians( m_navCameraPitch );

  m_navCameraPos.x = m_navCameraTarget.x + m_navCameraDistance * cos( radPitch ) * cos( radYaw );
  m_navCameraPos.y = m_navCameraTarget.y + m_navCameraDistance * sin( radPitch );
  m_navCameraPos.z = m_navCameraTarget.z + m_navCameraDistance * cos( radPitch ) * sin( radYaw );
}


void ZoneEditor::onSelectionCleared()
{
  clearMapTexture();
  // Clear other loaded data
}

void ZoneEditor::show()
{
  if( m_needsRefresh )
  {
    initializeCache();
  }

  ImGui::Begin( "Zone Editor" );

  showZoneList();
  ImGui::Separator();
  showZoneDetails();

  ImGui::End();

  // Show map window if needed
  if( m_showMapWindow )
  {
    showMapWindow();
  }

  if( m_showBnpcWindow )
  {
    showBnpcWindow();
  }

  if( m_showNavmeshWindow )
  {
    showNavmeshWindow();
  }
}


void ZoneEditor::buildNavmeshGeometry()
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
  buildBnpcMarkerGeometry();
}

// Also add a simplified version for testing
void ZoneEditor::buildSimpleNavmeshTest()
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

void ZoneEditor::initializeNavmeshRendering()
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

  initializeBnpcMarkerRendering();

  // Create framebuffer for rendering to texture
  createNavmeshFramebuffer();

  if( m_navmeshShader && m_navmeshFBO && m_bnpcMarkerShader )
  {
    printf( "Navmesh rendering initialized successfully\n" );
  }
  else
  {
    printf( "Failed to initialize navmesh rendering\n" );
  }
}

void ZoneEditor::renderBnpcMarkers()
{
  if( !m_showBnpcMarkersInNavmesh || !m_bnpcMarkerShader || !m_bnpcMarkerVAO || m_bnpcMarkerInstanceCount == 0 )
  {
    return;
  }

  // Set up matrices (same as navmesh)
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           ( float ) m_navmeshTextureWidth / ( float ) m_navmeshTextureHeight,
                                           0.1f, 10000.0f );

  // Enhanced blending for better visibility
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  // Temporarily disable depth writing but keep depth testing
  // This prevents markers from being occluded too aggressively
  glDepthMask( GL_FALSE );

  // Bias depth slightly to ensure markers appear on top
  glEnable( GL_POLYGON_OFFSET_FILL );
  glPolygonOffset( -1.0f, -1.0f );

  // Use billboard shader
  glUseProgram( m_bnpcMarkerShader );

  // Set uniforms
  GLint viewLoc = glGetUniformLocation( m_bnpcMarkerShader, "view" );
  if( viewLoc != -1 )
  {
    glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
  }

  GLint projectionLoc = glGetUniformLocation( m_bnpcMarkerShader, "projection" );
  if( projectionLoc != -1 )
  {
    glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
  }

  // Render instanced billboards
  glBindVertexArray( m_bnpcMarkerVAO );
  glDrawArraysInstanced( GL_TRIANGLES, 0, 6, m_bnpcMarkerInstanceCount ); // 6 vertices per quad
  glBindVertexArray( 0 );

  // Restore OpenGL state
  glDisable( GL_POLYGON_OFFSET_FILL );
  glDepthMask( GL_TRUE );

  // Unbind shader
  glUseProgram( 0 );
}

void ZoneEditor::initializeBnpcMarkerRendering()
{
  // Enhanced billboard vertex shader with world-space rotation
  const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 worldPos;
layout (location = 1) in vec2 offset;  // -1 to 1 for quad corners
layout (location = 2) in vec3 color;   // Per-instance color
layout (location = 3) in float size;   // Per-instance size
layout (location = 4) in float selected; // 1.0 if selected, 0.0 if not
layout (location = 5) in float rotation; // Y rotation in radians (π = 180°)

uniform mat4 view;
uniform mat4 projection;

out vec3 markerColor;
out vec2 texCoord;
out float markerAlpha;
out float isSelected;
out float distanceFactor;
out vec2 worldRotationDir; // World-space rotation direction

void main() {
    // Extract camera right and up vectors from view matrix
    vec3 cameraRight = vec3(view[0][0], view[1][0], view[2][0]);
    vec3 cameraUp = vec3(view[0][1], view[1][1], view[2][1]);

    // Scale up selected markers significantly
    float finalSize = size * (selected > 0.5 ? 2.0 : 1.0);

    // Create billboard position
    vec3 billboardPos = worldPos +
                       cameraRight * offset.x * finalSize +
                       cameraUp * offset.y * finalSize;

    gl_Position = projection * view * vec4(billboardPos, 1.0);

    // Pass through values
    markerColor = color;
    texCoord = offset; // -1 to 1, will be used to create shapes
    isSelected = selected;

    // Calculate world-space direction from rotation
    // Convert Y rotation to world-space XZ direction
    vec3 worldDirection = vec3(sin(rotation), 0.0, cos(rotation));

    // Project world direction onto camera plane to get screen-space direction
    float dirDotRight = dot(worldDirection, cameraRight);
    float dirDotUp = dot(worldDirection, cameraUp);
    worldRotationDir = normalize(vec2(dirDotRight, dirDotUp));

    // Calculate distance for better alpha management
    vec4 viewPos = view * vec4(worldPos, 1.0);
    float distance = length(viewPos.xyz);
    distanceFactor = distance;

    // More visible alpha calculation - higher minimum alpha
    markerAlpha = clamp(200.0 / distance, 0.7, 1.0);
}
)";

  // Enhanced fragment shader with world-space rotation indicator
  const char *fragmentShaderSource = R"(
#version 330 core
in vec3 markerColor;
in vec2 texCoord;
in float markerAlpha;
in float isSelected;
in float distanceFactor;
in vec2 worldRotationDir; // Screen-space projection of world rotation

out vec4 FragColor;

void main() {
    // Create a diamond shape - discard pixels outside the diamond
    float dist = abs(texCoord.x) + abs(texCoord.y);

    // Hard cutoff for diamond shape
    if (dist > 0.9) {
        discard;
    }

    // Create layers within the diamond
    float innerCore = 1.0 - smoothstep(0.0, 0.4, dist);
    float midRing = smoothstep(0.2, 0.5, dist) - smoothstep(0.5, 0.7, dist);
    float outerRing = smoothstep(0.6, 0.8, dist) - smoothstep(0.8, 0.9, dist);

    // Enhanced colors for better contrast
    vec3 finalColor = markerColor;

    // Use the world-space rotation direction (already projected to screen space)
    vec2 rotDir = normalize(worldRotationDir);

    // Check if current pixel is part of the rotation indicator
    vec2 pixelPos = texCoord;

    // Create an arrow pointing in the world-space rotation direction
    // Arrow line (from center towards the rotation direction)
    float lineDistance = abs(dot(pixelPos, vec2(-rotDir.y, rotDir.x))); // Perpendicular distance to line
    float alongLine = dot(pixelPos, rotDir); // Distance along the line

    // Arrow shaft: thin line from center to near the edge
    bool isArrowLine = (lineDistance < 0.06) && (alongLine > 0.0) && (alongLine < 0.65) && (dist > 0.15);

    // Arrow head: create a more visible triangle at the tip
    vec2 arrowTip = rotDir * 0.7;
    vec2 arrowBase1 = rotDir * 0.5 + vec2(-rotDir.y, rotDir.x) * 0.2;
    vec2 arrowBase2 = rotDir * 0.5 + vec2(rotDir.y, -rotDir.x) * 0.2;

    // Check if pixel is inside the arrow head triangle using barycentric coordinates
    vec2 v0 = arrowTip - pixelPos;
    vec2 v1 = arrowBase1 - pixelPos;
    vec2 v2 = arrowBase2 - pixelPos;

    float d1 = v0.x * v1.y - v0.y * v1.x;
    float d2 = v1.x * v2.y - v1.y * v2.x;
    float d3 = v2.x * v0.y - v2.y * v0.x;

    bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    bool isArrowHead = !(hasNeg && hasPos);

    // Combine rotation indicator elements
    bool isRotationIndicator = isArrowLine || isArrowHead;

    if (isSelected > 0.5) {
        // Selected markers: bright white core with colored ring
        finalColor = mix(markerColor, vec3(1.0, 1.0, 1.0), innerCore * 0.8);

        // Add pulsing effect for selected markers
        float time = gl_FragCoord.x * 0.02 + gl_FragCoord.y * 0.02;
        float pulse = sin(time) * 0.15 + 1.0;
        finalColor *= pulse;

        // Boost brightness
        finalColor *= 1.5;

        // Make rotation indicator very bright for selected
        if (isRotationIndicator) {
            finalColor = vec3(1.0, 1.0, 1.0); // Pure white arrow
        }
    } else {
        // Normal markers: brighter colors with white highlights in center
        finalColor = mix(markerColor, vec3(1.0, 1.0, 1.0), innerCore * 0.4);
        finalColor *= 1.3; // Make brighter

        // Make rotation indicator contrasting color
        if (isRotationIndicator) {
            finalColor = vec3(0.0, 0.0, 0.0); // Black arrow for contrast
        }
    }

    // Add black border only at the very edge of the diamond (but not over rotation indicator)
    if (outerRing > 0.5 && !isRotationIndicator) {
        finalColor = vec3(0.0, 0.0, 0.0); // Black border
    }

    // Calculate alpha based on distance from center (for anti-aliasing)
    float edgeAlpha = 1.0 - smoothstep(0.7, 0.9, dist);
    float finalAlpha = edgeAlpha * markerAlpha;

    // Boost alpha for rotation indicator
    if (isRotationIndicator) {
        finalAlpha = max(finalAlpha, 0.9);
    }

    // Boost alpha for very distant markers
    if (distanceFactor > 150.0) {
        finalAlpha = max(finalAlpha, 0.8);
    }

    // Minimum visibility threshold
    finalAlpha = max(finalAlpha, 0.6);

    // Final check - if alpha is too low, discard
    if (finalAlpha < 0.1) {
        discard;
    }

    FragColor = vec4(finalColor, finalAlpha);
}
)";

  m_bnpcMarkerShader = createShaderProgram( vertexShaderSource, fragmentShaderSource );

  if( m_bnpcMarkerShader )
  {
    printf( "Enhanced BNPC billboard shader with world-space rotation created successfully (ID: %u)\n",
            m_bnpcMarkerShader );
  }
  else
  {
    printf( "Failed to create enhanced BNPC billboard shader\n" );
  }
}


void ZoneEditor::buildBnpcMarkerGeometry()
{
  if( !m_selectedZone || m_bnpcs.empty() )
  {
    return;
  }

  // Clean up existing marker buffers
  if( m_bnpcMarkerVAO )
  {
    glDeleteVertexArrays( 1, &m_bnpcMarkerVAO );
  }
  if( m_bnpcMarkerVBO )
  {
    glDeleteBuffers( 1, &m_bnpcMarkerVBO );
  }
  if( m_bnpcMarkerInstanceVBO )
  {
    glDeleteBuffers( 1, &m_bnpcMarkerInstanceVBO );
  }

  // Create quad template (will be instanced for each BNPC)
  std::vector< float > quadVertices = {
    // positions (offset from center)
    -1.0f, -1.0f, // bottom-left
    1.0f, -1.0f, // bottom-right
    1.0f, 1.0f, // top-right
    -1.0f, -1.0f, // bottom-left
    1.0f, 1.0f, // top-right
    -1.0f, 1.0f // top-left
  };

  // Create instance data for each BNPC (now includes rotation)
  struct BnpcInstance
  {
    glm::vec3 worldPos;
    glm::vec3 color;
    float size;
    float selected;
    float rotation; // New: Y rotation in radians
  };

  std::vector< BnpcInstance > instanceData;
  m_bnpcWorldPositions.clear(); // Clear the cache
  instanceData.reserve( m_bnpcs.size() );

  // Create a set of filtered BNPC IDs for quick lookup
  std::unordered_set< uint32_t > filteredBnpcIds;
  for( auto *bnpc : m_filteredBnpcs )
  {
    filteredBnpcIds.insert( bnpc->instanceId );
  }

  // Get selected BNPC for highlighting
  CachedBnpc *selectedBnpc = nullptr;
  if( m_selectedBnpcIndex >= 0 && m_selectedBnpcIndex < m_filteredBnpcs.size() )
  {
    selectedBnpc = m_filteredBnpcs[ m_selectedBnpcIndex ];
  }

  for( const auto& bnpc : m_bnpcs )
  {
    if( bnpc->territoryType != m_selectedZone->id )
      continue;

    BnpcInstance instance;
    instance.worldPos = glm::vec3( bnpc->x, bnpc->y + 3.0f, bnpc->z ); // Higher above ground for visibility

    // Store world position for mouse picking
    m_bnpcWorldPositions.push_back( { instance.worldPos, bnpc.get() } );

    // Determine if this BNPC is filtered (visible in search results)
    bool isFiltered = filteredBnpcIds.find( bnpc->instanceId ) != filteredBnpcIds.end();

    // Enhanced colors with better contrast
    if( !isFiltered )
    {
      // Darker grey for unfiltered BNPCs but still visible
      instance.color = glm::vec3( 0.6f, 0.6f, 0.6f );
    }
    else
    {
      // Brighter, more saturated colors for filtered BNPCs
      if( bnpc->Level > 50 )
      {
        instance.color = glm::vec3( 1.0f, 0.0f, 0.0f ); // Pure red for high level
      }
      else if( bnpc->Level > 30 )
      {
        instance.color = glm::vec3( 1.0f, 0.8f, 0.0f ); // Bright orange for mid level
      }
      else
      {
        instance.color = glm::vec3( 0.0f, 1.0f, 0.0f ); // Pure green for low level
      }
    }

    // Check if this BNPC is selected
    instance.selected = ( selectedBnpc && selectedBnpc->instanceId == bnpc->instanceId ) ? 1.0f : 0.0f;

    // Set rotation - the value is already in radians where π = 180°
    instance.rotation = bnpc->rotation;

    // Larger base sizes for better visibility
    float baseSize = 2.5f + ( bnpc->Level * 0.03f );
    if( !isFiltered )
    {
      baseSize *= 0.8f; // Slightly smaller for unfiltered but still visible
    }
    instance.size = baseSize;

    instanceData.push_back( instance );
  }

  if( instanceData.empty() )
  {
    printf( "No BNPCs found for zone %u\n", m_selectedZone->id );
    return;
  }

  // Create VAO and VBOs
  glGenVertexArrays( 1, &m_bnpcMarkerVAO );
  glGenBuffers( 1, &m_bnpcMarkerVBO );
  glGenBuffers( 1, &m_bnpcMarkerInstanceVBO );

  glBindVertexArray( m_bnpcMarkerVAO );

  // Upload quad vertex data (static)
  glBindBuffer( GL_ARRAY_BUFFER, m_bnpcMarkerVBO );
  glBufferData( GL_ARRAY_BUFFER, quadVertices.size() * sizeof( float ), quadVertices.data(), GL_STATIC_DRAW );

  // Set vertex attributes for quad offsets
  glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), ( void * ) 0 );
  glEnableVertexAttribArray( 1 );

  // Upload instance data (per-BNPC data)
  glBindBuffer( GL_ARRAY_BUFFER, m_bnpcMarkerInstanceVBO );
  glBufferData( GL_ARRAY_BUFFER, instanceData.size() * sizeof( BnpcInstance ), instanceData.data(), GL_DYNAMIC_DRAW );

  // Set instance attributes
  // World position (vec3)
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( BnpcInstance ),
                         ( void * ) offsetof( BnpcInstance, worldPos ) );
  glEnableVertexAttribArray( 0 );
  glVertexAttribDivisor( 0, 1 ); // One per instance

  // Color (vec3)
  glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( BnpcInstance ), ( void * ) offsetof( BnpcInstance, color ) );
  glEnableVertexAttribArray( 2 );
  glVertexAttribDivisor( 2, 1 ); // One per instance

  // Size (float)
  glVertexAttribPointer( 3, 1, GL_FLOAT, GL_FALSE, sizeof( BnpcInstance ), ( void * ) offsetof( BnpcInstance, size ) );
  glEnableVertexAttribArray( 3 );
  glVertexAttribDivisor( 3, 1 ); // One per instance

  // Selected (float)
  glVertexAttribPointer( 4, 1, GL_FLOAT, GL_FALSE, sizeof( BnpcInstance ),
                         ( void * ) offsetof( BnpcInstance, selected ) );
  glEnableVertexAttribArray( 4 );
  glVertexAttribDivisor( 4, 1 ); // One per instance

  // Rotation (float) - NEW
  glVertexAttribPointer( 5, 1, GL_FLOAT, GL_FALSE, sizeof( BnpcInstance ),
                         ( void * ) offsetof( BnpcInstance, rotation ) );
  glEnableVertexAttribArray( 5 );
  glVertexAttribDivisor( 5, 1 ); // One per instance

  glBindVertexArray( 0 );

  m_bnpcMarkerInstanceCount = instanceData.size();

  printf( "Created %d enhanced BNPC billboard markers with rotation indicators for zone %u\n",
          m_bnpcMarkerInstanceCount, m_selectedZone->id );
}

// Helper function to project 3D world position to 2D screen coordinates
glm::vec2 ZoneEditor::worldTo3DScreen( const glm::vec3& worldPos, const ImVec2& imageSize )
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

// New function to handle 3D BNPC tooltips and selection
void ZoneEditor::handle3DBnpcInteraction( ImVec2 imagePos, ImVec2 imageSize )
{
  if( !m_selectedZone || m_bnpcWorldPositions.empty() )
    return;

  ImDrawList *drawList = ImGui::GetWindowDrawList();

  // Handle mouse interaction
  if( ImGui::IsWindowHovered() )
  {
    ImVec2 mousePos = ImGui::GetMousePos();
    mousePos.x -= imagePos.x;
    mousePos.y -= imagePos.y;

    // Find the closest BNPC to the mouse cursor
    float closestDistance = FLT_MAX;
    int closestIndex = -1;
    CachedBnpc *hoveredBnpc = nullptr;
    ImVec2 hoveredScreenPos;

    for( size_t i = 0; i < m_bnpcWorldPositions.size(); i++ )
    {
      const auto& entry = m_bnpcWorldPositions[ i ];
      glm::vec2 screenPos = worldTo3DScreen( entry.worldPos, imageSize );

      // Skip if outside visible area
      if( screenPos.x < 0 || screenPos.x > imageSize.x ||
          screenPos.y < 0 || screenPos.y > imageSize.y )
        continue;

      // Calculate distance from mouse to BNPC
      float dx = screenPos.x - mousePos.x;
      float dy = screenPos.y - mousePos.y;
      float distance = sqrtf( dx * dx + dy * dy );

      // Check if this is within hover radius and closest so far
      if( distance < 25.0f && distance < closestDistance )
      {
        closestDistance = distance;
        hoveredBnpc = entry.bnpc;
        hoveredScreenPos = ImVec2( imagePos.x + screenPos.x, imagePos.y + screenPos.y );

        // Find this BNPC in filtered list for potential selection
        for( size_t j = 0; j < m_filteredBnpcs.size(); j++ )
        {
          if( m_filteredBnpcs[ j ]->instanceId == entry.bnpc->instanceId )
          {
            closestIndex = static_cast< int >( j );
            break;
          }
        }
      }
    }

    // Handle mouse click for selection
    if( ImGui::IsMouseClicked( 0 ) && closestIndex >= 0 )
    {
      m_selectedBnpcIndex = closestIndex;
      // Rebuild markers to update selection highlighting
      buildBnpcMarkerGeometry();
    }

    // Show tooltip for hovered BNPC
    if( hoveredBnpc )
    {
      ImGui::SetMouseCursor( ImGuiMouseCursor_Hand );

      // Position tooltip near the BNPC but avoid screen edges
      ImVec2 tooltipPos = hoveredScreenPos;
      tooltipPos.x += 15;
      tooltipPos.y -= 10;

      ImGui::SetNextWindowPos( tooltipPos );
      ImGui::SetNextWindowBgAlpha( 0.9f );

      if( ImGui::Begin( "##BnpcTooltip", nullptr,
                        ImGuiWindowFlags_Tooltip |
                        ImGuiWindowFlags_NoInputs |
                        ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoMove |
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoSavedSettings |
                        ImGuiWindowFlags_AlwaysAutoResize ) )
      {
        if( !hoveredBnpc->nameString.empty() )
          ImGui::Text( "%s", hoveredBnpc->nameString.c_str() );
        ImGui::Separator();
        ImGui::Text( "ID: %u", hoveredBnpc->instanceId );
        ImGui::Text( "Level: %u", hoveredBnpc->Level );
        ImGui::Text( "Position: %.1f, %.1f, %.1f", hoveredBnpc->x, hoveredBnpc->y, hoveredBnpc->z );

        ImGui::End();
      }
    }
  }

  // Draw name for selected BNPC
  if( m_selectedBnpcIndex >= 0 && m_selectedBnpcIndex < m_filteredBnpcs.size() )
  {
    CachedBnpc *selectedBnpc = m_filteredBnpcs[ m_selectedBnpcIndex ];

    // Find the world position of selected BNPC
    for( const auto& entry : m_bnpcWorldPositions )
    {
      if( entry.bnpc->instanceId == selectedBnpc->instanceId )
      {
        glm::vec2 screenPos = worldTo3DScreen( entry.worldPos, imageSize );

        if( screenPos.x >= 0 && screenPos.x <= imageSize.x &&
            screenPos.y >= 0 && screenPos.y <= imageSize.y )
        {
          // Draw name above the selected BNPC
          ImVec2 textPos = ImVec2( imagePos.x + screenPos.x, imagePos.y + screenPos.y - 40 );

          ImVec2 textSize = ImGui::CalcTextSize( selectedBnpc->nameString.empty()
                                                   ? "not set"
                                                   : selectedBnpc->nameString.c_str() );

          // Center the text horizontally
          textPos.x -= textSize.x * 0.5f;

          // Draw background
          drawList->AddRectFilled(
            ImVec2( textPos.x - 4, textPos.y - 2 ),
            ImVec2( textPos.x + textSize.x + 4, textPos.y + textSize.y + 2 ),
            IM_COL32( 0, 0, 0, 200 )
          );

          if( !selectedBnpc->nameString.empty() )
            drawList->AddText( textPos, IM_COL32( 255, 255, 255, 255 ), selectedBnpc->nameString.c_str() );
        }
        break;
      }
    }
  }
}

void ZoneEditor::renderNavmesh()
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

  // Handle 3D BNPC interaction (replaces the old 2D overlay)
  handle3DBnpcInteraction( imageScreenPos, imageSize );

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
  ImGui::Text( "BNPCs: %d 3D markers", m_bnpcMarkerInstanceCount );
  ImGui::Checkbox( "Show BNPC Markers", &m_showBnpcMarkersInNavmesh );
  ImGui::Text( "Camera: dist=%.1f yaw=%.1f pitch=%.1f",
               m_navCameraDistance, m_navCameraYaw, m_navCameraPitch );
  ImGui::Text( "Target: (%.1f, %.1f, %.1f)",
               m_navCameraTarget.x, m_navCameraTarget.y, m_navCameraTarget.z );
  ImGui::Text( "Controls: LMB=rotate, MMB=pan, wheel=zoom, click markers=select" );
}


void ZoneEditor::cleanupBnpcMarkerRendering()
{
  if( m_bnpcMarkerVAO )
  {
    glDeleteVertexArrays( 1, &m_bnpcMarkerVAO );
    m_bnpcMarkerVAO = 0;
  }

  if( m_bnpcMarkerVBO )
  {
    glDeleteBuffers( 1, &m_bnpcMarkerVBO );
    m_bnpcMarkerVBO = 0;
  }

  if( m_bnpcMarkerInstanceVBO )
  {
    glDeleteBuffers( 1, &m_bnpcMarkerInstanceVBO );
    m_bnpcMarkerInstanceVBO = 0;
  }

  if( m_bnpcMarkerShader )
  {
    glDeleteProgram( m_bnpcMarkerShader );
    m_bnpcMarkerShader = 0;
  }

  m_bnpcMarkerInstanceCount = 0;
}

void ZoneEditor::renderNavmeshToTexture()
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

  // Render BNPC markers on top
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  renderBnpcMarkers();

  // Unbind framebuffer (back to default)
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

glm::vec2 ZoneEditor::worldToNavmeshScreen( float worldX, float worldY, float worldZ, ImVec2 imageSize )
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

void ZoneEditor::createNavmeshFramebuffer()
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

void ZoneEditor::showNavmeshWindow()
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

void ZoneEditor::showZoneList()
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
          m_selectedBnpcIndex = -1;
          m_bnpcWorldPositions.clear();
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

void ZoneEditor::showZoneDetails()
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
      //ImGui::Text( "Weather Rate: %u", data.WeatherRate );
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
    if( ImGui::Button( "Show BNPCs" ) )
    {
      if( !m_bnpcs.empty() )
      {
        m_showBnpcWindow = true;
        updateBnpcSearchFilter();
      }
    }
    if( ImGui::Button( "Show Navmesh" ) )
    {
      m_showNavmeshWindow = true;
    }
    ImGui::SameLine();
  }
  ImGui::EndChild();
}

void ZoneEditor::showMapWindow()
{
  if( !m_showMapWindow || m_mapTextureId == 0 )
    return;

  ImGui::Begin( "Map Viewer", &m_showMapWindow, ImGuiWindowFlags_MenuBar );

  // Menu bar with map info and controls
  if( ImGui::BeginMenuBar() )
  {
    ImGui::Text( "Map ID: %u | Size: %dx%d", m_currentMapId, m_mapWidth, m_mapHeight );
    ImGui::Separator();

    ImGui::Checkbox( "Show BNPCs", &m_showBnpcIcons );

    if( m_showBnpcIcons )
    {
      ImGui::SetNextItemWidth( 100 );
      ImGui::SliderFloat( "Icon Size", &m_bnpcIconSize, 4.0f, 20.0f );
    }

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

    // Draw BNPC icons if enabled
    if( m_showBnpcIcons && !m_bnpcs.empty() )
    {
      drawBnpcIcons();
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
  if( m_showBnpcIcons )
  {
    ImGui::Text( "BNPCs: %zu visible", m_bnpcs.size() );
  }

  ImGui::End();
}

std::vector< uint8_t > ZoneEditor::decompressDXT1( const uint8_t *compressedData, int width, int height )
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

ImVec2 ZoneEditor::worldToScreenPos( float worldX, float worldZ, const ImVec2& imagePos, const ImVec2& imageSize )
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

void ZoneEditor::drawBnpcIcons()
{
  if( !m_showMapWindow || m_mapTextureId == 0 || m_bnpcs.empty() )
    return;

  // Get the current image position and size
  ImVec2 imagePos = ImGui::GetItemRectMin();
  ImVec2 imageSize = ImGui::GetItemRectSize();

  // Get draw list for drawing on top of the image
  ImDrawList *drawList = ImGui::GetWindowDrawList();

  // Check if we're currently dragging - if so, don't process button clicks
  bool isDragging = ImGui::IsMouseDragging( ImGuiMouseButton_Left );

  // Draw each BNPC
  for( size_t i = 0; i < m_bnpcs.size(); ++i )
  {
    const auto& bnpc = m_bnpcs[ i ];

    // Convert world position to screen position
    ImVec2 screenPos = worldToScreenPos( bnpc->x, bnpc->z, imagePos, imageSize );

    // Check if the icon is within the visible image area
    if( screenPos.x < imagePos.x || screenPos.x > imagePos.x + imageSize.x ||
        screenPos.y < imagePos.y || screenPos.y > imagePos.y + imageSize.y )
    {
      continue; // Skip if outside visible area
    }

    // Choose color based on selection
    ImU32 iconColor = m_bnpcIconColor;
    if( m_selectedBnpcIndex >= 0 &&
        m_selectedBnpcIndex < static_cast< int >( m_filteredBnpcs.size() ) &&
        m_filteredBnpcs[ m_selectedBnpcIndex ] == bnpc.get() )
    {
      iconColor = m_selectedBnpcIconColor;
    }

    // Draw diamond shape
    float halfSize = m_bnpcIconSize * 0.5f;
    ImVec2 points[ 4 ] = {
      ImVec2( screenPos.x, screenPos.y - halfSize ), // Top
      ImVec2( screenPos.x + halfSize, screenPos.y ), // Right
      ImVec2( screenPos.x, screenPos.y + halfSize ), // Bottom
      ImVec2( screenPos.x - halfSize, screenPos.y ) // Left
    };

    // Draw filled diamond
    drawList->AddConvexPolyFilled( points, 4, iconColor );

    // Draw border
    drawList->AddPolyline( points, 4, IM_COL32( 0, 0, 0, 255 ), true, 1.0f );

    // Only add invisible button for click detection if we're not dragging
    if( !isDragging )
    {
      ImGui::SetCursorScreenPos( ImVec2( screenPos.x - halfSize, screenPos.y - halfSize ) );
      ImGui::InvisibleButton( ( "bnpc_" + std::to_string( i ) ).c_str(), ImVec2( m_bnpcIconSize, m_bnpcIconSize ) );

      // Handle click
      if( ImGui::IsItemClicked() )
      {
        // Find this BNPC in filtered list and select it
        for( int j = 0; j < static_cast< int >( m_filteredBnpcs.size() ); ++j )
        {
          if( m_filteredBnpcs[ j ] == bnpc.get() )
          {
            m_selectedBnpcIndex = j;
            m_showBnpcWindow = true; // Show BNPC window when clicked
            break;
          }
        }
      }

      // Show tooltip on hover
      if( ImGui::IsItemHovered() )
      {
        ImGui::BeginTooltip();
        if( !bnpc->nameString.empty() )
          ImGui::Text( "%s", bnpc->nameString.c_str() );
        ImGui::Text( "BNPC: %s", bnpc->bnpcName.c_str() );
        ImGui::Text( "ID: %u", bnpc->instanceId );
        ImGui::Text( "Level: %u", bnpc->Level );
        ImGui::Text( "Position: %.1f, %.1f, %.1f", bnpc->x, bnpc->y, bnpc->z );
        ImGui::Separator();
        ImGui::EndTooltip();
      }
    }
  }
}

void ZoneEditor::loadMapTexture( uint32_t mapId )
{
  auto& exdD = Engine::Service< Data::ExdData >::ref();
  auto mapEntry = exdD.getRow< Excel::Ps3::Map >( mapId );
  if( !mapEntry )
    return;
  auto mapData = mapEntry->data();

  m_mapScale = mapData.Scale;
  auto mapPath = mapEntry->getString( mapData.Path );
  std::string file = mapPath;
  file.erase( std::remove( file.begin(), file.end(), '/' ), file.end() );
  file += "_m.tex";

  auto& gameData = Engine::Service< xivps3::dat::GameData >::ref();

  return;
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

void ZoneEditor::clearMapTexture()
{
  if( m_mapTextureId != 0 )
  {
    glDeleteTextures( 1, &m_mapTextureId );
    m_mapTextureId = 0;
  }
}

void ZoneEditor::refresh()
{
  m_needsRefresh = true;
  m_zoneIds.clear();
  m_cachedZones.clear();
  m_filteredZones.clear(); // For search results
  initializeCache();
  m_lastSearchTerm = "N/A";
  m_lastBnpcSearchTerm = "N/A";
}

// Convert screen coordinates to world ray
ZoneEditor::Ray ZoneEditor::screenToWorldRay( const ImVec2& screenPos, const ImVec2& imageSize )
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
bool ZoneEditor::rayTriangleIntersect( const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
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
ZoneEditor::RayHit ZoneEditor::castRayToNavmesh( const Ray& ray )
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
ZoneEditor::RayHit ZoneEditor::castRayToObjModel( const Ray& ray )
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
ZoneEditor::RayHit ZoneEditor::castRayToGeometry( const Ray& ray )
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
void ZoneEditor::renderWorldMarker( const glm::vec3& worldPos )
{
  if( !m_showClickMarker ) return;

  // Simple marker implementation - draw a small cross at the clicked position
  // You can expand this to draw a more sophisticated marker

  // For now, we'll just store the position and optionally print it
  // The actual rendering could be added to your existing rendering pipeline
}

// Callback for world clicking - implement your editing logic here
void ZoneEditor::onWorldClick( const RayHit& hit )
{
  // Example: Create a new BNPC at the clicked position
  if( m_worldEditingMode )
  {
    // This is where you'd implement your BNPC creation logic
    printf( "Would create BNPC at position: (%.2f, %.2f, %.2f)\n",
            hit.position.x, hit.position.y, hit.position.z );

    // You can also use the NaviProvider to find the nearest walkable position
    if( m_pNaviProvider )
    {
      auto nearestPos = m_pNaviProvider->findNearestPosition( hit.position.x, hit.position.z );
      printf( "Nearest walkable position: (%.2f, %.2f, %.2f)\n",
              nearestPos.x, nearestPos.y, nearestPos.z );
    }
  }
}
