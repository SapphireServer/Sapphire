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
   initialHide = exdData->getField< bool >( row, 20 );
}

Sapphire::Data::AchievementCategory::AchievementCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_AchievementCategoryDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   achievementKind = exdData->getField< uint8_t >( row, 1 );
   hideCategory = exdData->getField< bool >( row, 3 );
}

Sapphire::Data::AchievementKind::AchievementKind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_AchievementKindDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
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
   costType = exdData->getField< uint8_t >( row, 31 );
   cost = exdData->getField< uint16_t >( row, 32 );
   actionCombo = exdData->getField< uint16_t >( row, 35 );
   preservesCombo = exdData->getField< bool >( row, 36 );
   cast100ms = exdData->getField< uint16_t >( row, 37 );
   recast100ms = exdData->getField< uint16_t >( row, 38 );
   cooldownGroup = exdData->getField< uint8_t >( row, 39 );
   attackType = exdData->getField< int8_t >( row, 40 );
   aspect = exdData->getField< uint8_t >( row, 41 );
   actionProcStatus = exdData->getField< uint8_t >( row, 42 );
   statusGainSelf = exdData->getField< uint16_t >( row, 43 );
   unlockLink = exdData->getField< uint32_t >( row, 44 );
   classJobCategory = exdData->getField< uint8_t >( row, 45 );
   affectsPosition = exdData->getField< bool >( row, 48 );
   omen = exdData->getField< uint8_t >( row, 49 );
   isPvP = exdData->getField< bool >( row, 50 );
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
   key = exdData->getField< std::string >( row, 6 );
}

Sapphire::Data::ActionTimelineMove::ActionTimelineMove( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ActionTimelineMoveDat.get_row( row_id );
}

Sapphire::Data::ActionTimelineReplace::ActionTimelineReplace( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ActionTimelineReplaceDat.get_row( row_id );
   old = exdData->getField< uint16_t >( row, 0 );
   New = exdData->getField< uint16_t >( row, 1 );
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

Sapphire::Data::AddonHud::AddonHud( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_AddonHudDat.get_row( row_id );
   _long = exdData->getField< std::string >( row, 0 );
   _short = exdData->getField< std::string >( row, 1 );
   _function = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::Adventure::Adventure( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_AdventureDat.get_row( row_id );
   level = exdData->getField< int32_t >( row, 0 );
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
   aethernetGroup = exdData->getField< uint8_t >( row, 16 );
   requiredQuest = exdData->getField< uint32_t >( row, 18 );
   map = exdData->getField< uint16_t >( row, 19 );
   aetherstreamX = exdData->getField< int16_t >( row, 20 );
   aetherstreamY = exdData->getField< int16_t >( row, 21 );
}

Sapphire::Data::AetheryteSystemDefine::AetheryteSystemDefine( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_AetheryteSystemDefineDat.get_row( row_id );
   text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::AirshipExplorationLevel::AirshipExplorationLevel( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_AirshipExplorationLevelDat.get_row( row_id );
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
   rank = exdData->getField< uint8_t >( row, 1 );
   components = exdData->getField< uint8_t >( row, 2 );
   surveillance = exdData->getField< int16_t >( row, 3 );
   retrieval = exdData->getField< int16_t >( row, 4 );
   speed = exdData->getField< int16_t >( row, 5 );
   range = exdData->getField< int16_t >( row, 6 );
   favor = exdData->getField< int16_t >( row, 7 );
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

Sapphire::Data::Balloon::Balloon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BalloonDat.get_row( row_id );
   dialogue = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::BaseParam::BaseParam( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BaseParamDat.get_row( row_id );
   order = exdData->getField< int8_t >( row, 0 );
   name = exdData->getField< std::string >( row, 1 );
   description = exdData->getField< std::string >( row, 2 );
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
   chestHead = exdData->getField< uint8_t >( row, 18 );
   chestHeadLegsFeet = exdData->getField< uint8_t >( row, 19 );
   legsFeet = exdData->getField< uint8_t >( row, 21 );
   headChestHandsLegsFeet = exdData->getField< uint8_t >( row, 22 );
   chestLegsGloves = exdData->getField< uint8_t >( row, 23 );
   chestLegsFeet = exdData->getField< uint8_t >( row, 24 );
}

Sapphire::Data::BattleLeve::BattleLeve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BattleLeveDat.get_row( row_id );
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
}

Sapphire::Data::BeastRankBonus::BeastRankBonus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BeastRankBonusDat.get_row( row_id );
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
}

Sapphire::Data::BeastTribe::BeastTribe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BeastTribeDat.get_row( row_id );
   minLevel = exdData->getField< uint8_t >( row, 0 );
   maxLevel = exdData->getField< uint8_t >( row, 1 );
   beastRankBonus = exdData->getField< uint8_t >( row, 2 );
   iconReputation = exdData->getField< uint32_t >( row, 3 );
   icon = exdData->getField< uint32_t >( row, 4 );
   maxRank = exdData->getField< uint8_t >( row, 5 );
   alliedBeastTribeQuest = exdData->getField< uint32_t >( row, 6 );
   expansion = exdData->getField< uint8_t >( row, 7 );
   currencyItem = exdData->getField< uint32_t >( row, 8 );
   displayOrder = exdData->getField< uint8_t >( row, 9 );
   name = exdData->getField< std::string >( row, 10 );
   nameRelation = exdData->getField< std::string >( row, 18 );
}

Sapphire::Data::Behavior::Behavior( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BehaviorDat.get_row( row_id, subRow );
   balloon = exdData->getField< uint16_t >( row, 6 );
}

Sapphire::Data::BGM::BGM( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BGMDat.get_row( row_id );
   file = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::BGMFade::BGMFade( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BGMFadeDat.get_row( row_id );
   bGMFadeType = exdData->getField< int32_t >( row, 2 );
}

Sapphire::Data::BGMSituation::BGMSituation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BGMSituationDat.get_row( row_id );
   bGMDay = exdData->getField< uint16_t >( row, 0 );
   bGMNight = exdData->getField< uint16_t >( row, 1 );
   bGMBattle = exdData->getField< uint16_t >( row, 2 );
   bGMField = exdData->getField< uint16_t >( row, 3 );
}

Sapphire::Data::BGMSwitch::BGMSwitch( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BGMSwitchDat.get_row( row_id, subRow );
   bGMSystemDefine = exdData->getField< uint8_t >( row, 0 );
   quest = exdData->getField< uint32_t >( row, 1 );
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
   actionTimelineMove = exdData->getField< uint8_t >( row, 1 );
   scale = exdData->getField< float >( row, 4 );
   modelChara = exdData->getField< uint16_t >( row, 5 );
   bNpcCustomize = exdData->getField< uint16_t >( row, 6 );
   npcEquip = exdData->getField< uint16_t >( row, 7 );
   arrayEventHandler = exdData->getField< int32_t >( row, 11 );
   bNpcParts = exdData->getField< uint8_t >( row, 12 );
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

Sapphire::Data::Buddy::Buddy( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BuddyDat.get_row( row_id );
   questRequirement2 = exdData->getField< int32_t >( row, 1 );
   questRequirement1 = exdData->getField< int32_t >( row, 2 );
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
}

Sapphire::Data::BuddyItem::BuddyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_BuddyItemDat.get_row( row_id );
   item = exdData->getField< uint16_t >( row, 0 );
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

Sapphire::Data::CharaMakeCustomize::CharaMakeCustomize( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CharaMakeCustomizeDat.get_row( row_id );
   icon = exdData->getField< uint32_t >( row, 1 );
   data = exdData->getField< uint16_t >( row, 2 );
   isPurchasable = exdData->getField< bool >( row, 3 );
}

Sapphire::Data::CharaMakeType::CharaMakeType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CharaMakeTypeDat.get_row( row_id );
   race = exdData->getField< int32_t >( row, 0 );
   tribe = exdData->getField< int32_t >( row, 1 );
   gender = exdData->getField< int8_t >( row, 2 );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3291 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3292 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3293 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3294 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3295 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3296 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3297 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3298 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3299 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3300 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3301 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3302 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3303 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3304 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3305 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3306 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3307 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3308 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3309 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3310 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3311 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3312 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3313 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3314 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3315 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3316 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3317 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3318 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3319 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3320 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3321 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3322 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3323 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3324 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3325 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3326 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3327 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3328 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3329 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3330 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3331 ) );
   facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 3332 ) );
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
}

Sapphire::Data::ChocoboTaxiStand::ChocoboTaxiStand( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ChocoboTaxiStandDat.get_row( row_id );
   placeName = exdData->getField< std::string >( row, 8 );
}

Sapphire::Data::ClassJob::ClassJob( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ClassJobDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   abbreviation = exdData->getField< std::string >( row, 1 );
   classJobCategory = exdData->getField< uint8_t >( row, 3 );
   expArrayIndex = exdData->getField< int8_t >( row, 4 );
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
   limitBreak1 = exdData->getField< uint16_t >( row, 34 );
   limitBreak2 = exdData->getField< uint16_t >( row, 35 );
   limitBreak3 = exdData->getField< uint16_t >( row, 36 );
   itemSoulCrystal = exdData->getField< uint32_t >( row, 38 );
   unlockQuest = exdData->getField< uint32_t >( row, 39 );
   relicQuest = exdData->getField< uint32_t >( row, 40 );
   prerequisite = exdData->getField< uint32_t >( row, 41 );
   startingLevel = exdData->getField< uint8_t >( row, 42 );
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
   behavior = exdData->getField< uint8_t >( row, 14 );
   icon = exdData->getField< uint16_t >( row, 26 );
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
   territoryType = exdData->getField< uint16_t >( row, 1 );
   contentLinkType = exdData->getField< uint8_t >( row, 2 );
   content = exdData->getField< uint16_t >( row, 3 );
   contentMemberType = exdData->getField< uint8_t >( row, 9 );
   classJobLevelRequired = exdData->getField< uint8_t >( row, 15 );
   classJobLevelSync = exdData->getField< uint8_t >( row, 16 );
   itemLevelRequired = exdData->getField< uint16_t >( row, 17 );
   itemLevelSync = exdData->getField< uint16_t >( row, 18 );
   allowReplacement = exdData->getField< bool >( row, 20 );
   highEndDuty = exdData->getField< bool >( row, 26 );
   dutyRecorderAllowed = exdData->getField< bool >( row, 30 );
   name = exdData->getField< std::string >( row, 34 );
   contentType = exdData->getField< uint8_t >( row, 35 );
   transient = exdData->getField< uint8_t >( row, 36 );
   image = exdData->getField< uint32_t >( row, 39 );
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
}

Sapphire::Data::ContentNpcTalk::ContentNpcTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ContentNpcTalkDat.get_row( row_id );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 1 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 2 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 3 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 4 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 5 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 6 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 7 ) );
   contentTalk.push_back( exdData->getField< uint32_t >( row, 8 ) );
}

Sapphire::Data::ContentRoulette::ContentRoulette( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ContentRouletteDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   description = exdData->getField< std::string >( row, 2 );
   dutyType = exdData->getField< std::string >( row, 3 );
   isInDutyFinder = exdData->getField< bool >( row, 6 );
   openRule = exdData->getField< uint8_t >( row, 7 );
   requiredLevel = exdData->getField< uint8_t >( row, 9 );
   itemLevelRequired = exdData->getField< uint16_t >( row, 11 );
   icon = exdData->getField< uint32_t >( row, 13 );
   contentRouletteRoleBonus = exdData->getField< uint8_t >( row, 14 );
   rewardTomeA = exdData->getField< uint16_t >( row, 15 );
   rewardTomeB = exdData->getField< uint16_t >( row, 16 );
   rewardTomeC = exdData->getField< uint16_t >( row, 17 );
   sortKey = exdData->getField< uint8_t >( row, 20 );
   contentMemberType = exdData->getField< uint8_t >( row, 22 );
   requireAllDuties = exdData->getField< bool >( row, 32 );
   contentRouletteOpenRule = exdData->getField< uint8_t >( row, 34 );
   instanceContent = exdData->getField< uint16_t >( row, 35 );
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
   menuOrder = exdData->getField< uint8_t >( row, 2 );
   requiredAmount = exdData->getField< int32_t >( row, 3 );
   expMultiplier = exdData->getField< int32_t >( row, 5 );
   gilRward = exdData->getField< int32_t >( row, 7 );
   levelUnlock = exdData->getField< uint16_t >( row, 8 );
   howTo = exdData->getField< uint16_t >( row, 9 );
   name = exdData->getField< std::string >( row, 11 );
   description = exdData->getField< std::string >( row, 12 );
   expCap = exdData->getField< int32_t >( row, 13 );
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

Sapphire::Data::CraftType::CraftType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CraftTypeDat.get_row( row_id );
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

Sapphire::Data::CreditCast::CreditCast( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CreditCastDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Currency::Currency( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CurrencyDat.get_row( row_id );
   item = exdData->getField< uint32_t >( row, 0 );
   limit = exdData->getField< uint32_t >( row, 3 );
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
}

Sapphire::Data::Cutscene::Cutscene( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CutsceneDat.get_row( row_id );
   path = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::CutScreenImage::CutScreenImage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_CutScreenImageDat.get_row( row_id );
   image = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::DailySupplyItem::DailySupplyItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_DailySupplyItemDat.get_row( row_id );
}

Sapphire::Data::DeepDungeon::DeepDungeon( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_DeepDungeonDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 22 );
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

Sapphire::Data::ENpcBase::ENpcBase( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ENpcBaseDat.get_row( row_id );
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
   balloon = exdData->getField< uint16_t >( row, 91 );
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
   data = exdData->getField< uint32_t >( row, 9 );
   sgbPath = exdData->getField< uint16_t >( row, 11 );
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
   male = exdData->getField< bool >( row, 6 );
   female = exdData->getField< bool >( row, 7 );
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

Sapphire::Data::ExportedSG::ExportedSG( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ExportedSGDat.get_row( row_id );
   sgbPath = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::ExVersion::ExVersion( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ExVersionDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Fate::Fate( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_FateDat.get_row( row_id );
   eurekaFate = exdData->getField< uint8_t >( row, 0 );
   location = exdData->getField< uint32_t >( row, 2 );
   classJobLevel = exdData->getField< uint8_t >( row, 3 );
   classJobLevelMax = exdData->getField< uint8_t >( row, 4 );
   eventItem = exdData->getField< uint32_t >( row, 5 );
   iconObjective = exdData->getField< uint32_t >( row, 10 );
   iconMap = exdData->getField< uint32_t >( row, 11 );
   music = exdData->getField< int32_t >( row, 13 );
   hasWorldMapIcon = exdData->getField< bool >( row, 19 );
   name = exdData->getField< std::string >( row, 27 );
   description = exdData->getField< std::string >( row, 28 );
   objective = exdData->getField< std::string >( row, 29 );
   statusText.push_back( exdData->getField< std::string >( row, 30 ) );
   statusText.push_back( exdData->getField< std::string >( row, 31 ) );
   statusText.push_back( exdData->getField< std::string >( row, 32 ) );
   arrayIndex = exdData->getField< uint32_t >( row, 33 );
}

Sapphire::Data::FCActivity::FCActivity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_FCActivityDat.get_row( row_id );
   text = exdData->getField< std::string >( row, 0 );
   fCActivityCategory = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::FCActivityCategory::FCActivityCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_FCActivityCategoryDat.get_row( row_id );
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
   name = exdData->getField< std::string >( row, 1 );
}

Sapphire::Data::FCReputation::FCReputation( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_FCReputationDat.get_row( row_id );
   pointsToNext = exdData->getField< uint32_t >( row, 0 );
   requiredPoints = exdData->getField< uint32_t >( row, 1 );
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
   territoryType = exdData->getField< uint16_t >( row, 5 );
   x = exdData->getField< int16_t >( row, 6 );
   z = exdData->getField< int16_t >( row, 7 );
   radius = exdData->getField< uint16_t >( row, 8 );
   item.push_back( exdData->getField< int32_t >( row, 10 ) );
   item.push_back( exdData->getField< int32_t >( row, 11 ) );
   item.push_back( exdData->getField< int32_t >( row, 12 ) );
   item.push_back( exdData->getField< int32_t >( row, 13 ) );
   item.push_back( exdData->getField< int32_t >( row, 14 ) );
   item.push_back( exdData->getField< int32_t >( row, 15 ) );
   item.push_back( exdData->getField< int32_t >( row, 16 ) );
   item.push_back( exdData->getField< int32_t >( row, 17 ) );
   item.push_back( exdData->getField< int32_t >( row, 18 ) );
   item.push_back( exdData->getField< int32_t >( row, 19 ) );
   placeName = exdData->getField< uint16_t >( row, 20 );
}

Sapphire::Data::FishParameter::FishParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_FishParameterDat.get_row( row_id );
   text = exdData->getField< std::string >( row, 0 );
   item = exdData->getField< int32_t >( row, 1 );
   gatheringItemLevel = exdData->getField< uint16_t >( row, 2 );
   isHidden = exdData->getField< bool >( row, 3 );
   fishingRecordType = exdData->getField< uint8_t >( row, 5 );
   territoryType = exdData->getField< int32_t >( row, 6 );
   isInLog = exdData->getField< bool >( row, 7 );
   timeRestricted = exdData->getField< bool >( row, 8 );
   weatherRestricted = exdData->getField< bool >( row, 9 );
   gatheringSubCategory = exdData->getField< uint16_t >( row, 10 );
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

Sapphire::Data::GardeningSeed::GardeningSeed( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GardeningSeedDat.get_row( row_id );
   item = exdData->getField< uint32_t >( row, 0 );
   icon = exdData->getField< uint32_t >( row, 2 );
}

Sapphire::Data::GatheringCondition::GatheringCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GatheringConditionDat.get_row( row_id );
   text = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::GatheringExp::GatheringExp( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GatheringExpDat.get_row( row_id );
   exp = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::GatheringItem::GatheringItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GatheringItemDat.get_row( row_id );
   item = exdData->getField< int32_t >( row, 0 );
   gatheringItemLevel = exdData->getField< uint16_t >( row, 1 );
   isHidden = exdData->getField< bool >( row, 2 );
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
   requiredItem1 = exdData->getField< int32_t >( row, 4 );
   leveLevel = exdData->getField< uint8_t >( row, 5 );
   requiredItem2 = exdData->getField< int32_t >( row, 6 );
}

Sapphire::Data::GatheringLeveRoute::GatheringLeveRoute( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GatheringLeveRouteDat.get_row( row_id );
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
   gatheringPointBase = exdData->getField< int32_t >( row, 1 );
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
   conditionValue = exdData->getField< uint16_t >( row, 1 );
   bonusType = exdData->getField< uint8_t >( row, 3 );
   bonusValue = exdData->getField< uint16_t >( row, 4 );
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

Sapphire::Data::GatheringSubCategory::GatheringSubCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GatheringSubCategoryDat.get_row( row_id );
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

Sapphire::Data::GilShop::GilShop( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GilShopDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   icon = exdData->getField< uint32_t >( row, 1 );
   questRequired.push_back( exdData->getField< uint32_t >( row, 2 ) );
   questRequired.push_back( exdData->getField< uint32_t >( row, 3 ) );
   questRequired.push_back( exdData->getField< uint32_t >( row, 4 ) );
   questRequired.push_back( exdData->getField< uint32_t >( row, 5 ) );
   acceptTalk = exdData->getField< int32_t >( row, 6 );
   failTalk = exdData->getField< int32_t >( row, 7 );
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

Sapphire::Data::GuardianDeity::GuardianDeity( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GuardianDeityDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   description = exdData->getField< std::string >( row, 1 );
   icon = exdData->getField< uint16_t >( row, 2 );
}

Sapphire::Data::GuildleveAssignment::GuildleveAssignment( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_GuildleveAssignmentDat.get_row( row_id );
   assignmentTalk = exdData->getField< uint32_t >( row, 1 );
   quest.push_back( exdData->getField< uint32_t >( row, 2 ) );
   quest.push_back( exdData->getField< uint32_t >( row, 3 ) );
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
   housingLayoutLimit = exdData->getField< uint8_t >( row, 4 );
   aquariumTier = exdData->getField< uint8_t >( row, 5 );
   customTalk = exdData->getField< uint32_t >( row, 6 );
   item = exdData->getField< uint32_t >( row, 7 );
   destroyOnRemoval = exdData->getField< bool >( row, 8 );
   tooltip = exdData->getField< bool >( row, 9 );
}

Sapphire::Data::HousingMapMarkerInfo::HousingMapMarkerInfo( uint32_t row_id, uint32_t subRow, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_HousingMapMarkerInfoDat.get_row( row_id, subRow );
   x = exdData->getField< float >( row, 0 );
   y = exdData->getField< float >( row, 1 );
   z = exdData->getField< float >( row, 2 );
   plotNumberDistance = exdData->getField< float >( row, 3 );
   map = exdData->getField< uint16_t >( row, 4 );
}

Sapphire::Data::HousingMerchantPose::HousingMerchantPose( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_HousingMerchantPoseDat.get_row( row_id );
   actionTimeline = exdData->getField< uint16_t >( row, 0 );
   pose = exdData->getField< std::string >( row, 1 );
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
   for ( int i = 60; i < 60 + 60; i++ )
     minPrice.push_back( exdData->getField< uint32_t >( row, i ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 300 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 301 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 302 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 303 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 304 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 305 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 306 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 307 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 308 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 309 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 310 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 311 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 312 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 313 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 314 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 315 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 316 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 317 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 318 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 319 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 320 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 321 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 322 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 323 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 324 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 325 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 326 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 327 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 328 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 329 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 330 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 331 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 332 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 333 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 334 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 335 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 336 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 337 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 338 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 339 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 340 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 341 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 342 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 343 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 344 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 345 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 346 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 347 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 348 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 349 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 350 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 351 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 352 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 353 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 354 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 355 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 356 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 357 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 358 ) );
   initialPrice.push_back( exdData->getField< uint32_t >( row, 359 ) );
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
   housingLayoutLimit = exdData->getField< uint8_t >( row, 4 );
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

Sapphire::Data::InstanceContent::InstanceContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_InstanceContentDat.get_row( row_id );
   instanceContentType = exdData->getField< uint8_t >( row, 0 );
   weekRestriction = exdData->getField< uint8_t >( row, 1 );
   timeLimitmin = exdData->getField< uint16_t >( row, 2 );
   name = exdData->getField< std::string >( row, 3 );
   bGM = exdData->getField< uint16_t >( row, 5 );
   winBGM = exdData->getField< uint16_t >( row, 6 );
   cutscene = exdData->getField< uint32_t >( row, 7 );
   order = exdData->getField< uint16_t >( row, 9 );
   instanceContentTextDataBossStart = exdData->getField< uint32_t >( row, 12 );
   instanceContentTextDataBossEnd = exdData->getField< uint32_t >( row, 13 );
   bNpcBaseBoss = exdData->getField< uint32_t >( row, 14 );
   instanceContentTextDataObjectiveStart = exdData->getField< uint32_t >( row, 15 );
   instanceContentTextDataObjectiveEnd = exdData->getField< uint32_t >( row, 16 );
   sortKey = exdData->getField< uint16_t >( row, 17 );
   newPlayerBonusA = exdData->getField< uint16_t >( row, 20 );
   newPlayerBonusB = exdData->getField< uint16_t >( row, 21 );
   finalBossExp = exdData->getField< uint32_t >( row, 22 );
   finalBossCurrencyA = exdData->getField< uint16_t >( row, 23 );
   finalBossCurrencyB = exdData->getField< uint16_t >( row, 24 );
   finalBossCurrencyC = exdData->getField< uint16_t >( row, 25 );
   instanceClearExp = exdData->getField< uint32_t >( row, 46 );
   instanceContentBuff = exdData->getField< int32_t >( row, 51 );
   reqInstance = exdData->getField< uint32_t >( row, 52 );
   partyCondition = exdData->getField< uint8_t >( row, 54 );
}

Sapphire::Data::InstanceContentBuff::InstanceContentBuff( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_InstanceContentBuffDat.get_row( row_id );
   echoStart = exdData->getField< uint16_t >( row, 0 );
   echoDeath = exdData->getField< uint16_t >( row, 1 );
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
   stackSize = exdData->getField< uint32_t >( row, 19 );
   isUnique = exdData->getField< bool >( row, 20 );
   isUntradable = exdData->getField< bool >( row, 21 );
   isIndisposable = exdData->getField< bool >( row, 22 );
   isEquippable = exdData->getField< bool >( row, 23 );
   priceMid = exdData->getField< uint32_t >( row, 24 );
   priceLow = exdData->getField< uint32_t >( row, 25 );
   canBeHq = exdData->getField< bool >( row, 26 );
   isDyeable = exdData->getField< bool >( row, 27 );
   isCrestWorthy = exdData->getField< bool >( row, 28 );
   itemAction = exdData->getField< uint16_t >( row, 29 );
   cooldowns = exdData->getField< uint16_t >( row, 31 );
   classJobRepair = exdData->getField< uint8_t >( row, 32 );
   itemRepair = exdData->getField< int32_t >( row, 33 );
   itemGlamour = exdData->getField< int32_t >( row, 34 );
   salvage = exdData->getField< uint16_t >( row, 35 );
   isCollectable = exdData->getField< bool >( row, 36 );
   aetherialReduce = exdData->getField< uint16_t >( row, 37 );
   levelEquip = exdData->getField< uint8_t >( row, 38 );
   equipRestriction = exdData->getField< uint8_t >( row, 40 );
   classJobCategory = exdData->getField< uint8_t >( row, 41 );
   grandCompany = exdData->getField< uint8_t >( row, 42 );
   itemSeries = exdData->getField< uint8_t >( row, 43 );
   baseParamModifier = exdData->getField< uint8_t >( row, 44 );
   modelMain = exdData->getField< uint64_t >( row, 45 );
   modelSub = exdData->getField< uint64_t >( row, 46 );
   classJobUse = exdData->getField< uint8_t >( row, 47 );
   damagePhys = exdData->getField< uint16_t >( row, 49 );
   damageMag = exdData->getField< uint16_t >( row, 50 );
   delayms = exdData->getField< uint16_t >( row, 51 );
   blockRate = exdData->getField< uint16_t >( row, 53 );
   block = exdData->getField< uint16_t >( row, 54 );
   defensePhys = exdData->getField< uint16_t >( row, 55 );
   defenseMag = exdData->getField< uint16_t >( row, 56 );
   itemSpecialBonus = exdData->getField< uint8_t >( row, 69 );
   itemSpecialBonusParam = exdData->getField< uint8_t >( row, 70 );
   materializeType = exdData->getField< uint8_t >( row, 83 );
   materiaSlotCount = exdData->getField< uint8_t >( row, 84 );
   isAdvancedMeldingPermitted = exdData->getField< bool >( row, 85 );
   isPvP = exdData->getField< bool >( row, 86 );
   isGlamourous = exdData->getField< bool >( row, 88 );
}

Sapphire::Data::ItemAction::ItemAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ItemActionDat.get_row( row_id );
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

Sapphire::Data::ItemFood::ItemFood( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ItemFoodDat.get_row( row_id );
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

Sapphire::Data::JournalCategory::JournalCategory( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_JournalCategoryDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   journalSection = exdData->getField< uint8_t >( row, 3 );
}

Sapphire::Data::JournalGenre::JournalGenre( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_JournalGenreDat.get_row( row_id );
   icon = exdData->getField< int32_t >( row, 0 );
   journalCategory = exdData->getField< uint8_t >( row, 1 );
   name = exdData->getField< std::string >( row, 2 );
}

Sapphire::Data::JournalSection::JournalSection( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_JournalSectionDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::Leve::Leve( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_LeveDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   description = exdData->getField< std::string >( row, 1 );
   leveClient = exdData->getField< int32_t >( row, 2 );
   leveAssignmentType = exdData->getField< int32_t >( row, 3 );
   classJobLevel = exdData->getField< uint16_t >( row, 5 );
   allowanceCost = exdData->getField< uint8_t >( row, 7 );
   placeNameStart = exdData->getField< int32_t >( row, 9 );
   placeNameIssued = exdData->getField< int32_t >( row, 10 );
   classJobCategory = exdData->getField< uint8_t >( row, 12 );
   journalGenre = exdData->getField< int32_t >( row, 13 );
   placeNameStartZone = exdData->getField< int32_t >( row, 15 );
   iconCityState = exdData->getField< int32_t >( row, 16 );
   dataId = exdData->getField< int32_t >( row, 17 );
   expReward = exdData->getField< uint32_t >( row, 21 );
   gilReward = exdData->getField< uint32_t >( row, 22 );
   leveRewardItem = exdData->getField< uint16_t >( row, 23 );
   leveVfx = exdData->getField< uint8_t >( row, 24 );
   leveVfxFrame = exdData->getField< uint8_t >( row, 25 );
   levelLevemete = exdData->getField< uint32_t >( row, 26 );
   iconIssuer = exdData->getField< int32_t >( row, 27 );
   levelStart = exdData->getField< uint32_t >( row, 29 );
   bGM = exdData->getField< uint16_t >( row, 30 );
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

Sapphire::Data::LeveVfx::LeveVfx( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_LeveVfxDat.get_row( row_id );
   effect = exdData->getField< std::string >( row, 0 );
   icon = exdData->getField< int32_t >( row, 1 );
}

Sapphire::Data::LogFilter::LogFilter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_LogFilterDat.get_row( row_id );
   logKind = exdData->getField< uint8_t >( row, 0 );
   name = exdData->getField< std::string >( row, 6 );
   example = exdData->getField< std::string >( row, 7 );
}

Sapphire::Data::LogKind::LogKind( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_LogKindDat.get_row( row_id );
   format = exdData->getField< std::string >( row, 1 );
   name = exdData->getField< std::string >( row, 2 );
   example = exdData->getField< std::string >( row, 3 );
   logKindCategoryText = exdData->getField< uint8_t >( row, 4 );
}

Sapphire::Data::LogKindCategoryText::LogKindCategoryText( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_LogKindCategoryTextDat.get_row( row_id );
   text = exdData->getField< std::string >( row, 0 );
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
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 17 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 18 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 19 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 20 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 21 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 22 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 23 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 24 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 25 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 26 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 27 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 28 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 29 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 30 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 31 ) );
   amountAccepted.push_back( exdData->getField< uint32_t >( row, 32 ) );
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
   mainCommandCategory = exdData->getField< uint8_t >( row, 2 );
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
   hierarchy = exdData->getField< uint8_t >( row, 3 );
   mapMarkerRange = exdData->getField< uint16_t >( row, 4 );
   id = exdData->getField< std::string >( row, 5 );
   sizeFactor = exdData->getField< uint16_t >( row, 6 );
   offsetX = exdData->getField< int16_t >( row, 7 );
   offsetY = exdData->getField< int16_t >( row, 8 );
   placeNameRegion = exdData->getField< uint16_t >( row, 9 );
   placeName = exdData->getField< uint16_t >( row, 10 );
   placeNameSub = exdData->getField< uint16_t >( row, 11 );
   discoveryIndex = exdData->getField< int16_t >( row, 12 );
   territoryType = exdData->getField< uint16_t >( row, 14 );
   discoveryArrayByte = exdData->getField< bool >( row, 15 );
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
   x = exdData->getField< int16_t >( row, 0 );
}

Sapphire::Data::MapSymbol::MapSymbol( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_MapSymbolDat.get_row( row_id );
   icon = exdData->getField< int32_t >( row, 0 );
   placeName = exdData->getField< int32_t >( row, 1 );
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
   value.push_back( exdData->getField< uint8_t >( row, 11 ) );
   value.push_back( exdData->getField< uint8_t >( row, 12 ) );
   value.push_back( exdData->getField< uint8_t >( row, 13 ) );
   value.push_back( exdData->getField< uint8_t >( row, 14 ) );
   value.push_back( exdData->getField< uint8_t >( row, 15 ) );
   value.push_back( exdData->getField< uint8_t >( row, 16 ) );
   value.push_back( exdData->getField< uint8_t >( row, 17 ) );
   value.push_back( exdData->getField< uint8_t >( row, 18 ) );
   value.push_back( exdData->getField< uint8_t >( row, 19 ) );
   value.push_back( exdData->getField< uint8_t >( row, 20 ) );
}

Sapphire::Data::MiniGameRA::MiniGameRA( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_MiniGameRADat.get_row( row_id );
   icon = exdData->getField< int32_t >( row, 1 );
   bGM = exdData->getField< int32_t >( row, 2 );
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

Sapphire::Data::MobHuntOrderType::MobHuntOrderType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_MobHuntOrderTypeDat.get_row( row_id );
   quest = exdData->getField< uint32_t >( row, 1 );
   eventItem = exdData->getField< uint32_t >( row, 2 );
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
}

Sapphire::Data::ModelState::ModelState( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ModelStateDat.get_row( row_id );
   start = exdData->getField< uint16_t >( row, 0 );
   end = exdData->getField< uint16_t >( row, 1 );
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
   order = exdData->getField< int16_t >( row, 29 );
   icon = exdData->getField< uint16_t >( row, 30 );
   extraSeats = exdData->getField< uint8_t >( row, 36 );
   mountAction = exdData->getField< uint16_t >( row, 37 );
   isAirborne = exdData->getField< bool >( row, 38 );
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
   hyurMaleScale = exdData->getField< float >( row, 1 );
   hyurFemaleScale = exdData->getField< float >( row, 2 );
   elezenMaleScale = exdData->getField< float >( row, 3 );
   elezenFemaleScale = exdData->getField< float >( row, 4 );
   lalaMaleScale = exdData->getField< float >( row, 5 );
   lalaFemaleScale = exdData->getField< float >( row, 6 );
   miqoMaleScale = exdData->getField< float >( row, 7 );
   miqoFemaleScale = exdData->getField< float >( row, 8 );
   roeMaleScale = exdData->getField< float >( row, 9 );
   roeFemaleScale = exdData->getField< float >( row, 10 );
   auRaMaleScale = exdData->getField< float >( row, 11 );
   auRaFemaleScale = exdData->getField< float >( row, 12 );
   hyurMaleCameraHeight = exdData->getField< uint8_t >( row, 13 );
   hyurFemaleCameraHeight = exdData->getField< uint8_t >( row, 14 );
   elezenMaleCameraHeight = exdData->getField< uint8_t >( row, 15 );
   elezenFemaleCameraHeight = exdData->getField< uint8_t >( row, 16 );
   lalaMaleCameraHeight = exdData->getField< uint8_t >( row, 17 );
   lalaFemaleCameraHeight = exdData->getField< uint8_t >( row, 18 );
   miqoMaleCameraHeight = exdData->getField< uint8_t >( row, 19 );
   miqoFemaleCameraHeight = exdData->getField< uint8_t >( row, 20 );
   roeMaleCameraHeight = exdData->getField< uint8_t >( row, 21 );
   roeFemaleCameraHeight = exdData->getField< uint8_t >( row, 22 );
   auRaMaleCameraHeight = exdData->getField< uint8_t >( row, 23 );
   auRaFemaleCameraHeight = exdData->getField< uint8_t >( row, 24 );
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
   text = exdData->getField< std::string >( row, 9 );
}

Sapphire::Data::Omen::Omen( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_OmenDat.get_row( row_id );
   fileName = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::OnlineStatus::OnlineStatus( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_OnlineStatusDat.get_row( row_id );
   priority = exdData->getField< uint8_t >( row, 2 );
   name = exdData->getField< std::string >( row, 3 );
   icon = exdData->getField< uint32_t >( row, 4 );
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

Sapphire::Data::ParamGrow::ParamGrow( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ParamGrowDat.get_row( row_id );
   expToNext = exdData->getField< int32_t >( row, 0 );
   additionalActions = exdData->getField< uint8_t >( row, 1 );
   mpModifier = exdData->getField< int32_t >( row, 4 );
   baseSpeed = exdData->getField< int32_t >( row, 5 );
   levelModifier = exdData->getField< int32_t >( row, 6 );
   questExpModifier = exdData->getField< uint8_t >( row, 7 );
   hpModifier = exdData->getField< uint16_t >( row, 8 );
   huntingLogExpReward = exdData->getField< int32_t >( row, 9 );
}

Sapphire::Data::PartyContent::PartyContent( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_PartyContentDat.get_row( row_id );
   key = exdData->getField< uint8_t >( row, 0 );
   timeLimit = exdData->getField< uint16_t >( row, 1 );
   name = exdData->getField< std::string >( row, 2 );
   textDataStart = exdData->getField< uint32_t >( row, 3 );
   textDataEnd = exdData->getField< uint32_t >( row, 4 );
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
}

Sapphire::Data::Picture::Picture( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_PictureDat.get_row( row_id );
   item = exdData->getField< int32_t >( row, 0 );
   image = exdData->getField< int32_t >( row, 1 );
   signature = exdData->getField< int32_t >( row, 2 );
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
   gilShop = exdData->getField< uint32_t >( row, 0 );
   actionTimeline = exdData->getField< uint16_t >( row, 2 );
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
   contentFinderCondition = exdData->getField< uint16_t >( row, 8 );
   additionalData = exdData->getField< uint16_t >( row, 9 );
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

Sapphire::Data::PvPAction::PvPAction( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_PvPActionDat.get_row( row_id );
   action = exdData->getField< uint16_t >( row, 0 );
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
   levelMax = exdData->getField< uint16_t >( row, 6 );
   classJobCategory1 = exdData->getField< uint8_t >( row, 7 );
   classJobLevel1 = exdData->getField< uint16_t >( row, 8 );
   previousQuestJoin = exdData->getField< uint8_t >( row, 9 );
   previousQuest0 = exdData->getField< uint32_t >( row, 10 );
   previousQuest1 = exdData->getField< uint32_t >( row, 12 );
   previousQuest2 = exdData->getField< uint32_t >( row, 13 );
   questLockJoin = exdData->getField< uint8_t >( row, 14 );
   questLock.push_back( exdData->getField< uint32_t >( row, 15 ) );
   questLock.push_back( exdData->getField< uint32_t >( row, 16 ) );
   classJobUnlock = exdData->getField< uint8_t >( row, 20 );
   grandCompany = exdData->getField< uint8_t >( row, 21 );
   grandCompanyRank = exdData->getField< uint8_t >( row, 22 );
   instanceContentJoin = exdData->getField< uint8_t >( row, 23 );
   instanceContent.push_back( exdData->getField< uint32_t >( row, 24 ) );
   instanceContent.push_back( exdData->getField< uint32_t >( row, 25 ) );
   instanceContent.push_back( exdData->getField< uint32_t >( row, 26 ) );
   festival = exdData->getField< uint8_t >( row, 27 );
   bellStart = exdData->getField< uint16_t >( row, 30 );
   bellEnd = exdData->getField< uint16_t >( row, 31 );
   beastTribe = exdData->getField< uint8_t >( row, 32 );
   beastReputationRank = exdData->getField< uint8_t >( row, 33 );
   mountRequired = exdData->getField< int32_t >( row, 37 );
   isHouseRequired = exdData->getField< bool >( row, 38 );
   eNpcResidentStart = exdData->getField< uint32_t >( row, 40 );
   eNpcResidentEnd = exdData->getField< uint32_t >( row, 42 );
   isRepeatable = exdData->getField< bool >( row, 43 );
   repeatIntervalType = exdData->getField< uint8_t >( row, 44 );
   questRepeatFlag = exdData->getField< uint8_t >( row, 45 );
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
   scriptArg.push_back( exdData->getField< uint32_t >( row, 149 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1222 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1223 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1224 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1225 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1226 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1227 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1228 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1229 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1230 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1231 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1232 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1233 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1234 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1235 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1236 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1237 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1238 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1239 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1240 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1241 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1242 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1243 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1244 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1245 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1246 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1247 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1248 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1249 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1250 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1251 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1252 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1253 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1254 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1255 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1256 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1257 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1258 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1259 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1260 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1261 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1262 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1263 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1264 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1265 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1266 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1267 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1268 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1269 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1270 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1271 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1272 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1273 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1274 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1275 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1276 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1277 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1278 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1279 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1280 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1281 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1282 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1283 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1284 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1285 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1286 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1287 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1288 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1289 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1290 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1291 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1292 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1293 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1294 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1295 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1296 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1297 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1298 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1299 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1300 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1301 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1302 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1303 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1304 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1305 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1306 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1307 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1308 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1309 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1310 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1311 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1312 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1313 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1314 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1315 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1316 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1317 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1318 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1319 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1320 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1321 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1322 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1323 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1324 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1325 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1326 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1327 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1328 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1329 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1330 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1331 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1332 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1333 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1334 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1335 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1336 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1337 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1338 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1339 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1340 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1341 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1342 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1343 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1344 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1345 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1346 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1347 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1348 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1349 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1350 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1351 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1352 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1353 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1354 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1355 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1356 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1357 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1358 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1359 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1360 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1361 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1362 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1363 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1364 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1365 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1366 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1367 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1368 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1369 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1370 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1371 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1372 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1373 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1374 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1375 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1376 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1377 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1378 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1379 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1380 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1381 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1382 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1383 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1384 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1385 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1386 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1387 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1388 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1389 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1390 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1391 ) );
   level.push_back( exdData->getField< uint32_t >( row, 1392 ) );
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
   otherReward = exdData->getField< uint8_t >( row, 1497 );
   instanceContentUnlock = exdData->getField< uint32_t >( row, 1500 );
   tomestoneReward = exdData->getField< uint8_t >( row, 1502 );
   tomestoneCountReward = exdData->getField< uint8_t >( row, 1503 );
   reputationReward = exdData->getField< uint8_t >( row, 1504 );
   placeName = exdData->getField< uint16_t >( row, 1505 );
   journalGenre = exdData->getField< uint8_t >( row, 1506 );
   icon = exdData->getField< uint32_t >( row, 1508 );
   iconSpecial = exdData->getField< uint32_t >( row, 1509 );
   eventIconType = exdData->getField< uint8_t >( row, 1512 );
   sortKey = exdData->getField< uint16_t >( row, 1514 );
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

Sapphire::Data::Recipe::Recipe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_RecipeDat.get_row( row_id );
   craftType = exdData->getField< int32_t >( row, 1 );
   recipeLevelTable = exdData->getField< uint16_t >( row, 2 );
   itemResult = exdData->getField< int32_t >( row, 3 );
   amountResult = exdData->getField< uint8_t >( row, 4 );
   recipeElement = exdData->getField< uint8_t >( row, 25 );
   isSecondary = exdData->getField< bool >( row, 27 );
   difficultyFactor = exdData->getField< uint16_t >( row, 28 );
   qualityFactor = exdData->getField< uint16_t >( row, 29 );
   durabilityFactor = exdData->getField< uint16_t >( row, 30 );
   requiredCraftsmanship = exdData->getField< uint16_t >( row, 32 );
   requiredControl = exdData->getField< uint16_t >( row, 33 );
   quickSynthCraftsmanship = exdData->getField< uint16_t >( row, 34 );
   quickSynthControl = exdData->getField< uint16_t >( row, 35 );
   secretRecipeBook = exdData->getField< uint16_t >( row, 36 );
   canQuickSynth = exdData->getField< bool >( row, 37 );
   canHq = exdData->getField< bool >( row, 38 );
   expRewarded = exdData->getField< bool >( row, 39 );
   statusRequired = exdData->getField< int32_t >( row, 40 );
   itemRequired = exdData->getField< int32_t >( row, 41 );
   isSpecializationRequired = exdData->getField< bool >( row, 42 );
   patchNumber = exdData->getField< uint16_t >( row, 44 );
}

Sapphire::Data::RecipeElement::RecipeElement( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_RecipeElementDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::RecipeLevelTable::RecipeLevelTable( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_RecipeLevelTableDat.get_row( row_id );
   classJobLevel = exdData->getField< uint8_t >( row, 0 );
   stars = exdData->getField< uint8_t >( row, 1 );
   suggestedCraftsmanship = exdData->getField< uint16_t >( row, 2 );
   difficulty = exdData->getField< uint16_t >( row, 3 );
   quality = exdData->getField< int16_t >( row, 4 );
   durability = exdData->getField< uint16_t >( row, 5 );
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
}

Sapphire::Data::Relic::Relic( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_RelicDat.get_row( row_id );
   itemAtma = exdData->getField< uint32_t >( row, 0 );
   itemAnimus = exdData->getField< uint32_t >( row, 1 );
   icon = exdData->getField< int32_t >( row, 2 );
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
   residentMotionType = exdData->getField< uint8_t >( row, 3 );
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

Sapphire::Data::RPParameter::RPParameter( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_RPParameterDat.get_row( row_id );
   bNpcName = exdData->getField< uint16_t >( row, 0 );
   classJob = exdData->getField< uint8_t >( row, 1 );
}

Sapphire::Data::Salvage::Salvage( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_SalvageDat.get_row( row_id );
   optimalSkill = exdData->getField< uint16_t >( row, 0 );
}

Sapphire::Data::SatisfactionNpc::SatisfactionNpc( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_SatisfactionNpcDat.get_row( row_id );
   npc = exdData->getField< int32_t >( row, 0 );
   questRequired = exdData->getField< int32_t >( row, 1 );
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

Sapphire::Data::ScenarioTreeTipsQuest::ScenarioTreeTipsQuest( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_ScenarioTreeTipsQuestDat.get_row( row_id );
   level = exdData->getField< uint32_t >( row, 0 );
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
   objective1 = exdData->getField< uint16_t >( row, 4 );
   requiredAmount1 = exdData->getField< uint8_t >( row, 6 );
   objective2 = exdData->getField< uint16_t >( row, 9 );
   requiredAmount2 = exdData->getField< uint8_t >( row, 11 );
   objective3 = exdData->getField< uint16_t >( row, 14 );
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

Sapphire::Data::SpearfishingItem::SpearfishingItem( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_SpearfishingItemDat.get_row( row_id );
   description = exdData->getField< std::string >( row, 0 );
   item = exdData->getField< int32_t >( row, 1 );
   gatheringItemLevel = exdData->getField< uint16_t >( row, 2 );
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
   questUnlock = exdData->getField< uint32_t >( row, 1862 );
   questShop = exdData->getField< int32_t >( row, 1863 );
   notCompleteText = exdData->getField< int32_t >( row, 1864 );
   completeText = exdData->getField< int32_t >( row, 1865 );
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
   name = exdData->getField< std::string >( row, 2 );
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
   category = exdData->getField< uint8_t >( row, 4 );
   hitEffect = exdData->getField< uint8_t >( row, 5 );
   vFX = exdData->getField< uint8_t >( row, 6 );
   lockMovement = exdData->getField< bool >( row, 7 );
   lockActions = exdData->getField< bool >( row, 9 );
   lockControl = exdData->getField< bool >( row, 10 );
   transfiguration = exdData->getField< bool >( row, 11 );
   canDispel = exdData->getField< bool >( row, 13 );
   inflictedByActor = exdData->getField< bool >( row, 14 );
   isPermanent = exdData->getField< bool >( row, 15 );
   isFcBuff = exdData->getField< bool >( row, 21 );
   invisibility = exdData->getField< bool >( row, 22 );
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
}

Sapphire::Data::SubmarineExploration::SubmarineExploration( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_SubmarineExplorationDat.get_row( row_id );
   destination = exdData->getField< std::string >( row, 0 );
   location = exdData->getField< std::string >( row, 1 );
   rankReq = exdData->getField< uint8_t >( row, 5 );
   ceruleumTankReq = exdData->getField< uint8_t >( row, 6 );
   durationmin = exdData->getField< uint16_t >( row, 7 );
   distanceForSurvey = exdData->getField< uint8_t >( row, 8 );
   expReward = exdData->getField< uint32_t >( row, 9 );
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
   repairMaterials = exdData->getField< uint8_t >( row, 9 );
}

Sapphire::Data::SubmarineRank::SubmarineRank( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_SubmarineRankDat.get_row( row_id );
   rank = exdData->getField< uint16_t >( row, 0 );
   expToNext = exdData->getField< uint32_t >( row, 1 );
}

Sapphire::Data::SwitchTalk::SwitchTalk( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_SwitchTalkDat.get_row( row_id );
   quest.push_back( exdData->getField< uint32_t >( row, 2 ) );
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
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 17 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 18 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 19 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 20 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 21 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 22 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 23 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 24 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 25 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 26 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 27 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 28 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 29 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 30 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 31 ) );
   defaultTalk.push_back( exdData->getField< uint32_t >( row, 32 ) );
}

Sapphire::Data::TerritoryType::TerritoryType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_TerritoryTypeDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
   bg = exdData->getField< std::string >( row, 1 );
   placeNameRegion = exdData->getField< uint16_t >( row, 3 );
   placeNameZone = exdData->getField< uint16_t >( row, 4 );
   placeName = exdData->getField< uint16_t >( row, 5 );
   map = exdData->getField< uint16_t >( row, 6 );
   territoryIntendedUse = exdData->getField< uint8_t >( row, 9 );
   weatherRate = exdData->getField< uint8_t >( row, 12 );
   arrayEventHandler = exdData->getField< uint32_t >( row, 22 );
   aetheryte = exdData->getField< int32_t >( row, 24 );
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
   bNpcCustomize = exdData->getField< int32_t >( row, 4 );
   action.push_back( exdData->getField< uint16_t >( row, 5 ) );
   action.push_back( exdData->getField< uint16_t >( row, 6 ) );
   action.push_back( exdData->getField< uint16_t >( row, 7 ) );
   action.push_back( exdData->getField< uint16_t >( row, 8 ) );
   action.push_back( exdData->getField< uint16_t >( row, 9 ) );
   action.push_back( exdData->getField< uint16_t >( row, 10 ) );
   speed = exdData->getField< float >( row, 13 );
   scale = exdData->getField< float >( row, 14 );
   isPvP = exdData->getField< bool >( row, 15 );
   isEvent = exdData->getField< bool >( row, 16 );
   playerCamera = exdData->getField< bool >( row, 17 );
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
   minPartySize = exdData->getField< uint8_t >( row, 6 );
}

Sapphire::Data::Tribe::Tribe( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_TribeDat.get_row( row_id );
   masculine = exdData->getField< std::string >( row, 0 );
   feminine = exdData->getField< std::string >( row, 1 );
   sTR = exdData->getField< int8_t >( row, 4 );
   dEX = exdData->getField< int8_t >( row, 5 );
   vIT = exdData->getField< int8_t >( row, 6 );
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
   foreground = exdData->getField< uint32_t >( row, 0 );
   background = exdData->getField< uint32_t >( row, 1 );
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
   level = exdData->getField< uint32_t >( row, 0 );
   placeName = exdData->getField< uint16_t >( row, 1 );
   conditionSuccessEvent = exdData->getField< uint32_t >( row, 2 );
   conditionFailEvent = exdData->getField< uint32_t >( row, 3 );
   confirmEvent = exdData->getField< uint32_t >( row, 4 );
   warpCondition = exdData->getField< uint16_t >( row, 5 );
   warpLogic = exdData->getField< uint16_t >( row, 6 );
}

Sapphire::Data::WarpCondition::WarpCondition( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_WarpConditionDat.get_row( row_id );
   requiredQuest1 = exdData->getField< uint32_t >( row, 2 );
   requiredQuest2 = exdData->getField< uint32_t >( row, 3 );
   dRequiredQuest3 = exdData->getField< uint32_t >( row, 4 );
   requiredQuest4 = exdData->getField< uint32_t >( row, 5 );
}

Sapphire::Data::WarpLogic::WarpLogic( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_WarpLogicDat.get_row( row_id );
   warpName = exdData->getField< std::string >( row, 1 );
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
   argument.push_back( exdData->getField< uint32_t >( row, 13 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 14 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 15 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 16 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 17 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 18 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 19 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 20 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 21 ) );
   argument.push_back( exdData->getField< uint32_t >( row, 22 ) );
   question = exdData->getField< std::string >( row, 23 );
   responseYes = exdData->getField< std::string >( row, 24 );
   responseNo = exdData->getField< std::string >( row, 25 );
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
   dataCenter = exdData->getField< uint8_t >( row, 2 );
   isPublic = exdData->getField< bool >( row, 3 );
}

Sapphire::Data::WorldDCGroupType::WorldDCGroupType( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_WorldDCGroupTypeDat.get_row( row_id );
   name = exdData->getField< std::string >( row, 0 );
}

Sapphire::Data::YKW::YKW( uint32_t row_id, Sapphire::Data::ExdDataGenerated* exdData )
{
   auto row = exdData->m_YKWDat.get_row( row_id );
   item = exdData->getField< uint32_t >( row, 1 );
   location.push_back( exdData->getField< uint16_t >( row, 2 ) );
   location.push_back( exdData->getField< uint16_t >( row, 3 ) );
   location.push_back( exdData->getField< uint16_t >( row, 4 ) );
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
      m_AddonHudDat = setupDatAccess( "AddonHud", xiv::exd::Language::en );
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
      m_AquariumFishDat = setupDatAccess( "AquariumFish", xiv::exd::Language::none );
      m_AquariumWaterDat = setupDatAccess( "AquariumWater", xiv::exd::Language::en );
      m_ArrayEventHandlerDat = setupDatAccess( "ArrayEventHandler", xiv::exd::Language::none );
      m_AttackTypeDat = setupDatAccess( "AttackType", xiv::exd::Language::en );
      m_BacklightColorDat = setupDatAccess( "BacklightColor", xiv::exd::Language::none );
      m_BalloonDat = setupDatAccess( "Balloon", xiv::exd::Language::en );
      m_BaseParamDat = setupDatAccess( "BaseParam", xiv::exd::Language::en );
      m_BattleLeveDat = setupDatAccess( "BattleLeve", xiv::exd::Language::none );
      m_BeastRankBonusDat = setupDatAccess( "BeastRankBonus", xiv::exd::Language::none );
      m_BeastReputationRankDat = setupDatAccess( "BeastReputationRank", xiv::exd::Language::en );
      m_BeastTribeDat = setupDatAccess( "BeastTribe", xiv::exd::Language::en );
      m_BehaviorDat = setupDatAccess( "Behavior", xiv::exd::Language::none );
      m_BGMDat = setupDatAccess( "BGM", xiv::exd::Language::none );
      m_BGMFadeDat = setupDatAccess( "BGMFade", xiv::exd::Language::none );
      m_BGMSituationDat = setupDatAccess( "BGMSituation", xiv::exd::Language::none );
      m_BGMSwitchDat = setupDatAccess( "BGMSwitch", xiv::exd::Language::none );
      m_BGMSystemDefineDat = setupDatAccess( "BGMSystemDefine", xiv::exd::Language::none );
      m_BNpcAnnounceIconDat = setupDatAccess( "BNpcAnnounceIcon", xiv::exd::Language::none );
      m_BNpcBaseDat = setupDatAccess( "BNpcBase", xiv::exd::Language::none );
      m_BNpcCustomizeDat = setupDatAccess( "BNpcCustomize", xiv::exd::Language::none );
      m_BNpcNameDat = setupDatAccess( "BNpcName", xiv::exd::Language::en );
      m_BNpcPartsDat = setupDatAccess( "BNpcParts", xiv::exd::Language::none );
      m_BuddyDat = setupDatAccess( "Buddy", xiv::exd::Language::none );
      m_BuddyActionDat = setupDatAccess( "BuddyAction", xiv::exd::Language::en );
      m_BuddyEquipDat = setupDatAccess( "BuddyEquip", xiv::exd::Language::en );
      m_BuddyItemDat = setupDatAccess( "BuddyItem", xiv::exd::Language::none );
      m_BuddyRankDat = setupDatAccess( "BuddyRank", xiv::exd::Language::none );
      m_BuddySkillDat = setupDatAccess( "BuddySkill", xiv::exd::Language::none );
      m_CabinetDat = setupDatAccess( "Cabinet", xiv::exd::Language::none );
      m_CabinetCategoryDat = setupDatAccess( "CabinetCategory", xiv::exd::Language::none );
      m_CalendarDat = setupDatAccess( "Calendar", xiv::exd::Language::none );
      m_CharaMakeCustomizeDat = setupDatAccess( "CharaMakeCustomize", xiv::exd::Language::none );
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
      m_ClassJobDat = setupDatAccess( "ClassJob", xiv::exd::Language::en );
      m_ClassJobCategoryDat = setupDatAccess( "ClassJobCategory", xiv::exd::Language::en );
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
      m_CompleteJournalDat = setupDatAccess( "CompleteJournal", xiv::exd::Language::en );
      m_CompleteJournalCategoryDat = setupDatAccess( "CompleteJournalCategory", xiv::exd::Language::none );
      m_ContentCloseCycleDat = setupDatAccess( "ContentCloseCycle", xiv::exd::Language::none );
      m_ContentExActionDat = setupDatAccess( "ContentExAction", xiv::exd::Language::none );
      m_ContentFinderConditionDat = setupDatAccess( "ContentFinderCondition", xiv::exd::Language::en );
      m_ContentFinderConditionTransientDat = setupDatAccess( "ContentFinderConditionTransient", xiv::exd::Language::en );
      m_ContentGaugeDat = setupDatAccess( "ContentGauge", xiv::exd::Language::en );
      m_ContentGaugeColorDat = setupDatAccess( "ContentGaugeColor", xiv::exd::Language::none );
      m_ContentMemberTypeDat = setupDatAccess( "ContentMemberType", xiv::exd::Language::none );
      m_ContentNpcTalkDat = setupDatAccess( "ContentNpcTalk", xiv::exd::Language::none );
      m_ContentRouletteDat = setupDatAccess( "ContentRoulette", xiv::exd::Language::en );
      m_ContentRouletteOpenRuleDat = setupDatAccess( "ContentRouletteOpenRule", xiv::exd::Language::none );
      m_ContentRouletteRoleBonusDat = setupDatAccess( "ContentRouletteRoleBonus", xiv::exd::Language::none );
      m_ContentsNoteDat = setupDatAccess( "ContentsNote", xiv::exd::Language::en );
      m_ContentTalkDat = setupDatAccess( "ContentTalk", xiv::exd::Language::en );
      m_ContentTalkParamDat = setupDatAccess( "ContentTalkParam", xiv::exd::Language::none );
      m_ContentTypeDat = setupDatAccess( "ContentType", xiv::exd::Language::en );
      m_CraftActionDat = setupDatAccess( "CraftAction", xiv::exd::Language::en );
      m_CraftLeveDat = setupDatAccess( "CraftLeve", xiv::exd::Language::none );
      m_CraftTypeDat = setupDatAccess( "CraftType", xiv::exd::Language::en );
      m_CreditDat = setupDatAccess( "Credit", xiv::exd::Language::none );
      m_CreditCastDat = setupDatAccess( "CreditCast", xiv::exd::Language::en );
      m_CurrencyDat = setupDatAccess( "Currency", xiv::exd::Language::none );
      m_CustomTalkDat = setupDatAccess( "CustomTalk", xiv::exd::Language::en );
      m_CutsceneDat = setupDatAccess( "Cutscene", xiv::exd::Language::none );
      m_CutScreenImageDat = setupDatAccess( "CutScreenImage", xiv::exd::Language::none );
      m_DailySupplyItemDat = setupDatAccess( "DailySupplyItem", xiv::exd::Language::none );
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
      m_DisposalShopDat = setupDatAccess( "DisposalShop", xiv::exd::Language::en );
      m_DisposalShopFilterTypeDat = setupDatAccess( "DisposalShopFilterType", xiv::exd::Language::en );
      m_DisposalShopItemDat = setupDatAccess( "DisposalShopItem", xiv::exd::Language::none );
      m_DpsChallengeDat = setupDatAccess( "DpsChallenge", xiv::exd::Language::en );
      m_DpsChallengeOfficerDat = setupDatAccess( "DpsChallengeOfficer", xiv::exd::Language::none );
      m_DpsChallengeTransientDat = setupDatAccess( "DpsChallengeTransient", xiv::exd::Language::none );
      m_EmoteDat = setupDatAccess( "Emote", xiv::exd::Language::en );
      m_EmoteCategoryDat = setupDatAccess( "EmoteCategory", xiv::exd::Language::en );
      m_ENpcBaseDat = setupDatAccess( "ENpcBase", xiv::exd::Language::none );
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
      m_ExportedSGDat = setupDatAccess( "ExportedSG", xiv::exd::Language::none );
      m_ExVersionDat = setupDatAccess( "ExVersion", xiv::exd::Language::en );
      m_FateDat = setupDatAccess( "Fate", xiv::exd::Language::en );
      m_FCActivityDat = setupDatAccess( "FCActivity", xiv::exd::Language::en );
      m_FCActivityCategoryDat = setupDatAccess( "FCActivityCategory", xiv::exd::Language::en );
      m_FCAuthorityDat = setupDatAccess( "FCAuthority", xiv::exd::Language::en );
      m_FCAuthorityCategoryDat = setupDatAccess( "FCAuthorityCategory", xiv::exd::Language::en );
      m_FCChestNameDat = setupDatAccess( "FCChestName", xiv::exd::Language::en );
      m_FccShopDat = setupDatAccess( "FccShop", xiv::exd::Language::en );
      m_FCHierarchyDat = setupDatAccess( "FCHierarchy", xiv::exd::Language::en );
      m_FCProfileDat = setupDatAccess( "FCProfile", xiv::exd::Language::en );
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
      m_GardeningSeedDat = setupDatAccess( "GardeningSeed", xiv::exd::Language::none );
      m_GatheringConditionDat = setupDatAccess( "GatheringCondition", xiv::exd::Language::en );
      m_GatheringExpDat = setupDatAccess( "GatheringExp", xiv::exd::Language::none );
      m_GatheringItemDat = setupDatAccess( "GatheringItem", xiv::exd::Language::none );
      m_GatheringItemLevelConvertTableDat = setupDatAccess( "GatheringItemLevelConvertTable", xiv::exd::Language::none );
      m_GatheringItemPointDat = setupDatAccess( "GatheringItemPoint", xiv::exd::Language::none );
      m_GatheringLeveDat = setupDatAccess( "GatheringLeve", xiv::exd::Language::none );
      m_GatheringLeveRouteDat = setupDatAccess( "GatheringLeveRoute", xiv::exd::Language::none );
      m_GatheringNotebookListDat = setupDatAccess( "GatheringNotebookList", xiv::exd::Language::none );
      m_GatheringPointDat = setupDatAccess( "GatheringPoint", xiv::exd::Language::none );
      m_GatheringPointBaseDat = setupDatAccess( "GatheringPointBase", xiv::exd::Language::none );
      m_GatheringPointBonusDat = setupDatAccess( "GatheringPointBonus", xiv::exd::Language::none );
      m_GatheringPointBonusTypeDat = setupDatAccess( "GatheringPointBonusType", xiv::exd::Language::en );
      m_GatheringPointNameDat = setupDatAccess( "GatheringPointName", xiv::exd::Language::en );
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
      m_GilShopDat = setupDatAccess( "GilShop", xiv::exd::Language::en );
      m_GilShopItemDat = setupDatAccess( "GilShopItem", xiv::exd::Language::none );
      m_GoldSaucerArcadeMachineDat = setupDatAccess( "GoldSaucerArcadeMachine", xiv::exd::Language::en );
      m_GoldSaucerTextDataDat = setupDatAccess( "GoldSaucerTextData", xiv::exd::Language::en );
      m_GrandCompanyDat = setupDatAccess( "GrandCompany", xiv::exd::Language::en );
      m_GrandCompanyRankDat = setupDatAccess( "GrandCompanyRank", xiv::exd::Language::none );
      m_GuardianDeityDat = setupDatAccess( "GuardianDeity", xiv::exd::Language::en );
      m_GuildleveAssignmentDat = setupDatAccess( "GuildleveAssignment", xiv::exd::Language::none );
      m_GuildleveAssignmentCategoryDat = setupDatAccess( "GuildleveAssignmentCategory", xiv::exd::Language::none );
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
      m_HousingMapMarkerInfoDat = setupDatAccess( "HousingMapMarkerInfo", xiv::exd::Language::none );
      m_HousingMerchantPoseDat = setupDatAccess( "HousingMerchantPose", xiv::exd::Language::en );
      m_HousingLandSetDat = setupDatAccess( "HousingLandSet", xiv::exd::Language::none );
      m_HousingPlacementDat = setupDatAccess( "HousingPlacement", xiv::exd::Language::en );
      m_HousingPresetDat = setupDatAccess( "HousingPreset", xiv::exd::Language::en );
      m_HousingUnitedExteriorDat = setupDatAccess( "HousingUnitedExterior", xiv::exd::Language::none );
      m_HousingYardObjectDat = setupDatAccess( "HousingYardObject", xiv::exd::Language::none );
      m_HowToDat = setupDatAccess( "HowTo", xiv::exd::Language::en );
      m_HowToCategoryDat = setupDatAccess( "HowToCategory", xiv::exd::Language::en );
      m_HowToPageDat = setupDatAccess( "HowToPage", xiv::exd::Language::en );
      m_InstanceContentDat = setupDatAccess( "InstanceContent", xiv::exd::Language::en );
      m_InstanceContentBuffDat = setupDatAccess( "InstanceContentBuff", xiv::exd::Language::none );
      m_InstanceContentTextDataDat = setupDatAccess( "InstanceContentTextData", xiv::exd::Language::en );
      m_ItemDat = setupDatAccess( "Item", xiv::exd::Language::en );
      m_ItemActionDat = setupDatAccess( "ItemAction", xiv::exd::Language::none );
      m_ItemFoodDat = setupDatAccess( "ItemFood", xiv::exd::Language::none );
      m_ItemLevelDat = setupDatAccess( "ItemLevel", xiv::exd::Language::none );
      m_ItemSearchCategoryDat = setupDatAccess( "ItemSearchCategory", xiv::exd::Language::en );
      m_ItemSeriesDat = setupDatAccess( "ItemSeries", xiv::exd::Language::en );
      m_ItemSpecialBonusDat = setupDatAccess( "ItemSpecialBonus", xiv::exd::Language::en );
      m_ItemUICategoryDat = setupDatAccess( "ItemUICategory", xiv::exd::Language::en );
      m_JournalCategoryDat = setupDatAccess( "JournalCategory", xiv::exd::Language::en );
      m_JournalGenreDat = setupDatAccess( "JournalGenre", xiv::exd::Language::en );
      m_JournalSectionDat = setupDatAccess( "JournalSection", xiv::exd::Language::en );
      m_LeveDat = setupDatAccess( "Leve", xiv::exd::Language::en );
      m_LeveAssignmentTypeDat = setupDatAccess( "LeveAssignmentType", xiv::exd::Language::en );
      m_LeveClientDat = setupDatAccess( "LeveClient", xiv::exd::Language::en );
      m_LevelDat = setupDatAccess( "Level", xiv::exd::Language::none );
      m_LeveRewardItemDat = setupDatAccess( "LeveRewardItem", xiv::exd::Language::none );
      m_LeveRewardItemGroupDat = setupDatAccess( "LeveRewardItemGroup", xiv::exd::Language::none );
      m_LeveVfxDat = setupDatAccess( "LeveVfx", xiv::exd::Language::none );
      m_LogFilterDat = setupDatAccess( "LogFilter", xiv::exd::Language::en );
      m_LogKindDat = setupDatAccess( "LogKind", xiv::exd::Language::en );
      m_LogKindCategoryTextDat = setupDatAccess( "LogKindCategoryText", xiv::exd::Language::en );
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
      m_MiniGameRADat = setupDatAccess( "MiniGameRA", xiv::exd::Language::none );
      m_MinionRaceDat = setupDatAccess( "MinionRace", xiv::exd::Language::en );
      m_MinionRulesDat = setupDatAccess( "MinionRules", xiv::exd::Language::en );
      m_MinionSkillTypeDat = setupDatAccess( "MinionSkillType", xiv::exd::Language::en );
      m_MobHuntOrderTypeDat = setupDatAccess( "MobHuntOrderType", xiv::exd::Language::none );
      m_MobHuntTargetDat = setupDatAccess( "MobHuntTarget", xiv::exd::Language::none );
      m_ModelCharaDat = setupDatAccess( "ModelChara", xiv::exd::Language::none );
      m_ModelStateDat = setupDatAccess( "ModelState", xiv::exd::Language::none );
      m_MonsterNoteDat = setupDatAccess( "MonsterNote", xiv::exd::Language::en );
      m_MonsterNoteTargetDat = setupDatAccess( "MonsterNoteTarget", xiv::exd::Language::none );
      m_MountDat = setupDatAccess( "Mount", xiv::exd::Language::en );
      m_MountActionDat = setupDatAccess( "MountAction", xiv::exd::Language::none );
      m_MountCustomizeDat = setupDatAccess( "MountCustomize", xiv::exd::Language::none );
      m_MountFlyingConditionDat = setupDatAccess( "MountFlyingCondition", xiv::exd::Language::none );
      m_MountSpeedDat = setupDatAccess( "MountSpeed", xiv::exd::Language::none );
      m_MountTransientDat = setupDatAccess( "MountTransient", xiv::exd::Language::en );
      m_MoveTimelineDat = setupDatAccess( "MoveTimeline", xiv::exd::Language::none );
      m_MoveVfxDat = setupDatAccess( "MoveVfx", xiv::exd::Language::none );
      m_NpcEquipDat = setupDatAccess( "NpcEquip", xiv::exd::Language::none );
      m_NpcYellDat = setupDatAccess( "NpcYell", xiv::exd::Language::en );
      m_OmenDat = setupDatAccess( "Omen", xiv::exd::Language::none );
      m_OnlineStatusDat = setupDatAccess( "OnlineStatus", xiv::exd::Language::en );
      m_OpeningDat = setupDatAccess( "Opening", xiv::exd::Language::none );
      m_OrchestrionDat = setupDatAccess( "Orchestrion", xiv::exd::Language::en );
      m_OrchestrionCategoryDat = setupDatAccess( "OrchestrionCategory", xiv::exd::Language::en );
      m_OrchestrionPathDat = setupDatAccess( "OrchestrionPath", xiv::exd::Language::none );
      m_OrchestrionUiparamDat = setupDatAccess( "OrchestrionUiparam", xiv::exd::Language::none );
      m_ParamGrowDat = setupDatAccess( "ParamGrow", xiv::exd::Language::none );
      m_PartyContentDat = setupDatAccess( "PartyContent", xiv::exd::Language::en );
      m_PartyContentCutsceneDat = setupDatAccess( "PartyContentCutscene", xiv::exd::Language::none );
      m_PartyContentTextDataDat = setupDatAccess( "PartyContentTextData", xiv::exd::Language::en );
      m_PerformDat = setupDatAccess( "Perform", xiv::exd::Language::en );
      m_PerformTransientDat = setupDatAccess( "PerformTransient", xiv::exd::Language::en );
      m_PetDat = setupDatAccess( "Pet", xiv::exd::Language::en );
      m_PetActionDat = setupDatAccess( "PetAction", xiv::exd::Language::en );
      m_PictureDat = setupDatAccess( "Picture", xiv::exd::Language::none );
      m_PlaceNameDat = setupDatAccess( "PlaceName", xiv::exd::Language::en );
      m_PlantPotFlowerSeedDat = setupDatAccess( "PlantPotFlowerSeed", xiv::exd::Language::none );
      m_PreHandlerDat = setupDatAccess( "PreHandler", xiv::exd::Language::none );
      m_PublicContentDat = setupDatAccess( "PublicContent", xiv::exd::Language::en );
      m_PublicContentCutsceneDat = setupDatAccess( "PublicContentCutscene", xiv::exd::Language::none );
      m_PublicContentTextDataDat = setupDatAccess( "PublicContentTextData", xiv::exd::Language::en );
      m_PvPActionDat = setupDatAccess( "PvPAction", xiv::exd::Language::none );
      m_PvPActionSortDat = setupDatAccess( "PvPActionSort", xiv::exd::Language::none );
      m_PvPRankDat = setupDatAccess( "PvPRank", xiv::exd::Language::none );
      m_PvPSelectTraitDat = setupDatAccess( "PvPSelectTrait", xiv::exd::Language::en );
      m_PvPTraitDat = setupDatAccess( "PvPTrait", xiv::exd::Language::none );
      m_QuestDat = setupDatAccess( "Quest", xiv::exd::Language::en );
      m_QuestClassJobRewardDat = setupDatAccess( "QuestClassJobReward", xiv::exd::Language::none );
      m_QuestClassJobSupplyDat = setupDatAccess( "QuestClassJobSupply", xiv::exd::Language::none );
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
      m_RecipeDat = setupDatAccess( "Recipe", xiv::exd::Language::none );
      m_RecipeElementDat = setupDatAccess( "RecipeElement", xiv::exd::Language::en );
      m_RecipeLevelTableDat = setupDatAccess( "RecipeLevelTable", xiv::exd::Language::none );
      m_RecipeNotebookListDat = setupDatAccess( "RecipeNotebookList", xiv::exd::Language::none );
      m_RecommendContentsDat = setupDatAccess( "RecommendContents", xiv::exd::Language::none );
      m_RelicDat = setupDatAccess( "Relic", xiv::exd::Language::none );
      m_Relic3Dat = setupDatAccess( "Relic3", xiv::exd::Language::none );
      m_RelicItemDat = setupDatAccess( "RelicItem", xiv::exd::Language::none );
      m_RelicNoteDat = setupDatAccess( "RelicNote", xiv::exd::Language::none );
      m_RelicNoteCategoryDat = setupDatAccess( "RelicNoteCategory", xiv::exd::Language::en );
      m_ResidentDat = setupDatAccess( "Resident", xiv::exd::Language::none );
      m_RetainerTaskDat = setupDatAccess( "RetainerTask", xiv::exd::Language::none );
      m_RetainerTaskLvRangeDat = setupDatAccess( "RetainerTaskLvRange", xiv::exd::Language::none );
      m_RetainerTaskNormalDat = setupDatAccess( "RetainerTaskNormal", xiv::exd::Language::none );
      m_RetainerTaskParameterDat = setupDatAccess( "RetainerTaskParameter", xiv::exd::Language::none );
      m_RetainerTaskRandomDat = setupDatAccess( "RetainerTaskRandom", xiv::exd::Language::en );
      m_RPParameterDat = setupDatAccess( "RPParameter", xiv::exd::Language::none );
      m_SalvageDat = setupDatAccess( "Salvage", xiv::exd::Language::none );
      m_SatisfactionNpcDat = setupDatAccess( "SatisfactionNpc", xiv::exd::Language::none );
      m_SatisfactionSupplyDat = setupDatAccess( "SatisfactionSupply", xiv::exd::Language::none );
      m_SatisfactionSupplyRewardDat = setupDatAccess( "SatisfactionSupplyReward", xiv::exd::Language::none );
      m_ScenarioTreeDat = setupDatAccess( "ScenarioTree", xiv::exd::Language::none );
      m_ScenarioTreeTipsDat = setupDatAccess( "ScenarioTreeTips", xiv::exd::Language::none );
      m_ScenarioTreeTipsClassQuestDat = setupDatAccess( "ScenarioTreeTipsClassQuest", xiv::exd::Language::none );
      m_ScenarioTreeTipsQuestDat = setupDatAccess( "ScenarioTreeTipsQuest", xiv::exd::Language::none );
      m_ScenarioTypeDat = setupDatAccess( "ScenarioType", xiv::exd::Language::en );
      m_ScreenImageDat = setupDatAccess( "ScreenImage", xiv::exd::Language::none );
      m_SecretRecipeBookDat = setupDatAccess( "SecretRecipeBook", xiv::exd::Language::en );
      m_SkyIsland2MissionDat = setupDatAccess( "SkyIsland2Mission", xiv::exd::Language::en );
      m_SkyIsland2MissionDetailDat = setupDatAccess( "SkyIsland2MissionDetail", xiv::exd::Language::en );
      m_SkyIsland2MissionTypeDat = setupDatAccess( "SkyIsland2MissionType", xiv::exd::Language::none );
      m_SkyIsland2RangeTypeDat = setupDatAccess( "SkyIsland2RangeType", xiv::exd::Language::none );
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
      m_SubmarinePartDat = setupDatAccess( "SubmarinePart", xiv::exd::Language::none );
      m_SubmarineRankDat = setupDatAccess( "SubmarineRank", xiv::exd::Language::none );
      m_SwitchTalkDat = setupDatAccess( "SwitchTalk", xiv::exd::Language::none );
      m_TerritoryTypeDat = setupDatAccess( "TerritoryType", xiv::exd::Language::none );
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
      m_WeatherDat = setupDatAccess( "Weather", xiv::exd::Language::en );
      m_WeatherGroupDat = setupDatAccess( "WeatherGroup", xiv::exd::Language::none );
      m_WeatherRateDat = setupDatAccess( "WeatherRate", xiv::exd::Language::none );
      m_WeddingBGMDat = setupDatAccess( "WeddingBGM", xiv::exd::Language::en );
      m_WeeklyBingoOrderDataDat = setupDatAccess( "WeeklyBingoOrderData", xiv::exd::Language::none );
      m_WeeklyBingoRewardDataDat = setupDatAccess( "WeeklyBingoRewardData", xiv::exd::Language::none );
      m_WeeklyBingoTextDat = setupDatAccess( "WeeklyBingoText", xiv::exd::Language::en );
      m_WeeklyLotBonusDat = setupDatAccess( "WeeklyLotBonus", xiv::exd::Language::none );
      m_WorldDat = setupDatAccess( "World", xiv::exd::Language::none );
      m_WorldDCGroupTypeDat = setupDatAccess( "WorldDCGroupType", xiv::exd::Language::none );
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




