#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "commonshader.h"
#include "ExdData.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <Navi/NaviProvider.h>
#include "Engine/GfxApi.h"

// Add Detour includes for navmesh
#include <complex.h>

#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"
#include "datReaderPs3/DatCategories/bg/lgb.h"

class LgbViewer
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


  // Camera/view controls for navmesh
  glm::vec3 m_navCameraPos = glm::vec3( 0.0f, 30.0f, 0.0f );
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

  // Methods for OBJ model support
  bool loadObjModel( const std::string& filepath );

  void cleanupObjModel();

  void renderObjModel();

  void checkForObjFile();

  std::string getObjFilePath();


  // Add these methods
  void cleanupNavmeshGeometry(); // Separate from full cleanup

  // Add these methods
  void showBnpcWindow();

  void updateBnpcSearchFilter();

  void showNavmeshWindow();

  void initializeNavmeshRendering();

  void buildNavmeshGeometry();

  void buildSimpleNavmeshTest();

  void updateNavmeshCamera();

  void renderNavmesh();

  void cleanupNavmeshRendering();

  bool loadLgbData( std::string lgbPath, std::vector< LGB_GROUP >& groups, std::string& name );

  void createNavmeshFramebuffer();

  void renderNavmeshToTexture();


  std::vector< std::shared_ptr< CachedBnpc > > m_bnpcs;

public:
  LgbViewer();

  ~LgbViewer();

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

  std::vector< LGB_GROUP > bgGroups;
  std::string bgGroupsName;
  std::vector< LGB_GROUP > planeventGroups;
  std::string planeventName;
  std::vector< LGB_GROUP > planliveGroups;
  std::string planliveName;
  std::vector< LGB_GROUP > planmapGroups;
  std::string planmapName;
  std::vector< LGB_GROUP > plannerGroups;
  std::string plannerName;
  glm::vec3 m_focusWorldPos = glm::vec3( 0.0f );
  bool m_shouldFocusOnMap = false;

  // Add these methods
  void initializeBnpcMarkerRendering();

  void buildBnpcMarkerGeometry();

  void renderBnpcMarkers();

  void cleanupBnpcMarkerRendering();

  void drawBnpcOverlayMarkers( ImVec2 imagePos, ImVec2 imageSize );

  void showGroupsWindow();

  std::string getEntryTypeString( LgbEntryType type );

  std::string getEntryName( LgbEntry *entry );

  void onEntrySelected( LgbEntry *entry );

  void focusOn3DPosition( const vec3& position );

  glm::vec2 worldToNavmeshScreen( float worldX, float worldY, float worldZ, ImVec2 imageSize );

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

  // Add these members for individual entry viewing
  struct EntryViewWidget
  {
    ImGuiID id;
    std::shared_ptr<LgbEntry> entry;
    bool isOpen;
    std::string windowTitle;

    EntryViewWidget(std::shared_ptr<LgbEntry> e) : entry(e), isOpen(true)
    {
      id = ImGui::GetID(("EntryView_" + std::to_string(entry->header.instanceId)).c_str());
      windowTitle = std::to_string(entry->header.instanceId);
    }
  };

  std::vector<EntryViewWidget> m_entryViewWidgets;

  // Methods for entry viewing
  void showEntryViewWidget(EntryViewWidget& widget);
  void showSGEntryView(LGB_SG_ENTRY* entry);
  void showEObjEntryView(LGB_EOBJ_ENTRY* entry);
  void showExitRangeEntryView(LGB_EXIT_RANGE_ENTRY* entry);
  void showPopRangeEntryView(LGB_POP_RANGE_ENTRY* entry);
  void showUnimplementedEntryView(LgbEntry* entry);
  void openEntryViewWidget(std::shared_ptr<LgbEntry> entry);
  void showServerPathEntryView( LGB_SERVERPATH_ENTRY *entry );
  void showBnpcEntryView( LGB_BNPC_ENTRY *entry );

};
