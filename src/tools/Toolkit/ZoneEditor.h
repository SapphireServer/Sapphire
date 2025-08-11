#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "Common.h"
#include "Exd/ExdData.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <Navi/NaviProvider.h>

struct CachedBnpc
{
  uint16_t territoryType;
  std::string bnpcName;
  uint32_t instanceId;
  uint32_t nameOffset;
  float x;
  float y;
  float z;
  float rotation;
  uint32_t BaseId;
  uint32_t PopWeather;
  uint8_t PopTimeStart;
  uint8_t PopTimeEnd;
  uint32_t MoveAI;
  uint8_t WanderingRange;
  uint8_t Route;
  uint16_t EventGroup;
  uint32_t NameId;
  uint32_t DropItem;
  float SenseRangeRate;
  uint16_t Level;
  uint8_t ActiveType;
  uint8_t PopInterval;
  uint8_t PopRate;
  uint8_t PopEvent;
  uint8_t LinkGroup;
  uint8_t LinkFamily;
  uint8_t LinkRange;
  uint8_t LinkCountLimit;
  int8_t NonpopInitZone;
  int8_t InvalidRepop;
  int8_t LinkParent;
  int8_t LinkOverride;
  int8_t LinkReply;
  int8_t Nonpop;
  float HorizontalPopRange;
  float VerticalPopRange;
  int32_t BNpcBaseData;
  uint8_t RepopId;
  uint8_t BNPCRankId;
  uint16_t TerritoryRange;
  uint32_t BoundInstanceID;
  uint32_t FateLayoutLabelId;
  uint32_t NormalAI;
  uint32_t ServerPathId;
  uint32_t EquipmentID;
  uint32_t CustomizeID;

  std::string nameString;
};

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

  bool m_showBnpcWindow = true;
  char m_bnpcSearchBuffer[256] = "";
  std::string m_lastBnpcSearchTerm = "N/A";
  std::vector<CachedBnpc*> m_filteredBnpcs;
  int m_selectedBnpcIndex = -1;
  std::shared_ptr< Sapphire::Common::Navi::NaviProvider > m_pNaviProvider;

  // Add these methods
  void showBnpcWindow();
  void updateBnpcSearchFilter();


  std::vector< std::shared_ptr< CachedBnpc > > m_bnpcs;

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

  bool m_showBnpcIcons = true;
  float m_bnpcIconSize = 8.0f;
  ImU32 m_bnpcIconColor = IM_COL32(255, 255, 0, 255); // Yellow
  ImU32 m_selectedBnpcIconColor = IM_COL32(255, 0, 0, 255); // Red for selected
  float m_mapScale = 100.0f; // You'll need to get this from the map data
  ImVec2 m_mapOffset = ImVec2(1024.0f, 1024.0f); // Default offset

  // Helper methods
  void drawBnpcIcons();
  ImVec2 worldToScreenPos(float worldX, float worldZ, const ImVec2& imagePos, const ImVec2& imageSize);


private:
  void initializeCache();

  void updateSearchFilter();

  void loadBnpcs();

  void onSelectionChanged();

  void onSelectionCleared();

  void showZoneList();

  void showZoneDetails();

  void showMapWindow();

  std::vector< uint8_t > decompressDXT1( const uint8_t *compressedData, int width, int height );

  void loadMapTexture( uint32_t mapId );

  void clearMapTexture();
};
