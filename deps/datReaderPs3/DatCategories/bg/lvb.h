#ifndef _LVB_H
#define _LVB_H

#include <cstring>
#include <memory>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "matrix4.h"
#include "vec3.h"
#include "sgb.h"
#include "LgbTypes.h"
#include "../../bparse.h"

struct FileHeader
{
  char FileID[4];
  int32_t FileSize;
  int32_t TotalChunkCount;
  char ChunkID[4];
  int32_t ChunkSize;
};
static_assert( sizeof( FileHeader ) == 20 );

struct LayoutLayerSet
{
  uint32_t m_layerSetId;
  uint32_t m_territoryTypeId;
  char m_layerSetName[32];
};
static_assert( sizeof( LayoutLayerSet ) == 40 );

struct LayerSet
{
  int32_t NavimeshAssetPath;
  uint32_t LayerSetID;
  int32_t LayerReferences;
  int32_t LayerReference_Count;
  uint32_t TerritoryTypeID;
  int32_t Name;
};
static_assert( sizeof( LayerSet ) == 24 );

struct SceneChunk
{
  int32_t LayerGroups;
  int32_t LayerGroup_Count;
  int32_t Settings;
  int32_t LayerSetFold;
  int32_t SGTimelineFold;
  int32_t LGBAssetPaths;
  int32_t LGBAssetPathCount;
  int32_t _SGDoorSettings;
  int32_t SGSetting;
  int32_t _SGRotationSettings;
  int32_t _SGRandomTimelineSettings;
  int32_t HousingSetting;
  int32_t _SGClockSettings;
  int32_t Reserved1[3];
};
static_assert( sizeof( SceneChunk ) == 64 );

struct SceneSettings
{
  int8_t IsPartialOutput;
  int8_t ContainsLayerSetRef;
  int8_t IsDungeon;
  int8_t ExistsGrassData;
  int32_t TerrainAssetPath;
  int32_t EnvSetAttrReferences;
  int32_t EnvSetAttrReference_Count;
  int32_t SunriseAngle;
  int32_t SkyVisibilityPath;
  float CameraFarClipDistance;
  float MainLightOrbitCurve;
  float MainLightOrbitClamp;
  float ShadowFarDistance;
  float ShadowDistanceFade;
  float BGSkyVisibility;
  int32_t BGMaterialColor;
  int32_t LightClipAABBPath;
  int8_t TerrainOcclusionRainEnabled;
  int8_t TerrainOcclusionDustEnabled;
  int8_t ConstantTimeModeEnabled;
  uint8_t Padding00[1];
  float ConstantTime;
  int32_t LevelWeatherTable;
  int32_t Reserved1[5];
};
static_assert( sizeof( SceneSettings ) == 88 );

struct LayerSetFolder
{
  int32_t LayerSets;
  int32_t LayerSetCount;
};
static_assert( sizeof( LayerSetFolder ) == 8 );

struct SGTimelineFolder
{
  int32_t SGTimelines;
  int32_t SGTimelineCount;
};
static_assert( sizeof( SGTimelineFolder ) ==  8 );

enum eShowHideAnimationType : int32_t
{
  Invalid = 0x0,
  None_1 = 0x1,
  Auto = 0x2,
  Timeline_0 = 0x3,
  AutoWithAnimationTime = 0x4,
};

/* 20883 */
struct SGSettings
{
  uint8_t NamePlateInstanceID;
  uint8_t TimelineShowingID;
  uint8_t TimelineHidingID;
  uint8_t TimelineShownID;
  uint8_t TimelineHiddenID;
  uint8_t GeneralPurposeTimelineIDs[16];
  int8_t TimelineShowingIDEnabled;
  int8_t TimelineHidingIDEnabled;
  uint8_t Padding00[1];
  eShowHideAnimationType ShowHideAnimationType;
  uint16_t ShowAnimationTime;
  uint16_t HideAnimationTime;
  int32_t SGActionFolder;
};
static_assert( sizeof( SGSettings ) == 36 );

struct LVB_FILE
{
  FileHeader header;
  SceneChunk sceneChunk;
  SceneSettings sceneSettings;

  LayerSetFolder layerSetFolder;
  SGTimelineFolder sgTimelineFolder;
  SGSettings sgSettings;

  std::vector< LayerSet > layers;
  std::vector< LayoutLayerSet > layoutLayers;
  std::vector< std::string > layerNames;

  //std::vector< LGB_GROUP > groups;
  std::string m_name;

  LVB_FILE( char* buf, const std::string& name ) : LVB_FILE( buf )
  {
    m_name = name;
  }

  LVB_FILE( char* buf )
  {
    header = *reinterpret_cast< FileHeader* >( buf );
    convertToLEBytes( header );

    if( strncmp( &header.FileID[ 0 ], "LVB1", 4 ) != 0 )
      throw std::runtime_error( "Invalid LVB file!" );

    auto baseOffset = sizeof( header );
    auto dataOffset = baseOffset;

    sceneChunk = *reinterpret_cast< SceneChunk* >( buf + baseOffset );
    convertToLEBytes( sceneChunk );

    baseOffset += sizeof( sceneChunk );

    sceneSettings = *reinterpret_cast< SceneSettings* >( buf + baseOffset );
    convertToLEBytes( sceneSettings );

    layerSetFolder = *reinterpret_cast< LayerSetFolder* >( buf + dataOffset + sceneChunk.LayerSetFold );
    convertToLEBytes( layerSetFolder );

    sgTimelineFolder = *reinterpret_cast< SGTimelineFolder* >( buf + dataOffset + sceneChunk.SGTimelineFold );
    convertToLEBytes( sgTimelineFolder );

    sgSettings = *reinterpret_cast< SGSettings* >( buf + dataOffset + sceneChunk.SGSetting );
    convertToLEBytes( sgSettings );

    layers.resize( layerSetFolder.LayerSetCount );
    memcpy( (char*)&layers[0], buf + dataOffset + sceneChunk.LayerSetFold + layerSetFolder.LayerSets, sizeof( LayerSet ) * layerSetFolder.LayerSetCount );

    int i = 0;
    for( auto& entry : layers )
    {
      convertToLEBytes( entry );

      auto entryOffset = buf + dataOffset + sceneChunk.LayerSetFold + layerSetFolder.LayerSets + ( sizeof( LayerSet ) * i++ );

      layerNames.emplace_back( entryOffset + entry.Name );

//      for( int j = 0; j < entry.LayerReference_Count; ++j )
//      {
//        LayoutLayerSet layoutLayer{};
//
//        memcpy(
//          ( char* ) &layoutLayer,
//          entryOffset + entry.LayerReferences + ( sizeof( LayoutLayerSet ) * j ),
//          sizeof( LayoutLayerSet )
//        );
//
//        convertToLEBytes( layoutLayer );
//
//        layoutLayers.emplace_back( layoutLayer );
//      }
    }

  }

  void convertToLEBytes( LayoutLayerSet& lls ) const
  {
    lls.m_layerSetId = xivps3::utils::bparse::byteswap( lls.m_layerSetId );
    lls.m_territoryTypeId = xivps3::utils::bparse::byteswap( lls.m_territoryTypeId );
  }

  void convertToLEBytes( FileHeader& header ) const
  {
    header.FileSize = xivps3::utils::bparse::byteswap( header.FileSize );
    header.TotalChunkCount = xivps3::utils::bparse::byteswap( header.TotalChunkCount );
    header.ChunkSize = xivps3::utils::bparse::byteswap( header.ChunkSize );
  }

  void convertToLEBytes( LayerSet& entry ) const
  {
    entry.LayerReference_Count = xivps3::utils::bparse::byteswap( entry.LayerReference_Count );
    entry.LayerReferences = xivps3::utils::bparse::byteswap( entry.LayerReferences );
    entry.LayerSetID = xivps3::utils::bparse::byteswap( entry.LayerSetID );
    entry.Name = xivps3::utils::bparse::byteswap( entry.Name );
    entry.NavimeshAssetPath = xivps3::utils::bparse::byteswap( entry.NavimeshAssetPath );
    entry.TerritoryTypeID = xivps3::utils::bparse::byteswap( entry.TerritoryTypeID );
  }

  void convertToLEBytes( SGSettings& sgSettings ) const
  {
    sgSettings.HideAnimationTime = xivps3::utils::bparse::byteswap( sgSettings.HideAnimationTime );
    sgSettings.SGActionFolder = xivps3::utils::bparse::byteswap( sgSettings.SGActionFolder );
    sgSettings.ShowAnimationTime = xivps3::utils::bparse::byteswap( sgSettings.ShowAnimationTime );
    sgSettings.ShowHideAnimationType = xivps3::utils::bparse::byteswap( sgSettings.ShowHideAnimationType );
  }

  void convertToLEBytes( SGTimelineFolder& sgTimelineFolder ) const
  {
    sgTimelineFolder.SGTimelineCount = xivps3::utils::bparse::byteswap( sgTimelineFolder.SGTimelineCount );
    sgTimelineFolder.SGTimelines = xivps3::utils::bparse::byteswap( sgTimelineFolder.SGTimelines );
  }

  void convertToLEBytes( LayerSetFolder& layerSetFolder ) const
  {
    layerSetFolder.LayerSetCount = xivps3::utils::bparse::byteswap( layerSetFolder.LayerSetCount );
    layerSetFolder.LayerSets = xivps3::utils::bparse::byteswap( layerSetFolder.LayerSets );
  }

  void convertToLEBytes( SceneSettings& sceneSettings ) const
  {
    sceneSettings.BGMaterialColor = xivps3::utils::bparse::byteswap( sceneSettings.BGMaterialColor );
    sceneSettings.BGSkyVisibility = xivps3::utils::bparse::byteswap( sceneSettings.BGSkyVisibility );
    sceneSettings.CameraFarClipDistance = xivps3::utils::bparse::byteswap( sceneSettings.CameraFarClipDistance );
    sceneSettings.ConstantTime = xivps3::utils::bparse::byteswap( sceneSettings.ConstantTime );
    sceneSettings.EnvSetAttrReference_Count = xivps3::utils::bparse::byteswap( sceneSettings.EnvSetAttrReference_Count );
    sceneSettings.EnvSetAttrReferences = xivps3::utils::bparse::byteswap( sceneSettings.EnvSetAttrReferences );
    sceneSettings.LevelWeatherTable = xivps3::utils::bparse::byteswap( sceneSettings.LevelWeatherTable );
    sceneSettings.LightClipAABBPath = xivps3::utils::bparse::byteswap( sceneSettings.LightClipAABBPath );
    sceneSettings.MainLightOrbitClamp = xivps3::utils::bparse::byteswap( sceneSettings.MainLightOrbitClamp );
    sceneSettings.ShadowDistanceFade = xivps3::utils::bparse::byteswap( sceneSettings.ShadowDistanceFade );
    sceneSettings.ShadowFarDistance = xivps3::utils::bparse::byteswap( sceneSettings.ShadowFarDistance );
    sceneSettings.SkyVisibilityPath = xivps3::utils::bparse::byteswap( sceneSettings.SkyVisibilityPath );
    sceneSettings.SunriseAngle = xivps3::utils::bparse::byteswap( sceneSettings.SunriseAngle );
    sceneSettings.TerrainAssetPath = xivps3::utils::bparse::byteswap( sceneSettings.TerrainAssetPath );
  }

  void convertToLEBytes( SceneChunk& sceneChunk ) const
  {
    sceneChunk._SGClockSettings = xivps3::utils::bparse::byteswap( sceneChunk._SGClockSettings );
    sceneChunk._SGDoorSettings = xivps3::utils::bparse::byteswap( sceneChunk._SGDoorSettings );
    sceneChunk._SGRandomTimelineSettings = xivps3::utils::bparse::byteswap( sceneChunk._SGRandomTimelineSettings );
    sceneChunk._SGRotationSettings = xivps3::utils::bparse::byteswap( sceneChunk._SGRotationSettings );
    sceneChunk.HousingSetting = xivps3::utils::bparse::byteswap( sceneChunk.HousingSetting );
    sceneChunk.LayerGroup_Count = xivps3::utils::bparse::byteswap( sceneChunk.LayerGroup_Count );
    sceneChunk.LayerGroups = xivps3::utils::bparse::byteswap( sceneChunk.LayerGroups );
    sceneChunk.LayerSetFold = xivps3::utils::bparse::byteswap( sceneChunk.LayerSetFold );
    sceneChunk.LGBAssetPathCount = xivps3::utils::bparse::byteswap( sceneChunk.LGBAssetPathCount );
    sceneChunk.LGBAssetPaths = xivps3::utils::bparse::byteswap( sceneChunk.LGBAssetPaths );
    sceneChunk.Settings = xivps3::utils::bparse::byteswap( sceneChunk.Settings );
    sceneChunk.SGSetting = xivps3::utils::bparse::byteswap( sceneChunk.SGSetting );
    sceneChunk.SGTimelineFold = xivps3::utils::bparse::byteswap( sceneChunk.SGTimelineFold );
  };
};

#endif