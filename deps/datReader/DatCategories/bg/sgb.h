#ifndef _SGB_H
#define _SGB_H

#include <cstring>
#include <memory>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "vec3.h"
#include "DatCategories/Layer.h"
#include "DatCategories/InstanceObjectParser.h"
#include <set>
#include <unordered_map>
// garbage to skip model loading
extern bool noObj;

//
// ported from https://github.com/ufx/SaintCoinach/blob/master/SaintCoinach/Graphics/Sgb/SgbDataType.cs

struct SGB_FILE;
struct SGB_HEADER;


enum SgbDataType :
    uint32_t
{
  Unknown0008 = 0x0008,
  Group = 0x0100,
};

enum SgbGroupEntryType :
    uint32_t
{
  Model = 0x01,
  Gimmick = 0x06,
};

enum eTimelineCollisionState : int32_t
{
  NoChange = 0x0,
  On = 0x1,
  Off = 0x2,
};

struct SGTimeline_t
{
  uint32_t MemberID;
  int32_t Name;
  int32_t Binders;
  int32_t Binder_Count;
  int32_t BinaryAssetPath;
  int32_t Binary;
  int32_t Binary_Count;
  uint32_t TimelineID;
  int8_t AutoPlay;
  int8_t LoopPlayback;
  uint8_t Padding00[ 2 ];
  eTimelineCollisionState CollisionState;
  uint32_t Reserved[ 1 ];
};


struct Scene_t
{
  int32_t LayerGroups;
  int32_t LayerGroup_Count;
  int32_t Settings;
  int32_t LayerSetFolder;
  int32_t SGTimelineFolder;
  int32_t LGBAssetPaths;
  int32_t LGBAssetPath_Count;
  int32_t _SGDoorSettings;
  int32_t SGSettings;
  int32_t _SGRotationSettings;
  int32_t _SGRandomTimelineSettings;
  int32_t HousingSettings;
  int32_t _SGClockSettings;
  int32_t Reserved1[ 4 ];
};

struct SceneSettings_t
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
  uint8_t Padding00[ 1 ];
  float ConstantTime;
  int32_t LevelWeatherTable;
  int32_t Reserved1[ 5 ];
};


struct SGTimelineFolder_t
{
  int32_t SGTimelines;
  int32_t SGTimeline_Count;
};


struct SGB_HEADER
{
  char magic[ 4 ]; // SGB1
  uint32_t fileSize;
  uint32_t unknown1;
  char ChunkID[ 4 ];
  int ChunkSize;
};

struct SGB_FILE
{
  SGB_HEADER header;
  Scene_t scene;
  SceneSettings_t sceneSettings;
  LayerGroup layerGroup;
  SGTimelineFolder_t sgTimelineFolder;
  std::vector< SGTimeline_t > timelines;
  std::vector< std::string > timelineNames;
  std::vector< Layer > layers;

  std::unordered_map< uint32_t, std::vector< std::shared_ptr< InstanceObjectEntry > > > layerInstanceObjects;

  SGB_FILE()
  {
    memset( &header, 0, sizeof( header ) );
  }

  SGB_FILE( char *buf )
  {
    constexpr int baseOffset = 0x14;
    header = *reinterpret_cast< SGB_HEADER * >( buf );
    scene = *reinterpret_cast< Scene_t * >( buf + sizeof( SGB_HEADER ) );
    sgTimelineFolder = *reinterpret_cast< SGTimelineFolder_t * >( buf + sizeof( SGB_HEADER ) + scene.SGTimelineFolder );
    sceneSettings = *reinterpret_cast< SceneSettings_t * >( buf + sizeof( SGB_HEADER ) + scene.Settings );
    layerGroup = *reinterpret_cast< LayerGroup * >( buf + sizeof( SGB_HEADER ) + scene.LayerGroups );

    int layerOffset = sizeof( SGB_HEADER ) + scene.LayerGroups + layerGroup.Layers;

    layers.resize( layerGroup.Layer_Count );
    std::vector< int > layerOffsets;
    layerOffsets.resize( layerGroup.Layer_Count );
    memcpy( layerOffsets.data(), buf + sizeof( SGB_HEADER ) + scene.LayerGroups + sizeof( LayerGroup ),
            sizeof( int ) * layerGroup.Layer_Count );

    for( auto i = 0; i < layerGroup.Layer_Count; ++i )
    {
      auto& layer = layers[ i ];
      layer = *reinterpret_cast< Layer * >( buf + layerOffset + layerOffsets[ i ] );
      std::string name = std::string(
        buf + sizeof( SGB_HEADER ) + scene.LayerGroups + sizeof( LayerGroup ) + layers[ i ].Name );


      const auto entriesOffset = layerOffset + layer.InstanceObjects + layerOffsets[ i ];
      for( int ioIdx = 0; ioIdx < layer.InstanceObject_Count; ++ioIdx )
      {
        const auto entryOffset = entriesOffset + *reinterpret_cast< int32_t * >( buf + ( entriesOffset + ioIdx * 4 ) );

        try
        {
          const auto type = *reinterpret_cast< eAssetType * >( buf + entryOffset );
          switch( type )
          {
            case BG:
            {
              auto entry = std::make_shared< BGEntry >( buf, entryOffset );
              layerInstanceObjects[ layer.LayerID ].push_back( entry );
              break;
            }


              case eAssetType::SharedGroup:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< SharedGroupEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::EventNPC:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< EventNPCEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::EventObject:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< EventObjectEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::ExitRange:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< ExitRangeEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::EventRange:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< EventRangeEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::PopRange:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< PopRangeEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::MapRange:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< MapRangeEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::BattleNPC:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< BattleNPCEntry >( buf, entryOffset ) );
                break;
              }
              case eAssetType::CollisionBox:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< CollisionBoxEntry >( buf, entryOffset ) );
                break;
              }
              default:
              {
                layerInstanceObjects[ layer.LayerID ].emplace_back( std::make_shared< InstanceObjectEntry >( buf, entryOffset ) );
                break;
              }

          }
        } catch( std::exception& e )
        {
          std::cout << ( std::string( e.what() ) + "\n" );
        }
      }
    }


    for( auto i = 0; i < sgTimelineFolder.SGTimeline_Count; ++i )
    {
      timelines.push_back(
        *reinterpret_cast< SGTimeline_t * >( buf + sizeof( SGB_HEADER ) + scene.SGTimelineFolder + sgTimelineFolder.
                                             SGTimelines + i * sizeof( SGTimeline_t ) ) );
      timelineNames.emplace_back(
        buf + sizeof( SGB_HEADER ) + scene.SGTimelineFolder + sgTimelineFolder.SGTimelines + i * sizeof( SGTimeline_t )
        + timelines.back().Name );
    }

    if( strncmp( &header.magic[ 0 ], "SGB1", 4 ) != 0 || strncmp( &header.ChunkID[ 0 ], "SCN1", 4 ) != 0 )
      throw std::runtime_error( "Unable to load SGB File!" );

  };
};


#endif // !_SGB_H
