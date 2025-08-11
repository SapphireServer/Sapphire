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

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/IconsFontAwesome5.h"
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


GLuint compileShader( GLenum type, const char *source )
{
  GLuint shader = glCreateShader( type );
  glShaderSource( shader, 1, &source, nullptr );
  glCompileShader( shader );

  GLint success;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
  if( !success )
  {
    char infoLog[ 512 ];
    glGetShaderInfoLog( shader, 512, nullptr, infoLog );
    printf( "Shader compilation failed: %s\n", infoLog );
    glDeleteShader( shader );
    return 0;
  }
  return shader;
}

GLuint createShaderProgram( const char *vertexSource, const char *fragmentSource )
{
  GLuint vertexShader = compileShader( GL_VERTEX_SHADER, vertexSource );
  GLuint fragmentShader = compileShader( GL_FRAGMENT_SHADER, fragmentSource );

  if( !vertexShader || !fragmentShader )
  {
    if( vertexShader )
      glDeleteShader( vertexShader );
    if( fragmentShader )
      glDeleteShader( fragmentShader );
    return 0;
  }

  GLuint program = glCreateProgram();
  glAttachShader( program, vertexShader );
  glAttachShader( program, fragmentShader );
  glLinkProgram( program );

  GLint success;
  glGetProgramiv( program, GL_LINK_STATUS, &success );
  if( !success )
  {
    char infoLog[ 512 ];
    glGetProgramInfoLog( program, 512, nullptr, infoLog );
    printf( "Shader linking failed: %s\n", infoLog );
    glDeleteProgram( program );
    program = 0;
  }

  glDeleteShader( vertexShader );
  glDeleteShader( fragmentShader );

  return program;
}


extern Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;


ZoneEditor::ZoneEditor()
{
}

ZoneEditor::~ZoneEditor()
{
  clearMapTexture();
  cleanupNavmeshRendering();
  if( m_navmeshShader )
  {
    glDeleteProgram( m_navmeshShader );
    m_navmeshShader = 0;
  }
}

void ZoneEditor::init()
{
  initializeCache();
  initializeNavmeshRendering();
}

void ZoneEditor::initializeCache()
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
    auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();

    std::string bnpcName = bnpc->bnpcName;
    auto bnpcNameEntry = exdD.getRow< Excel::BNpcName >( bnpc->NameId );
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
      }
      else
        m_pNaviProvider = nullptr;
    }
  }
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

  // Process ALL tiles, not just a limited number
  for( int i = 0; i < navMesh->getMaxTiles(); ++i )
  {
    const dtMeshTile *tile = navMesh->getTile( i );
    if( !tile || !tile->header || !tile->dataSize ) continue;

    printf( "Processing tile %d: %d polygons\n", i, tile->header->polyCount );
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

  if( m_bnpcMarkerShader )
  {
    glDeleteProgram( m_bnpcMarkerShader );
    m_bnpcMarkerShader = 0;
  }

  m_bnpcMarkerVertexCount = 0;
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
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;

out vec3 Normal;

void main()
{
    Normal = normal;
    gl_Position = mvp * vec4(position, 1.0);
}
)";

  const char *fragmentShaderSource = R"(
#version 330 core
in vec3 Normal;

out vec4 FragColor;

uniform vec3 color = vec3(0.0, 0.8, 1.0);
uniform bool wireframe = false;

void main()
{
    if (wireframe) {
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        float shade = abs(Normal.y) * 0.5 + 0.5;
        FragColor = vec4(color * shade, 1.0);
    }
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

void ZoneEditor::initializeBnpcMarkerRendering()
{
  // Simple vertex shader for BNPC markers
  const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    gl_PointSize = 8.0;
}
)";

  // Simple fragment shader for BNPC markers
  const char *fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

uniform vec3 markerColor = vec3(1.0, 1.0, 0.0); // Yellow

void main()
{
    // Create a diamond shape within the point
    vec2 coord = gl_PointCoord - vec2(0.5, 0.5);
    float dist = abs(coord.x) + abs(coord.y);

    if (dist > 0.4) {
        discard;
    }

    // Add some anti-aliasing
    float alpha = 1.0 - smoothstep(0.3, 0.4, dist);
    FragColor = vec4(markerColor, alpha);
}
)";

  m_bnpcMarkerShader = createShaderProgram( vertexShaderSource, fragmentShaderSource );

  if( m_bnpcMarkerShader )
  {
    printf( "BNPC marker shader created successfully (ID: %u)\n", m_bnpcMarkerShader );
  }
  else
  {
    printf( "Failed to create BNPC marker shader\n" );
  }
}


void ZoneEditor::buildBnpcMarkerGeometry()
{
  if( !m_selectedZone || m_bnpcs.empty() )
  {
    return;
  }

  std::vector< float > markerPositions;

  // Get current zone's BNPCs
  for( const auto& bnpc : m_bnpcs )
  {
    if( bnpc->territoryType == m_selectedZone->id )
    {
      // Add BNPC position
      markerPositions.push_back( bnpc->x );
      markerPositions.push_back( bnpc->y );
      markerPositions.push_back( bnpc->z );
    }
  }

  if( markerPositions.empty() )
  {
    printf( "No BNPCs found for zone %u\n", m_selectedZone->id );
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

  // Create VAO and VBO for markers
  glGenVertexArrays( 1, &m_bnpcMarkerVAO );
  glGenBuffers( 1, &m_bnpcMarkerVBO );

  glBindVertexArray( m_bnpcMarkerVAO );

  // Upload marker position data
  glBindBuffer( GL_ARRAY_BUFFER, m_bnpcMarkerVBO );
  glBufferData( GL_ARRAY_BUFFER, markerPositions.size() * sizeof( float ), markerPositions.data(), GL_STATIC_DRAW );

  // Set vertex attributes (position only)
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void * ) 0 );
  glEnableVertexAttribArray( 0 );

  glBindVertexArray( 0 );

  m_bnpcMarkerVertexCount = markerPositions.size() / 3;

  printf( "Created %d BNPC markers for zone %u\n", m_bnpcMarkerVertexCount, m_selectedZone->id );
}

void ZoneEditor::renderBnpcMarkers()
{
  if( !m_showBnpcMarkersInNavmesh || !m_bnpcMarkerShader || !m_bnpcMarkerVAO || m_bnpcMarkerVertexCount == 0 )
  {
    return;
  }

  // Set up matrices (same as navmesh)
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           ( float ) m_navmeshTextureWidth / ( float ) m_navmeshTextureHeight,
                                           0.1f, 10000.0f );
  glm::mat4 model = glm::mat4( 1.0f );
  glm::mat4 mvp = projection * view * model;

  // Enable point rendering
  glEnable( GL_PROGRAM_POINT_SIZE );

  // Use marker shader
  glUseProgram( m_bnpcMarkerShader );

  // Set uniforms
  GLint mvpLoc = glGetUniformLocation( m_bnpcMarkerShader, "mvp" );
  if( mvpLoc != -1 )
  {
    glUniformMatrix4fv( mvpLoc, 1, GL_FALSE, glm::value_ptr( mvp ) );
  }

  GLint colorLoc = glGetUniformLocation( m_bnpcMarkerShader, "markerColor" );
  if( colorLoc != -1 )
  {
    glUniform3f( colorLoc, 1.0f, 1.0f, 0.0f ); // Yellow
  }

  // Render markers as points
  glBindVertexArray( m_bnpcMarkerVAO );
  glDrawArrays( GL_POINTS, 0, m_bnpcMarkerVertexCount );
  glBindVertexArray( 0 );

  // Unbind shader
  glUseProgram( 0 );

  glDisable( GL_PROGRAM_POINT_SIZE );
}

void ZoneEditor::renderNavmeshToTexture()
{
  if( !m_navmeshShader || !m_navmeshVAO || m_navmeshIndexCount == 0 || !m_navmeshFBO )
  {
    return;
  }

  // Bind our framebuffer
  glBindFramebuffer( GL_FRAMEBUFFER, m_navmeshFBO );

  // Set viewport to match texture size
  glViewport( 0, 0, m_navmeshTextureWidth, m_navmeshTextureHeight );

  // Clear the framebuffer
  glClearColor( 0.1f, 0.1f, 0.2f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // Set up matrices
  glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );
  glm::mat4 projection = glm::perspective( glm::radians( 45.0f ),
                                           ( float ) m_navmeshTextureWidth / ( float ) m_navmeshTextureHeight,
                                           0.1f, 10000.0f );
  glm::mat4 model = glm::mat4( 1.0f );
  glm::mat4 mvp = projection * view * model;

  // Set OpenGL state
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LESS );
  glDisable( GL_BLEND );
  glDisable( GL_CULL_FACE );

  // Render navmesh first
  glUseProgram( m_navmeshShader );

  GLint mvpLoc = glGetUniformLocation( m_navmeshShader, "mvp" );
  if( mvpLoc != -1 )
  {
    glUniformMatrix4fv( mvpLoc, 1, GL_FALSE, glm::value_ptr( mvp ) );
  }

  GLint colorLoc = glGetUniformLocation( m_navmeshShader, "color" );
  if( colorLoc != -1 )
  {
    glUniform3f( colorLoc, 0.2f, 0.8f, 1.0f );
  }

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
  glBindVertexArray( 0 );

  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glUseProgram( 0 );

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

void ZoneEditor::drawBnpcOverlayMarkers( ImVec2 imagePos, ImVec2 imageSize )
{
  if( !m_showBnpcMarkersInNavmesh || !m_selectedZone || m_bnpcs.empty() )
  {
    return;
  }

  ImDrawList *drawList = ImGui::GetWindowDrawList();

  for( const auto& bnpc : m_bnpcs )
  {
    if( bnpc->territoryType != m_selectedZone->id )
    {
      continue;
    }

    // Convert world position to screen space
    glm::vec2 screenPos = worldToNavmeshScreen( bnpc->x, bnpc->y, bnpc->z, imageSize );

    // Skip if outside view
    if( screenPos.x < 0 || screenPos.y < 0 || screenPos.x >= imageSize.x || screenPos.y >= imageSize.y )
    {
      continue;
    }

    // Convert to ImGui screen coordinates
    ImVec2 markerPos( imagePos.x + screenPos.x, imagePos.y + screenPos.y );

    // Draw diamond shape
    float size = 4.0f;
    ImVec2 points[ 4 ] = {
      ImVec2( markerPos.x, markerPos.y - size ), // Top
      ImVec2( markerPos.x + size, markerPos.y ), // Right
      ImVec2( markerPos.x, markerPos.y + size ), // Bottom
      ImVec2( markerPos.x - size, markerPos.y ) // Left
    };

    // Draw filled diamond
    drawList->AddConvexPolyFilled( points, 4, m_bnpcIconColor );

    // Draw outline
    drawList->AddPolyline( points, 4, IM_COL32( 0, 0, 0, 255 ), ImDrawFlags_Closed, 1.0f );

    // Optional: draw BNPC name on hover
    if( ImGui::IsMouseHoveringRect( ImVec2( markerPos.x - size, markerPos.y - size ),
                                    ImVec2( markerPos.x + size, markerPos.y + size ) ) )
    {
      ImGui::SetTooltip( "BNPC: %s\nID: %u\nPos: %.1f, %.1f, %.1f",
                         bnpc->nameString.c_str(), bnpc->instanceId,
                         bnpc->x, bnpc->y, bnpc->z );
    }
  }
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
  ImGui::Image( reinterpret_cast< void * >( m_navmeshTexture ), imageSize, ImVec2( 0, 1 ), ImVec2( 1, 0 ) );

  // Draw BNPC markers as overlay (alternative to 3D markers)
  drawBnpcOverlayMarkers( imageScreenPos, imageSize );

  // Handle mouse interaction over the image
  if( ImGui::IsItemHovered() )
  {
    ImGuiIO& io = ImGui::GetIO();

    // Left mouse button - rotate camera
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
      // Middle mouse button
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

        // Convert mouse movement to world space movement
        glm::mat4 view = glm::lookAt( m_navCameraPos, m_navCameraTarget, glm::vec3( 0, 1, 0 ) );

        // Get camera right and up vectors
        glm::vec3 cameraRight = glm::vec3( view[ 0 ][ 0 ], view[ 1 ][ 0 ], view[ 2 ][ 0 ] );
        glm::vec3 cameraUp = glm::vec3( view[ 0 ][ 1 ], view[ 1 ][ 1 ], view[ 2 ][ 1 ] );

        // Pan sensitivity based on distance
        float panSensitivity = m_navCameraDistance * 0.001f;

        // Move target in camera space
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
      m_navCameraDistance -= io.MouseWheel * 10.0f;
      m_navCameraDistance = glm::clamp( m_navCameraDistance, 1.0f, 1000.0f );
      m_navCameraControlActive = true;
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
  ImGui::Text( "BNPCs: %d markers", m_bnpcMarkerVertexCount );
  ImGui::Checkbox( "Show BNPC Markers", &m_showBnpcMarkersInNavmesh );
  static bool showWireframe = false;
  ImGui::Checkbox( "Wireframe", &showWireframe );
  ImGui::Text( "Camera: dist=%.1f yaw=%.1f pitch=%.1f",
               m_navCameraDistance, m_navCameraYaw, m_navCameraPitch );
  ImGui::Text( "Target: (%.1f, %.1f, %.1f)",
               m_navCameraTarget.x, m_navCameraTarget.y, m_navCameraTarget.z );
  ImGui::Text( "Controls: LMB=rotate, MMB=pan, wheel=zoom" );
}

void ZoneEditor::showNavmeshWindow()
{
  if( !ImGui::Begin( "Navmesh Viewer", &m_showNavmeshWindow ) )
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

  // Add test buttons
  if( ImGui::Button( "Test Simple Triangle" ) )
  {
    buildSimpleNavmeshTest();
  }
  ImGui::SameLine();

  // Disable the button if no zone is selected or no navi provider
  bool canBuildNavmesh = m_selectedZone && m_pNaviProvider;
  if( !canBuildNavmesh )
  {
    ImGui::BeginDisabled();
  }

  if( ImGui::Button( "Build Real Navmesh" ) )
  {
    buildNavmeshGeometry();
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

  if( ImGui::Button( "Clear Navmesh" ) )
  {
    cleanupNavmeshGeometry();
  }

  // Add some debug info
  ImGui::Separator();
  ImGui::Text( "Current zone: %s", m_selectedZone ? m_selectedZone->name.c_str() : "None" );
  ImGui::Text( "Zone ID: %u", m_selectedZone ? m_selectedZone->id : 0 );
  ImGui::Text( "NavMesh available: %s", m_pNaviProvider && m_pNaviProvider->getNavMesh() ? "Yes" : "No" );
  ImGui::Text( "Loaded navmesh zone: %u", m_currentNavmeshZoneId );
  ImGui::Text( "Triangle count: %d", m_navmeshIndexCount / 3 );

  // Camera controls - only update sliders if not actively using mouse controls
  if( ImGui::CollapsingHeader( "Camera Controls", ImGuiTreeNodeFlags_DefaultOpen ) )
  {
    // Disable sliders when mouse controls are active
    if( m_navCameraControlActive )
    {
      ImGui::BeginDisabled();
    }

    if( ImGui::SliderFloat( "Distance", &m_navCameraDistance, 1.0f, 500.0f ) )
    {
      m_navCameraDistance = glm::clamp( m_navCameraDistance, 1.0f, 500.0f );
    }
    if( ImGui::SliderFloat( "Yaw", &m_navCameraYaw, -180.0f, 180.0f ) )
    {
      // Keep yaw in range
      while( m_navCameraYaw > 180.0f ) m_navCameraYaw -= 360.0f;
      while( m_navCameraYaw < -180.0f ) m_navCameraYaw += 360.0f;
    }
    if( ImGui::SliderFloat( "Pitch", &m_navCameraPitch, -89.0f, 89.0f ) )
    {
      m_navCameraPitch = glm::clamp( m_navCameraPitch, -89.0f, 89.0f );
    }

    if( m_navCameraControlActive )
    {
      ImGui::EndDisabled();
    }

    // Target position controls
    ImGui::Text( "Target Position:" );
    ImGui::SliderFloat( "Target X", &m_navCameraTarget.x, -1000.0f, 1000.0f );
    ImGui::SliderFloat( "Target Y", &m_navCameraTarget.y, -100.0f, 100.0f );
    ImGui::SliderFloat( "Target Z", &m_navCameraTarget.z, -1000.0f, 1000.0f );

    if( ImGui::Button( "Reset Camera" ) )
    {
      m_navCameraDistance = 100.0f;
      m_navCameraYaw = 0.0f;
      m_navCameraPitch = -30.0f;
      m_navCameraTarget = glm::vec3( 0.0f, 0.0f, 0.0f );
      m_navCameraControlActive = false;
    }

    if( ImGui::Button( "Top View" ) )
    {
      m_navCameraYaw = 0.0f;
      m_navCameraPitch = -89.0f;
      m_navCameraDistance = 200.0f;
      m_navCameraControlActive = false;
    }
    ImGui::SameLine();
    if( ImGui::Button( "Side View" ) )
    {
      m_navCameraYaw = 90.0f;
      m_navCameraPitch = 0.0f;
      m_navCameraDistance = 100.0f;
      m_navCameraControlActive = false;
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
    if( ImGui::BeginChild( "NavmeshRender", contentRegion, true, ImGuiWindowFlags_NoScrollbar ) )
    {
      renderNavmesh();
    }
    ImGui::EndChild();
  }

  ImGui::End();

  // If window was just closed, clean up geometry to free memory
  if( !m_showNavmeshWindow && m_navmeshIndexCount > 0 )
  {
    cleanupNavmeshGeometry();
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
