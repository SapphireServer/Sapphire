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
struct SGB_MODEL_ENTRY;
struct SGB_MODEL_HEADER;
struct SGB_GROUP;
struct SGB_GROUP_HEADER;


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

enum eTimelineCollisionState : __int32
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
  uint8_t Padding00[2];
  eTimelineCollisionState CollisionState;
  uint32_t Reserved[1];
};


struct SGB_GROUP_HEADER
{
  SGTimeline_t timeline;
};

struct SGB_GROUP1C_HEADER
{
  SgbDataType type;
  int32_t nameOffset;
  uint32_t unknown08;
  
  int32_t entryCount;
  uint32_t unknown14;
  int32_t modelFileOffset;
  vec3 unknownFloat3;
  vec3 unknownFloat3_2;
  int32_t stateOffset;
  int32_t modelFileOffset2;
  uint32_t unknown3;
  float unknown4;
  int32_t nameOffset2;
  vec3 unknownFloat3_3;
};

struct SGB_GROUP1C_ENTRY
{
  uint32_t unk;
  uint32_t unk2;
  int32_t nameOffset;
  uint32_t index;
  uint32_t unk3;
  int32_t modelFileOffset;
};

struct SGB_GROUP_ENTRY
{
public:
  char* m_buf;
  uint32_t m_offset;

  SGB_GROUP_ENTRY()
  {
    m_buf = nullptr;
    m_offset = 0;
  };

  SGB_GROUP_ENTRY( char* buf, uint32_t offset )
  {
    m_buf = buf;
    m_offset = offset;
  };

  virtual ~SGB_GROUP_ENTRY()
  {
  };
};

struct SGB_ENTRY_HEADER
{
  SgbGroupEntryType type;
  uint32_t unknown2;
  int32_t nameOffset;
  vec3 translation;
  vec3 rotation;
  vec3 scale;
};

struct SGB_MODEL_HEADER :
  public SGB_ENTRY_HEADER
{
  int32_t modelFileOffset;
  int32_t collisionFileOffset;
};

struct SGB_MODEL_ENTRY :
  public SGB_GROUP_ENTRY
{
  SGB_MODEL_HEADER header;
  SgbGroupEntryType type;
  std::string name;
  std::string modelFileName;
  std::string collisionFileName;

  SGB_MODEL_ENTRY( char* buf, uint32_t offset, SgbGroupEntryType type )
  {
    this->type = type;
    header = *reinterpret_cast< SGB_MODEL_HEADER* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );
    modelFileName = std::string( buf + offset + header.modelFileOffset );
    collisionFileName = std::string( buf + offset + header.collisionFileOffset );
  }
};

struct SGB_GROUP
{
  SGB_GROUP_HEADER header;
  std::string name;
  SGB_FILE* parent;
  std::vector< std::shared_ptr< SGB_GROUP_ENTRY > > entries;

  SGB_GROUP( char* buf, SGB_FILE* file, std::set< std::string >* offset1cObjects, uint32_t fileSize, uint32_t offset, bool isOffset1C = false )
  {
    parent = file;


    if( isOffset1C )
    {
      auto header1c = *reinterpret_cast< SGB_GROUP1C_HEADER* >( buf + offset );

      auto entriesOffset = offset + sizeof( header1c );

      auto entryCount = header1c.entryCount;
      for( auto i = 0; i < entryCount; ++i )
      {
        auto entryOffset = entriesOffset + ( i * 24 );
        auto entry = *reinterpret_cast< SGB_GROUP1C_ENTRY* >( buf + entryOffset );

        std::string entryModelFile( buf + entryOffset + entry.modelFileOffset + 9 );
        if( entryModelFile.find( ".sgb" ) != std::string::npos )
        {
          offset1cObjects->emplace( entryModelFile );
        }
      }
      return;
    }
    auto entriesOffset = offset + sizeof( header );

  /*  header = *reinterpret_cast< SGB_GROUP_HEADER* >( buf + offset );
    name = std::string( buf + offset + header.nameOffset );

    for( auto i = 0; i < header.entryCount; ++i )
    {
      auto entryOffset = entriesOffset + *reinterpret_cast< uint32_t* >( buf + ( entriesOffset + ( i * 4 ) ) );
      if( entryOffset > fileSize )
        throw std::runtime_error( "SGB_GROUP entry offset was larger than SGB file size!" );
      auto type = *reinterpret_cast< uint32_t* >( buf + entryOffset );
      if( type == SgbGroupEntryType::Model || type == SgbGroupEntryType::Gimmick )
      {
        entries.push_back( std::make_shared< SGB_MODEL_ENTRY >( buf, entryOffset, ( SgbGroupEntryType )type ) );
      }
      else
      {
        // std::cout << "\t\tUnknown SGB entry! Group: " << name << " type: " << type << " index: " << i << " entryOffset: " << entryOffset << "\n";
      }
    }*/
  }
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
  int32_t Reserved1[4];
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
  uint8_t Padding00[1];
  float ConstantTime;
  int32_t LevelWeatherTable;
  int32_t Reserved1[5];
};


struct SGTimelineFolder_t
{
  int32_t SGTimelines;
  int32_t SGTimeline_Count;
};


struct SGB_HEADER
{
  char magic[4];     // SGB1
  uint32_t fileSize;
  uint32_t unknown1;
  char ChunkID[4];
  int ChunkSize;
};

struct SGB_FILE
{
  SGB_HEADER header;
  Scene_t scene;
  SceneSettings_t sceneSettings;
  LayerGroup layerGroup;
  SGTimelineFolder_t sgTimelineFolder;
  SGTimeline_t timeline;
  std::set< std::string > stateEntries;
  std::vector< Layer > layers;

  std::unordered_map< uint32_t, std::vector< std::shared_ptr< InstanceObjectEntry > > > layerInstanceObjects;

  SGB_FILE()
  {
    memset( &header, 0, sizeof( header ) );
  }

  SGB_FILE( char* buf )
  {
    constexpr int baseOffset = 0x14;
    header = *reinterpret_cast< SGB_HEADER* >( buf );
    scene = *reinterpret_cast< Scene_t* >( buf + sizeof( SGB_HEADER ) );
    sgTimelineFolder = *reinterpret_cast< SGTimelineFolder_t* >( buf + sizeof( SGB_HEADER ) + scene.SGTimelineFolder );
    sceneSettings = *reinterpret_cast< SceneSettings_t * >( buf + sizeof( SGB_HEADER ) + scene.Settings );
    layerGroup = *reinterpret_cast< LayerGroup* >( buf + sizeof( SGB_HEADER ) + scene.LayerGroups );

    int layerOffset = sizeof( SGB_HEADER ) + scene.LayerGroups + layerGroup.Layers;

    layers.resize( layerGroup.Layer_Count );
    std::vector< int > layerOffsets;
    layerOffsets.resize( layerGroup.Layer_Count );
    memcpy( layerOffsets.data(), buf + sizeof( SGB_HEADER ) + scene.LayerGroups + sizeof( LayerGroup ), sizeof( int ) * layerGroup.Layer_Count  );

    for( auto i = 0; i < layerGroup.Layer_Count; ++i )
    {
      auto& layer = layers[ i ];
      layer = *reinterpret_cast< Layer* >( buf + layerOffset + layerOffsets[ i ]  );
      std::string name = std::string( buf + sizeof( SGB_HEADER ) + scene.LayerGroups + sizeof(LayerGroup) + layers[i].Name );



      const auto entriesOffset = layerOffset + layer.InstanceObjects + layerOffsets[ i ];
      for( int ioIdx = 0; ioIdx < layer.InstanceObject_Count; ++ioIdx )
      {
        const auto entryOffset = entriesOffset + *reinterpret_cast< int32_t* >( buf + ( entriesOffset  ) );

        try
        {
          const auto type = *reinterpret_cast<eAssetType*>( buf + entryOffset );
          switch( type )
          {
            case BG:
            {
              auto entry = std::make_shared< BGEntry >( buf, entryOffset );
              layerInstanceObjects[ layer.LayerID ].push_back( entry );
              break;
            }

            case SharedGroup:
            {
              auto entry = std::make_shared< SharedGroupEntry >( buf, entryOffset );
              layerInstanceObjects[ layer.LayerID ].push_back( entry );
              break;
            }

            default:
              break;

          }
        }
        catch( std::exception& e )
        {
          std::cout << ( std::string( e.what() ) + "\n" );
        }
      }
    }

    if( sgTimelineFolder.SGTimeline_Count != 0 )
      timeline = *reinterpret_cast< SGTimeline_t* >( buf + sizeof( SGB_HEADER ) + scene.SGTimelineFolder + sgTimelineFolder.SGTimelines );

    if( strncmp( &header.magic[ 0 ], "SGB1", 4 ) != 0 || strncmp( &header.ChunkID[ 0 ], "SCN1", 4 ) != 0 )
      throw std::runtime_error( "Unable to load SGB File!" );

    try
    {
    //  auto group = SGB_GROUP( buf, this, &stateEntries, header.fileSize, baseOffset + header.sgTimelineFolder.SGTimelines );
    //  entries.push_back( group );
    //  timeline = *reinterpret_cast< SGTimeline_t * >( buf + sizeof( SGB_HEADER ) + header.sgTimelineFolder.SGTimelines  );

    }
    catch( std::exception& e )
    {
      std::cout << ( std::string( e.what() ) + "\n" );
    }
  };
};


#endif // !_SGB_H
