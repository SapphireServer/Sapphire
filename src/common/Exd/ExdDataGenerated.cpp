#include "ExdDataGenerated.h"
#include <memory>

Sapphire::Data::Achievement::Achievement( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AchievementDat.get_row( row_id );
  achievementCategory = exdData->getField< uint8_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
  description = exdData->getField< std::string >( row, 2 );
  points = exdData->getField< uint8_t >( row, 3 );
  title = exdData->getField< uint16_t >( row, 4 );
  item = exdData->getField< uint32_t >( row, 5 );
  icon = exdData->getField< uint16_t >( row, 6 );
  type = exdData->getField< uint8_t >( row, 8 );
  key = exdData->getField< int32_t >( row, 9 );
  data.push_back( exdData->getField< int32_t >( row, 10 ) );
  data.push_back( exdData->getField< int32_t >( row, 11 ) );
  data.push_back( exdData->getField< int32_t >( row, 12 ) );
  data.push_back( exdData->getField< int32_t >( row, 13 ) );
  data.push_back( exdData->getField< int32_t >( row, 14 ) );
  data.push_back( exdData->getField< int32_t >( row, 15 ) );
  data.push_back( exdData->getField< int32_t >( row, 16 ) );
  data.push_back( exdData->getField< int32_t >( row, 17 ) );
  order = exdData->getField< uint16_t >( row, 18 );
  achievementHideCondition = exdData->getField< uint8_t >( row, 20 );
}

Sapphire::Data::AchievementCategory::AchievementCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AchievementCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  achievementKind = exdData->getField< uint8_t >( row, 1 );
  showComplete = exdData->getField< bool >( row, 2 );
  hideCategory = exdData->getField< bool >( row, 3 );
  order = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::AchievementHideCondition::AchievementHideCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AchievementHideConditionDat.get_row( row_id );
  hideAchievement = exdData->getField< bool >( row, 0 );
  hideName = exdData->getField< bool >( row, 1 );
  hideConditions = exdData->getField< bool >( row, 2 );
}

Sapphire::Data::AchievementKind::AchievementKind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AchievementKindDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  order = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::Action::Action( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< uint16_t >( row, 2 );
  actionCategory = exdData->getField< uint8_t >( row, 3 );
  animationStart = exdData->getField< uint8_t >( row, 5 );
  vFX = exdData->getField< uint8_t >( row, 6 );
  animationEnd = exdData->getField< int16_t >( row, 7 );
  actionTimelineHit = exdData->getField< uint16_t >( row, 8 );
  classJob = exdData->getField< int8_t >( row, 10 );
  behaviourType = exdData->getField< uint8_t >( row, 11 );
  classJobLevel = exdData->getField< uint8_t >( row, 12 );
  isRoleAction = exdData->getField< bool >( row, 13 );
  range = exdData->getField< int8_t >( row, 14 );
  canTargetSelf = exdData->getField< bool >( row, 15 );
  canTargetParty = exdData->getField< bool >( row, 16 );
  canTargetFriendly = exdData->getField< bool >( row, 17 );
  canTargetHostile = exdData->getField< bool >( row, 18 );
  targetArea = exdData->getField< bool >( row, 21 );
  canTargetDead = exdData->getField< bool >( row, 25 );
  castType = exdData->getField< uint8_t >( row, 27 );
  effectRange = exdData->getField< uint8_t >( row, 28 );
  xAxisModifier = exdData->getField< uint8_t >( row, 29 );
  primaryCostType = exdData->getField< uint8_t >( row, 31 );
  primaryCostValue = exdData->getField< uint16_t >( row, 32 );
  secondaryCostType = exdData->getField< uint8_t >( row, 33 );
  secondaryCostValue = exdData->getField< uint16_t >( row, 34 );
  actionCombo = exdData->getField< uint16_t >( row, 35 );
  preservesCombo = exdData->getField< bool >( row, 36 );
  cast100ms = exdData->getField< uint16_t >( row, 37 );
  recast100ms = exdData->getField< uint16_t >( row, 38 );
  cooldownGroup = exdData->getField< uint8_t >( row, 39 );
  maxCharges = exdData->getField< uint8_t >( row, 41 );
  attackType = exdData->getField< int8_t >( row, 42 );
  aspect = exdData->getField< uint8_t >( row, 43 );
  actionProcStatus = exdData->getField< uint8_t >( row, 44 );
  statusGainSelf = exdData->getField< uint16_t >( row, 46 );
  unlockLink = exdData->getField< uint32_t >( row, 47 );
  classJobCategory = exdData->getField< uint8_t >( row, 48 );
  affectsPosition = exdData->getField< bool >( row, 51 );
  omen = exdData->getField< uint16_t >( row, 52 );
  isPvP = exdData->getField< bool >( row, 53 );
  isPlayerAction = exdData->getField< bool >( row, 65 );
}

Sapphire::Data::ActionCastTimeline::ActionCastTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionCastTimelineDat.get_row( row_id );
  name = exdData->getField< uint16_t >( row, 0 );
  vFX = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::ActionCastVFX::ActionCastVFX( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionCastVFXDat.get_row( row_id );
  vFX = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::ActionCategory::ActionCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ActionComboRoute::ActionComboRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionComboRouteDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  action.push_back( exdData->getField< uint16_t >( row, 2 ) );
  action.push_back( exdData->getField< uint16_t >( row, 3 ) );
  action.push_back( exdData->getField< uint16_t >( row, 4 ) );
  action.push_back( exdData->getField< uint16_t >( row, 5 ) );
}

Sapphire::Data::ActionIndirection::ActionIndirection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionIndirectionDat.get_row( row_id );
  name = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::ActionParam::ActionParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionParamDat.get_row( row_id );
  name = exdData->getField< int16_t >( row, 0 );
}

Sapphire::Data::ActionProcStatus::ActionProcStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionProcStatusDat.get_row( row_id );
  status = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::ActionTimeline::ActionTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionTimelineDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  priority = exdData->getField< uint8_t >( row, 1 );
  pause = exdData->getField< bool >( row, 2 );
  stance = exdData->getField< uint8_t >( row, 3 );
  slot = exdData->getField< uint8_t >( row, 4 );
  lookAtMode = exdData->getField< uint8_t >( row, 5 );
  key = exdData->getField< std::string >( row, 6 );
  actionTimelineIDMode = exdData->getField< uint8_t >( row, 7 );
  weaponTimeline = exdData->getField< uint8_t >( row, 8 );
  loadType = exdData->getField< uint8_t >( row, 9 );
  startAttach = exdData->getField< uint8_t >( row, 10 );
  residentPap = exdData->getField< uint8_t >( row, 11 );
  resident = exdData->getField< bool >( row, 12 );
  killUpper = exdData->getField< uint16_t >( row, 13 );
  isMotionCanceledByMoving = exdData->getField< bool >( row, 14 );
  isLoop = exdData->getField< uint8_t >( row, 16 );
}

Sapphire::Data::ActionTimelineMove::ActionTimelineMove( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionTimelineMoveDat.get_row( row_id );
}

Sapphire::Data::ActionTimelineReplace::ActionTimelineReplace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionTimelineReplaceDat.get_row( row_id );
  old = exdData->getField< uint16_t >( row, 0 );
  _new = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::ActionTransient::ActionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActionTransientDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ActivityFeedButtons::ActivityFeedButtons( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActivityFeedButtonsDat.get_row( row_id );
  bannerURL = exdData->getField< std::string >( row, 1 );
  description = exdData->getField< std::string >( row, 2 );
  language = exdData->getField< std::string >( row, 3 );
  pictureURL = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::ActivityFeedCaptions::ActivityFeedCaptions( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActivityFeedCaptionsDat.get_row( row_id );
  jA = exdData->getField< std::string >( row, 0 );
  eN = exdData->getField< std::string >( row, 1 );
  dE = exdData->getField< std::string >( row, 2 );
  fR = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::ActivityFeedGroupCaptions::ActivityFeedGroupCaptions( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActivityFeedGroupCaptionsDat.get_row( row_id );
  jA = exdData->getField< std::string >( row, 0 );
  eN = exdData->getField< std::string >( row, 1 );
  dE = exdData->getField< std::string >( row, 2 );
  fR = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::ActivityFeedImages::ActivityFeedImages( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ActivityFeedImagesDat.get_row( row_id );
  expansionImage = exdData->getField< std::string >( row, 0 );
  activityFeedJA = exdData->getField< std::string >( row, 1 );
  activityFeedEN = exdData->getField< std::string >( row, 2 );
  activityFeedDE = exdData->getField< std::string >( row, 3 );
  activityFeedFR = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::Addon::Addon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AddonDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Adventure::Adventure( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AdventureDat.get_row( row_id );
  level = exdData->getField< int32_t >( row, 0 );
  minLevel = exdData->getField< int32_t >( row, 1 );
  maxLevel = exdData->getField< uint8_t >( row, 2 );
  emote = exdData->getField< uint16_t >( row, 3 );
  minTime = exdData->getField< uint16_t >( row, 4 );
  maxTime = exdData->getField< uint16_t >( row, 5 );
  placeName = exdData->getField< int32_t >( row, 6 );
  iconList = exdData->getField< int32_t >( row, 7 );
  iconDiscovered = exdData->getField< int32_t >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
  impression = exdData->getField< std::string >( row, 10 );
  description = exdData->getField< std::string >( row, 11 );
  iconUndiscovered = exdData->getField< int32_t >( row, 12 );
  isInitial = exdData->getField< bool >( row, 13 );
}

Sapphire::Data::AdventureExPhase::AdventureExPhase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AdventureExPhaseDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
  adventureBegin = exdData->getField< uint32_t >( row, 1 );
  adventureEnd = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::AetherCurrent::AetherCurrent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AetherCurrentDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::AetherCurrentCompFlgSet::AetherCurrentCompFlgSet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AetherCurrentCompFlgSetDat.get_row( row_id );
  territory = exdData->getField< int32_t >( row, 0 );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 2 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 3 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 4 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 5 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 6 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 7 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 8 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 9 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 10 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 11 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 12 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 13 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 14 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 15 ) );
  aetherCurrent.push_back( exdData->getField< int32_t >( row, 16 ) );
}

Sapphire::Data::AetherialWheel::AetherialWheel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AetherialWheelDat.get_row( row_id );
  itemUnprimed = exdData->getField< int32_t >( row, 0 );
  itemPrimed = exdData->getField< int32_t >( row, 1 );
  grade = exdData->getField< uint8_t >( row, 2 );
  hoursRequired = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::Aetheryte::Aetheryte( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AetheryteDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  placeName = exdData->getField< uint16_t >( row, 8 );
  aethernetName = exdData->getField< uint16_t >( row, 9 );
  territory = exdData->getField< uint16_t >( row, 10 );
  level.push_back( exdData->getField< uint32_t >( row, 11 ) );
  level.push_back( exdData->getField< uint32_t >( row, 12 ) );
  level.push_back( exdData->getField< uint32_t >( row, 13 ) );
  level.push_back( exdData->getField< uint32_t >( row, 14 ) );
  isAetheryte = exdData->getField< bool >( row, 15 );
  aethernetGroup = exdData->getField< uint8_t >( row, 17 );
  requiredQuest = exdData->getField< uint32_t >( row, 19 );
  map = exdData->getField< uint16_t >( row, 20 );
  aetherstreamX = exdData->getField< int16_t >( row, 21 );
  aetherstreamY = exdData->getField< int16_t >( row, 22 );
}

Sapphire::Data::AetheryteSystemDefine::AetheryteSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AetheryteSystemDefineDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
  defineValue = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::AirshipExplorationLevel::AirshipExplorationLevel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AirshipExplorationLevelDat.get_row( row_id );
  capacity = exdData->getField< uint16_t >( row, 0 );
  expToNext = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::AirshipExplorationLog::AirshipExplorationLog( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AirshipExplorationLogDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::AirshipExplorationParamType::AirshipExplorationParamType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AirshipExplorationParamTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::AirshipExplorationPart::AirshipExplorationPart( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AirshipExplorationPartDat.get_row( row_id );
  slot = exdData->getField< uint8_t >( row, 0 );
  rank = exdData->getField< uint8_t >( row, 1 );
  components = exdData->getField< uint8_t >( row, 2 );
  surveillance = exdData->getField< int16_t >( row, 3 );
  retrieval = exdData->getField< int16_t >( row, 4 );
  speed = exdData->getField< int16_t >( row, 5 );
  range = exdData->getField< int16_t >( row, 6 );
  favor = exdData->getField< int16_t >( row, 7 );
  _class = exdData->getField< uint16_t >( row, 8 );
  repairMaterials = exdData->getField< uint8_t >( row, 9 );
}

Sapphire::Data::AirshipExplorationPoint::AirshipExplorationPoint( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AirshipExplorationPointDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  nameShort = exdData->getField< std::string >( row, 1 );
  requiredLevel = exdData->getField< uint8_t >( row, 5 );
  requiredFuel = exdData->getField< uint16_t >( row, 6 );
  durationmin = exdData->getField< uint16_t >( row, 7 );
  requiredSurveillance = exdData->getField< uint8_t >( row, 10 );
  expReward = exdData->getField< uint32_t >( row, 13 );
}

Sapphire::Data::AnimationLOD::AnimationLOD( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimationLODDat.get_row( row_id );
  cameraDistance = exdData->getField< float >( row, 0 );
  sampleInterval = exdData->getField< float >( row, 1 );
  boneLOD = exdData->getField< int8_t >( row, 2 );
  animationEnable.push_back( exdData->getField< bool >( row, 3 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 4 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 5 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 6 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 7 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 8 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 9 ) );
  animationEnable.push_back( exdData->getField< bool >( row, 10 ) );
}

Sapphire::Data::AnimaWeapon5::AnimaWeapon5( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeapon5Dat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  secondaryStatTotal = exdData->getField< uint8_t >( row, 2 );
  parameter.push_back( exdData->getField< uint8_t >( row, 3 ) );
  parameter.push_back( exdData->getField< uint8_t >( row, 4 ) );
  parameter.push_back( exdData->getField< uint8_t >( row, 5 ) );
  parameter.push_back( exdData->getField< uint8_t >( row, 6 ) );
  parameter.push_back( exdData->getField< uint8_t >( row, 7 ) );
}

Sapphire::Data::AnimaWeapon5Param::AnimaWeapon5Param( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeapon5ParamDat.get_row( row_id );
  baseParam = exdData->getField< uint8_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::AnimaWeapon5PatternGroup::AnimaWeapon5PatternGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeapon5PatternGroupDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::AnimaWeapon5SpiritTalk::AnimaWeapon5SpiritTalk( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeapon5SpiritTalkDat.get_row( row_id, subRow );
  dialogue = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::AnimaWeapon5SpiritTalkParam::AnimaWeapon5SpiritTalkParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeapon5SpiritTalkParamDat.get_row( row_id );
  prologue = exdData->getField< std::string >( row, 0 );
  epilogue = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::AnimaWeapon5TradeItem::AnimaWeapon5TradeItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeapon5TradeItemDat.get_row( row_id );
  crystalSand = exdData->getField< uint32_t >( row, 1 );
  qty = exdData->getField< uint8_t >( row, 2 );
  category = exdData->getField< uint8_t >( row, 27 );
}

Sapphire::Data::AnimaWeaponFUITalk::AnimaWeaponFUITalk( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeaponFUITalkDat.get_row( row_id, subRow );
  dialogue = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::AnimaWeaponFUITalkParam::AnimaWeaponFUITalkParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeaponFUITalkParamDat.get_row( row_id );
  prologue = exdData->getField< std::string >( row, 0 );
  epilogue = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::AnimaWeaponIcon::AnimaWeaponIcon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeaponIconDat.get_row( row_id );
  hyperconductive = exdData->getField< int32_t >( row, 0 );
  reborn = exdData->getField< int32_t >( row, 1 );
  sharpened = exdData->getField< int32_t >( row, 2 );
  zodiac = exdData->getField< int32_t >( row, 3 );
  zodiacLux = exdData->getField< int32_t >( row, 4 );
}

Sapphire::Data::AnimaWeaponItem::AnimaWeaponItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AnimaWeaponItemDat.get_row( row_id );
  item.push_back( exdData->getField< uint32_t >( row, 0 ) );
  item.push_back( exdData->getField< uint32_t >( row, 1 ) );
  item.push_back( exdData->getField< uint32_t >( row, 2 ) );
  item.push_back( exdData->getField< uint32_t >( row, 3 ) );
  item.push_back( exdData->getField< uint32_t >( row, 4 ) );
  item.push_back( exdData->getField< uint32_t >( row, 5 ) );
  item.push_back( exdData->getField< uint32_t >( row, 6 ) );
  item.push_back( exdData->getField< uint32_t >( row, 7 ) );
  item.push_back( exdData->getField< uint32_t >( row, 8 ) );
  item.push_back( exdData->getField< uint32_t >( row, 9 ) );
  item.push_back( exdData->getField< uint32_t >( row, 10 ) );
  item.push_back( exdData->getField< uint32_t >( row, 11 ) );
  item.push_back( exdData->getField< uint32_t >( row, 12 ) );
  item.push_back( exdData->getField< uint32_t >( row, 13 ) );
}

Sapphire::Data::AozAction::AozAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AozActionDat.get_row( row_id );
  action = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::AozActionTransient::AozActionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AozActionTransientDat.get_row( row_id );
  number = exdData->getField< uint8_t >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  stats = exdData->getField< std::string >( row, 2 );
  description = exdData->getField< std::string >( row, 3 );
  locationKey = exdData->getField< uint8_t >( row, 4 );
  location = exdData->getField< uint16_t >( row, 5 );
  requiredForQuest = exdData->getField< uint32_t >( row, 6 );
  previousQuest = exdData->getField< uint32_t >( row, 7 );
  targetsEnemy = exdData->getField< bool >( row, 8 );
  targetsSelfOrAlly = exdData->getField< bool >( row, 9 );
  causeSlow = exdData->getField< bool >( row, 10 );
  causePetrify = exdData->getField< bool >( row, 11 );
  causeParalysis = exdData->getField< bool >( row, 12 );
  causeInterrupt = exdData->getField< bool >( row, 13 );
  causeBlind = exdData->getField< bool >( row, 14 );
  causeStun = exdData->getField< bool >( row, 15 );
  causeSleep = exdData->getField< bool >( row, 16 );
  causeBind = exdData->getField< bool >( row, 17 );
  causeHeavy = exdData->getField< bool >( row, 18 );
  causeDeath = exdData->getField< bool >( row, 19 );
}

Sapphire::Data::AOZArrangement::AOZArrangement( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AOZArrangementDat.get_row( row_id, subRow );
  aOZContentBriefingBNpc = exdData->getField< uint16_t >( row, 0 );
  position = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::AOZBoss::AOZBoss( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AOZBossDat.get_row( row_id );
  boss = exdData->getField< uint16_t >( row, 0 );
  position = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::AOZContent::AOZContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AOZContentDat.get_row( row_id );
  standardFinishTime = exdData->getField< uint16_t >( row, 0 );
  idealFinishTime = exdData->getField< uint16_t >( row, 1 );
  act1FightType = exdData->getField< uint8_t >( row, 2 );
  act1 = exdData->getField< uint16_t >( row, 3 );
  arenaType1 = exdData->getField< uint8_t >( row, 4 );
  act2FightType = exdData->getField< uint8_t >( row, 5 );
  act2 = exdData->getField< uint16_t >( row, 6 );
  arenaType2 = exdData->getField< uint8_t >( row, 7 );
  act3FightType = exdData->getField< uint8_t >( row, 8 );
  act3 = exdData->getField< uint16_t >( row, 9 );
  arenaType3 = exdData->getField< uint8_t >( row, 10 );
  contentEntry = exdData->getField< uint32_t >( row, 11 );
  order = exdData->getField< uint8_t >( row, 12 );
  gilReward = exdData->getField< uint16_t >( row, 13 );
  alliedSealsReward = exdData->getField< uint16_t >( row, 14 );
  tomestonesReward = exdData->getField< uint16_t >( row, 15 );
}

Sapphire::Data::AOZContentBriefingBNpc::AOZContentBriefingBNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AOZContentBriefingBNpcDat.get_row( row_id );
  bNpcName = exdData->getField< uint32_t >( row, 0 );
  targetSmall = exdData->getField< uint32_t >( row, 1 );
  targetLarge = exdData->getField< uint32_t >( row, 2 );
  hideStats = exdData->getField< bool >( row, 3 );
  endurance = exdData->getField< uint8_t >( row, 4 );
  fire = exdData->getField< uint8_t >( row, 5 );
  ice = exdData->getField< uint8_t >( row, 6 );
  wind = exdData->getField< uint8_t >( row, 7 );
  earth = exdData->getField< uint8_t >( row, 8 );
  thunder = exdData->getField< uint8_t >( row, 9 );
  water = exdData->getField< uint8_t >( row, 10 );
  slashing = exdData->getField< uint8_t >( row, 11 );
  piercing = exdData->getField< uint8_t >( row, 12 );
  blunt = exdData->getField< uint8_t >( row, 13 );
  magic = exdData->getField< uint8_t >( row, 14 );
  slowVuln = exdData->getField< bool >( row, 15 );
  petrificationVuln = exdData->getField< bool >( row, 16 );
  paralysisVuln = exdData->getField< bool >( row, 17 );
  interruptionVuln = exdData->getField< bool >( row, 18 );
  blindVuln = exdData->getField< bool >( row, 19 );
  stunVuln = exdData->getField< bool >( row, 20 );
  sleepVuln = exdData->getField< bool >( row, 21 );
  bindVuln = exdData->getField< bool >( row, 22 );
  heavyVuln = exdData->getField< bool >( row, 23 );
  flatOrDeathVuln = exdData->getField< bool >( row, 24 );
}

Sapphire::Data::AquariumFish::AquariumFish( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AquariumFishDat.get_row( row_id );
  aquariumWater = exdData->getField< uint8_t >( row, 0 );
  size = exdData->getField< uint8_t >( row, 1 );
  item = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::AquariumWater::AquariumWater( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AquariumWaterDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::ArrayEventHandler::ArrayEventHandler( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ArrayEventHandlerDat.get_row( row_id );
  data.push_back( exdData->getField< uint32_t >( row, 0 ) );
  data.push_back( exdData->getField< uint32_t >( row, 1 ) );
  data.push_back( exdData->getField< uint32_t >( row, 2 ) );
  data.push_back( exdData->getField< uint32_t >( row, 3 ) );
  data.push_back( exdData->getField< uint32_t >( row, 4 ) );
  data.push_back( exdData->getField< uint32_t >( row, 5 ) );
  data.push_back( exdData->getField< uint32_t >( row, 6 ) );
  data.push_back( exdData->getField< uint32_t >( row, 7 ) );
  data.push_back( exdData->getField< uint32_t >( row, 8 ) );
  data.push_back( exdData->getField< uint32_t >( row, 9 ) );
  data.push_back( exdData->getField< uint32_t >( row, 10 ) );
  data.push_back( exdData->getField< uint32_t >( row, 11 ) );
  data.push_back( exdData->getField< uint32_t >( row, 12 ) );
  data.push_back( exdData->getField< uint32_t >( row, 13 ) );
  data.push_back( exdData->getField< uint32_t >( row, 14 ) );
  data.push_back( exdData->getField< uint32_t >( row, 15 ) );
}

Sapphire::Data::AttackType::AttackType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_AttackTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::BacklightColor::BacklightColor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BacklightColorDat.get_row( row_id );
  color = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::Ballista::Ballista( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BallistaDat.get_row( row_id );
  bNPC = exdData->getField< uint16_t >( row, 0 );
  near = exdData->getField< int8_t >( row, 1 );
  far = exdData->getField< int8_t >( row, 2 );
  angle = exdData->getField< uint16_t >( row, 3 );
  bullet = exdData->getField< uint8_t >( row, 4 );
  action0 = exdData->getField< uint16_t >( row, 7 );
  action1 = exdData->getField< uint16_t >( row, 8 );
  action2 = exdData->getField< uint16_t >( row, 9 );
  action3 = exdData->getField< uint16_t >( row, 10 );
}

Sapphire::Data::Balloon::Balloon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BalloonDat.get_row( row_id );
  slowly = exdData->getField< bool >( row, 0 );
  dialogue = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::BaseParam::BaseParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BaseParamDat.get_row( row_id );
  packetIndex = exdData->getField< int8_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
  description = exdData->getField< std::string >( row, 2 );
  orderPriority = exdData->getField< uint8_t >( row, 3 );
  oneHWpn = exdData->getField< uint8_t >( row, 4 );
  oH = exdData->getField< uint8_t >( row, 5 );
  head = exdData->getField< uint8_t >( row, 6 );
  chest = exdData->getField< uint8_t >( row, 7 );
  hands = exdData->getField< uint8_t >( row, 8 );
  waist = exdData->getField< uint8_t >( row, 9 );
  legs = exdData->getField< uint8_t >( row, 10 );
  feet = exdData->getField< uint8_t >( row, 11 );
  earring = exdData->getField< uint8_t >( row, 12 );
  necklace = exdData->getField< uint8_t >( row, 13 );
  bracelet = exdData->getField< uint8_t >( row, 14 );
  ring = exdData->getField< uint8_t >( row, 15 );
  twoHWpn = exdData->getField< uint8_t >( row, 16 );
  underArmor = exdData->getField< uint8_t >( row, 17 );
  chestHead = exdData->getField< uint8_t >( row, 18 );
  chestHeadLegsFeet = exdData->getField< uint8_t >( row, 19 );
  legsFeet = exdData->getField< uint8_t >( row, 21 );
  headChestHandsLegsFeet = exdData->getField< uint8_t >( row, 22 );
  chestLegsGloves = exdData->getField< uint8_t >( row, 23 );
  chestLegsFeet = exdData->getField< uint8_t >( row, 24 );
  meldParam.push_back( exdData->getField< uint8_t >( row, 25 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 26 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 27 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 28 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 29 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 30 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 31 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 32 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 33 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 34 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 35 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 36 ) );
  meldParam.push_back( exdData->getField< uint8_t >( row, 37 ) );
}

Sapphire::Data::BattleLeve::BattleLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BattleLeveDat.get_row( row_id );
  time.push_back( exdData->getField< uint16_t >( row, 0 ) );
  time.push_back( exdData->getField< uint16_t >( row, 1 ) );
  time.push_back( exdData->getField< uint16_t >( row, 2 ) );
  time.push_back( exdData->getField< uint16_t >( row, 3 ) );
  time.push_back( exdData->getField< uint16_t >( row, 4 ) );
  time.push_back( exdData->getField< uint16_t >( row, 5 ) );
  time.push_back( exdData->getField< uint16_t >( row, 6 ) );
  time.push_back( exdData->getField< uint16_t >( row, 7 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 8 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 9 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 10 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 11 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 12 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 13 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 14 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 15 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 16 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 17 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 18 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 19 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 20 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 21 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 22 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 23 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 24 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 25 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 26 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 27 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 28 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 29 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 30 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 31 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 32 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 33 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 34 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 35 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 36 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 37 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 38 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 39 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 40 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 41 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 42 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 43 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 44 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 45 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 46 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 47 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 48 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 49 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 50 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 51 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 52 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 53 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 54 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 55 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 56 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 57 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 58 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 59 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 60 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 61 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 62 ) );
  toDoNumberInvolved.push_back( exdData->getField< uint32_t >( row, 63 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 168 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 169 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 170 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 171 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 172 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 173 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 174 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 175 ) );
  rule = exdData->getField< int32_t >( row, 176 );
  varient = exdData->getField< uint8_t >( row, 177 );
  objective0 = exdData->getField< uint16_t >( row, 178 );
  objective1 = exdData->getField< uint16_t >( row, 179 );
  objective2 = exdData->getField< uint16_t >( row, 180 );
  help0 = exdData->getField< uint16_t >( row, 181 );
  help1 = exdData->getField< uint16_t >( row, 182 );
}

Sapphire::Data::BattleLeveRule::BattleLeveRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BattleLeveRuleDat.get_row( row_id );
  rule = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::BeastRankBonus::BeastRankBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BeastRankBonusDat.get_row( row_id );
  neutral = exdData->getField< uint16_t >( row, 0 );
  recognized = exdData->getField< uint16_t >( row, 1 );
  friendly = exdData->getField< uint16_t >( row, 2 );
  trusted = exdData->getField< uint16_t >( row, 3 );
  respected = exdData->getField< uint16_t >( row, 4 );
  honored = exdData->getField< uint16_t >( row, 5 );
  sworn = exdData->getField< uint16_t >( row, 6 );
  alliedBloodsworn = exdData->getField< uint16_t >( row, 7 );
  item = exdData->getField< uint32_t >( row, 8 );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 9 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 10 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 11 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 12 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 13 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 14 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 15 ) );
  itemQuantity.push_back( exdData->getField< uint8_t >( row, 16 ) );
}

Sapphire::Data::BeastReputationRank::BeastReputationRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BeastReputationRankDat.get_row( row_id );
  requiredReputation = exdData->getField< uint16_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
  alliedNames = exdData->getField< std::string >( row, 2 );
  color = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::BeastTribe::BeastTribe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BeastTribeDat.get_row( row_id );
  minLevel = exdData->getField< uint8_t >( row, 1 );
  beastRankBonus = exdData->getField< uint8_t >( row, 2 );
  iconReputation = exdData->getField< uint32_t >( row, 3 );
  icon = exdData->getField< uint32_t >( row, 4 );
  maxRank = exdData->getField< uint8_t >( row, 5 );
  expansion = exdData->getField< uint8_t >( row, 6 );
  currencyItem = exdData->getField< uint32_t >( row, 7 );
  displayOrder = exdData->getField< uint8_t >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
  adjective = exdData->getField< int8_t >( row, 10 );
  plural = exdData->getField< std::string >( row, 11 );
  possessivePronoun = exdData->getField< int8_t >( row, 12 );
  startsWithVowel = exdData->getField< int8_t >( row, 13 );
  pronoun = exdData->getField< int8_t >( row, 14 );
  article = exdData->getField< int8_t >( row, 15 );
  dEF = exdData->getField< int8_t >( row, 16 );
  nameRelation = exdData->getField< std::string >( row, 17 );
}

Sapphire::Data::Behavior::Behavior( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BehaviorDat.get_row( row_id, subRow );
  condition0Target = exdData->getField< uint8_t >( row, 2 );
  condition0Type = exdData->getField< uint8_t >( row, 3 );
  balloon = exdData->getField< int32_t >( row, 4 );
  condition1Target = exdData->getField< uint8_t >( row, 9 );
  condition1Type = exdData->getField< uint8_t >( row, 10 );
  contentArgument0 = exdData->getField< uint32_t >( row, 11 );
  contentArgument1 = exdData->getField< uint8_t >( row, 12 );
}

Sapphire::Data::BehaviorPath::BehaviorPath( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BehaviorPathDat.get_row( row_id );
  isTurnTransition = exdData->getField< bool >( row, 0 );
  isFadeOut = exdData->getField< bool >( row, 1 );
  isFadeIn = exdData->getField< bool >( row, 2 );
  isWalking = exdData->getField< bool >( row, 3 );
  speed = exdData->getField< float >( row, 5 );
}

Sapphire::Data::BenchmarkOverrideEquipment::BenchmarkOverrideEquipment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BenchmarkOverrideEquipmentDat.get_row( row_id );
  modelMainHand = exdData->getField< uint64_t >( row, 4 );
  dyeMainHand = exdData->getField< uint8_t >( row, 5 );
  modelOffHand = exdData->getField< uint64_t >( row, 6 );
  dyeOffHand = exdData->getField< uint8_t >( row, 7 );
  modelHead = exdData->getField< uint32_t >( row, 10 );
  dyeHead = exdData->getField< uint8_t >( row, 11 );
  modelBody = exdData->getField< uint32_t >( row, 12 );
  dyeBody = exdData->getField< uint8_t >( row, 13 );
  modelHands = exdData->getField< uint32_t >( row, 14 );
  dyeHands = exdData->getField< uint8_t >( row, 15 );
  modelLegs = exdData->getField< uint32_t >( row, 16 );
  dyeLegs = exdData->getField< uint8_t >( row, 17 );
  modelFeet = exdData->getField< uint32_t >( row, 18 );
  dyeFeet = exdData->getField< uint8_t >( row, 19 );
  modelEars = exdData->getField< uint32_t >( row, 20 );
  dyeEars = exdData->getField< uint8_t >( row, 21 );
  modelNeck = exdData->getField< uint32_t >( row, 22 );
  dyeNeck = exdData->getField< uint8_t >( row, 23 );
  modelWrists = exdData->getField< uint32_t >( row, 24 );
  dyeWrists = exdData->getField< uint8_t >( row, 25 );
  modelLeftRing = exdData->getField< uint32_t >( row, 26 );
  dyeLeftRing = exdData->getField< uint8_t >( row, 27 );
  modelRightRing = exdData->getField< uint32_t >( row, 28 );
  dyeRightRing = exdData->getField< uint8_t >( row, 29 );
}

Sapphire::Data::BGM::BGM( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMDat.get_row( row_id );
  file = exdData->getField< std::string >( row, 0 );
  priority = exdData->getField< uint8_t >( row, 1 );
  disableRestartTimeOut = exdData->getField< bool >( row, 2 );
  disableRestart = exdData->getField< bool >( row, 3 );
  passEnd = exdData->getField< bool >( row, 4 );
  disableRestartResetTime = exdData->getField< float >( row, 5 );
  specialMode = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::BGMFade::BGMFade( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMFadeDat.get_row( row_id );
  sceneOut = exdData->getField< int32_t >( row, 0 );
  sceneIn = exdData->getField< int32_t >( row, 1 );
  bGMFadeType = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::BGMFadeType::BGMFadeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMFadeTypeDat.get_row( row_id );
  fadeOutTime = exdData->getField< float >( row, 0 );
  fadeInTime = exdData->getField< float >( row, 1 );
  fadeInStartTime = exdData->getField< float >( row, 2 );
  resumeFadeInTime = exdData->getField< float >( row, 3 );
}

Sapphire::Data::BGMScene::BGMScene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMSceneDat.get_row( row_id );
  enableDisableRestart = exdData->getField< bool >( row, 0 );
  resume = exdData->getField< bool >( row, 1 );
  enablePassEnd = exdData->getField< bool >( row, 2 );
  forceAutoReset = exdData->getField< bool >( row, 3 );
  ignoreBattle = exdData->getField< bool >( row, 4 );
}

Sapphire::Data::BGMSituation::BGMSituation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMSituationDat.get_row( row_id );
  daytimeID = exdData->getField< uint16_t >( row, 0 );
  nightID = exdData->getField< uint16_t >( row, 1 );
  battleID = exdData->getField< uint16_t >( row, 2 );
  daybreakID = exdData->getField< uint16_t >( row, 3 );
  twilightID = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::BGMSwitch::BGMSwitch( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMSwitchDat.get_row( row_id, subRow );
  bGMSystemDefine = exdData->getField< uint8_t >( row, 0 );
  quest = exdData->getField< uint32_t >( row, 1 );
  bGM = exdData->getField< uint16_t >( row, 3 );
}

Sapphire::Data::BGMSystemDefine::BGMSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BGMSystemDefineDat.get_row( row_id );
  define = exdData->getField< float >( row, 0 );
}

Sapphire::Data::BNpcAnnounceIcon::BNpcAnnounceIcon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BNpcAnnounceIconDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::BNpcBase::BNpcBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BNpcBaseDat.get_row( row_id );
  behavior = exdData->getField< uint16_t >( row, 0 );
  battalion = exdData->getField< uint8_t >( row, 1 );
  linkRace = exdData->getField< uint8_t >( row, 2 );
  rank = exdData->getField< uint8_t >( row, 3 );
  scale = exdData->getField< float >( row, 4 );
  modelChara = exdData->getField< uint16_t >( row, 5 );
  bNpcCustomize = exdData->getField< uint16_t >( row, 6 );
  npcEquip = exdData->getField< uint16_t >( row, 7 );
  special = exdData->getField< uint16_t >( row, 8 );
  sEPack = exdData->getField< uint8_t >( row, 9 );
  arrayEventHandler = exdData->getField< int32_t >( row, 11 );
  bNpcParts = exdData->getField< uint8_t >( row, 12 );
  isTargetLine = exdData->getField< bool >( row, 14 );
  isDisplayLevel = exdData->getField< bool >( row, 15 );
}

Sapphire::Data::BNpcCustomize::BNpcCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BNpcCustomizeDat.get_row( row_id );
  race = exdData->getField< uint8_t >( row, 0 );
  gender = exdData->getField< uint8_t >( row, 1 );
  bodyType = exdData->getField< uint8_t >( row, 2 );
  height = exdData->getField< uint8_t >( row, 3 );
  tribe = exdData->getField< uint8_t >( row, 4 );
  face = exdData->getField< uint8_t >( row, 5 );
  hairStyle = exdData->getField< uint8_t >( row, 6 );
  hairHighlight = exdData->getField< uint8_t >( row, 7 );
  skinColor = exdData->getField< uint8_t >( row, 8 );
  eyeHeterochromia = exdData->getField< uint8_t >( row, 9 );
  hairColor = exdData->getField< uint8_t >( row, 10 );
  hairHighlightColor = exdData->getField< uint8_t >( row, 11 );
  facialFeature = exdData->getField< uint8_t >( row, 12 );
  facialFeatureColor = exdData->getField< uint8_t >( row, 13 );
  eyebrows = exdData->getField< uint8_t >( row, 14 );
  eyeColor = exdData->getField< uint8_t >( row, 15 );
  eyeShape = exdData->getField< uint8_t >( row, 16 );
  nose = exdData->getField< uint8_t >( row, 17 );
  jaw = exdData->getField< uint8_t >( row, 18 );
  mouth = exdData->getField< uint8_t >( row, 19 );
  lipColor = exdData->getField< uint8_t >( row, 20 );
  bustOrTone1 = exdData->getField< uint8_t >( row, 21 );
  extraFeature1 = exdData->getField< uint8_t >( row, 22 );
  extraFeature2OrBust = exdData->getField< uint8_t >( row, 23 );
  facePaint = exdData->getField< uint8_t >( row, 24 );
  facePaintColor = exdData->getField< uint8_t >( row, 25 );
}

Sapphire::Data::BNpcName::BNpcName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BNpcNameDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
}

Sapphire::Data::BNpcParts::BNpcParts( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BNpcPartsDat.get_row( row_id );
  bNpcBase1 = exdData->getField< uint16_t >( row, 0 );
  partSlot1 = exdData->getField< uint8_t >( row, 1 );
  x1 = exdData->getField< float >( row, 6 );
  y1 = exdData->getField< float >( row, 7 );
  z1 = exdData->getField< float >( row, 8 );
  scale1 = exdData->getField< float >( row, 10 );
  bNpcBase2 = exdData->getField< uint16_t >( row, 11 );
  partSlot2 = exdData->getField< uint8_t >( row, 12 );
  x2 = exdData->getField< float >( row, 17 );
  y2 = exdData->getField< float >( row, 18 );
  z2 = exdData->getField< float >( row, 19 );
  scale2 = exdData->getField< float >( row, 21 );
  bNpcBase3 = exdData->getField< uint16_t >( row, 22 );
  partSlot3 = exdData->getField< uint8_t >( row, 23 );
  x3 = exdData->getField< float >( row, 28 );
  y3 = exdData->getField< float >( row, 29 );
  z3 = exdData->getField< float >( row, 30 );
  scale3 = exdData->getField< int16_t >( row, 31 );
  bNpcBase4 = exdData->getField< uint16_t >( row, 33 );
  partSlot4 = exdData->getField< uint8_t >( row, 34 );
  x4 = exdData->getField< float >( row, 39 );
  y4 = exdData->getField< float >( row, 40 );
  z4 = exdData->getField< float >( row, 41 );
  scale4 = exdData->getField< float >( row, 43 );
  bNpcBase5 = exdData->getField< uint16_t >( row, 44 );
  partSlot5 = exdData->getField< uint8_t >( row, 45 );
  x5 = exdData->getField< float >( row, 50 );
  y5 = exdData->getField< float >( row, 51 );
  z5 = exdData->getField< float >( row, 52 );
  scale5 = exdData->getField< float >( row, 54 );
}

Sapphire::Data::BNpcState::BNpcState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BNpcStateDat.get_row( row_id );
  slot = exdData->getField< uint8_t >( row, 0 );
  overRay = exdData->getField< int8_t >( row, 1 );
  idle = exdData->getField< uint16_t >( row, 4 );
  attribute0 = exdData->getField< uint8_t >( row, 5 );
  attributeFlag0 = exdData->getField< bool >( row, 6 );
  attribute1 = exdData->getField< uint8_t >( row, 7 );
  attributeFlag1 = exdData->getField< bool >( row, 8 );
  attribute2 = exdData->getField< uint8_t >( row, 9 );
  attributeFlag2 = exdData->getField< bool >( row, 10 );
  scale = exdData->getField< float >( row, 11 );
  loopTimeline = exdData->getField< int32_t >( row, 13 );
}

Sapphire::Data::Buddy::Buddy( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BuddyDat.get_row( row_id );
  base = exdData->getField< uint8_t >( row, 0 );
  questRequirement2 = exdData->getField< int32_t >( row, 1 );
  questRequirement1 = exdData->getField< int32_t >( row, 2 );
  baseEquip = exdData->getField< int32_t >( row, 3 );
  soundEffect4 = exdData->getField< std::string >( row, 4 );
  soundEffect3 = exdData->getField< std::string >( row, 5 );
  soundEffect2 = exdData->getField< std::string >( row, 6 );
  soundEffect1 = exdData->getField< std::string >( row, 7 );
}

Sapphire::Data::BuddyAction::BuddyAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BuddyActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< int32_t >( row, 2 );
  iconStatus = exdData->getField< int32_t >( row, 3 );
  reward = exdData->getField< uint16_t >( row, 4 );
  sort = exdData->getField< uint8_t >( row, 5 );
}

Sapphire::Data::BuddyEquip::BuddyEquip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BuddyEquipDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  name = exdData->getField< std::string >( row, 8 );
  modelTop = exdData->getField< int32_t >( row, 9 );
  modelBody = exdData->getField< int32_t >( row, 10 );
  modelLegs = exdData->getField< int32_t >( row, 11 );
  grandCompany = exdData->getField< uint8_t >( row, 12 );
  iconHead = exdData->getField< uint16_t >( row, 13 );
  iconBody = exdData->getField< uint16_t >( row, 14 );
  iconLegs = exdData->getField< uint16_t >( row, 15 );
  order = exdData->getField< uint8_t >( row, 16 );
}

Sapphire::Data::BuddyItem::BuddyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BuddyItemDat.get_row( row_id );
  item = exdData->getField< uint16_t >( row, 0 );
  useField = exdData->getField< bool >( row, 1 );
  useTraining = exdData->getField< bool >( row, 2 );
  status = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::BuddyRank::BuddyRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BuddyRankDat.get_row( row_id );
  expRequired = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::BuddySkill::BuddySkill( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_BuddySkillDat.get_row( row_id );
  buddyLevel = exdData->getField< uint8_t >( row, 0 );
  isActive = exdData->getField< bool >( row, 1 );
  defender = exdData->getField< uint16_t >( row, 2 );
  attacker = exdData->getField< uint16_t >( row, 3 );
  healer = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::Cabinet::Cabinet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CabinetDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  order = exdData->getField< uint16_t >( row, 1 );
  category = exdData->getField< uint8_t >( row, 2 );
}

Sapphire::Data::CabinetCategory::CabinetCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CabinetCategoryDat.get_row( row_id );
  menuOrder = exdData->getField< uint8_t >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  category = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::Calendar::Calendar( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CalendarDat.get_row( row_id );
  month.push_back( exdData->getField< uint8_t >( row, 0 ) );
  month.push_back( exdData->getField< uint8_t >( row, 1 ) );
  month.push_back( exdData->getField< uint8_t >( row, 2 ) );
  month.push_back( exdData->getField< uint8_t >( row, 3 ) );
  month.push_back( exdData->getField< uint8_t >( row, 4 ) );
  month.push_back( exdData->getField< uint8_t >( row, 5 ) );
  month.push_back( exdData->getField< uint8_t >( row, 6 ) );
  month.push_back( exdData->getField< uint8_t >( row, 7 ) );
  month.push_back( exdData->getField< uint8_t >( row, 8 ) );
  month.push_back( exdData->getField< uint8_t >( row, 9 ) );
  month.push_back( exdData->getField< uint8_t >( row, 10 ) );
  month.push_back( exdData->getField< uint8_t >( row, 11 ) );
  month.push_back( exdData->getField< uint8_t >( row, 12 ) );
  month.push_back( exdData->getField< uint8_t >( row, 13 ) );
  month.push_back( exdData->getField< uint8_t >( row, 14 ) );
  month.push_back( exdData->getField< uint8_t >( row, 15 ) );
  month.push_back( exdData->getField< uint8_t >( row, 16 ) );
  month.push_back( exdData->getField< uint8_t >( row, 17 ) );
  month.push_back( exdData->getField< uint8_t >( row, 18 ) );
  month.push_back( exdData->getField< uint8_t >( row, 19 ) );
  month.push_back( exdData->getField< uint8_t >( row, 20 ) );
  month.push_back( exdData->getField< uint8_t >( row, 21 ) );
  month.push_back( exdData->getField< uint8_t >( row, 22 ) );
  month.push_back( exdData->getField< uint8_t >( row, 23 ) );
  month.push_back( exdData->getField< uint8_t >( row, 24 ) );
  month.push_back( exdData->getField< uint8_t >( row, 25 ) );
  month.push_back( exdData->getField< uint8_t >( row, 26 ) );
  month.push_back( exdData->getField< uint8_t >( row, 27 ) );
  month.push_back( exdData->getField< uint8_t >( row, 28 ) );
  month.push_back( exdData->getField< uint8_t >( row, 29 ) );
  month.push_back( exdData->getField< uint8_t >( row, 30 ) );
  month.push_back( exdData->getField< uint8_t >( row, 31 ) );
  day.push_back( exdData->getField< uint8_t >( row, 32 ) );
  day.push_back( exdData->getField< uint8_t >( row, 33 ) );
  day.push_back( exdData->getField< uint8_t >( row, 34 ) );
  day.push_back( exdData->getField< uint8_t >( row, 35 ) );
  day.push_back( exdData->getField< uint8_t >( row, 36 ) );
  day.push_back( exdData->getField< uint8_t >( row, 37 ) );
  day.push_back( exdData->getField< uint8_t >( row, 38 ) );
  day.push_back( exdData->getField< uint8_t >( row, 39 ) );
  day.push_back( exdData->getField< uint8_t >( row, 40 ) );
  day.push_back( exdData->getField< uint8_t >( row, 41 ) );
  day.push_back( exdData->getField< uint8_t >( row, 42 ) );
  day.push_back( exdData->getField< uint8_t >( row, 43 ) );
  day.push_back( exdData->getField< uint8_t >( row, 44 ) );
  day.push_back( exdData->getField< uint8_t >( row, 45 ) );
  day.push_back( exdData->getField< uint8_t >( row, 46 ) );
  day.push_back( exdData->getField< uint8_t >( row, 47 ) );
  day.push_back( exdData->getField< uint8_t >( row, 48 ) );
  day.push_back( exdData->getField< uint8_t >( row, 49 ) );
  day.push_back( exdData->getField< uint8_t >( row, 50 ) );
  day.push_back( exdData->getField< uint8_t >( row, 51 ) );
  day.push_back( exdData->getField< uint8_t >( row, 52 ) );
  day.push_back( exdData->getField< uint8_t >( row, 53 ) );
  day.push_back( exdData->getField< uint8_t >( row, 54 ) );
  day.push_back( exdData->getField< uint8_t >( row, 55 ) );
  day.push_back( exdData->getField< uint8_t >( row, 56 ) );
  day.push_back( exdData->getField< uint8_t >( row, 57 ) );
  day.push_back( exdData->getField< uint8_t >( row, 58 ) );
  day.push_back( exdData->getField< uint8_t >( row, 59 ) );
  day.push_back( exdData->getField< uint8_t >( row, 60 ) );
  day.push_back( exdData->getField< uint8_t >( row, 61 ) );
  day.push_back( exdData->getField< uint8_t >( row, 62 ) );
  day.push_back( exdData->getField< uint8_t >( row, 63 ) );
}

Sapphire::Data::Carry::Carry( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CarryDat.get_row( row_id );
  model = exdData->getField< uint64_t >( row, 0 );
  timeline = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::Channeling::Channeling( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChannelingDat.get_row( row_id );
  file = exdData->getField< std::string >( row, 0 );
  widthScale = exdData->getField< uint8_t >( row, 1 );
  addedIn53 = exdData->getField< bool >( row, 2 );
}

Sapphire::Data::CharaMakeClassEquip::CharaMakeClassEquip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CharaMakeClassEquipDat.get_row( row_id );
  helmet = exdData->getField< uint64_t >( row, 0 );
  top = exdData->getField< uint64_t >( row, 1 );
  glove = exdData->getField< uint64_t >( row, 2 );
  down = exdData->getField< uint64_t >( row, 3 );
  shoes = exdData->getField< uint64_t >( row, 4 );
  weapon = exdData->getField< uint64_t >( row, 5 );
  subWeapon = exdData->getField< uint64_t >( row, 6 );
  _class = exdData->getField< int32_t >( row, 7 );
}

Sapphire::Data::CharaMakeCustomize::CharaMakeCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CharaMakeCustomizeDat.get_row( row_id );
  featureID = exdData->getField< uint8_t >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  data = exdData->getField< uint16_t >( row, 2 );
  isPurchasable = exdData->getField< bool >( row, 3 );
  hint = exdData->getField< uint32_t >( row, 4 );
  hintItem = exdData->getField< uint32_t >( row, 5 );
}

Sapphire::Data::CharaMakeName::CharaMakeName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CharaMakeNameDat.get_row( row_id );
  hyurMidlanderMale = exdData->getField< std::string >( row, 0 );
  hyurMidlanderFemale = exdData->getField< std::string >( row, 1 );
  hyurMidlanderLastName = exdData->getField< std::string >( row, 2 );
  hyurHighlanderMale = exdData->getField< std::string >( row, 3 );
  hyurHighlanderFemale = exdData->getField< std::string >( row, 4 );
  hyurHighlanderLastName = exdData->getField< std::string >( row, 5 );
  elezenMale = exdData->getField< std::string >( row, 6 );
  elezenFemale = exdData->getField< std::string >( row, 7 );
  elezenWildwoodLastName = exdData->getField< std::string >( row, 8 );
  elezenDuskwightLastName = exdData->getField< std::string >( row, 9 );
  miqoteSunMale = exdData->getField< std::string >( row, 10 );
  miqoteSunFemale = exdData->getField< std::string >( row, 11 );
  miqoteSunMaleLastName = exdData->getField< std::string >( row, 12 );
  miqoteSunFemaleLastName = exdData->getField< std::string >( row, 13 );
  miqoteMoonMale = exdData->getField< std::string >( row, 14 );
  miqoteMoonFemale = exdData->getField< std::string >( row, 15 );
  miqoteMoonLastname = exdData->getField< std::string >( row, 16 );
  lalafellPlainsfolkFirstNameStart = exdData->getField< std::string >( row, 17 );
  lalafellPlainsfolkLastNameStart = exdData->getField< std::string >( row, 18 );
  lalafellPlainsfolkEndOfNames = exdData->getField< std::string >( row, 19 );
  lalafellDunesfolkMale = exdData->getField< std::string >( row, 20 );
  lalafellDunesfolkMaleLastName = exdData->getField< std::string >( row, 21 );
  lalafellDunesfolkFemale = exdData->getField< std::string >( row, 22 );
  lalafellDunesfolkFemaleLastName = exdData->getField< std::string >( row, 23 );
  roegadynSeaWolfMale = exdData->getField< std::string >( row, 24 );
  roegadynSeaWolfMaleLastName = exdData->getField< std::string >( row, 25 );
  roegadynSeaWolfFemale = exdData->getField< std::string >( row, 26 );
  roegadynSeaWolfFemaleLastName = exdData->getField< std::string >( row, 27 );
  roegadynHellsguardFirstName = exdData->getField< std::string >( row, 28 );
  roegadynHellsguardMaleLastName = exdData->getField< std::string >( row, 29 );
  roegadynHellsguardFemaleLastName = exdData->getField< std::string >( row, 30 );
  auRaRaenMale = exdData->getField< std::string >( row, 31 );
  auRaRaenFemale = exdData->getField< std::string >( row, 32 );
  auRaRaenLastName = exdData->getField< std::string >( row, 33 );
  auRaXaelaMale = exdData->getField< std::string >( row, 34 );
  auRaXaelaFemale = exdData->getField< std::string >( row, 35 );
  auRaXaelaLastName = exdData->getField< std::string >( row, 36 );
  hrothgarHellionsFirstName = exdData->getField< std::string >( row, 37 );
  hrothgarHellionsLastName = exdData->getField< std::string >( row, 38 );
  hrothgarLostFirstName = exdData->getField< std::string >( row, 39 );
  hrothgarLostLastName = exdData->getField< std::string >( row, 40 );
  vieraFirstName = exdData->getField< std::string >( row, 41 );
  vieraRavaLastName = exdData->getField< std::string >( row, 42 );
  vieraVeenaLastName = exdData->getField< std::string >( row, 43 );
}

Sapphire::Data::CharaMakeType::CharaMakeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CharaMakeTypeDat.get_row( row_id );
  race = exdData->getField< int32_t >( row, 0 );
  tribe = exdData->getField< int32_t >( row, 1 );
  gender = exdData->getField< int8_t >( row, 2 );
  menu.push_back( exdData->getField< uint32_t >( row, 3 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 4 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 5 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 6 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 7 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 8 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 9 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 10 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 11 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 12 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 13 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 14 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 15 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 16 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 17 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 18 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 19 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 20 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 21 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 22 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 23 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 24 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 25 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 26 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 27 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 28 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 29 ) );
  menu.push_back( exdData->getField< uint32_t >( row, 30 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 31 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 32 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 33 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 34 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 35 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 36 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 37 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 38 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 39 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 40 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 41 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 42 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 43 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 44 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 45 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 46 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 47 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 48 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 49 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 50 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 51 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 52 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 53 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 54 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 55 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 56 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 57 ) );
  initVal.push_back( exdData->getField< uint8_t >( row, 58 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 59 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 60 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 61 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 62 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 63 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 64 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 65 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 66 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 67 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 68 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 69 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 70 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 71 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 72 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 73 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 74 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 75 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 76 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 77 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 78 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 79 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 80 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 81 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 82 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 83 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 84 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 85 ) );
  subMenuType.push_back( exdData->getField< uint8_t >( row, 86 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 87 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 88 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 89 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 90 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 91 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 92 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 93 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 94 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 95 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 96 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 97 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 98 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 99 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 100 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 101 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 102 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 103 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 104 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 105 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 106 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 107 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 108 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 109 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 110 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 111 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 112 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 113 ) );
  subMenuNum.push_back( exdData->getField< uint8_t >( row, 114 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 115 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 116 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 117 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 118 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 119 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 120 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 121 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 122 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 123 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 124 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 125 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 126 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 127 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 128 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 129 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 130 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 131 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 132 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 133 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 134 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 135 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 136 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 137 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 138 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 139 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 140 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 141 ) );
  lookAt.push_back( exdData->getField< uint8_t >( row, 142 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 143 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 144 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 145 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 146 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 147 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 148 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 149 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 150 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 151 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 152 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 153 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 154 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 155 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 156 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 157 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 158 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 159 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 160 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 161 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 162 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 163 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 164 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 165 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 166 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 167 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 168 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 169 ) );
  subMenuMask.push_back( exdData->getField< uint32_t >( row, 170 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 171 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 172 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 173 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 174 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 175 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 176 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 177 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 178 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 179 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 180 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 181 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 182 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 183 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 184 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 185 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 186 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 187 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 188 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 189 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 190 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 191 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 192 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 193 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 194 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 195 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 196 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 197 ) );
  customize.push_back( exdData->getField< uint32_t >( row, 198 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3279 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3280 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3281 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3282 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3283 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3284 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3285 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3286 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3287 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3288 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3289 ) );
  voiceStruct.push_back( exdData->getField< uint8_t >( row, 3290 ) );
}

Sapphire::Data::ChocoboRace::ChocoboRace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceDat.get_row( row_id );
  chocoboRaceRank = exdData->getField< uint8_t >( row, 0 );
  chocoboRaceTerritory = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::ChocoboRaceAbility::ChocoboRaceAbility( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceAbilityDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< uint32_t >( row, 2 );
  chocoboRaceAbilityType = exdData->getField< int8_t >( row, 3 );
  value = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::ChocoboRaceAbilityType::ChocoboRaceAbilityType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceAbilityTypeDat.get_row( row_id );
  isActive = exdData->getField< bool >( row, 0 );
}

Sapphire::Data::ChocoboRaceItem::ChocoboRaceItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceItemDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::ChocoboRaceRank::ChocoboRaceRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceRankDat.get_row( row_id );
  ratingMin = exdData->getField< uint16_t >( row, 0 );
  ratingMax = exdData->getField< uint16_t >( row, 1 );
  name = exdData->getField< uint16_t >( row, 2 );
  fee = exdData->getField< uint16_t >( row, 3 );
  icon = exdData->getField< int32_t >( row, 4 );
}

Sapphire::Data::ChocoboRaceStatus::ChocoboRaceStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceStatusDat.get_row( row_id );
  status = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::ChocoboRaceTerritory::ChocoboRaceTerritory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceTerritoryDat.get_row( row_id );
  name = exdData->getField< uint16_t >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::ChocoboRaceTutorial::ChocoboRaceTutorial( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceTutorialDat.get_row( row_id );
  npcYell.push_back( exdData->getField< int32_t >( row, 0 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 1 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 2 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 3 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 4 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 5 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 6 ) );
  npcYell.push_back( exdData->getField< int32_t >( row, 7 ) );
}

Sapphire::Data::ChocoboRaceWeather::ChocoboRaceWeather( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboRaceWeatherDat.get_row( row_id );
  weatherType1 = exdData->getField< int32_t >( row, 0 );
  weatherType2 = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::ChocoboTaxi::ChocoboTaxi( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboTaxiDat.get_row( row_id );
  location = exdData->getField< uint32_t >( row, 0 );
  fare = exdData->getField< uint8_t >( row, 1 );
  timeRequired = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::ChocoboTaxiStand::ChocoboTaxiStand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ChocoboTaxiStandDat.get_row( row_id );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 0 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 1 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 2 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 3 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 4 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 5 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 6 ) );
  targetLocations.push_back( exdData->getField< uint16_t >( row, 7 ) );
  placeName = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::CircleActivity::CircleActivity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CircleActivityDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  order = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::ClassJob::ClassJob( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ClassJobDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  abbreviation = exdData->getField< std::string >( row, 1 );
  classJobCategory = exdData->getField< uint8_t >( row, 3 );
  expArrayIndex = exdData->getField< int8_t >( row, 4 );
  battleClassIndex = exdData->getField< int8_t >( row, 5 );
  jobIndex = exdData->getField< uint8_t >( row, 7 );
  dohDolJobIndex = exdData->getField< int8_t >( row, 8 );
  modifierHitPoints = exdData->getField< uint16_t >( row, 9 );
  modifierManaPoints = exdData->getField< uint16_t >( row, 10 );
  modifierStrength = exdData->getField< uint16_t >( row, 11 );
  modifierVitality = exdData->getField< uint16_t >( row, 12 );
  modifierDexterity = exdData->getField< uint16_t >( row, 13 );
  modifierIntelligence = exdData->getField< uint16_t >( row, 14 );
  modifierMind = exdData->getField< uint16_t >( row, 15 );
  modifierPiety = exdData->getField< uint16_t >( row, 16 );
  classJobParent = exdData->getField< uint8_t >( row, 26 );
  nameEnglish = exdData->getField< std::string >( row, 27 );
  itemStartingWeapon = exdData->getField< int32_t >( row, 28 );
  role = exdData->getField< uint8_t >( row, 30 );
  startingTown = exdData->getField< uint8_t >( row, 31 );
  monsterNote = exdData->getField< int8_t >( row, 32 );
  primaryStat = exdData->getField< uint8_t >( row, 33 );
  limitBreak1 = exdData->getField< uint16_t >( row, 34 );
  limitBreak2 = exdData->getField< uint16_t >( row, 35 );
  limitBreak3 = exdData->getField< uint16_t >( row, 36 );
  uIPriority = exdData->getField< uint8_t >( row, 37 );
  itemSoulCrystal = exdData->getField< uint32_t >( row, 38 );
  unlockQuest = exdData->getField< uint32_t >( row, 39 );
  relicQuest = exdData->getField< uint32_t >( row, 40 );
  prerequisite = exdData->getField< uint32_t >( row, 41 );
  startingLevel = exdData->getField< uint8_t >( row, 42 );
  partyBonus = exdData->getField< uint8_t >( row, 43 );
  isLimitedJob = exdData->getField< bool >( row, 44 );
  canQueueForDuty = exdData->getField< bool >( row, 45 );
}

Sapphire::Data::ClassJobCategory::ClassJobCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ClassJobCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  aDV = exdData->getField< bool >( row, 1 );
  gLA = exdData->getField< bool >( row, 2 );
  pGL = exdData->getField< bool >( row, 3 );
  mRD = exdData->getField< bool >( row, 4 );
  lNC = exdData->getField< bool >( row, 5 );
  aRC = exdData->getField< bool >( row, 6 );
  cNJ = exdData->getField< bool >( row, 7 );
  tHM = exdData->getField< bool >( row, 8 );
  cRP = exdData->getField< bool >( row, 9 );
  bSM = exdData->getField< bool >( row, 10 );
  aRM = exdData->getField< bool >( row, 11 );
  gSM = exdData->getField< bool >( row, 12 );
  lTW = exdData->getField< bool >( row, 13 );
  wVR = exdData->getField< bool >( row, 14 );
  aLC = exdData->getField< bool >( row, 15 );
  cUL = exdData->getField< bool >( row, 16 );
  mIN = exdData->getField< bool >( row, 17 );
  bTN = exdData->getField< bool >( row, 18 );
  fSH = exdData->getField< bool >( row, 19 );
  pLD = exdData->getField< bool >( row, 20 );
  mNK = exdData->getField< bool >( row, 21 );
  wAR = exdData->getField< bool >( row, 22 );
  dRG = exdData->getField< bool >( row, 23 );
  bRD = exdData->getField< bool >( row, 24 );
  wHM = exdData->getField< bool >( row, 25 );
  bLM = exdData->getField< bool >( row, 26 );
  aCN = exdData->getField< bool >( row, 27 );
  sMN = exdData->getField< bool >( row, 28 );
  sCH = exdData->getField< bool >( row, 29 );
  rOG = exdData->getField< bool >( row, 30 );
  nIN = exdData->getField< bool >( row, 31 );
  mCH = exdData->getField< bool >( row, 32 );
  dRK = exdData->getField< bool >( row, 33 );
  aST = exdData->getField< bool >( row, 34 );
  sAM = exdData->getField< bool >( row, 35 );
  rDM = exdData->getField< bool >( row, 36 );
  bLU = exdData->getField< bool >( row, 37 );
  gNB = exdData->getField< bool >( row, 38 );
  dNC = exdData->getField< bool >( row, 39 );
}

Sapphire::Data::CollectablesShop::CollectablesShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CollectablesShopDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  quest = exdData->getField< uint32_t >( row, 1 );
  shopItems.push_back( exdData->getField< uint16_t >( row, 3 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 4 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 5 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 6 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 7 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 8 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 9 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 10 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 11 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 12 ) );
  shopItems.push_back( exdData->getField< uint16_t >( row, 13 ) );
}

Sapphire::Data::CollectablesShopItem::CollectablesShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CollectablesShopItemDat.get_row( row_id, subRow );
  item = exdData->getField< uint32_t >( row, 0 );
  collectablesShopItemGroup = exdData->getField< uint8_t >( row, 1 );
  levelMin = exdData->getField< uint16_t >( row, 2 );
  levelMax = exdData->getField< uint16_t >( row, 3 );
  collectablesShopRefine = exdData->getField< uint16_t >( row, 6 );
  collectablesShopRewardScrip = exdData->getField< uint16_t >( row, 7 );
}

Sapphire::Data::CollectablesShopItemGroup::CollectablesShopItemGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CollectablesShopItemGroupDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CollectablesShopRefine::CollectablesShopRefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CollectablesShopRefineDat.get_row( row_id );
  lowCollectability = exdData->getField< uint16_t >( row, 0 );
  midCollectability = exdData->getField< uint16_t >( row, 1 );
  highCollectability = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::CollectablesShopRewardItem::CollectablesShopRewardItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CollectablesShopRewardItemDat.get_row( row_id );
  item = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::CollectablesShopRewardScrip::CollectablesShopRewardScrip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CollectablesShopRewardScripDat.get_row( row_id );
  currency = exdData->getField< uint16_t >( row, 0 );
  lowReward = exdData->getField< uint16_t >( row, 1 );
  midReward = exdData->getField< uint16_t >( row, 2 );
  highReward = exdData->getField< uint16_t >( row, 3 );
  expRatioLow = exdData->getField< uint16_t >( row, 4 );
  expRatioMid = exdData->getField< uint16_t >( row, 5 );
  expRatioHigh = exdData->getField< uint16_t >( row, 6 );
}

Sapphire::Data::Companion::Companion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanionDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  model = exdData->getField< uint16_t >( row, 8 );
  scale = exdData->getField< uint8_t >( row, 9 );
  inactiveIdle0 = exdData->getField< uint8_t >( row, 10 );
  inactiveIdle1 = exdData->getField< uint8_t >( row, 11 );
  inactiveBattle = exdData->getField< uint8_t >( row, 12 );
  inactiveWandering = exdData->getField< uint8_t >( row, 13 );
  behavior = exdData->getField< uint8_t >( row, 14 );
  special = exdData->getField< uint8_t >( row, 15 );
  wanderingWait = exdData->getField< uint8_t >( row, 16 );
  priority = exdData->getField< uint16_t >( row, 17 );
  roulette = exdData->getField< bool >( row, 18 );
  battle = exdData->getField< bool >( row, 20 );
  lookAt = exdData->getField< bool >( row, 21 );
  poke = exdData->getField< bool >( row, 22 );
  enemy = exdData->getField< uint16_t >( row, 23 );
  stroke = exdData->getField< bool >( row, 24 );
  clapping = exdData->getField< bool >( row, 25 );
  icon = exdData->getField< uint16_t >( row, 26 );
  order = exdData->getField< uint16_t >( row, 27 );
  cost = exdData->getField< uint8_t >( row, 30 );
  hP = exdData->getField< uint16_t >( row, 31 );
  skillAngle = exdData->getField< uint16_t >( row, 33 );
  skillCost = exdData->getField< uint8_t >( row, 34 );
  minionRace = exdData->getField< uint8_t >( row, 37 );
}

Sapphire::Data::CompanionMove::CompanionMove( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanionMoveDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CompanionTransient::CompanionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanionTransientDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
  descriptionEnhanced = exdData->getField< std::string >( row, 1 );
  tooltip = exdData->getField< std::string >( row, 2 );
  specialActionName = exdData->getField< std::string >( row, 3 );
  specialActionDescription = exdData->getField< std::string >( row, 4 );
  attack = exdData->getField< uint8_t >( row, 5 );
  defense = exdData->getField< uint8_t >( row, 6 );
  speed = exdData->getField< uint8_t >( row, 7 );
  hasAreaAttack = exdData->getField< bool >( row, 8 );
  strengthGate = exdData->getField< bool >( row, 9 );
  strengthEye = exdData->getField< bool >( row, 10 );
  strengthShield = exdData->getField< bool >( row, 11 );
  strengthArcana = exdData->getField< bool >( row, 12 );
  minionSkillType = exdData->getField< uint8_t >( row, 13 );
}

Sapphire::Data::CompanyAction::CompanyAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< int32_t >( row, 2 );
  fCRank = exdData->getField< uint8_t >( row, 3 );
  cost = exdData->getField< uint32_t >( row, 4 );
  order = exdData->getField< uint8_t >( row, 5 );
  purchasable = exdData->getField< bool >( row, 6 );
}

Sapphire::Data::CompanyCraftDraft::CompanyCraftDraft( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftDraftDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  companyCraftDraftCategory = exdData->getField< uint8_t >( row, 1 );
  order = exdData->getField< uint32_t >( row, 8 );
}

Sapphire::Data::CompanyCraftDraftCategory::CompanyCraftDraftCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftDraftCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CompanyCraftManufactoryState::CompanyCraftManufactoryState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftManufactoryStateDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CompanyCraftPart::CompanyCraftPart( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftPartDat.get_row( row_id );
  companyCraftType = exdData->getField< uint8_t >( row, 1 );
  companyCraftProcess.push_back( exdData->getField< uint16_t >( row, 2 ) );
  companyCraftProcess.push_back( exdData->getField< uint16_t >( row, 3 ) );
  companyCraftProcess.push_back( exdData->getField< uint16_t >( row, 4 ) );
}

Sapphire::Data::CompanyCraftProcess::CompanyCraftProcess( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftProcessDat.get_row( row_id );
}

Sapphire::Data::CompanyCraftSequence::CompanyCraftSequence( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftSequenceDat.get_row( row_id );
  resultItem = exdData->getField< int32_t >( row, 0 );
  category = exdData->getField< int32_t >( row, 1 );
  companyCraftDraftCategory = exdData->getField< int32_t >( row, 2 );
  companyCraftType = exdData->getField< int32_t >( row, 3 );
  companyCraftDraft = exdData->getField< int32_t >( row, 4 );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 5 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 6 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 7 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 8 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 9 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 10 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 11 ) );
  companyCraftPart.push_back( exdData->getField< uint16_t >( row, 12 ) );
  order = exdData->getField< uint32_t >( row, 13 );
}

Sapphire::Data::CompanyCraftSupplyItem::CompanyCraftSupplyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftSupplyItemDat.get_row( row_id );
  item = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::CompanyCraftType::CompanyCraftType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyCraftTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CompanyLeve::CompanyLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyLeveDat.get_row( row_id );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 0 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 1 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 2 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 3 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 4 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 5 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 6 ) );
  routePointTime.push_back( exdData->getField< uint16_t >( row, 7 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 8 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 9 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 10 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 11 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 12 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 13 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 14 ) );
  baseID.push_back( exdData->getField< int32_t >( row, 15 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 16 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 17 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 18 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 19 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 20 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 21 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 22 ) );
  enemyLevel.push_back( exdData->getField< uint16_t >( row, 23 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 24 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 25 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 26 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 27 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 28 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 29 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 30 ) );
  bNpcName.push_back( exdData->getField< uint32_t >( row, 31 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 32 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 33 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 34 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 35 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 36 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 37 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 38 ) );
  itemsInvolved.push_back( exdData->getField< int32_t >( row, 39 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 40 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 41 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 42 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 43 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 44 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 45 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 46 ) );
  itemsInvolvedQty.push_back( exdData->getField< uint8_t >( row, 47 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 48 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 49 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 50 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 51 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 52 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 53 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 54 ) );
  itemDropRate.push_back( exdData->getField< uint8_t >( row, 55 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 168 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 169 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 170 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 171 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 172 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 173 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 174 ) );
  toDoSequence.push_back( exdData->getField< uint8_t >( row, 175 ) );
  rule = exdData->getField< int32_t >( row, 176 );
  ruleParam = exdData->getField< uint8_t >( row, 177 );
}

Sapphire::Data::CompanyLeveRule::CompanyLeveRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompanyLeveRuleDat.get_row( row_id );
  type = exdData->getField< std::string >( row, 0 );
  objective = exdData->getField< uint16_t >( row, 1 );
  help = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::CompleteJournal::CompleteJournal( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompleteJournalDat.get_row( row_id );
  requiredLevel = exdData->getField< uint16_t >( row, 1 );
  icon = exdData->getField< int32_t >( row, 3 );
  name = exdData->getField< std::string >( row, 5 );
  cutscene.push_back( exdData->getField< int32_t >( row, 6 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 7 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 8 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 9 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 10 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 11 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 12 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 13 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 14 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 15 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 16 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 17 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 18 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 19 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 20 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 21 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 22 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 23 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 24 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 25 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 26 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 27 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 28 ) );
  cutscene.push_back( exdData->getField< int32_t >( row, 29 ) );
}

Sapphire::Data::CompleteJournalCategory::CompleteJournalCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CompleteJournalCategoryDat.get_row( row_id );
  firstQuest = exdData->getField< uint32_t >( row, 0 );
  lastQuest = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::Condition::Condition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ConditionDat.get_row( row_id );
  logMessage = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::ConfigKey::ConfigKey( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ConfigKeyDat.get_row( row_id );
  label = exdData->getField< std::string >( row, 0 );
  param = exdData->getField< uint8_t >( row, 1 );
  platform = exdData->getField< uint8_t >( row, 2 );
  required = exdData->getField< bool >( row, 3 );
  category = exdData->getField< uint8_t >( row, 4 );
  text = exdData->getField< std::string >( row, 7 );
}

Sapphire::Data::ContentCloseCycle::ContentCloseCycle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentCloseCycleDat.get_row( row_id );
  unixtime = exdData->getField< uint32_t >( row, 0 );
  timeSeconds = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::ContentExAction::ContentExAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentExActionDat.get_row( row_id );
  name = exdData->getField< uint32_t >( row, 0 );
  charges = exdData->getField< uint8_t >( row, 2 );
}

Sapphire::Data::ContentFinderCondition::ContentFinderCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentFinderConditionDat.get_row( row_id );
  shortCode = exdData->getField< std::string >( row, 0 );
  territoryType = exdData->getField< uint16_t >( row, 1 );
  contentLinkType = exdData->getField< uint8_t >( row, 2 );
  content = exdData->getField< uint16_t >( row, 3 );
  pvP = exdData->getField< bool >( row, 4 );
  acceptClassJobCategory = exdData->getField< uint8_t >( row, 8 );
  contentMemberType = exdData->getField< uint8_t >( row, 9 );
  unlockQuest = exdData->getField< uint32_t >( row, 13 );
  classJobLevelRequired = exdData->getField< uint8_t >( row, 15 );
  classJobLevelSync = exdData->getField< uint8_t >( row, 16 );
  itemLevelRequired = exdData->getField< uint16_t >( row, 17 );
  itemLevelSync = exdData->getField< uint16_t >( row, 18 );
  addedIn53 = exdData->getField< bool >( row, 19 );
  allowUndersized = exdData->getField< bool >( row, 20 );
  allowReplacement = exdData->getField< bool >( row, 21 );
  allowExplorerMode = exdData->getField< bool >( row, 23 );
  unknown54 = exdData->getField< bool >( row, 25 );
  highEndDuty = exdData->getField< bool >( row, 28 );
  dutyRecorderAllowed = exdData->getField< bool >( row, 32 );
  name = exdData->getField< std::string >( row, 37 );
  contentType = exdData->getField< uint8_t >( row, 38 );
  transientKey = exdData->getField< uint8_t >( row, 39 );
  transient = exdData->getField< uint32_t >( row, 40 );
  sortKey = exdData->getField< uint16_t >( row, 41 );
  image = exdData->getField< uint32_t >( row, 42 );
  icon = exdData->getField< uint32_t >( row, 43 );
  levelingRoulette = exdData->getField< bool >( row, 45 );
  level506070Roulette = exdData->getField< bool >( row, 46 );
  mSQRoulette = exdData->getField< bool >( row, 47 );
  guildHestRoulette = exdData->getField< bool >( row, 48 );
  expertRoulette = exdData->getField< bool >( row, 49 );
  trialRoulette = exdData->getField< bool >( row, 50 );
  dailyFrontlineChallenge = exdData->getField< bool >( row, 51 );
  level80Roulette = exdData->getField< bool >( row, 52 );
  mentorRoulette = exdData->getField< bool >( row, 53 );
  allianceRoulette = exdData->getField< bool >( row, 59 );
  normalRaidRoulette = exdData->getField< bool >( row, 61 );
}

Sapphire::Data::ContentFinderConditionTransient::ContentFinderConditionTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentFinderConditionTransientDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ContentGauge::ContentGauge( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentGaugeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  color = exdData->getField< uint8_t >( row, 1 );
  textString = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::ContentGaugeColor::ContentGaugeColor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentGaugeColorDat.get_row( row_id );
  androidColor1 = exdData->getField< uint32_t >( row, 0 );
  androidColor2 = exdData->getField< uint32_t >( row, 1 );
  androidColor3 = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::ContentMemberType::ContentMemberType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentMemberTypeDat.get_row( row_id );
  tanksPerParty = exdData->getField< uint8_t >( row, 9 );
  healersPerParty = exdData->getField< uint8_t >( row, 10 );
  meleesPerParty = exdData->getField< uint8_t >( row, 11 );
  rangedPerParty = exdData->getField< uint8_t >( row, 12 );
  unknown54 = exdData->getField< uint8_t >( row, 13 );
}

Sapphire::Data::ContentNpcTalk::ContentNpcTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentNpcTalkDat.get_row( row_id );
  type = exdData->getField< int32_t >( row, 0 );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 1 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 2 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 3 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 4 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 5 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 6 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 7 ) );
  contentTalk.push_back( exdData->getField< uint32_t >( row, 8 ) );
}

Sapphire::Data::ContentRandomSelect::ContentRandomSelect( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentRandomSelectDat.get_row( row_id, subRow );
  name = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::ContentRoulette::ContentRoulette( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentRouletteDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  category = exdData->getField< std::string >( row, 1 );
  description = exdData->getField< std::string >( row, 3 );
  dutyType = exdData->getField< std::string >( row, 4 );
  isInDutyFinder = exdData->getField< bool >( row, 8 );
  openRule = exdData->getField< uint8_t >( row, 9 );
  requiredLevel = exdData->getField< uint8_t >( row, 11 );
  itemLevelRequired = exdData->getField< uint16_t >( row, 13 );
  icon = exdData->getField< uint32_t >( row, 15 );
  contentRouletteRoleBonus = exdData->getField< uint8_t >( row, 16 );
  rewardTomeA = exdData->getField< uint16_t >( row, 17 );
  rewardTomeB = exdData->getField< uint16_t >( row, 18 );
  rewardTomeC = exdData->getField< uint16_t >( row, 19 );
  sortKey = exdData->getField< uint8_t >( row, 22 );
  contentMemberType = exdData->getField< uint8_t >( row, 24 );
  requireAllDuties = exdData->getField< bool >( row, 34 );
  contentRouletteOpenRule = exdData->getField< uint8_t >( row, 36 );
  instanceContent = exdData->getField< uint16_t >( row, 37 );
}

Sapphire::Data::ContentRouletteOpenRule::ContentRouletteOpenRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentRouletteOpenRuleDat.get_row( row_id );
  type = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::ContentRouletteRoleBonus::ContentRouletteRoleBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentRouletteRoleBonusDat.get_row( row_id );
  itemRewardType = exdData->getField< uint32_t >( row, 6 );
  rewardAmount = exdData->getField< uint8_t >( row, 7 );
}

Sapphire::Data::ContentsNote::ContentsNote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentsNoteDat.get_row( row_id );
  contentType = exdData->getField< uint8_t >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  menuOrder = exdData->getField< uint8_t >( row, 2 );
  requiredAmount = exdData->getField< int32_t >( row, 3 );
  reward0 = exdData->getField< uint8_t >( row, 4 );
  expMultiplier = exdData->getField< int32_t >( row, 5 );
  reward1 = exdData->getField< uint8_t >( row, 6 );
  gilRward = exdData->getField< int32_t >( row, 7 );
  levelUnlock = exdData->getField< uint16_t >( row, 8 );
  howTo = exdData->getField< uint16_t >( row, 9 );
  reqUnlock = exdData->getField< uint32_t >( row, 10 );
  name = exdData->getField< std::string >( row, 11 );
  description = exdData->getField< std::string >( row, 12 );
  expCap = exdData->getField< int32_t >( row, 13 );
}

Sapphire::Data::ContentsTutorial::ContentsTutorial( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentsTutorialDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  page.push_back( exdData->getField< int32_t >( row, 2 ) );
  page.push_back( exdData->getField< int32_t >( row, 3 ) );
  page.push_back( exdData->getField< int32_t >( row, 4 ) );
  page.push_back( exdData->getField< int32_t >( row, 5 ) );
  page.push_back( exdData->getField< int32_t >( row, 6 ) );
  page.push_back( exdData->getField< int32_t >( row, 7 ) );
  page.push_back( exdData->getField< int32_t >( row, 8 ) );
  page.push_back( exdData->getField< int32_t >( row, 9 ) );
}

Sapphire::Data::ContentsTutorialPage::ContentsTutorialPage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentsTutorialPageDat.get_row( row_id );
  image = exdData->getField< int32_t >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::ContentTalk::ContentTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentTalkDat.get_row( row_id );
  contentTalkParam = exdData->getField< uint8_t >( row, 0 );
  text = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::ContentTalkParam::ContentTalkParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentTalkParamDat.get_row( row_id );
  param = exdData->getField< bool >( row, 0 );
  testAction = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::ContentType::ContentType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ContentTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  iconDutyFinder = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::CraftAction::CraftAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CraftActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  animationStart = exdData->getField< uint16_t >( row, 2 );
  animationEnd = exdData->getField< uint16_t >( row, 3 );
  icon = exdData->getField< uint16_t >( row, 4 );
  classJob = exdData->getField< int8_t >( row, 5 );
  classJobCategory = exdData->getField< uint8_t >( row, 6 );
  classJobLevel = exdData->getField< uint8_t >( row, 7 );
  questRequirement = exdData->getField< uint32_t >( row, 8 );
  specialist = exdData->getField< bool >( row, 9 );
  cost = exdData->getField< uint8_t >( row, 11 );
  cRP = exdData->getField< int32_t >( row, 12 );
  bSM = exdData->getField< int32_t >( row, 13 );
  aRM = exdData->getField< int32_t >( row, 14 );
  gSM = exdData->getField< int32_t >( row, 15 );
  lTW = exdData->getField< int32_t >( row, 16 );
  wVR = exdData->getField< int32_t >( row, 17 );
  aLC = exdData->getField< int32_t >( row, 18 );
  cUL = exdData->getField< int32_t >( row, 19 );
}

Sapphire::Data::CraftLeve::CraftLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CraftLeveDat.get_row( row_id );
  leve = exdData->getField< int32_t >( row, 0 );
  craftLeveTalk = exdData->getField< int32_t >( row, 1 );
  repeats = exdData->getField< uint8_t >( row, 2 );
}

Sapphire::Data::CraftLevelDifference::CraftLevelDifference( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CraftLevelDifferenceDat.get_row( row_id );
  difference = exdData->getField< int16_t >( row, 0 );
  progressFactor = exdData->getField< int16_t >( row, 1 );
  qualityFactor = exdData->getField< int16_t >( row, 2 );
}

Sapphire::Data::CraftType::CraftType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CraftTypeDat.get_row( row_id );
  mainPhysical = exdData->getField< uint8_t >( row, 0 );
  subPhysical = exdData->getField< uint8_t >( row, 1 );
  name = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::Credit::Credit( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CreditDat.get_row( row_id, subRow );
  roles1 = exdData->getField< uint16_t >( row, 1 );
  japaneseCast1 = exdData->getField< uint16_t >( row, 2 );
  englishCast1 = exdData->getField< uint16_t >( row, 3 );
  frenchCast1 = exdData->getField< uint16_t >( row, 4 );
  germanCast1 = exdData->getField< uint16_t >( row, 5 );
  roles2 = exdData->getField< uint16_t >( row, 6 );
  japaneseCast2 = exdData->getField< uint16_t >( row, 7 );
  englishCast2 = exdData->getField< uint16_t >( row, 8 );
  frenchCast2 = exdData->getField< uint16_t >( row, 9 );
  germanCast2 = exdData->getField< uint16_t >( row, 10 );
}

Sapphire::Data::CreditBackImage::CreditBackImage( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CreditBackImageDat.get_row( row_id, subRow );
  unknown54 = exdData->getField< bool >( row, 2 );
  backImage = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::CreditCast::CreditCast( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CreditCastDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CreditList::CreditList( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CreditListDat.get_row( row_id, subRow );
  scale = exdData->getField< uint16_t >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  font = exdData->getField< uint32_t >( row, 2 );
  cast = exdData->getField< uint32_t >( row, 5 );
}

Sapphire::Data::CreditListText::CreditListText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CreditListTextDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CustomTalk::CustomTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CustomTalkDat.get_row( row_id );
  iconActor = exdData->getField< uint32_t >( row, 0 );
  iconMap = exdData->getField< uint32_t >( row, 1 );
  name = exdData->getField< std::string >( row, 2 );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 3 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 4 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 5 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 6 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 7 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 8 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 9 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 10 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 11 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 12 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 13 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 14 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 15 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 16 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 17 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 18 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 19 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 20 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 21 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 22 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 23 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 24 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 25 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 26 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 27 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 28 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 29 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 30 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 31 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 32 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 33 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 34 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 35 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 36 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 37 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 38 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 39 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 40 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 41 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 42 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 43 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 44 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 45 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 46 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 47 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 48 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 49 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 50 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 51 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 52 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 53 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 54 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 55 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 56 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 57 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 58 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 59 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 60 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 61 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 62 ) );
  text = exdData->getField< bool >( row, 66 );
  unknown54 = exdData->getField< bool >( row, 77 );
}

Sapphire::Data::CustomTalkDynamicIcon::CustomTalkDynamicIcon( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CustomTalkDynamicIconDat.get_row( row_id, subRow );
  smallIcon = exdData->getField< uint32_t >( row, 0 );
  largeIcon = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::CustomTalkNestHandlers::CustomTalkNestHandlers( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CustomTalkNestHandlersDat.get_row( row_id, subRow );
  nestHandler = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::Cutscene::Cutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CutsceneDat.get_row( row_id );
  path = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CutsceneMotion::CutsceneMotion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CutsceneMotionDat.get_row( row_id );
  wALK_LOOP_SPEED = exdData->getField< float >( row, 0 );
  rUN_LOOP_SPEED = exdData->getField< float >( row, 1 );
  sLOWWALK_LOOP_SPEED = exdData->getField< float >( row, 2 );
  sLOWRUN_LOOP_SPEED = exdData->getField< float >( row, 3 );
  bATTLEWALK_LOOP_SPEED = exdData->getField< float >( row, 4 );
  bATTLERUN_LOOP_SPEED = exdData->getField< float >( row, 5 );
  dASH_LOOP_SPEED = exdData->getField< float >( row, 6 );
  tURN_CW90_FRAME = exdData->getField< uint8_t >( row, 7 );
  tURN_CCW90_FRAME = exdData->getField< uint8_t >( row, 8 );
  tURN_CW180_FRAME = exdData->getField< uint8_t >( row, 9 );
  tURN_CCW180_FRAME = exdData->getField< uint8_t >( row, 10 );
}

Sapphire::Data::CutsceneWorkIndex::CutsceneWorkIndex( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CutsceneWorkIndexDat.get_row( row_id );
  workIndex = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::CutScreenImage::CutScreenImage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CutScreenImageDat.get_row( row_id );
  type = exdData->getField< int16_t >( row, 0 );
  image = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::CycleTime::CycleTime( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_CycleTimeDat.get_row( row_id );
  firstCycle = exdData->getField< uint32_t >( row, 0 );
  cycle = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::DailySupplyItem::DailySupplyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DailySupplyItemDat.get_row( row_id );
}

Sapphire::Data::DawnContent::DawnContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DawnContentDat.get_row( row_id );
  content = exdData->getField< uint32_t >( row, 0 );
  exp = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::DawnGrowMember::DawnGrowMember( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DawnGrowMemberDat.get_row( row_id );
  member = exdData->getField< uint32_t >( row, 0 );
  imageName = exdData->getField< uint32_t >( row, 1 );
  bigImageOld = exdData->getField< uint32_t >( row, 2 );
  bigImageNew = exdData->getField< uint32_t >( row, 3 );
  smallImageOld = exdData->getField< uint32_t >( row, 4 );
  smallImageNew = exdData->getField< uint32_t >( row, 5 );
  _class = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::DawnMemberUIParam::DawnMemberUIParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DawnMemberUIParamDat.get_row( row_id );
  classSingular = exdData->getField< std::string >( row, 0 );
  voiceLine = exdData->getField< uint32_t >( row, 1 );
  classPlural = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::DawnQuestAnnounce::DawnQuestAnnounce( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DawnQuestAnnounceDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
  content = exdData->getField< uint8_t >( row, 1 );
  eNPC.push_back( exdData->getField< uint32_t >( row, 2 ) );
  eNPC.push_back( exdData->getField< uint32_t >( row, 3 ) );
  eNPC.push_back( exdData->getField< uint32_t >( row, 4 ) );
  eNPC.push_back( exdData->getField< uint32_t >( row, 5 ) );
  eNPC.push_back( exdData->getField< uint32_t >( row, 6 ) );
  eNPC.push_back( exdData->getField< uint32_t >( row, 7 ) );
}

Sapphire::Data::DawnQuestMember::DawnQuestMember( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DawnQuestMemberDat.get_row( row_id );
  member = exdData->getField< uint32_t >( row, 0 );
  imageName = exdData->getField< uint32_t >( row, 1 );
  bigImageOld = exdData->getField< uint32_t >( row, 2 );
  bigImageNew = exdData->getField< uint32_t >( row, 3 );
  _class = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::DeepDungeon::DeepDungeon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonDat.get_row( row_id );
  aetherpoolArm = exdData->getField< uint8_t >( row, 0 );
  aetherpoolArmor = exdData->getField< uint8_t >( row, 1 );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 2 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 3 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 4 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 5 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 6 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 7 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 8 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 9 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 10 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 11 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 12 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 13 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 14 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 15 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 16 ) );
  pomanderSlot.push_back( exdData->getField< uint8_t >( row, 17 ) );
  magiciteSlot.push_back( exdData->getField< uint8_t >( row, 18 ) );
  magiciteSlot.push_back( exdData->getField< uint8_t >( row, 19 ) );
  magiciteSlot.push_back( exdData->getField< uint8_t >( row, 20 ) );
  magiciteSlot.push_back( exdData->getField< uint8_t >( row, 21 ) );
  name = exdData->getField< std::string >( row, 22 );
  contentFinderConditionStart = exdData->getField< uint16_t >( row, 23 );
}

Sapphire::Data::DeepDungeonBan::DeepDungeonBan( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonBanDat.get_row( row_id );
  screenImage = exdData->getField< uint16_t >( row, 0 );
  logMessage = exdData->getField< uint16_t >( row, 1 );
  name = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::DeepDungeonDanger::DeepDungeonDanger( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonDangerDat.get_row( row_id );
  screenImage = exdData->getField< uint16_t >( row, 0 );
  logMessage = exdData->getField< uint16_t >( row, 1 );
  name = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::DeepDungeonEquipment::DeepDungeonEquipment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonEquipmentDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
  singular = exdData->getField< std::string >( row, 1 );
  adjective = exdData->getField< int8_t >( row, 2 );
  plural = exdData->getField< std::string >( row, 3 );
  possessivePronoun = exdData->getField< int8_t >( row, 4 );
  startsWithVowel = exdData->getField< int8_t >( row, 5 );
  pronoun = exdData->getField< int8_t >( row, 7 );
  article = exdData->getField< int8_t >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
  description = exdData->getField< std::string >( row, 10 );
}

Sapphire::Data::DeepDungeonFloorEffectUI::DeepDungeonFloorEffectUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonFloorEffectUIDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
  description = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::DeepDungeonItem::DeepDungeonItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonItemDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
  singular = exdData->getField< std::string >( row, 1 );
  adjective = exdData->getField< int8_t >( row, 2 );
  plural = exdData->getField< std::string >( row, 3 );
  possessivePronoun = exdData->getField< int8_t >( row, 4 );
  startsWithVowel = exdData->getField< int8_t >( row, 5 );
  pronoun = exdData->getField< int8_t >( row, 7 );
  article = exdData->getField< int8_t >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
  tooltip = exdData->getField< std::string >( row, 10 );
  action = exdData->getField< uint32_t >( row, 11 );
}

Sapphire::Data::DeepDungeonLayer::DeepDungeonLayer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonLayerDat.get_row( row_id );
  deepDungeon = exdData->getField< uint8_t >( row, 0 );
  floorSet = exdData->getField< uint8_t >( row, 1 );
  roomA = exdData->getField< uint16_t >( row, 2 );
  roomB = exdData->getField< uint16_t >( row, 3 );
  roomC = exdData->getField< uint16_t >( row, 4 );
  wepMinLv = exdData->getField< uint8_t >( row, 5 );
  armourMinLv = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::DeepDungeonMagicStone::DeepDungeonMagicStone( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonMagicStoneDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
  singular = exdData->getField< std::string >( row, 1 );
  adjective = exdData->getField< int8_t >( row, 2 );
  plural = exdData->getField< std::string >( row, 3 );
  possessivePronoun = exdData->getField< int8_t >( row, 4 );
  startsWithVowel = exdData->getField< int8_t >( row, 5 );
  pronoun = exdData->getField< int8_t >( row, 7 );
  article = exdData->getField< int8_t >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
  tooltip = exdData->getField< std::string >( row, 10 );
}

Sapphire::Data::DeepDungeonMap5X::DeepDungeonMap5X( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonMap5XDat.get_row( row_id, subRow );
  deepDungeonRoom.push_back( exdData->getField< uint16_t >( row, 0 ) );
  deepDungeonRoom.push_back( exdData->getField< uint16_t >( row, 1 ) );
  deepDungeonRoom.push_back( exdData->getField< uint16_t >( row, 2 ) );
  deepDungeonRoom.push_back( exdData->getField< uint16_t >( row, 3 ) );
  deepDungeonRoom.push_back( exdData->getField< uint16_t >( row, 4 ) );
}

Sapphire::Data::DeepDungeonRoom::DeepDungeonRoom( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonRoomDat.get_row( row_id );
  level.push_back( exdData->getField< uint32_t >( row, 0 ) );
  level.push_back( exdData->getField< uint32_t >( row, 1 ) );
  level.push_back( exdData->getField< uint32_t >( row, 2 ) );
  level.push_back( exdData->getField< uint32_t >( row, 3 ) );
  level.push_back( exdData->getField< uint32_t >( row, 4 ) );
}

Sapphire::Data::DeepDungeonStatus::DeepDungeonStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeepDungeonStatusDat.get_row( row_id );
  screenImage = exdData->getField< uint16_t >( row, 0 );
  logMessage = exdData->getField< uint16_t >( row, 1 );
  name = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::DefaultTalk::DefaultTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DefaultTalkDat.get_row( row_id );
  actionTimelinePose.push_back( exdData->getField< uint16_t >( row, 5 ) );
  actionTimelinePose.push_back( exdData->getField< uint16_t >( row, 6 ) );
  actionTimelinePose.push_back( exdData->getField< uint16_t >( row, 7 ) );
  text.push_back( exdData->getField< std::string >( row, 20 ) );
  text.push_back( exdData->getField< std::string >( row, 21 ) );
  text.push_back( exdData->getField< std::string >( row, 22 ) );
}

Sapphire::Data::DefaultTalkLipSyncType::DefaultTalkLipSyncType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DefaultTalkLipSyncTypeDat.get_row( row_id );
  actionTimeline = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::DeliveryQuest::DeliveryQuest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DeliveryQuestDat.get_row( row_id );
  quest = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::Description::Description( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DescriptionDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
  textLong = exdData->getField< std::string >( row, 1 );
  textShort = exdData->getField< std::string >( row, 2 );
  textCommentary = exdData->getField< std::string >( row, 3 );
  section = exdData->getField< uint32_t >( row, 5 );
}

Sapphire::Data::DescriptionPage::DescriptionPage( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DescriptionPageDat.get_row( row_id, subRow );
  quest = exdData->getField< uint32_t >( row, 0 );
  text1 = exdData->getField< uint16_t >( row, 1 );
  image1 = exdData->getField< uint32_t >( row, 2 );
  text2 = exdData->getField< uint16_t >( row, 3 );
  image2 = exdData->getField< uint32_t >( row, 4 );
  text3 = exdData->getField< uint16_t >( row, 5 );
  image3 = exdData->getField< uint32_t >( row, 6 );
  text4 = exdData->getField< uint16_t >( row, 7 );
  image4 = exdData->getField< uint32_t >( row, 8 );
  text5 = exdData->getField< uint16_t >( row, 9 );
  image5 = exdData->getField< uint32_t >( row, 10 );
  text6 = exdData->getField< uint16_t >( row, 11 );
  image6 = exdData->getField< uint32_t >( row, 12 );
  text7 = exdData->getField< uint16_t >( row, 13 );
  image7 = exdData->getField< uint32_t >( row, 14 );
  text8 = exdData->getField< uint16_t >( row, 15 );
  image8 = exdData->getField< uint32_t >( row, 16 );
  text9 = exdData->getField< uint16_t >( row, 17 );
  image9 = exdData->getField< uint32_t >( row, 18 );
}

Sapphire::Data::DescriptionSection::DescriptionSection( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DescriptionSectionDat.get_row( row_id, subRow );
  string = exdData->getField< uint16_t >( row, 0 );
  page = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::DescriptionString::DescriptionString( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DescriptionStringDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::DisposalShop::DisposalShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DisposalShopDat.get_row( row_id );
  shopName = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::DisposalShopFilterType::DisposalShopFilterType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DisposalShopFilterTypeDat.get_row( row_id );
  category = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::DisposalShopItem::DisposalShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DisposalShopItemDat.get_row( row_id, subRow );
  itemDisposed = exdData->getField< int32_t >( row, 0 );
  itemReceived = exdData->getField< int32_t >( row, 2 );
  quantityReceived = exdData->getField< uint32_t >( row, 4 );
}

Sapphire::Data::DpsChallenge::DpsChallenge( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DpsChallengeDat.get_row( row_id );
  playerLevel = exdData->getField< uint16_t >( row, 0 );
  placeName = exdData->getField< uint16_t >( row, 1 );
  icon = exdData->getField< uint32_t >( row, 2 );
  order = exdData->getField< uint16_t >( row, 3 );
  name = exdData->getField< std::string >( row, 4 );
  description = exdData->getField< std::string >( row, 5 );
}

Sapphire::Data::DpsChallengeOfficer::DpsChallengeOfficer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DpsChallengeOfficerDat.get_row( row_id );
  unlockQuest = exdData->getField< uint32_t >( row, 0 );
  challengeName.push_back( exdData->getField< uint16_t >( row, 1 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 2 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 3 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 4 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 5 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 6 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 7 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 8 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 9 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 10 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 11 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 12 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 13 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 14 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 15 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 16 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 17 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 18 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 19 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 20 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 21 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 22 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 23 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 24 ) );
  challengeName.push_back( exdData->getField< uint16_t >( row, 25 ) );
}

Sapphire::Data::DpsChallengeTransient::DpsChallengeTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DpsChallengeTransientDat.get_row( row_id );
  instanceContent = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::DynamicEvent::DynamicEvent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DynamicEventDat.get_row( row_id );
  eventType = exdData->getField< uint8_t >( row, 0 );
  enemyType = exdData->getField< uint8_t >( row, 1 );
  lGBEventObject = exdData->getField< uint32_t >( row, 4 );
  lGBMapRange = exdData->getField< uint32_t >( row, 5 );
  quest = exdData->getField< uint32_t >( row, 6 );
  singleBattle = exdData->getField< uint8_t >( row, 8 );
  announce = exdData->getField< uint32_t >( row, 9 );
  name = exdData->getField< std::string >( row, 10 );
  description = exdData->getField< std::string >( row, 11 );
}

Sapphire::Data::DynamicEventEnemyType::DynamicEventEnemyType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DynamicEventEnemyTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::DynamicEventSingleBattle::DynamicEventSingleBattle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DynamicEventSingleBattleDat.get_row( row_id );
  actionIcon = exdData->getField< int32_t >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  text = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::DynamicEventType::DynamicEventType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_DynamicEventTypeDat.get_row( row_id );
  iconObjective0 = exdData->getField< uint32_t >( row, 0 );
  iconObjective1 = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::EmjAddon::EmjAddon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EmjAddonDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::EmjDani::EmjDani( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EmjDaniDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::Emote::Emote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EmoteDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 1 ) );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 2 ) );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 3 ) );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 4 ) );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 5 ) );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 6 ) );
  actionTimeline.push_back( exdData->getField< uint16_t >( row, 7 ) );
  emoteCategory = exdData->getField< uint8_t >( row, 11 );
  emoteMode = exdData->getField< uint8_t >( row, 12 );
  hasCancelEmote = exdData->getField< bool >( row, 15 );
  drawsWeapon = exdData->getField< bool >( row, 16 );
  order = exdData->getField< uint16_t >( row, 17 );
  textCommand = exdData->getField< int32_t >( row, 18 );
  icon = exdData->getField< uint16_t >( row, 19 );
  logMessageTargeted = exdData->getField< uint16_t >( row, 20 );
  logMessageUntargeted = exdData->getField< uint16_t >( row, 21 );
  unlockLink = exdData->getField< uint32_t >( row, 22 );
}

Sapphire::Data::EmoteCategory::EmoteCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EmoteCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::EmoteMode::EmoteMode( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EmoteModeDat.get_row( row_id );
  startEmote = exdData->getField< uint16_t >( row, 0 );
  endEmote = exdData->getField< uint16_t >( row, 1 );
  move = exdData->getField< bool >( row, 2 );
  camera = exdData->getField< bool >( row, 3 );
  endOnRotate = exdData->getField< bool >( row, 4 );
  endOnEmote = exdData->getField< bool >( row, 5 );
  conditionMode = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::ENpcBase::ENpcBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ENpcBaseDat.get_row( row_id );
  eventHandler = exdData->getField< uint16_t >( row, 0 );
  important = exdData->getField< bool >( row, 1 );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 2 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 3 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 4 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 5 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 6 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 7 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 8 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 9 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 10 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 11 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 12 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 13 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 14 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 15 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 16 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 17 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 18 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 19 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 20 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 21 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 22 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 23 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 24 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 25 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 26 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 27 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 28 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 29 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 30 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 31 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 32 ) );
  eNpcData.push_back( exdData->getField< uint32_t >( row, 33 ) );
  scale = exdData->getField< float >( row, 34 );
  modelChara = exdData->getField< uint16_t >( row, 35 );
  race = exdData->getField< uint8_t >( row, 36 );
  gender = exdData->getField< uint8_t >( row, 37 );
  bodyType = exdData->getField< uint8_t >( row, 38 );
  height = exdData->getField< uint8_t >( row, 39 );
  tribe = exdData->getField< uint8_t >( row, 40 );
  face = exdData->getField< uint8_t >( row, 41 );
  hairStyle = exdData->getField< uint8_t >( row, 42 );
  hairHighlight = exdData->getField< uint8_t >( row, 43 );
  skinColor = exdData->getField< uint8_t >( row, 44 );
  eyeHeterochromia = exdData->getField< uint8_t >( row, 45 );
  hairColor = exdData->getField< uint8_t >( row, 46 );
  hairHighlightColor = exdData->getField< uint8_t >( row, 47 );
  facialFeature = exdData->getField< uint8_t >( row, 48 );
  facialFeatureColor = exdData->getField< uint8_t >( row, 49 );
  eyebrows = exdData->getField< uint8_t >( row, 50 );
  eyeColor = exdData->getField< uint8_t >( row, 51 );
  eyeShape = exdData->getField< uint8_t >( row, 52 );
  nose = exdData->getField< uint8_t >( row, 53 );
  jaw = exdData->getField< uint8_t >( row, 54 );
  mouth = exdData->getField< uint8_t >( row, 55 );
  lipColor = exdData->getField< uint8_t >( row, 56 );
  bustOrTone1 = exdData->getField< uint8_t >( row, 57 );
  extraFeature1 = exdData->getField< uint8_t >( row, 58 );
  extraFeature2OrBust = exdData->getField< uint8_t >( row, 59 );
  facePaint = exdData->getField< uint8_t >( row, 60 );
  facePaintColor = exdData->getField< uint8_t >( row, 61 );
  npcEquip = exdData->getField< uint16_t >( row, 63 );
  behavior = exdData->getField< uint16_t >( row, 64 );
  modelMainHand = exdData->getField< uint64_t >( row, 65 );
  dyeMainHand = exdData->getField< uint8_t >( row, 66 );
  modelOffHand = exdData->getField< uint64_t >( row, 67 );
  dyeOffHand = exdData->getField< uint8_t >( row, 68 );
  modelHead = exdData->getField< uint32_t >( row, 69 );
  dyeHead = exdData->getField< uint8_t >( row, 70 );
  visor = exdData->getField< bool >( row, 71 );
  modelBody = exdData->getField< uint32_t >( row, 72 );
  dyeBody = exdData->getField< uint8_t >( row, 73 );
  modelHands = exdData->getField< uint32_t >( row, 74 );
  dyeHands = exdData->getField< uint8_t >( row, 75 );
  modelLegs = exdData->getField< uint32_t >( row, 76 );
  dyeLegs = exdData->getField< uint8_t >( row, 77 );
  modelFeet = exdData->getField< uint32_t >( row, 78 );
  dyeFeet = exdData->getField< uint8_t >( row, 79 );
  modelEars = exdData->getField< uint32_t >( row, 80 );
  dyeEars = exdData->getField< uint8_t >( row, 81 );
  modelNeck = exdData->getField< uint32_t >( row, 82 );
  dyeNeck = exdData->getField< uint8_t >( row, 83 );
  modelWrists = exdData->getField< uint32_t >( row, 84 );
  dyeWrists = exdData->getField< uint8_t >( row, 85 );
  modelLeftRing = exdData->getField< uint32_t >( row, 86 );
  dyeLeftRing = exdData->getField< uint8_t >( row, 87 );
  modelRightRing = exdData->getField< uint32_t >( row, 88 );
  dyeRightRing = exdData->getField< uint8_t >( row, 89 );
  invisibility = exdData->getField< uint8_t >( row, 90 );
  balloon = exdData->getField< uint16_t >( row, 91 );
  notRewriteHeight = exdData->getField< bool >( row, 92 );
  defaultBalloon = exdData->getField< uint8_t >( row, 93 );
}

Sapphire::Data::ENpcDressUp::ENpcDressUp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ENpcDressUpDat.get_row( row_id );
  eNpcDressUpDress = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::ENpcDressUpDress::ENpcDressUpDress( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ENpcDressUpDressDat.get_row( row_id, subRow );
  addedIn530 = exdData->getField< bool >( row, 5 );
  eNpc = exdData->getField< uint32_t >( row, 7 );
  addedIn531 = exdData->getField< uint16_t >( row, 8 );
  behavior = exdData->getField< uint16_t >( row, 9 );
  addedIn532 = exdData->getField< uint8_t >( row, 36 );
  modelMainHand = exdData->getField< uint64_t >( row, 37 );
  dyeMainHand = exdData->getField< uint8_t >( row, 38 );
  modelOffHand = exdData->getField< uint64_t >( row, 39 );
  dyeOffHand = exdData->getField< uint8_t >( row, 40 );
  modelHead = exdData->getField< uint32_t >( row, 41 );
  dyeHead = exdData->getField< uint8_t >( row, 42 );
  modelBody = exdData->getField< uint32_t >( row, 43 );
  dyeBody = exdData->getField< uint8_t >( row, 44 );
  modelHands = exdData->getField< uint32_t >( row, 45 );
  dyeHands = exdData->getField< uint8_t >( row, 46 );
  modelLegs = exdData->getField< uint32_t >( row, 47 );
  dyeLegs = exdData->getField< uint8_t >( row, 48 );
  modelFeet = exdData->getField< uint32_t >( row, 49 );
  dyeFeet = exdData->getField< uint8_t >( row, 50 );
}

Sapphire::Data::ENpcResident::ENpcResident( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ENpcResidentDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  title = exdData->getField< std::string >( row, 8 );
  map = exdData->getField< uint8_t >( row, 9 );
}

Sapphire::Data::EObj::EObj( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EObjDat.get_row( row_id );
  popType = exdData->getField< uint8_t >( row, 8 );
  data = exdData->getField< uint32_t >( row, 9 );
  invisibility = exdData->getField< uint8_t >( row, 10 );
  sgbPath = exdData->getField< uint16_t >( row, 11 );
  eyeCollision = exdData->getField< bool >( row, 12 );
  directorControl = exdData->getField< bool >( row, 13 );
  target = exdData->getField< bool >( row, 14 );
  eventHighAddition = exdData->getField< uint8_t >( row, 15 );
  addedIn53 = exdData->getField< bool >( row, 18 );
}

Sapphire::Data::EObjName::EObjName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EObjNameDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
}

Sapphire::Data::EquipRaceCategory::EquipRaceCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EquipRaceCategoryDat.get_row( row_id );
  hyur = exdData->getField< bool >( row, 0 );
  elezen = exdData->getField< bool >( row, 1 );
  lalafell = exdData->getField< bool >( row, 2 );
  miqote = exdData->getField< bool >( row, 3 );
  roegadyn = exdData->getField< bool >( row, 4 );
  auRa = exdData->getField< bool >( row, 5 );
  male = exdData->getField< bool >( row, 8 );
  female = exdData->getField< bool >( row, 9 );
}

Sapphire::Data::EquipSlotCategory::EquipSlotCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EquipSlotCategoryDat.get_row( row_id );
  mainHand = exdData->getField< int8_t >( row, 0 );
  offHand = exdData->getField< int8_t >( row, 1 );
  head = exdData->getField< int8_t >( row, 2 );
  body = exdData->getField< int8_t >( row, 3 );
  gloves = exdData->getField< int8_t >( row, 4 );
  waist = exdData->getField< int8_t >( row, 5 );
  legs = exdData->getField< int8_t >( row, 6 );
  feet = exdData->getField< int8_t >( row, 7 );
  ears = exdData->getField< int8_t >( row, 8 );
  neck = exdData->getField< int8_t >( row, 9 );
  wrists = exdData->getField< int8_t >( row, 10 );
  fingerL = exdData->getField< int8_t >( row, 11 );
  fingerR = exdData->getField< int8_t >( row, 12 );
  soulCrystal = exdData->getField< int8_t >( row, 13 );
}

Sapphire::Data::EurekaAetherItem::EurekaAetherItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaAetherItemDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  name = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::EurekaAethernet::EurekaAethernet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaAethernetDat.get_row( row_id );
  location = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::EurekaGrowData::EurekaGrowData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaGrowDataDat.get_row( row_id );
  baseResistance = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::EurekaLogosMixerProbability::EurekaLogosMixerProbability( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaLogosMixerProbabilityDat.get_row( row_id );
  probability = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::EurekaMagiaAction::EurekaMagiaAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaMagiaActionDat.get_row( row_id );
  action = exdData->getField< uint32_t >( row, 0 );
  maxUses = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::EurekaMagiciteItem::EurekaMagiciteItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaMagiciteItemDat.get_row( row_id );
  eurekaMagiciteItemType = exdData->getField< uint8_t >( row, 0 );
  classJobCategory = exdData->getField< uint8_t >( row, 1 );
  item = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::EurekaMagiciteItemType::EurekaMagiciteItemType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaMagiciteItemTypeDat.get_row( row_id );
  type = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::EurekaSphereElementAdjust::EurekaSphereElementAdjust( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EurekaSphereElementAdjustDat.get_row( row_id );
  powerModifier = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::EventAction::EventAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< uint16_t >( row, 1 );
  castTime = exdData->getField< uint8_t >( row, 2 );
  animation.push_back( exdData->getField< uint16_t >( row, 3 ) );
  animation.push_back( exdData->getField< uint16_t >( row, 4 ) );
  animation.push_back( exdData->getField< uint16_t >( row, 5 ) );
}

Sapphire::Data::EventIconPriority::EventIconPriority( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventIconPriorityDat.get_row( row_id );
  icon.push_back( exdData->getField< uint32_t >( row, 0 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 1 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 2 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 3 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 4 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 5 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 6 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 7 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 8 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 9 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 10 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 11 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 12 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 13 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 14 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 15 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 16 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 17 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 18 ) );
}

Sapphire::Data::EventIconType::EventIconType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventIconTypeDat.get_row( row_id );
  npcIconAvailable = exdData->getField< uint32_t >( row, 0 );
  mapIconAvailable = exdData->getField< uint32_t >( row, 1 );
  npcIconInvalid = exdData->getField< uint32_t >( row, 2 );
  mapIconInvalid = exdData->getField< uint32_t >( row, 3 );
  iconRange = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::EventItem::EventItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventItemDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  name = exdData->getField< std::string >( row, 9 );
  icon = exdData->getField< uint16_t >( row, 10 );
  action = exdData->getField< uint16_t >( row, 11 );
  stackSize = exdData->getField< uint8_t >( row, 12 );
  quest = exdData->getField< uint32_t >( row, 14 );
  castTime = exdData->getField< uint8_t >( row, 15 );
  castTimeline = exdData->getField< uint8_t >( row, 16 );
  timeline = exdData->getField< uint8_t >( row, 17 );
}

Sapphire::Data::EventItemCastTimeline::EventItemCastTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventItemCastTimelineDat.get_row( row_id );
  actionTimeline = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::EventItemHelp::EventItemHelp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventItemHelpDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::EventItemTimeline::EventItemTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventItemTimelineDat.get_row( row_id );
  actionTimeline = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::EventSystemDefine::EventSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_EventSystemDefineDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
  defineValue = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::ExportedSG::ExportedSG( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ExportedSGDat.get_row( row_id );
  sgbPath = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ExVersion::ExVersion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ExVersionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  acceptJingle = exdData->getField< uint16_t >( row, 1 );
  completeJingle = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::Fate::Fate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FateDat.get_row( row_id );
  eurekaFate = exdData->getField< uint8_t >( row, 0 );
  rule = exdData->getField< uint8_t >( row, 1 );
  fateRuleEx = exdData->getField< uint16_t >( row, 2 );
  location = exdData->getField< uint32_t >( row, 3 );
  classJobLevel = exdData->getField< uint8_t >( row, 4 );
  classJobLevelMax = exdData->getField< uint8_t >( row, 5 );
  eventItem = exdData->getField< uint32_t >( row, 6 );
  typeToDoValue.push_back( exdData->getField< uint8_t >( row, 7 ) );
  typeToDoValue.push_back( exdData->getField< uint8_t >( row, 8 ) );
  typeToDoValue.push_back( exdData->getField< uint8_t >( row, 9 ) );
  iconObjective = exdData->getField< uint32_t >( row, 10 );
  iconMap = exdData->getField< uint32_t >( row, 11 );
  iconInactiveMap = exdData->getField< uint32_t >( row, 12 );
  music = exdData->getField< int32_t >( row, 13 );
  lGBGuardNPCLocation = exdData->getField< uint32_t >( row, 14 );
  screenImageAccept = exdData->getField< uint16_t >( row, 15 );
  screenImageComplete = exdData->getField< uint16_t >( row, 16 );
  screenImageFailed = exdData->getField< uint16_t >( row, 17 );
  specialFate = exdData->getField< bool >( row, 20 );
  givenStatus = exdData->getField< uint16_t >( row, 22 );
  adventEvent = exdData->getField< bool >( row, 24 );
  moonFaireEvent = exdData->getField< bool >( row, 25 );
  fATEChain = exdData->getField< uint32_t >( row, 27 );
  name = exdData->getField< std::string >( row, 30 );
  description = exdData->getField< std::string >( row, 31 );
  objective = exdData->getField< std::string >( row, 32 );
  statusText.push_back( exdData->getField< std::string >( row, 33 ) );
  statusText.push_back( exdData->getField< std::string >( row, 34 ) );
  statusText.push_back( exdData->getField< std::string >( row, 35 ) );
  arrayIndex = exdData->getField< uint32_t >( row, 36 );
  reqEventItem = exdData->getField< uint32_t >( row, 38 );
  turnInEventItem = exdData->getField< uint32_t >( row, 39 );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 40 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 41 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 42 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 43 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 44 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 45 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 46 ) );
  objectiveIcon.push_back( exdData->getField< uint16_t >( row, 47 ) );
}

Sapphire::Data::FateEvent::FateEvent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FateEventDat.get_row( row_id );
  turn.push_back( exdData->getField< uint8_t >( row, 0 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 1 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 2 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 3 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 4 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 5 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 6 ) );
  turn.push_back( exdData->getField< uint8_t >( row, 7 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 8 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 9 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 10 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 11 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 12 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 13 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 14 ) );
  gesture.push_back( exdData->getField< uint32_t >( row, 15 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 16 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 17 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 18 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 19 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 20 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 21 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 22 ) );
  lipSync.push_back( exdData->getField< int32_t >( row, 23 ) );
  facial.push_back( exdData->getField< int32_t >( row, 24 ) );
  facial.push_back( exdData->getField< int32_t >( row, 25 ) );
  facial.push_back( exdData->getField< int32_t >( row, 26 ) );
  facial.push_back( exdData->getField< int32_t >( row, 27 ) );
  facial.push_back( exdData->getField< int32_t >( row, 28 ) );
  facial.push_back( exdData->getField< int32_t >( row, 29 ) );
  facial.push_back( exdData->getField< int32_t >( row, 30 ) );
  facial.push_back( exdData->getField< int32_t >( row, 31 ) );
  shape.push_back( exdData->getField< int32_t >( row, 32 ) );
  shape.push_back( exdData->getField< int32_t >( row, 33 ) );
  shape.push_back( exdData->getField< int32_t >( row, 34 ) );
  shape.push_back( exdData->getField< int32_t >( row, 35 ) );
  shape.push_back( exdData->getField< int32_t >( row, 36 ) );
  shape.push_back( exdData->getField< int32_t >( row, 37 ) );
  shape.push_back( exdData->getField< int32_t >( row, 38 ) );
  shape.push_back( exdData->getField< int32_t >( row, 39 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 40 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 41 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 42 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 43 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 44 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 45 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 46 ) );
  isAutoShake.push_back( exdData->getField< bool >( row, 47 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 48 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 49 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 50 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 51 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 52 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 53 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 54 ) );
  widgetType.push_back( exdData->getField< uint8_t >( row, 55 ) );
  text.push_back( exdData->getField< std::string >( row, 56 ) );
  text.push_back( exdData->getField< std::string >( row, 57 ) );
  text.push_back( exdData->getField< std::string >( row, 58 ) );
  text.push_back( exdData->getField< std::string >( row, 59 ) );
  text.push_back( exdData->getField< std::string >( row, 60 ) );
  text.push_back( exdData->getField< std::string >( row, 61 ) );
  text.push_back( exdData->getField< std::string >( row, 62 ) );
  text.push_back( exdData->getField< std::string >( row, 63 ) );
}

Sapphire::Data::FateMode::FateMode( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FateModeDat.get_row( row_id );
  motivationIcon = exdData->getField< uint32_t >( row, 1 );
  motivationMapMarker = exdData->getField< uint32_t >( row, 2 );
  objectiveIcon = exdData->getField< uint32_t >( row, 3 );
  objectiveMapMarker = exdData->getField< uint32_t >( row, 4 );
}

Sapphire::Data::FateProgressUI::FateProgressUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FateProgressUIDat.get_row( row_id );
  location = exdData->getField< int32_t >( row, 0 );
  achievement = exdData->getField< int32_t >( row, 1 );
  reqFatesToRank2 = exdData->getField< uint8_t >( row, 2 );
  reqFatesToRank3 = exdData->getField< uint8_t >( row, 3 );
  displayOrder = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::FateTokenType::FateTokenType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FateTokenTypeDat.get_row( row_id );
  currency = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::FCActivity::FCActivity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCActivityDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
  selfKind = exdData->getField< uint8_t >( row, 1 );
  targetKind = exdData->getField< uint8_t >( row, 2 );
  numParam = exdData->getField< uint8_t >( row, 3 );
  fCActivityCategory = exdData->getField< uint8_t >( row, 4 );
  iconType = exdData->getField< int8_t >( row, 5 );
}

Sapphire::Data::FCActivityCategory::FCActivityCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCActivityCategoryDat.get_row( row_id );
  priority = exdData->getField< uint8_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::FCAuthority::FCAuthority( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCAuthorityDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  fCAuthorityCategory = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::FCAuthorityCategory::FCAuthorityCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCAuthorityCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::FCChestName::FCChestName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCChestNameDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::FCCrestSymbol::FCCrestSymbol( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCCrestSymbolDat.get_row( row_id );
  colorNum = exdData->getField< uint8_t >( row, 0 );
  fCRight = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::FccShop::FccShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FccShopDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::FCHierarchy::FCHierarchy( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCHierarchyDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::FCProfile::FCProfile( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCProfileDat.get_row( row_id );
  priority = exdData->getField< uint8_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::FCRank::FCRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCRankDat.get_row( row_id );
  nextPoint = exdData->getField< uint32_t >( row, 0 );
  currentPoint = exdData->getField< uint32_t >( row, 1 );
  rights = exdData->getField< uint16_t >( row, 2 );
  fCActionActiveNum = exdData->getField< uint8_t >( row, 5 );
  fCActionStockNum = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::FCReputation::FCReputation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCReputationDat.get_row( row_id );
  pointsToNext = exdData->getField< uint32_t >( row, 0 );
  requiredPoints = exdData->getField< uint32_t >( row, 1 );
  discountRate = exdData->getField< uint8_t >( row, 2 );
  color = exdData->getField< uint32_t >( row, 3 );
  name = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::FCRights::FCRights( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FCRightsDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< uint16_t >( row, 2 );
  fCRank = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::Festival::Festival( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FestivalDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::FieldMarker::FieldMarker( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FieldMarkerDat.get_row( row_id );
  vFX = exdData->getField< int32_t >( row, 0 );
  icon = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::FishingRecordType::FishingRecordType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FishingRecordTypeDat.get_row( row_id );
  addon = exdData->getField< int32_t >( row, 0 );
  rankBRequirement = exdData->getField< uint16_t >( row, 1 );
  rankARequirement = exdData->getField< uint16_t >( row, 2 );
  rankAARequirement = exdData->getField< uint16_t >( row, 3 );
  rankAAARequirement = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::FishingRecordTypeTransient::FishingRecordTypeTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FishingRecordTypeTransientDat.get_row( row_id );
  image = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::FishingSpot::FishingSpot( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FishingSpotDat.get_row( row_id );
  gatheringLevel = exdData->getField< uint8_t >( row, 0 );
  bigFishOnReach = exdData->getField< std::string >( row, 1 );
  bigFishOnEnd = exdData->getField< std::string >( row, 2 );
  fishingSpotCategory = exdData->getField< uint8_t >( row, 3 );
  rare = exdData->getField< bool >( row, 4 );
  territoryType = exdData->getField< uint16_t >( row, 5 );
  placeNameMain = exdData->getField< uint16_t >( row, 6 );
  placeNameSub = exdData->getField< uint16_t >( row, 7 );
  x = exdData->getField< int16_t >( row, 8 );
  z = exdData->getField< int16_t >( row, 9 );
  radius = exdData->getField< uint16_t >( row, 10 );
  item.push_back( exdData->getField< int32_t >( row, 12 ) );
  item.push_back( exdData->getField< int32_t >( row, 13 ) );
  item.push_back( exdData->getField< int32_t >( row, 14 ) );
  item.push_back( exdData->getField< int32_t >( row, 15 ) );
  item.push_back( exdData->getField< int32_t >( row, 16 ) );
  item.push_back( exdData->getField< int32_t >( row, 17 ) );
  item.push_back( exdData->getField< int32_t >( row, 18 ) );
  item.push_back( exdData->getField< int32_t >( row, 19 ) );
  item.push_back( exdData->getField< int32_t >( row, 20 ) );
  item.push_back( exdData->getField< int32_t >( row, 21 ) );
  placeName = exdData->getField< uint16_t >( row, 22 );
  order = exdData->getField< uint8_t >( row, 23 );
}

Sapphire::Data::FishParameter::FishParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FishParameterDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
  item = exdData->getField< int32_t >( row, 1 );
  gatheringItemLevel = exdData->getField< uint16_t >( row, 2 );
  isHidden = exdData->getField< bool >( row, 4 );
  fishingRecordType = exdData->getField< uint8_t >( row, 6 );
  territoryType = exdData->getField< int32_t >( row, 7 );
  gatheringSubCategory = exdData->getField< uint16_t >( row, 8 );
  isInLog = exdData->getField< bool >( row, 9 );
  timeRestricted = exdData->getField< bool >( row, 10 );
  weatherRestricted = exdData->getField< bool >( row, 11 );
}

Sapphire::Data::Frontline03::Frontline03( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_Frontline03Dat.get_row( row_id );
  emptyIcon.push_back( exdData->getField< uint32_t >( row, 9 ) );
  emptyIcon.push_back( exdData->getField< uint32_t >( row, 10 ) );
  emptyIcon.push_back( exdData->getField< uint32_t >( row, 11 ) );
  maelstromIcon.push_back( exdData->getField< uint32_t >( row, 12 ) );
  maelstromIcon.push_back( exdData->getField< uint32_t >( row, 13 ) );
  maelstromIcon.push_back( exdData->getField< uint32_t >( row, 14 ) );
  twinAdderIcon.push_back( exdData->getField< uint32_t >( row, 15 ) );
  twinAdderIcon.push_back( exdData->getField< uint32_t >( row, 16 ) );
  twinAdderIcon.push_back( exdData->getField< uint32_t >( row, 17 ) );
  immortalFlamesIcon.push_back( exdData->getField< uint32_t >( row, 18 ) );
  immortalFlamesIcon.push_back( exdData->getField< uint32_t >( row, 19 ) );
  immortalFlamesIcon.push_back( exdData->getField< uint32_t >( row, 20 ) );
}

Sapphire::Data::Frontline04::Frontline04( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_Frontline04Dat.get_row( row_id );
  level1 = exdData->getField< int32_t >( row, 0 );
  level2 = exdData->getField< int32_t >( row, 1 );
  level3 = exdData->getField< int32_t >( row, 2 );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 6 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 7 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 8 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 9 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 10 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 11 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 12 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 13 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 14 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 15 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 16 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 17 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 18 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 19 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 20 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 21 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 22 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 23 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 24 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 25 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 26 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 27 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 28 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 29 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 30 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 31 ) );
  unknownLevel.push_back( exdData->getField< int32_t >( row, 32 ) );
}

Sapphire::Data::FurnitureCatalogCategory::FurnitureCatalogCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FurnitureCatalogCategoryDat.get_row( row_id );
  category = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::FurnitureCatalogItemList::FurnitureCatalogItemList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_FurnitureCatalogItemListDat.get_row( row_id );
  category = exdData->getField< uint16_t >( row, 0 );
  item = exdData->getField< int32_t >( row, 1 );
  patch = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::GardeningSeed::GardeningSeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GardeningSeedDat.get_row( row_id );
  item = exdData->getField< uint32_t >( row, 0 );
  modelID = exdData->getField< uint16_t >( row, 1 );
  icon = exdData->getField< uint32_t >( row, 2 );
  sE = exdData->getField< bool >( row, 3 );
}

Sapphire::Data::GatheringCondition::GatheringCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringConditionDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GatheringExp::GatheringExp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringExpDat.get_row( row_id );
  exp = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::GatheringItem::GatheringItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringItemDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  gatheringItemLevel = exdData->getField< uint16_t >( row, 1 );
  isHidden = exdData->getField< bool >( row, 4 );
}

Sapphire::Data::GatheringItemLevelConvertTable::GatheringItemLevelConvertTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringItemLevelConvertTableDat.get_row( row_id );
  gatheringItemLevel = exdData->getField< uint8_t >( row, 0 );
  stars = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::GatheringItemPoint::GatheringItemPoint( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringItemPointDat.get_row( row_id, subRow );
  gatheringPoint = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::GatheringLeve::GatheringLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringLeveDat.get_row( row_id );
  route.push_back( exdData->getField< int32_t >( row, 0 ) );
  route.push_back( exdData->getField< int32_t >( row, 1 ) );
  route.push_back( exdData->getField< int32_t >( row, 2 ) );
  route.push_back( exdData->getField< int32_t >( row, 3 ) );
  requiredItem0 = exdData->getField< int32_t >( row, 4 );
  requiredItemQty0 = exdData->getField< uint8_t >( row, 5 );
  requiredItem1 = exdData->getField< int32_t >( row, 6 );
  requiredItemQty1 = exdData->getField< uint8_t >( row, 7 );
  requiredItem2 = exdData->getField< int32_t >( row, 8 );
  requiredItemQty2 = exdData->getField< uint8_t >( row, 9 );
  requiredItem3 = exdData->getField< int32_t >( row, 10 );
  requiredItemQty3 = exdData->getField< uint8_t >( row, 11 );
  itemNumber = exdData->getField< uint8_t >( row, 12 );
  rule = exdData->getField< int32_t >( row, 13 );
  varient = exdData->getField< uint8_t >( row, 14 );
  objective0 = exdData->getField< uint16_t >( row, 15 );
  objective1 = exdData->getField< uint16_t >( row, 16 );
  bNpcEntry = exdData->getField< int32_t >( row, 17 );
  useSecondaryTool = exdData->getField< bool >( row, 18 );
}

Sapphire::Data::GatheringLeveRoute::GatheringLeveRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringLeveRouteDat.get_row( row_id );
}

Sapphire::Data::GatheringLeveRule::GatheringLeveRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringLeveRuleDat.get_row( row_id );
  rule = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GatheringNotebookList::GatheringNotebookList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringNotebookListDat.get_row( row_id );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 1 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 2 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 3 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 4 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 5 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 6 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 7 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 8 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 9 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 10 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 11 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 12 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 13 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 14 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 15 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 16 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 17 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 18 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 19 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 20 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 21 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 22 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 23 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 24 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 25 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 26 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 27 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 28 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 29 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 30 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 31 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 32 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 33 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 34 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 35 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 36 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 37 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 38 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 39 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 40 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 41 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 42 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 43 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 44 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 45 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 46 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 47 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 48 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 49 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 50 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 51 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 52 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 53 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 54 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 55 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 56 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 57 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 58 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 59 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 60 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 61 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 62 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 63 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 64 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 65 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 66 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 67 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 68 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 69 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 70 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 71 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 72 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 73 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 74 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 75 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 76 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 77 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 78 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 79 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 80 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 81 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 82 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 83 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 84 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 85 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 86 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 87 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 88 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 89 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 90 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 91 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 92 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 93 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 94 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 95 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 96 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 97 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 98 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 99 ) );
  gatheringItem.push_back( exdData->getField< int32_t >( row, 100 ) );
}

Sapphire::Data::GatheringPoint::GatheringPoint( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringPointDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  gatheringPointBase = exdData->getField< int32_t >( row, 1 );
  count = exdData->getField< uint8_t >( row, 2 );
  gatheringPointBonus.push_back( exdData->getField< uint16_t >( row, 3 ) );
  gatheringPointBonus.push_back( exdData->getField< uint16_t >( row, 4 ) );
  territoryType = exdData->getField< uint16_t >( row, 5 );
  placeName = exdData->getField< uint16_t >( row, 6 );
  gatheringSubCategory = exdData->getField< uint16_t >( row, 7 );
}

Sapphire::Data::GatheringPointBase::GatheringPointBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringPointBaseDat.get_row( row_id );
  gatheringType = exdData->getField< int32_t >( row, 0 );
  gatheringLevel = exdData->getField< uint8_t >( row, 1 );
  item.push_back( exdData->getField< int32_t >( row, 2 ) );
  item.push_back( exdData->getField< int32_t >( row, 3 ) );
  item.push_back( exdData->getField< int32_t >( row, 4 ) );
  item.push_back( exdData->getField< int32_t >( row, 5 ) );
  item.push_back( exdData->getField< int32_t >( row, 6 ) );
  item.push_back( exdData->getField< int32_t >( row, 7 ) );
  item.push_back( exdData->getField< int32_t >( row, 8 ) );
  item.push_back( exdData->getField< int32_t >( row, 9 ) );
  isLimited = exdData->getField< bool >( row, 10 );
}

Sapphire::Data::GatheringPointBonus::GatheringPointBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringPointBonusDat.get_row( row_id );
  condition = exdData->getField< uint8_t >( row, 0 );
  conditionValue = exdData->getField< uint32_t >( row, 1 );
  bonusType = exdData->getField< uint8_t >( row, 3 );
  bonusValue = exdData->getField< uint16_t >( row, 4 );
  unknown53 = exdData->getField< bool >( row, 6 );
  unknown54 = exdData->getField< uint32_t >( row, 7 );
}

Sapphire::Data::GatheringPointBonusType::GatheringPointBonusType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringPointBonusTypeDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GatheringPointName::GatheringPointName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringPointNameDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
}

Sapphire::Data::GatheringPointTransient::GatheringPointTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringPointTransientDat.get_row( row_id );
  ephemeralStartTime = exdData->getField< uint16_t >( row, 0 );
  ephemeralEndTime = exdData->getField< uint16_t >( row, 1 );
  gatheringRarePopTimeTable = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::GatheringRarePopTimeTable::GatheringRarePopTimeTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringRarePopTimeTableDat.get_row( row_id );
}

Sapphire::Data::GatheringSubCategory::GatheringSubCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringSubCategoryDat.get_row( row_id );
  gatheringType = exdData->getField< uint8_t >( row, 0 );
  classJob = exdData->getField< uint8_t >( row, 1 );
  division = exdData->getField< uint16_t >( row, 3 );
  item = exdData->getField< int32_t >( row, 4 );
  folkloreBook = exdData->getField< std::string >( row, 5 );
}

Sapphire::Data::GatheringType::GatheringType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GatheringTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  iconMain = exdData->getField< int32_t >( row, 1 );
  iconOff = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::GcArmyCaptureTactics::GcArmyCaptureTactics( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GcArmyCaptureTacticsDat.get_row( row_id );
  name = exdData->getField< int32_t >( row, 0 );
  hP = exdData->getField< uint8_t >( row, 1 );
  damageDealt = exdData->getField< uint8_t >( row, 2 );
  damageReceived = exdData->getField< uint8_t >( row, 3 );
  tactic = exdData->getField< uint32_t >( row, 4 );
  icon = exdData->getField< uint32_t >( row, 5 );
}

Sapphire::Data::GcArmyExpedition::GcArmyExpedition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GcArmyExpeditionDat.get_row( row_id );
  requiredFlag = exdData->getField< uint8_t >( row, 0 );
  unlockFlag = exdData->getField< uint8_t >( row, 1 );
  requiredLevel = exdData->getField< uint8_t >( row, 2 );
  requiredSeals = exdData->getField< uint16_t >( row, 3 );
  rewardExperience = exdData->getField< uint32_t >( row, 4 );
  percentBase = exdData->getField< uint8_t >( row, 5 );
  gcArmyExpeditionType = exdData->getField< uint8_t >( row, 7 );
  name = exdData->getField< std::string >( row, 8 );
  description = exdData->getField< std::string >( row, 9 );
}

Sapphire::Data::GcArmyExpeditionMemberBonus::GcArmyExpeditionMemberBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GcArmyExpeditionMemberBonusDat.get_row( row_id );
  race = exdData->getField< uint8_t >( row, 0 );
  classJob = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::GcArmyExpeditionType::GcArmyExpeditionType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GcArmyExpeditionTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GcArmyMemberGrow::GcArmyMemberGrow( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GcArmyMemberGrowDat.get_row( row_id );
  classJob = exdData->getField< uint8_t >( row, 0 );
  classBook = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::GcArmyTraining::GcArmyTraining( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GcArmyTrainingDat.get_row( row_id );
  physicalBonus = exdData->getField< int8_t >( row, 0 );
  mentalBonus = exdData->getField< int8_t >( row, 1 );
  tacticalBonus = exdData->getField< int8_t >( row, 2 );
  experience = exdData->getField< uint32_t >( row, 3 );
  name = exdData->getField< std::string >( row, 4 );
  description = exdData->getField< std::string >( row, 5 );
}

Sapphire::Data::GCRankGridaniaFemaleText::GCRankGridaniaFemaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCRankGridaniaFemaleTextDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  nameRank = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GCRankGridaniaMaleText::GCRankGridaniaMaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCRankGridaniaMaleTextDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  nameRank = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GCRankLimsaFemaleText::GCRankLimsaFemaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCRankLimsaFemaleTextDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  nameRank = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GCRankLimsaMaleText::GCRankLimsaMaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCRankLimsaMaleTextDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  nameRank = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GCRankUldahFemaleText::GCRankUldahFemaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCRankUldahFemaleTextDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  nameRank = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GCRankUldahMaleText::GCRankUldahMaleText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCRankUldahMaleTextDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  nameRank = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GCScripShopCategory::GCScripShopCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCScripShopCategoryDat.get_row( row_id );
  grandCompany = exdData->getField< int8_t >( row, 0 );
  tier = exdData->getField< int8_t >( row, 1 );
  subCategory = exdData->getField< int8_t >( row, 2 );
}

Sapphire::Data::GCScripShopItem::GCScripShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCScripShopItemDat.get_row( row_id, subRow );
  item = exdData->getField< int32_t >( row, 0 );
  requiredGrandCompanyRank = exdData->getField< int32_t >( row, 1 );
  costGCSeals = exdData->getField< uint32_t >( row, 2 );
  sortKey = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::GCShop::GCShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCShopDat.get_row( row_id );
  grandCompany = exdData->getField< int8_t >( row, 0 );
}

Sapphire::Data::GCShopItemCategory::GCShopItemCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCShopItemCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GCSupplyDuty::GCSupplyDuty( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCSupplyDutyDat.get_row( row_id );
}

Sapphire::Data::GCSupplyDutyReward::GCSupplyDutyReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GCSupplyDutyRewardDat.get_row( row_id );
  experienceSupply = exdData->getField< uint32_t >( row, 0 );
  experienceProvisioning = exdData->getField< uint32_t >( row, 1 );
  sealsExpertDelivery = exdData->getField< uint32_t >( row, 2 );
  sealsSupply = exdData->getField< uint32_t >( row, 3 );
  sealsProvisioning = exdData->getField< uint32_t >( row, 4 );
}

Sapphire::Data::GeneralAction::GeneralAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GeneralActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  action = exdData->getField< uint16_t >( row, 3 );
  unlockLink = exdData->getField< uint16_t >( row, 4 );
  recast = exdData->getField< uint8_t >( row, 5 );
  uIPriority = exdData->getField< uint8_t >( row, 6 );
  icon = exdData->getField< int32_t >( row, 7 );
}

Sapphire::Data::GFATE::GFATE( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GFATEDat.get_row( row_id );
  icon.push_back( exdData->getField< uint32_t >( row, 22 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 23 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 24 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 25 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 26 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 27 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 28 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 29 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 30 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 31 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 32 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 33 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 34 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 35 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 36 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 37 ) );
}

Sapphire::Data::GFateClimbing2::GFateClimbing2( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GFateClimbing2Dat.get_row( row_id );
  contentEntry = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::GFateClimbing2Content::GFateClimbing2Content( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GFateClimbing2ContentDat.get_row( row_id );
  publicContentTextData = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::GFateClimbing2TotemType::GFateClimbing2TotemType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GFateClimbing2TotemTypeDat.get_row( row_id );
  publicContentTextData = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::GFateRideShooting::GFateRideShooting( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GFateRideShootingDat.get_row( row_id );
  contentEntry = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::GilShop::GilShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GilShopDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  quest = exdData->getField< uint32_t >( row, 2 );
  acceptTalk = exdData->getField< int32_t >( row, 3 );
  failTalk = exdData->getField< int32_t >( row, 4 );
}

Sapphire::Data::GilShopItem::GilShopItem( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GilShopItemDat.get_row( row_id, subRow );
  item = exdData->getField< int32_t >( row, 0 );
  rowRequired.push_back( exdData->getField< int32_t >( row, 3 ) );
  rowRequired.push_back( exdData->getField< int32_t >( row, 4 ) );
  rowRequired.push_back( exdData->getField< int32_t >( row, 5 ) );
  stateRequired = exdData->getField< uint16_t >( row, 7 );
  patch = exdData->getField< uint16_t >( row, 8 );
}

Sapphire::Data::GimmickAccessor::GimmickAccessor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GimmickAccessorDat.get_row( row_id );
  param0 = exdData->getField< int32_t >( row, 0 );
  param1 = exdData->getField< uint32_t >( row, 1 );
  param2 = exdData->getField< uint32_t >( row, 2 );
  type = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::GimmickJump::GimmickJump( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GimmickJumpDat.get_row( row_id );
  fallDamage = exdData->getField< uint16_t >( row, 0 );
  height = exdData->getField< int8_t >( row, 1 );
  loopMotion = exdData->getField< uint32_t >( row, 2 );
  endMotion = exdData->getField< uint32_t >( row, 3 );
  startClient = exdData->getField< bool >( row, 4 );
}

Sapphire::Data::GimmickRect::GimmickRect( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GimmickRectDat.get_row( row_id );
  layoutID = exdData->getField< uint32_t >( row, 0 );
  triggerIn = exdData->getField< uint8_t >( row, 1 );
  param0 = exdData->getField< uint32_t >( row, 2 );
  triggerOut = exdData->getField< uint8_t >( row, 6 );
  param1 = exdData->getField< uint32_t >( row, 7 );
}

Sapphire::Data::GoldSaucerArcadeMachine::GoldSaucerArcadeMachine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GoldSaucerArcadeMachineDat.get_row( row_id );
  failImage = exdData->getField< uint32_t >( row, 6 );
  poor = exdData->getField< uint32_t >( row, 35 );
  good = exdData->getField< uint32_t >( row, 36 );
  great = exdData->getField< uint32_t >( row, 37 );
  excellent = exdData->getField< uint32_t >( row, 38 );
}

Sapphire::Data::GoldSaucerTextData::GoldSaucerTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GoldSaucerTextDataDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GrandCompany::GrandCompany( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GrandCompanyDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GrandCompanyRank::GrandCompanyRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GrandCompanyRankDat.get_row( row_id );
  tier = exdData->getField< uint8_t >( row, 0 );
  order = exdData->getField< uint8_t >( row, 1 );
  maxSeals = exdData->getField< uint32_t >( row, 2 );
  requiredSeals = exdData->getField< uint32_t >( row, 3 );
  iconMaelstrom = exdData->getField< int32_t >( row, 4 );
  iconSerpents = exdData->getField< int32_t >( row, 5 );
  iconFlames = exdData->getField< int32_t >( row, 6 );
  questMaelstrom = exdData->getField< int32_t >( row, 7 );
  questSerpents = exdData->getField< int32_t >( row, 8 );
  questFlames = exdData->getField< int32_t >( row, 9 );
}

Sapphire::Data::GroupPoseFrame::GroupPoseFrame( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GroupPoseFrameDat.get_row( row_id );
  image = exdData->getField< int32_t >( row, 1 );
  gridText = exdData->getField< std::string >( row, 2 );
  unknown54 = exdData->getField< int32_t >( row, 6 );
  text = exdData->getField< std::string >( row, 7 );
}

Sapphire::Data::GroupPoseStamp::GroupPoseStamp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GroupPoseStampDat.get_row( row_id );
  stampIcon = exdData->getField< int32_t >( row, 0 );
  category = exdData->getField< int32_t >( row, 2 );
  unknown540 = exdData->getField< int32_t >( row, 4 );
  unknown541 = exdData->getField< bool >( row, 5 );
  name = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::GroupPoseStampCategory::GroupPoseStampCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GroupPoseStampCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::GuardianDeity::GuardianDeity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuardianDeityDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::Guide::Guide( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuideDat.get_row( row_id );
  guideTitle = exdData->getField< uint16_t >( row, 0 );
  guidePage = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::GuidePage::GuidePage( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuidePageDat.get_row( row_id, subRow );
  key = exdData->getField< uint8_t >( row, 0 );
  output = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::GuidePageString::GuidePageString( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuidePageStringDat.get_row( row_id );
  string = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GuideTitle::GuideTitle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuideTitleDat.get_row( row_id );
  title = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GuildleveAssignment::GuildleveAssignment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuildleveAssignmentDat.get_row( row_id );
  addedIn53 = exdData->getField< uint8_t >( row, 1 );
  assignmentTalk = exdData->getField< uint32_t >( row, 2 );
  quest.push_back( exdData->getField< uint32_t >( row, 3 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 4 ) );
}

Sapphire::Data::GuildleveAssignmentCategory::GuildleveAssignmentCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuildleveAssignmentCategoryDat.get_row( row_id );
  category.push_back( exdData->getField< int32_t >( row, 0 ) );
  category.push_back( exdData->getField< int32_t >( row, 1 ) );
  category.push_back( exdData->getField< int32_t >( row, 2 ) );
  category.push_back( exdData->getField< int32_t >( row, 3 ) );
  category.push_back( exdData->getField< int32_t >( row, 4 ) );
  category.push_back( exdData->getField< int32_t >( row, 5 ) );
  category.push_back( exdData->getField< int32_t >( row, 6 ) );
  category.push_back( exdData->getField< int32_t >( row, 7 ) );
}

Sapphire::Data::GuildOrder::GuildOrder( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuildOrderDat.get_row( row_id );
  eNpcName = exdData->getField< uint32_t >( row, 0 );
  objective = exdData->getField< std::string >( row, 1 );
  description1 = exdData->getField< std::string >( row, 2 );
  description2 = exdData->getField< std::string >( row, 3 );
  description3 = exdData->getField< std::string >( row, 4 );
  completionBonusExp = exdData->getField< uint32_t >( row, 5 );
  rewardExp = exdData->getField< uint32_t >( row, 6 );
  completionBonusGil = exdData->getField< uint32_t >( row, 7 );
  rewardGil = exdData->getField< uint32_t >( row, 8 );
}

Sapphire::Data::GuildOrderGuide::GuildOrderGuide( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuildOrderGuideDat.get_row( row_id );
}

Sapphire::Data::GuildOrderOfficer::GuildOrderOfficer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_GuildOrderOfficerDat.get_row( row_id );
}

Sapphire::Data::HairMakeType::HairMakeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HairMakeTypeDat.get_row( row_id );
  race = exdData->getField< int32_t >( row, 0 );
  tribe = exdData->getField< int32_t >( row, 1 );
  gender = exdData->getField< int8_t >( row, 2 );
}

Sapphire::Data::HouseRetainerPose::HouseRetainerPose( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HouseRetainerPoseDat.get_row( row_id );
  actionTimeline = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::HousingAethernet::HousingAethernet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingAethernetDat.get_row( row_id );
  level = exdData->getField< uint32_t >( row, 0 );
  territoryType = exdData->getField< uint16_t >( row, 1 );
  placeName = exdData->getField< uint16_t >( row, 2 );
  order = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::HousingAppeal::HousingAppeal( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingAppealDat.get_row( row_id );
  tag = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  order = exdData->getField< uint8_t >( row, 2 );
}

Sapphire::Data::HousingEmploymentNpcList::HousingEmploymentNpcList( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingEmploymentNpcListDat.get_row( row_id, subRow );
  race = exdData->getField< uint8_t >( row, 0 );
  eNpcBase.push_back( exdData->getField< uint32_t >( row, 1 ) );
  eNpcBase.push_back( exdData->getField< uint32_t >( row, 2 ) );
}

Sapphire::Data::HousingEmploymentNpcRace::HousingEmploymentNpcRace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingEmploymentNpcRaceDat.get_row( row_id );
  race = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::HousingExterior::HousingExterior( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingExteriorDat.get_row( row_id );
  placeName = exdData->getField< uint16_t >( row, 2 );
  housingSize = exdData->getField< uint8_t >( row, 3 );
  model = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::HousingFurniture::HousingFurniture( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingFurnitureDat.get_row( row_id );
  modelKey = exdData->getField< uint16_t >( row, 0 );
  housingItemCategory = exdData->getField< uint8_t >( row, 1 );
  usageType = exdData->getField< uint8_t >( row, 2 );
  usageParameter = exdData->getField< uint32_t >( row, 3 );
  aquariumTier = exdData->getField< uint8_t >( row, 5 );
  customTalk = exdData->getField< uint32_t >( row, 6 );
  item = exdData->getField< uint32_t >( row, 7 );
  destroyOnRemoval = exdData->getField< bool >( row, 8 );
  tooltip = exdData->getField< bool >( row, 9 );
}

Sapphire::Data::HousingLandSet::HousingLandSet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingLandSetDat.get_row( row_id );
  plotSize.push_back( exdData->getField< uint8_t >( row, 0 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 1 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 2 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 3 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 4 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 5 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 6 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 7 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 8 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 9 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 10 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 11 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 12 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 13 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 14 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 15 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 16 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 17 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 18 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 19 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 20 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 21 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 22 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 23 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 24 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 25 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 26 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 27 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 28 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 29 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 30 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 31 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 32 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 33 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 34 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 35 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 36 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 37 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 38 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 39 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 40 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 41 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 42 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 43 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 44 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 45 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 46 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 47 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 48 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 49 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 50 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 51 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 52 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 53 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 54 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 55 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 56 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 57 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 58 ) );
  plotSize.push_back( exdData->getField< uint8_t >( row, 59 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 60 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 61 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 62 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 63 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 64 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 65 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 66 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 67 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 68 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 69 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 70 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 71 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 72 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 73 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 74 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 75 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 76 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 77 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 78 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 79 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 80 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 81 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 82 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 83 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 84 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 85 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 86 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 87 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 88 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 89 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 90 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 91 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 92 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 93 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 94 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 95 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 96 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 97 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 98 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 99 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 100 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 101 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 102 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 103 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 104 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 105 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 106 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 107 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 108 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 109 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 110 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 111 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 112 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 113 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 114 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 115 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 116 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 117 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 118 ) );
  minPrice.push_back( exdData->getField< uint32_t >( row, 119 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 240 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 241 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 242 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 243 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 244 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 245 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 246 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 247 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 248 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 249 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 250 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 251 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 252 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 253 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 254 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 255 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 256 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 257 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 258 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 259 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 260 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 261 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 262 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 263 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 264 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 265 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 266 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 267 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 268 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 269 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 270 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 271 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 272 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 273 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 274 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 275 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 276 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 277 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 278 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 279 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 280 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 281 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 282 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 283 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 284 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 285 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 286 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 287 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 288 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 289 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 290 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 291 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 292 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 293 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 294 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 295 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 296 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 297 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 298 ) );
  initialPrice.push_back( exdData->getField< uint32_t >( row, 299 ) );
}

Sapphire::Data::HousingMapMarkerInfo::HousingMapMarkerInfo( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingMapMarkerInfoDat.get_row( row_id, subRow );
  x = exdData->getField< float >( row, 0 );
  y = exdData->getField< float >( row, 1 );
  z = exdData->getField< float >( row, 2 );
  map = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::HousingMerchantPose::HousingMerchantPose( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingMerchantPoseDat.get_row( row_id );
  actionTimeline = exdData->getField< uint16_t >( row, 0 );
  pose = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::HousingPlacement::HousingPlacement( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingPlacementDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::HousingPreset::HousingPreset( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingPresetDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  placeName = exdData->getField< uint16_t >( row, 8 );
  housingSize = exdData->getField< uint8_t >( row, 9 );
  exteriorRoof = exdData->getField< int32_t >( row, 10 );
  exteriorWall = exdData->getField< int32_t >( row, 11 );
  exteriorWindow = exdData->getField< int32_t >( row, 12 );
  exteriorDoor = exdData->getField< int32_t >( row, 13 );
  interiorWall = exdData->getField< int32_t >( row, 14 );
  interiorFlooring = exdData->getField< int32_t >( row, 15 );
  interiorLighting = exdData->getField< int32_t >( row, 16 );
  otherFloorWall = exdData->getField< int32_t >( row, 17 );
  otherFloorFlooring = exdData->getField< int32_t >( row, 18 );
  otherFloorLighting = exdData->getField< int32_t >( row, 19 );
  basementWall = exdData->getField< int32_t >( row, 20 );
  basementFlooring = exdData->getField< int32_t >( row, 21 );
  basementLighting = exdData->getField< int32_t >( row, 22 );
  mansionLighting = exdData->getField< int32_t >( row, 23 );
}

Sapphire::Data::HousingUnitedExterior::HousingUnitedExterior( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingUnitedExteriorDat.get_row( row_id );
  item.push_back( exdData->getField< uint32_t >( row, 1 ) );
  item.push_back( exdData->getField< uint32_t >( row, 2 ) );
  item.push_back( exdData->getField< uint32_t >( row, 3 ) );
  item.push_back( exdData->getField< uint32_t >( row, 4 ) );
  item.push_back( exdData->getField< uint32_t >( row, 5 ) );
  item.push_back( exdData->getField< uint32_t >( row, 6 ) );
  item.push_back( exdData->getField< uint32_t >( row, 7 ) );
  item.push_back( exdData->getField< uint32_t >( row, 8 ) );
}

Sapphire::Data::HousingYardObject::HousingYardObject( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HousingYardObjectDat.get_row( row_id );
  modelKey = exdData->getField< uint8_t >( row, 0 );
  housingItemCategory = exdData->getField< uint8_t >( row, 1 );
  usageType = exdData->getField< uint8_t >( row, 2 );
  usageParameter = exdData->getField< uint32_t >( row, 3 );
  customTalk = exdData->getField< uint32_t >( row, 5 );
  item = exdData->getField< uint32_t >( row, 6 );
  destroyOnRemoval = exdData->getField< bool >( row, 7 );
}

Sapphire::Data::HowTo::HowTo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HowToDat.get_row( row_id );
  images.push_back( exdData->getField< int16_t >( row, 2 ) );
  images.push_back( exdData->getField< int16_t >( row, 3 ) );
  images.push_back( exdData->getField< int16_t >( row, 4 ) );
  images.push_back( exdData->getField< int16_t >( row, 5 ) );
  images.push_back( exdData->getField< int16_t >( row, 6 ) );
  images.push_back( exdData->getField< int16_t >( row, 7 ) );
  images.push_back( exdData->getField< int16_t >( row, 8 ) );
  images.push_back( exdData->getField< int16_t >( row, 9 ) );
  images.push_back( exdData->getField< int16_t >( row, 10 ) );
  images.push_back( exdData->getField< int16_t >( row, 11 ) );
  category = exdData->getField< int8_t >( row, 12 );
}

Sapphire::Data::HowToCategory::HowToCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HowToCategoryDat.get_row( row_id );
  category = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::HowToPage::HowToPage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HowToPageDat.get_row( row_id );
  image = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::HugeCraftworksNpc::HugeCraftworksNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HugeCraftworksNpcDat.get_row( row_id );
  eNpcResident = exdData->getField< uint32_t >( row, 0 );
  classJobCategory = exdData->getField< uint16_t >( row, 1 );
  itemRequested.push_back( exdData->getField< uint32_t >( row, 3 ) );
  itemRequested.push_back( exdData->getField< uint32_t >( row, 4 ) );
  itemRequested.push_back( exdData->getField< uint32_t >( row, 5 ) );
  itemRequested.push_back( exdData->getField< uint32_t >( row, 6 ) );
  qtyRequested.push_back( exdData->getField< uint8_t >( row, 9 ) );
  qtyRequested.push_back( exdData->getField< uint8_t >( row, 10 ) );
  qtyRequested.push_back( exdData->getField< uint8_t >( row, 11 ) );
  qtyRequested.push_back( exdData->getField< uint8_t >( row, 12 ) );
  itemReward.push_back( exdData->getField< uint32_t >( row, 52 ) );
  itemReward.push_back( exdData->getField< uint32_t >( row, 53 ) );
  itemReward.push_back( exdData->getField< uint32_t >( row, 54 ) );
  itemReward.push_back( exdData->getField< uint32_t >( row, 55 ) );
  qtyItemReward.push_back( exdData->getField< uint8_t >( row, 64 ) );
  qtyItemReward.push_back( exdData->getField< uint8_t >( row, 65 ) );
  qtyItemReward.push_back( exdData->getField< uint8_t >( row, 66 ) );
  qtyItemReward.push_back( exdData->getField< uint8_t >( row, 67 ) );
  itemUnkown.push_back( exdData->getField< uint32_t >( row, 70 ) );
  itemUnkown.push_back( exdData->getField< uint32_t >( row, 71 ) );
  itemUnkown.push_back( exdData->getField< uint32_t >( row, 72 ) );
  itemUnkown.push_back( exdData->getField< uint32_t >( row, 73 ) );
  qtyItemUnkown.push_back( exdData->getField< uint8_t >( row, 82 ) );
  qtyItemUnkown.push_back( exdData->getField< uint8_t >( row, 83 ) );
  qtyItemUnkown.push_back( exdData->getField< uint8_t >( row, 84 ) );
  qtyItemUnkown.push_back( exdData->getField< uint8_t >( row, 85 ) );
  transient = exdData->getField< std::string >( row, 86 );
}

Sapphire::Data::HugeCraftworksRank::HugeCraftworksRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HugeCraftworksRankDat.get_row( row_id );
  crafterLevel = exdData->getField< uint8_t >( row, 0 );
  expRewardPerItem = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::HWDAnnounce::HWDAnnounce( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDAnnounceDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  eNPC = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::HWDCrafterSupply::HWDCrafterSupply( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDCrafterSupplyDat.get_row( row_id );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 0 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 1 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 2 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 3 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 4 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 5 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 6 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 7 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 8 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 9 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 10 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 11 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 12 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 13 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 14 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 15 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 16 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 17 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 18 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 19 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 20 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 21 ) );
  itemTradeIn.push_back( exdData->getField< uint32_t >( row, 22 ) );
  level.push_back( exdData->getField< uint8_t >( row, 23 ) );
  level.push_back( exdData->getField< uint8_t >( row, 24 ) );
  level.push_back( exdData->getField< uint8_t >( row, 25 ) );
  level.push_back( exdData->getField< uint8_t >( row, 26 ) );
  level.push_back( exdData->getField< uint8_t >( row, 27 ) );
  level.push_back( exdData->getField< uint8_t >( row, 28 ) );
  level.push_back( exdData->getField< uint8_t >( row, 29 ) );
  level.push_back( exdData->getField< uint8_t >( row, 30 ) );
  level.push_back( exdData->getField< uint8_t >( row, 31 ) );
  level.push_back( exdData->getField< uint8_t >( row, 32 ) );
  level.push_back( exdData->getField< uint8_t >( row, 33 ) );
  level.push_back( exdData->getField< uint8_t >( row, 34 ) );
  level.push_back( exdData->getField< uint8_t >( row, 35 ) );
  level.push_back( exdData->getField< uint8_t >( row, 36 ) );
  level.push_back( exdData->getField< uint8_t >( row, 37 ) );
  level.push_back( exdData->getField< uint8_t >( row, 38 ) );
  level.push_back( exdData->getField< uint8_t >( row, 39 ) );
  level.push_back( exdData->getField< uint8_t >( row, 40 ) );
  level.push_back( exdData->getField< uint8_t >( row, 41 ) );
  level.push_back( exdData->getField< uint8_t >( row, 42 ) );
  level.push_back( exdData->getField< uint8_t >( row, 43 ) );
  level.push_back( exdData->getField< uint8_t >( row, 44 ) );
  level.push_back( exdData->getField< uint8_t >( row, 45 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 46 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 47 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 48 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 49 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 50 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 51 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 52 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 53 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 54 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 55 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 56 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 57 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 58 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 59 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 60 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 61 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 62 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 63 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 64 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 65 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 66 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 67 ) );
  levelMax.push_back( exdData->getField< uint8_t >( row, 68 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 92 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 93 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 94 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 95 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 96 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 97 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 98 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 99 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 100 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 101 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 102 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 103 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 104 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 105 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 106 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 107 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 108 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 109 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 110 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 111 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 112 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 113 ) );
  baseCollectableRating.push_back( exdData->getField< uint16_t >( row, 114 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 115 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 116 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 117 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 118 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 119 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 120 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 121 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 122 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 123 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 124 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 125 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 126 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 127 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 128 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 129 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 130 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 131 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 132 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 133 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 134 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 135 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 136 ) );
  midCollectableRating.push_back( exdData->getField< uint16_t >( row, 137 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 138 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 139 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 140 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 141 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 142 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 143 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 144 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 145 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 146 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 147 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 148 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 149 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 150 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 151 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 152 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 153 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 154 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 155 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 156 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 157 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 158 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 159 ) );
  highCollectableRating.push_back( exdData->getField< uint16_t >( row, 160 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 161 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 162 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 163 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 164 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 165 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 166 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 167 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 168 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 169 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 170 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 171 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 172 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 173 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 174 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 175 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 176 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 177 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 178 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 179 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 180 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 181 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 182 ) );
  baseCollectableReward.push_back( exdData->getField< uint16_t >( row, 183 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 184 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 185 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 186 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 187 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 188 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 189 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 190 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 191 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 192 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 193 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 194 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 195 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 196 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 197 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 198 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 199 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 200 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 201 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 202 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 203 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 204 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 205 ) );
  midCollectableReward.push_back( exdData->getField< uint16_t >( row, 206 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 207 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 208 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 209 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 210 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 211 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 212 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 213 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 214 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 215 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 216 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 217 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 218 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 219 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 220 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 221 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 222 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 223 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 224 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 225 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 226 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 227 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 228 ) );
  highCollectableReward.push_back( exdData->getField< uint16_t >( row, 229 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 230 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 231 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 232 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 233 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 234 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 235 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 236 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 237 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 238 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 239 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 240 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 241 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 242 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 243 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 244 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 245 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 246 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 247 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 248 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 249 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 250 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 251 ) );
  baseCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 252 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 253 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 254 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 255 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 256 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 257 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 258 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 259 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 260 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 261 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 262 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 263 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 264 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 265 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 266 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 267 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 268 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 269 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 270 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 271 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 272 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 273 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 274 ) );
  midCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 275 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 276 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 277 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 278 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 279 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 280 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 281 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 282 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 283 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 284 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 285 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 286 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 287 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 288 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 289 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 290 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 291 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 292 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 293 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 294 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 295 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 296 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 297 ) );
  highCollectableRewardPostPhase.push_back( exdData->getField< uint16_t >( row, 298 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 299 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 300 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 301 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 302 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 303 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 304 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 305 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 306 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 307 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 308 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 309 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 310 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 311 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 312 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 313 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 314 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 315 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 316 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 317 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 318 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 319 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 320 ) );
  termName.push_back( exdData->getField< uint8_t >( row, 321 ) );
}

Sapphire::Data::HWDCrafterSupplyReward::HWDCrafterSupplyReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDCrafterSupplyRewardDat.get_row( row_id );
  scriptRewardAmount = exdData->getField< uint16_t >( row, 0 );
  expReward = exdData->getField< uint32_t >( row, 1 );
  Points = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::HWDCrafterSupplyTerm::HWDCrafterSupplyTerm( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDCrafterSupplyTermDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::HWDDevLayerControl::HWDDevLayerControl( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDDevLayerControlDat.get_row( row_id );
}

Sapphire::Data::HWDDevLevelUI::HWDDevLevelUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDDevLevelUIDat.get_row( row_id );
}

Sapphire::Data::HWDDevLively::HWDDevLively( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDDevLivelyDat.get_row( row_id, subRow );
  eNPC = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::HWDDevProgress::HWDDevProgress( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDDevProgressDat.get_row( row_id );
  canGoNext = exdData->getField< bool >( row, 0 );
}

Sapphire::Data::HWDGathereInspectTerm::HWDGathereInspectTerm( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDGathereInspectTermDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::HWDGathererInspection::HWDGathererInspection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDGathererInspectionDat.get_row( row_id );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 0 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 1 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 2 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 3 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 4 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 5 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 6 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 7 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 8 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 9 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 10 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 11 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 12 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 13 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 14 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 15 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 16 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 17 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 18 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 19 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 20 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 21 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 22 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 23 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 24 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 25 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 26 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 27 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 28 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 29 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 30 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 31 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 32 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 33 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 34 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 35 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 36 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 37 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 38 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 39 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 40 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 41 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 42 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 43 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 44 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 45 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 46 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 47 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 48 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 49 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 50 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 51 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 52 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 53 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 54 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 55 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 56 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 57 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 58 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 59 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 60 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 61 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 62 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 63 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 64 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 65 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 66 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 67 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 68 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 69 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 70 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 71 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 72 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 73 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 74 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 75 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 76 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 77 ) );
  itemRequired.push_back( exdData->getField< uint32_t >( row, 78 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 79 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 80 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 81 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 82 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 83 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 84 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 85 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 86 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 87 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 88 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 89 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 90 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 91 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 92 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 93 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 94 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 95 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 96 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 97 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 98 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 99 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 100 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 101 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 102 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 103 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 104 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 105 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 106 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 107 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 108 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 109 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 110 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 111 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 112 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 113 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 114 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 115 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 116 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 117 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 118 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 119 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 120 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 121 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 122 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 123 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 124 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 125 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 126 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 127 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 128 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 129 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 130 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 131 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 132 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 133 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 134 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 135 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 136 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 137 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 138 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 139 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 140 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 141 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 142 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 143 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 144 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 145 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 146 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 147 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 148 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 149 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 150 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 151 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 152 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 153 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 154 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 155 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 156 ) );
  fishParameter.push_back( exdData->getField< uint32_t >( row, 157 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 158 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 159 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 160 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 161 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 162 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 163 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 164 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 165 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 166 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 167 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 168 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 169 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 170 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 171 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 172 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 173 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 174 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 175 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 176 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 177 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 178 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 179 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 180 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 181 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 182 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 183 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 184 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 185 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 186 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 187 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 188 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 189 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 190 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 191 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 192 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 193 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 194 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 195 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 196 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 197 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 198 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 199 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 200 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 201 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 202 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 203 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 204 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 205 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 206 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 207 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 208 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 209 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 210 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 211 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 212 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 213 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 214 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 215 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 216 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 217 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 218 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 219 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 220 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 221 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 222 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 223 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 224 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 225 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 226 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 227 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 228 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 229 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 230 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 231 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 232 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 233 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 234 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 235 ) );
  amountRequired.push_back( exdData->getField< uint8_t >( row, 236 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 237 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 238 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 239 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 240 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 241 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 242 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 243 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 244 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 245 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 246 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 247 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 248 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 249 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 250 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 251 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 252 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 253 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 254 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 255 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 256 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 257 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 258 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 259 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 260 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 261 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 262 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 263 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 264 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 265 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 266 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 267 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 268 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 269 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 270 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 271 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 272 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 273 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 274 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 275 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 276 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 277 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 278 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 279 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 280 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 281 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 282 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 283 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 284 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 285 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 286 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 287 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 288 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 289 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 290 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 291 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 292 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 293 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 294 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 295 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 296 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 297 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 298 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 299 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 300 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 301 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 302 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 303 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 304 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 305 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 306 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 307 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 308 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 309 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 310 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 311 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 312 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 313 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 314 ) );
  itemReceived.push_back( exdData->getField< uint32_t >( row, 315 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 316 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 317 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 318 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 319 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 320 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 321 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 322 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 323 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 324 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 325 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 326 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 327 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 328 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 329 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 330 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 331 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 332 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 333 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 334 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 335 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 336 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 337 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 338 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 339 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 340 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 341 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 342 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 343 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 344 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 345 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 346 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 347 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 348 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 349 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 350 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 351 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 352 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 353 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 354 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 355 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 356 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 357 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 358 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 359 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 360 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 361 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 362 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 363 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 364 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 365 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 366 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 367 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 368 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 369 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 370 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 371 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 372 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 373 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 374 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 375 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 376 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 377 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 378 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 379 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 380 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 381 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 382 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 383 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 384 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 385 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 386 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 387 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 388 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 389 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 390 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 391 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 392 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 393 ) );
  reward1.push_back( exdData->getField< uint16_t >( row, 394 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 395 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 396 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 397 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 398 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 399 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 400 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 401 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 402 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 403 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 404 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 405 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 406 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 407 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 408 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 409 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 410 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 411 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 412 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 413 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 414 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 415 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 416 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 417 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 418 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 419 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 420 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 421 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 422 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 423 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 424 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 425 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 426 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 427 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 428 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 429 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 430 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 431 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 432 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 433 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 434 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 435 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 436 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 437 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 438 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 439 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 440 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 441 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 442 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 443 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 444 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 445 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 446 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 447 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 448 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 449 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 450 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 451 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 452 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 453 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 454 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 455 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 456 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 457 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 458 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 459 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 460 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 461 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 462 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 463 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 464 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 465 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 466 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 467 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 468 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 469 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 470 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 471 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 472 ) );
  reward2.push_back( exdData->getField< uint16_t >( row, 473 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 474 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 475 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 476 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 477 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 478 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 479 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 480 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 481 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 482 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 483 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 484 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 485 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 486 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 487 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 488 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 489 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 490 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 491 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 492 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 493 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 494 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 495 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 496 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 497 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 498 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 499 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 500 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 501 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 502 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 503 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 504 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 505 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 506 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 507 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 508 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 509 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 510 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 511 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 512 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 513 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 514 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 515 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 516 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 517 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 518 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 519 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 520 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 521 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 522 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 523 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 524 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 525 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 526 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 527 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 528 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 529 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 530 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 531 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 532 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 533 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 534 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 535 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 536 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 537 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 538 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 539 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 540 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 541 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 542 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 543 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 544 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 545 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 546 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 547 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 548 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 549 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 550 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 551 ) );
  phase.push_back( exdData->getField< uint8_t >( row, 552 ) );
}

Sapphire::Data::HWDGathererInspectionReward::HWDGathererInspectionReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDGathererInspectionRewardDat.get_row( row_id );
  scrips = exdData->getField< uint16_t >( row, 0 );
  points = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::HWDInfoBoardArticle::HWDInfoBoardArticle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDInfoBoardArticleDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  text = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::HWDInfoBoardArticleTransient::HWDInfoBoardArticleTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDInfoBoardArticleTransientDat.get_row( row_id );
  image = exdData->getField< uint32_t >( row, 0 );
  text = exdData->getField< std::string >( row, 1 );
  npcName = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::HWDInfoBoardArticleType::HWDInfoBoardArticleType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDInfoBoardArticleTypeDat.get_row( row_id );
  type = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::HWDLevelChangeDeception::HWDLevelChangeDeception( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDLevelChangeDeceptionDat.get_row( row_id );
  image = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::HWDSharedGroup::HWDSharedGroup( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDSharedGroupDat.get_row( row_id, subRow );
  lGB = exdData->getField< uint32_t >( row, 0 );
  param = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::HWDSharedGroupControlParam::HWDSharedGroupControlParam( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_HWDSharedGroupControlParamDat.get_row( row_id, subRow );
  paramValue = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::IKDContentBonus::IKDContentBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_IKDContentBonusDat.get_row( row_id );
  objective = exdData->getField< std::string >( row, 0 );
  requirement = exdData->getField< std::string >( row, 1 );
  image = exdData->getField< uint32_t >( row, 3 );
  order = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::IKDFishParam::IKDFishParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_IKDFishParamDat.get_row( row_id );
  fish = exdData->getField< uint32_t >( row, 0 );
  iKDContentBonus = exdData->getField< uint8_t >( row, 1 );
  unknown54 = exdData->getField< uint8_t >( row, 2 );
}

Sapphire::Data::IKDRoute::IKDRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_IKDRouteDat.get_row( row_id );
  image = exdData->getField< uint32_t >( row, 6 );
  territoryType = exdData->getField< uint32_t >( row, 7 );
  name = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::IKDRouteTable::IKDRouteTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_IKDRouteTableDat.get_row( row_id );
  route = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::IKDSpot::IKDSpot( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_IKDSpotDat.get_row( row_id );
  spotMain = exdData->getField< uint32_t >( row, 0 );
  spotSub = exdData->getField< uint32_t >( row, 1 );
  placeName = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::InclusionShop::InclusionShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InclusionShopDat.get_row( row_id );
  category.push_back( exdData->getField< uint16_t >( row, 2 ) );
  category.push_back( exdData->getField< uint16_t >( row, 3 ) );
  category.push_back( exdData->getField< uint16_t >( row, 4 ) );
  category.push_back( exdData->getField< uint16_t >( row, 5 ) );
  category.push_back( exdData->getField< uint16_t >( row, 6 ) );
  category.push_back( exdData->getField< uint16_t >( row, 7 ) );
  category.push_back( exdData->getField< uint16_t >( row, 8 ) );
  category.push_back( exdData->getField< uint16_t >( row, 9 ) );
  category.push_back( exdData->getField< uint16_t >( row, 10 ) );
  category.push_back( exdData->getField< uint16_t >( row, 11 ) );
  category.push_back( exdData->getField< uint16_t >( row, 12 ) );
  category.push_back( exdData->getField< uint16_t >( row, 13 ) );
  category.push_back( exdData->getField< uint16_t >( row, 14 ) );
  category.push_back( exdData->getField< uint16_t >( row, 15 ) );
  category.push_back( exdData->getField< uint16_t >( row, 16 ) );
  category.push_back( exdData->getField< uint16_t >( row, 17 ) );
  category.push_back( exdData->getField< uint16_t >( row, 18 ) );
  category.push_back( exdData->getField< uint16_t >( row, 19 ) );
  category.push_back( exdData->getField< uint16_t >( row, 20 ) );
  category.push_back( exdData->getField< uint16_t >( row, 21 ) );
  category.push_back( exdData->getField< uint16_t >( row, 22 ) );
  category.push_back( exdData->getField< uint16_t >( row, 23 ) );
  category.push_back( exdData->getField< uint16_t >( row, 24 ) );
  category.push_back( exdData->getField< uint16_t >( row, 25 ) );
  category.push_back( exdData->getField< uint16_t >( row, 26 ) );
  category.push_back( exdData->getField< uint16_t >( row, 27 ) );
  category.push_back( exdData->getField< uint16_t >( row, 28 ) );
  category.push_back( exdData->getField< uint16_t >( row, 29 ) );
  category.push_back( exdData->getField< uint16_t >( row, 30 ) );
  category.push_back( exdData->getField< uint16_t >( row, 31 ) );
}

Sapphire::Data::InclusionShopCategory::InclusionShopCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InclusionShopCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  classJobCategory = exdData->getField< uint8_t >( row, 1 );
  inclusionShopSeries = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::InclusionShopSeries::InclusionShopSeries( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InclusionShopSeriesDat.get_row( row_id, subRow );
  specialShop = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::IndividualWeather::IndividualWeather( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_IndividualWeatherDat.get_row( row_id );
  weather.push_back( exdData->getField< uint8_t >( row, 0 ) );
  weather.push_back( exdData->getField< uint8_t >( row, 1 ) );
  weather.push_back( exdData->getField< uint8_t >( row, 2 ) );
  weather.push_back( exdData->getField< uint8_t >( row, 3 ) );
  weather.push_back( exdData->getField< uint8_t >( row, 4 ) );
  weather.push_back( exdData->getField< uint8_t >( row, 5 ) );
  addedIn530 = exdData->getField< uint8_t >( row, 12 );
  addedIn531 = exdData->getField< uint8_t >( row, 13 );
  quest.push_back( exdData->getField< uint32_t >( row, 15 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 16 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 17 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 18 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 19 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 20 ) );
}

Sapphire::Data::InstanceContent::InstanceContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InstanceContentDat.get_row( row_id );
  instanceContentType = exdData->getField< uint8_t >( row, 0 );
  weekRestriction = exdData->getField< uint8_t >( row, 1 );
  timeLimitmin = exdData->getField< uint16_t >( row, 2 );
  bGM = exdData->getField< uint16_t >( row, 4 );
  winBGM = exdData->getField< uint16_t >( row, 5 );
  cutscene = exdData->getField< uint32_t >( row, 6 );
  order = exdData->getField< uint16_t >( row, 8 );
  colosseum = exdData->getField< uint8_t >( row, 9 );
  instanceContentTextDataBossStart = exdData->getField< uint32_t >( row, 11 );
  instanceContentTextDataBossEnd = exdData->getField< uint32_t >( row, 12 );
  bNpcBaseBoss = exdData->getField< uint32_t >( row, 13 );
  instanceContentTextDataObjectiveStart = exdData->getField< uint32_t >( row, 14 );
  instanceContentTextDataObjectiveEnd = exdData->getField< uint32_t >( row, 15 );
  sortKey = exdData->getField< uint16_t >( row, 16 );
  instanceClearExp = exdData->getField< uint32_t >( row, 17 );
  newPlayerBonusA = exdData->getField< uint16_t >( row, 19 );
  finalBossCurrencyC = exdData->getField< uint16_t >( row, 20 );
  finalBossCurrencyA = exdData->getField< uint32_t >( row, 22 );
  finalBossCurrencyB = exdData->getField< uint16_t >( row, 23 );
  newPlayerBonusB = exdData->getField< uint16_t >( row, 24 );
  instanceClearGil = exdData->getField< uint32_t >( row, 46 );
  instanceContentRewardItem = exdData->getField< uint32_t >( row, 47 );
  finalBossExp = exdData->getField< uint8_t >( row, 49 );
  instanceContentBuff = exdData->getField< uint32_t >( row, 50 );
  reqInstance = exdData->getField< int32_t >( row, 51 );
  partyCondition = exdData->getField< int16_t >( row, 53 );
  unknown540 = exdData->getField< uint16_t >( row, 61 );
  unknown541 = exdData->getField< uint16_t >( row, 62 );
}

Sapphire::Data::InstanceContentBuff::InstanceContentBuff( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InstanceContentBuffDat.get_row( row_id );
  echoStart = exdData->getField< uint16_t >( row, 0 );
  echoDeath = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::InstanceContentCSBonus::InstanceContentCSBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InstanceContentCSBonusDat.get_row( row_id );
  instance = exdData->getField< uint16_t >( row, 0 );
  item = exdData->getField< uint32_t >( row, 1 );
  unknown540 = exdData->getField< uint8_t >( row, 3 );
  unknown541 = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::InstanceContentGuide::InstanceContentGuide( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InstanceContentGuideDat.get_row( row_id );
  instance = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::InstanceContentTextData::InstanceContentTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_InstanceContentTextDataDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Item::Item( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  description = exdData->getField< std::string >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
  icon = exdData->getField< uint16_t >( row, 10 );
  levelItem = exdData->getField< uint16_t >( row, 11 );
  rarity = exdData->getField< uint8_t >( row, 12 );
  filterGroup = exdData->getField< uint8_t >( row, 13 );
  additionalData = exdData->getField< uint32_t >( row, 14 );
  itemUICategory = exdData->getField< uint8_t >( row, 15 );
  itemSearchCategory = exdData->getField< uint8_t >( row, 16 );
  equipSlotCategory = exdData->getField< uint8_t >( row, 17 );
  itemSortCategory = exdData->getField< uint8_t >( row, 18 );
  stackSize = exdData->getField< uint32_t >( row, 20 );
  isUnique = exdData->getField< bool >( row, 21 );
  isUntradable = exdData->getField< bool >( row, 22 );
  isIndisposable = exdData->getField< bool >( row, 23 );
  lot = exdData->getField< bool >( row, 24 );
  priceMid = exdData->getField< uint32_t >( row, 25 );
  priceLow = exdData->getField< uint32_t >( row, 26 );
  canBeHq = exdData->getField< bool >( row, 27 );
  isDyeable = exdData->getField< bool >( row, 28 );
  isCrestWorthy = exdData->getField< bool >( row, 29 );
  itemAction = exdData->getField< uint16_t >( row, 30 );
  cooldowns = exdData->getField< uint16_t >( row, 32 );
  classJobRepair = exdData->getField< uint8_t >( row, 33 );
  itemRepair = exdData->getField< int32_t >( row, 34 );
  itemGlamour = exdData->getField< int32_t >( row, 35 );
  desynth = exdData->getField< uint16_t >( row, 36 );
  isCollectable = exdData->getField< bool >( row, 37 );
  alwaysCollectable = exdData->getField< bool >( row, 38 );
  aetherialReduce = exdData->getField< uint16_t >( row, 39 );
  unknown54 = exdData->getField< uint16_t >( row, 40 );
  levelEquip = exdData->getField< uint8_t >( row, 41 );
  equipRestriction = exdData->getField< uint8_t >( row, 43 );
  classJobCategory = exdData->getField< uint8_t >( row, 44 );
  grandCompany = exdData->getField< uint8_t >( row, 45 );
  itemSeries = exdData->getField< uint8_t >( row, 46 );
  baseParamModifier = exdData->getField< uint8_t >( row, 47 );
  modelMain = exdData->getField< uint64_t >( row, 48 );
  modelSub = exdData->getField< uint64_t >( row, 49 );
  classJobUse = exdData->getField< uint8_t >( row, 50 );
  damagePhys = exdData->getField< uint16_t >( row, 52 );
  damageMag = exdData->getField< uint16_t >( row, 53 );
  delayms = exdData->getField< uint16_t >( row, 54 );
  blockRate = exdData->getField< uint16_t >( row, 56 );
  block = exdData->getField< uint16_t >( row, 57 );
  defensePhys = exdData->getField< uint16_t >( row, 58 );
  defenseMag = exdData->getField< uint16_t >( row, 59 );
  itemSpecialBonus = exdData->getField< uint8_t >( row, 72 );
  itemSpecialBonusParam = exdData->getField< uint8_t >( row, 73 );
  materializeType = exdData->getField< uint8_t >( row, 86 );
  materiaSlotCount = exdData->getField< uint8_t >( row, 87 );
  isAdvancedMeldingPermitted = exdData->getField< bool >( row, 88 );
  isPvP = exdData->getField< bool >( row, 89 );
  isGlamourous = exdData->getField< bool >( row, 91 );

  for( int i = 0; i < 6; ++i )
  {
    param[i].baseparam = exdData->getField< uint8_t >( row, 60 + i * 2 );
    param[i].value = exdData->getField< int16_t >( row, 61 + i * 2 );
  }
}

Sapphire::Data::ItemAction::ItemAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemActionDat.get_row( row_id );
  condLv = exdData->getField< uint8_t >( row, 0 );
  condBattle = exdData->getField< bool >( row, 1 );
  condPVP = exdData->getField< bool >( row, 2 );
  condPVPOnly = exdData->getField< bool >( row, 3 );
  type = exdData->getField< uint16_t >( row, 4 );
  data.push_back( exdData->getField< uint16_t >( row, 5 ) );
  data.push_back( exdData->getField< uint16_t >( row, 6 ) );
  data.push_back( exdData->getField< uint16_t >( row, 7 ) );
  data.push_back( exdData->getField< uint16_t >( row, 8 ) );
  data.push_back( exdData->getField< uint16_t >( row, 9 ) );
  data.push_back( exdData->getField< uint16_t >( row, 10 ) );
  data.push_back( exdData->getField< uint16_t >( row, 11 ) );
  data.push_back( exdData->getField< uint16_t >( row, 12 ) );
  data.push_back( exdData->getField< uint16_t >( row, 13 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 14 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 15 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 16 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 17 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 18 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 19 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 20 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 21 ) );
  dataHQ.push_back( exdData->getField< uint16_t >( row, 22 ) );
}

Sapphire::Data::ItemActionTelepo::ItemActionTelepo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemActionTelepoDat.get_row( row_id );
  requirement = exdData->getField< uint32_t >( row, 0 );
  denyMessage = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::ItemBarterCheck::ItemBarterCheck( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemBarterCheckDat.get_row( row_id, subRow );
  category = exdData->getField< uint16_t >( row, 0 );
  question = exdData->getField< uint32_t >( row, 1 );
  confirm = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::ItemFood::ItemFood( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemFoodDat.get_row( row_id );
  eXPBonus = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::ItemLevel::ItemLevel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemLevelDat.get_row( row_id );
  strength = exdData->getField< uint16_t >( row, 0 );
  dexterity = exdData->getField< uint16_t >( row, 1 );
  vitality = exdData->getField< uint16_t >( row, 2 );
  intelligence = exdData->getField< uint16_t >( row, 3 );
  mind = exdData->getField< uint16_t >( row, 4 );
  piety = exdData->getField< uint16_t >( row, 5 );
  hP = exdData->getField< uint16_t >( row, 6 );
  mP = exdData->getField< uint16_t >( row, 7 );
  tP = exdData->getField< uint16_t >( row, 8 );
  gP = exdData->getField< uint16_t >( row, 9 );
  cP = exdData->getField< uint16_t >( row, 10 );
  physicalDamage = exdData->getField< uint16_t >( row, 11 );
  magicalDamage = exdData->getField< uint16_t >( row, 12 );
  delay = exdData->getField< uint16_t >( row, 13 );
  additionalEffect = exdData->getField< uint16_t >( row, 14 );
  attackSpeed = exdData->getField< uint16_t >( row, 15 );
  blockRate = exdData->getField< uint16_t >( row, 16 );
  blockStrength = exdData->getField< uint16_t >( row, 17 );
  tenacity = exdData->getField< uint16_t >( row, 18 );
  attackPower = exdData->getField< uint16_t >( row, 19 );
  defense = exdData->getField< uint16_t >( row, 20 );
  directHitRate = exdData->getField< uint16_t >( row, 21 );
  evasion = exdData->getField< uint16_t >( row, 22 );
  magicDefense = exdData->getField< uint16_t >( row, 23 );
  criticalHitPower = exdData->getField< uint16_t >( row, 24 );
  criticalHitResilience = exdData->getField< uint16_t >( row, 25 );
  criticalHit = exdData->getField< uint16_t >( row, 26 );
  criticalHitEvasion = exdData->getField< uint16_t >( row, 27 );
  slashingResistance = exdData->getField< uint16_t >( row, 28 );
  piercingResistance = exdData->getField< uint16_t >( row, 29 );
  bluntResistance = exdData->getField< uint16_t >( row, 30 );
  projectileResistance = exdData->getField< uint16_t >( row, 31 );
  attackMagicPotency = exdData->getField< uint16_t >( row, 32 );
  healingMagicPotency = exdData->getField< uint16_t >( row, 33 );
  enhancementMagicPotency = exdData->getField< uint16_t >( row, 34 );
  enfeeblingMagicPotency = exdData->getField< uint16_t >( row, 35 );
  fireResistance = exdData->getField< uint16_t >( row, 36 );
  iceResistance = exdData->getField< uint16_t >( row, 37 );
  windResistance = exdData->getField< uint16_t >( row, 38 );
  earthResistance = exdData->getField< uint16_t >( row, 39 );
  lightningResistance = exdData->getField< uint16_t >( row, 40 );
  waterResistance = exdData->getField< uint16_t >( row, 41 );
  magicResistance = exdData->getField< uint16_t >( row, 42 );
  determination = exdData->getField< uint16_t >( row, 43 );
  skillSpeed = exdData->getField< uint16_t >( row, 44 );
  spellSpeed = exdData->getField< uint16_t >( row, 45 );
  haste = exdData->getField< uint16_t >( row, 46 );
  morale = exdData->getField< uint16_t >( row, 47 );
  enmity = exdData->getField< uint16_t >( row, 48 );
  enmityReduction = exdData->getField< uint16_t >( row, 49 );
  carefulDesynthesis = exdData->getField< uint16_t >( row, 50 );
  eXPBonus = exdData->getField< uint16_t >( row, 51 );
  regen = exdData->getField< uint16_t >( row, 52 );
  refresh = exdData->getField< uint16_t >( row, 53 );
  movementSpeed = exdData->getField< uint16_t >( row, 54 );
  spikes = exdData->getField< uint16_t >( row, 55 );
  slowResistance = exdData->getField< uint16_t >( row, 56 );
  petrificationResistance = exdData->getField< uint16_t >( row, 57 );
  paralysisResistance = exdData->getField< uint16_t >( row, 58 );
  silenceResistance = exdData->getField< uint16_t >( row, 59 );
  blindResistance = exdData->getField< uint16_t >( row, 60 );
  poisonResistance = exdData->getField< uint16_t >( row, 61 );
  stunResistance = exdData->getField< uint16_t >( row, 62 );
  sleepResistance = exdData->getField< uint16_t >( row, 63 );
  bindResistance = exdData->getField< uint16_t >( row, 64 );
  heavyResistance = exdData->getField< uint16_t >( row, 65 );
  doomResistance = exdData->getField< uint16_t >( row, 66 );
  reducedDurabilityLoss = exdData->getField< uint16_t >( row, 67 );
  increasedSpiritbondGain = exdData->getField< uint16_t >( row, 68 );
  craftsmanship = exdData->getField< uint16_t >( row, 69 );
  control = exdData->getField< uint16_t >( row, 70 );
  gathering = exdData->getField< uint16_t >( row, 71 );
  perception = exdData->getField< uint16_t >( row, 72 );
}

Sapphire::Data::ItemSearchCategory::ItemSearchCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemSearchCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  category = exdData->getField< uint8_t >( row, 2 );
  order = exdData->getField< uint8_t >( row, 3 );
  classJob = exdData->getField< int8_t >( row, 4 );
}

Sapphire::Data::ItemSeries::ItemSeries( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemSeriesDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ItemSortCategory::ItemSortCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemSortCategoryDat.get_row( row_id );
  param = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::ItemSpecialBonus::ItemSpecialBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemSpecialBonusDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ItemUICategory::ItemUICategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ItemUICategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  orderMinor = exdData->getField< uint8_t >( row, 2 );
  orderMajor = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::JobHudManual::JobHudManual( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_JobHudManualDat.get_row( row_id );
  action = exdData->getField< uint32_t >( row, 2 );
  guide = exdData->getField< uint16_t >( row, 5 );
}

Sapphire::Data::JobHudManualPriority::JobHudManualPriority( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_JobHudManualPriorityDat.get_row( row_id );
  jobHudManual.push_back( exdData->getField< uint8_t >( row, 0 ) );
  jobHudManual.push_back( exdData->getField< uint8_t >( row, 1 ) );
  jobHudManual.push_back( exdData->getField< uint8_t >( row, 2 ) );
}

Sapphire::Data::JournalCategory::JournalCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_JournalCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  separateType = exdData->getField< uint8_t >( row, 1 );
  dataType = exdData->getField< uint8_t >( row, 2 );
  journalSection = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::JournalGenre::JournalGenre( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_JournalGenreDat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 0 );
  journalCategory = exdData->getField< uint8_t >( row, 1 );
  name = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::JournalSection::JournalSection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_JournalSectionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Knockback::Knockback( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_KnockbackDat.get_row( row_id );
  distance = exdData->getField< uint8_t >( row, 0 );
  speed = exdData->getField< uint8_t >( row, 1 );
  motion = exdData->getField< bool >( row, 2 );
  nearDistance = exdData->getField< uint8_t >( row, 3 );
  direction = exdData->getField< uint8_t >( row, 4 );
  directionArg = exdData->getField< uint8_t >( row, 5 );
  cancelMove = exdData->getField< bool >( row, 6 );
}

Sapphire::Data::LegacyQuest::LegacyQuest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LegacyQuestDat.get_row( row_id );
  legacyQuestID = exdData->getField< uint16_t >( row, 0 );
  text = exdData->getField< std::string >( row, 1 );
  string = exdData->getField< std::string >( row, 2 );
  sortKey = exdData->getField< uint16_t >( row, 3 );
  genre = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::Leve::Leve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  leveClient = exdData->getField< int32_t >( row, 2 );
  leveAssignmentType = exdData->getField< uint8_t >( row, 3 );
  town = exdData->getField< int32_t >( row, 4 );
  classJobLevel = exdData->getField< uint16_t >( row, 6 );
  timeLimit = exdData->getField< uint8_t >( row, 7 );
  allowanceCost = exdData->getField< uint8_t >( row, 8 );
  evaluation = exdData->getField< int32_t >( row, 9 );
  placeNameStart = exdData->getField< int32_t >( row, 10 );
  placeNameIssued = exdData->getField< int32_t >( row, 11 );
  classJobCategory = exdData->getField< uint8_t >( row, 13 );
  journalGenre = exdData->getField< int32_t >( row, 14 );
  placeNameStartZone = exdData->getField< int32_t >( row, 16 );
  iconCityState = exdData->getField< int32_t >( row, 17 );
  dataId = exdData->getField< int32_t >( row, 18 );
  canCancel = exdData->getField< bool >( row, 19 );
  maxDifficulty = exdData->getField< uint8_t >( row, 20 );
  expFactor = exdData->getField< float >( row, 21 );
  expReward = exdData->getField< uint32_t >( row, 22 );
  gilReward = exdData->getField< uint32_t >( row, 23 );
  leveRewardItem = exdData->getField< uint16_t >( row, 24 );
  leveVfx = exdData->getField< uint8_t >( row, 25 );
  leveVfxFrame = exdData->getField< uint8_t >( row, 26 );
  levelLevemete = exdData->getField< uint32_t >( row, 27 );
  iconIssuer = exdData->getField< int32_t >( row, 28 );
  lockedLeve = exdData->getField< bool >( row, 29 );
  levelStart = exdData->getField< uint32_t >( row, 30 );
  bGM = exdData->getField< uint16_t >( row, 31 );
}

Sapphire::Data::LeveAssignmentType::LeveAssignmentType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveAssignmentTypeDat.get_row( row_id );
  isFaction = exdData->getField< bool >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  name = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::LeveClient::LeveClient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveClientDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Level::Level( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LevelDat.get_row( row_id );
  x = exdData->getField< float >( row, 0 );
  y = exdData->getField< float >( row, 1 );
  z = exdData->getField< float >( row, 2 );
  yaw = exdData->getField< float >( row, 3 );
  radius = exdData->getField< float >( row, 4 );
  type = exdData->getField< uint8_t >( row, 5 );
  object = exdData->getField< uint32_t >( row, 6 );
  map = exdData->getField< uint16_t >( row, 7 );
  eventId = exdData->getField< uint32_t >( row, 8 );
  territory = exdData->getField< uint16_t >( row, 9 );
}

Sapphire::Data::LeveRewardItem::LeveRewardItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveRewardItemDat.get_row( row_id );
}

Sapphire::Data::LeveRewardItemGroup::LeveRewardItemGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveRewardItemGroupDat.get_row( row_id );
}

Sapphire::Data::LeveString::LeveString( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveStringDat.get_row( row_id );
  objective = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::LeveVfx::LeveVfx( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LeveVfxDat.get_row( row_id );
  effect = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::Lobby::Lobby( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LobbyDat.get_row( row_id );
  tYPE = exdData->getField< uint32_t >( row, 0 );
  pARAM = exdData->getField< uint32_t >( row, 1 );
  lINK = exdData->getField< uint32_t >( row, 2 );
  text = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::LogFilter::LogFilter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LogFilterDat.get_row( row_id );
  logKind = exdData->getField< uint8_t >( row, 0 );
  caster = exdData->getField< uint16_t >( row, 1 );
  target = exdData->getField< uint16_t >( row, 2 );
  category = exdData->getField< uint8_t >( row, 3 );
  displayOrder = exdData->getField< uint8_t >( row, 4 );
  preset = exdData->getField< uint8_t >( row, 5 );
  name = exdData->getField< std::string >( row, 6 );
  example = exdData->getField< std::string >( row, 7 );
}

Sapphire::Data::LogKind::LogKind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LogKindDat.get_row( row_id );
  format = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::LogMessage::LogMessage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LogMessageDat.get_row( row_id );
  logKind = exdData->getField< uint16_t >( row, 0 );
  text = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::LotteryExchangeShop::LotteryExchangeShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_LotteryExchangeShopDat.get_row( row_id );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 1 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 2 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 3 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 4 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 5 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 6 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 7 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 8 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 9 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 10 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 11 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 12 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 13 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 14 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 15 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 16 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 17 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 18 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 19 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 20 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 21 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 22 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 23 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 24 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 25 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 26 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 27 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 28 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 29 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 30 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 31 ) );
  itemAccepted.push_back( exdData->getField< int32_t >( row, 32 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 33 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 34 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 35 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 36 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 37 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 38 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 39 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 40 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 41 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 42 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 43 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 44 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 45 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 46 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 47 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 48 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 49 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 50 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 51 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 52 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 53 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 54 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 55 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 56 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 57 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 58 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 59 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 60 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 61 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 62 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 63 ) );
  amountAccepted.push_back( exdData->getField< uint32_t >( row, 64 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 65 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 66 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 67 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 68 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 69 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 70 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 71 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 72 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 73 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 74 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 75 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 76 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 77 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 78 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 79 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 80 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 81 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 82 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 83 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 84 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 85 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 86 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 87 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 88 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 89 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 90 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 91 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 92 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 93 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 94 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 95 ) );
  unknown540.push_back( exdData->getField< uint8_t >( row, 96 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 97 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 98 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 99 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 100 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 101 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 102 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 103 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 104 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 105 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 106 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 107 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 108 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 109 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 110 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 111 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 112 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 113 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 114 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 115 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 116 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 117 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 118 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 119 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 120 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 121 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 122 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 123 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 124 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 125 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 126 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 127 ) );
  unknown541.push_back( exdData->getField< uint8_t >( row, 128 ) );
  lua = exdData->getField< std::string >( row, 129 );
  logMessage.push_back( exdData->getField< uint32_t >( row, 130 ) );
  logMessage.push_back( exdData->getField< uint32_t >( row, 131 ) );
  logMessage.push_back( exdData->getField< uint32_t >( row, 132 ) );
}

Sapphire::Data::MacroIcon::MacroIcon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MacroIconDat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 0 );
}

Sapphire::Data::MacroIconRedirectOld::MacroIconRedirectOld( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MacroIconRedirectOldDat.get_row( row_id );
  iconOld = exdData->getField< uint32_t >( row, 0 );
  iconNew = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::MainCommand::MainCommand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MainCommandDat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 0 );
  category = exdData->getField< uint8_t >( row, 1 );
  mainCommandCategory = exdData->getField< uint8_t >( row, 2 );
  sortID = exdData->getField< int8_t >( row, 3 );
  name = exdData->getField< std::string >( row, 4 );
  description = exdData->getField< std::string >( row, 5 );
}

Sapphire::Data::MainCommandCategory::MainCommandCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MainCommandCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::ManeuversArmor::ManeuversArmor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ManeuversArmorDat.get_row( row_id );
  bNpcBase.push_back( exdData->getField< uint32_t >( row, 1 ) );
  bNpcBase.push_back( exdData->getField< uint32_t >( row, 2 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 5 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 6 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 7 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 8 ) );
  icon.push_back( exdData->getField< uint32_t >( row, 9 ) );
}

Sapphire::Data::Map::Map( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MapDat.get_row( row_id );
  mapCondition = exdData->getField< uint8_t >( row, 0 );
  priorityCategoryUI = exdData->getField< uint8_t >( row, 1 );
  priorityUI = exdData->getField< uint8_t >( row, 2 );
  mapIndex = exdData->getField< int8_t >( row, 3 );
  hierarchy = exdData->getField< uint8_t >( row, 4 );
  mapMarkerRange = exdData->getField< uint16_t >( row, 5 );
  id = exdData->getField< std::string >( row, 6 );
  sizeFactor = exdData->getField< uint16_t >( row, 7 );
  offsetX = exdData->getField< int16_t >( row, 8 );
  offsetY = exdData->getField< int16_t >( row, 9 );
  placeNameRegion = exdData->getField< uint16_t >( row, 10 );
  placeName = exdData->getField< uint16_t >( row, 11 );
  placeNameSub = exdData->getField< uint16_t >( row, 12 );
  discoveryIndex = exdData->getField< int16_t >( row, 13 );
  discoveryFlag = exdData->getField< uint32_t >( row, 14 );
  territoryType = exdData->getField< uint16_t >( row, 15 );
  discoveryArrayByte = exdData->getField< bool >( row, 16 );
  isEvent = exdData->getField< bool >( row, 17 );
}

Sapphire::Data::MapMarker::MapMarker( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MapMarkerDat.get_row( row_id, subRow );
  x = exdData->getField< int16_t >( row, 0 );
  y = exdData->getField< int16_t >( row, 1 );
  icon = exdData->getField< uint16_t >( row, 2 );
  placeNameSubtext = exdData->getField< uint16_t >( row, 3 );
  subtextOrientation = exdData->getField< uint8_t >( row, 4 );
  mapMarkerRegion = exdData->getField< uint8_t >( row, 5 );
  type = exdData->getField< uint8_t >( row, 6 );
  dataType = exdData->getField< uint8_t >( row, 7 );
  dataKey = exdData->getField< uint16_t >( row, 8 );
}

Sapphire::Data::MapMarkerRegion::MapMarkerRegion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MapMarkerRegionDat.get_row( row_id );
  x = exdData->getField< int16_t >( row, 1 );
}

Sapphire::Data::MapSymbol::MapSymbol( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MapSymbolDat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 0 );
  placeName = exdData->getField< int32_t >( row, 1 );
  displayNavi = exdData->getField< bool >( row, 2 );
}

Sapphire::Data::Marker::Marker( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MarkerDat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::MasterpieceSupplyDuty::MasterpieceSupplyDuty( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MasterpieceSupplyDutyDat.get_row( row_id );
  classJob = exdData->getField< uint8_t >( row, 0 );
  classJobLevel = exdData->getField< uint8_t >( row, 1 );
  rewardCurrency = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::MasterpieceSupplyMultiplier::MasterpieceSupplyMultiplier( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MasterpieceSupplyMultiplierDat.get_row( row_id );
  xpMultiplier.push_back( exdData->getField< uint16_t >( row, 0 ) );
  xpMultiplier.push_back( exdData->getField< uint16_t >( row, 1 ) );
  currencyMultiplier.push_back( exdData->getField< uint16_t >( row, 4 ) );
  currencyMultiplier.push_back( exdData->getField< uint16_t >( row, 5 ) );
}

Sapphire::Data::Materia::Materia( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MateriaDat.get_row( row_id );
  item.push_back( exdData->getField< int32_t >( row, 0 ) );
  item.push_back( exdData->getField< int32_t >( row, 1 ) );
  item.push_back( exdData->getField< int32_t >( row, 2 ) );
  item.push_back( exdData->getField< int32_t >( row, 3 ) );
  item.push_back( exdData->getField< int32_t >( row, 4 ) );
  item.push_back( exdData->getField< int32_t >( row, 5 ) );
  item.push_back( exdData->getField< int32_t >( row, 6 ) );
  item.push_back( exdData->getField< int32_t >( row, 7 ) );
  item.push_back( exdData->getField< int32_t >( row, 8 ) );
  item.push_back( exdData->getField< int32_t >( row, 9 ) );
  baseParam = exdData->getField< uint8_t >( row, 10 );
  value.push_back( exdData->getField< int16_t >( row, 11 ) );
  value.push_back( exdData->getField< int16_t >( row, 12 ) );
  value.push_back( exdData->getField< int16_t >( row, 13 ) );
  value.push_back( exdData->getField< int16_t >( row, 14 ) );
  value.push_back( exdData->getField< int16_t >( row, 15 ) );
  value.push_back( exdData->getField< int16_t >( row, 16 ) );
  value.push_back( exdData->getField< int16_t >( row, 17 ) );
  value.push_back( exdData->getField< int16_t >( row, 18 ) );
  value.push_back( exdData->getField< int16_t >( row, 19 ) );
  value.push_back( exdData->getField< int16_t >( row, 20 ) );
}

Sapphire::Data::MateriaJoinRate::MateriaJoinRate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MateriaJoinRateDat.get_row( row_id );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 0 ) );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 1 ) );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 2 ) );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 3 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 4 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 5 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 6 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 7 ) );
}

Sapphire::Data::MateriaJoinRateGatherCraft::MateriaJoinRateGatherCraft( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MateriaJoinRateGatherCraftDat.get_row( row_id );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 0 ) );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 1 ) );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 2 ) );
  NQOvermeldSlot.push_back( exdData->getField< float >( row, 3 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 4 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 5 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 6 ) );
  HQOvermeldSlot.push_back( exdData->getField< float >( row, 7 ) );
}

Sapphire::Data::MateriaTomestoneRate::MateriaTomestoneRate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MateriaTomestoneRateDat.get_row( row_id );
  rate = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::MiniGameRA::MiniGameRA( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MiniGameRADat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 1 );
  image = exdData->getField< int32_t >( row, 2 );
  bGM = exdData->getField< int32_t >( row, 3 );
}

Sapphire::Data::MinionRace::MinionRace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MinionRaceDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::MinionRules::MinionRules( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MinionRulesDat.get_row( row_id );
  rule = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::MinionSkillType::MinionSkillType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MinionSkillTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::MobHuntOrder::MobHuntOrder( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MobHuntOrderDat.get_row( row_id, subRow );
  target = exdData->getField< uint16_t >( row, 0 );
  neededKills = exdData->getField< uint8_t >( row, 1 );
  type = exdData->getField< uint8_t >( row, 2 );
  rank = exdData->getField< uint8_t >( row, 3 );
  mobHuntReward = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::MobHuntOrderType::MobHuntOrderType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MobHuntOrderTypeDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  quest = exdData->getField< uint32_t >( row, 1 );
  eventItem = exdData->getField< uint32_t >( row, 2 );
  orderStart = exdData->getField< uint16_t >( row, 3 );
  orderAmount = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::MobHuntReward::MobHuntReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MobHuntRewardDat.get_row( row_id );
  expReward = exdData->getField< uint32_t >( row, 0 );
  gilReward = exdData->getField< uint16_t >( row, 1 );
  expansion = exdData->getField< uint8_t >( row, 2 );
  currencyReward = exdData->getField< uint16_t >( row, 3 );
}

Sapphire::Data::MobHuntRewardCap::MobHuntRewardCap( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MobHuntRewardCapDat.get_row( row_id );
  expCap = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::MobHuntTarget::MobHuntTarget( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MobHuntTargetDat.get_row( row_id );
  name = exdData->getField< uint16_t >( row, 0 );
  fATE = exdData->getField< uint16_t >( row, 1 );
  icon = exdData->getField< uint32_t >( row, 2 );
  territoryType = exdData->getField< uint16_t >( row, 3 );
  placeName = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::ModelChara::ModelChara( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ModelCharaDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  model = exdData->getField< uint16_t >( row, 1 );
  base = exdData->getField< uint8_t >( row, 2 );
  variant = exdData->getField< uint8_t >( row, 3 );
  sEPack = exdData->getField< uint16_t >( row, 4 );
  papVariation = exdData->getField< bool >( row, 7 );
}

Sapphire::Data::ModelSkeleton::ModelSkeleton( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ModelSkeletonDat.get_row( row_id );
  radius = exdData->getField< float >( row, 0 );
  height = exdData->getField< float >( row, 1 );
  vFXScale = exdData->getField< float >( row, 2 );
  floatHeight = exdData->getField< float >( row, 11 );
  floatDown = exdData->getField< float >( row, 12 );
  floatUp = exdData->getField< uint16_t >( row, 13 );
  motionBlendType = exdData->getField< bool >( row, 15 );
  loopFlySE = exdData->getField< uint8_t >( row, 16 );
}

Sapphire::Data::ModelState::ModelState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ModelStateDat.get_row( row_id );
  start = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::MonsterNote::MonsterNote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MonsterNoteDat.get_row( row_id );
  monsterNoteTarget.push_back( exdData->getField< uint16_t >( row, 0 ) );
  monsterNoteTarget.push_back( exdData->getField< uint16_t >( row, 1 ) );
  monsterNoteTarget.push_back( exdData->getField< uint16_t >( row, 2 ) );
  monsterNoteTarget.push_back( exdData->getField< uint16_t >( row, 3 ) );
  count.push_back( exdData->getField< uint8_t >( row, 4 ) );
  count.push_back( exdData->getField< uint8_t >( row, 5 ) );
  count.push_back( exdData->getField< uint8_t >( row, 6 ) );
  count.push_back( exdData->getField< uint8_t >( row, 7 ) );
  reward = exdData->getField< uint32_t >( row, 8 );
  name = exdData->getField< std::string >( row, 9 );
}

Sapphire::Data::MonsterNoteTarget::MonsterNoteTarget( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MonsterNoteTargetDat.get_row( row_id );
  bNpcName = exdData->getField< uint16_t >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  town = exdData->getField< uint8_t >( row, 2 );
}

Sapphire::Data::MotionTimeline::MotionTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MotionTimelineDat.get_row( row_id );
  filename = exdData->getField< std::string >( row, 0 );
  blendGroup = exdData->getField< uint8_t >( row, 1 );
  isLoop = exdData->getField< bool >( row, 2 );
  isBlinkEnable = exdData->getField< bool >( row, 3 );
  isLipEnable = exdData->getField< bool >( row, 4 );
}

Sapphire::Data::MotionTimelineBlendTable::MotionTimelineBlendTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MotionTimelineBlendTableDat.get_row( row_id );
  destBlendGroup = exdData->getField< uint8_t >( row, 0 );
  srcBlendGroup = exdData->getField< uint8_t >( row, 1 );
  blendFrame_PC = exdData->getField< uint8_t >( row, 2 );
  blendFram_TypeA = exdData->getField< uint8_t >( row, 3 );
  blendFram_TypeB = exdData->getField< uint8_t >( row, 4 );
  blendFram_TypeC = exdData->getField< uint8_t >( row, 5 );
}

Sapphire::Data::Mount::Mount( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MountDat.get_row( row_id );
  singular = exdData->getField< std::string >( row, 0 );
  adjective = exdData->getField< int8_t >( row, 1 );
  plural = exdData->getField< std::string >( row, 2 );
  possessivePronoun = exdData->getField< int8_t >( row, 3 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  pronoun = exdData->getField< int8_t >( row, 6 );
  article = exdData->getField< int8_t >( row, 7 );
  modelChara = exdData->getField< int32_t >( row, 8 );
  flyingCondition = exdData->getField< uint8_t >( row, 10 );
  isFlying = exdData->getField< uint8_t >( row, 14 );
  mountCustomize = exdData->getField< uint8_t >( row, 16 );
  rideBGM = exdData->getField< uint16_t >( row, 17 );
  exitMoveDist = exdData->getField< uint8_t >( row, 21 );
  exitMoveSpeed = exdData->getField< uint8_t >( row, 22 );
  isEmote = exdData->getField< bool >( row, 24 );
  equipHead = exdData->getField< int32_t >( row, 25 );
  equipBody = exdData->getField< int32_t >( row, 26 );
  equipLeg = exdData->getField< int32_t >( row, 27 );
  equipFoot = exdData->getField< int32_t >( row, 28 );
  order = exdData->getField< int16_t >( row, 29 );
  icon = exdData->getField< uint16_t >( row, 30 );
  uIPriority = exdData->getField< uint8_t >( row, 31 );
  radiusRate = exdData->getField< uint8_t >( row, 32 );
  baseMotionSpeed_Run = exdData->getField< uint8_t >( row, 33 );
  baseMotionSpeed_Walk = exdData->getField< uint8_t >( row, 34 );
  extraSeats = exdData->getField< uint8_t >( row, 36 );
  mountAction = exdData->getField< uint16_t >( row, 37 );
  isAirborne = exdData->getField< bool >( row, 38 );
  exHotbarEnableConfig = exdData->getField< bool >( row, 39 );
  useEP = exdData->getField< bool >( row, 40 );
  isImmobile = exdData->getField< bool >( row, 42 );
}

Sapphire::Data::MountAction::MountAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MountActionDat.get_row( row_id );
  action.push_back( exdData->getField< uint16_t >( row, 0 ) );
  action.push_back( exdData->getField< uint16_t >( row, 1 ) );
  action.push_back( exdData->getField< uint16_t >( row, 2 ) );
  action.push_back( exdData->getField< uint16_t >( row, 3 ) );
  action.push_back( exdData->getField< uint16_t >( row, 4 ) );
  action.push_back( exdData->getField< uint16_t >( row, 5 ) );
}

Sapphire::Data::MountCustomize::MountCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MountCustomizeDat.get_row( row_id );
  hyurMaleScale = exdData->getField< uint16_t >( row, 1 );
  hyurFemaleScale = exdData->getField< uint16_t >( row, 2 );
  elezenMaleScale = exdData->getField< uint16_t >( row, 3 );
  elezenFemaleScale = exdData->getField< uint16_t >( row, 4 );
  lalaMaleScale = exdData->getField< uint16_t >( row, 5 );
  lalaFemaleScale = exdData->getField< uint16_t >( row, 6 );
  miqoMaleScale = exdData->getField< uint16_t >( row, 7 );
  miqoFemaleScale = exdData->getField< uint16_t >( row, 8 );
  roeMaleScale = exdData->getField< uint16_t >( row, 9 );
  roeFemaleScale = exdData->getField< uint16_t >( row, 10 );
  auRaMaleScale = exdData->getField< uint16_t >( row, 11 );
  auRaFemaleScale = exdData->getField< uint16_t >( row, 12 );
  hrothgarMaleScale = exdData->getField< uint16_t >( row, 13 );
  hrothgarFemaleScale = exdData->getField< uint16_t >( row, 14 );
  vieraMaleScale = exdData->getField< uint16_t >( row, 15 );
  vieraFemaleScale = exdData->getField< uint16_t >( row, 16 );
  hyurMaleCameraHeight = exdData->getField< uint8_t >( row, 17 );
  hyurFemaleCameraHeight = exdData->getField< uint8_t >( row, 18 );
  elezenMaleCameraHeight = exdData->getField< uint8_t >( row, 19 );
  elezenFemaleCameraHeight = exdData->getField< uint8_t >( row, 20 );
  lalaMaleCameraHeight = exdData->getField< uint8_t >( row, 21 );
  lalaFemaleCameraHeight = exdData->getField< uint8_t >( row, 22 );
  miqoMaleCameraHeight = exdData->getField< uint8_t >( row, 23 );
  miqoFemaleCameraHeight = exdData->getField< uint8_t >( row, 24 );
  roeMaleCameraHeight = exdData->getField< uint8_t >( row, 25 );
  roeFemaleCameraHeight = exdData->getField< uint8_t >( row, 26 );
  auRaMaleCameraHeight = exdData->getField< uint8_t >( row, 27 );
  auRaFemaleCameraHeight = exdData->getField< uint8_t >( row, 28 );
  hrothgarMaleCameraHeight = exdData->getField< uint8_t >( row, 29 );
  hrothgarRoeFemaleCameraHeight = exdData->getField< uint8_t >( row, 30 );
  vieraMaleCameraHeight = exdData->getField< uint8_t >( row, 31 );
  vieraFemaleCameraHeight = exdData->getField< uint8_t >( row, 32 );
}

Sapphire::Data::MountFlyingCondition::MountFlyingCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MountFlyingConditionDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::MountSpeed::MountSpeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MountSpeedDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::MountTransient::MountTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MountTransientDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
  descriptionEnhanced = exdData->getField< std::string >( row, 1 );
  tooltip = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::MoveTimeline::MoveTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MoveTimelineDat.get_row( row_id );
  idle = exdData->getField< uint16_t >( row, 0 );
  moveForward = exdData->getField< uint16_t >( row, 1 );
  moveBack = exdData->getField< uint16_t >( row, 2 );
  moveLeft = exdData->getField< uint16_t >( row, 3 );
  moveRight = exdData->getField< uint16_t >( row, 4 );
  moveUp = exdData->getField< uint16_t >( row, 5 );
  moveDown = exdData->getField< uint16_t >( row, 6 );
  moveTurnLeft = exdData->getField< uint16_t >( row, 7 );
  moveTurnRight = exdData->getField< uint16_t >( row, 8 );
  extra = exdData->getField< uint16_t >( row, 9 );
}

Sapphire::Data::MoveVfx::MoveVfx( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MoveVfxDat.get_row( row_id );
  vFXNormal = exdData->getField< uint16_t >( row, 0 );
  vFXWalking = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::MovieStaffList::MovieStaffList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MovieStaffListDat.get_row( row_id );
  image = exdData->getField< uint32_t >( row, 0 );
  startTime = exdData->getField< float >( row, 1 );
  endTime = exdData->getField< float >( row, 2 );
}

Sapphire::Data::MovieSubtitle::MovieSubtitle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MovieSubtitleDat.get_row( row_id );
  startTime = exdData->getField< float >( row, 0 );
  endTime = exdData->getField< float >( row, 1 );
}

Sapphire::Data::MovieSubtitle500::MovieSubtitle500( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MovieSubtitle500Dat.get_row( row_id );
  startTime = exdData->getField< float >( row, 0 );
  endTime = exdData->getField< float >( row, 1 );
}

Sapphire::Data::MovieSubtitleVoyage::MovieSubtitleVoyage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MovieSubtitleVoyageDat.get_row( row_id );
  startTime = exdData->getField< float >( row, 0 );
  endTime = exdData->getField< float >( row, 1 );
}

Sapphire::Data::MYCTemporaryItem::MYCTemporaryItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MYCTemporaryItemDat.get_row( row_id );
  category = exdData->getField< uint8_t >( row, 0 );
  type = exdData->getField< uint8_t >( row, 1 );
  action = exdData->getField< uint32_t >( row, 2 );
  max = exdData->getField< uint8_t >( row, 3 );
  weight = exdData->getField< uint8_t >( row, 4 );
  order = exdData->getField< uint8_t >( row, 5 );
}

Sapphire::Data::MYCTemporaryItemUICategory::MYCTemporaryItemUICategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MYCTemporaryItemUICategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::MYCWarResultNotebook::MYCWarResultNotebook( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_MYCWarResultNotebookDat.get_row( row_id );
  number = exdData->getField< uint8_t >( row, 0 );
  unknown540 = exdData->getField< uint8_t >( row, 1 );
  unknown541 = exdData->getField< uint8_t >( row, 2 );
  quest = exdData->getField< int32_t >( row, 3 );
  icon = exdData->getField< int32_t >( row, 4 );
  image = exdData->getField< int32_t >( row, 5 );
  rarity = exdData->getField< uint8_t >( row, 6 );
  nameJP = exdData->getField< std::string >( row, 7 );
  name = exdData->getField< std::string >( row, 8 );
  description = exdData->getField< std::string >( row, 9 );
}

Sapphire::Data::NotebookDivision::NotebookDivision( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_NotebookDivisionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  notebookDivisionCategory = exdData->getField< uint8_t >( row, 1 );
  craftOpeningLevel = exdData->getField< uint8_t >( row, 2 );
  gatheringOpeningLevel = exdData->getField< uint8_t >( row, 3 );
  questUnlock = exdData->getField< uint32_t >( row, 4 );
  cRPCraft = exdData->getField< bool >( row, 7 );
  bSMCraft = exdData->getField< bool >( row, 8 );
  aRMCraft = exdData->getField< bool >( row, 9 );
  gSMCraft = exdData->getField< bool >( row, 10 );
  lTWCraft = exdData->getField< bool >( row, 11 );
  wVRCraft = exdData->getField< bool >( row, 12 );
  aLCCraft = exdData->getField< bool >( row, 13 );
  cULCraft = exdData->getField< bool >( row, 14 );
}

Sapphire::Data::NotebookDivisionCategory::NotebookDivisionCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_NotebookDivisionCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  index = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::NotoriousMonster::NotoriousMonster( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_NotoriousMonsterDat.get_row( row_id );
  bNpcBase = exdData->getField< int32_t >( row, 0 );
  rank = exdData->getField< uint8_t >( row, 1 );
  bNpcName = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::NpcEquip::NpcEquip( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_NpcEquipDat.get_row( row_id );
  modelMainHand = exdData->getField< uint64_t >( row, 0 );
  dyeMainHand = exdData->getField< uint8_t >( row, 1 );
  modelOffHand = exdData->getField< uint64_t >( row, 2 );
  dyeOffHand = exdData->getField< uint8_t >( row, 3 );
  modelHead = exdData->getField< uint32_t >( row, 4 );
  dyeHead = exdData->getField< uint8_t >( row, 5 );
  visor = exdData->getField< bool >( row, 6 );
  modelBody = exdData->getField< uint32_t >( row, 7 );
  dyeBody = exdData->getField< uint8_t >( row, 8 );
  modelHands = exdData->getField< uint32_t >( row, 9 );
  dyeHands = exdData->getField< uint8_t >( row, 10 );
  modelLegs = exdData->getField< uint32_t >( row, 11 );
  dyeLegs = exdData->getField< uint8_t >( row, 12 );
  modelFeet = exdData->getField< uint32_t >( row, 13 );
  dyeFeet = exdData->getField< uint8_t >( row, 14 );
  modelEars = exdData->getField< uint32_t >( row, 15 );
  dyeEars = exdData->getField< uint8_t >( row, 16 );
  modelNeck = exdData->getField< uint32_t >( row, 17 );
  dyeNeck = exdData->getField< uint8_t >( row, 18 );
  modelWrists = exdData->getField< uint32_t >( row, 19 );
  dyeWrists = exdData->getField< uint8_t >( row, 20 );
  modelLeftRing = exdData->getField< uint32_t >( row, 21 );
  dyeLeftRing = exdData->getField< uint8_t >( row, 22 );
  modelRightRing = exdData->getField< uint32_t >( row, 23 );
  dyeRightRing = exdData->getField< uint8_t >( row, 24 );
}

Sapphire::Data::NpcYell::NpcYell( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_NpcYellDat.get_row( row_id );
  outputType = exdData->getField< uint8_t >( row, 5 );
  balloonTime = exdData->getField< float >( row, 6 );
  isBalloonSlow = exdData->getField< bool >( row, 7 );
  battleTalkTime = exdData->getField< bool >( row, 8 );
  unknown54 = exdData->getField< uint8_t >( row, 9 );
  text = exdData->getField< std::string >( row, 10 );
}

Sapphire::Data::Omen::Omen( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OmenDat.get_row( row_id );
  path = exdData->getField< std::string >( row, 0 );
  pathAlly = exdData->getField< std::string >( row, 1 );
  type = exdData->getField< uint8_t >( row, 2 );
  restrictYScale = exdData->getField< bool >( row, 3 );
  largeScale = exdData->getField< bool >( row, 4 );
}

Sapphire::Data::OnlineStatus::OnlineStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OnlineStatusDat.get_row( row_id );
  list = exdData->getField< bool >( row, 0 );
  priority = exdData->getField< uint8_t >( row, 2 );
  name = exdData->getField< std::string >( row, 3 );
  icon = exdData->getField< uint32_t >( row, 4 );
}

Sapphire::Data::OpenContent::OpenContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OpenContentDat.get_row( row_id );
  content.push_back( exdData->getField< uint16_t >( row, 0 ) );
  content.push_back( exdData->getField< uint16_t >( row, 1 ) );
  content.push_back( exdData->getField< uint16_t >( row, 2 ) );
  content.push_back( exdData->getField< uint16_t >( row, 3 ) );
  content.push_back( exdData->getField< uint16_t >( row, 4 ) );
  content.push_back( exdData->getField< uint16_t >( row, 5 ) );
  content.push_back( exdData->getField< uint16_t >( row, 6 ) );
  content.push_back( exdData->getField< uint16_t >( row, 7 ) );
  content.push_back( exdData->getField< uint16_t >( row, 8 ) );
  content.push_back( exdData->getField< uint16_t >( row, 9 ) );
  content.push_back( exdData->getField< uint16_t >( row, 10 ) );
  content.push_back( exdData->getField< uint16_t >( row, 11 ) );
  content.push_back( exdData->getField< uint16_t >( row, 12 ) );
  content.push_back( exdData->getField< uint16_t >( row, 13 ) );
  content.push_back( exdData->getField< uint16_t >( row, 14 ) );
  content.push_back( exdData->getField< uint16_t >( row, 15 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 16 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 17 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 18 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 19 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 20 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 21 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 22 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 23 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 24 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 25 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 26 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 27 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 28 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 29 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 30 ) );
  candidateName.push_back( exdData->getField< uint32_t >( row, 31 ) );
}

Sapphire::Data::OpenContentCandidateName::OpenContentCandidateName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OpenContentCandidateNameDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Opening::Opening( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OpeningDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  quest = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::Orchestrion::Orchestrion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OrchestrionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::OrchestrionCategory::OrchestrionCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OrchestrionCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  hideOrder = exdData->getField< uint8_t >( row, 1 );
  icon = exdData->getField< uint32_t >( row, 2 );
  order = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::OrchestrionPath::OrchestrionPath( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OrchestrionPathDat.get_row( row_id );
  file = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::OrchestrionUiparam::OrchestrionUiparam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OrchestrionUiparamDat.get_row( row_id );
  orchestrionCategory = exdData->getField< uint8_t >( row, 0 );
  order = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::Ornament::Ornament( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_OrnamentDat.get_row( row_id );
  model = exdData->getField< uint16_t >( row, 0 );
  order = exdData->getField< int16_t >( row, 4 );
  icon = exdData->getField< uint16_t >( row, 5 );
  transient = exdData->getField< uint16_t >( row, 6 );
  singular = exdData->getField< std::string >( row, 7 );
  adjective = exdData->getField< int8_t >( row, 8 );
  plural = exdData->getField< std::string >( row, 9 );
  possessivePronoun = exdData->getField< int8_t >( row, 10 );
  startsWithVowel = exdData->getField< int8_t >( row, 11 );
  pronoun = exdData->getField< int8_t >( row, 13 );
  article = exdData->getField< int8_t >( row, 14 );
}

Sapphire::Data::ParamGrow::ParamGrow( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ParamGrowDat.get_row( row_id );
  expToNext = exdData->getField< int32_t >( row, 0 );
  additionalActions = exdData->getField< uint8_t >( row, 1 );
  applyAction = exdData->getField< uint8_t >( row, 2 );
  scaledQuestXP = exdData->getField< uint16_t >( row, 3 );
  mpModifier = exdData->getField< int32_t >( row, 4 );
  baseSpeed = exdData->getField< int32_t >( row, 5 );
  levelModifier = exdData->getField< int32_t >( row, 6 );
  questExpModifier = exdData->getField< uint8_t >( row, 7 );
  hpModifier = exdData->getField< uint16_t >( row, 8 );
  huntingLogExpReward = exdData->getField< int32_t >( row, 9 );
  monsterNoteSeals = exdData->getField< int32_t >( row, 10 );
  itemLevelSync = exdData->getField< uint16_t >( row, 11 );
  properDungeon = exdData->getField< uint16_t >( row, 12 );
  properGuildOrder = exdData->getField< uint16_t >( row, 13 );
  craftingLevel = exdData->getField< uint16_t >( row, 14 );
}

Sapphire::Data::PartyContent::PartyContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PartyContentDat.get_row( row_id );
  key = exdData->getField< uint8_t >( row, 0 );
  timeLimit = exdData->getField< uint16_t >( row, 1 );
  name = exdData->getField< bool >( row, 2 );
  textDataStart = exdData->getField< uint32_t >( row, 3 );
  textDataEnd = exdData->getField< uint32_t >( row, 4 );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 5 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 6 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 7 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 8 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 9 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 10 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 11 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 12 ) );
  lGBEventObject0.push_back( exdData->getField< uint32_t >( row, 13 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 14 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 15 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 16 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 17 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 18 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 19 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 20 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 21 ) );
  lGBEventRange.push_back( exdData->getField< uint32_t >( row, 22 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 23 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 24 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 25 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 26 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 27 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 28 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 29 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 30 ) );
  lGBEventObject1.push_back( exdData->getField< uint32_t >( row, 31 ) );
  contentFinderCondition = exdData->getField< uint16_t >( row, 33 );
  image = exdData->getField< uint32_t >( row, 34 );
}

Sapphire::Data::PartyContentCutscene::PartyContentCutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PartyContentCutsceneDat.get_row( row_id );
  cutscene = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::PartyContentTextData::PartyContentTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PartyContentTextDataDat.get_row( row_id );
  data = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::PatchMark::PatchMark( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PatchMarkDat.get_row( row_id );
  category = exdData->getField< int8_t >( row, 0 );
  subCategoryType = exdData->getField< uint8_t >( row, 1 );
  subCategory = exdData->getField< uint16_t >( row, 2 );
  markID = exdData->getField< uint32_t >( row, 5 );
  version = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::Perform::Perform( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PerformDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  modelKey = exdData->getField< uint64_t >( row, 2 );
  animationStart = exdData->getField< uint16_t >( row, 3 );
  animationEnd = exdData->getField< uint16_t >( row, 4 );
  animationIdle = exdData->getField< uint16_t >( row, 5 );
  animationPlay01 = exdData->getField< uint16_t >( row, 6 );
  animationPlay02 = exdData->getField< uint16_t >( row, 7 );
  stopAnimation = exdData->getField< int32_t >( row, 8 );
  instrument = exdData->getField< std::string >( row, 9 );
  transient = exdData->getField< uint8_t >( row, 11 );
}

Sapphire::Data::PerformTransient::PerformTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PerformTransientDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Pet::Pet( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PetDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::PetAction::PetAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PetActionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< int32_t >( row, 2 );
  action = exdData->getField< uint16_t >( row, 3 );
  pet = exdData->getField< uint8_t >( row, 4 );
  masterOrder = exdData->getField< bool >( row, 5 );
  disableOrder = exdData->getField< bool >( row, 6 );
}

Sapphire::Data::PhysicsGroup::PhysicsGroup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PhysicsGroupDat.get_row( row_id );
  simulationTime.push_back( exdData->getField< float >( row, 0 ) );
  simulationTime.push_back( exdData->getField< float >( row, 1 ) );
  simulationTime.push_back( exdData->getField< float >( row, 2 ) );
  simulationTime.push_back( exdData->getField< float >( row, 3 ) );
  simulationTime.push_back( exdData->getField< float >( row, 4 ) );
  simulationTime.push_back( exdData->getField< float >( row, 5 ) );
  pS3SimulationTime.push_back( exdData->getField< float >( row, 6 ) );
  pS3SimulationTime.push_back( exdData->getField< float >( row, 7 ) );
  pS3SimulationTime.push_back( exdData->getField< float >( row, 8 ) );
  pS3SimulationTime.push_back( exdData->getField< float >( row, 9 ) );
  pS3SimulationTime.push_back( exdData->getField< float >( row, 10 ) );
  pS3SimulationTime.push_back( exdData->getField< float >( row, 11 ) );
  resetByLookAt = exdData->getField< bool >( row, 12 );
  rootFollowingGame = exdData->getField< float >( row, 13 );
  rootFollowingCutScene = exdData->getField< float >( row, 14 );
  configSwitch.push_back( exdData->getField< int8_t >( row, 15 ) );
  configSwitch.push_back( exdData->getField< int8_t >( row, 16 ) );
  configSwitch.push_back( exdData->getField< int8_t >( row, 17 ) );
  forceAttractByPhysicsOff = exdData->getField< bool >( row, 18 );
}

Sapphire::Data::PhysicsWind::PhysicsWind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PhysicsWindDat.get_row( row_id );
  threshold = exdData->getField< float >( row, 0 );
  amplitude = exdData->getField< float >( row, 1 );
  amplitudeFrequency = exdData->getField< float >( row, 2 );
  powerMin = exdData->getField< float >( row, 3 );
  powerMax = exdData->getField< float >( row, 4 );
  powerFrequency = exdData->getField< float >( row, 5 );
}

Sapphire::Data::Picture::Picture( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PictureDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  image = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::PlaceName::PlaceName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PlaceNameDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  nameNoArticle = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::PlantPotFlowerSeed::PlantPotFlowerSeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PlantPotFlowerSeedDat.get_row( row_id );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 0 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 1 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 2 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 3 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 4 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 5 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 6 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 7 ) );
  seedIcon.push_back( exdData->getField< uint32_t >( row, 8 ) );
}

Sapphire::Data::PreHandler::PreHandler( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PreHandlerDat.get_row( row_id );
  image = exdData->getField< uint32_t >( row, 1 );
  target = exdData->getField< uint32_t >( row, 2 );
  unlockQuest = exdData->getField< uint32_t >( row, 3 );
  acceptMessage = exdData->getField< uint32_t >( row, 4 );
  denyMessage = exdData->getField< uint32_t >( row, 5 );
}

Sapphire::Data::PresetCamera::PresetCamera( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PresetCameraDat.get_row( row_id );
  eID = exdData->getField< uint16_t >( row, 0 );
  posX = exdData->getField< float >( row, 1 );
  posY = exdData->getField< float >( row, 2 );
  posZ = exdData->getField< float >( row, 3 );
  elezen = exdData->getField< float >( row, 4 );
  lalafell = exdData->getField< float >( row, 5 );
  miqote = exdData->getField< float >( row, 6 );
  roe = exdData->getField< float >( row, 7 );
  hrothgar = exdData->getField< float >( row, 8 );
  viera = exdData->getField< float >( row, 9 );
  hyur_F = exdData->getField< float >( row, 10 );
  elezen_F = exdData->getField< float >( row, 11 );
  lalafell_F = exdData->getField< float >( row, 12 );
  miqote_F = exdData->getField< float >( row, 13 );
  roe_F = exdData->getField< float >( row, 14 );
  hrothgar_F = exdData->getField< float >( row, 15 );
  viera_F = exdData->getField< float >( row, 16 );
}

Sapphire::Data::PresetCameraAdjust::PresetCameraAdjust( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PresetCameraAdjustDat.get_row( row_id );
  hyur_M = exdData->getField< float >( row, 0 );
  hyur_F = exdData->getField< float >( row, 1 );
  elezen_M = exdData->getField< float >( row, 2 );
  elezen_F = exdData->getField< float >( row, 3 );
  lalafell_M = exdData->getField< float >( row, 4 );
  lalafell_F = exdData->getField< float >( row, 5 );
  miqote_M = exdData->getField< float >( row, 6 );
  miqote_F = exdData->getField< float >( row, 7 );
  roe_M = exdData->getField< float >( row, 8 );
  roe_F = exdData->getField< float >( row, 9 );
  hrothgar_M = exdData->getField< float >( row, 10 );
  hrothgar_F = exdData->getField< float >( row, 11 );
  viera_M = exdData->getField< float >( row, 12 );
  viera_F = exdData->getField< float >( row, 13 );
}

Sapphire::Data::PublicContent::PublicContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PublicContentDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  timeLimit = exdData->getField< uint16_t >( row, 1 );
  mapIcon = exdData->getField< uint32_t >( row, 2 );
  name = exdData->getField< std::string >( row, 3 );
  textDataStart = exdData->getField< uint32_t >( row, 4 );
  textDataEnd = exdData->getField< uint32_t >( row, 5 );
  contentFinderCondition = exdData->getField< uint16_t >( row, 9 );
  additionalData = exdData->getField< uint16_t >( row, 10 );
  unknown540 = exdData->getField< int32_t >( row, 13 );
  unknown541 = exdData->getField< uint16_t >( row, 14 );
  unknown542 = exdData->getField< uint16_t >( row, 15 );
}

Sapphire::Data::PublicContentCutscene::PublicContentCutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PublicContentCutsceneDat.get_row( row_id );
  cutscene = exdData->getField< uint32_t >( row, 0 );
  cutscene2 = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::PublicContentTextData::PublicContentTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PublicContentTextDataDat.get_row( row_id );
  textData = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Purify::Purify( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PurifyDat.get_row( row_id );
  _class = exdData->getField< uint8_t >( row, 0 );
  level = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::PvPAction::PvPAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PvPActionDat.get_row( row_id );
  action = exdData->getField< uint16_t >( row, 0 );
  grandCompany.push_back( exdData->getField< bool >( row, 5 ) );
  grandCompany.push_back( exdData->getField< bool >( row, 6 ) );
  grandCompany.push_back( exdData->getField< bool >( row, 7 ) );
}

Sapphire::Data::PvPActionSort::PvPActionSort( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PvPActionSortDat.get_row( row_id, subRow );
  name = exdData->getField< uint8_t >( row, 0 );
  action = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::PvPRank::PvPRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PvPRankDat.get_row( row_id );
  expRequired = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::PvPSelectTrait::PvPSelectTrait( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PvPSelectTraitDat.get_row( row_id );
  effect = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< uint32_t >( row, 1 );
  value = exdData->getField< int16_t >( row, 2 );
}

Sapphire::Data::PvPTrait::PvPTrait( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_PvPTraitDat.get_row( row_id );
  trait1 = exdData->getField< uint16_t >( row, 0 );
  trait2 = exdData->getField< uint16_t >( row, 1 );
  trait3 = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::Quest::Quest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  id = exdData->getField< std::string >( row, 1 );
  expansion = exdData->getField< uint8_t >( row, 2 );
  classJobCategory0 = exdData->getField< uint8_t >( row, 3 );
  classJobLevel0 = exdData->getField< uint16_t >( row, 4 );
  questLevelOffset = exdData->getField< uint8_t >( row, 5 );
  classJobCategory1 = exdData->getField< uint8_t >( row, 6 );
  classJobLevel1 = exdData->getField< uint16_t >( row, 7 );
  previousQuestJoin = exdData->getField< uint8_t >( row, 8 );
  previousQuest0 = exdData->getField< uint32_t >( row, 9 );
  previousQuest1 = exdData->getField< uint32_t >( row, 11 );
  previousQuest2 = exdData->getField< uint32_t >( row, 12 );
  questLockJoin = exdData->getField< uint8_t >( row, 13 );
  questLock.push_back( exdData->getField< uint32_t >( row, 14 ) );
  questLock.push_back( exdData->getField< uint32_t >( row, 15 ) );
  header = exdData->getField< uint16_t >( row, 16 );
  classJobUnlock = exdData->getField< uint8_t >( row, 19 );
  grandCompany = exdData->getField< uint8_t >( row, 20 );
  grandCompanyRank = exdData->getField< uint8_t >( row, 21 );
  instanceContentJoin = exdData->getField< uint8_t >( row, 22 );
  instanceContent.push_back( exdData->getField< uint32_t >( row, 23 ) );
  instanceContent.push_back( exdData->getField< uint32_t >( row, 24 ) );
  instanceContent.push_back( exdData->getField< uint32_t >( row, 25 ) );
  festival = exdData->getField< uint8_t >( row, 26 );
  festivalBegin = exdData->getField< uint8_t >( row, 27 );
  festivalEnd = exdData->getField< uint8_t >( row, 28 );
  bellStart = exdData->getField< uint16_t >( row, 29 );
  bellEnd = exdData->getField< uint16_t >( row, 30 );
  beastTribe = exdData->getField< uint8_t >( row, 31 );
  beastReputationRank = exdData->getField< uint8_t >( row, 32 );
  beastReputationValue = exdData->getField< uint16_t >( row, 33 );
  mountRequired = exdData->getField< int32_t >( row, 36 );
  isHouseRequired = exdData->getField< bool >( row, 37 );
  deliveryQuest = exdData->getField< uint8_t >( row, 38 );
  issuerStart = exdData->getField< uint32_t >( row, 39 );
  issuerLocation = exdData->getField< uint32_t >( row, 40 );
  clientBehavior = exdData->getField< uint16_t >( row, 41 );
  targetEnd = exdData->getField< uint32_t >( row, 42 );
  isRepeatable = exdData->getField< bool >( row, 43 );
  repeatIntervalType = exdData->getField< uint8_t >( row, 44 );
  questRepeatFlag = exdData->getField< uint8_t >( row, 45 );
  canCancel = exdData->getField< bool >( row, 46 );
  type = exdData->getField< uint8_t >( row, 47 );
  questClassJobSupply = exdData->getField< uint16_t >( row, 48 );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 49 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 50 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 51 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 52 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 53 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 54 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 55 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 56 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 57 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 58 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 59 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 60 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 61 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 62 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 63 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 64 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 65 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 66 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 67 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 68 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 69 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 70 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 71 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 72 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 73 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 74 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 75 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 76 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 77 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 78 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 79 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 80 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 81 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 82 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 83 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 84 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 85 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 86 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 87 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 88 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 89 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 90 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 91 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 92 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 93 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 94 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 95 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 96 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 97 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 98 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 99 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 100 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 101 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 102 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 103 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 104 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 105 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 106 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 107 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 108 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 109 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 110 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 111 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 112 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 113 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 114 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 115 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 116 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 117 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 118 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 119 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 120 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 121 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 122 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 123 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 124 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 125 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 126 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 127 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 128 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 129 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 130 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 131 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 132 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 133 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 134 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 135 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 136 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 137 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 138 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 139 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 140 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 141 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 142 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 143 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 144 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 145 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 146 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 147 ) );
  scriptArg.push_back( exdData->getField< uint32_t >( row, 148 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 149 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 150 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 151 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 152 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 153 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 154 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 155 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 156 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 157 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 158 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 159 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 160 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 161 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 162 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 163 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 164 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 165 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 166 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 167 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 168 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 169 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 170 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 171 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 172 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 173 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 174 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 175 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 176 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 177 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 178 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 179 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 180 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 181 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 182 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 183 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 184 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 185 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 186 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 187 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 188 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 189 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 190 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 191 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 192 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 193 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 194 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 195 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 196 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 197 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 198 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 199 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 200 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 201 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 202 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 203 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 204 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 205 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 206 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 207 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 208 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 209 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 210 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 211 ) );
  actorSpawnSeq.push_back( exdData->getField< uint8_t >( row, 212 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 213 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 214 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 215 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 216 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 217 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 218 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 219 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 220 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 221 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 222 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 223 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 224 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 225 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 226 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 227 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 228 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 229 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 230 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 231 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 232 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 233 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 234 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 235 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 236 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 237 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 238 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 239 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 240 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 241 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 242 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 243 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 244 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 245 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 246 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 247 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 248 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 249 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 250 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 251 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 252 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 253 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 254 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 255 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 256 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 257 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 258 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 259 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 260 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 261 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 262 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 263 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 264 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 265 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 266 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 267 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 268 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 269 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 270 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 271 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 272 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 273 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 274 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 275 ) );
  actorDespawnSeq.push_back( exdData->getField< uint8_t >( row, 276 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 277 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 278 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 279 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 280 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 281 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 282 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 283 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 284 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 285 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 286 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 287 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 288 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 289 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 290 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 291 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 292 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 293 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 294 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 295 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 296 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 297 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 298 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 299 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 300 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 301 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 302 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 303 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 304 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 305 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 306 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 307 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 308 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 309 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 310 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 311 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 312 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 313 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 314 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 315 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 316 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 317 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 318 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 319 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 320 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 321 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 322 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 323 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 324 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 325 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 326 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 327 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 328 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 329 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 330 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 331 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 332 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 333 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 334 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 335 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 336 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 337 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 338 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 339 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 340 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 341 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 342 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 343 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 344 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 345 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 346 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 347 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 348 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 349 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 350 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 351 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 352 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 353 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 354 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 355 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 356 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 357 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 358 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 359 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 360 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 361 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 362 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 363 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 364 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 365 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 366 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 367 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 368 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 369 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 370 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 371 ) );
  questUInt8A.push_back( exdData->getField< uint8_t >( row, 372 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 373 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 374 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 375 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 376 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 377 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 378 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 379 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 380 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 381 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 382 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 383 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 384 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 385 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 386 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 387 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 388 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 389 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 390 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 391 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 392 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 393 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 394 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 395 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 396 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 397 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 398 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 399 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 400 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 401 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 402 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 403 ) );
  questUInt8B.push_back( exdData->getField< uint8_t >( row, 404 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 405 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 406 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 407 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 408 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 409 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 410 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 411 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 412 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 413 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 414 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 415 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 416 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 417 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 418 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 419 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 420 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 421 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 422 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 423 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 424 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 425 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 426 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 427 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 428 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 429 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 430 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 431 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 432 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 433 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 434 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 435 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 436 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 437 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 438 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 439 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 440 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 441 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 442 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 443 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 444 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 445 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 446 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 447 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 448 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 449 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 450 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 451 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 452 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 453 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 454 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 455 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 456 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 457 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 458 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 459 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 460 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 461 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 462 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 463 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 464 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 465 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 466 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 467 ) );
  conditionType.push_back( exdData->getField< uint8_t >( row, 468 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 469 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 470 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 471 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 472 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 473 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 474 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 475 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 476 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 477 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 478 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 479 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 480 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 481 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 482 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 483 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 484 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 485 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 486 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 487 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 488 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 489 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 490 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 491 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 492 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 493 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 494 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 495 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 496 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 497 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 498 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 499 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 500 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 501 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 502 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 503 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 504 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 505 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 506 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 507 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 508 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 509 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 510 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 511 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 512 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 513 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 514 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 515 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 516 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 517 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 518 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 519 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 520 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 521 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 522 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 523 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 524 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 525 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 526 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 527 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 528 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 529 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 530 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 531 ) );
  conditionValue.push_back( exdData->getField< uint32_t >( row, 532 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 533 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 534 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 535 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 536 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 537 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 538 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 539 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 540 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 541 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 542 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 543 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 544 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 545 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 546 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 547 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 548 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 549 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 550 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 551 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 552 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 553 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 554 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 555 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 556 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 557 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 558 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 559 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 560 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 561 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 562 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 563 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 564 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 565 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 566 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 567 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 568 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 569 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 570 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 571 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 572 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 573 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 574 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 575 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 576 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 577 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 578 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 579 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 580 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 581 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 582 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 583 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 584 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 585 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 586 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 587 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 588 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 589 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 590 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 591 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 592 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 593 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 594 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 595 ) );
  conditionOperator.push_back( exdData->getField< uint8_t >( row, 596 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 597 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 598 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 599 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 600 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 601 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 602 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 603 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 604 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 605 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 606 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 607 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 608 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 609 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 610 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 611 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 612 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 613 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 614 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 615 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 616 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 617 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 618 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 619 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 620 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 621 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 622 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 623 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 624 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 625 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 626 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 627 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 628 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 629 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 630 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 631 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 632 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 633 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 634 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 635 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 636 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 637 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 638 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 639 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 640 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 641 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 642 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 643 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 644 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 645 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 646 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 647 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 648 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 649 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 650 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 651 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 652 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 653 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 654 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 655 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 656 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 657 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 658 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 659 ) );
  behavior.push_back( exdData->getField< uint16_t >( row, 660 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 661 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 662 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 663 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 664 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 665 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 666 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 667 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 668 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 669 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 670 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 671 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 672 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 673 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 674 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 675 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 676 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 677 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 678 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 679 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 680 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 681 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 682 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 683 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 684 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 685 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 686 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 687 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 688 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 689 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 690 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 691 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 692 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 693 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 694 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 695 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 696 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 697 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 698 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 699 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 700 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 701 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 702 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 703 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 704 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 705 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 706 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 707 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 708 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 709 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 710 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 711 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 712 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 713 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 714 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 715 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 716 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 717 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 718 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 719 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 720 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 721 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 722 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 723 ) );
  visibleBool.push_back( exdData->getField< bool >( row, 724 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 725 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 726 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 727 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 728 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 729 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 730 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 731 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 732 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 733 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 734 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 735 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 736 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 737 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 738 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 739 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 740 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 741 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 742 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 743 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 744 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 745 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 746 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 747 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 748 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 749 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 750 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 751 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 752 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 753 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 754 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 755 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 756 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 757 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 758 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 759 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 760 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 761 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 762 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 763 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 764 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 765 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 766 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 767 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 768 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 769 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 770 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 771 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 772 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 773 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 774 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 775 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 776 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 777 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 778 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 779 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 780 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 781 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 782 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 783 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 784 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 785 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 786 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 787 ) );
  conditionBool.push_back( exdData->getField< bool >( row, 788 ) );
  itemBool.push_back( exdData->getField< bool >( row, 789 ) );
  itemBool.push_back( exdData->getField< bool >( row, 790 ) );
  itemBool.push_back( exdData->getField< bool >( row, 791 ) );
  itemBool.push_back( exdData->getField< bool >( row, 792 ) );
  itemBool.push_back( exdData->getField< bool >( row, 793 ) );
  itemBool.push_back( exdData->getField< bool >( row, 794 ) );
  itemBool.push_back( exdData->getField< bool >( row, 795 ) );
  itemBool.push_back( exdData->getField< bool >( row, 796 ) );
  itemBool.push_back( exdData->getField< bool >( row, 797 ) );
  itemBool.push_back( exdData->getField< bool >( row, 798 ) );
  itemBool.push_back( exdData->getField< bool >( row, 799 ) );
  itemBool.push_back( exdData->getField< bool >( row, 800 ) );
  itemBool.push_back( exdData->getField< bool >( row, 801 ) );
  itemBool.push_back( exdData->getField< bool >( row, 802 ) );
  itemBool.push_back( exdData->getField< bool >( row, 803 ) );
  itemBool.push_back( exdData->getField< bool >( row, 804 ) );
  itemBool.push_back( exdData->getField< bool >( row, 805 ) );
  itemBool.push_back( exdData->getField< bool >( row, 806 ) );
  itemBool.push_back( exdData->getField< bool >( row, 807 ) );
  itemBool.push_back( exdData->getField< bool >( row, 808 ) );
  itemBool.push_back( exdData->getField< bool >( row, 809 ) );
  itemBool.push_back( exdData->getField< bool >( row, 810 ) );
  itemBool.push_back( exdData->getField< bool >( row, 811 ) );
  itemBool.push_back( exdData->getField< bool >( row, 812 ) );
  itemBool.push_back( exdData->getField< bool >( row, 813 ) );
  itemBool.push_back( exdData->getField< bool >( row, 814 ) );
  itemBool.push_back( exdData->getField< bool >( row, 815 ) );
  itemBool.push_back( exdData->getField< bool >( row, 816 ) );
  itemBool.push_back( exdData->getField< bool >( row, 817 ) );
  itemBool.push_back( exdData->getField< bool >( row, 818 ) );
  itemBool.push_back( exdData->getField< bool >( row, 819 ) );
  itemBool.push_back( exdData->getField< bool >( row, 820 ) );
  itemBool.push_back( exdData->getField< bool >( row, 821 ) );
  itemBool.push_back( exdData->getField< bool >( row, 822 ) );
  itemBool.push_back( exdData->getField< bool >( row, 823 ) );
  itemBool.push_back( exdData->getField< bool >( row, 824 ) );
  itemBool.push_back( exdData->getField< bool >( row, 825 ) );
  itemBool.push_back( exdData->getField< bool >( row, 826 ) );
  itemBool.push_back( exdData->getField< bool >( row, 827 ) );
  itemBool.push_back( exdData->getField< bool >( row, 828 ) );
  itemBool.push_back( exdData->getField< bool >( row, 829 ) );
  itemBool.push_back( exdData->getField< bool >( row, 830 ) );
  itemBool.push_back( exdData->getField< bool >( row, 831 ) );
  itemBool.push_back( exdData->getField< bool >( row, 832 ) );
  itemBool.push_back( exdData->getField< bool >( row, 833 ) );
  itemBool.push_back( exdData->getField< bool >( row, 834 ) );
  itemBool.push_back( exdData->getField< bool >( row, 835 ) );
  itemBool.push_back( exdData->getField< bool >( row, 836 ) );
  itemBool.push_back( exdData->getField< bool >( row, 837 ) );
  itemBool.push_back( exdData->getField< bool >( row, 838 ) );
  itemBool.push_back( exdData->getField< bool >( row, 839 ) );
  itemBool.push_back( exdData->getField< bool >( row, 840 ) );
  itemBool.push_back( exdData->getField< bool >( row, 841 ) );
  itemBool.push_back( exdData->getField< bool >( row, 842 ) );
  itemBool.push_back( exdData->getField< bool >( row, 843 ) );
  itemBool.push_back( exdData->getField< bool >( row, 844 ) );
  itemBool.push_back( exdData->getField< bool >( row, 845 ) );
  itemBool.push_back( exdData->getField< bool >( row, 846 ) );
  itemBool.push_back( exdData->getField< bool >( row, 847 ) );
  itemBool.push_back( exdData->getField< bool >( row, 848 ) );
  itemBool.push_back( exdData->getField< bool >( row, 849 ) );
  itemBool.push_back( exdData->getField< bool >( row, 850 ) );
  itemBool.push_back( exdData->getField< bool >( row, 851 ) );
  itemBool.push_back( exdData->getField< bool >( row, 852 ) );
  announceBool.push_back( exdData->getField< bool >( row, 853 ) );
  announceBool.push_back( exdData->getField< bool >( row, 854 ) );
  announceBool.push_back( exdData->getField< bool >( row, 855 ) );
  announceBool.push_back( exdData->getField< bool >( row, 856 ) );
  announceBool.push_back( exdData->getField< bool >( row, 857 ) );
  announceBool.push_back( exdData->getField< bool >( row, 858 ) );
  announceBool.push_back( exdData->getField< bool >( row, 859 ) );
  announceBool.push_back( exdData->getField< bool >( row, 860 ) );
  announceBool.push_back( exdData->getField< bool >( row, 861 ) );
  announceBool.push_back( exdData->getField< bool >( row, 862 ) );
  announceBool.push_back( exdData->getField< bool >( row, 863 ) );
  announceBool.push_back( exdData->getField< bool >( row, 864 ) );
  announceBool.push_back( exdData->getField< bool >( row, 865 ) );
  announceBool.push_back( exdData->getField< bool >( row, 866 ) );
  announceBool.push_back( exdData->getField< bool >( row, 867 ) );
  announceBool.push_back( exdData->getField< bool >( row, 868 ) );
  announceBool.push_back( exdData->getField< bool >( row, 869 ) );
  announceBool.push_back( exdData->getField< bool >( row, 870 ) );
  announceBool.push_back( exdData->getField< bool >( row, 871 ) );
  announceBool.push_back( exdData->getField< bool >( row, 872 ) );
  announceBool.push_back( exdData->getField< bool >( row, 873 ) );
  announceBool.push_back( exdData->getField< bool >( row, 874 ) );
  announceBool.push_back( exdData->getField< bool >( row, 875 ) );
  announceBool.push_back( exdData->getField< bool >( row, 876 ) );
  announceBool.push_back( exdData->getField< bool >( row, 877 ) );
  announceBool.push_back( exdData->getField< bool >( row, 878 ) );
  announceBool.push_back( exdData->getField< bool >( row, 879 ) );
  announceBool.push_back( exdData->getField< bool >( row, 880 ) );
  announceBool.push_back( exdData->getField< bool >( row, 881 ) );
  announceBool.push_back( exdData->getField< bool >( row, 882 ) );
  announceBool.push_back( exdData->getField< bool >( row, 883 ) );
  announceBool.push_back( exdData->getField< bool >( row, 884 ) );
  announceBool.push_back( exdData->getField< bool >( row, 885 ) );
  announceBool.push_back( exdData->getField< bool >( row, 886 ) );
  announceBool.push_back( exdData->getField< bool >( row, 887 ) );
  announceBool.push_back( exdData->getField< bool >( row, 888 ) );
  announceBool.push_back( exdData->getField< bool >( row, 889 ) );
  announceBool.push_back( exdData->getField< bool >( row, 890 ) );
  announceBool.push_back( exdData->getField< bool >( row, 891 ) );
  announceBool.push_back( exdData->getField< bool >( row, 892 ) );
  announceBool.push_back( exdData->getField< bool >( row, 893 ) );
  announceBool.push_back( exdData->getField< bool >( row, 894 ) );
  announceBool.push_back( exdData->getField< bool >( row, 895 ) );
  announceBool.push_back( exdData->getField< bool >( row, 896 ) );
  announceBool.push_back( exdData->getField< bool >( row, 897 ) );
  announceBool.push_back( exdData->getField< bool >( row, 898 ) );
  announceBool.push_back( exdData->getField< bool >( row, 899 ) );
  announceBool.push_back( exdData->getField< bool >( row, 900 ) );
  announceBool.push_back( exdData->getField< bool >( row, 901 ) );
  announceBool.push_back( exdData->getField< bool >( row, 902 ) );
  announceBool.push_back( exdData->getField< bool >( row, 903 ) );
  announceBool.push_back( exdData->getField< bool >( row, 904 ) );
  announceBool.push_back( exdData->getField< bool >( row, 905 ) );
  announceBool.push_back( exdData->getField< bool >( row, 906 ) );
  announceBool.push_back( exdData->getField< bool >( row, 907 ) );
  announceBool.push_back( exdData->getField< bool >( row, 908 ) );
  announceBool.push_back( exdData->getField< bool >( row, 909 ) );
  announceBool.push_back( exdData->getField< bool >( row, 910 ) );
  announceBool.push_back( exdData->getField< bool >( row, 911 ) );
  announceBool.push_back( exdData->getField< bool >( row, 912 ) );
  announceBool.push_back( exdData->getField< bool >( row, 913 ) );
  announceBool.push_back( exdData->getField< bool >( row, 914 ) );
  announceBool.push_back( exdData->getField< bool >( row, 915 ) );
  announceBool.push_back( exdData->getField< bool >( row, 916 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 917 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 918 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 919 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 920 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 921 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 922 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 923 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 924 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 925 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 926 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 927 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 928 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 929 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 930 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 931 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 932 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 933 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 934 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 935 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 936 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 937 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 938 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 939 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 940 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 941 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 942 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 943 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 944 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 945 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 946 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 947 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 948 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 949 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 950 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 951 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 952 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 953 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 954 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 955 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 956 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 957 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 958 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 959 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 960 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 961 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 962 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 963 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 964 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 965 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 966 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 967 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 968 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 969 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 970 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 971 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 972 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 973 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 974 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 975 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 976 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 977 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 978 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 979 ) );
  behaviorBool.push_back( exdData->getField< bool >( row, 980 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 981 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 982 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 983 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 984 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 985 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 986 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 987 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 988 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 989 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 990 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 991 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 992 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 993 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 994 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 995 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 996 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 997 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 998 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 999 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1000 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1001 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1002 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1003 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1004 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1005 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1006 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1007 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1008 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1009 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1010 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1011 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1012 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1013 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1014 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1015 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1016 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1017 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1018 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1019 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1020 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1021 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1022 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1023 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1024 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1025 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1026 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1027 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1028 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1029 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1030 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1031 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1032 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1033 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1034 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1035 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1036 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1037 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1038 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1039 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1040 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1041 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1042 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1043 ) );
  acceptBool.push_back( exdData->getField< bool >( row, 1044 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1045 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1046 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1047 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1048 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1049 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1050 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1051 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1052 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1053 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1054 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1055 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1056 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1057 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1058 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1059 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1060 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1061 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1062 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1063 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1064 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1065 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1066 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1067 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1068 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1069 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1070 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1071 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1072 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1073 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1074 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1075 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1076 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1077 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1078 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1079 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1080 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1081 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1082 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1083 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1084 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1085 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1086 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1087 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1088 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1089 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1090 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1091 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1092 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1093 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1094 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1095 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1096 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1097 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1098 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1099 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1100 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1101 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1102 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1103 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1104 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1105 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1106 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1107 ) );
  qualifiedBool.push_back( exdData->getField< bool >( row, 1108 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1109 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1110 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1111 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1112 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1113 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1114 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1115 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1116 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1117 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1118 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1119 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1120 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1121 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1122 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1123 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1124 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1125 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1126 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1127 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1128 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1129 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1130 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1131 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1132 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1133 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1134 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1135 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1136 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1137 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1138 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1139 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1140 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1141 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1142 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1143 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1144 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1145 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1146 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1147 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1148 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1149 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1150 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1151 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1152 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1153 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1154 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1155 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1156 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1157 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1158 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1159 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1160 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1161 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1162 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1163 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1164 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1165 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1166 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1167 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1168 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1169 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1170 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1171 ) );
  canTargetBool.push_back( exdData->getField< bool >( row, 1172 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1173 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1174 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1175 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1176 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1177 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1178 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1179 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1180 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1181 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1182 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1183 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1184 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1185 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1186 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1187 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1188 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1189 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1190 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1191 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1192 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1193 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1194 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1195 ) );
  toDoCompleteSeq.push_back( exdData->getField< uint8_t >( row, 1196 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1197 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1198 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1199 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1200 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1201 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1202 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1203 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1204 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1205 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1206 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1207 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1208 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1209 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1210 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1211 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1212 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1213 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1214 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1215 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1216 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1217 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1218 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1219 ) );
  toDoQty.push_back( exdData->getField< uint8_t >( row, 1220 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1221 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1222 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1223 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1224 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1225 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1226 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1227 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1228 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1229 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1230 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1231 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1232 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1233 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1234 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1235 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1236 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1237 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1238 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1239 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1240 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1241 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1242 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1243 ) );
  toDoMainLocation.push_back( exdData->getField< uint32_t >( row, 1244 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1413 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1414 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1415 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1416 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1417 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1418 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1419 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1420 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1421 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1422 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1423 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1424 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1425 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1426 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1427 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1428 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1429 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1430 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1431 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1432 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1433 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1434 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1435 ) );
  countableNum.push_back( exdData->getField< uint8_t >( row, 1436 ) );
  levelMax = exdData->getField< uint8_t >( row, 1437 );
  classJobRequired = exdData->getField< uint8_t >( row, 1438 );
  expFactor = exdData->getField< uint16_t >( row, 1440 );
  gilReward = exdData->getField< uint32_t >( row, 1441 );
  gCSeals = exdData->getField< uint16_t >( row, 1443 );
  itemCatalyst.push_back( exdData->getField< uint8_t >( row, 1444 ) );
  itemCatalyst.push_back( exdData->getField< uint8_t >( row, 1445 ) );
  itemCatalyst.push_back( exdData->getField< uint8_t >( row, 1446 ) );
  itemCountCatalyst.push_back( exdData->getField< uint8_t >( row, 1447 ) );
  itemCountCatalyst.push_back( exdData->getField< uint8_t >( row, 1448 ) );
  itemCountCatalyst.push_back( exdData->getField< uint8_t >( row, 1449 ) );
  itemRewardType = exdData->getField< uint8_t >( row, 1450 );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1451 ) );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1452 ) );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1453 ) );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1454 ) );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1455 ) );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1456 ) );
  itemReward0.push_back( exdData->getField< uint32_t >( row, 1457 ) );
  itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1458 ) );
  itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1459 ) );
  itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1460 ) );
  itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1461 ) );
  itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1462 ) );
  itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1463 ) );
  stainReward0.push_back( exdData->getField< uint8_t >( row, 1465 ) );
  stainReward0.push_back( exdData->getField< uint8_t >( row, 1466 ) );
  stainReward0.push_back( exdData->getField< uint8_t >( row, 1467 ) );
  stainReward0.push_back( exdData->getField< uint8_t >( row, 1468 ) );
  stainReward0.push_back( exdData->getField< uint8_t >( row, 1469 ) );
  stainReward0.push_back( exdData->getField< uint8_t >( row, 1470 ) );
  itemReward1.push_back( exdData->getField< uint32_t >( row, 1472 ) );
  itemReward1.push_back( exdData->getField< uint32_t >( row, 1473 ) );
  itemReward1.push_back( exdData->getField< uint32_t >( row, 1474 ) );
  itemReward1.push_back( exdData->getField< uint32_t >( row, 1475 ) );
  itemReward1.push_back( exdData->getField< uint32_t >( row, 1476 ) );
  itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1477 ) );
  itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1478 ) );
  itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1479 ) );
  itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1480 ) );
  itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1481 ) );
  isHQReward1.push_back( exdData->getField< bool >( row, 1482 ) );
  isHQReward1.push_back( exdData->getField< bool >( row, 1483 ) );
  isHQReward1.push_back( exdData->getField< bool >( row, 1484 ) );
  isHQReward1.push_back( exdData->getField< bool >( row, 1485 ) );
  isHQReward1.push_back( exdData->getField< bool >( row, 1486 ) );
  stainReward1.push_back( exdData->getField< uint8_t >( row, 1487 ) );
  stainReward1.push_back( exdData->getField< uint8_t >( row, 1488 ) );
  stainReward1.push_back( exdData->getField< uint8_t >( row, 1489 ) );
  stainReward1.push_back( exdData->getField< uint8_t >( row, 1490 ) );
  stainReward1.push_back( exdData->getField< uint8_t >( row, 1491 ) );
  emoteReward = exdData->getField< uint8_t >( row, 1492 );
  actionReward = exdData->getField< uint16_t >( row, 1493 );
  generalActionReward.push_back( exdData->getField< uint8_t >( row, 1494 ) );
  generalActionReward.push_back( exdData->getField< uint8_t >( row, 1495 ) );
  systemReward0 = exdData->getField< uint16_t >( row, 1496 );
  otherReward = exdData->getField< uint8_t >( row, 1497 );
  systemReward1 = exdData->getField< uint16_t >( row, 1498 );
  gCTypeReward = exdData->getField< uint16_t >( row, 1499 );
  instanceContentUnlock = exdData->getField< uint32_t >( row, 1500 );
  tomestoneReward = exdData->getField< uint8_t >( row, 1502 );
  tomestoneCountReward = exdData->getField< uint8_t >( row, 1503 );
  reputationReward = exdData->getField< uint8_t >( row, 1504 );
  placeName = exdData->getField< uint16_t >( row, 1505 );
  journalGenre = exdData->getField< uint8_t >( row, 1506 );
  icon = exdData->getField< uint32_t >( row, 1508 );
  iconSpecial = exdData->getField< uint32_t >( row, 1509 );
  introduction = exdData->getField< bool >( row, 1510 );
  hideOfferIcon = exdData->getField< bool >( row, 1511 );
  eventIconType = exdData->getField< uint8_t >( row, 1512 );
  sortKey = exdData->getField< uint16_t >( row, 1514 );
  unknown54 = exdData->getField< bool >( row, 1515 );
}

Sapphire::Data::QuestBattle::QuestBattle( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestBattleDat.get_row( row_id );
  quest = exdData->getField< int32_t >( row, 0 );
  questBattleScene = exdData->getField< uint8_t >( row, 1 );
  timeLimit = exdData->getField< uint16_t >( row, 2 );
  levelSync = exdData->getField< uint16_t >( row, 3 );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 4 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 5 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 6 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 7 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 8 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 9 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 10 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 11 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 12 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 13 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 14 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 15 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 16 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 17 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 18 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 19 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 20 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 21 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 22 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 23 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 24 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 25 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 26 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 27 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 28 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 29 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 30 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 31 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 32 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 33 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 34 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 35 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 36 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 37 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 38 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 39 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 40 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 41 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 42 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 43 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 44 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 45 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 46 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 47 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 48 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 49 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 50 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 51 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 52 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 53 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 54 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 55 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 56 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 57 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 58 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 59 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 60 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 61 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 62 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 63 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 64 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 65 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 66 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 67 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 68 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 69 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 70 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 71 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 72 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 73 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 74 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 75 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 76 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 77 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 78 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 79 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 80 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 81 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 82 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 83 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 84 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 85 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 86 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 87 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 88 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 89 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 90 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 91 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 92 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 93 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 94 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 95 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 96 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 97 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 98 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 99 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 100 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 101 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 102 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 103 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 104 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 105 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 106 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 107 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 108 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 109 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 110 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 111 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 112 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 113 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 114 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 115 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 116 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 117 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 118 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 119 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 120 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 121 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 122 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 123 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 124 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 125 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 126 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 127 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 128 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 129 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 130 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 131 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 132 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 133 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 134 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 135 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 136 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 137 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 138 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 139 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 140 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 141 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 142 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 143 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 144 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 145 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 146 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 147 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 148 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 149 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 150 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 151 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 152 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 153 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 154 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 155 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 156 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 157 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 158 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 159 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 160 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 161 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 162 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 163 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 164 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 165 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 166 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 167 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 168 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 169 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 170 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 171 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 172 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 173 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 174 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 175 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 176 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 177 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 178 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 179 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 180 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 181 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 182 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 183 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 184 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 185 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 186 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 187 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 188 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 189 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 190 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 191 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 192 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 193 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 194 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 195 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 196 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 197 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 198 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 199 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 200 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 201 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 202 ) );
  scriptInstruction.push_back( exdData->getField< std::string >( row, 203 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 204 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 205 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 206 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 207 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 208 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 209 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 210 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 211 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 212 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 213 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 214 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 215 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 216 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 217 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 218 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 219 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 220 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 221 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 222 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 223 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 224 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 225 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 226 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 227 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 228 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 229 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 230 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 231 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 232 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 233 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 234 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 235 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 236 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 237 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 238 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 239 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 240 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 241 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 242 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 243 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 244 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 245 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 246 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 247 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 248 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 249 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 250 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 251 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 252 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 253 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 254 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 255 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 256 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 257 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 258 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 259 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 260 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 261 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 262 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 263 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 264 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 265 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 266 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 267 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 268 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 269 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 270 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 271 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 272 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 273 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 274 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 275 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 276 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 277 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 278 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 279 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 280 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 281 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 282 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 283 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 284 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 285 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 286 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 287 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 288 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 289 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 290 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 291 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 292 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 293 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 294 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 295 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 296 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 297 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 298 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 299 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 300 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 301 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 302 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 303 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 304 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 305 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 306 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 307 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 308 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 309 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 310 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 311 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 312 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 313 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 314 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 315 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 316 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 317 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 318 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 319 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 320 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 321 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 322 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 323 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 324 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 325 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 326 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 327 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 328 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 329 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 330 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 331 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 332 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 333 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 334 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 335 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 336 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 337 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 338 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 339 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 340 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 341 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 342 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 343 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 344 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 345 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 346 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 347 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 348 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 349 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 350 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 351 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 352 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 353 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 354 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 355 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 356 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 357 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 358 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 359 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 360 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 361 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 362 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 363 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 364 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 365 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 366 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 367 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 368 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 369 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 370 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 371 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 372 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 373 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 374 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 375 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 376 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 377 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 378 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 379 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 380 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 381 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 382 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 383 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 384 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 385 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 386 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 387 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 388 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 389 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 390 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 391 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 392 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 393 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 394 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 395 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 396 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 397 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 398 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 399 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 400 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 401 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 402 ) );
  scriptValue.push_back( exdData->getField< uint32_t >( row, 403 ) );
}

Sapphire::Data::QuestChapter::QuestChapter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestChapterDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
  redo = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::QuestClassJobReward::QuestClassJobReward( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestClassJobRewardDat.get_row( row_id, subRow );
  classJobCategory = exdData->getField< uint8_t >( row, 0 );
  rewardItem.push_back( exdData->getField< uint32_t >( row, 1 ) );
  rewardItem.push_back( exdData->getField< uint32_t >( row, 2 ) );
  rewardItem.push_back( exdData->getField< uint32_t >( row, 3 ) );
  rewardItem.push_back( exdData->getField< uint32_t >( row, 4 ) );
  rewardAmount.push_back( exdData->getField< uint8_t >( row, 5 ) );
  rewardAmount.push_back( exdData->getField< uint8_t >( row, 6 ) );
  rewardAmount.push_back( exdData->getField< uint8_t >( row, 7 ) );
  rewardAmount.push_back( exdData->getField< uint8_t >( row, 8 ) );
  requiredItem.push_back( exdData->getField< uint32_t >( row, 9 ) );
  requiredItem.push_back( exdData->getField< uint32_t >( row, 10 ) );
  requiredItem.push_back( exdData->getField< uint32_t >( row, 11 ) );
  requiredItem.push_back( exdData->getField< uint32_t >( row, 12 ) );
  requiredAmount.push_back( exdData->getField< uint8_t >( row, 13 ) );
  requiredAmount.push_back( exdData->getField< uint8_t >( row, 14 ) );
  requiredAmount.push_back( exdData->getField< uint8_t >( row, 15 ) );
  requiredAmount.push_back( exdData->getField< uint8_t >( row, 16 ) );
}

Sapphire::Data::QuestClassJobSupply::QuestClassJobSupply( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestClassJobSupplyDat.get_row( row_id, subRow );
  classJobCategory = exdData->getField< uint8_t >( row, 0 );
  eNpcResident = exdData->getField< uint32_t >( row, 2 );
  item = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::QuestDerivedClass::QuestDerivedClass( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestDerivedClassDat.get_row( row_id );
  classJob = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::QuestRedo::QuestRedo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRedoDat.get_row( row_id );
  finalQuest = exdData->getField< uint32_t >( row, 0 );
  chapter = exdData->getField< uint16_t >( row, 2 );
  quest.push_back( exdData->getField< uint32_t >( row, 3 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 4 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 5 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 6 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 7 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 8 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 9 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 10 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 11 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 12 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 13 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 14 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 15 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 16 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 17 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 18 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 19 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 20 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 21 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 22 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 23 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 24 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 25 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 26 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 27 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 28 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 29 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 30 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 31 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 32 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 33 ) );
  quest.push_back( exdData->getField< uint32_t >( row, 34 ) );
}

Sapphire::Data::QuestRedoChapterUI::QuestRedoChapterUI( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRedoChapterUIDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
  category = exdData->getField< uint8_t >( row, 2 );
  questRedoUISmall = exdData->getField< uint32_t >( row, 4 );
  questRedoUILarge = exdData->getField< uint32_t >( row, 5 );
  questRedoUIWide = exdData->getField< uint32_t >( row, 6 );
  chapterName = exdData->getField< std::string >( row, 7 );
  chapterPart = exdData->getField< std::string >( row, 8 );
  transient = exdData->getField< std::string >( row, 9 );
}

Sapphire::Data::QuestRedoChapterUICategory::QuestRedoChapterUICategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRedoChapterUICategoryDat.get_row( row_id );
  expac = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::QuestRedoChapterUITab::QuestRedoChapterUITab( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRedoChapterUITabDat.get_row( row_id );
  icon1 = exdData->getField< uint32_t >( row, 1 );
  icon2 = exdData->getField< uint32_t >( row, 2 );
  text = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::QuestRedoIncompChapter::QuestRedoIncompChapter( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRedoIncompChapterDat.get_row( row_id, subRow );
  chapter = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::QuestRepeatFlag::QuestRepeatFlag( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRepeatFlagDat.get_row( row_id );
  quest = exdData->getField< uint32_t >( row, 0 );
}

Sapphire::Data::QuestRewardOther::QuestRewardOther( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuestRewardOtherDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::QuickChat::QuickChat( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuickChatDat.get_row( row_id );
  nameAction = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  addon = exdData->getField< int32_t >( row, 2 );
  quickChatTransient = exdData->getField< int8_t >( row, 3 );
}

Sapphire::Data::QuickChatTransient::QuickChatTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_QuickChatTransientDat.get_row( row_id );
  textOutput = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Race::Race( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RaceDat.get_row( row_id );
  masculine = exdData->getField< std::string >( row, 0 );
  feminine = exdData->getField< std::string >( row, 1 );
  rSEMBody = exdData->getField< int32_t >( row, 2 );
  rSEMHands = exdData->getField< int32_t >( row, 3 );
  rSEMLegs = exdData->getField< int32_t >( row, 4 );
  rSEMFeet = exdData->getField< int32_t >( row, 5 );
  rSEFBody = exdData->getField< int32_t >( row, 6 );
  rSEFHands = exdData->getField< int32_t >( row, 7 );
  rSEFLegs = exdData->getField< int32_t >( row, 8 );
  rSEFFeet = exdData->getField< int32_t >( row, 9 );
  unknown54 = exdData->getField< uint8_t >( row, 10 );
  exPac = exdData->getField< uint8_t >( row, 11 );
}

Sapphire::Data::RacingChocoboItem::RacingChocoboItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RacingChocoboItemDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  category = exdData->getField< uint8_t >( row, 1 );
  param.push_back( exdData->getField< uint8_t >( row, 2 ) );
  param.push_back( exdData->getField< uint8_t >( row, 3 ) );
}

Sapphire::Data::RacingChocoboName::RacingChocoboName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RacingChocoboNameDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::RacingChocoboNameCategory::RacingChocoboNameCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RacingChocoboNameCategoryDat.get_row( row_id );
  sortKey = exdData->getField< uint8_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::RacingChocoboNameInfo::RacingChocoboNameInfo( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RacingChocoboNameInfoDat.get_row( row_id );
  racingChocoboNameCategory = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::RacingChocoboParam::RacingChocoboParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RacingChocoboParamDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::RecastNavimesh::RecastNavimesh( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RecastNavimeshDat.get_row( row_id );
  tileSize = exdData->getField< float >( row, 1 );
  cellSize = exdData->getField< float >( row, 2 );
  cellHeight = exdData->getField< float >( row, 3 );
  agentHeight = exdData->getField< float >( row, 4 );
  agentRadius = exdData->getField< float >( row, 5 );
  agentMaxClimb = exdData->getField< float >( row, 6 );
  agentMaxSlope = exdData->getField< float >( row, 7 );
  regionMinSize = exdData->getField< float >( row, 9 );
  regionMergedSize = exdData->getField< float >( row, 10 );
  maxEdgeLength = exdData->getField< float >( row, 12 );
  maxEdgeError = exdData->getField< float >( row, 13 );
  vertsPerPoly = exdData->getField< float >( row, 14 );
  detailMeshSampleDistance = exdData->getField< float >( row, 15 );
  detailMeshMaxSampleError = exdData->getField< float >( row, 16 );
}

Sapphire::Data::Recipe::Recipe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RecipeDat.get_row( row_id );
  number = exdData->getField< int32_t >( row, 0 );
  craftType = exdData->getField< int32_t >( row, 1 );
  recipeLevelTable = exdData->getField< uint16_t >( row, 2 );
  itemResult = exdData->getField< int32_t >( row, 3 );
  amountResult = exdData->getField< uint8_t >( row, 4 );
  isSecondary = exdData->getField< bool >( row, 26 );
  materialQualityFactor = exdData->getField< uint8_t >( row, 27 );
  difficultyFactor = exdData->getField< uint16_t >( row, 28 );
  qualityFactor = exdData->getField< uint16_t >( row, 29 );
  durabilityFactor = exdData->getField< uint16_t >( row, 30 );
  requiredCraftsmanship = exdData->getField< uint16_t >( row, 32 );
  requiredControl = exdData->getField< uint16_t >( row, 33 );
  quickSynthCraftsmanship = exdData->getField< uint16_t >( row, 34 );
  quickSynthControl = exdData->getField< uint16_t >( row, 35 );
  secretRecipeBook = exdData->getField< uint16_t >( row, 36 );
  canQuickSynth = exdData->getField< bool >( row, 38 );
  canHq = exdData->getField< bool >( row, 39 );
  expRewarded = exdData->getField< bool >( row, 40 );
  statusRequired = exdData->getField< int32_t >( row, 41 );
  itemRequired = exdData->getField< int32_t >( row, 42 );
  isSpecializationRequired = exdData->getField< bool >( row, 43 );
  isExpert = exdData->getField< bool >( row, 44 );
  patchNumber = exdData->getField< uint16_t >( row, 45 );
}

Sapphire::Data::RecipeLevelTable::RecipeLevelTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RecipeLevelTableDat.get_row( row_id );
  classJobLevel = exdData->getField< uint8_t >( row, 0 );
  stars = exdData->getField< uint8_t >( row, 1 );
  suggestedCraftsmanship = exdData->getField< uint16_t >( row, 2 );
  suggestedControl = exdData->getField< uint16_t >( row, 3 );
  difficulty = exdData->getField< uint16_t >( row, 4 );
  quality = exdData->getField< uint32_t >( row, 5 );
  durability = exdData->getField< uint16_t >( row, 6 );
  conditionsFlag = exdData->getField< uint16_t >( row, 7 );
}

Sapphire::Data::RecipeLookup::RecipeLookup( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RecipeLookupDat.get_row( row_id );
  cRP = exdData->getField< uint16_t >( row, 0 );
  bSM = exdData->getField< uint16_t >( row, 1 );
  aRM = exdData->getField< uint16_t >( row, 2 );
  gSM = exdData->getField< uint16_t >( row, 3 );
  lTW = exdData->getField< uint16_t >( row, 4 );
  wVR = exdData->getField< uint16_t >( row, 5 );
  aLC = exdData->getField< uint16_t >( row, 6 );
  cUL = exdData->getField< uint16_t >( row, 7 );
}

Sapphire::Data::RecipeNotebookList::RecipeNotebookList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RecipeNotebookListDat.get_row( row_id );
  recipe.push_back( exdData->getField< int32_t >( row, 1 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 2 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 3 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 4 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 5 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 6 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 7 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 8 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 9 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 10 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 11 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 12 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 13 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 14 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 15 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 16 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 17 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 18 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 19 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 20 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 21 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 22 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 23 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 24 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 25 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 26 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 27 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 28 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 29 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 30 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 31 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 32 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 33 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 34 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 35 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 36 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 37 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 38 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 39 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 40 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 41 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 42 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 43 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 44 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 45 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 46 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 47 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 48 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 49 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 50 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 51 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 52 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 53 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 54 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 55 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 56 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 57 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 58 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 59 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 60 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 61 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 62 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 63 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 64 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 65 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 66 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 67 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 68 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 69 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 70 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 71 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 72 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 73 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 74 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 75 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 76 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 77 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 78 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 79 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 80 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 81 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 82 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 83 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 84 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 85 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 86 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 87 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 88 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 89 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 90 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 91 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 92 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 93 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 94 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 95 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 96 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 97 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 98 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 99 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 100 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 101 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 102 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 103 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 104 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 105 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 106 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 107 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 108 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 109 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 110 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 111 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 112 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 113 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 114 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 115 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 116 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 117 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 118 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 119 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 120 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 121 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 122 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 123 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 124 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 125 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 126 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 127 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 128 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 129 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 130 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 131 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 132 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 133 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 134 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 135 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 136 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 137 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 138 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 139 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 140 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 141 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 142 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 143 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 144 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 145 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 146 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 147 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 148 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 149 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 150 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 151 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 152 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 153 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 154 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 155 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 156 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 157 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 158 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 159 ) );
  recipe.push_back( exdData->getField< int32_t >( row, 160 ) );
}

Sapphire::Data::RecommendContents::RecommendContents( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RecommendContentsDat.get_row( row_id );
  level = exdData->getField< int32_t >( row, 0 );
  classJob = exdData->getField< uint8_t >( row, 1 );
  minLevel = exdData->getField< uint8_t >( row, 2 );
  maxLevel = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::Relic::Relic( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RelicDat.get_row( row_id );
  itemAtma = exdData->getField< uint32_t >( row, 0 );
  itemAnimus = exdData->getField< uint32_t >( row, 1 );
  icon = exdData->getField< int32_t >( row, 2 );
  materia0 = exdData->getField< uint16_t >( row, 3 );
  noteMain0 = exdData->getField< uint8_t >( row, 4 );
  noteSub0 = exdData->getField< uint8_t >( row, 5 );
  noteSelection10 = exdData->getField< uint8_t >( row, 6 );
  materia1 = exdData->getField< uint16_t >( row, 7 );
  noteMain1 = exdData->getField< uint8_t >( row, 8 );
  noteSub1 = exdData->getField< uint8_t >( row, 9 );
  noteSelection1 = exdData->getField< uint8_t >( row, 10 );
  materia2 = exdData->getField< uint16_t >( row, 11 );
  noteMain2 = exdData->getField< uint8_t >( row, 12 );
  noteSub2 = exdData->getField< uint8_t >( row, 13 );
  materia3 = exdData->getField< uint16_t >( row, 14 );
  noteSelection3 = exdData->getField< uint8_t >( row, 15 );
}

Sapphire::Data::Relic3::Relic3( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_Relic3Dat.get_row( row_id );
  itemAnimus = exdData->getField< uint32_t >( row, 0 );
  itemScroll = exdData->getField< uint32_t >( row, 1 );
  materiaLimit = exdData->getField< uint8_t >( row, 2 );
  itemNovus = exdData->getField< uint32_t >( row, 3 );
  icon = exdData->getField< int32_t >( row, 4 );
}

Sapphire::Data::RelicItem::RelicItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RelicItemDat.get_row( row_id );
  gladiatorItem = exdData->getField< uint32_t >( row, 1 );
  pugilistItem = exdData->getField< uint32_t >( row, 2 );
  marauderItem = exdData->getField< uint32_t >( row, 3 );
  lancerItem = exdData->getField< uint32_t >( row, 4 );
  archerItem = exdData->getField< uint32_t >( row, 5 );
  conjurerItem = exdData->getField< uint32_t >( row, 6 );
  thaumaturgeItem = exdData->getField< uint32_t >( row, 7 );
  arcanistSMNItem = exdData->getField< uint32_t >( row, 8 );
  arcanistSCHItem = exdData->getField< uint32_t >( row, 9 );
  shieldItem = exdData->getField< uint32_t >( row, 10 );
  rogueItem = exdData->getField< uint32_t >( row, 11 );
}

Sapphire::Data::RelicNote::RelicNote( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RelicNoteDat.get_row( row_id );
  eventItem = exdData->getField< uint32_t >( row, 0 );
  monsterNoteTargetNM.push_back( exdData->getField< uint16_t >( row, 21 ) );
  monsterNoteTargetNM.push_back( exdData->getField< uint16_t >( row, 22 ) );
  monsterNoteTargetNM.push_back( exdData->getField< uint16_t >( row, 23 ) );
  leve.push_back( exdData->getField< uint16_t >( row, 31 ) );
  leve.push_back( exdData->getField< uint16_t >( row, 32 ) );
  leve.push_back( exdData->getField< uint16_t >( row, 33 ) );
}

Sapphire::Data::RelicNoteCategory::RelicNoteCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RelicNoteCategoryDat.get_row( row_id );
  text = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::Resident::Resident( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ResidentDat.get_row( row_id, subRow );
  model = exdData->getField< uint64_t >( row, 1 );
  npcYell = exdData->getField< int32_t >( row, 2 );
  addedIn53 = exdData->getField< uint16_t >( row, 3 );
  residentMotionType = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::ResistanceWeaponAdjust::ResistanceWeaponAdjust( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ResistanceWeaponAdjustDat.get_row( row_id );
  maxTotalStats = exdData->getField< uint16_t >( row, 0 );
  maxEachStat = exdData->getField< uint16_t >( row, 1 );
  baseParam.push_back( exdData->getField< uint8_t >( row, 2 ) );
  baseParam.push_back( exdData->getField< uint8_t >( row, 3 ) );
  baseParam.push_back( exdData->getField< uint8_t >( row, 4 ) );
  baseParam.push_back( exdData->getField< uint8_t >( row, 5 ) );
  image = exdData->getField< uint32_t >( row, 6 );
}

Sapphire::Data::RetainerTask::RetainerTask( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RetainerTaskDat.get_row( row_id );
  isRandom = exdData->getField< bool >( row, 0 );
  classJobCategory = exdData->getField< uint8_t >( row, 1 );
  retainerLevel = exdData->getField< uint8_t >( row, 2 );
  retainerTaskParameter = exdData->getField< uint16_t >( row, 4 );
  ventureCost = exdData->getField< uint16_t >( row, 5 );
  maxTimemin = exdData->getField< uint16_t >( row, 6 );
  experience = exdData->getField< int32_t >( row, 7 );
  requiredItemLevel = exdData->getField< uint16_t >( row, 8 );
  conditionParam0 = exdData->getField< uint8_t >( row, 9 );
  conditionParam1 = exdData->getField< uint8_t >( row, 10 );
  requiredGathering = exdData->getField< uint16_t >( row, 11 );
  task = exdData->getField< uint16_t >( row, 13 );
}

Sapphire::Data::RetainerTaskLvRange::RetainerTaskLvRange( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RetainerTaskLvRangeDat.get_row( row_id );
  min = exdData->getField< uint8_t >( row, 0 );
  max = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::RetainerTaskNormal::RetainerTaskNormal( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RetainerTaskNormalDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  quantity0 = exdData->getField< uint8_t >( row, 1 );
  quantity1 = exdData->getField< uint8_t >( row, 2 );
  quantity2 = exdData->getField< uint8_t >( row, 3 );
  gatheringLog = exdData->getField< int16_t >( row, 4 );
  fishingLog = exdData->getField< int16_t >( row, 5 );
}

Sapphire::Data::RetainerTaskParameter::RetainerTaskParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RetainerTaskParameterDat.get_row( row_id );
  itemLevelDoW.push_back( exdData->getField< int16_t >( row, 0 ) );
  itemLevelDoW.push_back( exdData->getField< int16_t >( row, 1 ) );
  gatheringDoL.push_back( exdData->getField< int16_t >( row, 2 ) );
  gatheringDoL.push_back( exdData->getField< int16_t >( row, 3 ) );
  gatheringFSH.push_back( exdData->getField< int16_t >( row, 4 ) );
  gatheringFSH.push_back( exdData->getField< int16_t >( row, 5 ) );
}

Sapphire::Data::RetainerTaskRandom::RetainerTaskRandom( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RetainerTaskRandomDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  requirement = exdData->getField< int16_t >( row, 1 );
}

Sapphire::Data::RideShooting::RideShooting( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RideShootingDat.get_row( row_id );
  gFateRideShooting = exdData->getField< uint16_t >( row, 0 );
  startText = exdData->getField< uint16_t >( row, 5 );
  popRange.push_back( exdData->getField< uint32_t >( row, 14 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 15 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 16 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 17 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 18 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 19 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 20 ) );
  popRange.push_back( exdData->getField< uint32_t >( row, 21 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 22 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 23 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 24 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 25 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 26 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 27 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 28 ) );
  eNpc.push_back( exdData->getField< uint32_t >( row, 29 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 30 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 31 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 32 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 33 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 34 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 35 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 36 ) );
  eNpcScale.push_back( exdData->getField< uint8_t >( row, 37 ) );
}

Sapphire::Data::RideShootingTextData::RideShootingTextData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RideShootingTextDataDat.get_row( row_id );
  string = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::RPParameter::RPParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_RPParameterDat.get_row( row_id );
  bNpcName = exdData->getField< uint16_t >( row, 0 );
  classJob = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::SatisfactionArbitration::SatisfactionArbitration( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SatisfactionArbitrationDat.get_row( row_id, subRow );
  quest = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::SatisfactionNpc::SatisfactionNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SatisfactionNpcDat.get_row( row_id );
  npc = exdData->getField< int32_t >( row, 0 );
  questRequired = exdData->getField< int32_t >( row, 1 );
  levelUnlock = exdData->getField< uint8_t >( row, 2 );
  deliveriesPerWeek = exdData->getField< uint8_t >( row, 3 );
  supplyIndex.push_back( exdData->getField< int32_t >( row, 4 ) );
  supplyIndex.push_back( exdData->getField< int32_t >( row, 5 ) );
  supplyIndex.push_back( exdData->getField< int32_t >( row, 6 ) );
  supplyIndex.push_back( exdData->getField< int32_t >( row, 7 ) );
  supplyIndex.push_back( exdData->getField< int32_t >( row, 8 ) );
  supplyIndex.push_back( exdData->getField< int32_t >( row, 9 ) );
  satisfactionRequired.push_back( exdData->getField< uint16_t >( row, 10 ) );
  satisfactionRequired.push_back( exdData->getField< uint16_t >( row, 11 ) );
  satisfactionRequired.push_back( exdData->getField< uint16_t >( row, 12 ) );
  satisfactionRequired.push_back( exdData->getField< uint16_t >( row, 13 ) );
  satisfactionRequired.push_back( exdData->getField< uint16_t >( row, 14 ) );
  satisfactionRequired.push_back( exdData->getField< uint16_t >( row, 15 ) );
  icon = exdData->getField< int32_t >( row, 70 );
  addedIn530 = exdData->getField< uint8_t >( row, 72 );
  addedIn531 = exdData->getField< uint8_t >( row, 73 );
}

Sapphire::Data::SatisfactionSupply::SatisfactionSupply( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SatisfactionSupplyDat.get_row( row_id, subRow );
  slot = exdData->getField< uint8_t >( row, 0 );
  probability = exdData->getField< uint8_t >( row, 1 );
  item = exdData->getField< int32_t >( row, 2 );
  collectabilityLow = exdData->getField< uint16_t >( row, 3 );
  collectabilityMid = exdData->getField< uint16_t >( row, 4 );
  collectabilityHigh = exdData->getField< uint16_t >( row, 5 );
  reward = exdData->getField< uint16_t >( row, 6 );
}

Sapphire::Data::SatisfactionSupplyReward::SatisfactionSupplyReward( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SatisfactionSupplyRewardDat.get_row( row_id );
  satisfactionLow = exdData->getField< uint16_t >( row, 10 );
  satisfactionMid = exdData->getField< uint16_t >( row, 11 );
  satisfactionHigh = exdData->getField< uint16_t >( row, 12 );
  gilLow = exdData->getField< uint16_t >( row, 13 );
  gilMid = exdData->getField< uint16_t >( row, 14 );
  gilHigh = exdData->getField< uint16_t >( row, 15 );
}

Sapphire::Data::ScenarioTree::ScenarioTree( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ScenarioTreeDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  image = exdData->getField< uint16_t >( row, 1 );
  unknown540 = exdData->getField< uint32_t >( row, 3 );
  unknown541 = exdData->getField< std::string >( row, 4 );
  unknown542 = exdData->getField< int32_t >( row, 5 );
}

Sapphire::Data::ScenarioTreeTips::ScenarioTreeTips( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ScenarioTreeTipsDat.get_row( row_id );
  tips1 = exdData->getField< uint32_t >( row, 1 );
  tips2 = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::ScenarioTreeTipsClassQuest::ScenarioTreeTipsClassQuest( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ScenarioTreeTipsClassQuestDat.get_row( row_id, subRow );
  quest = exdData->getField< uint32_t >( row, 0 );
  requiredLevel = exdData->getField< uint16_t >( row, 1 );
  requiredExpansion = exdData->getField< uint8_t >( row, 2 );
  requiredQuest = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::ScenarioType::ScenarioType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ScenarioTypeDat.get_row( row_id );
  type = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ScreenImage::ScreenImage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ScreenImageDat.get_row( row_id );
  image = exdData->getField< uint32_t >( row, 0 );
  jingle = exdData->getField< int16_t >( row, 1 );
  type = exdData->getField< int8_t >( row, 2 );
  lang = exdData->getField< bool >( row, 3 );
}

Sapphire::Data::SecretRecipeBook::SecretRecipeBook( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SecretRecipeBookDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::SkyIsland2Mission::SkyIsland2Mission( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SkyIsland2MissionDat.get_row( row_id );
  item1 = exdData->getField< uint32_t >( row, 0 );
  item2 = exdData->getField< uint32_t >( row, 1 );
  placeName = exdData->getField< uint16_t >( row, 2 );
  objective1 = exdData->getField< uint16_t >( row, 4 );
  popRange0 = exdData->getField< uint32_t >( row, 5 );
  requiredAmount1 = exdData->getField< uint8_t >( row, 6 );
  objective2 = exdData->getField< uint16_t >( row, 9 );
  popRange1 = exdData->getField< uint32_t >( row, 10 );
  requiredAmount2 = exdData->getField< uint8_t >( row, 11 );
  objective3 = exdData->getField< uint16_t >( row, 14 );
  popRange2 = exdData->getField< uint32_t >( row, 15 );
  image = exdData->getField< uint32_t >( row, 20 );
}

Sapphire::Data::SkyIsland2MissionDetail::SkyIsland2MissionDetail( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SkyIsland2MissionDetailDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
  range = exdData->getField< uint8_t >( row, 2 );
  eObj = exdData->getField< uint32_t >( row, 4 );
  objective = exdData->getField< std::string >( row, 7 );
}

Sapphire::Data::SkyIsland2MissionType::SkyIsland2MissionType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SkyIsland2MissionTypeDat.get_row( row_id );
  type = exdData->getField< bool >( row, 0 );
}

Sapphire::Data::SkyIsland2RangeType::SkyIsland2RangeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SkyIsland2RangeTypeDat.get_row( row_id );
  type = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::SnipeTalk::SnipeTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SnipeTalkDat.get_row( row_id );
  name = exdData->getField< uint16_t >( row, 2 );
  text = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::SnipeTalkName::SnipeTalkName( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SnipeTalkNameDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::SpearfishingItem::SpearfishingItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SpearfishingItemDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
  item = exdData->getField< int32_t >( row, 1 );
  gatheringItemLevel = exdData->getField< uint16_t >( row, 2 );
  fishingRecordType = exdData->getField< uint8_t >( row, 3 );
  territoryType = exdData->getField< uint16_t >( row, 4 );
  isVisible = exdData->getField< bool >( row, 5 );
}

Sapphire::Data::SpearfishingNotebook::SpearfishingNotebook( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SpearfishingNotebookDat.get_row( row_id );
  gatheringLevel = exdData->getField< uint8_t >( row, 0 );
  territoryType = exdData->getField< int32_t >( row, 2 );
  x = exdData->getField< int16_t >( row, 3 );
  y = exdData->getField< int16_t >( row, 4 );
  radius = exdData->getField< uint16_t >( row, 5 );
  placeName = exdData->getField< uint16_t >( row, 7 );
  gatheringPointBase = exdData->getField< uint16_t >( row, 9 );
}

Sapphire::Data::SpearfishingRecordPage::SpearfishingRecordPage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SpearfishingRecordPageDat.get_row( row_id );
  placeName = exdData->getField< int32_t >( row, 3 );
  image = exdData->getField< int32_t >( row, 4 );
}

Sapphire::Data::SpecialShop::SpecialShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SpecialShopDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  questItem.push_back( exdData->getField< int32_t >( row, 1201 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1202 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1203 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1204 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1205 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1206 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1207 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1208 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1209 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1210 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1211 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1212 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1213 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1214 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1215 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1216 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1217 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1218 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1219 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1220 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1221 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1222 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1223 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1224 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1225 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1226 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1227 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1228 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1229 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1230 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1231 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1232 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1233 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1234 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1235 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1236 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1237 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1238 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1239 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1240 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1241 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1242 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1243 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1244 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1245 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1246 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1247 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1248 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1249 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1250 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1251 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1252 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1253 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1254 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1255 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1256 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1257 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1258 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1259 ) );
  questItem.push_back( exdData->getField< int32_t >( row, 1260 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1261 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1262 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1263 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1264 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1265 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1266 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1267 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1268 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1269 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1270 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1271 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1272 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1273 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1274 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1275 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1276 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1277 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1278 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1279 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1280 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1281 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1282 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1283 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1284 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1285 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1286 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1287 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1288 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1289 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1290 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1291 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1292 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1293 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1294 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1295 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1296 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1297 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1298 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1299 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1300 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1301 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1302 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1303 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1304 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1305 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1306 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1307 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1308 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1309 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1310 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1311 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1312 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1313 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1314 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1315 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1316 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1317 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1318 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1319 ) );
  unknown.push_back( exdData->getField< int32_t >( row, 1320 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1321 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1322 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1323 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1324 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1325 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1326 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1327 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1328 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1329 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1330 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1331 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1332 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1333 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1334 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1335 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1336 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1337 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1338 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1339 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1340 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1341 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1342 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1343 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1344 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1345 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1346 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1347 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1348 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1349 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1350 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1351 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1352 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1353 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1354 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1355 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1356 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1357 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1358 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1359 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1360 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1361 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1362 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1363 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1364 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1365 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1366 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1367 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1368 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1369 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1370 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1371 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1372 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1373 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1374 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1375 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1376 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1377 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1378 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1379 ) );
  achievementUnlock.push_back( exdData->getField< int32_t >( row, 1380 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1441 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1442 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1443 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1444 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1445 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1446 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1447 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1448 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1449 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1450 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1451 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1452 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1453 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1454 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1455 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1456 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1457 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1458 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1459 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1460 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1461 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1462 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1463 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1464 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1465 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1466 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1467 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1468 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1469 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1470 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1471 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1472 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1473 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1474 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1475 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1476 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1477 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1478 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1479 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1480 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1481 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1482 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1483 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1484 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1485 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1486 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1487 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1488 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1489 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1490 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1491 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1492 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1493 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1494 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1495 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1496 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1497 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1498 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1499 ) );
  patchNumber.push_back( exdData->getField< uint16_t >( row, 1500 ) );
  useCurrencyType = exdData->getField< uint8_t >( row, 1501 );
  questUnlock = exdData->getField< uint32_t >( row, 1502 );
  completeText = exdData->getField< int32_t >( row, 1503 );
  notCompleteText = exdData->getField< int32_t >( row, 1504 );
}

Sapphire::Data::SpecialShopItemCategory::SpecialShopItemCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SpecialShopItemCategoryDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Stain::Stain( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_StainDat.get_row( row_id );
  color = exdData->getField< uint32_t >( row, 0 );
  shade = exdData->getField< uint8_t >( row, 1 );
  name = exdData->getField< std::string >( row, 3 );
}

Sapphire::Data::StainTransient::StainTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_StainTransientDat.get_row( row_id );
  item1 = exdData->getField< uint32_t >( row, 0 );
  item2 = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::Status::Status( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_StatusDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  icon = exdData->getField< uint16_t >( row, 2 );
  maxStacks = exdData->getField< uint8_t >( row, 3 );
  category = exdData->getField< uint8_t >( row, 5 );
  hitEffect = exdData->getField< uint8_t >( row, 6 );
  vFX = exdData->getField< uint16_t >( row, 7 );
  lockMovement = exdData->getField< bool >( row, 8 );
  lockActions = exdData->getField< bool >( row, 10 );
  lockControl = exdData->getField< bool >( row, 11 );
  transfiguration = exdData->getField< bool >( row, 12 );
  canDispel = exdData->getField< bool >( row, 14 );
  inflictedByActor = exdData->getField< bool >( row, 15 );
  isPermanent = exdData->getField< bool >( row, 16 );
  partyListPriority = exdData->getField< uint8_t >( row, 17 );
  log = exdData->getField< uint16_t >( row, 24 );
  isFcBuff = exdData->getField< bool >( row, 25 );
  invisibility = exdData->getField< bool >( row, 26 );
}

Sapphire::Data::StatusHitEffect::StatusHitEffect( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_StatusHitEffectDat.get_row( row_id );
  location = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::StatusLoopVFX::StatusLoopVFX( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_StatusLoopVFXDat.get_row( row_id );
  vFX = exdData->getField< uint16_t >( row, 0 );
  vFX2 = exdData->getField< uint16_t >( row, 2 );
  vFX3 = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::Story::Story( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_StoryDat.get_row( row_id );
  script = exdData->getField< std::string >( row, 0 );
  instruction.push_back( exdData->getField< std::string >( row, 1 ) );
  instruction.push_back( exdData->getField< std::string >( row, 2 ) );
  instruction.push_back( exdData->getField< std::string >( row, 3 ) );
  instruction.push_back( exdData->getField< std::string >( row, 4 ) );
  instruction.push_back( exdData->getField< std::string >( row, 5 ) );
  instruction.push_back( exdData->getField< std::string >( row, 6 ) );
  instruction.push_back( exdData->getField< std::string >( row, 7 ) );
  instruction.push_back( exdData->getField< std::string >( row, 8 ) );
  instruction.push_back( exdData->getField< std::string >( row, 9 ) );
  instruction.push_back( exdData->getField< std::string >( row, 10 ) );
  instruction.push_back( exdData->getField< std::string >( row, 11 ) );
  instruction.push_back( exdData->getField< std::string >( row, 12 ) );
  instruction.push_back( exdData->getField< std::string >( row, 13 ) );
  instruction.push_back( exdData->getField< std::string >( row, 14 ) );
  instruction.push_back( exdData->getField< std::string >( row, 15 ) );
  instruction.push_back( exdData->getField< std::string >( row, 16 ) );
  instruction.push_back( exdData->getField< std::string >( row, 17 ) );
  instruction.push_back( exdData->getField< std::string >( row, 18 ) );
  instruction.push_back( exdData->getField< std::string >( row, 19 ) );
  instruction.push_back( exdData->getField< std::string >( row, 20 ) );
  instruction.push_back( exdData->getField< std::string >( row, 21 ) );
  instruction.push_back( exdData->getField< std::string >( row, 22 ) );
  instruction.push_back( exdData->getField< std::string >( row, 23 ) );
  instruction.push_back( exdData->getField< std::string >( row, 24 ) );
  instruction.push_back( exdData->getField< std::string >( row, 25 ) );
  instruction.push_back( exdData->getField< std::string >( row, 26 ) );
  instruction.push_back( exdData->getField< std::string >( row, 27 ) );
  instruction.push_back( exdData->getField< std::string >( row, 28 ) );
  instruction.push_back( exdData->getField< std::string >( row, 29 ) );
  instruction.push_back( exdData->getField< std::string >( row, 30 ) );
  instruction.push_back( exdData->getField< std::string >( row, 31 ) );
  instruction.push_back( exdData->getField< std::string >( row, 32 ) );
  instruction.push_back( exdData->getField< std::string >( row, 33 ) );
  instruction.push_back( exdData->getField< std::string >( row, 34 ) );
  instruction.push_back( exdData->getField< std::string >( row, 35 ) );
  instruction.push_back( exdData->getField< std::string >( row, 36 ) );
  instruction.push_back( exdData->getField< std::string >( row, 37 ) );
  instruction.push_back( exdData->getField< std::string >( row, 38 ) );
  instruction.push_back( exdData->getField< std::string >( row, 39 ) );
  instruction.push_back( exdData->getField< std::string >( row, 40 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 41 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 42 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 43 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 44 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 45 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 46 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 47 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 48 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 49 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 50 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 51 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 52 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 53 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 54 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 55 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 56 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 57 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 58 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 59 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 60 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 61 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 62 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 63 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 64 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 65 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 66 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 67 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 68 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 69 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 70 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 71 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 72 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 73 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 74 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 75 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 76 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 77 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 78 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 79 ) );
  argument.push_back( exdData->getField< uint32_t >( row, 80 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 81 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 82 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 83 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 84 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 85 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 86 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 87 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 88 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 89 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 90 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 91 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 92 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 93 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 94 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 95 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 96 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 97 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 98 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 99 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 100 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 101 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 102 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 103 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 104 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 105 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 106 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 107 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 108 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 109 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 110 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 111 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 112 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 113 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 114 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 115 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 116 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 117 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 118 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 119 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 120 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 121 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 122 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 123 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 124 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 125 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 126 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 127 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 128 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 129 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 130 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 131 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 132 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 133 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 134 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 135 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 136 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 137 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 138 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 139 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 140 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 141 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 142 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 143 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 144 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 145 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 146 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 147 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 148 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 149 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 150 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 151 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 152 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 153 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 154 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 155 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 156 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 157 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 158 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 159 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 160 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 161 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 162 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 163 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 164 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 165 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 166 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 167 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 168 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 169 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 170 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 171 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 172 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 173 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 174 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 175 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 176 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 177 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 178 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 179 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 180 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 181 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 182 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 183 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 184 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 185 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 186 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 187 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 188 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 189 ) );
  sequence.push_back( exdData->getField< uint16_t >( row, 190 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 191 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 192 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 193 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 194 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 195 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 196 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 197 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 198 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 199 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 200 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 201 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 202 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 203 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 204 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 205 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 206 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 207 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 208 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 209 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 210 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 211 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 212 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 213 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 214 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 215 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 216 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 217 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 218 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 219 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 220 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 221 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 222 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 223 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 224 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 225 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 226 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 227 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 228 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 229 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 230 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 231 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 232 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 233 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 234 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 235 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 236 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 237 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 238 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 239 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 240 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 241 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 242 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 243 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 244 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 245 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 246 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 247 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 248 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 249 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 250 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 251 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 252 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 253 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 254 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 255 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 256 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 257 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 258 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 259 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 260 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 261 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 262 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 263 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 264 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 265 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 266 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 267 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 268 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 269 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 270 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 271 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 272 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 273 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 274 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 275 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 276 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 277 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 278 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 279 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 280 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 281 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 282 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 283 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 284 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 285 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 286 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 287 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 288 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 289 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 290 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 291 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 292 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 293 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 294 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 295 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 296 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 297 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 298 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 299 ) );
  completedQuestOperator.push_back( exdData->getField< uint8_t >( row, 300 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 301 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 302 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 303 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 304 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 305 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 306 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 307 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 308 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 309 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 310 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 311 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 312 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 313 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 314 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 315 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 316 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 317 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 318 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 319 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 320 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 321 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 322 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 323 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 324 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 325 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 326 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 327 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 328 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 329 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 330 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 331 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 332 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 333 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 334 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 335 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 336 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 337 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 338 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 339 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 340 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 341 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 342 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 343 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 344 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 345 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 346 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 347 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 348 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 349 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 350 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 351 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 352 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 353 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 354 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 355 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 356 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 357 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 358 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 359 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 360 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 361 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 362 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 363 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 364 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 365 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 366 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 367 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 368 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 369 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 370 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 371 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 372 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 373 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 374 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 375 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 376 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 377 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 378 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 379 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 380 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 381 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 382 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 383 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 384 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 385 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 386 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 387 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 388 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 389 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 390 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 391 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 392 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 393 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 394 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 395 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 396 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 397 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 398 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 399 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 400 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 401 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 402 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 403 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 404 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 405 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 406 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 407 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 408 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 409 ) );
  completedQuest0.push_back( exdData->getField< uint32_t >( row, 410 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 411 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 412 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 413 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 414 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 415 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 416 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 417 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 418 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 419 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 420 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 421 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 422 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 423 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 424 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 425 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 426 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 427 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 428 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 429 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 430 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 431 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 432 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 433 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 434 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 435 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 436 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 437 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 438 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 439 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 440 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 441 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 442 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 443 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 444 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 445 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 446 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 447 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 448 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 449 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 450 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 451 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 452 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 453 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 454 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 455 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 456 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 457 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 458 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 459 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 460 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 461 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 462 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 463 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 464 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 465 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 466 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 467 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 468 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 469 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 470 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 471 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 472 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 473 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 474 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 475 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 476 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 477 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 478 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 479 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 480 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 481 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 482 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 483 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 484 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 485 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 486 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 487 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 488 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 489 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 490 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 491 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 492 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 493 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 494 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 495 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 496 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 497 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 498 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 499 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 500 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 501 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 502 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 503 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 504 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 505 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 506 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 507 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 508 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 509 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 510 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 511 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 512 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 513 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 514 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 515 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 516 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 517 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 518 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 519 ) );
  completedQuest1.push_back( exdData->getField< uint32_t >( row, 520 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 521 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 522 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 523 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 524 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 525 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 526 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 527 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 528 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 529 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 530 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 531 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 532 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 533 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 534 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 535 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 536 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 537 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 538 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 539 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 540 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 541 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 542 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 543 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 544 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 545 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 546 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 547 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 548 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 549 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 550 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 551 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 552 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 553 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 554 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 555 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 556 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 557 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 558 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 559 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 560 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 561 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 562 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 563 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 564 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 565 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 566 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 567 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 568 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 569 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 570 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 571 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 572 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 573 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 574 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 575 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 576 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 577 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 578 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 579 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 580 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 581 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 582 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 583 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 584 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 585 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 586 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 587 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 588 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 589 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 590 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 591 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 592 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 593 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 594 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 595 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 596 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 597 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 598 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 599 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 600 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 601 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 602 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 603 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 604 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 605 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 606 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 607 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 608 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 609 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 610 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 611 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 612 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 613 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 614 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 615 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 616 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 617 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 618 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 619 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 620 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 621 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 622 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 623 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 624 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 625 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 626 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 627 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 628 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 629 ) );
  completedQuest2.push_back( exdData->getField< uint32_t >( row, 630 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 631 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 632 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 633 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 634 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 635 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 636 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 637 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 638 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 639 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 640 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 641 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 642 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 643 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 644 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 645 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 646 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 647 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 648 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 649 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 650 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 651 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 652 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 653 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 654 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 655 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 656 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 657 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 658 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 659 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 660 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 661 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 662 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 663 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 664 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 665 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 666 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 667 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 668 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 669 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 670 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 671 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 672 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 673 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 674 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 675 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 676 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 677 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 678 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 679 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 680 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 681 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 682 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 683 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 684 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 685 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 686 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 687 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 688 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 689 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 690 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 691 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 692 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 693 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 694 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 695 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 696 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 697 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 698 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 699 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 700 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 701 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 702 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 703 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 704 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 705 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 706 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 707 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 708 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 709 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 710 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 711 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 712 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 713 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 714 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 715 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 716 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 717 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 718 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 719 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 720 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 721 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 722 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 723 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 724 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 725 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 726 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 727 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 728 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 729 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 730 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 731 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 732 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 733 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 734 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 735 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 736 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 737 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 738 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 739 ) );
  acceptedQuestOperator.push_back( exdData->getField< uint8_t >( row, 740 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 741 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 742 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 743 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 744 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 745 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 746 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 747 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 748 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 749 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 750 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 751 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 752 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 753 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 754 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 755 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 756 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 757 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 758 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 759 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 760 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 761 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 762 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 763 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 764 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 765 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 766 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 767 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 768 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 769 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 770 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 771 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 772 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 773 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 774 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 775 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 776 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 777 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 778 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 779 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 780 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 781 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 782 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 783 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 784 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 785 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 786 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 787 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 788 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 789 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 790 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 791 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 792 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 793 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 794 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 795 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 796 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 797 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 798 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 799 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 800 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 801 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 802 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 803 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 804 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 805 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 806 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 807 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 808 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 809 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 810 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 811 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 812 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 813 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 814 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 815 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 816 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 817 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 818 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 819 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 820 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 821 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 822 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 823 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 824 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 825 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 826 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 827 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 828 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 829 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 830 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 831 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 832 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 833 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 834 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 835 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 836 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 837 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 838 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 839 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 840 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 841 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 842 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 843 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 844 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 845 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 846 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 847 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 848 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 849 ) );
  acceptedQuest0.push_back( exdData->getField< uint32_t >( row, 850 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 851 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 852 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 853 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 854 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 855 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 856 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 857 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 858 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 859 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 860 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 861 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 862 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 863 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 864 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 865 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 866 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 867 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 868 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 869 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 870 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 871 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 872 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 873 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 874 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 875 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 876 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 877 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 878 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 879 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 880 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 881 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 882 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 883 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 884 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 885 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 886 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 887 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 888 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 889 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 890 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 891 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 892 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 893 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 894 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 895 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 896 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 897 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 898 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 899 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 900 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 901 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 902 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 903 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 904 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 905 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 906 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 907 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 908 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 909 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 910 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 911 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 912 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 913 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 914 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 915 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 916 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 917 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 918 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 919 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 920 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 921 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 922 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 923 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 924 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 925 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 926 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 927 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 928 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 929 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 930 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 931 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 932 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 933 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 934 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 935 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 936 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 937 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 938 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 939 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 940 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 941 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 942 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 943 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 944 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 945 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 946 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 947 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 948 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 949 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 950 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 951 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 952 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 953 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 954 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 955 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 956 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 957 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 958 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 959 ) );
  acceptedQuestSequence0.push_back( exdData->getField< uint8_t >( row, 960 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 961 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 962 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 963 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 964 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 965 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 966 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 967 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 968 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 969 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 970 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 971 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 972 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 973 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 974 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 975 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 976 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 977 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 978 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 979 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 980 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 981 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 982 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 983 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 984 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 985 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 986 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 987 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 988 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 989 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 990 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 991 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 992 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 993 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 994 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 995 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 996 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 997 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 998 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 999 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1000 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1001 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1002 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1003 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1004 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1005 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1006 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1007 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1008 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1009 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1010 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1011 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1012 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1013 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1014 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1015 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1016 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1017 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1018 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1019 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1020 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1021 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1022 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1023 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1024 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1025 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1026 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1027 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1028 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1029 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1030 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1031 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1032 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1033 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1034 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1035 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1036 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1037 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1038 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1039 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1040 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1041 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1042 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1043 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1044 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1045 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1046 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1047 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1048 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1049 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1050 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1051 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1052 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1053 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1054 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1055 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1056 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1057 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1058 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1059 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1060 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1061 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1062 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1063 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1064 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1065 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1066 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1067 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1068 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1069 ) );
  acceptedQuest1.push_back( exdData->getField< uint32_t >( row, 1070 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1071 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1072 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1073 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1074 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1075 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1076 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1077 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1078 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1079 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1080 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1081 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1082 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1083 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1084 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1085 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1086 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1087 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1088 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1089 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1090 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1091 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1092 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1093 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1094 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1095 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1096 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1097 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1098 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1099 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1100 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1101 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1102 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1103 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1104 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1105 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1106 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1107 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1108 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1109 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1110 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1111 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1112 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1113 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1114 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1115 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1116 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1117 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1118 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1119 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1120 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1121 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1122 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1123 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1124 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1125 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1126 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1127 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1128 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1129 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1130 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1131 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1132 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1133 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1134 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1135 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1136 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1137 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1138 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1139 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1140 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1141 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1142 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1143 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1144 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1145 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1146 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1147 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1148 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1149 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1150 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1151 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1152 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1153 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1154 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1155 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1156 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1157 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1158 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1159 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1160 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1161 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1162 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1163 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1164 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1165 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1166 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1167 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1168 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1169 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1170 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1171 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1172 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1173 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1174 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1175 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1176 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1177 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1178 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1179 ) );
  acceptedQuestSequence1.push_back( exdData->getField< uint8_t >( row, 1180 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1181 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1182 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1183 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1184 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1185 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1186 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1187 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1188 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1189 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1190 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1191 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1192 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1193 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1194 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1195 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1196 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1197 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1198 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1199 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1200 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1201 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1202 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1203 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1204 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1205 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1206 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1207 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1208 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1209 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1210 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1211 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1212 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1213 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1214 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1215 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1216 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1217 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1218 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1219 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1220 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1221 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1222 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1223 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1224 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1225 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1226 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1227 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1228 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1229 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1230 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1231 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1232 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1233 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1234 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1235 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1236 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1237 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1238 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1239 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1240 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1241 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1242 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1243 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1244 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1245 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1246 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1247 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1248 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1249 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1250 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1251 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1252 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1253 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1254 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1255 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1256 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1257 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1258 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1259 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1260 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1261 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1262 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1263 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1264 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1265 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1266 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1267 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1268 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1269 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1270 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1271 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1272 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1273 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1274 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1275 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1276 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1277 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1278 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1279 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1280 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1281 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1282 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1283 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1284 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1285 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1286 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1287 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1288 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1289 ) );
  acceptedQuest2.push_back( exdData->getField< uint32_t >( row, 1290 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1291 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1292 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1293 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1294 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1295 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1296 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1297 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1298 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1299 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1300 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1301 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1302 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1303 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1304 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1305 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1306 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1307 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1308 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1309 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1310 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1311 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1312 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1313 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1314 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1315 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1316 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1317 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1318 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1319 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1320 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1321 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1322 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1323 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1324 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1325 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1326 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1327 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1328 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1329 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1330 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1331 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1332 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1333 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1334 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1335 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1336 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1337 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1338 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1339 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1340 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1341 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1342 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1343 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1344 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1345 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1346 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1347 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1348 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1349 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1350 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1351 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1352 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1353 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1354 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1355 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1356 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1357 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1358 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1359 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1360 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1361 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1362 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1363 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1364 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1365 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1366 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1367 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1368 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1369 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1370 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1371 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1372 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1373 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1374 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1375 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1376 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1377 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1378 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1379 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1380 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1381 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1382 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1383 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1384 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1385 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1386 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1387 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1388 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1389 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1390 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1391 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1392 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1393 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1394 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1395 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1396 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1397 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1398 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1399 ) );
  acceptedQuestSequence2.push_back( exdData->getField< uint8_t >( row, 1400 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1401 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1402 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1403 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1404 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1405 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1406 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1407 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1408 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1409 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1410 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1411 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1412 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1413 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1414 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1415 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1416 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1417 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1418 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1419 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1420 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1421 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1422 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1423 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1424 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1425 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1426 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1427 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1428 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1429 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1430 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1431 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1432 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1433 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1434 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1435 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1436 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1437 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1438 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1439 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1440 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1441 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1442 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1443 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1444 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1445 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1446 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1447 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1448 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1449 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1450 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1451 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1452 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1453 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1454 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1455 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1456 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1457 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1458 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1459 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1460 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1461 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1462 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1463 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1464 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1465 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1466 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1467 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1468 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1469 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1470 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1471 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1472 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1473 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1474 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1475 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1476 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1477 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1478 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1479 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1480 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1481 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1482 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1483 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1484 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1485 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1486 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1487 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1488 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1489 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1490 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1491 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1492 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1493 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1494 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1495 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1496 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1497 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1498 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1499 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1500 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1501 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1502 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1503 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1504 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1505 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1506 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1507 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1508 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1509 ) );
  layerSet0.push_back( exdData->getField< uint32_t >( row, 1510 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1511 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1512 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1513 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1514 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1515 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1516 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1517 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1518 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1519 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1520 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1521 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1522 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1523 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1524 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1525 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1526 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1527 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1528 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1529 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1530 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1531 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1532 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1533 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1534 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1535 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1536 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1537 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1538 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1539 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1540 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1541 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1542 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1543 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1544 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1545 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1546 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1547 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1548 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1549 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1550 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1551 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1552 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1553 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1554 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1555 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1556 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1557 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1558 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1559 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1560 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1561 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1562 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1563 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1564 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1565 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1566 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1567 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1568 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1569 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1570 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1571 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1572 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1573 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1574 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1575 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1576 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1577 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1578 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1579 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1580 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1581 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1582 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1583 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1584 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1585 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1586 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1587 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1588 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1589 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1590 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1591 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1592 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1593 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1594 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1595 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1596 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1597 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1598 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1599 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1600 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1601 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1602 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1603 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1604 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1605 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1606 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1607 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1608 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1609 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1610 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1611 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1612 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1613 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1614 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1615 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1616 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1617 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1618 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1619 ) );
  layerSet1.push_back( exdData->getField< uint32_t >( row, 1620 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1621 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1622 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1623 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1624 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1625 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1626 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1627 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1628 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1629 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1630 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1631 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1632 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1633 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1634 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1635 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1636 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1637 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1638 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1639 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1640 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1641 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1642 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1643 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1644 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1645 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1646 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1647 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1648 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1649 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1650 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1651 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1652 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1653 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1654 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1655 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1656 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1657 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1658 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1659 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1660 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1661 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1662 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1663 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1664 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1665 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1666 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1667 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1668 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1669 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1670 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1671 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1672 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1673 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1674 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1675 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1676 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1677 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1678 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1679 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1680 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1681 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1682 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1683 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1684 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1685 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1686 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1687 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1688 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1689 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1690 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1691 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1692 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1693 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1694 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1695 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1696 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1697 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1698 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1699 ) );
  sequenceBegin.push_back( exdData->getField< uint16_t >( row, 1700 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1701 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1702 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1703 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1704 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1705 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1706 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1707 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1708 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1709 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1710 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1711 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1712 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1713 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1714 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1715 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1716 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1717 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1718 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1719 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1720 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1721 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1722 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1723 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1724 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1725 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1726 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1727 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1728 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1729 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1730 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1731 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1732 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1733 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1734 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1735 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1736 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1737 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1738 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1739 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1740 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1741 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1742 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1743 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1744 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1745 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1746 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1747 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1748 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1749 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1750 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1751 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1752 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1753 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1754 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1755 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1756 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1757 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1758 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1759 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1760 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1761 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1762 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1763 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1764 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1765 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1766 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1767 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1768 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1769 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1770 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1771 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1772 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1773 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1774 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1775 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1776 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1777 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1778 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1779 ) );
  sequenceEnd.push_back( exdData->getField< uint16_t >( row, 1780 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1781 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1782 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1783 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1784 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1785 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1786 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1787 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1788 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1789 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1790 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1791 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1792 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1793 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1794 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1795 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1796 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1797 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1798 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1799 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1800 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1801 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1802 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1803 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1804 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1805 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1806 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1807 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1808 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1809 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1810 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1811 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1812 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1813 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1814 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1815 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1816 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1817 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1818 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1819 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1820 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1821 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1822 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1823 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1824 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1825 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1826 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1827 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1828 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1829 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1830 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1831 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1832 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1833 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1834 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1835 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1836 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1837 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1838 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1839 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1840 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1841 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1842 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1843 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1844 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1845 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1846 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1847 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1848 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1849 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1850 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1851 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1852 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1853 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1854 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1855 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1856 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1857 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1858 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1859 ) );
  listener.push_back( exdData->getField< uint32_t >( row, 1860 ) );
  layerSetTerritoryType0 = exdData->getField< uint16_t >( row, 1861 );
  layerSetTerritoryType1 = exdData->getField< uint16_t >( row, 1862 );
}

Sapphire::Data::SubmarineExploration::SubmarineExploration( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SubmarineExplorationDat.get_row( row_id );
  destination = exdData->getField< std::string >( row, 0 );
  location = exdData->getField< std::string >( row, 1 );
  map = exdData->getField< uint8_t >( row, 5 );
  stars = exdData->getField< uint8_t >( row, 7 );
  rankReq = exdData->getField< uint8_t >( row, 8 );
  ceruleumTankReq = exdData->getField< uint8_t >( row, 9 );
  durationmin = exdData->getField< uint16_t >( row, 10 );
  distanceForSurvey = exdData->getField< uint8_t >( row, 11 );
  expReward = exdData->getField< uint32_t >( row, 12 );
}

Sapphire::Data::SubmarineMap::SubmarineMap( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SubmarineMapDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  image = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::SubmarinePart::SubmarinePart( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SubmarinePartDat.get_row( row_id );
  slot = exdData->getField< uint8_t >( row, 0 );
  rank = exdData->getField< uint8_t >( row, 1 );
  components = exdData->getField< uint8_t >( row, 2 );
  surveillance = exdData->getField< int16_t >( row, 3 );
  retrieval = exdData->getField< int16_t >( row, 4 );
  speed = exdData->getField< int16_t >( row, 5 );
  range = exdData->getField< int16_t >( row, 6 );
  favor = exdData->getField< int16_t >( row, 7 );
  _class = exdData->getField< uint16_t >( row, 8 );
  repairMaterials = exdData->getField< uint8_t >( row, 9 );
}

Sapphire::Data::SubmarineRank::SubmarineRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SubmarineRankDat.get_row( row_id );
  capacity = exdData->getField< uint16_t >( row, 0 );
  expToNext = exdData->getField< uint32_t >( row, 1 );
  surveillanceBonus = exdData->getField< uint8_t >( row, 2 );
  retrievalBonus = exdData->getField< uint8_t >( row, 3 );
  speedBonus = exdData->getField< uint8_t >( row, 4 );
  rangeBonus = exdData->getField< uint8_t >( row, 5 );
  favorBonus = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::SwitchTalk::SwitchTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SwitchTalkDat.get_row( row_id );
}

Sapphire::Data::SwitchTalkVariation::SwitchTalkVariation( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_SwitchTalkVariationDat.get_row( row_id, subRow );
  quest0 = exdData->getField< uint32_t >( row, 0 );
  quest1 = exdData->getField< uint32_t >( row, 1 );
  defaultTalk = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::TerritoryType::TerritoryType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TerritoryTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  bg = exdData->getField< std::string >( row, 1 );
  battalionMode = exdData->getField< uint8_t >( row, 2 );
  placeNameRegion = exdData->getField< uint16_t >( row, 3 );
  placeNameZone = exdData->getField< uint16_t >( row, 4 );
  placeName = exdData->getField< uint16_t >( row, 5 );
  map = exdData->getField< uint16_t >( row, 6 );
  loadingImage = exdData->getField< uint8_t >( row, 7 );
  exclusiveType = exdData->getField< uint8_t >( row, 8 );
  territoryIntendedUse = exdData->getField< uint8_t >( row, 9 );
  weatherRate = exdData->getField< uint8_t >( row, 12 );
  pCSearch = exdData->getField< bool >( row, 15 );
  stealth = exdData->getField< bool >( row, 16 );
  mount = exdData->getField< bool >( row, 17 );
  bGM = exdData->getField< uint16_t >( row, 19 );
  placeNameRegionIcon = exdData->getField< int32_t >( row, 20 );
  placeNameIcon = exdData->getField< int32_t >( row, 21 );
  arrayEventHandler = exdData->getField< uint32_t >( row, 22 );
  questBattle = exdData->getField< uint16_t >( row, 23 );
  aetheryte = exdData->getField< int32_t >( row, 24 );
  fixedTime = exdData->getField< int32_t >( row, 25 );
  resident = exdData->getField< uint16_t >( row, 26 );
  achievementIndex = exdData->getField< int8_t >( row, 27 );
  isPvpZone = exdData->getField< bool >( row, 28 );
  exVersion = exdData->getField< uint8_t >( row, 29 );
  addedIn53 = exdData->getField< uint8_t >( row, 32 );
  mountSpeed = exdData->getField< uint8_t >( row, 33 );
  unknown54 = exdData->getField< bool >( row, 40 );
}

Sapphire::Data::TerritoryTypeTransient::TerritoryTypeTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TerritoryTypeTransientDat.get_row( row_id );
  offsetZ = exdData->getField< int16_t >( row, 0 );
}

Sapphire::Data::TextCommand::TextCommand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TextCommandDat.get_row( row_id );
  command = exdData->getField< std::string >( row, 5 );
  shortCommand = exdData->getField< std::string >( row, 6 );
  description = exdData->getField< std::string >( row, 7 );
  alias = exdData->getField< std::string >( row, 8 );
  shortAlias = exdData->getField< std::string >( row, 9 );
}

Sapphire::Data::Title::Title( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TitleDat.get_row( row_id );
  masculine = exdData->getField< std::string >( row, 0 );
  feminine = exdData->getField< std::string >( row, 1 );
  isPrefix = exdData->getField< bool >( row, 2 );
  order = exdData->getField< uint16_t >( row, 3 );
}

Sapphire::Data::Tomestones::Tomestones( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TomestonesDat.get_row( row_id );
  weeklyLimit = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::TomestonesItem::TomestonesItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TomestonesItemDat.get_row( row_id );
  item = exdData->getField< int32_t >( row, 0 );
  tomestones = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::TopicSelect::TopicSelect( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TopicSelectDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Town::Town( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TownDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::Trait::Trait( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TraitDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  icon = exdData->getField< int32_t >( row, 1 );
  classJob = exdData->getField< uint8_t >( row, 2 );
  level = exdData->getField< uint8_t >( row, 3 );
  quest = exdData->getField< uint32_t >( row, 4 );
  value = exdData->getField< int16_t >( row, 5 );
  classJobCategory = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::TraitRecast::TraitRecast( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TraitRecastDat.get_row( row_id );
  trait = exdData->getField< uint16_t >( row, 0 );
  action = exdData->getField< uint16_t >( row, 1 );
  timeds = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::TraitTransient::TraitTransient( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TraitTransientDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Transformation::Transformation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TransformationDat.get_row( row_id );
  model = exdData->getField< int16_t >( row, 1 );
  bNpcName = exdData->getField< uint16_t >( row, 2 );
  bNpcCustomize = exdData->getField< int32_t >( row, 3 );
  npcEquip = exdData->getField< int32_t >( row, 4 );
  exHotbarEnableConfig = exdData->getField< bool >( row, 5 );
  action0 = exdData->getField< uint16_t >( row, 6 );
  action1 = exdData->getField< uint16_t >( row, 8 );
  action2 = exdData->getField< uint16_t >( row, 10 );
  action3 = exdData->getField< uint16_t >( row, 12 );
  action4 = exdData->getField< uint16_t >( row, 14 );
  action5 = exdData->getField< uint16_t >( row, 16 );
  rPParameter = exdData->getField< uint16_t >( row, 18 );
  removeAction = exdData->getField< uint16_t >( row, 19 );
  speed = exdData->getField< float >( row, 23 );
  scale = exdData->getField< float >( row, 24 );
  isPvP = exdData->getField< bool >( row, 25 );
  isEvent = exdData->getField< bool >( row, 26 );
  playerCamera = exdData->getField< bool >( row, 27 );
  startVFX = exdData->getField< uint16_t >( row, 30 );
  endVFX = exdData->getField< uint16_t >( row, 31 );
  action6 = exdData->getField< uint32_t >( row, 32 );
  action7 = exdData->getField< uint16_t >( row, 34 );
  unknown54 = exdData->getField< bool >( row, 36 );
}

Sapphire::Data::Treasure::Treasure( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TreasureDat.get_row( row_id );
  item = exdData->getField< uint32_t >( row, 8 );
}

Sapphire::Data::TreasureHuntRank::TreasureHuntRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TreasureHuntRankDat.get_row( row_id );
  icon = exdData->getField< uint32_t >( row, 1 );
  itemName = exdData->getField< int32_t >( row, 2 );
  keyItemName = exdData->getField< int32_t >( row, 3 );
  instanceMap = exdData->getField< int32_t >( row, 4 );
  maxPartySize = exdData->getField< uint8_t >( row, 5 );
  treasureHuntTexture = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::TreasureModel::TreasureModel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TreasureModelDat.get_row( row_id );
  path = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::TreasureSpot::TreasureSpot( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TreasureSpotDat.get_row( row_id, subRow );
  location = exdData->getField< int32_t >( row, 0 );
  mapOffsetX = exdData->getField< float >( row, 1 );
  mapOffsetY = exdData->getField< float >( row, 2 );
}

Sapphire::Data::Tribe::Tribe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TribeDat.get_row( row_id );
  masculine = exdData->getField< std::string >( row, 0 );
  feminine = exdData->getField< std::string >( row, 1 );
  hp = exdData->getField< int8_t >( row, 2 );
  mp = exdData->getField< int8_t >( row, 3 );
  sTR = exdData->getField< int8_t >( row, 4 );
  vIT = exdData->getField< int8_t >( row, 5 );
  dEX = exdData->getField< int8_t >( row, 6 );
  iNT = exdData->getField< int8_t >( row, 7 );
  mND = exdData->getField< int8_t >( row, 8 );
  pIE = exdData->getField< int8_t >( row, 9 );
}

Sapphire::Data::TripleTriad::TripleTriad( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadDat.get_row( row_id );
  tripleTriadCardFixed.push_back( exdData->getField< uint16_t >( row, 0 ) );
  tripleTriadCardFixed.push_back( exdData->getField< uint16_t >( row, 1 ) );
  tripleTriadCardFixed.push_back( exdData->getField< uint16_t >( row, 2 ) );
  tripleTriadCardFixed.push_back( exdData->getField< uint16_t >( row, 3 ) );
  tripleTriadCardFixed.push_back( exdData->getField< uint16_t >( row, 4 ) );
  tripleTriadCardVariable.push_back( exdData->getField< uint16_t >( row, 5 ) );
  tripleTriadCardVariable.push_back( exdData->getField< uint16_t >( row, 6 ) );
  tripleTriadCardVariable.push_back( exdData->getField< uint16_t >( row, 7 ) );
  tripleTriadCardVariable.push_back( exdData->getField< uint16_t >( row, 8 ) );
  tripleTriadCardVariable.push_back( exdData->getField< uint16_t >( row, 9 ) );
  tripleTriadRule.push_back( exdData->getField< uint8_t >( row, 10 ) );
  tripleTriadRule.push_back( exdData->getField< uint8_t >( row, 11 ) );
  usesRegionalRules = exdData->getField< bool >( row, 12 );
  fee = exdData->getField< uint16_t >( row, 13 );
  previousQuestJoin = exdData->getField< uint8_t >( row, 14 );
  previousQuest.push_back( exdData->getField< uint32_t >( row, 15 ) );
  previousQuest.push_back( exdData->getField< uint32_t >( row, 16 ) );
  previousQuest.push_back( exdData->getField< uint32_t >( row, 17 ) );
  startTime = exdData->getField< uint16_t >( row, 18 );
  endTime = exdData->getField< uint16_t >( row, 19 );
  defaultTalkChallenge = exdData->getField< uint32_t >( row, 20 );
  defaultTalkUnavailable = exdData->getField< uint32_t >( row, 21 );
  defaultTalkNPCWin = exdData->getField< uint32_t >( row, 22 );
  defaultTalkDraw = exdData->getField< uint32_t >( row, 23 );
  defaultTalkPCWin = exdData->getField< uint32_t >( row, 24 );
  itemPossibleReward.push_back( exdData->getField< uint32_t >( row, 26 ) );
  itemPossibleReward.push_back( exdData->getField< uint32_t >( row, 27 ) );
  itemPossibleReward.push_back( exdData->getField< uint32_t >( row, 28 ) );
  itemPossibleReward.push_back( exdData->getField< uint32_t >( row, 29 ) );
}

Sapphire::Data::TripleTriadCard::TripleTriadCard( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadCardDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  startsWithVowel = exdData->getField< int8_t >( row, 4 );
  description = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::TripleTriadCardRarity::TripleTriadCardRarity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadCardRarityDat.get_row( row_id );
  stars = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::TripleTriadCardResident::TripleTriadCardResident( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadCardResidentDat.get_row( row_id );
  top = exdData->getField< uint8_t >( row, 1 );
  bottom = exdData->getField< uint8_t >( row, 2 );
  left = exdData->getField< uint8_t >( row, 3 );
  right = exdData->getField< uint8_t >( row, 4 );
  tripleTriadCardRarity = exdData->getField< uint8_t >( row, 5 );
  tripleTriadCardType = exdData->getField< uint8_t >( row, 6 );
  saleValue = exdData->getField< uint16_t >( row, 7 );
  sortKey = exdData->getField< uint8_t >( row, 8 );
  order = exdData->getField< uint16_t >( row, 9 );
  uIPriority = exdData->getField< uint8_t >( row, 10 );
  unknown54 = exdData->getField< bool >( row, 11 );
  acquisitionType = exdData->getField< uint8_t >( row, 12 );
  acquisition = exdData->getField< uint32_t >( row, 13 );
  location = exdData->getField< uint32_t >( row, 14 );
  quest = exdData->getField< uint32_t >( row, 15 );
}

Sapphire::Data::TripleTriadCardType::TripleTriadCardType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadCardTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::TripleTriadCompetition::TripleTriadCompetition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadCompetitionDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::TripleTriadRule::TripleTriadRule( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TripleTriadRuleDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  description = exdData->getField< std::string >( row, 1 );
  unknown54 = exdData->getField< bool >( row, 4 );
}

Sapphire::Data::Tutorial::Tutorial( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TutorialDat.get_row( row_id );
  exp = exdData->getField< uint32_t >( row, 4 );
  gil = exdData->getField< uint32_t >( row, 5 );
  rewardTank = exdData->getField< uint32_t >( row, 6 );
  rewardMelee = exdData->getField< uint32_t >( row, 7 );
  rewardRanged = exdData->getField< uint32_t >( row, 8 );
  objective = exdData->getField< uint32_t >( row, 9 );
}

Sapphire::Data::TutorialDPS::TutorialDPS( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TutorialDPSDat.get_row( row_id );
  objective = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::TutorialHealer::TutorialHealer( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TutorialHealerDat.get_row( row_id );
  objective = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::TutorialTank::TutorialTank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_TutorialTankDat.get_row( row_id );
  objective = exdData->getField< uint8_t >( row, 0 );
}

Sapphire::Data::UIColor::UIColor( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_UIColorDat.get_row( row_id );
  uIForeground = exdData->getField< uint32_t >( row, 0 );
  uIGlow = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::VaseFlower::VaseFlower( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_VaseFlowerDat.get_row( row_id );
  item = exdData->getField< uint32_t >( row, 3 );
}

Sapphire::Data::VFX::VFX( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_VFXDat.get_row( row_id );
  location = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Warp::Warp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WarpDat.get_row( row_id );
  popRange = exdData->getField< uint32_t >( row, 0 );
  territoryType = exdData->getField< uint16_t >( row, 1 );
  conditionSuccessEvent = exdData->getField< uint32_t >( row, 2 );
  conditionFailEvent = exdData->getField< uint32_t >( row, 3 );
  confirmEvent = exdData->getField< uint32_t >( row, 4 );
  warpCondition = exdData->getField< uint16_t >( row, 5 );
  warpLogic = exdData->getField< uint16_t >( row, 6 );
  startCutscene = exdData->getField< uint16_t >( row, 7 );
  endCutscene = exdData->getField< uint16_t >( row, 8 );
  canSkipCutscene = exdData->getField< bool >( row, 9 );
  name = exdData->getField< std::string >( row, 10 );
  question = exdData->getField< std::string >( row, 11 );
}

Sapphire::Data::WarpCondition::WarpCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WarpConditionDat.get_row( row_id );
  gil = exdData->getField< uint16_t >( row, 0 );
  completeParam = exdData->getField< uint8_t >( row, 1 );
  requiredQuest1 = exdData->getField< uint32_t >( row, 2 );
  requiredQuest2 = exdData->getField< uint32_t >( row, 3 );
  dRequiredQuest3 = exdData->getField< uint32_t >( row, 4 );
  requiredQuest4 = exdData->getField< uint32_t >( row, 5 );
  questReward = exdData->getField< uint16_t >( row, 6 );
  classLevel = exdData->getField< uint16_t >( row, 7 );
}

Sapphire::Data::WarpLogic::WarpLogic( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WarpLogicDat.get_row( row_id );
  warpName = exdData->getField< std::string >( row, 1 );
  canSkipCutscene = exdData->getField< bool >( row, 2 );
  function.push_back( exdData->getField< std::string >( row, 3 ) );
  function.push_back( exdData->getField< std::string >( row, 4 ) );
  function.push_back( exdData->getField< std::string >( row, 5 ) );
  function.push_back( exdData->getField< std::string >( row, 6 ) );
  function.push_back( exdData->getField< std::string >( row, 7 ) );
  function.push_back( exdData->getField< std::string >( row, 8 ) );
  function.push_back( exdData->getField< std::string >( row, 9 ) );
  function.push_back( exdData->getField< std::string >( row, 10 ) );
  function.push_back( exdData->getField< std::string >( row, 11 ) );
  function.push_back( exdData->getField< std::string >( row, 12 ) );
  question = exdData->getField< std::string >( row, 23 );
  responseYes = exdData->getField< std::string >( row, 24 );
  responseNo = exdData->getField< std::string >( row, 25 );
}

Sapphire::Data::WeaponTimeline::WeaponTimeline( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeaponTimelineDat.get_row( row_id );
  file = exdData->getField< std::string >( row, 0 );
  nextWeaponTimeline = exdData->getField< int16_t >( row, 1 );
}

Sapphire::Data::Weather::Weather( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeatherDat.get_row( row_id );
  icon = exdData->getField< int32_t >( row, 0 );
  name = exdData->getField< std::string >( row, 1 );
  description = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::WeatherGroup::WeatherGroup( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeatherGroupDat.get_row( row_id, subRow );
  weatherRate = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::WeatherRate::WeatherRate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeatherRateDat.get_row( row_id );
}

Sapphire::Data::WeatherReportReplace::WeatherReportReplace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeatherReportReplaceDat.get_row( row_id );
  placeNameSub = exdData->getField< uint16_t >( row, 0 );
  placeNameParent = exdData->getField< uint16_t >( row, 1 );
}

Sapphire::Data::WebGuidance::WebGuidance( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WebGuidanceDat.get_row( row_id );
  image = exdData->getField< int32_t >( row, 0 );
  url = exdData->getField< uint8_t >( row, 1 );
  name = exdData->getField< std::string >( row, 2 );
  unknown54 = exdData->getField< std::string >( row, 3 );
  description = exdData->getField< std::string >( row, 4 );
}

Sapphire::Data::WebURL::WebURL( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WebURLDat.get_row( row_id );
  uRL = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::WeddingBGM::WeddingBGM( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeddingBGMDat.get_row( row_id );
  song = exdData->getField< uint16_t >( row, 0 );
  songName = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::WeeklyBingoOrderData::WeeklyBingoOrderData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeeklyBingoOrderDataDat.get_row( row_id );
  type = exdData->getField< uint32_t >( row, 0 );
  data = exdData->getField< uint32_t >( row, 1 );
  text = exdData->getField< uint8_t >( row, 3 );
  icon = exdData->getField< uint32_t >( row, 4 );
}

Sapphire::Data::WeeklyBingoRewardData::WeeklyBingoRewardData( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeeklyBingoRewardDataDat.get_row( row_id );
  rewardItem2 = exdData->getField< uint32_t >( row, 10 );
  rewardHQ2 = exdData->getField< bool >( row, 11 );
  rewardQuantity2 = exdData->getField< uint16_t >( row, 12 );
}

Sapphire::Data::WeeklyBingoText::WeeklyBingoText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeeklyBingoTextDat.get_row( row_id );
  description = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::WeeklyLotBonus::WeeklyLotBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WeeklyLotBonusDat.get_row( row_id );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 0 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 1 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 2 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 3 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 4 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 5 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 6 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 7 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 8 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 9 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 10 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 11 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 12 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 13 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 14 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 15 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 16 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 17 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 18 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 19 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 20 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 21 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 22 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 23 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 24 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 25 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 26 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 27 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 28 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 29 ) );
  weeklyLotBonusThreshold.push_back( exdData->getField< uint8_t >( row, 30 ) );
}

Sapphire::Data::World::World( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WorldDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  userType = exdData->getField< uint8_t >( row, 1 );
  dataCenter = exdData->getField< uint8_t >( row, 2 );
  isPublic = exdData->getField< bool >( row, 3 );
}

Sapphire::Data::WorldDCGroupType::WorldDCGroupType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_WorldDCGroupTypeDat.get_row( row_id );
  name = exdData->getField< std::string >( row, 0 );
  region = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::YardCatalogCategory::YardCatalogCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_YardCatalogCategoryDat.get_row( row_id );
  category = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::YardCatalogItemList::YardCatalogItemList( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_YardCatalogItemListDat.get_row( row_id );
  category = exdData->getField< uint16_t >( row, 0 );
  item = exdData->getField< int32_t >( row, 1 );
  patch = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::YKW::YKW( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_YKWDat.get_row( row_id );
  item = exdData->getField< uint32_t >( row, 1 );
  location.push_back( exdData->getField< uint16_t >( row, 2 ) );
  location.push_back( exdData->getField< uint16_t >( row, 3 ) );
  location.push_back( exdData->getField< uint16_t >( row, 4 ) );
  location.push_back( exdData->getField< uint16_t >( row, 5 ) );
  location.push_back( exdData->getField< uint16_t >( row, 6 ) );
  location.push_back( exdData->getField< uint16_t >( row, 7 ) );
}

Sapphire::Data::ZoneSharedGroup::ZoneSharedGroup( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
  auto row = exdData->m_ZoneSharedGroupDat.get_row( row_id, subRow );
  quest1 = exdData->getField< uint32_t >( row, 2 );
  quest2 = exdData->getField< uint32_t >( row, 6 );
  quest3 = exdData->getField< uint32_t >( row, 10 );
  quest4 = exdData->getField< uint32_t >( row, 14 );
  quest5 = exdData->getField< uint32_t >( row, 18 );
  quest6 = exdData->getField< uint32_t >( row, 22 );
}


Sapphire::Data::ExdDataGenerated::ExdDataGenerated()
{
}

Sapphire::Data::ExdDataGenerated::~ExdDataGenerated()
{
}

xiv::exd::Exd Sapphire::Data::ExdDataGenerated::setupDatAccess( const std::string& name, xiv::exd::Language lang )
{
  auto& cat = m_exd_data->get_category( name );
  return static_cast< xiv::exd::Exd >( cat.get_data_ln( lang ) );
};


void Sapphire::Data::ExdDataGenerated::loadIdList( xiv::exd::Exd& data, std::set< uint32_t >& outIdList )
{
  auto pDataRows = data.get_rows();

  for( auto row : pDataRows )
  {
    uint32_t id = row.first;
    outIdList.insert( id );
  }
}

bool Sapphire::Data::ExdDataGenerated::init( const std::string& path )
{
  try
  {
    m_data = std::make_shared< xiv::dat::GameData >( path );
    m_exd_data = std::make_shared< xiv::exd::ExdData >( *m_data );

    m_AchievementDat = setupDatAccess( "Achievement", xiv::exd::Language::en );
    m_AchievementCategoryDat = setupDatAccess( "AchievementCategory", xiv::exd::Language::en );
    m_AchievementHideConditionDat = setupDatAccess( "AchievementHideCondition", xiv::exd::Language::none );
    m_AchievementKindDat = setupDatAccess( "AchievementKind", xiv::exd::Language::en );
    m_ActionDat = setupDatAccess( "Action", xiv::exd::Language::en );
    m_ActionCastTimelineDat = setupDatAccess( "ActionCastTimeline", xiv::exd::Language::none );
    m_ActionCastVFXDat = setupDatAccess( "ActionCastVFX", xiv::exd::Language::none );
    m_ActionCategoryDat = setupDatAccess( "ActionCategory", xiv::exd::Language::en );
    m_ActionComboRouteDat = setupDatAccess( "ActionComboRoute", xiv::exd::Language::en );
    m_ActionIndirectionDat = setupDatAccess( "ActionIndirection", xiv::exd::Language::none );
    m_ActionParamDat = setupDatAccess( "ActionParam", xiv::exd::Language::none );
    m_ActionProcStatusDat = setupDatAccess( "ActionProcStatus", xiv::exd::Language::none );
    m_ActionTimelineDat = setupDatAccess( "ActionTimeline", xiv::exd::Language::none );
    m_ActionTimelineMoveDat = setupDatAccess( "ActionTimelineMove", xiv::exd::Language::none );
    m_ActionTimelineReplaceDat = setupDatAccess( "ActionTimelineReplace", xiv::exd::Language::none );
    m_ActionTransientDat = setupDatAccess( "ActionTransient", xiv::exd::Language::en );
    m_ActivityFeedButtonsDat = setupDatAccess( "ActivityFeedButtons", xiv::exd::Language::none );
    m_ActivityFeedCaptionsDat = setupDatAccess( "ActivityFeedCaptions", xiv::exd::Language::none );
    m_ActivityFeedGroupCaptionsDat = setupDatAccess( "ActivityFeedGroupCaptions", xiv::exd::Language::none );
    m_ActivityFeedImagesDat = setupDatAccess( "ActivityFeedImages", xiv::exd::Language::none );
    m_AddonDat = setupDatAccess( "Addon", xiv::exd::Language::en );
    m_AdventureDat = setupDatAccess( "Adventure", xiv::exd::Language::en );
    m_AdventureExPhaseDat = setupDatAccess( "AdventureExPhase", xiv::exd::Language::none );
    m_AetherCurrentDat = setupDatAccess( "AetherCurrent", xiv::exd::Language::none );
    m_AetherCurrentCompFlgSetDat = setupDatAccess( "AetherCurrentCompFlgSet", xiv::exd::Language::none );
    m_AetherialWheelDat = setupDatAccess( "AetherialWheel", xiv::exd::Language::none );
    m_AetheryteDat = setupDatAccess( "Aetheryte", xiv::exd::Language::en );
    m_AetheryteSystemDefineDat = setupDatAccess( "AetheryteSystemDefine", xiv::exd::Language::none );
    m_AirshipExplorationLevelDat = setupDatAccess( "AirshipExplorationLevel", xiv::exd::Language::none );
    m_AirshipExplorationLogDat = setupDatAccess( "AirshipExplorationLog", xiv::exd::Language::en );
    m_AirshipExplorationParamTypeDat = setupDatAccess( "AirshipExplorationParamType", xiv::exd::Language::en );
    m_AirshipExplorationPartDat = setupDatAccess( "AirshipExplorationPart", xiv::exd::Language::none );
    m_AirshipExplorationPointDat = setupDatAccess( "AirshipExplorationPoint", xiv::exd::Language::en );
    m_AnimationLODDat = setupDatAccess( "AnimationLOD", xiv::exd::Language::none );
    m_AnimaWeapon5Dat = setupDatAccess( "AnimaWeapon5", xiv::exd::Language::none );
    m_AnimaWeapon5ParamDat = setupDatAccess( "AnimaWeapon5Param", xiv::exd::Language::en );
    m_AnimaWeapon5PatternGroupDat = setupDatAccess( "AnimaWeapon5PatternGroup", xiv::exd::Language::en );
    m_AnimaWeapon5SpiritTalkDat = setupDatAccess( "AnimaWeapon5SpiritTalk", xiv::exd::Language::none );
    m_AnimaWeapon5SpiritTalkParamDat = setupDatAccess( "AnimaWeapon5SpiritTalkParam", xiv::exd::Language::en );
    m_AnimaWeapon5TradeItemDat = setupDatAccess( "AnimaWeapon5TradeItem", xiv::exd::Language::none );
    m_AnimaWeaponFUITalkDat = setupDatAccess( "AnimaWeaponFUITalk", xiv::exd::Language::none );
    m_AnimaWeaponFUITalkParamDat = setupDatAccess( "AnimaWeaponFUITalkParam", xiv::exd::Language::en );
    m_AnimaWeaponIconDat = setupDatAccess( "AnimaWeaponIcon", xiv::exd::Language::none );
    m_AnimaWeaponItemDat = setupDatAccess( "AnimaWeaponItem", xiv::exd::Language::none );
    m_AozActionDat = setupDatAccess( "AozAction", xiv::exd::Language::none );
    m_AozActionTransientDat = setupDatAccess( "AozActionTransient", xiv::exd::Language::en );
    m_AOZArrangementDat = setupDatAccess( "AOZArrangement", xiv::exd::Language::none );
    m_AOZBossDat = setupDatAccess( "AOZBoss", xiv::exd::Language::none );
    m_AOZContentDat = setupDatAccess( "AOZContent", xiv::exd::Language::none );
    m_AOZContentBriefingBNpcDat = setupDatAccess( "AOZContentBriefingBNpc", xiv::exd::Language::none );
    m_AquariumFishDat = setupDatAccess( "AquariumFish", xiv::exd::Language::none );
    m_AquariumWaterDat = setupDatAccess( "AquariumWater", xiv::exd::Language::en );
    m_ArrayEventHandlerDat = setupDatAccess( "ArrayEventHandler", xiv::exd::Language::none );
    m_AttackTypeDat = setupDatAccess( "AttackType", xiv::exd::Language::en );
    m_BacklightColorDat = setupDatAccess( "BacklightColor", xiv::exd::Language::none );
    m_BallistaDat = setupDatAccess( "Ballista", xiv::exd::Language::none );
    m_BalloonDat = setupDatAccess( "Balloon", xiv::exd::Language::en );
    m_BaseParamDat = setupDatAccess( "BaseParam", xiv::exd::Language::en );
    m_BattleLeveDat = setupDatAccess( "BattleLeve", xiv::exd::Language::none );
    m_BattleLeveRuleDat = setupDatAccess( "BattleLeveRule", xiv::exd::Language::none );
    m_BeastRankBonusDat = setupDatAccess( "BeastRankBonus", xiv::exd::Language::none );
    m_BeastReputationRankDat = setupDatAccess( "BeastReputationRank", xiv::exd::Language::en );
    m_BeastTribeDat = setupDatAccess( "BeastTribe", xiv::exd::Language::en );
    m_BehaviorDat = setupDatAccess( "Behavior", xiv::exd::Language::none );
    m_BehaviorPathDat = setupDatAccess( "BehaviorPath", xiv::exd::Language::none );
    m_BenchmarkOverrideEquipmentDat = setupDatAccess( "BenchmarkOverrideEquipment", xiv::exd::Language::none );
    m_BGMDat = setupDatAccess( "BGM", xiv::exd::Language::none );
    m_BGMFadeDat = setupDatAccess( "BGMFade", xiv::exd::Language::none );
    m_BGMFadeTypeDat = setupDatAccess( "BGMFadeType", xiv::exd::Language::none );
    m_BGMSceneDat = setupDatAccess( "BGMScene", xiv::exd::Language::none );
    m_BGMSituationDat = setupDatAccess( "BGMSituation", xiv::exd::Language::none );
    m_BGMSwitchDat = setupDatAccess( "BGMSwitch", xiv::exd::Language::none );
    m_BGMSystemDefineDat = setupDatAccess( "BGMSystemDefine", xiv::exd::Language::none );
    m_BNpcAnnounceIconDat = setupDatAccess( "BNpcAnnounceIcon", xiv::exd::Language::none );
    m_BNpcBaseDat = setupDatAccess( "BNpcBase", xiv::exd::Language::none );
    m_BNpcCustomizeDat = setupDatAccess( "BNpcCustomize", xiv::exd::Language::none );
    m_BNpcNameDat = setupDatAccess( "BNpcName", xiv::exd::Language::en );
    m_BNpcPartsDat = setupDatAccess( "BNpcParts", xiv::exd::Language::none );
    m_BNpcStateDat = setupDatAccess( "BNpcState", xiv::exd::Language::none );
    m_BuddyDat = setupDatAccess( "Buddy", xiv::exd::Language::none );
    m_BuddyActionDat = setupDatAccess( "BuddyAction", xiv::exd::Language::en );
    m_BuddyEquipDat = setupDatAccess( "BuddyEquip", xiv::exd::Language::en );
    m_BuddyItemDat = setupDatAccess( "BuddyItem", xiv::exd::Language::none );
    m_BuddyRankDat = setupDatAccess( "BuddyRank", xiv::exd::Language::none );
    m_BuddySkillDat = setupDatAccess( "BuddySkill", xiv::exd::Language::none );
    m_CabinetDat = setupDatAccess( "Cabinet", xiv::exd::Language::none );
    m_CabinetCategoryDat = setupDatAccess( "CabinetCategory", xiv::exd::Language::none );
    m_CalendarDat = setupDatAccess( "Calendar", xiv::exd::Language::none );
    m_CarryDat = setupDatAccess( "Carry", xiv::exd::Language::none );
    m_ChannelingDat = setupDatAccess( "Channeling", xiv::exd::Language::none );
    m_CharaMakeClassEquipDat = setupDatAccess( "CharaMakeClassEquip", xiv::exd::Language::none );
    m_CharaMakeCustomizeDat = setupDatAccess( "CharaMakeCustomize", xiv::exd::Language::none );
    m_CharaMakeNameDat = setupDatAccess( "CharaMakeName", xiv::exd::Language::en );
    m_CharaMakeTypeDat = setupDatAccess( "CharaMakeType", xiv::exd::Language::en );
    m_ChocoboRaceDat = setupDatAccess( "ChocoboRace", xiv::exd::Language::none );
    m_ChocoboRaceAbilityDat = setupDatAccess( "ChocoboRaceAbility", xiv::exd::Language::en );
    m_ChocoboRaceAbilityTypeDat = setupDatAccess( "ChocoboRaceAbilityType", xiv::exd::Language::none );
    m_ChocoboRaceItemDat = setupDatAccess( "ChocoboRaceItem", xiv::exd::Language::en );
    m_ChocoboRaceRankDat = setupDatAccess( "ChocoboRaceRank", xiv::exd::Language::none );
    m_ChocoboRaceStatusDat = setupDatAccess( "ChocoboRaceStatus", xiv::exd::Language::none );
    m_ChocoboRaceTerritoryDat = setupDatAccess( "ChocoboRaceTerritory", xiv::exd::Language::none );
    m_ChocoboRaceTutorialDat = setupDatAccess( "ChocoboRaceTutorial", xiv::exd::Language::none );
    m_ChocoboRaceWeatherDat = setupDatAccess( "ChocoboRaceWeather", xiv::exd::Language::none );
    m_ChocoboTaxiDat = setupDatAccess( "ChocoboTaxi", xiv::exd::Language::none );
    m_ChocoboTaxiStandDat = setupDatAccess( "ChocoboTaxiStand", xiv::exd::Language::en );
    m_CircleActivityDat = setupDatAccess( "CircleActivity", xiv::exd::Language::en );
    m_ClassJobDat = setupDatAccess( "ClassJob", xiv::exd::Language::en );
    m_ClassJobCategoryDat = setupDatAccess( "ClassJobCategory", xiv::exd::Language::en );
    m_CollectablesShopDat = setupDatAccess( "CollectablesShop", xiv::exd::Language::en );
    m_CollectablesShopItemDat = setupDatAccess( "CollectablesShopItem", xiv::exd::Language::none );
    m_CollectablesShopItemGroupDat = setupDatAccess( "CollectablesShopItemGroup", xiv::exd::Language::en );
    m_CollectablesShopRefineDat = setupDatAccess( "CollectablesShopRefine", xiv::exd::Language::none );
    m_CollectablesShopRewardItemDat = setupDatAccess( "CollectablesShopRewardItem", xiv::exd::Language::none );
    m_CollectablesShopRewardScripDat = setupDatAccess( "CollectablesShopRewardScrip", xiv::exd::Language::none );
    m_CompanionDat = setupDatAccess( "Companion", xiv::exd::Language::en );
    m_CompanionMoveDat = setupDatAccess( "CompanionMove", xiv::exd::Language::en );
    m_CompanionTransientDat = setupDatAccess( "CompanionTransient", xiv::exd::Language::en );
    m_CompanyActionDat = setupDatAccess( "CompanyAction", xiv::exd::Language::en );
    m_CompanyCraftDraftDat = setupDatAccess( "CompanyCraftDraft", xiv::exd::Language::en );
    m_CompanyCraftDraftCategoryDat = setupDatAccess( "CompanyCraftDraftCategory", xiv::exd::Language::en );
    m_CompanyCraftManufactoryStateDat = setupDatAccess( "CompanyCraftManufactoryState", xiv::exd::Language::en );
    m_CompanyCraftPartDat = setupDatAccess( "CompanyCraftPart", xiv::exd::Language::none );
    m_CompanyCraftProcessDat = setupDatAccess( "CompanyCraftProcess", xiv::exd::Language::none );
    m_CompanyCraftSequenceDat = setupDatAccess( "CompanyCraftSequence", xiv::exd::Language::none );
    m_CompanyCraftSupplyItemDat = setupDatAccess( "CompanyCraftSupplyItem", xiv::exd::Language::none );
    m_CompanyCraftTypeDat = setupDatAccess( "CompanyCraftType", xiv::exd::Language::en );
    m_CompanyLeveDat = setupDatAccess( "CompanyLeve", xiv::exd::Language::none );
    m_CompanyLeveRuleDat = setupDatAccess( "CompanyLeveRule", xiv::exd::Language::none );
    m_CompleteJournalDat = setupDatAccess( "CompleteJournal", xiv::exd::Language::en );
    m_CompleteJournalCategoryDat = setupDatAccess( "CompleteJournalCategory", xiv::exd::Language::none );
    m_ConditionDat = setupDatAccess( "Condition", xiv::exd::Language::none );
    m_ConfigKeyDat = setupDatAccess( "ConfigKey", xiv::exd::Language::en );
    m_ContentCloseCycleDat = setupDatAccess( "ContentCloseCycle", xiv::exd::Language::none );
    m_ContentExActionDat = setupDatAccess( "ContentExAction", xiv::exd::Language::none );
    m_ContentFinderConditionDat = setupDatAccess( "ContentFinderCondition", xiv::exd::Language::en );
    m_ContentFinderConditionTransientDat = setupDatAccess( "ContentFinderConditionTransient", xiv::exd::Language::en );
    m_ContentGaugeDat = setupDatAccess( "ContentGauge", xiv::exd::Language::en );
    m_ContentGaugeColorDat = setupDatAccess( "ContentGaugeColor", xiv::exd::Language::none );
    m_ContentMemberTypeDat = setupDatAccess( "ContentMemberType", xiv::exd::Language::none );
    m_ContentNpcTalkDat = setupDatAccess( "ContentNpcTalk", xiv::exd::Language::none );
    m_ContentRandomSelectDat = setupDatAccess( "ContentRandomSelect", xiv::exd::Language::none );
    m_ContentRouletteDat = setupDatAccess( "ContentRoulette", xiv::exd::Language::en );
    m_ContentRouletteOpenRuleDat = setupDatAccess( "ContentRouletteOpenRule", xiv::exd::Language::none );
    m_ContentRouletteRoleBonusDat = setupDatAccess( "ContentRouletteRoleBonus", xiv::exd::Language::none );
    m_ContentsNoteDat = setupDatAccess( "ContentsNote", xiv::exd::Language::en );
    m_ContentsTutorialDat = setupDatAccess( "ContentsTutorial", xiv::exd::Language::en );
    m_ContentsTutorialPageDat = setupDatAccess( "ContentsTutorialPage", xiv::exd::Language::en );
    m_ContentTalkDat = setupDatAccess( "ContentTalk", xiv::exd::Language::en );
    m_ContentTalkParamDat = setupDatAccess( "ContentTalkParam", xiv::exd::Language::none );
    m_ContentTypeDat = setupDatAccess( "ContentType", xiv::exd::Language::en );
    m_CraftActionDat = setupDatAccess( "CraftAction", xiv::exd::Language::en );
    m_CraftLeveDat = setupDatAccess( "CraftLeve", xiv::exd::Language::none );
    m_CraftLevelDifferenceDat = setupDatAccess( "CraftLevelDifference", xiv::exd::Language::none );
    m_CraftTypeDat = setupDatAccess( "CraftType", xiv::exd::Language::en );
    m_CreditDat = setupDatAccess( "Credit", xiv::exd::Language::none );
    m_CreditBackImageDat = setupDatAccess( "CreditBackImage", xiv::exd::Language::none );
    m_CreditCastDat = setupDatAccess( "CreditCast", xiv::exd::Language::en );
    m_CreditListDat = setupDatAccess( "CreditList", xiv::exd::Language::none );
    m_CreditListTextDat = setupDatAccess( "CreditListText", xiv::exd::Language::en );
    m_CustomTalkDat = setupDatAccess( "CustomTalk", xiv::exd::Language::en );
    m_CustomTalkDynamicIconDat = setupDatAccess( "CustomTalkDynamicIcon", xiv::exd::Language::none );
    m_CustomTalkNestHandlersDat = setupDatAccess( "CustomTalkNestHandlers", xiv::exd::Language::none );
    m_CutsceneDat = setupDatAccess( "Cutscene", xiv::exd::Language::none );
    m_CutsceneMotionDat = setupDatAccess( "CutsceneMotion", xiv::exd::Language::none );
    m_CutsceneWorkIndexDat = setupDatAccess( "CutsceneWorkIndex", xiv::exd::Language::none );
    m_CutScreenImageDat = setupDatAccess( "CutScreenImage", xiv::exd::Language::none );
    m_CycleTimeDat = setupDatAccess( "CycleTime", xiv::exd::Language::none );
    m_DailySupplyItemDat = setupDatAccess( "DailySupplyItem", xiv::exd::Language::none );
    m_DawnContentDat = setupDatAccess( "DawnContent", xiv::exd::Language::none );
    m_DawnGrowMemberDat = setupDatAccess( "DawnGrowMember", xiv::exd::Language::none );
    m_DawnMemberUIParamDat = setupDatAccess( "DawnMemberUIParam", xiv::exd::Language::en );
    m_DawnQuestAnnounceDat = setupDatAccess( "DawnQuestAnnounce", xiv::exd::Language::none );
    m_DawnQuestMemberDat = setupDatAccess( "DawnQuestMember", xiv::exd::Language::none );
    m_DeepDungeonDat = setupDatAccess( "DeepDungeon", xiv::exd::Language::en );
    m_DeepDungeonBanDat = setupDatAccess( "DeepDungeonBan", xiv::exd::Language::none );
    m_DeepDungeonDangerDat = setupDatAccess( "DeepDungeonDanger", xiv::exd::Language::none );
    m_DeepDungeonEquipmentDat = setupDatAccess( "DeepDungeonEquipment", xiv::exd::Language::en );
    m_DeepDungeonFloorEffectUIDat = setupDatAccess( "DeepDungeonFloorEffectUI", xiv::exd::Language::en );
    m_DeepDungeonItemDat = setupDatAccess( "DeepDungeonItem", xiv::exd::Language::en );
    m_DeepDungeonLayerDat = setupDatAccess( "DeepDungeonLayer", xiv::exd::Language::none );
    m_DeepDungeonMagicStoneDat = setupDatAccess( "DeepDungeonMagicStone", xiv::exd::Language::en );
    m_DeepDungeonMap5XDat = setupDatAccess( "DeepDungeonMap5X", xiv::exd::Language::none );
    m_DeepDungeonRoomDat = setupDatAccess( "DeepDungeonRoom", xiv::exd::Language::none );
    m_DeepDungeonStatusDat = setupDatAccess( "DeepDungeonStatus", xiv::exd::Language::none );
    m_DefaultTalkDat = setupDatAccess( "DefaultTalk", xiv::exd::Language::en );
    m_DefaultTalkLipSyncTypeDat = setupDatAccess( "DefaultTalkLipSyncType", xiv::exd::Language::none );
    m_DeliveryQuestDat = setupDatAccess( "DeliveryQuest", xiv::exd::Language::none );
    m_DescriptionDat = setupDatAccess( "Description", xiv::exd::Language::en );
    m_DescriptionPageDat = setupDatAccess( "DescriptionPage", xiv::exd::Language::none );
    m_DescriptionSectionDat = setupDatAccess( "DescriptionSection", xiv::exd::Language::none );
    m_DescriptionStringDat = setupDatAccess( "DescriptionString", xiv::exd::Language::en );
    m_DisposalShopDat = setupDatAccess( "DisposalShop", xiv::exd::Language::en );
    m_DisposalShopFilterTypeDat = setupDatAccess( "DisposalShopFilterType", xiv::exd::Language::en );
    m_DisposalShopItemDat = setupDatAccess( "DisposalShopItem", xiv::exd::Language::none );
    m_DpsChallengeDat = setupDatAccess( "DpsChallenge", xiv::exd::Language::en );
    m_DpsChallengeOfficerDat = setupDatAccess( "DpsChallengeOfficer", xiv::exd::Language::none );
    m_DpsChallengeTransientDat = setupDatAccess( "DpsChallengeTransient", xiv::exd::Language::none );
    m_DynamicEventDat = setupDatAccess( "DynamicEvent", xiv::exd::Language::en );
    m_DynamicEventEnemyTypeDat = setupDatAccess( "DynamicEventEnemyType", xiv::exd::Language::en );
    m_DynamicEventSingleBattleDat = setupDatAccess( "DynamicEventSingleBattle", xiv::exd::Language::en );
    m_DynamicEventTypeDat = setupDatAccess( "DynamicEventType", xiv::exd::Language::none );
    m_EmjAddonDat = setupDatAccess( "EmjAddon", xiv::exd::Language::en );
    m_EmjDaniDat = setupDatAccess( "EmjDani", xiv::exd::Language::none );
    m_EmoteDat = setupDatAccess( "Emote", xiv::exd::Language::en );
    m_EmoteCategoryDat = setupDatAccess( "EmoteCategory", xiv::exd::Language::en );
    m_EmoteModeDat = setupDatAccess( "EmoteMode", xiv::exd::Language::none );
    m_ENpcBaseDat = setupDatAccess( "ENpcBase", xiv::exd::Language::none );
    m_ENpcDressUpDat = setupDatAccess( "ENpcDressUp", xiv::exd::Language::none );
    m_ENpcDressUpDressDat = setupDatAccess( "ENpcDressUpDress", xiv::exd::Language::none );
    m_ENpcResidentDat = setupDatAccess( "ENpcResident", xiv::exd::Language::en );
    m_EObjDat = setupDatAccess( "EObj", xiv::exd::Language::none );
    m_EObjNameDat = setupDatAccess( "EObjName", xiv::exd::Language::en );
    m_EquipRaceCategoryDat = setupDatAccess( "EquipRaceCategory", xiv::exd::Language::none );
    m_EquipSlotCategoryDat = setupDatAccess( "EquipSlotCategory", xiv::exd::Language::none );
    m_EurekaAetherItemDat = setupDatAccess( "EurekaAetherItem", xiv::exd::Language::en );
    m_EurekaAethernetDat = setupDatAccess( "EurekaAethernet", xiv::exd::Language::none );
    m_EurekaGrowDataDat = setupDatAccess( "EurekaGrowData", xiv::exd::Language::none );
    m_EurekaLogosMixerProbabilityDat = setupDatAccess( "EurekaLogosMixerProbability", xiv::exd::Language::none );
    m_EurekaMagiaActionDat = setupDatAccess( "EurekaMagiaAction", xiv::exd::Language::none );
    m_EurekaMagiciteItemDat = setupDatAccess( "EurekaMagiciteItem", xiv::exd::Language::none );
    m_EurekaMagiciteItemTypeDat = setupDatAccess( "EurekaMagiciteItemType", xiv::exd::Language::en );
    m_EurekaSphereElementAdjustDat = setupDatAccess( "EurekaSphereElementAdjust", xiv::exd::Language::none );
    m_EventActionDat = setupDatAccess( "EventAction", xiv::exd::Language::en );
    m_EventIconPriorityDat = setupDatAccess( "EventIconPriority", xiv::exd::Language::none );
    m_EventIconTypeDat = setupDatAccess( "EventIconType", xiv::exd::Language::none );
    m_EventItemDat = setupDatAccess( "EventItem", xiv::exd::Language::en );
    m_EventItemCastTimelineDat = setupDatAccess( "EventItemCastTimeline", xiv::exd::Language::none );
    m_EventItemHelpDat = setupDatAccess( "EventItemHelp", xiv::exd::Language::en );
    m_EventItemTimelineDat = setupDatAccess( "EventItemTimeline", xiv::exd::Language::none );
    m_EventSystemDefineDat = setupDatAccess( "EventSystemDefine", xiv::exd::Language::none );
    m_ExportedSGDat = setupDatAccess( "ExportedSG", xiv::exd::Language::none );
    m_ExVersionDat = setupDatAccess( "ExVersion", xiv::exd::Language::en );
    m_FateDat = setupDatAccess( "Fate", xiv::exd::Language::en );
    m_FateEventDat = setupDatAccess( "FateEvent", xiv::exd::Language::en );
    m_FateModeDat = setupDatAccess( "FateMode", xiv::exd::Language::none );
    m_FateProgressUIDat = setupDatAccess( "FateProgressUI", xiv::exd::Language::none );
    m_FateTokenTypeDat = setupDatAccess( "FateTokenType", xiv::exd::Language::none );
    m_FCActivityDat = setupDatAccess( "FCActivity", xiv::exd::Language::en );
    m_FCActivityCategoryDat = setupDatAccess( "FCActivityCategory", xiv::exd::Language::en );
    m_FCAuthorityDat = setupDatAccess( "FCAuthority", xiv::exd::Language::en );
    m_FCAuthorityCategoryDat = setupDatAccess( "FCAuthorityCategory", xiv::exd::Language::en );
    m_FCChestNameDat = setupDatAccess( "FCChestName", xiv::exd::Language::en );
    m_FCCrestSymbolDat = setupDatAccess( "FCCrestSymbol", xiv::exd::Language::none );
    m_FccShopDat = setupDatAccess( "FccShop", xiv::exd::Language::en );
    m_FCHierarchyDat = setupDatAccess( "FCHierarchy", xiv::exd::Language::en );
    m_FCProfileDat = setupDatAccess( "FCProfile", xiv::exd::Language::en );
    m_FCRankDat = setupDatAccess( "FCRank", xiv::exd::Language::none );
    m_FCReputationDat = setupDatAccess( "FCReputation", xiv::exd::Language::en );
    m_FCRightsDat = setupDatAccess( "FCRights", xiv::exd::Language::en );
    m_FestivalDat = setupDatAccess( "Festival", xiv::exd::Language::none );
    m_FieldMarkerDat = setupDatAccess( "FieldMarker", xiv::exd::Language::en );
    m_FishingRecordTypeDat = setupDatAccess( "FishingRecordType", xiv::exd::Language::none );
    m_FishingRecordTypeTransientDat = setupDatAccess( "FishingRecordTypeTransient", xiv::exd::Language::none );
    m_FishingSpotDat = setupDatAccess( "FishingSpot", xiv::exd::Language::en );
    m_FishParameterDat = setupDatAccess( "FishParameter", xiv::exd::Language::en );
    m_Frontline03Dat = setupDatAccess( "Frontline03", xiv::exd::Language::none );
    m_Frontline04Dat = setupDatAccess( "Frontline04", xiv::exd::Language::none );
    m_FurnitureCatalogCategoryDat = setupDatAccess( "FurnitureCatalogCategory", xiv::exd::Language::en );
    m_FurnitureCatalogItemListDat = setupDatAccess( "FurnitureCatalogItemList", xiv::exd::Language::none );
    m_GardeningSeedDat = setupDatAccess( "GardeningSeed", xiv::exd::Language::none );
    m_GatheringConditionDat = setupDatAccess( "GatheringCondition", xiv::exd::Language::en );
    m_GatheringExpDat = setupDatAccess( "GatheringExp", xiv::exd::Language::none );
    m_GatheringItemDat = setupDatAccess( "GatheringItem", xiv::exd::Language::none );
    m_GatheringItemLevelConvertTableDat = setupDatAccess( "GatheringItemLevelConvertTable", xiv::exd::Language::none );
    m_GatheringItemPointDat = setupDatAccess( "GatheringItemPoint", xiv::exd::Language::none );
    m_GatheringLeveDat = setupDatAccess( "GatheringLeve", xiv::exd::Language::none );
    m_GatheringLeveRouteDat = setupDatAccess( "GatheringLeveRoute", xiv::exd::Language::none );
    m_GatheringLeveRuleDat = setupDatAccess( "GatheringLeveRule", xiv::exd::Language::none );
    m_GatheringNotebookListDat = setupDatAccess( "GatheringNotebookList", xiv::exd::Language::none );
    m_GatheringPointDat = setupDatAccess( "GatheringPoint", xiv::exd::Language::none );
    m_GatheringPointBaseDat = setupDatAccess( "GatheringPointBase", xiv::exd::Language::none );
    m_GatheringPointBonusDat = setupDatAccess( "GatheringPointBonus", xiv::exd::Language::none );
    m_GatheringPointBonusTypeDat = setupDatAccess( "GatheringPointBonusType", xiv::exd::Language::en );
    m_GatheringPointNameDat = setupDatAccess( "GatheringPointName", xiv::exd::Language::en );
    m_GatheringPointTransientDat = setupDatAccess( "GatheringPointTransient", xiv::exd::Language::none );
    m_GatheringRarePopTimeTableDat = setupDatAccess( "GatheringRarePopTimeTable", xiv::exd::Language::none );
    m_GatheringSubCategoryDat = setupDatAccess( "GatheringSubCategory", xiv::exd::Language::en );
    m_GatheringTypeDat = setupDatAccess( "GatheringType", xiv::exd::Language::en );
    m_GcArmyCaptureTacticsDat = setupDatAccess( "GcArmyCaptureTactics", xiv::exd::Language::none );
    m_GcArmyExpeditionDat = setupDatAccess( "GcArmyExpedition", xiv::exd::Language::en );
    m_GcArmyExpeditionMemberBonusDat = setupDatAccess( "GcArmyExpeditionMemberBonus", xiv::exd::Language::none );
    m_GcArmyExpeditionTypeDat = setupDatAccess( "GcArmyExpeditionType", xiv::exd::Language::en );
    m_GcArmyMemberGrowDat = setupDatAccess( "GcArmyMemberGrow", xiv::exd::Language::none );
    m_GcArmyTrainingDat = setupDatAccess( "GcArmyTraining", xiv::exd::Language::en );
    m_GCRankGridaniaFemaleTextDat = setupDatAccess( "GCRankGridaniaFemaleText", xiv::exd::Language::en );
    m_GCRankGridaniaMaleTextDat = setupDatAccess( "GCRankGridaniaMaleText", xiv::exd::Language::en );
    m_GCRankLimsaFemaleTextDat = setupDatAccess( "GCRankLimsaFemaleText", xiv::exd::Language::en );
    m_GCRankLimsaMaleTextDat = setupDatAccess( "GCRankLimsaMaleText", xiv::exd::Language::en );
    m_GCRankUldahFemaleTextDat = setupDatAccess( "GCRankUldahFemaleText", xiv::exd::Language::en );
    m_GCRankUldahMaleTextDat = setupDatAccess( "GCRankUldahMaleText", xiv::exd::Language::en );
    m_GCScripShopCategoryDat = setupDatAccess( "GCScripShopCategory", xiv::exd::Language::none );
    m_GCScripShopItemDat = setupDatAccess( "GCScripShopItem", xiv::exd::Language::none );
    m_GCShopDat = setupDatAccess( "GCShop", xiv::exd::Language::none );
    m_GCShopItemCategoryDat = setupDatAccess( "GCShopItemCategory", xiv::exd::Language::en );
    m_GCSupplyDutyDat = setupDatAccess( "GCSupplyDuty", xiv::exd::Language::none );
    m_GCSupplyDutyRewardDat = setupDatAccess( "GCSupplyDutyReward", xiv::exd::Language::none );
    m_GeneralActionDat = setupDatAccess( "GeneralAction", xiv::exd::Language::en );
    m_GFATEDat = setupDatAccess( "GFATE", xiv::exd::Language::none );
    m_GFateClimbing2Dat = setupDatAccess( "GFateClimbing2", xiv::exd::Language::none );
    m_GFateClimbing2ContentDat = setupDatAccess( "GFateClimbing2Content", xiv::exd::Language::none );
    m_GFateClimbing2TotemTypeDat = setupDatAccess( "GFateClimbing2TotemType", xiv::exd::Language::none );
    m_GFateRideShootingDat = setupDatAccess( "GFateRideShooting", xiv::exd::Language::none );
    m_GilShopDat = setupDatAccess( "GilShop", xiv::exd::Language::en );
    m_GilShopItemDat = setupDatAccess( "GilShopItem", xiv::exd::Language::none );
    m_GimmickAccessorDat = setupDatAccess( "GimmickAccessor", xiv::exd::Language::none );
    m_GimmickJumpDat = setupDatAccess( "GimmickJump", xiv::exd::Language::none );
    m_GimmickRectDat = setupDatAccess( "GimmickRect", xiv::exd::Language::none );
    m_GoldSaucerArcadeMachineDat = setupDatAccess( "GoldSaucerArcadeMachine", xiv::exd::Language::en );
    m_GoldSaucerTextDataDat = setupDatAccess( "GoldSaucerTextData", xiv::exd::Language::en );
    m_GrandCompanyDat = setupDatAccess( "GrandCompany", xiv::exd::Language::en );
    m_GrandCompanyRankDat = setupDatAccess( "GrandCompanyRank", xiv::exd::Language::none );
    m_GroupPoseFrameDat = setupDatAccess( "GroupPoseFrame", xiv::exd::Language::en );
    m_GroupPoseStampDat = setupDatAccess( "GroupPoseStamp", xiv::exd::Language::en );
    m_GroupPoseStampCategoryDat = setupDatAccess( "GroupPoseStampCategory", xiv::exd::Language::en );
    m_GuardianDeityDat = setupDatAccess( "GuardianDeity", xiv::exd::Language::en );
    m_GuideDat = setupDatAccess( "Guide", xiv::exd::Language::none );
    m_GuidePageDat = setupDatAccess( "GuidePage", xiv::exd::Language::none );
    m_GuidePageStringDat = setupDatAccess( "GuidePageString", xiv::exd::Language::en );
    m_GuideTitleDat = setupDatAccess( "GuideTitle", xiv::exd::Language::en );
    m_GuildleveAssignmentDat = setupDatAccess( "GuildleveAssignment", xiv::exd::Language::en );
    m_GuildleveAssignmentCategoryDat = setupDatAccess( "GuildleveAssignmentCategory", xiv::exd::Language::none );
    m_GuildOrderDat = setupDatAccess( "GuildOrder", xiv::exd::Language::en );
    m_GuildOrderGuideDat = setupDatAccess( "GuildOrderGuide", xiv::exd::Language::none );
    m_GuildOrderOfficerDat = setupDatAccess( "GuildOrderOfficer", xiv::exd::Language::none );
    m_HairMakeTypeDat = setupDatAccess( "HairMakeType", xiv::exd::Language::none );
    m_HouseRetainerPoseDat = setupDatAccess( "HouseRetainerPose", xiv::exd::Language::none );
    m_HousingAethernetDat = setupDatAccess( "HousingAethernet", xiv::exd::Language::none );
    m_HousingAppealDat = setupDatAccess( "HousingAppeal", xiv::exd::Language::en );
    m_HousingEmploymentNpcListDat = setupDatAccess( "HousingEmploymentNpcList", xiv::exd::Language::none );
    m_HousingEmploymentNpcRaceDat = setupDatAccess( "HousingEmploymentNpcRace", xiv::exd::Language::en );
    m_HousingExteriorDat = setupDatAccess( "HousingExterior", xiv::exd::Language::none );
    m_HousingFurnitureDat = setupDatAccess( "HousingFurniture", xiv::exd::Language::none );
    m_HousingLandSetDat = setupDatAccess( "HousingLandSet", xiv::exd::Language::none );
    m_HousingMapMarkerInfoDat = setupDatAccess( "HousingMapMarkerInfo", xiv::exd::Language::none );
    m_HousingMerchantPoseDat = setupDatAccess( "HousingMerchantPose", xiv::exd::Language::en );
    m_HousingPlacementDat = setupDatAccess( "HousingPlacement", xiv::exd::Language::en );
    m_HousingPresetDat = setupDatAccess( "HousingPreset", xiv::exd::Language::en );
    m_HousingUnitedExteriorDat = setupDatAccess( "HousingUnitedExterior", xiv::exd::Language::none );
    m_HousingYardObjectDat = setupDatAccess( "HousingYardObject", xiv::exd::Language::none );
    m_HowToDat = setupDatAccess( "HowTo", xiv::exd::Language::en );
    m_HowToCategoryDat = setupDatAccess( "HowToCategory", xiv::exd::Language::en );
    m_HowToPageDat = setupDatAccess( "HowToPage", xiv::exd::Language::en );
    m_HugeCraftworksNpcDat = setupDatAccess( "HugeCraftworksNpc", xiv::exd::Language::en );
    m_HugeCraftworksRankDat = setupDatAccess( "HugeCraftworksRank", xiv::exd::Language::none );
    m_HWDAnnounceDat = setupDatAccess( "HWDAnnounce", xiv::exd::Language::en );
    m_HWDCrafterSupplyDat = setupDatAccess( "HWDCrafterSupply", xiv::exd::Language::none );
    m_HWDCrafterSupplyRewardDat = setupDatAccess( "HWDCrafterSupplyReward", xiv::exd::Language::none );
    m_HWDCrafterSupplyTermDat = setupDatAccess( "HWDCrafterSupplyTerm", xiv::exd::Language::en );
    m_HWDDevLayerControlDat = setupDatAccess( "HWDDevLayerControl", xiv::exd::Language::none );
    m_HWDDevLevelUIDat = setupDatAccess( "HWDDevLevelUI", xiv::exd::Language::none );
    m_HWDDevLivelyDat = setupDatAccess( "HWDDevLively", xiv::exd::Language::none );
    m_HWDDevProgressDat = setupDatAccess( "HWDDevProgress", xiv::exd::Language::none );
    m_HWDGathereInspectTermDat = setupDatAccess( "HWDGathereInspectTerm", xiv::exd::Language::en );
    m_HWDGathererInspectionDat = setupDatAccess( "HWDGathererInspection", xiv::exd::Language::none );
    m_HWDGathererInspectionRewardDat = setupDatAccess( "HWDGathererInspectionReward", xiv::exd::Language::none );
    m_HWDInfoBoardArticleDat = setupDatAccess( "HWDInfoBoardArticle", xiv::exd::Language::en );
    m_HWDInfoBoardArticleTransientDat = setupDatAccess( "HWDInfoBoardArticleTransient", xiv::exd::Language::en );
    m_HWDInfoBoardArticleTypeDat = setupDatAccess( "HWDInfoBoardArticleType", xiv::exd::Language::en );
    m_HWDLevelChangeDeceptionDat = setupDatAccess( "HWDLevelChangeDeception", xiv::exd::Language::none );
    m_HWDSharedGroupDat = setupDatAccess( "HWDSharedGroup", xiv::exd::Language::none );
    m_HWDSharedGroupControlParamDat = setupDatAccess( "HWDSharedGroupControlParam", xiv::exd::Language::none );
    m_IKDContentBonusDat = setupDatAccess( "IKDContentBonus", xiv::exd::Language::en );
    m_IKDFishParamDat = setupDatAccess( "IKDFishParam", xiv::exd::Language::none );
    m_IKDRouteDat = setupDatAccess( "IKDRoute", xiv::exd::Language::en );
    m_IKDRouteTableDat = setupDatAccess( "IKDRouteTable", xiv::exd::Language::none );
    m_IKDSpotDat = setupDatAccess( "IKDSpot", xiv::exd::Language::none );
    m_InclusionShopDat = setupDatAccess( "InclusionShop", xiv::exd::Language::en );
    m_InclusionShopCategoryDat = setupDatAccess( "InclusionShopCategory", xiv::exd::Language::en );
    m_InclusionShopSeriesDat = setupDatAccess( "InclusionShopSeries", xiv::exd::Language::none );
    m_IndividualWeatherDat = setupDatAccess( "IndividualWeather", xiv::exd::Language::none );
    m_InstanceContentDat = setupDatAccess( "InstanceContent", xiv::exd::Language::none );
    m_InstanceContentBuffDat = setupDatAccess( "InstanceContentBuff", xiv::exd::Language::none );
    m_InstanceContentCSBonusDat = setupDatAccess( "InstanceContentCSBonus", xiv::exd::Language::none );
    m_InstanceContentGuideDat = setupDatAccess( "InstanceContentGuide", xiv::exd::Language::none );
    m_InstanceContentTextDataDat = setupDatAccess( "InstanceContentTextData", xiv::exd::Language::en );
    m_ItemDat = setupDatAccess( "Item", xiv::exd::Language::en );
    m_ItemActionDat = setupDatAccess( "ItemAction", xiv::exd::Language::none );
    m_ItemActionTelepoDat = setupDatAccess( "ItemActionTelepo", xiv::exd::Language::none );
    m_ItemBarterCheckDat = setupDatAccess( "ItemBarterCheck", xiv::exd::Language::none );
    m_ItemFoodDat = setupDatAccess( "ItemFood", xiv::exd::Language::none );
    m_ItemLevelDat = setupDatAccess( "ItemLevel", xiv::exd::Language::none );
    m_ItemSearchCategoryDat = setupDatAccess( "ItemSearchCategory", xiv::exd::Language::en );
    m_ItemSeriesDat = setupDatAccess( "ItemSeries", xiv::exd::Language::en );
    m_ItemSortCategoryDat = setupDatAccess( "ItemSortCategory", xiv::exd::Language::none );
    m_ItemSpecialBonusDat = setupDatAccess( "ItemSpecialBonus", xiv::exd::Language::en );
    m_ItemUICategoryDat = setupDatAccess( "ItemUICategory", xiv::exd::Language::en );
    m_JobHudManualDat = setupDatAccess( "JobHudManual", xiv::exd::Language::none );
    m_JobHudManualPriorityDat = setupDatAccess( "JobHudManualPriority", xiv::exd::Language::none );
    m_JournalCategoryDat = setupDatAccess( "JournalCategory", xiv::exd::Language::en );
    m_JournalGenreDat = setupDatAccess( "JournalGenre", xiv::exd::Language::en );
    m_JournalSectionDat = setupDatAccess( "JournalSection", xiv::exd::Language::en );
    m_KnockbackDat = setupDatAccess( "Knockback", xiv::exd::Language::none );
    m_LegacyQuestDat = setupDatAccess( "LegacyQuest", xiv::exd::Language::en );
    m_LeveDat = setupDatAccess( "Leve", xiv::exd::Language::en );
    m_LeveAssignmentTypeDat = setupDatAccess( "LeveAssignmentType", xiv::exd::Language::en );
    m_LeveClientDat = setupDatAccess( "LeveClient", xiv::exd::Language::en );
    m_LevelDat = setupDatAccess( "Level", xiv::exd::Language::none );
    m_LeveRewardItemDat = setupDatAccess( "LeveRewardItem", xiv::exd::Language::none );
    m_LeveRewardItemGroupDat = setupDatAccess( "LeveRewardItemGroup", xiv::exd::Language::none );
    m_LeveStringDat = setupDatAccess( "LeveString", xiv::exd::Language::en );
    m_LeveVfxDat = setupDatAccess( "LeveVfx", xiv::exd::Language::none );
    m_LobbyDat = setupDatAccess( "Lobby", xiv::exd::Language::en );
    m_LogFilterDat = setupDatAccess( "LogFilter", xiv::exd::Language::en );
    m_LogKindDat = setupDatAccess( "LogKind", xiv::exd::Language::en );
    m_LogMessageDat = setupDatAccess( "LogMessage", xiv::exd::Language::en );
    m_LotteryExchangeShopDat = setupDatAccess( "LotteryExchangeShop", xiv::exd::Language::en );
    m_MacroIconDat = setupDatAccess( "MacroIcon", xiv::exd::Language::none );
    m_MacroIconRedirectOldDat = setupDatAccess( "MacroIconRedirectOld", xiv::exd::Language::none );
    m_MainCommandDat = setupDatAccess( "MainCommand", xiv::exd::Language::en );
    m_MainCommandCategoryDat = setupDatAccess( "MainCommandCategory", xiv::exd::Language::en );
    m_ManeuversArmorDat = setupDatAccess( "ManeuversArmor", xiv::exd::Language::en );
    m_MapDat = setupDatAccess( "Map", xiv::exd::Language::none );
    m_MapMarkerDat = setupDatAccess( "MapMarker", xiv::exd::Language::none );
    m_MapMarkerRegionDat = setupDatAccess( "MapMarkerRegion", xiv::exd::Language::none );
    m_MapSymbolDat = setupDatAccess( "MapSymbol", xiv::exd::Language::none );
    m_MarkerDat = setupDatAccess( "Marker", xiv::exd::Language::en );
    m_MasterpieceSupplyDutyDat = setupDatAccess( "MasterpieceSupplyDuty", xiv::exd::Language::none );
    m_MasterpieceSupplyMultiplierDat = setupDatAccess( "MasterpieceSupplyMultiplier", xiv::exd::Language::none );
    m_MateriaDat = setupDatAccess( "Materia", xiv::exd::Language::none );
    m_MateriaJoinRateDat = setupDatAccess( "MateriaJoinRate", xiv::exd::Language::none );
    m_MateriaJoinRateGatherCraftDat = setupDatAccess( "MateriaJoinRateGatherCraft", xiv::exd::Language::none );
    m_MateriaTomestoneRateDat = setupDatAccess( "MateriaTomestoneRate", xiv::exd::Language::none );
    m_MiniGameRADat = setupDatAccess( "MiniGameRA", xiv::exd::Language::none );
    m_MinionRaceDat = setupDatAccess( "MinionRace", xiv::exd::Language::en );
    m_MinionRulesDat = setupDatAccess( "MinionRules", xiv::exd::Language::en );
    m_MinionSkillTypeDat = setupDatAccess( "MinionSkillType", xiv::exd::Language::en );
    m_MobHuntOrderDat = setupDatAccess( "MobHuntOrder", xiv::exd::Language::none );
    m_MobHuntOrderTypeDat = setupDatAccess( "MobHuntOrderType", xiv::exd::Language::none );
    m_MobHuntRewardDat = setupDatAccess( "MobHuntReward", xiv::exd::Language::none );
    m_MobHuntRewardCapDat = setupDatAccess( "MobHuntRewardCap", xiv::exd::Language::none );
    m_MobHuntTargetDat = setupDatAccess( "MobHuntTarget", xiv::exd::Language::none );
    m_ModelCharaDat = setupDatAccess( "ModelChara", xiv::exd::Language::none );
    m_ModelSkeletonDat = setupDatAccess( "ModelSkeleton", xiv::exd::Language::none );
    m_ModelStateDat = setupDatAccess( "ModelState", xiv::exd::Language::none );
    m_MonsterNoteDat = setupDatAccess( "MonsterNote", xiv::exd::Language::en );
    m_MonsterNoteTargetDat = setupDatAccess( "MonsterNoteTarget", xiv::exd::Language::none );
    m_MotionTimelineDat = setupDatAccess( "MotionTimeline", xiv::exd::Language::none );
    m_MotionTimelineBlendTableDat = setupDatAccess( "MotionTimelineBlendTable", xiv::exd::Language::none );
    m_MountDat = setupDatAccess( "Mount", xiv::exd::Language::en );
    m_MountActionDat = setupDatAccess( "MountAction", xiv::exd::Language::none );
    m_MountCustomizeDat = setupDatAccess( "MountCustomize", xiv::exd::Language::none );
    m_MountFlyingConditionDat = setupDatAccess( "MountFlyingCondition", xiv::exd::Language::none );
    m_MountSpeedDat = setupDatAccess( "MountSpeed", xiv::exd::Language::none );
    m_MountTransientDat = setupDatAccess( "MountTransient", xiv::exd::Language::en );
    m_MoveTimelineDat = setupDatAccess( "MoveTimeline", xiv::exd::Language::none );
    m_MoveVfxDat = setupDatAccess( "MoveVfx", xiv::exd::Language::none );
    m_MovieStaffListDat = setupDatAccess( "MovieStaffList", xiv::exd::Language::none );
    m_MovieSubtitleDat = setupDatAccess( "MovieSubtitle", xiv::exd::Language::en );
    m_MovieSubtitle500Dat = setupDatAccess( "MovieSubtitle500", xiv::exd::Language::en );
    m_MovieSubtitleVoyageDat = setupDatAccess( "MovieSubtitleVoyage", xiv::exd::Language::en );
    m_MYCTemporaryItemDat = setupDatAccess( "MYCTemporaryItem", xiv::exd::Language::none );
    m_MYCTemporaryItemUICategoryDat = setupDatAccess( "MYCTemporaryItemUICategory", xiv::exd::Language::en );
    m_MYCWarResultNotebookDat = setupDatAccess( "MYCWarResultNotebook", xiv::exd::Language::en );
    m_NotebookDivisionDat = setupDatAccess( "NotebookDivision", xiv::exd::Language::en );
    m_NotebookDivisionCategoryDat = setupDatAccess( "NotebookDivisionCategory", xiv::exd::Language::en );
    m_NotoriousMonsterDat = setupDatAccess( "NotoriousMonster", xiv::exd::Language::none );
    m_NpcEquipDat = setupDatAccess( "NpcEquip", xiv::exd::Language::none );
    m_NpcYellDat = setupDatAccess( "NpcYell", xiv::exd::Language::en );
    m_OmenDat = setupDatAccess( "Omen", xiv::exd::Language::none );
    m_OnlineStatusDat = setupDatAccess( "OnlineStatus", xiv::exd::Language::en );
    m_OpenContentDat = setupDatAccess( "OpenContent", xiv::exd::Language::none );
    m_OpenContentCandidateNameDat = setupDatAccess( "OpenContentCandidateName", xiv::exd::Language::en );
    m_OpeningDat = setupDatAccess( "Opening", xiv::exd::Language::none );
    m_OrchestrionDat = setupDatAccess( "Orchestrion", xiv::exd::Language::en );
    m_OrchestrionCategoryDat = setupDatAccess( "OrchestrionCategory", xiv::exd::Language::en );
    m_OrchestrionPathDat = setupDatAccess( "OrchestrionPath", xiv::exd::Language::none );
    m_OrchestrionUiparamDat = setupDatAccess( "OrchestrionUiparam", xiv::exd::Language::none );
    m_OrnamentDat = setupDatAccess( "Ornament", xiv::exd::Language::en );
    m_ParamGrowDat = setupDatAccess( "ParamGrow", xiv::exd::Language::none );
    m_PartyContentDat = setupDatAccess( "PartyContent", xiv::exd::Language::none );
    m_PartyContentCutsceneDat = setupDatAccess( "PartyContentCutscene", xiv::exd::Language::none );
    m_PartyContentTextDataDat = setupDatAccess( "PartyContentTextData", xiv::exd::Language::en );
    m_PatchMarkDat = setupDatAccess( "PatchMark", xiv::exd::Language::none );
    m_PerformDat = setupDatAccess( "Perform", xiv::exd::Language::en );
    m_PerformTransientDat = setupDatAccess( "PerformTransient", xiv::exd::Language::en );
    m_PetDat = setupDatAccess( "Pet", xiv::exd::Language::en );
    m_PetActionDat = setupDatAccess( "PetAction", xiv::exd::Language::en );
    m_PhysicsGroupDat = setupDatAccess( "PhysicsGroup", xiv::exd::Language::none );
    m_PhysicsWindDat = setupDatAccess( "PhysicsWind", xiv::exd::Language::none );
    m_PictureDat = setupDatAccess( "Picture", xiv::exd::Language::none );
    m_PlaceNameDat = setupDatAccess( "PlaceName", xiv::exd::Language::en );
    m_PlantPotFlowerSeedDat = setupDatAccess( "PlantPotFlowerSeed", xiv::exd::Language::none );
    m_PreHandlerDat = setupDatAccess( "PreHandler", xiv::exd::Language::en );
    m_PresetCameraDat = setupDatAccess( "PresetCamera", xiv::exd::Language::none );
    m_PresetCameraAdjustDat = setupDatAccess( "PresetCameraAdjust", xiv::exd::Language::none );
    m_PublicContentDat = setupDatAccess( "PublicContent", xiv::exd::Language::en );
    m_PublicContentCutsceneDat = setupDatAccess( "PublicContentCutscene", xiv::exd::Language::none );
    m_PublicContentTextDataDat = setupDatAccess( "PublicContentTextData", xiv::exd::Language::en );
    m_PurifyDat = setupDatAccess( "Purify", xiv::exd::Language::none );
    m_PvPActionDat = setupDatAccess( "PvPAction", xiv::exd::Language::none );
    m_PvPActionSortDat = setupDatAccess( "PvPActionSort", xiv::exd::Language::none );
    m_PvPRankDat = setupDatAccess( "PvPRank", xiv::exd::Language::none );
    m_PvPSelectTraitDat = setupDatAccess( "PvPSelectTrait", xiv::exd::Language::en );
    m_PvPTraitDat = setupDatAccess( "PvPTrait", xiv::exd::Language::none );
    m_QuestDat = setupDatAccess( "Quest", xiv::exd::Language::en );
    m_QuestBattleDat = setupDatAccess( "QuestBattle", xiv::exd::Language::none );
    m_QuestChapterDat = setupDatAccess( "QuestChapter", xiv::exd::Language::none );
    m_QuestClassJobRewardDat = setupDatAccess( "QuestClassJobReward", xiv::exd::Language::none );
    m_QuestClassJobSupplyDat = setupDatAccess( "QuestClassJobSupply", xiv::exd::Language::none );
    m_QuestDerivedClassDat = setupDatAccess( "QuestDerivedClass", xiv::exd::Language::none );
    m_QuestRedoDat = setupDatAccess( "QuestRedo", xiv::exd::Language::none );
    m_QuestRedoChapterUIDat = setupDatAccess( "QuestRedoChapterUI", xiv::exd::Language::en );
    m_QuestRedoChapterUICategoryDat = setupDatAccess( "QuestRedoChapterUICategory", xiv::exd::Language::en );
    m_QuestRedoChapterUITabDat = setupDatAccess( "QuestRedoChapterUITab", xiv::exd::Language::en );
    m_QuestRedoIncompChapterDat = setupDatAccess( "QuestRedoIncompChapter", xiv::exd::Language::none );
    m_QuestRepeatFlagDat = setupDatAccess( "QuestRepeatFlag", xiv::exd::Language::none );
    m_QuestRewardOtherDat = setupDatAccess( "QuestRewardOther", xiv::exd::Language::en );
    m_QuickChatDat = setupDatAccess( "QuickChat", xiv::exd::Language::en );
    m_QuickChatTransientDat = setupDatAccess( "QuickChatTransient", xiv::exd::Language::en );
    m_RaceDat = setupDatAccess( "Race", xiv::exd::Language::en );
    m_RacingChocoboItemDat = setupDatAccess( "RacingChocoboItem", xiv::exd::Language::none );
    m_RacingChocoboNameDat = setupDatAccess( "RacingChocoboName", xiv::exd::Language::en );
    m_RacingChocoboNameCategoryDat = setupDatAccess( "RacingChocoboNameCategory", xiv::exd::Language::en );
    m_RacingChocoboNameInfoDat = setupDatAccess( "RacingChocoboNameInfo", xiv::exd::Language::none );
    m_RacingChocoboParamDat = setupDatAccess( "RacingChocoboParam", xiv::exd::Language::en );
    m_RecastNavimeshDat = setupDatAccess( "RecastNavimesh", xiv::exd::Language::none );
    m_RecipeDat = setupDatAccess( "Recipe", xiv::exd::Language::none );
    m_RecipeLevelTableDat = setupDatAccess( "RecipeLevelTable", xiv::exd::Language::none );
    m_RecipeLookupDat = setupDatAccess( "RecipeLookup", xiv::exd::Language::none );
    m_RecipeNotebookListDat = setupDatAccess( "RecipeNotebookList", xiv::exd::Language::none );
    m_RecommendContentsDat = setupDatAccess( "RecommendContents", xiv::exd::Language::none );
    m_RelicDat = setupDatAccess( "Relic", xiv::exd::Language::none );
    m_Relic3Dat = setupDatAccess( "Relic3", xiv::exd::Language::none );
    m_RelicItemDat = setupDatAccess( "RelicItem", xiv::exd::Language::none );
    m_RelicNoteDat = setupDatAccess( "RelicNote", xiv::exd::Language::none );
    m_RelicNoteCategoryDat = setupDatAccess( "RelicNoteCategory", xiv::exd::Language::en );
    m_ResidentDat = setupDatAccess( "Resident", xiv::exd::Language::none );
    m_ResistanceWeaponAdjustDat = setupDatAccess( "ResistanceWeaponAdjust", xiv::exd::Language::none );
    m_RetainerTaskDat = setupDatAccess( "RetainerTask", xiv::exd::Language::none );
    m_RetainerTaskLvRangeDat = setupDatAccess( "RetainerTaskLvRange", xiv::exd::Language::none );
    m_RetainerTaskNormalDat = setupDatAccess( "RetainerTaskNormal", xiv::exd::Language::none );
    m_RetainerTaskParameterDat = setupDatAccess( "RetainerTaskParameter", xiv::exd::Language::none );
    m_RetainerTaskRandomDat = setupDatAccess( "RetainerTaskRandom", xiv::exd::Language::en );
    m_RideShootingDat = setupDatAccess( "RideShooting", xiv::exd::Language::none );
    m_RideShootingTextDataDat = setupDatAccess( "RideShootingTextData", xiv::exd::Language::en );
    m_RPParameterDat = setupDatAccess( "RPParameter", xiv::exd::Language::none );
    m_SatisfactionArbitrationDat = setupDatAccess( "SatisfactionArbitration", xiv::exd::Language::none );
    m_SatisfactionNpcDat = setupDatAccess( "SatisfactionNpc", xiv::exd::Language::none );
    m_SatisfactionSupplyDat = setupDatAccess( "SatisfactionSupply", xiv::exd::Language::none );
    m_SatisfactionSupplyRewardDat = setupDatAccess( "SatisfactionSupplyReward", xiv::exd::Language::none );
    m_ScenarioTreeDat = setupDatAccess( "ScenarioTree", xiv::exd::Language::none );
    m_ScenarioTreeTipsDat = setupDatAccess( "ScenarioTreeTips", xiv::exd::Language::none );
    m_ScenarioTreeTipsClassQuestDat = setupDatAccess( "ScenarioTreeTipsClassQuest", xiv::exd::Language::none );
    m_ScenarioTypeDat = setupDatAccess( "ScenarioType", xiv::exd::Language::en );
    m_ScreenImageDat = setupDatAccess( "ScreenImage", xiv::exd::Language::none );
    m_SecretRecipeBookDat = setupDatAccess( "SecretRecipeBook", xiv::exd::Language::en );
    m_SkyIsland2MissionDat = setupDatAccess( "SkyIsland2Mission", xiv::exd::Language::en );
    m_SkyIsland2MissionDetailDat = setupDatAccess( "SkyIsland2MissionDetail", xiv::exd::Language::en );
    m_SkyIsland2MissionTypeDat = setupDatAccess( "SkyIsland2MissionType", xiv::exd::Language::none );
    m_SkyIsland2RangeTypeDat = setupDatAccess( "SkyIsland2RangeType", xiv::exd::Language::none );
    m_SnipeTalkDat = setupDatAccess( "SnipeTalk", xiv::exd::Language::en );
    m_SnipeTalkNameDat = setupDatAccess( "SnipeTalkName", xiv::exd::Language::en );
    m_SpearfishingItemDat = setupDatAccess( "SpearfishingItem", xiv::exd::Language::en );
    m_SpearfishingNotebookDat = setupDatAccess( "SpearfishingNotebook", xiv::exd::Language::none );
    m_SpearfishingRecordPageDat = setupDatAccess( "SpearfishingRecordPage", xiv::exd::Language::none );
    m_SpecialShopDat = setupDatAccess( "SpecialShop", xiv::exd::Language::en );
    m_SpecialShopItemCategoryDat = setupDatAccess( "SpecialShopItemCategory", xiv::exd::Language::en );
    m_StainDat = setupDatAccess( "Stain", xiv::exd::Language::en );
    m_StainTransientDat = setupDatAccess( "StainTransient", xiv::exd::Language::none );
    m_StatusDat = setupDatAccess( "Status", xiv::exd::Language::en );
    m_StatusHitEffectDat = setupDatAccess( "StatusHitEffect", xiv::exd::Language::none );
    m_StatusLoopVFXDat = setupDatAccess( "StatusLoopVFX", xiv::exd::Language::none );
    m_StoryDat = setupDatAccess( "Story", xiv::exd::Language::none );
    m_SubmarineExplorationDat = setupDatAccess( "SubmarineExploration", xiv::exd::Language::en );
    m_SubmarineMapDat = setupDatAccess( "SubmarineMap", xiv::exd::Language::en );
    m_SubmarinePartDat = setupDatAccess( "SubmarinePart", xiv::exd::Language::none );
    m_SubmarineRankDat = setupDatAccess( "SubmarineRank", xiv::exd::Language::none );
    m_SwitchTalkDat = setupDatAccess( "SwitchTalk", xiv::exd::Language::none );
    m_SwitchTalkVariationDat = setupDatAccess( "SwitchTalkVariation", xiv::exd::Language::none );
    m_TerritoryTypeDat = setupDatAccess( "TerritoryType", xiv::exd::Language::none );
    m_TerritoryTypeTransientDat = setupDatAccess( "TerritoryTypeTransient", xiv::exd::Language::none );
    m_TextCommandDat = setupDatAccess( "TextCommand", xiv::exd::Language::en );
    m_TitleDat = setupDatAccess( "Title", xiv::exd::Language::en );
    m_TomestonesDat = setupDatAccess( "Tomestones", xiv::exd::Language::none );
    m_TomestonesItemDat = setupDatAccess( "TomestonesItem", xiv::exd::Language::none );
    m_TopicSelectDat = setupDatAccess( "TopicSelect", xiv::exd::Language::en );
    m_TownDat = setupDatAccess( "Town", xiv::exd::Language::en );
    m_TraitDat = setupDatAccess( "Trait", xiv::exd::Language::en );
    m_TraitRecastDat = setupDatAccess( "TraitRecast", xiv::exd::Language::none );
    m_TraitTransientDat = setupDatAccess( "TraitTransient", xiv::exd::Language::en );
    m_TransformationDat = setupDatAccess( "Transformation", xiv::exd::Language::none );
    m_TreasureDat = setupDatAccess( "Treasure", xiv::exd::Language::en );
    m_TreasureHuntRankDat = setupDatAccess( "TreasureHuntRank", xiv::exd::Language::none );
    m_TreasureModelDat = setupDatAccess( "TreasureModel", xiv::exd::Language::none );
    m_TreasureSpotDat = setupDatAccess( "TreasureSpot", xiv::exd::Language::none );
    m_TribeDat = setupDatAccess( "Tribe", xiv::exd::Language::en );
    m_TripleTriadDat = setupDatAccess( "TripleTriad", xiv::exd::Language::none );
    m_TripleTriadCardDat = setupDatAccess( "TripleTriadCard", xiv::exd::Language::en );
    m_TripleTriadCardRarityDat = setupDatAccess( "TripleTriadCardRarity", xiv::exd::Language::none );
    m_TripleTriadCardResidentDat = setupDatAccess( "TripleTriadCardResident", xiv::exd::Language::none );
    m_TripleTriadCardTypeDat = setupDatAccess( "TripleTriadCardType", xiv::exd::Language::en );
    m_TripleTriadCompetitionDat = setupDatAccess( "TripleTriadCompetition", xiv::exd::Language::en );
    m_TripleTriadRuleDat = setupDatAccess( "TripleTriadRule", xiv::exd::Language::en );
    m_TutorialDat = setupDatAccess( "Tutorial", xiv::exd::Language::none );
    m_TutorialDPSDat = setupDatAccess( "TutorialDPS", xiv::exd::Language::none );
    m_TutorialHealerDat = setupDatAccess( "TutorialHealer", xiv::exd::Language::none );
    m_TutorialTankDat = setupDatAccess( "TutorialTank", xiv::exd::Language::none );
    m_UIColorDat = setupDatAccess( "UIColor", xiv::exd::Language::none );
    m_VaseFlowerDat = setupDatAccess( "VaseFlower", xiv::exd::Language::none );
    m_VFXDat = setupDatAccess( "VFX", xiv::exd::Language::none );
    m_WarpDat = setupDatAccess( "Warp", xiv::exd::Language::en );
    m_WarpConditionDat = setupDatAccess( "WarpCondition", xiv::exd::Language::none );
    m_WarpLogicDat = setupDatAccess( "WarpLogic", xiv::exd::Language::en );
    m_WeaponTimelineDat = setupDatAccess( "WeaponTimeline", xiv::exd::Language::none );
    m_WeatherDat = setupDatAccess( "Weather", xiv::exd::Language::en );
    m_WeatherGroupDat = setupDatAccess( "WeatherGroup", xiv::exd::Language::none );
    m_WeatherRateDat = setupDatAccess( "WeatherRate", xiv::exd::Language::none );
    m_WeatherReportReplaceDat = setupDatAccess( "WeatherReportReplace", xiv::exd::Language::none );
    m_WebGuidanceDat = setupDatAccess( "WebGuidance", xiv::exd::Language::en );
    m_WebURLDat = setupDatAccess( "WebURL", xiv::exd::Language::en );
    m_WeddingBGMDat = setupDatAccess( "WeddingBGM", xiv::exd::Language::en );
    m_WeeklyBingoOrderDataDat = setupDatAccess( "WeeklyBingoOrderData", xiv::exd::Language::none );
    m_WeeklyBingoRewardDataDat = setupDatAccess( "WeeklyBingoRewardData", xiv::exd::Language::none );
    m_WeeklyBingoTextDat = setupDatAccess( "WeeklyBingoText", xiv::exd::Language::en );
    m_WeeklyLotBonusDat = setupDatAccess( "WeeklyLotBonus", xiv::exd::Language::none );
    m_WorldDat = setupDatAccess( "World", xiv::exd::Language::none );
    m_WorldDCGroupTypeDat = setupDatAccess( "WorldDCGroupType", xiv::exd::Language::none );
    m_YardCatalogCategoryDat = setupDatAccess( "YardCatalogCategory", xiv::exd::Language::en );
    m_YardCatalogItemListDat = setupDatAccess( "YardCatalogItemList", xiv::exd::Language::none );
    m_YKWDat = setupDatAccess( "YKW", xiv::exd::Language::en );
    m_ZoneSharedGroupDat = setupDatAccess( "ZoneSharedGroup", xiv::exd::Language::none );

  }
  catch( std::runtime_error )
  {
    return false;
  }

  return true;
}

///////////////////////////////////////////////////////////////
// DIRECT GETTERS




