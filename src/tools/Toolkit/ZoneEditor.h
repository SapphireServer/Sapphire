#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "Exd/ExdData.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct CachedZoneInfo
{
  uint32_t id;
  std::string name;
  std::string lvb;
  Excel::TerritoryType data;

  std::string placeName;

  // Pre-computed display strings
  std::string displayText;
  std::string searchText; // Lowercase for searching
};

class ZoneEditor
{
private:
  // Cached data
  std::vector< uint32_t > m_zoneIds;
  std::unordered_map< uint32_t, std::unique_ptr< CachedZoneInfo > > m_cachedZones;
  std::vector< CachedZoneInfo * > m_filteredZones; // For search results

  // UI state
  int m_selectedIndex = -1;
  uint32_t m_selectedZoneId = 0;
  CachedZoneInfo *m_selectedZone = nullptr;
  char m_searchBuffer[ 256 ] = "";
  std::string m_lastSearchTerm = "N/A";
  bool m_needsRefresh = true;
  bool m_showMapWindow = false;

  // Texture/rendering data
  uint32_t m_mapTextureId = 0;
  int m_mapWidth = 0;
  int m_mapHeight = 0;
  uint32_t m_currentMapId = 0;
  float m_zoomLevel = 1.0f;


public:
  ZoneEditor();

  ~ZoneEditor();

  void init();

  // Main interface
  void show();

  void refresh(); // Force refresh of cached data

  // Getters
  uint32_t getSelectedZoneId() const
  {
    return m_selectedZoneId;
  }

  const CachedZoneInfo *getSelectedZone() const
  {
    return m_selectedZone;
  }

  glm::vec3 get3dPosFrom2d( float x, float y, float scale, uint32_t height, uint32_t width )
  {
    glm::vec3 ret;
    float scale2 = ( float ) scale / 100.0f;
    ret.x = ( x * scale2 ) + ( ( float ) height * 2.f ); //( x / scale2 ) - mapOffsetX;
    ret.z = ( y * scale2 ) + ( ( float ) width * 2.f ); //( y / scale2 ) - mapOffsetY;

    return ret;
  }

  glm::vec2 get2dPosFrom3d( float x, float y, float scale )
  {
    glm::vec2 ret;
    float scale2 = ( float ) ( ( float ) scale / 100.f );
    ret.x = ( ( x * scale2 ) + 1024.f );
    ret.y = ( ( y * scale2 ) + 1024.f );

    return ret;
  }

private:
  void initializeCache();

  void updateSearchFilter();

  void onSelectionChanged();

  void onSelectionCleared();

  void showZoneList();

  void showZoneDetails();

  void showMapWindow();

  std::vector< uint8_t > decompressDXT1( const uint8_t *compressedData, int width, int height );

  void loadMapTexture( uint32_t mapId );

  void clearMapTexture();
};
