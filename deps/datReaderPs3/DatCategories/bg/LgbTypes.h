#ifndef SAPPHIRE_LGBTYPES_H
#define SAPPHIRE_LGBTYPES_H

#include "vec3.h"

enum class LgbEntryType : uint32_t
{
  BgParts = 1,
  Attribute = 2,
  Light = 3,
  Vfx = 4,
  PositionMarker = 5,
  SharedGroup = 6,// secondary variable is set to 2
  Sound = 7,
  EventNpc = 8,
  BattleNpc = 9,
  RoutePath = 10,
  Character = 11,
  Aetheryte = 12,
  EnvSpace = 13,
  Gathering = 14,
  SharedGroup15 = 15,// secondary variable is set to 13
  Treasure = 16,
  Clip = 0x11,
  ClipCtrlPoint = 0x12,
  ClipCamera = 0x13,
  ClipLight = 0x14,
  ClipReserve00 = 0x15,
  ClipReserve01 = 0x16,
  ClipReserve02 = 0x17,
  ClipReserve03 = 0x18,
  ClipReserve04 = 0x19,
  ClipReserve05 = 0x1A,
  ClipReserve06 = 0x1B,
  ClipReserve07 = 0x1C,
  ClipReserve08 = 0x1D,
  ClipReserve09 = 0x1E,
  ClipReserve10 = 0x1F,
  ClipReserve11 = 0x20,
  ClipReserve12 = 0x21,
  ClipReserve13 = 0x22,
  ClipReserve14 = 0x23,
  CutAssetOnlySelectable = 0x24,
  Player = 37,
  Monster = 38,
  Weapon = 39,
  PopRange = 40,
  ExitRange = 41,
  LVB = 42,
  MapRange = 43,
  NaviMeshRange = 44,
  EventObject = 45,
  DemiHuman = 46,
  EnvLocation = 47,
  ControlPoint = 48,
  EventRange = 49,
  RestBonusRange = 50,
  QuestMarker = 51,
  TimeLine = 52,
  ObjectBehaviorSet = 53,
  Movie = 54,
  ScenarioEXD = 55,
  ScenarioText = 56,
  CollisionBox = 57,
  DoorRange = 58,
  LineVfx = 59,
  SoundEnvSet = 60,
  CutActionTimeline = 61,
  CharaScene = 62,
  CutAction = 63,
  EquipPreset = 64,
  ClientPath = 65,
  ServerPath = 66,
  GimmickRange = 67,
  TargetMarker = 68,
  ChairMarker = 69,
  ClickableRange = 70,
  PrefetchRange = 71,
  FateRange = 72,
  PartyMember = 73,
  KeepRange = 74,
  SphereCastRange = 75,
  IndoorObject = 76,
  OutdoorObject = 77,
  EditGroup = 78,
  StableChocobo = 79
};

enum PopType : uint32_t
{
  PopTypePC = 0x1,
  PopTypeNPC = 0x2,
  PopTypeBNPC = 0x2,
  PopTypeContent = 0x3,
};

struct Transformation
{
  vec3 translation;
  vec3 rotation;
  vec3 scale;
};

struct RelativePositions_
{
  int32_t Pos;
  int32_t PosCount;
};

struct InstanceObject
{
  LgbEntryType type;
  uint32_t instanceId;
  uint32_t nameOffset;
  Transformation transform;
};

struct GameInstanceObject : public InstanceObject
{
  uint32_t BaseId;
};

struct NPCInstanceObject : public GameInstanceObject
{
  uint32_t PopWeather;
  uint8_t PopTimeStart;
  uint8_t PopTimeEnd;
  uint8_t Padding00[2];
  uint32_t MoveAI;
  uint8_t WanderingRange;
  uint8_t Route;
  uint16_t EventGroup;
  uint32_t Reserved1;
  uint32_t Reserved2;
};


struct BNpcBaseData
{
  uint16_t TerritoryRange;
  uint8_t Sense[2];
  uint8_t SenseRange[2];
};


struct BNPCInstanceObject : public NPCInstanceObject
{
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
  RelativePositions_ RelativePositions;
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
};

enum eModelConfigCollisionType : int32_t
{
  COLLISION_ATTRIBUTE_TYPE_None = 0x0,
  COLLISION_ATTRIBUTE_TYPE_Replace = 0x1,
  COLLISION_ATTRIBUTE_TYPE_Box = 0x2,
};

struct BgPartsData : public InstanceObject
{
  int32_t AssetPath;
  int32_t CollisionAssetPath;
  eModelConfigCollisionType CollisionType;
  uint32_t AttributeMask;
  uint32_t Attribute;
  int32_t CollisionConfig;
  int8_t IsVisible;
  uint8_t RenderShadowEnabled;
  uint8_t RenderLightShadowEnabled;
  uint8_t Padding00[1];
  float RenderModelClipRange;
};



struct PopRangeData : public InstanceObject
{
  PopType popType;
  RelativePositions_ relativePositions;
  float innerRadiusRatio;
  uint8_t index;
  uint8_t padding00[3];
  uint32_t reserved;
};

enum eDoorState : int32_t
{
  Auto_0 = 0x1,
  Open = 0x2,
  Closed = 0x3,
};

enum eRotationState : int32_t
{
  Rounding = 0x1,
  Stopped = 0x2,
};

enum eTransformState : int32_t
{
  TransformStatePlay = 0x0,
  TransformStateStop = 0x1,
  TransformStateReplay = 0x2,
  TransformStateReset = 0x3,
};

enum eColorState : int32_t
{
  ColorStatePlay = 0x0,
  ColorStateStop = 0x1,
  ColorStateReplay = 0x2,
  ColorStateReset = 0x3,
};

struct SGData : public InstanceObject
{
  int32_t AssetPath;
  eDoorState InitialDoorState;
  int32_t OverriddenMembers;
  int32_t OverriddenMember_Count;
  eRotationState InitialRotationState;
  int8_t RandomTimelineAutoPlay;
  int8_t RandomTimelineLoopPlayback;
  int8_t IsCollisionControllableWithoutEObj;
  uint8_t Padding00[1];
  uint32_t BoundClientPathInstanceID;
  int32_t MovePathSettings;
  int8_t NotCreateNavimeshDoor;
  uint8_t Padding01[3];
  eTransformState InitialTransformState;
  eColorState InitialColorState;
};

struct ENpcData : public InstanceObject
{
  uint32_t enpcId;
  uint8_t unknown1[0x24];
};

struct EObjData : public InstanceObject
{
  uint32_t BaseId;
  uint32_t BoundInstanceID;
  uint32_t LinkedInstanceID;
  uint32_t Reserved1;
  uint32_t Reserved2;
};

enum TriggerBoxShape : uint32_t
{
  TriggerBoxShapeBox = 0x1,
  TriggerBoxShapeSphere = 0x2,
  TriggerBoxShapeCylinder = 0x3,
  TriggerBoxShapeBoard = 0x4,
  TriggerBoxShapeMesh = 0x5,
  TriggerBoxShapeBoardBothSides = 0x6,
};

struct TriggerBoxInstanceObject
{
  TriggerBoxShape triggerBoxShape;
  int16_t priority;
  int8_t enabled;
  uint8_t padding;
  uint32_t reserved;
};

struct ExitRangeData : public InstanceObject
{
  TriggerBoxInstanceObject triggerBoxType;
  uint32_t exitType;
  uint16_t zoneId;
  uint16_t destTerritoryType;
  int index;
  uint32_t destInstanceObjectId;
  uint32_t returnInstanceObjectId;
  float direction;
  uint32_t reserved;
};

struct PathControlPoint
{
  vec3 Translation;
  uint16_t PointID;
  int8_t Selected;
  uint8_t Padding00[1];
};

struct ServerPathData : public InstanceObject
{
    int32_t ControlPoints;
    int32_t ControlPoint_Count;
    uint32_t Reserved1;
    uint32_t Reserved2;
};

struct MapRangeData : public InstanceObject
{
  TriggerBoxInstanceObject triggerBoxType;
  uint32_t mapId;
  uint32_t placeNameBlock;
  uint32_t placeNameSpot;
  uint32_t bGM;
  uint32_t weather;
  uint32_t reserved;
  uint32_t reserved2;
  uint16_t reserved3;
  uint8_t housingBlockId;
  int8_t restBonusEffective;
  uint8_t discoveryIndex;
  int8_t mapEnabled;
  int8_t placeNameEnabled;
  int8_t discoveryEnabled;
  int8_t bGMEnabled;
  int8_t weatherEnabled;
  int8_t restBonusEnabled;
  int8_t bGMPlayZoneInOnly;
  int8_t liftEnabled;
  int8_t housingEnabled;
  uint16_t padding;
};

#endif //SAPPHIRE_LGBTYPES_H
