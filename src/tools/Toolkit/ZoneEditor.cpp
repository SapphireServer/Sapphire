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

ZoneEditor::ZoneEditor()
{
}

ZoneEditor::~ZoneEditor()
{
  clearMapTexture();
}

void ZoneEditor::init()
{
  initializeCache();
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

    // Load navmesh, audio, etc.
    // loadNavMesh(m_selectedZoneId);
    // loadZoneAudio(data.BGM);
  }
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

    // Action buttons
    if( ImGui::Button( "Load Zone" ) )
    {
      // Add your zone loading logic here
    }
    ImGui::SameLine();
    if( ImGui::Button( "Show Map" ) )
    {
      if( data.Map > 0 )
      {
        m_showMapWindow = true;
      }
    }
    ImGui::SameLine();
    if( ImGui::Button( "Export Data" ) )
    {
      // Add export functionality here
    }
    ImGui::SameLine();
    if( ImGui::Button( "Clear Selection" ) )
    {
      m_selectedIndex = -1;
      m_selectedZoneId = 0;
      m_selectedZone = nullptr;
      onSelectionCleared();
    }
  }
  ImGui::EndChild();
}

void ZoneEditor::showMapWindow()
{
    if (!m_showMapWindow || m_mapTextureId == 0)
        return;

    ImGui::Begin("Map Viewer", &m_showMapWindow, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);

    // Menu bar with map info and controls
    if (ImGui::BeginMenuBar()) {
        ImGui::Text("Map ID: %u | Size: %dx%d", m_currentMapId, m_mapWidth, m_mapHeight);
        ImGui::Separator();
        if (ImGui::Button("Reset Zoom")) {
            m_zoomLevel = 1.0f;
        }
        if (ImGui::Button("Fit to Window")) {
            m_zoomLevel = -1.0f; // Special value to trigger fit-to-window
        }
        ImGui::EndMenuBar();
    }

    // Get available content region
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();

    // Handle zoom controls
    if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) {
        float wheel = ImGui::GetIO().MouseWheel;
        if (wheel != 0.0f) {
            m_zoomLevel += wheel * 0.1f;
            m_zoomLevel = std::max(0.1f, std::min(m_zoomLevel, 10.0f));
        }
    }

    // Calculate image size
    ImVec2 imageSize;
    if (m_zoomLevel <= 0.0f) {
        // Fit to window mode
        float scaleX = contentRegion.x / static_cast<float>(m_mapWidth);
        float scaleY = contentRegion.y / static_cast<float>(m_mapHeight);
        float scale = std::min(scaleX, scaleY);
        imageSize = ImVec2(m_mapWidth * scale, m_mapHeight * scale);
    } else {
        // Manual zoom mode
        imageSize = ImVec2(m_mapWidth * m_zoomLevel, m_mapHeight * m_zoomLevel);
    }

    // Center the image if it's smaller than the content region
    ImVec2 cursorPos = ImGui::GetCursorPos();
    if (imageSize.x < contentRegion.x) {
        cursorPos.x += (contentRegion.x - imageSize.x) * 0.5f;
    }
    if (imageSize.y < contentRegion.y) {
        cursorPos.y += (contentRegion.y - imageSize.y) * 0.5f;
    }
    ImGui::SetCursorPos(cursorPos);

    // Display the map image
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(m_mapTextureId)), imageSize);

    // Handle panning (drag to move when zoomed in)
    if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        ImGui::SetScrollX(ImGui::GetScrollX() - delta.x);
        ImGui::SetScrollY(ImGui::GetScrollY() - delta.y);
    }

    // Show zoom level and controls in bottom-left corner
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPos(ImVec2(10, windowSize.y - 60));

    if (m_zoomLevel > 0.0f) {
        ImGui::Text("Zoom: %.1fx", m_zoomLevel);
    } else {
        ImGui::Text("Zoom: Fit to Window");
    }
    ImGui::Text("Mouse wheel: Zoom | Left drag: Pan");

    ImGui::End();
}


std::vector<uint8_t> ZoneEditor::decompressDXT1(const uint8_t* compressedData, int width, int height)
{
    std::vector<uint8_t> decompressed(width * height * 4); // RGBA output

    const int blockCountX = (width + 3) / 4;
    const int blockCountY = (height + 3) / 4;

    for (int by = 0; by < blockCountY; ++by) {
        for (int bx = 0; bx < blockCountX; ++bx) {
            const uint8_t* block = compressedData + (by * blockCountX + bx) * 8;

            // Read color endpoints (little endian)
            uint16_t color0 = block[0] | (block[1] << 8);
            uint16_t color1 = block[2] | (block[3] << 8);
            uint32_t indices = block[4] | (block[5] << 8) | (block[6] << 16) | (block[7] << 24);

            // Convert RGB565 to RGB888
            uint8_t r0 = ((color0 >> 11) & 0x1F) << 3;  // 5 bits -> 8 bits
            uint8_t g0 = ((color0 >> 5) & 0x3F) << 2;   // 6 bits -> 8 bits
            uint8_t b0 = (color0 & 0x1F) << 3;          // 5 bits -> 8 bits

            uint8_t r1 = ((color1 >> 11) & 0x1F) << 3;
            uint8_t g1 = ((color1 >> 5) & 0x3F) << 2;
            uint8_t b1 = (color1 & 0x1F) << 3;

            // Generate color palette (4 colors)
            uint8_t colors[4][4]; // [color_index][rgba]
            colors[0][0] = r0; colors[0][1] = g0; colors[0][2] = b0; colors[0][3] = 255;
            colors[1][0] = r1; colors[1][1] = g1; colors[1][2] = b1; colors[1][3] = 255;

            if (color0 > color1) {
                // 4-color mode (opaque)
                colors[2][0] = (2 * r0 + r1) / 3;
                colors[2][1] = (2 * g0 + g1) / 3;
                colors[2][2] = (2 * b0 + b1) / 3;
                colors[2][3] = 255;

                colors[3][0] = (r0 + 2 * r1) / 3;
                colors[3][1] = (g0 + 2 * g1) / 3;
                colors[3][2] = (b0 + 2 * b1) / 3;
                colors[3][3] = 255;
            } else {
                // 3-color mode (with transparency)
                colors[2][0] = (r0 + r1) / 2;
                colors[2][1] = (g0 + g1) / 2;
                colors[2][2] = (b0 + b1) / 2;
                colors[2][3] = 255;

                colors[3][0] = 0;
                colors[3][1] = 0;
                colors[3][2] = 0;
                colors[3][3] = 0; // Transparent
            }

            // Decode 16 pixels in this 4x4 block
            for (int py = 0; py < 4 && (by * 4 + py) < height; ++py) {
                for (int px = 0; px < 4 && (bx * 4 + px) < width; ++px) {
                    // Each pixel uses 2 bits for color index
                    int pixelIndex = (py * 4 + px) * 2;
                    int colorIndex = (indices >> pixelIndex) & 0x3;

                    // Calculate output position
                    int outputX = bx * 4 + px;
                    int outputY = by * 4 + py;
                    int outputIndex = (outputY * width + outputX) * 4;

                    // Write RGBA pixel
                    decompressed[outputIndex + 0] = colors[colorIndex][0]; // R
                    decompressed[outputIndex + 1] = colors[colorIndex][1]; // G
                    decompressed[outputIndex + 2] = colors[colorIndex][2]; // B
                    decompressed[outputIndex + 3] = colors[colorIndex][3]; // A
                }
            }
        }
    }

    return decompressed;
}

void ZoneEditor::loadMapTexture( uint32_t mapId )
{
  auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();
  auto mapEntry = exdD.getRow< Excel::Map >( mapId );
  if( !mapEntry )
    return;
  auto mapData = mapEntry->data();
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

  const uint8_t* header = reinterpret_cast<const uint8_t*>(headerData.data());

  // Parse header information (adjust these offsets based on your actual header format)
  uint32_t width = *reinterpret_cast<const uint16_t*>(header + 8);
  uint32_t height = *reinterpret_cast<const uint16_t*>(header + 10);
  uint32_t format = *reinterpret_cast<const uint32_t*>(header + 12); // Should indicate DXT1

  // Validate dimensions
  if( width == 0 || height == 0 || width > 4096 || height > 4096 )
    return;

  // Calculate expected DXT1 size
  size_t expectedSize = ((width + 3) / 4) * ((height + 3) / 4) * 8; // 8 bytes per 4x4 block
  if( dxtData.size() < expectedSize )
    return;

  // Get raw DXT1 data
  const uint8_t* compressedData = reinterpret_cast<const uint8_t*>(dxtData.data());

  // Decompress DXT1 to RGBA
  auto decompressedData = decompressDXT1(compressedData, width, height);

  // Clean up previous texture
  clearMapTexture();

  // Create OpenGL texture
  glGenTextures(1, &m_mapTextureId);
  glBindTexture(GL_TEXTURE_2D, m_mapTextureId);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // Upload texture data
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, decompressedData.data());

  glBindTexture(GL_TEXTURE_2D, 0);

  m_mapWidth = width;
  m_mapHeight = height;
  m_currentMapId = mapId;
  m_showMapWindow = true;

  // Optional: Debug output
  Engine::Logger::info("Loaded map texture: {}x{}, format: {}, compressed size: {}, decompressed size: {}",
                       width, height, format, dxtData.size(), decompressedData.size());
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
}
