#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <set>
#include "commonshader.h"
#include "Exd/ExdData.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <Navi/NaviProvider.h>
#include "Engine/GfxApi.h"

// Add Detour includes for navmesh
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"


struct CachedServerPath
{
  vec3 position;
  uint32_t instanceId;
  std::vector< PathControlPoint > points;
};

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
  std::string groupName;

  enum SenseType : uint8_t
  {
    NONE = 0,
    VISION = 1,
    HEARING = 2,
    PRESENCE = 3,
    VITALITY = 4,
    MAGIC = 5,
    ABILITIE = 6,
    WEAPON_SKILL = 7,
    POISON = 8,
    SENSE_COUNT
  };
  struct BNpcBaseData
  {
    uint16_t TerritoryRange;
    SenseType Sense[2];
    uint8_t SenseRange[2];
  } baseData;
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
  char m_bnpcSearchBuffer[ 256 ] = "";
  std::string m_lastBnpcSearchTerm = "N/A";
  std::vector< CachedBnpc * > m_filteredBnpcs;
  int m_selectedBnpcIndex = -1;
  std::shared_ptr< Sapphire::Common::Navi::NaviProvider > m_pNaviProvider;

  // Navmesh rendering members
  bool m_showNavmeshWindow = true;
  GLuint m_navmeshVAO = 0;
  GLuint m_navmeshVBO = 0;
  GLuint m_navmeshEBO = 0;
  GLuint m_navmeshShader = 0;
  int m_navmeshIndexCount = 0;

  GLuint m_navmeshFBO = 0;
  GLuint m_navmeshTexture = 0;
  GLuint m_navmeshDepthBuffer = 0;
  int m_navmeshTextureWidth = 512;
  int m_navmeshTextureHeight = 512;
  bool m_needsNavmeshRebuild = false;
  bool m_navCameraControlActive = false;
  float m_navmeshMinHeight = 0.0f;
  float m_navmeshMaxHeight = 1.0f;
  GLuint m_bnpcMarkerInstanceVBO = 0;
  int m_bnpcMarkerInstanceCount = 0;

  struct BnpcWorldPos
  {
    glm::vec3 worldPos;
    CachedBnpc *bnpc;
  };

  glm::vec3 m_focusWorldPos = glm::vec3( 0.0f );
  bool m_shouldFocusOnMap = false;

  // Add these new members for group color coding
  std::unordered_map< std::string, ImU32 > m_groupColorMap;

  // Helper method to generate group colors
  ImU32 getGroupColor( const std::string& groupName );


  std::vector< BnpcWorldPos > m_bnpcWorldPositions;

  // Helper functions
  glm::vec2 worldTo3DScreen( const glm::vec3& worldPos, const ImVec2& imageSize );

  void handle3DBnpcInteraction( ImVec2 imagePos, ImVec2 imageSize );

  // Ray casting for world interaction
  struct Ray
  {
    glm::vec3 origin;
    glm::vec3 direction;
  };

  struct RayHit
  {
    bool hit = false;
    glm::vec3 position;
    glm::vec3 normal;
    float distance = 0.0f;
    int triangleIndex = -1;
  };

  // Ray casting methods
  Ray screenToWorldRay( const ImVec2& screenPos, const ImVec2& imageSize );

  RayHit castRayToNavmesh( const Ray& ray );

  RayHit castRayToObjModel( const Ray& ray );

  RayHit castRayToGeometry( const Ray& ray ); // Unified method
  bool rayTriangleIntersect( const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
                             float& distance, glm::vec3& normal );

  void onWorldClick( const RayHit& hit );

  void renderWorldMarker( const glm::vec3& worldPos );

  // World editing state
  bool m_worldEditingMode = false;
  glm::vec3 m_lastClickWorldPos = glm::vec3( 0.0f );
  bool m_showClickMarker = false;
  bool m_showServerPathWindow = true;
  uint32_t m_selectedServerPathId = 0;
  GLuint m_serverPathVAO = 0;
  GLuint m_serverPathVBO = 0;
  int m_serverPathVertexCount = 0;

  void initializeServerPathShader();

  void initializeServerPathRendering();
  void buildServerPathGeometry();
  bool m_showServerPathsInNavmesh = true;
  GLuint m_serverPathShader = 0;

  void renderServerPaths();


  // Camera/view controls for navmesh
  glm::vec3 m_navCameraPos = glm::vec3( 0.0f, 10.0f, 0.0f );
  glm::vec3 m_navCameraTarget = glm::vec3( 0.0f, 0.0f, 0.0f );
  float m_navCameraDistance = 50.0f;
  float m_navCameraYaw = 0.0f;
  float m_navCameraPitch = 30.0f;
  // Mouse interaction state
  bool m_navMouseDragging = false;
  bool m_navMousePanning = false;
  ImVec2 m_navLastMousePos = ImVec2( 0, 0 );

  uint32_t m_currentNavmeshZoneId = 0;

  // OBJ Model support
  struct ObjVertex
  {
    glm::vec3 position; // Only position, no normals or texcoords
  };


  struct ObjModel
  {
    std::vector< ObjVertex > vertices;
    std::vector< unsigned int > indices;
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    int indexCount = 0;
    bool loaded = false;
  };

  ObjModel m_objModel;
  GLuint m_objShader = 0;
  bool m_objLoaded = false;
  bool m_showObjModel = false;
  std::string m_currentObjPath;

  std::string m_selectedGroupName = "";
  std::set< uint32_t > m_selectedBnpcInstanceIds; // Store instance IDs of selected BNPCs
  bool m_groupSelectionMode = true; // Toggle between group and individual selection

  // Methods for OBJ model support
  bool loadObjModel( const std::string& filepath );

  void cleanupObjModel();

  void renderObjModel();

  void checkForObjFile();

  std::string getObjFilePath();

  void cleanupNavmeshGeometry(); // Separate from full cleanup

  void showBnpcWindow();

  void showBnpcWindow2();

  void showServerPathWindow();

  void updateBnpcSearchFilter();

  void showNavmeshWindow();

  void initializeNavmeshRendering();

  void buildNavmeshGeometry();

  void buildSimpleNavmeshTest();

  void updateNavmeshCamera();

  void renderNavmesh();

  void cleanupNavmeshRendering();

  void createNavmeshFramebuffer();

  void renderNavmeshToTexture();

  struct BnpcNameCacheEntry
  {
    std::string name;
    Excel::BNpcName data;
  };

  std::vector< std::shared_ptr< CachedBnpc > > m_bnpcs;
  std::unordered_map< uint32_t, Excel::BNpcBase > m_bnpcBaseCache;
  std::unordered_map< uint32_t, CachedServerPath > m_serverPathCache;
  std::unordered_map< uint32_t, BnpcNameCacheEntry > m_bnpcNameCache;
  std::unordered_map< uint32_t, Excel::BNpcCustomize > m_bnpcCustomizeCache;

  // Add these to ZoneEditor.h in the private section:
  bool m_showBnpcNameSelector = false;
  bool m_showBnpcBaseSelector = false;
  char m_nameSearchBuffer[256] = "";
  char m_baseSearchBuffer[256] = "";

  // Add these method declarations to the public section:
  void showBnpcNameSelector();
  void showBnpcBaseSelector();
  // BNPC Window UI Functions
  void showBnpcWindowHeader();
  void showBnpcTreeView( float splitterWidth, const ImVec2& windowSize );
  void showBnpcSplitter( float& splitterWidth, const ImVec2& windowSize );
  void showBnpcDetailsView( const ImVec2& windowSize );
  void showBnpcSelectors();

  // BNPC Tree View Functions
  void showBnpcGroupNode( const std::string& groupName, const std::vector< CachedBnpc * >& bnpcs );
  void showBnpcNodesInGroup( const std::string& groupName, const std::vector< CachedBnpc * >& bnpcs );
  void showBnpcNode( const std::string& groupName, CachedBnpc* bnpc, const std::vector< CachedBnpc * >& groupBnpcs );

  // BNPC Selection Handling Functions
  void handleGroupSelection( const std::string& groupName, const std::vector< CachedBnpc * >& bnpcs );
  void handleCollapsedGroupSelection( const std::string& groupName, const std::vector< CachedBnpc * >& bnpcs );
  void handleBnpcSelection( const std::string& groupName, CachedBnpc* bnpc, const std::vector< CachedBnpc * >& groupBnpcs );

  // BNPC Context Menu Functions
  void showGroupContextMenu( const std::string& groupName, const std::string& contextIdPrefix );
  void showBnpcContextMenu( CachedBnpc* bnpc );
  void showBnpcTreeContextMenu();

  // BNPC Details Panel Functions
  bool showBnpcBasicInfo( CachedBnpc* selectedBnpc );
  bool showBnpcPositionInfo( CachedBnpc* selectedBnpc );
  bool showBnpcPopulationInfo( CachedBnpc* selectedBnpc );
  bool showBnpcAIBehaviorInfo( CachedBnpc* selectedBnpc );
  bool showBnpcLinkInfo( CachedBnpc* selectedBnpc );
  bool showBnpcAppearanceInfo( CachedBnpc* selectedBnpc );
  bool showBnpcInstanceInfo( CachedBnpc* selectedBnpc );
  void showBnpcActionButtons( CachedBnpc* selectedBnpc );
  bool showBnpcBaseDataInfo( CachedBnpc* selectedBnpc );


  // Add these new members for sense range rendering
  GLuint m_senseRangeVAO = 0;
  GLuint m_senseRangeVBO = 0;
  GLuint m_senseRangeShader = 0;
  int m_senseRangeVertexCount = 0;
  bool m_showSenseRanges = true;

  // Add these methods
  void initializeSenseRangeRendering();
  void buildSenseRangeGeometry();
  void renderSenseRanges();
  void cleanupSenseRangeRendering();

  // Helper methods for geometry creation
  std::vector<float> createCircleVertices(float radius, int segments = 64);
  std::vector<float> createConeVertices(float radius, float angle, int segments = 32);


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
  float m_bnpcIconSize = 2.0f;
  ImU32 m_bnpcIconColor = IM_COL32( 255, 255, 0, 255 ); // Yellow
  ImU32 m_selectedBnpcIconColor = IM_COL32( 255, 0, 0, 255 ); // Red for selected
  float m_mapScale = 100.0f; // You'll need to get this from the map data
  ImVec2 m_mapOffset = ImVec2( 1024.0f, 1024.0f ); // Default offset

  // Helper methods
  void drawBnpcIcons();

  ImVec2 worldToScreenPos( float worldX, float worldZ, const ImVec2& imagePos, const ImVec2& imageSize );


  // Add these new members for BNPC rendering
  bool m_showBnpcMarkersInNavmesh = true;
  GLuint m_bnpcMarkerVAO = 0;
  GLuint m_bnpcMarkerVBO = 0;
  GLuint m_bnpcMarkerShader = 0;
  int m_bnpcMarkerVertexCount = 0;

  // Add these methods
  void initializeBnpcMarkerRendering();

  void buildBnpcMarkerGeometry();

  void renderBnpcMarkers();

  void cleanupBnpcMarkerRendering();

  glm::vec2 worldToNavmeshScreen( float worldX, float worldY, float worldZ, ImVec2 imageSize );
  void focusOn3DPosition( const glm::vec3& position );
  void showGambitEditor();
private:
  void initializeCache();

  void updateSearchFilter();

  void loadBnpcs();

  void loadServerPaths();

  void onSelectionChanged();

  void onSelectionCleared();

  void showZoneList();

  void showZoneDetails();

  void showMapWindow();

  std::vector< uint8_t > decompressDXT1( const uint8_t *compressedData, int width, int height );

  void loadMapTexture( uint32_t mapId );

  void clearMapTexture();
};
