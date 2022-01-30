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
  Gimmick = 6,
  SharedGroup6 = 6,// secondary variable is set to 2
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

struct InstanceObject
{
  LgbEntryType type;
  uint32_t instanceId;
  uint32_t nameOffset;
  Transformation transform;
};

struct BgPartsData : public InstanceObject
{
  uint32_t modelFileOffset;
  uint32_t collisionFileOffset;
  uint32_t unknown4;
  uint32_t unknown5;
  uint32_t unknown6;
  uint32_t unknown7;
  uint32_t unknown8;
  uint32_t unknown9;
};

struct RelativePositions
{
  int32_t Pos;
  int32_t PosCount;
};

struct PopRangeData : public InstanceObject
{
  PopType popType;
  RelativePositions relativePositions;
  float innerRadiusRatio;
  uint8_t index;
  uint8_t padding00[3];
  uint32_t reserved;
};

struct GimmickData : public InstanceObject
{
  uint32_t gimmickFileOffset;
  char unknownBytes[100];
};

struct ENpcData : public InstanceObject
{
  uint32_t enpcId;
  uint8_t unknown1[0x24];
};

struct EObjData : public InstanceObject
{
  uint32_t eobjId;
  uint32_t levelHierachyId;
  uint8_t unknown1[136];
};

enum TriggerBoxShape : int32_t
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

struct EventRangeData : public InstanceObject
{
  TriggerBoxInstanceObject triggerBox;
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
