#include "ExdDataGenerated.h"
#include <boost/make_shared.hpp>

#include <boost/variant.hpp>



      Core::Data::Achievement::Achievement( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
         data.push_back( exdData->getField< int32_t >( row, 9 ) );
         data.push_back( exdData->getField< int32_t >( row, 10 ) );
         data.push_back( exdData->getField< int32_t >( row, 11 ) );
         data.push_back( exdData->getField< int32_t >( row, 12 ) );
         data.push_back( exdData->getField< int32_t >( row, 13 ) );
         data.push_back( exdData->getField< int32_t >( row, 14 ) );
         data.push_back( exdData->getField< int32_t >( row, 15 ) );
         data.push_back( exdData->getField< int32_t >( row, 16 ) );
         data.push_back( exdData->getField< int32_t >( row, 17 ) );
         order = exdData->getField< uint16_t >( row, 18 );
      }

      Core::Data::AchievementCategory::AchievementCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AchievementCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         achievementKind = exdData->getField< uint8_t >( row, 1 );
      }

      Core::Data::AchievementKind::AchievementKind( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AchievementKindDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Action::Action( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< uint16_t >( row, 2 );
         actionCategory = exdData->getField< uint8_t >( row, 3 );
         actionTimelineUse = exdData->getField< int16_t >( row, 7 );
         actionTimelineHit = exdData->getField< uint16_t >( row, 8 );
         classJob = exdData->getField< int8_t >( row, 10 );
         classJobLevel = exdData->getField< uint8_t >( row, 11 );
         isRoleAction = exdData->getField< bool >( row, 12 );
         range = exdData->getField< int8_t >( row, 13 );
         canTargetSelf = exdData->getField< bool >( row, 14 );
         canTargetParty = exdData->getField< bool >( row, 15 );
         canTargetFriendly = exdData->getField< bool >( row, 16 );
         canTargetHostile = exdData->getField< bool >( row, 17 );
         targetArea = exdData->getField< bool >( row, 20 );
         canTargetDead = exdData->getField< bool >( row, 24 );
         castType = exdData->getField< uint8_t >( row, 26 );
         effectRange = exdData->getField< uint8_t >( row, 27 );
         xAxisModifier = exdData->getField< uint8_t >( row, 28 );
         costType = exdData->getField< uint8_t >( row, 30 );
         cost = exdData->getField< uint16_t >( row, 31 );
         actionCombo = exdData->getField< uint16_t >( row, 34 );
         preservesCombo = exdData->getField< bool >( row, 35 );
         cast100ms = exdData->getField< uint16_t >( row, 36 );
         recast100ms = exdData->getField< uint16_t >( row, 37 );
         cooldownGroup = exdData->getField< uint8_t >( row, 38 );
         attackType = exdData->getField< int8_t >( row, 39 );
         aspect = exdData->getField< uint8_t >( row, 40 );
         actionProcStatus = exdData->getField< uint8_t >( row, 41 );
         statusGainSelf = exdData->getField< uint16_t >( row, 42 );
         actionData = exdData->getField< uint32_t >( row, 43 );
         classJobCategory = exdData->getField< uint8_t >( row, 44 );
         affectsPosition = exdData->getField< bool >( row, 47 );
         omen = exdData->getField< uint8_t >( row, 48 );
         isPvP = exdData->getField< bool >( row, 49 );
      }

      Core::Data::ActionCategory::ActionCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ActionComboRoute::ActionComboRoute( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionComboRouteDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         action.push_back( exdData->getField< uint16_t >( row, 2 ) );
         action.push_back( exdData->getField< uint16_t >( row, 3 ) );
         action.push_back( exdData->getField< uint16_t >( row, 4 ) );
         action.push_back( exdData->getField< uint16_t >( row, 5 ) );
      }

      Core::Data::ActionIndirection::ActionIndirection( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionIndirectionDat.get_row( row_id );
         name = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::ActionProcStatus::ActionProcStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionProcStatusDat.get_row( row_id );
         status = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::ActionTimeline::ActionTimeline( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionTimelineDat.get_row( row_id );
         key = exdData->getField< std::string >( row, 6 );
      }

      Core::Data::ActionTransient::ActionTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ActionTransientDat.get_row( row_id );
         description = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Addon::Addon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AddonDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Adventure::Adventure( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AdventureDat.get_row( row_id );
         level = exdData->getField< int32_t >( row, 0 );
         emote = exdData->getField< uint8_t >( row, 3 );
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

      Core::Data::AdventureExPhase::AdventureExPhase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AdventureExPhaseDat.get_row( row_id );
         quest = exdData->getField< uint32_t >( row, 0 );
         adventureBegin = exdData->getField< uint32_t >( row, 1 );
         adventureEnd = exdData->getField< uint32_t >( row, 2 );
      }

      Core::Data::AetherCurrent::AetherCurrent( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AetherCurrentDat.get_row( row_id );
         quest = exdData->getField< uint32_t >( row, 0 );
      }

      Core::Data::AetherialWheel::AetherialWheel( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AetherialWheelDat.get_row( row_id );
         itemUnprimed = exdData->getField< int32_t >( row, 0 );
         itemPrimed = exdData->getField< int32_t >( row, 1 );
         grade = exdData->getField< uint8_t >( row, 2 );
         hoursRequired = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::Aetheryte::Aetheryte( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AetheryteDat.get_row( row_id );
         placeName = exdData->getField< uint16_t >( row, 8 );
         aethernetName = exdData->getField< uint16_t >( row, 9 );
         territory = exdData->getField< uint16_t >( row, 10 );
         isAetheryte = exdData->getField< bool >( row, 15 );
         aethernetGroup = exdData->getField< uint8_t >( row, 16 );
         map = exdData->getField< uint16_t >( row, 19 );
         aetherstreamX = exdData->getField< int16_t >( row, 20 );
         aetherstreamY = exdData->getField< int16_t >( row, 21 );
      }

      Core::Data::AirshipExplorationLevel::AirshipExplorationLevel( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AirshipExplorationLevelDat.get_row( row_id );
         expToNext = exdData->getField< uint32_t >( row, 1 );
      }

      Core::Data::AirshipExplorationLog::AirshipExplorationLog( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AirshipExplorationLogDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::AirshipExplorationParamType::AirshipExplorationParamType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AirshipExplorationParamTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::AirshipExplorationPart::AirshipExplorationPart( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::AirshipExplorationPoint::AirshipExplorationPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::AnimaWeapon5::AnimaWeapon5( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::AnimaWeapon5Param::AnimaWeapon5Param( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeapon5ParamDat.get_row( row_id );
         baseParam = exdData->getField< uint8_t >( row, 0 );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::AnimaWeapon5PatternGroup::AnimaWeapon5PatternGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeapon5PatternGroupDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::AnimaWeapon5SpiritTalk::AnimaWeapon5SpiritTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeapon5SpiritTalkDat.get_row( row_id );
         dialogue = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::AnimaWeapon5SpiritTalkParam::AnimaWeapon5SpiritTalkParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeapon5SpiritTalkParamDat.get_row( row_id );
         prologue = exdData->getField< std::string >( row, 0 );
         epilogue = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::AnimaWeapon5TradeItem::AnimaWeapon5TradeItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeapon5TradeItemDat.get_row( row_id );
         crystalSand = exdData->getField< uint32_t >( row, 1 );
         qty = exdData->getField< uint8_t >( row, 2 );
         category = exdData->getField< uint8_t >( row, 27 );
      }

      Core::Data::AnimaWeaponFUITalk::AnimaWeaponFUITalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeaponFUITalkDat.get_row( row_id );
         dialogue = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::AnimaWeaponFUITalkParam::AnimaWeaponFUITalkParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeaponFUITalkParamDat.get_row( row_id );
         prologue = exdData->getField< std::string >( row, 0 );
         epilogue = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::AnimaWeaponIcon::AnimaWeaponIcon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AnimaWeaponIconDat.get_row( row_id );
         hyperconductive = exdData->getField< int32_t >( row, 0 );
         reborn = exdData->getField< int32_t >( row, 1 );
         sharpened = exdData->getField< int32_t >( row, 2 );
         zodiac = exdData->getField< int32_t >( row, 3 );
         zodiacLux = exdData->getField< int32_t >( row, 4 );
      }

      Core::Data::AnimaWeaponItem::AnimaWeaponItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::AquariumFish::AquariumFish( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AquariumFishDat.get_row( row_id );
         aquariumWater = exdData->getField< uint8_t >( row, 0 );
         size = exdData->getField< uint8_t >( row, 1 );
         item = exdData->getField< uint32_t >( row, 2 );
      }

      Core::Data::AquariumWater::AquariumWater( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AquariumWaterDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::AttackType::AttackType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_AttackTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Balloon::Balloon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BalloonDat.get_row( row_id );
         dialogue = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::BaseParam::BaseParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BaseParamDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 1 );
         description = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::BattleLeve::BattleLeve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::BeastRankBonus::BeastRankBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::BeastReputationRank::BeastReputationRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BeastReputationRankDat.get_row( row_id );
         requiredReputation = exdData->getField< uint16_t >( row, 0 );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::BeastTribe::BeastTribe( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BeastTribeDat.get_row( row_id );
         beastRankBonus = exdData->getField< uint8_t >( row, 2 );
         iconReputation = exdData->getField< uint32_t >( row, 3 );
         icon = exdData->getField< uint32_t >( row, 4 );
         name = exdData->getField< std::string >( row, 11 );
         nameRelation = exdData->getField< std::string >( row, 19 );
      }

      Core::Data::Behavior::Behavior( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BehaviorDat.get_row( row_id );
         balloon = exdData->getField< uint16_t >( row, 6 );
      }

      Core::Data::BGM::BGM( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BGMDat.get_row( row_id );
         file = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::BNpcAnnounceIcon::BNpcAnnounceIcon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BNpcAnnounceIconDat.get_row( row_id );
         icon = exdData->getField< uint32_t >( row, 0 );
      }

      Core::Data::BNpcBase::BNpcBase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BNpcBaseDat.get_row( row_id );
         scale = exdData->getField< float >( row, 4 );
         modelChara = exdData->getField< uint16_t >( row, 5 );
         bNpcCustomize = exdData->getField< uint16_t >( row, 6 );
         npcEquip = exdData->getField< uint16_t >( row, 7 );
         arrayEventHandler = exdData->getField< int32_t >( row, 11 );
      }

      Core::Data::BNpcCustomize::BNpcCustomize( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::BNpcName::BNpcName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BNpcNameDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::BuddyAction::BuddyAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BuddyActionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< int32_t >( row, 2 );
         iconStatus = exdData->getField< int32_t >( row, 3 );
      }

      Core::Data::BuddyEquip::BuddyEquip( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BuddyEquipDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
         name = exdData->getField< std::string >( row, 8 );
         modelTop = exdData->getField< int32_t >( row, 9 );
         modelBody = exdData->getField< int32_t >( row, 10 );
         modelLegs = exdData->getField< int32_t >( row, 11 );
         grandCompany = exdData->getField< uint8_t >( row, 12 );
         iconHead = exdData->getField< uint16_t >( row, 13 );
         iconBody = exdData->getField< uint16_t >( row, 14 );
         iconLegs = exdData->getField< uint16_t >( row, 15 );
      }

      Core::Data::BuddyItem::BuddyItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BuddyItemDat.get_row( row_id );
         name = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::BuddyRank::BuddyRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BuddyRankDat.get_row( row_id );
         expRequired = exdData->getField< uint32_t >( row, 0 );
      }

      Core::Data::BuddySkill::BuddySkill( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_BuddySkillDat.get_row( row_id );
         buddyLevel = exdData->getField< uint8_t >( row, 0 );
      }

      Core::Data::Cabinet::Cabinet( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CabinetDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         order = exdData->getField< uint16_t >( row, 1 );
         category = exdData->getField< uint8_t >( row, 2 );
      }

      Core::Data::CabinetCategory::CabinetCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CabinetCategoryDat.get_row( row_id );
         menuOrder = exdData->getField< uint8_t >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
         category = exdData->getField< int32_t >( row, 2 );
      }

      Core::Data::Calendar::Calendar( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::ChainBonus::ChainBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChainBonusDat.get_row( row_id );
         bonus = exdData->getField< uint8_t >( row, 0 );
         timeouts = exdData->getField< uint8_t >( row, 1 );
      }

      Core::Data::CharaMakeCustomize::CharaMakeCustomize( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CharaMakeCustomizeDat.get_row( row_id );
         icon = exdData->getField< uint32_t >( row, 1 );
         data = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::CharaMakeType::CharaMakeType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CharaMakeTypeDat.get_row( row_id );
         race = exdData->getField< int32_t >( row, 0 );
         tribe = exdData->getField< int32_t >( row, 1 );
         gender = exdData->getField< int8_t >( row, 2 );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2283 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2284 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2285 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2286 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2287 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2288 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2289 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2290 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2291 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2292 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2293 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2294 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2295 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2296 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2297 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2298 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2299 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2300 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2301 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2302 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2303 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2304 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2305 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2306 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2307 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2308 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2309 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2310 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2311 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2312 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2313 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2314 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2315 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2316 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2317 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2318 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2319 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2320 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2321 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2322 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2323 ) );
         facialFeatureIcon.push_back( exdData->getField< int32_t >( row, 2324 ) );
      }

      Core::Data::ChocoboRace::ChocoboRace( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceDat.get_row( row_id );
         chocoboRaceRank = exdData->getField< uint8_t >( row, 0 );
         chocoboRaceTerritory = exdData->getField< uint8_t >( row, 1 );
      }

      Core::Data::ChocoboRaceAbility::ChocoboRaceAbility( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceAbilityDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< uint32_t >( row, 2 );
         chocoboRaceAbilityType = exdData->getField< int8_t >( row, 3 );
         value = exdData->getField< uint8_t >( row, 4 );
      }

      Core::Data::ChocoboRaceAbilityType::ChocoboRaceAbilityType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceAbilityTypeDat.get_row( row_id );
         isActive = exdData->getField< bool >( row, 0 );
      }

      Core::Data::ChocoboRaceItem::ChocoboRaceItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceItemDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< uint32_t >( row, 2 );
      }

      Core::Data::ChocoboRaceRank::ChocoboRaceRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceRankDat.get_row( row_id );
         ratingMin = exdData->getField< uint16_t >( row, 0 );
         ratingMax = exdData->getField< uint16_t >( row, 1 );
         name = exdData->getField< uint16_t >( row, 2 );
         fee = exdData->getField< uint16_t >( row, 3 );
         icon = exdData->getField< int32_t >( row, 4 );
      }

      Core::Data::ChocoboRaceStatus::ChocoboRaceStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceStatusDat.get_row( row_id );
         status = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::ChocoboRaceTerritory::ChocoboRaceTerritory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboRaceTerritoryDat.get_row( row_id );
         name = exdData->getField< uint16_t >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::ChocoboTaxiStand::ChocoboTaxiStand( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ChocoboTaxiStandDat.get_row( row_id );
         placeName = exdData->getField< std::string >( row, 8 );
      }

      Core::Data::ClassJob::ClassJob( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ClassJobDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         abbreviation = exdData->getField< std::string >( row, 1 );
         classJobCategory = exdData->getField< uint8_t >( row, 3 );
         modifierHitPoints = exdData->getField< uint16_t >( row, 9 );
         modifierStrength = exdData->getField< uint16_t >( row, 11 );
         modifierVitality = exdData->getField< uint16_t >( row, 12 );
         modifierDexterity = exdData->getField< uint16_t >( row, 13 );
         modifierIntelligence = exdData->getField< uint16_t >( row, 14 );
         modifierMind = exdData->getField< uint16_t >( row, 15 );
         modifierPiety = exdData->getField< uint16_t >( row, 16 );
         classJobParent = exdData->getField< uint8_t >( row, 26 );
         nameEnglish = exdData->getField< std::string >( row, 27 );
         itemStartingWeapon = exdData->getField< int32_t >( row, 28 );
         limitBreak1 = exdData->getField< uint16_t >( row, 33 );
         limitBreak2 = exdData->getField< uint16_t >( row, 34 );
         limitBreak3 = exdData->getField< uint16_t >( row, 35 );
         itemSoulCrystal = exdData->getField< uint32_t >( row, 37 );
         startingLevel = exdData->getField< uint8_t >( row, 41 );
      }

      Core::Data::ClassJobCategory::ClassJobCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
      }

      Core::Data::Companion::Companion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanionDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
         behavior = exdData->getField< uint8_t >( row, 14 );
         icon = exdData->getField< uint16_t >( row, 26 );
         cost = exdData->getField< uint8_t >( row, 30 );
         hP = exdData->getField< uint16_t >( row, 31 );
         skillAngle = exdData->getField< uint16_t >( row, 33 );
         skillCost = exdData->getField< uint8_t >( row, 34 );
         minionRace = exdData->getField< uint8_t >( row, 37 );
      }

      Core::Data::CompanionMove::CompanionMove( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanionMoveDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::CompanionTransient::CompanionTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::CompanyAction::CompanyAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::CompanyCraftDraft::CompanyCraftDraft( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftDraftDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         companyCraftDraftCategory = exdData->getField< uint8_t >( row, 1 );
         order = exdData->getField< uint32_t >( row, 8 );
      }

      Core::Data::CompanyCraftDraftCategory::CompanyCraftDraftCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftDraftCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::CompanyCraftManufactoryState::CompanyCraftManufactoryState( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftManufactoryStateDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::CompanyCraftPart::CompanyCraftPart( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftPartDat.get_row( row_id );
         companyCraftType = exdData->getField< uint8_t >( row, 1 );
         companyCraftProcess.push_back( exdData->getField< uint16_t >( row, 2 ) );
         companyCraftProcess.push_back( exdData->getField< uint16_t >( row, 3 ) );
         companyCraftProcess.push_back( exdData->getField< uint16_t >( row, 4 ) );
      }

      Core::Data::CompanyCraftProcess::CompanyCraftProcess( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftProcessDat.get_row( row_id );
      }

      Core::Data::CompanyCraftSequence::CompanyCraftSequence( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::CompanyCraftSupplyItem::CompanyCraftSupplyItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftSupplyItemDat.get_row( row_id );
         item = exdData->getField< uint32_t >( row, 0 );
      }

      Core::Data::CompanyCraftType::CompanyCraftType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompanyCraftTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::CompleteJournal::CompleteJournal( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompleteJournalDat.get_row( row_id );
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

      Core::Data::CompleteJournalCategory::CompleteJournalCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CompleteJournalCategoryDat.get_row( row_id );
         firstQuest = exdData->getField< uint32_t >( row, 0 );
         lastQuest = exdData->getField< uint32_t >( row, 1 );
      }

      Core::Data::ContentExAction::ContentExAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ContentExActionDat.get_row( row_id );
         name = exdData->getField< uint32_t >( row, 0 );
         charges = exdData->getField< uint8_t >( row, 2 );
      }

      Core::Data::ContentFinderCondition::ContentFinderCondition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ContentFinderConditionDat.get_row( row_id );
         contentIndicator = exdData->getField< uint8_t >( row, 0 );
         instanceContent = exdData->getField< uint16_t >( row, 1 );
         contentMemberType = exdData->getField< uint8_t >( row, 5 );
         classJobLevel = exdData->getField< uint8_t >( row, 8 );
         itemLevelRequired = exdData->getField< uint16_t >( row, 10 );
         icon = exdData->getField< uint32_t >( row, 29 );
      }

      Core::Data::ContentFinderConditionTransient::ContentFinderConditionTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ContentFinderConditionTransientDat.get_row( row_id );
         description = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ContentMemberType::ContentMemberType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ContentMemberTypeDat.get_row( row_id );
         tanksPerParty = exdData->getField< uint8_t >( row, 9 );
         healersPerParty = exdData->getField< uint8_t >( row, 10 );
         meleesPerParty = exdData->getField< uint8_t >( row, 11 );
         rangedPerParty = exdData->getField< uint8_t >( row, 12 );
      }

      Core::Data::ContentRoulette::ContentRoulette( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ContentRouletteDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 2 );
         dutyType = exdData->getField< std::string >( row, 3 );
         isInDutyFinder = exdData->getField< bool >( row, 5 );
         requireAllDuties = exdData->getField< bool >( row, 6 );
         itemLevelRequired = exdData->getField< uint16_t >( row, 9 );
         icon = exdData->getField< uint32_t >( row, 11 );
         rewardTomeA = exdData->getField< uint16_t >( row, 13 );
         rewardTomeB = exdData->getField< uint16_t >( row, 14 );
         rewardTomeC = exdData->getField< uint16_t >( row, 15 );
         sortKey = exdData->getField< uint8_t >( row, 18 );
         contentMemberType = exdData->getField< uint8_t >( row, 20 );
      }

      Core::Data::ContentType::ContentType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ContentTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< uint32_t >( row, 1 );
         iconDutyFinder = exdData->getField< uint32_t >( row, 2 );
      }

      Core::Data::CraftAction::CraftAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CraftActionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
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

      Core::Data::CraftLeve::CraftLeve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CraftLeveDat.get_row( row_id );
         leve = exdData->getField< int32_t >( row, 0 );
         repeats = exdData->getField< uint8_t >( row, 2 );
      }

      Core::Data::CraftType::CraftType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CraftTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::Currency::Currency( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CurrencyDat.get_row( row_id );
         item = exdData->getField< uint32_t >( row, 0 );
         limit = exdData->getField< uint32_t >( row, 3 );
      }

      Core::Data::CustomTalk::CustomTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::Cutscene::Cutscene( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CutsceneDat.get_row( row_id );
         path = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::CutScreenImage::CutScreenImage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_CutScreenImageDat.get_row( row_id );
         image = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::DailySupplyItem::DailySupplyItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DailySupplyItemDat.get_row( row_id );
      }

      Core::Data::DeepDungeonBan::DeepDungeonBan( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeepDungeonBanDat.get_row( row_id );
         screenImage = exdData->getField< uint16_t >( row, 0 );
         logMessage = exdData->getField< uint16_t >( row, 1 );
         name = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::DeepDungeonDanger::DeepDungeonDanger( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeepDungeonDangerDat.get_row( row_id );
         screenImage = exdData->getField< uint16_t >( row, 0 );
         logMessage = exdData->getField< uint16_t >( row, 1 );
         name = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::DeepDungeonEquipment::DeepDungeonEquipment( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeepDungeonEquipmentDat.get_row( row_id );
         icon = exdData->getField< uint32_t >( row, 0 );
         singular = exdData->getField< std::string >( row, 1 );
         plural = exdData->getField< std::string >( row, 3 );
         name = exdData->getField< std::string >( row, 9 );
         description = exdData->getField< std::string >( row, 10 );
      }

      Core::Data::DeepDungeonFloorEffectUI::DeepDungeonFloorEffectUI( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeepDungeonFloorEffectUIDat.get_row( row_id );
         icon = exdData->getField< uint32_t >( row, 0 );
         name = exdData->getField< std::string >( row, 1 );
         description = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::DeepDungeonItem::DeepDungeonItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeepDungeonItemDat.get_row( row_id );
         icon = exdData->getField< uint32_t >( row, 0 );
         singular = exdData->getField< std::string >( row, 1 );
         plural = exdData->getField< std::string >( row, 3 );
         name = exdData->getField< std::string >( row, 9 );
         tooltip = exdData->getField< std::string >( row, 10 );
         action = exdData->getField< uint32_t >( row, 11 );
      }

      Core::Data::DeepDungeonStatus::DeepDungeonStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeepDungeonStatusDat.get_row( row_id );
         screenImage = exdData->getField< uint16_t >( row, 0 );
         logMessage = exdData->getField< uint16_t >( row, 1 );
         name = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::DefaultTalk::DefaultTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DefaultTalkDat.get_row( row_id );
         actionTimelinePose.push_back( exdData->getField< uint16_t >( row, 5 ) );
         actionTimelinePose.push_back( exdData->getField< uint16_t >( row, 6 ) );
         actionTimelinePose.push_back( exdData->getField< uint16_t >( row, 7 ) );
         text.push_back( exdData->getField< std::string >( row, 20 ) );
         text.push_back( exdData->getField< std::string >( row, 21 ) );
         text.push_back( exdData->getField< std::string >( row, 22 ) );
      }

      Core::Data::DeliveryQuest::DeliveryQuest( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DeliveryQuestDat.get_row( row_id );
         quest = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::DisposalShop::DisposalShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DisposalShopDat.get_row( row_id );
         shopName = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::DisposalShopFilterType::DisposalShopFilterType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DisposalShopFilterTypeDat.get_row( row_id );
         category = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::DisposalShopItem::DisposalShopItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DisposalShopItemDat.get_row( row_id );
         itemDisposed = exdData->getField< int32_t >( row, 0 );
         itemReceived = exdData->getField< int32_t >( row, 2 );
         quantityReceived = exdData->getField< uint32_t >( row, 4 );
      }

      Core::Data::DpsChallenge::DpsChallenge( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DpsChallengeDat.get_row( row_id );
         playerLevel = exdData->getField< uint16_t >( row, 0 );
         placeName = exdData->getField< uint16_t >( row, 1 );
         icon = exdData->getField< uint32_t >( row, 2 );
         order = exdData->getField< uint16_t >( row, 3 );
         name = exdData->getField< std::string >( row, 4 );
         description = exdData->getField< std::string >( row, 5 );
      }

      Core::Data::DpsChallengeOfficer::DpsChallengeOfficer( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::DpsChallengeTransient::DpsChallengeTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_DpsChallengeTransientDat.get_row( row_id );
         instanceContent = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::Emote::Emote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EmoteDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         emoteCategory = exdData->getField< uint8_t >( row, 11 );
         textCommand = exdData->getField< int32_t >( row, 18 );
         icon = exdData->getField< uint16_t >( row, 19 );
         logMessageTargeted = exdData->getField< uint16_t >( row, 20 );
         logMessageUntargeted = exdData->getField< uint16_t >( row, 21 );
      }

      Core::Data::EmoteCategory::EmoteCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EmoteCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ENpcBase::ENpcBase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::ENpcResident::ENpcResident( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ENpcResidentDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
         title = exdData->getField< std::string >( row, 8 );
         map = exdData->getField< uint8_t >( row, 9 );
      }

      Core::Data::EObj::EObj( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EObjDat.get_row( row_id );
         data = exdData->getField< uint32_t >( row, 9 );
      }

      Core::Data::EquipRaceCategory::EquipRaceCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::EquipSlotCategory::EquipSlotCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::EventAction::EventAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EventActionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< uint16_t >( row, 1 );
      }

      Core::Data::EventIconPriority::EventIconPriority( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::EventIconType::EventIconType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EventIconTypeDat.get_row( row_id );
         npcIconAvailable = exdData->getField< uint32_t >( row, 0 );
         mapIconAvailable = exdData->getField< uint32_t >( row, 1 );
         npcIconInvalid = exdData->getField< uint32_t >( row, 2 );
         mapIconInvalid = exdData->getField< uint32_t >( row, 3 );
         iconRange = exdData->getField< uint8_t >( row, 4 );
      }

      Core::Data::EventItem::EventItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EventItemDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
         rarity = exdData->getField< int8_t >( row, 5 );
         name = exdData->getField< std::string >( row, 9 );
         icon = exdData->getField< uint16_t >( row, 10 );
         stackSize = exdData->getField< uint8_t >( row, 12 );
         quest = exdData->getField< uint32_t >( row, 14 );
      }

      Core::Data::EventItemHelp::EventItemHelp( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_EventItemHelpDat.get_row( row_id );
         description = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ExVersion::ExVersion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ExVersionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Fate::Fate( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FateDat.get_row( row_id );
         classJobLevel = exdData->getField< uint8_t >( row, 2 );
         classJobLevelMax = exdData->getField< uint8_t >( row, 3 );
         eventItem = exdData->getField< uint32_t >( row, 4 );
         iconObjective = exdData->getField< uint32_t >( row, 9 );
         iconMap = exdData->getField< uint32_t >( row, 10 );
         name = exdData->getField< std::string >( row, 26 );
         description = exdData->getField< std::string >( row, 27 );
         objective = exdData->getField< std::string >( row, 28 );
         statusText.push_back( exdData->getField< std::string >( row, 29 ) );
         statusText.push_back( exdData->getField< std::string >( row, 30 ) );
         statusText.push_back( exdData->getField< std::string >( row, 31 ) );
      }

      Core::Data::FCActivity::FCActivity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCActivityDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::FCAuthority::FCAuthority( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCAuthorityDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         fCAuthorityCategory = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::FCAuthorityCategory::FCAuthorityCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCAuthorityCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::FCChestName::FCChestName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCChestNameDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::FccShop::FccShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FccShopDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::FCHierarchy::FCHierarchy( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCHierarchyDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::FCReputation::FCReputation( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCReputationDat.get_row( row_id );
         pointsToNext = exdData->getField< uint32_t >( row, 0 );
         requiredPoints = exdData->getField< uint32_t >( row, 1 );
         name = exdData->getField< std::string >( row, 4 );
      }

      Core::Data::FCRights::FCRights( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FCRightsDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< uint16_t >( row, 2 );
         fCRank = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::FishingSpot::FishingSpot( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::FishParameter::FishParameter( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_FishParameterDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
         item = exdData->getField< int32_t >( row, 1 );
         gatheringItemLevel = exdData->getField< uint16_t >( row, 2 );
         territoryType = exdData->getField< int32_t >( row, 4 );
         isFish = exdData->getField< bool >( row, 5 );
         gatheringSubCategory = exdData->getField< uint16_t >( row, 6 );
      }

      Core::Data::GardeningSeed::GardeningSeed( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GardeningSeedDat.get_row( row_id );
         item = exdData->getField< uint32_t >( row, 0 );
         icon = exdData->getField< uint32_t >( row, 2 );
      }

      Core::Data::GatheringCondition::GatheringCondition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringConditionDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GatheringExp::GatheringExp( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringExpDat.get_row( row_id );
         exp = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::GatheringItem::GatheringItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringItemDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         gatheringItemLevel = exdData->getField< uint16_t >( row, 1 );
         isHidden = exdData->getField< bool >( row, 2 );
      }

      Core::Data::GatheringItemLevelConvertTable::GatheringItemLevelConvertTable( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringItemLevelConvertTableDat.get_row( row_id );
         gatheringItemLevel = exdData->getField< uint8_t >( row, 0 );
         stars = exdData->getField< uint8_t >( row, 1 );
      }

      Core::Data::GatheringItemPoint::GatheringItemPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringItemPointDat.get_row( row_id );
         gatheringPoint = exdData->getField< uint32_t >( row, 0 );
      }

      Core::Data::GatheringNotebookList::GatheringNotebookList( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::GatheringPoint::GatheringPoint( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringPointDat.get_row( row_id );
         gatheringPointBase = exdData->getField< int32_t >( row, 1 );
         gatheringPointBonus.push_back( exdData->getField< uint16_t >( row, 3 ) );
         gatheringPointBonus.push_back( exdData->getField< uint16_t >( row, 4 ) );
         territoryType = exdData->getField< uint16_t >( row, 5 );
         placeName = exdData->getField< uint16_t >( row, 6 );
         gatheringSubCategory = exdData->getField< uint16_t >( row, 7 );
      }

      Core::Data::GatheringPointBase::GatheringPointBase( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::GatheringPointBonus::GatheringPointBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringPointBonusDat.get_row( row_id );
         condition = exdData->getField< uint8_t >( row, 0 );
         conditionValue = exdData->getField< uint16_t >( row, 1 );
         bonusType = exdData->getField< uint8_t >( row, 3 );
         bonusValue = exdData->getField< uint16_t >( row, 4 );
      }

      Core::Data::GatheringPointBonusType::GatheringPointBonusType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringPointBonusTypeDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GatheringPointName::GatheringPointName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringPointNameDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::GatheringSubCategory::GatheringSubCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringSubCategoryDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 4 );
         folkloreBook = exdData->getField< std::string >( row, 5 );
      }

      Core::Data::GatheringType::GatheringType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GatheringTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         iconMain = exdData->getField< int32_t >( row, 1 );
         iconOff = exdData->getField< int32_t >( row, 2 );
      }

      Core::Data::GcArmyExpedition::GcArmyExpedition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::GcArmyExpeditionMemberBonus::GcArmyExpeditionMemberBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GcArmyExpeditionMemberBonusDat.get_row( row_id );
         race = exdData->getField< uint8_t >( row, 0 );
         classJob = exdData->getField< uint8_t >( row, 1 );
      }

      Core::Data::GcArmyExpeditionType::GcArmyExpeditionType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GcArmyExpeditionTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GcArmyMemberGrow::GcArmyMemberGrow( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GcArmyMemberGrowDat.get_row( row_id );
         classJob = exdData->getField< uint8_t >( row, 0 );
         classBook = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::GcArmyTraining::GcArmyTraining( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GcArmyTrainingDat.get_row( row_id );
         physicalBonus = exdData->getField< int8_t >( row, 0 );
         mentalBonus = exdData->getField< int8_t >( row, 1 );
         tacticalBonus = exdData->getField< int8_t >( row, 2 );
         experience = exdData->getField< uint32_t >( row, 3 );
         name = exdData->getField< std::string >( row, 4 );
         description = exdData->getField< std::string >( row, 5 );
      }

      Core::Data::GCScripShopCategory::GCScripShopCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GCScripShopCategoryDat.get_row( row_id );
         grandCompany = exdData->getField< int8_t >( row, 0 );
         tier = exdData->getField< int8_t >( row, 1 );
         subCategory = exdData->getField< int8_t >( row, 2 );
      }

      Core::Data::GCScripShopItem::GCScripShopItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GCScripShopItemDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         requiredGrandCompanyRank = exdData->getField< int32_t >( row, 1 );
         costGCSeals = exdData->getField< uint32_t >( row, 2 );
         sortKey = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::GCShop::GCShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GCShopDat.get_row( row_id );
         grandCompany = exdData->getField< int8_t >( row, 0 );
      }

      Core::Data::GCShopItemCategory::GCShopItemCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GCShopItemCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GCSupplyDuty::GCSupplyDuty( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GCSupplyDutyDat.get_row( row_id );
      }

      Core::Data::GCSupplyDutyReward::GCSupplyDutyReward( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GCSupplyDutyRewardDat.get_row( row_id );
         experienceSupply = exdData->getField< uint32_t >( row, 0 );
         experienceProvisioning = exdData->getField< uint32_t >( row, 1 );
         sealsExpertDelivery = exdData->getField< uint32_t >( row, 2 );
         sealsSupply = exdData->getField< uint32_t >( row, 3 );
         sealsProvisioning = exdData->getField< uint32_t >( row, 4 );
      }

      Core::Data::GeneralAction::GeneralAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GeneralActionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< int32_t >( row, 7 );
      }

      Core::Data::GilShop::GilShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GilShopDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GilShopItem::GilShopItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GilShopItemDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::GoldSaucerTextData::GoldSaucerTextData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GoldSaucerTextDataDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GrandCompany::GrandCompany( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GrandCompanyDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::GrandCompanyRank::GrandCompanyRank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::GuardianDeity::GuardianDeity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GuardianDeityDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::GuildleveAssignment::GuildleveAssignment( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GuildleveAssignmentDat.get_row( row_id );
         quest.push_back( exdData->getField< uint32_t >( row, 2 ) );
         quest.push_back( exdData->getField< uint32_t >( row, 3 ) );
      }

      Core::Data::GuildOrderGuide::GuildOrderGuide( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GuildOrderGuideDat.get_row( row_id );
      }

      Core::Data::GuildOrderOfficer::GuildOrderOfficer( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_GuildOrderOfficerDat.get_row( row_id );
      }

      Core::Data::HouseRetainerPose::HouseRetainerPose( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_HouseRetainerPoseDat.get_row( row_id );
         actionTimeline = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::HousingFurniture::HousingFurniture( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_HousingFurnitureDat.get_row( row_id );
         modelKey = exdData->getField< uint16_t >( row, 0 );
         housingItemCategory = exdData->getField< uint8_t >( row, 1 );
         usageType = exdData->getField< uint8_t >( row, 2 );
         usageParameter = exdData->getField< uint32_t >( row, 3 );
         housingLayoutLimit = exdData->getField< uint8_t >( row, 4 );
         event = exdData->getField< uint32_t >( row, 5 );
         item = exdData->getField< uint32_t >( row, 6 );
         destroyOnRemoval = exdData->getField< bool >( row, 7 );
      }

      Core::Data::HousingYardObject::HousingYardObject( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_HousingYardObjectDat.get_row( row_id );
         modelKey = exdData->getField< uint8_t >( row, 0 );
         housingItemCategory = exdData->getField< uint8_t >( row, 1 );
         usageType = exdData->getField< uint8_t >( row, 2 );
         usageParameter = exdData->getField< uint32_t >( row, 3 );
         housingLayoutLimit = exdData->getField< uint8_t >( row, 4 );
         event = exdData->getField< uint32_t >( row, 5 );
         item = exdData->getField< uint32_t >( row, 6 );
         destroyOnRemoval = exdData->getField< bool >( row, 7 );
      }

      Core::Data::InstanceContent::InstanceContent( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_InstanceContentDat.get_row( row_id );
         instanceContentType = exdData->getField< uint8_t >( row, 0 );
         weekRestriction = exdData->getField< uint8_t >( row, 1 );
         timeLimitmin = exdData->getField< uint16_t >( row, 2 );
         classJobLevelSync = exdData->getField< uint8_t >( row, 3 );
         name = exdData->getField< std::string >( row, 4 );
         bGM = exdData->getField< uint16_t >( row, 6 );
         itemLevelSync = exdData->getField< uint16_t >( row, 9 );
         territoryType = exdData->getField< uint32_t >( row, 11 );
         icon = exdData->getField< uint32_t >( row, 13 );
         instanceContentTextDataBossStart = exdData->getField< uint32_t >( row, 15 );
         instanceContentTextDataBossEnd = exdData->getField< uint32_t >( row, 16 );
         bNpcBaseBoss = exdData->getField< uint32_t >( row, 17 );
         instanceContentTextDataObjectiveStart = exdData->getField< uint32_t >( row, 18 );
         instanceContentTextDataObjectiveEnd = exdData->getField< uint32_t >( row, 19 );
         sortKey = exdData->getField< uint16_t >( row, 20 );
         newPlayerBonusA = exdData->getField< uint16_t >( row, 23 );
         newPlayerBonusB = exdData->getField< uint16_t >( row, 24 );
         finalBossCurrencyA = exdData->getField< uint16_t >( row, 26 );
         finalBossCurrencyB = exdData->getField< uint16_t >( row, 27 );
         finalBossCurrencyC = exdData->getField< uint16_t >( row, 28 );
         instanceContentBuff = exdData->getField< int32_t >( row, 54 );
         partyCondition = exdData->getField< uint8_t >( row, 58 );
      }

      Core::Data::InstanceContentBuff::InstanceContentBuff( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_InstanceContentBuffDat.get_row( row_id );
         echoStart = exdData->getField< uint16_t >( row, 0 );
         echoDeath = exdData->getField< uint16_t >( row, 1 );
      }

      Core::Data::InstanceContentTextData::InstanceContentTextData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_InstanceContentTextDataDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::InstanceContentType::InstanceContentType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_InstanceContentTypeDat.get_row( row_id );
         sortKey = exdData->getField< uint8_t >( row, 2 );
         contentType = exdData->getField< uint8_t >( row, 4 );
      }

      Core::Data::Item::Item( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ItemDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
         startsWithVowel = exdData->getField< int8_t >( row, 4 );
         description = exdData->getField< std::string >( row, 8 );
         name = exdData->getField< std::string >( row, 9 );
         icon = exdData->getField< uint16_t >( row, 10 );
         levelItem = exdData->getField< uint16_t >( row, 11 );
         rarity = exdData->getField< uint8_t >( row, 12 );
         filterGroup = exdData->getField< uint8_t >( row, 13 );
         stain = exdData->getField< uint32_t >( row, 14 );
         itemUICategory = exdData->getField< uint8_t >( row, 15 );
         itemSearchCategory = exdData->getField< uint8_t >( row, 16 );
         equipSlotCategory = exdData->getField< uint8_t >( row, 17 );
         stackSize = exdData->getField< uint32_t >( row, 19 );
         isUnique = exdData->getField< bool >( row, 20 );
         isUntradable = exdData->getField< bool >( row, 21 );
         isIndisposable = exdData->getField< bool >( row, 22 );
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
      }

      Core::Data::ItemAction::ItemAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::ItemFood::ItemFood( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ItemFoodDat.get_row( row_id );
      }

      Core::Data::ItemSearchCategory::ItemSearchCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ItemSearchCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
         category = exdData->getField< uint8_t >( row, 2 );
         order = exdData->getField< uint8_t >( row, 3 );
         classJob = exdData->getField< int8_t >( row, 4 );
      }

      Core::Data::ItemSeries::ItemSeries( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ItemSeriesDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ItemSpecialBonus::ItemSpecialBonus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ItemSpecialBonusDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ItemUICategory::ItemUICategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ItemUICategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
         orderMinor = exdData->getField< uint8_t >( row, 2 );
         orderMajor = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::JournalCategory::JournalCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_JournalCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         journalSection = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::JournalGenre::JournalGenre( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_JournalGenreDat.get_row( row_id );
         icon = exdData->getField< int32_t >( row, 0 );
         journalCategory = exdData->getField< uint8_t >( row, 1 );
         name = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::JournalSection::JournalSection( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_JournalSectionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Leve::Leve( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
         journalCategory = exdData->getField< int32_t >( row, 13 );
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

      Core::Data::LeveAssignmentType::LeveAssignmentType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LeveAssignmentTypeDat.get_row( row_id );
         isFaction = exdData->getField< bool >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
         name = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::LeveClient::LeveClient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LeveClientDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Level::Level( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LevelDat.get_row( row_id );
         x = exdData->getField< float >( row, 0 );
         y = exdData->getField< float >( row, 1 );
         z = exdData->getField< float >( row, 2 );
         yaw = exdData->getField< float >( row, 3 );
         radius = exdData->getField< float >( row, 4 );
         type = exdData->getField< uint8_t >( row, 5 );
         objectKey = exdData->getField< uint32_t >( row, 6 );
         map = exdData->getField< uint16_t >( row, 7 );
         territory = exdData->getField< uint16_t >( row, 9 );
      }

      Core::Data::LeveRewardItem::LeveRewardItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LeveRewardItemDat.get_row( row_id );
      }

      Core::Data::LeveRewardItemGroup::LeveRewardItemGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LeveRewardItemGroupDat.get_row( row_id );
      }

      Core::Data::LeveVfx::LeveVfx( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LeveVfxDat.get_row( row_id );
         effect = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::LogFilter::LogFilter( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LogFilterDat.get_row( row_id );
         logKind = exdData->getField< uint16_t >( row, 1 );
         name = exdData->getField< std::string >( row, 6 );
         example = exdData->getField< std::string >( row, 7 );
      }

      Core::Data::LogKind::LogKind( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LogKindDat.get_row( row_id );
         format = exdData->getField< std::string >( row, 1 );
         name = exdData->getField< std::string >( row, 2 );
         example = exdData->getField< std::string >( row, 3 );
         logKindCategoryText = exdData->getField< uint8_t >( row, 4 );
      }

      Core::Data::LogKindCategoryText::LogKindCategoryText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LogKindCategoryTextDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::LogMessage::LogMessage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_LogMessageDat.get_row( row_id );
         logKind = exdData->getField< uint16_t >( row, 0 );
         text = exdData->getField< std::string >( row, 4 );
      }

      Core::Data::MacroIcon::MacroIcon( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MacroIconDat.get_row( row_id );
         icon = exdData->getField< int32_t >( row, 0 );
      }

      Core::Data::MacroIconRedirectOld::MacroIconRedirectOld( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MacroIconRedirectOldDat.get_row( row_id );
         iconOld = exdData->getField< uint32_t >( row, 0 );
         iconNew = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::MainCommand::MainCommand( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MainCommandDat.get_row( row_id );
         icon = exdData->getField< int32_t >( row, 0 );
         mainCommandCategory = exdData->getField< uint8_t >( row, 2 );
         name = exdData->getField< std::string >( row, 4 );
         description = exdData->getField< std::string >( row, 5 );
      }

      Core::Data::MainCommandCategory::MainCommandCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MainCommandCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::Map::Map( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
         territoryType = exdData->getField< uint16_t >( row, 14 );
      }

      Core::Data::MapMarker::MapMarker( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MapMarkerDat.get_row( row_id );
         x = exdData->getField< int16_t >( row, 0 );
         y = exdData->getField< int16_t >( row, 1 );
         icon = exdData->getField< uint16_t >( row, 2 );
         placeNameSubtext = exdData->getField< uint16_t >( row, 3 );
         subtextOrientation = exdData->getField< uint8_t >( row, 4 );
         type = exdData->getField< uint8_t >( row, 6 );
         dataType = exdData->getField< uint8_t >( row, 7 );
         dataKey = exdData->getField< uint16_t >( row, 8 );
      }

      Core::Data::MapSymbol::MapSymbol( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MapSymbolDat.get_row( row_id );
         icon = exdData->getField< int32_t >( row, 0 );
         placeName = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::MasterpieceSupplyDuty::MasterpieceSupplyDuty( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MasterpieceSupplyDutyDat.get_row( row_id );
         classJob = exdData->getField< uint8_t >( row, 0 );
         classJobLevel = exdData->getField< uint8_t >( row, 1 );
         rewardCurrency = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::MasterpieceSupplyMultiplier::MasterpieceSupplyMultiplier( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MasterpieceSupplyMultiplierDat.get_row( row_id );
         xpMultiplier.push_back( exdData->getField< uint16_t >( row, 0 ) );
         xpMultiplier.push_back( exdData->getField< uint16_t >( row, 1 ) );
         currencyMultiplier.push_back( exdData->getField< uint16_t >( row, 4 ) );
         currencyMultiplier.push_back( exdData->getField< uint16_t >( row, 5 ) );
      }

      Core::Data::Materia::Materia( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::MinionRace::MinionRace( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MinionRaceDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::MinionRules::MinionRules( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MinionRulesDat.get_row( row_id );
         rule = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::MinionSkillType::MinionSkillType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MinionSkillTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::MobHuntTarget::MobHuntTarget( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MobHuntTargetDat.get_row( row_id );
         name = exdData->getField< uint16_t >( row, 0 );
         fATE = exdData->getField< uint16_t >( row, 1 );
         icon = exdData->getField< uint32_t >( row, 2 );
         territoryType = exdData->getField< uint16_t >( row, 3 );
         placeName = exdData->getField< uint16_t >( row, 4 );
      }

      Core::Data::ModelChara::ModelChara( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ModelCharaDat.get_row( row_id );
         type = exdData->getField< uint8_t >( row, 0 );
         model = exdData->getField< uint16_t >( row, 1 );
         base = exdData->getField< uint8_t >( row, 2 );
         variant = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::MonsterNote::MonsterNote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::MonsterNoteTarget::MonsterNoteTarget( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MonsterNoteTargetDat.get_row( row_id );
         bNpcName = exdData->getField< uint16_t >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::Mount::Mount( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MountDat.get_row( row_id );
         singular = exdData->getField< std::string >( row, 0 );
         plural = exdData->getField< std::string >( row, 2 );
         flyingCondition = exdData->getField< uint8_t >( row, 10 );
         isFlying = exdData->getField< uint8_t >( row, 14 );
         rideBGM = exdData->getField< uint16_t >( row, 28 );
         icon = exdData->getField< uint16_t >( row, 41 );
      }

      Core::Data::MountAction::MountAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_MountActionDat.get_row( row_id );
         action.push_back( exdData->getField< uint16_t >( row, 0 ) );
         action.push_back( exdData->getField< uint16_t >( row, 1 ) );
         action.push_back( exdData->getField< uint16_t >( row, 2 ) );
         action.push_back( exdData->getField< uint16_t >( row, 3 ) );
         action.push_back( exdData->getField< uint16_t >( row, 4 ) );
         action.push_back( exdData->getField< uint16_t >( row, 5 ) );
      }

      Core::Data::NpcEquip::NpcEquip( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::Omen::Omen( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_OmenDat.get_row( row_id );
         fileName = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::OnlineStatus::OnlineStatus( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_OnlineStatusDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 2 );
         icon = exdData->getField< uint32_t >( row, 3 );
      }

      Core::Data::Orchestrion::Orchestrion( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_OrchestrionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::OrchestrionPath::OrchestrionPath( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_OrchestrionPathDat.get_row( row_id );
         file = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::ParamGrow::ParamGrow( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::Pet::Pet( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_PetDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::PetAction::PetAction( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_PetActionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         action = exdData->getField< uint16_t >( row, 3 );
         pet = exdData->getField< uint8_t >( row, 4 );
      }

      Core::Data::Picture::Picture( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_PictureDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         image = exdData->getField< int32_t >( row, 1 );
         signature = exdData->getField< int32_t >( row, 2 );
      }

      Core::Data::PlaceName::PlaceName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_PlaceNameDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         nameNoArticle = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::Quest::Quest( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_QuestDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         id = exdData->getField< std::string >( row, 1 );
         expansion = exdData->getField< uint8_t >( row, 2 );
         classJobCategory0 = exdData->getField< uint8_t >( row, 3 );
         classJobLevel0 = exdData->getField< uint16_t >( row, 4 );
         questLevelOffset = exdData->getField< uint8_t >( row, 5 );
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
         level.push_back( exdData->getField< uint32_t >( row, 1221 ) );
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
         classJobRequired = exdData->getField< uint8_t >( row, 1437 );
         expFactor = exdData->getField< uint16_t >( row, 1439 );
         gilReward = exdData->getField< uint32_t >( row, 1440 );
         gCSeals = exdData->getField< uint16_t >( row, 1442 );
         itemCatalyst.push_back( exdData->getField< uint8_t >( row, 1443 ) );
         itemCatalyst.push_back( exdData->getField< uint8_t >( row, 1444 ) );
         itemCatalyst.push_back( exdData->getField< uint8_t >( row, 1445 ) );
         itemCountCatalyst.push_back( exdData->getField< uint8_t >( row, 1446 ) );
         itemCountCatalyst.push_back( exdData->getField< uint8_t >( row, 1447 ) );
         itemCountCatalyst.push_back( exdData->getField< uint8_t >( row, 1448 ) );
         itemRewardType = exdData->getField< uint8_t >( row, 1449 );
         itemReward0.push_back( exdData->getField< uint32_t >( row, 1450 ) );
         itemReward0.push_back( exdData->getField< uint32_t >( row, 1451 ) );
         itemReward0.push_back( exdData->getField< uint32_t >( row, 1452 ) );
         itemReward0.push_back( exdData->getField< uint32_t >( row, 1453 ) );
         itemReward0.push_back( exdData->getField< uint32_t >( row, 1454 ) );
         itemReward0.push_back( exdData->getField< uint32_t >( row, 1455 ) );
         itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1457 ) );
         itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1458 ) );
         itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1459 ) );
         itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1460 ) );
         itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1461 ) );
         itemCountReward0.push_back( exdData->getField< uint8_t >( row, 1462 ) );
         stainReward0.push_back( exdData->getField< uint8_t >( row, 1464 ) );
         stainReward0.push_back( exdData->getField< uint8_t >( row, 1465 ) );
         stainReward0.push_back( exdData->getField< uint8_t >( row, 1466 ) );
         stainReward0.push_back( exdData->getField< uint8_t >( row, 1467 ) );
         stainReward0.push_back( exdData->getField< uint8_t >( row, 1468 ) );
         stainReward0.push_back( exdData->getField< uint8_t >( row, 1469 ) );
         itemReward1.push_back( exdData->getField< uint32_t >( row, 1471 ) );
         itemReward1.push_back( exdData->getField< uint32_t >( row, 1472 ) );
         itemReward1.push_back( exdData->getField< uint32_t >( row, 1473 ) );
         itemReward1.push_back( exdData->getField< uint32_t >( row, 1474 ) );
         itemReward1.push_back( exdData->getField< uint32_t >( row, 1475 ) );
         itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1476 ) );
         itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1477 ) );
         itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1478 ) );
         itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1479 ) );
         itemCountReward1.push_back( exdData->getField< uint8_t >( row, 1480 ) );
         isHQReward1.push_back( exdData->getField< bool >( row, 1481 ) );
         isHQReward1.push_back( exdData->getField< bool >( row, 1482 ) );
         isHQReward1.push_back( exdData->getField< bool >( row, 1483 ) );
         isHQReward1.push_back( exdData->getField< bool >( row, 1484 ) );
         isHQReward1.push_back( exdData->getField< bool >( row, 1485 ) );
         stainReward1.push_back( exdData->getField< uint8_t >( row, 1486 ) );
         stainReward1.push_back( exdData->getField< uint8_t >( row, 1487 ) );
         stainReward1.push_back( exdData->getField< uint8_t >( row, 1488 ) );
         stainReward1.push_back( exdData->getField< uint8_t >( row, 1489 ) );
         stainReward1.push_back( exdData->getField< uint8_t >( row, 1490 ) );
         emoteReward = exdData->getField< uint8_t >( row, 1491 );
         actionReward = exdData->getField< uint16_t >( row, 1492 );
         generalActionReward.push_back( exdData->getField< uint8_t >( row, 1493 ) );
         generalActionReward.push_back( exdData->getField< uint8_t >( row, 1494 ) );
         otherReward = exdData->getField< uint8_t >( row, 1496 );
         instanceContentUnlock = exdData->getField< uint32_t >( row, 1499 );
         tomestoneReward = exdData->getField< uint8_t >( row, 1501 );
         tomestoneCountReward = exdData->getField< uint8_t >( row, 1502 );
         reputationReward = exdData->getField< uint8_t >( row, 1503 );
         placeName = exdData->getField< uint16_t >( row, 1504 );
         journalGenre = exdData->getField< uint8_t >( row, 1505 );
         icon = exdData->getField< uint32_t >( row, 1507 );
         iconSpecial = exdData->getField< uint32_t >( row, 1508 );
         eventIconType = exdData->getField< uint8_t >( row, 1511 );
         sortKey = exdData->getField< uint16_t >( row, 1513 );
      }

      Core::Data::QuestRewardOther::QuestRewardOther( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_QuestRewardOtherDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::Race::Race( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::RacingChocoboItem::RacingChocoboItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RacingChocoboItemDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         category = exdData->getField< uint8_t >( row, 1 );
         param.push_back( exdData->getField< uint8_t >( row, 2 ) );
         param.push_back( exdData->getField< uint8_t >( row, 3 ) );
      }

      Core::Data::RacingChocoboName::RacingChocoboName( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RacingChocoboNameDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::RacingChocoboNameCategory::RacingChocoboNameCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RacingChocoboNameCategoryDat.get_row( row_id );
         sortKey = exdData->getField< uint8_t >( row, 0 );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::RacingChocoboNameInfo::RacingChocoboNameInfo( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RacingChocoboNameInfoDat.get_row( row_id );
         racingChocoboNameCategory = exdData->getField< uint8_t >( row, 0 );
      }

      Core::Data::RacingChocoboParam::RacingChocoboParam( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RacingChocoboParamDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Recipe::Recipe( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
         statusRequired = exdData->getField< int32_t >( row, 40 );
         itemRequired = exdData->getField< int32_t >( row, 41 );
         isSpecializationRequired = exdData->getField< bool >( row, 42 );
      }

      Core::Data::RecipeElement::RecipeElement( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RecipeElementDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::RecipeLevelTable::RecipeLevelTable( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RecipeLevelTableDat.get_row( row_id );
         classJobLevel = exdData->getField< uint8_t >( row, 0 );
         stars = exdData->getField< uint8_t >( row, 1 );
         difficulty = exdData->getField< uint16_t >( row, 2 );
         quality = exdData->getField< int16_t >( row, 3 );
         durability = exdData->getField< uint16_t >( row, 4 );
      }

      Core::Data::RecipeNotebookList::RecipeNotebookList( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::Relic::Relic( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RelicDat.get_row( row_id );
         itemAtma = exdData->getField< uint32_t >( row, 0 );
         itemAnimus = exdData->getField< uint32_t >( row, 1 );
         icon = exdData->getField< int32_t >( row, 2 );
      }

      Core::Data::Relic3::Relic3( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_Relic3Dat.get_row( row_id );
         itemAnimus = exdData->getField< uint32_t >( row, 0 );
         itemScroll = exdData->getField< uint32_t >( row, 1 );
         materiaLimit = exdData->getField< uint8_t >( row, 2 );
         itemNovus = exdData->getField< uint32_t >( row, 3 );
         icon = exdData->getField< int32_t >( row, 4 );
      }

      Core::Data::RelicItem::RelicItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::RelicNote::RelicNote( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::RelicNoteCategory::RelicNoteCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RelicNoteCategoryDat.get_row( row_id );
         text = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::RetainerTask::RetainerTask( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::RetainerTaskNormal::RetainerTaskNormal( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RetainerTaskNormalDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         quantity0 = exdData->getField< uint8_t >( row, 1 );
         quantity1 = exdData->getField< uint8_t >( row, 2 );
         quantity2 = exdData->getField< uint8_t >( row, 3 );
      }

      Core::Data::RetainerTaskParameter::RetainerTaskParameter( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RetainerTaskParameterDat.get_row( row_id );
         itemLevelDoW.push_back( exdData->getField< int16_t >( row, 0 ) );
         itemLevelDoW.push_back( exdData->getField< int16_t >( row, 1 ) );
         gatheringDoL.push_back( exdData->getField< int16_t >( row, 2 ) );
         gatheringDoL.push_back( exdData->getField< int16_t >( row, 3 ) );
         gatheringFSH.push_back( exdData->getField< int16_t >( row, 4 ) );
         gatheringFSH.push_back( exdData->getField< int16_t >( row, 5 ) );
      }

      Core::Data::RetainerTaskRandom::RetainerTaskRandom( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_RetainerTaskRandomDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         requirement = exdData->getField< int16_t >( row, 1 );
      }

      Core::Data::Salvage::Salvage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_SalvageDat.get_row( row_id );
         optimalSkill = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::SatisfactionNpc::SatisfactionNpc( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::SatisfactionSupply::SatisfactionSupply( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_SatisfactionSupplyDat.get_row( row_id );
         slot = exdData->getField< uint8_t >( row, 0 );
         probability = exdData->getField< uint8_t >( row, 1 );
         item = exdData->getField< int32_t >( row, 2 );
         collectabilityLow = exdData->getField< uint16_t >( row, 3 );
         collectabilityMid = exdData->getField< uint16_t >( row, 4 );
         collectabilityHigh = exdData->getField< uint16_t >( row, 5 );
         reward = exdData->getField< uint16_t >( row, 6 );
      }

      Core::Data::SatisfactionSupplyReward::SatisfactionSupplyReward( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_SatisfactionSupplyRewardDat.get_row( row_id );
         satisfactionLow = exdData->getField< uint16_t >( row, 10 );
         satisfactionMid = exdData->getField< uint16_t >( row, 11 );
         satisfactionHigh = exdData->getField< uint16_t >( row, 12 );
         gilLow = exdData->getField< uint16_t >( row, 13 );
         gilMid = exdData->getField< uint16_t >( row, 14 );
         gilHigh = exdData->getField< uint16_t >( row, 15 );
      }

      Core::Data::ScreenImage::ScreenImage( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_ScreenImageDat.get_row( row_id );
         image = exdData->getField< uint32_t >( row, 0 );
      }

      Core::Data::SecretRecipeBook::SecretRecipeBook( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_SecretRecipeBookDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         name = exdData->getField< std::string >( row, 1 );
      }

      Core::Data::SpearfishingItem::SpearfishingItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_SpearfishingItemDat.get_row( row_id );
         description = exdData->getField< std::string >( row, 0 );
         item = exdData->getField< int32_t >( row, 1 );
         gatheringItemLevel = exdData->getField< uint16_t >( row, 2 );
         territoryType = exdData->getField< uint16_t >( row, 4 );
         isVisible = exdData->getField< bool >( row, 5 );
      }

      Core::Data::SpearfishingNotebook::SpearfishingNotebook( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::SpecialShop::SpecialShop( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
         questShop = exdData->getField< int32_t >( row, 1863 );
      }

      Core::Data::SpecialShopItemCategory::SpecialShopItemCategory( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_SpecialShopItemCategoryDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Stain::Stain( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_StainDat.get_row( row_id );
         color = exdData->getField< uint32_t >( row, 0 );
         shade = exdData->getField< uint8_t >( row, 1 );
         name = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::Status::Status( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_StatusDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         description = exdData->getField< std::string >( row, 1 );
         icon = exdData->getField< uint16_t >( row, 2 );
         maxStacks = exdData->getField< uint8_t >( row, 3 );
         lockMovement = exdData->getField< bool >( row, 7 );
         lockActions = exdData->getField< bool >( row, 9 );
         lockControl = exdData->getField< bool >( row, 10 );
         transfiguration = exdData->getField< bool >( row, 11 );
         canDispel = exdData->getField< bool >( row, 13 );
         isPermanent = exdData->getField< bool >( row, 15 );
         inflictedByActor = exdData->getField< bool >( row, 17 );
         isFcBuff = exdData->getField< bool >( row, 21 );
         invisibility = exdData->getField< bool >( row, 22 );
      }

      Core::Data::Story::Story( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_StoryDat.get_row( row_id );
      }

      Core::Data::SwitchTalk::SwitchTalk( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::TerritoryType::TerritoryType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TerritoryTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         bg = exdData->getField< std::string >( row, 1 );
         placeNameRegion = exdData->getField< uint16_t >( row, 3 );
         placeNameZone = exdData->getField< uint16_t >( row, 4 );
         placeName = exdData->getField< uint16_t >( row, 5 );
         map = exdData->getField< uint16_t >( row, 6 );
         weatherRate = exdData->getField< uint8_t >( row, 12 );
         aetheryte = exdData->getField< int32_t >( row, 23 );
      }

      Core::Data::TextCommand::TextCommand( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TextCommandDat.get_row( row_id );
         command = exdData->getField< std::string >( row, 5 );
         shortCommand = exdData->getField< std::string >( row, 6 );
         description = exdData->getField< std::string >( row, 7 );
         alias = exdData->getField< std::string >( row, 8 );
         shortAlias = exdData->getField< std::string >( row, 9 );
      }

      Core::Data::Title::Title( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TitleDat.get_row( row_id );
         masculine = exdData->getField< std::string >( row, 0 );
         feminine = exdData->getField< std::string >( row, 1 );
         isPrefix = exdData->getField< bool >( row, 2 );
      }

      Core::Data::Tomestones::Tomestones( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TomestonesDat.get_row( row_id );
         weeklyLimit = exdData->getField< uint16_t >( row, 0 );
      }

      Core::Data::TomestonesItem::TomestonesItem( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TomestonesItemDat.get_row( row_id );
         item = exdData->getField< int32_t >( row, 0 );
         tomestones = exdData->getField< int32_t >( row, 2 );
      }

      Core::Data::TopicSelect::TopicSelect( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TopicSelectDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Town::Town( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TownDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::Trait::Trait( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TraitDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         icon = exdData->getField< int32_t >( row, 1 );
         classJob = exdData->getField< uint8_t >( row, 2 );
         level = exdData->getField< uint8_t >( row, 3 );
         value = exdData->getField< int16_t >( row, 5 );
         classJobCategory = exdData->getField< uint8_t >( row, 6 );
      }

      Core::Data::TraitRecast::TraitRecast( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TraitRecastDat.get_row( row_id );
         trait = exdData->getField< uint16_t >( row, 0 );
         action = exdData->getField< uint16_t >( row, 1 );
         timeds = exdData->getField< uint16_t >( row, 2 );
      }

      Core::Data::TraitTransient::TraitTransient( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TraitTransientDat.get_row( row_id );
         description = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Tribe::Tribe( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::TripleTriad::TripleTriad( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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
      }

      Core::Data::TripleTriadCard::TripleTriadCard( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TripleTriadCardDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
         startsWithVowel = exdData->getField< int8_t >( row, 4 );
         description = exdData->getField< std::string >( row, 8 );
      }

      Core::Data::TripleTriadCardRarity::TripleTriadCardRarity( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TripleTriadCardRarityDat.get_row( row_id );
         stars = exdData->getField< uint8_t >( row, 0 );
      }

      Core::Data::TripleTriadCardResident::TripleTriadCardResident( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
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

      Core::Data::TripleTriadCardType::TripleTriadCardType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TripleTriadCardTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::TripleTriadCompetition::TripleTriadCompetition( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TripleTriadCompetitionDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::TripleTriadRule::TripleTriadRule( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TripleTriadRuleDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::Tutorial::Tutorial( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TutorialDat.get_row( row_id );
         exp = exdData->getField< uint32_t >( row, 4 );
         gil = exdData->getField< uint32_t >( row, 5 );
         rewardTank = exdData->getField< uint32_t >( row, 6 );
         rewardMelee = exdData->getField< uint32_t >( row, 7 );
         rewardRanged = exdData->getField< uint32_t >( row, 8 );
         objective = exdData->getField< uint32_t >( row, 9 );
      }

      Core::Data::TutorialDPS::TutorialDPS( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TutorialDPSDat.get_row( row_id );
         objective = exdData->getField< uint8_t >( row, 0 );
      }

      Core::Data::TutorialHealer::TutorialHealer( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TutorialHealerDat.get_row( row_id );
         objective = exdData->getField< uint8_t >( row, 0 );
      }

      Core::Data::TutorialTank::TutorialTank( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_TutorialTankDat.get_row( row_id );
         objective = exdData->getField< uint8_t >( row, 0 );
      }

      Core::Data::Warp::Warp( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WarpDat.get_row( row_id );
         level = exdData->getField< uint32_t >( row, 0 );
         placeName = exdData->getField< uint16_t >( row, 1 );
         defaultTalk1 = exdData->getField< uint32_t >( row, 2 );
         defaultTalk2 = exdData->getField< uint32_t >( row, 3 );
         defaultTalk3 = exdData->getField< uint32_t >( row, 4 );
         warpCondition = exdData->getField< uint16_t >( row, 5 );
         warpLogic = exdData->getField< uint16_t >( row, 6 );
      }

      Core::Data::Weather::Weather( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WeatherDat.get_row( row_id );
         icon = exdData->getField< int32_t >( row, 0 );
         name = exdData->getField< std::string >( row, 1 );
         description = exdData->getField< std::string >( row, 2 );
      }

      Core::Data::WeatherGroup::WeatherGroup( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WeatherGroupDat.get_row( row_id );
         weatherRate = exdData->getField< int32_t >( row, 1 );
      }

      Core::Data::WeatherRate::WeatherRate( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WeatherRateDat.get_row( row_id );
      }

      Core::Data::WeeklyBingoOrderData::WeeklyBingoOrderData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WeeklyBingoOrderDataDat.get_row( row_id );
         data = exdData->getField< uint32_t >( row, 1 );
         text = exdData->getField< uint8_t >( row, 3 );
         icon = exdData->getField< uint32_t >( row, 4 );
      }

      Core::Data::WeeklyBingoRewardData::WeeklyBingoRewardData( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WeeklyBingoRewardDataDat.get_row( row_id );
         rewardItem2 = exdData->getField< uint32_t >( row, 10 );
         rewardHQ2 = exdData->getField< bool >( row, 11 );
         rewardQuantity2 = exdData->getField< uint16_t >( row, 12 );
      }

      Core::Data::WeeklyBingoText::WeeklyBingoText( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WeeklyBingoTextDat.get_row( row_id );
         description = exdData->getField< std::string >( row, 0 );
      }

      Core::Data::WorldDCGroupType::WorldDCGroupType( uint32_t row_id, Core::Data::ExdDataGenerated* exdData )
      {
         auto row = exdData->m_WorldDCGroupTypeDat.get_row( row_id );
         name = exdData->getField< std::string >( row, 0 );
      }


Core::Data::ExdDataGenerated::ExdDataGenerated()
{
}

Core::Data::ExdDataGenerated::~ExdDataGenerated()
{
}

xiv::exd::Exd Core::Data::ExdDataGenerated::setupDatAccess( const std::string& name, xiv::exd::Language lang )
{
   auto& cat = m_exd_data->get_category( name );
   return static_cast< xiv::exd::Exd >( cat.get_data_ln( lang ) );
};


void Core::Data::ExdDataGenerated::loadIdList( xiv::exd::Exd& data, std::set< uint32_t >& outIdList )
{
   auto pDataRows = data.get_rows();

   for( auto row : pDataRows )
   {
      uint32_t id = row.first;
      outIdList.insert( id );
   }
}

bool Core::Data::ExdDataGenerated::init( const std::string& path )
{
   try
   {
      m_data = boost::make_shared< xiv::dat::GameData >( path );
      m_exd_data = boost::make_shared< xiv::exd::ExdData >( *m_data );

      m_AchievementDat = setupDatAccess( "Achievement", xiv::exd::Language::en );
      m_AchievementCategoryDat = setupDatAccess( "AchievementCategory", xiv::exd::Language::en );
      m_AchievementKindDat = setupDatAccess( "AchievementKind", xiv::exd::Language::en );
      m_ActionDat = setupDatAccess( "Action", xiv::exd::Language::en );
      m_ActionCategoryDat = setupDatAccess( "ActionCategory", xiv::exd::Language::en );
      m_ActionComboRouteDat = setupDatAccess( "ActionComboRoute", xiv::exd::Language::en );
      m_ActionIndirectionDat = setupDatAccess( "ActionIndirection", xiv::exd::Language::none );
      m_ActionProcStatusDat = setupDatAccess( "ActionProcStatus", xiv::exd::Language::none );
      m_ActionTimelineDat = setupDatAccess( "ActionTimeline", xiv::exd::Language::none );
      m_ActionTransientDat = setupDatAccess( "ActionTransient", xiv::exd::Language::en );
      m_AddonDat = setupDatAccess( "Addon", xiv::exd::Language::en );
      m_AdventureDat = setupDatAccess( "Adventure", xiv::exd::Language::en );
      m_AdventureExPhaseDat = setupDatAccess( "AdventureExPhase", xiv::exd::Language::none );
      m_AetherCurrentDat = setupDatAccess( "AetherCurrent", xiv::exd::Language::none );
      m_AetherialWheelDat = setupDatAccess( "AetherialWheel", xiv::exd::Language::none );
      m_AetheryteDat = setupDatAccess( "Aetheryte", xiv::exd::Language::en );
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
      m_AttackTypeDat = setupDatAccess( "AttackType", xiv::exd::Language::en );
      m_BalloonDat = setupDatAccess( "Balloon", xiv::exd::Language::en );
      m_BaseParamDat = setupDatAccess( "BaseParam", xiv::exd::Language::en );
      m_BattleLeveDat = setupDatAccess( "BattleLeve", xiv::exd::Language::none );
      m_BeastRankBonusDat = setupDatAccess( "BeastRankBonus", xiv::exd::Language::none );
      m_BeastReputationRankDat = setupDatAccess( "BeastReputationRank", xiv::exd::Language::en );
      m_BeastTribeDat = setupDatAccess( "BeastTribe", xiv::exd::Language::en );
      m_BehaviorDat = setupDatAccess( "Behavior", xiv::exd::Language::none );
      m_BGMDat = setupDatAccess( "BGM", xiv::exd::Language::none );
      m_BNpcAnnounceIconDat = setupDatAccess( "BNpcAnnounceIcon", xiv::exd::Language::none );
      m_BNpcBaseDat = setupDatAccess( "BNpcBase", xiv::exd::Language::none );
      m_BNpcCustomizeDat = setupDatAccess( "BNpcCustomize", xiv::exd::Language::none );
      m_BNpcNameDat = setupDatAccess( "BNpcName", xiv::exd::Language::en );
      m_BuddyActionDat = setupDatAccess( "BuddyAction", xiv::exd::Language::en );
      m_BuddyEquipDat = setupDatAccess( "BuddyEquip", xiv::exd::Language::en );
      m_BuddyItemDat = setupDatAccess( "BuddyItem", xiv::exd::Language::none );
      m_BuddyRankDat = setupDatAccess( "BuddyRank", xiv::exd::Language::none );
      m_BuddySkillDat = setupDatAccess( "BuddySkill", xiv::exd::Language::none );
      m_CabinetDat = setupDatAccess( "Cabinet", xiv::exd::Language::none );
      m_CabinetCategoryDat = setupDatAccess( "CabinetCategory", xiv::exd::Language::none );
      m_CalendarDat = setupDatAccess( "Calendar", xiv::exd::Language::none );
      m_ChainBonusDat = setupDatAccess( "ChainBonus", xiv::exd::Language::none );
      m_CharaMakeCustomizeDat = setupDatAccess( "CharaMakeCustomize", xiv::exd::Language::none );
      m_CharaMakeTypeDat = setupDatAccess( "CharaMakeType", xiv::exd::Language::en );
      m_ChocoboRaceDat = setupDatAccess( "ChocoboRace", xiv::exd::Language::none );
      m_ChocoboRaceAbilityDat = setupDatAccess( "ChocoboRaceAbility", xiv::exd::Language::en );
      m_ChocoboRaceAbilityTypeDat = setupDatAccess( "ChocoboRaceAbilityType", xiv::exd::Language::none );
      m_ChocoboRaceItemDat = setupDatAccess( "ChocoboRaceItem", xiv::exd::Language::en );
      m_ChocoboRaceRankDat = setupDatAccess( "ChocoboRaceRank", xiv::exd::Language::none );
      m_ChocoboRaceStatusDat = setupDatAccess( "ChocoboRaceStatus", xiv::exd::Language::none );
      m_ChocoboRaceTerritoryDat = setupDatAccess( "ChocoboRaceTerritory", xiv::exd::Language::none );
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
      m_ContentExActionDat = setupDatAccess( "ContentExAction", xiv::exd::Language::none );
      m_ContentFinderConditionDat = setupDatAccess( "ContentFinderCondition", xiv::exd::Language::en );
      m_ContentFinderConditionTransientDat = setupDatAccess( "ContentFinderConditionTransient", xiv::exd::Language::en );
      m_ContentMemberTypeDat = setupDatAccess( "ContentMemberType", xiv::exd::Language::none );
      m_ContentRouletteDat = setupDatAccess( "ContentRoulette", xiv::exd::Language::en );
      m_ContentTypeDat = setupDatAccess( "ContentType", xiv::exd::Language::en );
      m_CraftActionDat = setupDatAccess( "CraftAction", xiv::exd::Language::en );
      m_CraftLeveDat = setupDatAccess( "CraftLeve", xiv::exd::Language::none );
      m_CraftTypeDat = setupDatAccess( "CraftType", xiv::exd::Language::en );
      m_CurrencyDat = setupDatAccess( "Currency", xiv::exd::Language::none );
      m_CustomTalkDat = setupDatAccess( "CustomTalk", xiv::exd::Language::en );
      m_CutsceneDat = setupDatAccess( "Cutscene", xiv::exd::Language::none );
      m_CutScreenImageDat = setupDatAccess( "CutScreenImage", xiv::exd::Language::none );
      m_DailySupplyItemDat = setupDatAccess( "DailySupplyItem", xiv::exd::Language::none );
      m_DeepDungeonBanDat = setupDatAccess( "DeepDungeonBan", xiv::exd::Language::none );
      m_DeepDungeonDangerDat = setupDatAccess( "DeepDungeonDanger", xiv::exd::Language::none );
      m_DeepDungeonEquipmentDat = setupDatAccess( "DeepDungeonEquipment", xiv::exd::Language::en );
      m_DeepDungeonFloorEffectUIDat = setupDatAccess( "DeepDungeonFloorEffectUI", xiv::exd::Language::en );
      m_DeepDungeonItemDat = setupDatAccess( "DeepDungeonItem", xiv::exd::Language::en );
      m_DeepDungeonStatusDat = setupDatAccess( "DeepDungeonStatus", xiv::exd::Language::none );
      m_DefaultTalkDat = setupDatAccess( "DefaultTalk", xiv::exd::Language::en );
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
      m_EquipRaceCategoryDat = setupDatAccess( "EquipRaceCategory", xiv::exd::Language::none );
      m_EquipSlotCategoryDat = setupDatAccess( "EquipSlotCategory", xiv::exd::Language::none );
      m_EventActionDat = setupDatAccess( "EventAction", xiv::exd::Language::en );
      m_EventIconPriorityDat = setupDatAccess( "EventIconPriority", xiv::exd::Language::none );
      m_EventIconTypeDat = setupDatAccess( "EventIconType", xiv::exd::Language::none );
      m_EventItemDat = setupDatAccess( "EventItem", xiv::exd::Language::en );
      m_EventItemHelpDat = setupDatAccess( "EventItemHelp", xiv::exd::Language::en );
      m_ExVersionDat = setupDatAccess( "ExVersion", xiv::exd::Language::en );
      m_FateDat = setupDatAccess( "Fate", xiv::exd::Language::en );
      m_FCActivityDat = setupDatAccess( "FCActivity", xiv::exd::Language::en );
      m_FCAuthorityDat = setupDatAccess( "FCAuthority", xiv::exd::Language::en );
      m_FCAuthorityCategoryDat = setupDatAccess( "FCAuthorityCategory", xiv::exd::Language::en );
      m_FCChestNameDat = setupDatAccess( "FCChestName", xiv::exd::Language::en );
      m_FccShopDat = setupDatAccess( "FccShop", xiv::exd::Language::en );
      m_FCHierarchyDat = setupDatAccess( "FCHierarchy", xiv::exd::Language::en );
      m_FCReputationDat = setupDatAccess( "FCReputation", xiv::exd::Language::en );
      m_FCRightsDat = setupDatAccess( "FCRights", xiv::exd::Language::en );
      m_FishingSpotDat = setupDatAccess( "FishingSpot", xiv::exd::Language::en );
      m_FishParameterDat = setupDatAccess( "FishParameter", xiv::exd::Language::en );
      m_GardeningSeedDat = setupDatAccess( "GardeningSeed", xiv::exd::Language::none );
      m_GatheringConditionDat = setupDatAccess( "GatheringCondition", xiv::exd::Language::en );
      m_GatheringExpDat = setupDatAccess( "GatheringExp", xiv::exd::Language::none );
      m_GatheringItemDat = setupDatAccess( "GatheringItem", xiv::exd::Language::none );
      m_GatheringItemLevelConvertTableDat = setupDatAccess( "GatheringItemLevelConvertTable", xiv::exd::Language::none );
      m_GatheringItemPointDat = setupDatAccess( "GatheringItemPoint", xiv::exd::Language::none );
      m_GatheringNotebookListDat = setupDatAccess( "GatheringNotebookList", xiv::exd::Language::none );
      m_GatheringPointDat = setupDatAccess( "GatheringPoint", xiv::exd::Language::none );
      m_GatheringPointBaseDat = setupDatAccess( "GatheringPointBase", xiv::exd::Language::none );
      m_GatheringPointBonusDat = setupDatAccess( "GatheringPointBonus", xiv::exd::Language::none );
      m_GatheringPointBonusTypeDat = setupDatAccess( "GatheringPointBonusType", xiv::exd::Language::en );
      m_GatheringPointNameDat = setupDatAccess( "GatheringPointName", xiv::exd::Language::en );
      m_GatheringSubCategoryDat = setupDatAccess( "GatheringSubCategory", xiv::exd::Language::en );
      m_GatheringTypeDat = setupDatAccess( "GatheringType", xiv::exd::Language::en );
      m_GcArmyExpeditionDat = setupDatAccess( "GcArmyExpedition", xiv::exd::Language::en );
      m_GcArmyExpeditionMemberBonusDat = setupDatAccess( "GcArmyExpeditionMemberBonus", xiv::exd::Language::none );
      m_GcArmyExpeditionTypeDat = setupDatAccess( "GcArmyExpeditionType", xiv::exd::Language::en );
      m_GcArmyMemberGrowDat = setupDatAccess( "GcArmyMemberGrow", xiv::exd::Language::none );
      m_GcArmyTrainingDat = setupDatAccess( "GcArmyTraining", xiv::exd::Language::en );
      m_GCScripShopCategoryDat = setupDatAccess( "GCScripShopCategory", xiv::exd::Language::none );
      m_GCScripShopItemDat = setupDatAccess( "GCScripShopItem", xiv::exd::Language::none );
      m_GCShopDat = setupDatAccess( "GCShop", xiv::exd::Language::none );
      m_GCShopItemCategoryDat = setupDatAccess( "GCShopItemCategory", xiv::exd::Language::en );
      m_GCSupplyDutyDat = setupDatAccess( "GCSupplyDuty", xiv::exd::Language::none );
      m_GCSupplyDutyRewardDat = setupDatAccess( "GCSupplyDutyReward", xiv::exd::Language::none );
      m_GeneralActionDat = setupDatAccess( "GeneralAction", xiv::exd::Language::en );
      m_GilShopDat = setupDatAccess( "GilShop", xiv::exd::Language::en );
      m_GilShopItemDat = setupDatAccess( "GilShopItem", xiv::exd::Language::none );
      m_GoldSaucerTextDataDat = setupDatAccess( "GoldSaucerTextData", xiv::exd::Language::en );
      m_GrandCompanyDat = setupDatAccess( "GrandCompany", xiv::exd::Language::en );
      m_GrandCompanyRankDat = setupDatAccess( "GrandCompanyRank", xiv::exd::Language::none );
      m_GuardianDeityDat = setupDatAccess( "GuardianDeity", xiv::exd::Language::en );
      m_GuildleveAssignmentDat = setupDatAccess( "GuildleveAssignment", xiv::exd::Language::none );
      m_GuildOrderGuideDat = setupDatAccess( "GuildOrderGuide", xiv::exd::Language::none );
      m_GuildOrderOfficerDat = setupDatAccess( "GuildOrderOfficer", xiv::exd::Language::none );
      m_HouseRetainerPoseDat = setupDatAccess( "HouseRetainerPose", xiv::exd::Language::none );
      m_HousingFurnitureDat = setupDatAccess( "HousingFurniture", xiv::exd::Language::none );
      m_HousingYardObjectDat = setupDatAccess( "HousingYardObject", xiv::exd::Language::none );
      m_InstanceContentDat = setupDatAccess( "InstanceContent", xiv::exd::Language::en );
      m_InstanceContentBuffDat = setupDatAccess( "InstanceContentBuff", xiv::exd::Language::none );
      m_InstanceContentTextDataDat = setupDatAccess( "InstanceContentTextData", xiv::exd::Language::en );
      m_InstanceContentTypeDat = setupDatAccess( "InstanceContentType", xiv::exd::Language::none );
      m_ItemDat = setupDatAccess( "Item", xiv::exd::Language::en );
      m_ItemActionDat = setupDatAccess( "ItemAction", xiv::exd::Language::none );
      m_ItemFoodDat = setupDatAccess( "ItemFood", xiv::exd::Language::none );
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
      m_MacroIconDat = setupDatAccess( "MacroIcon", xiv::exd::Language::none );
      m_MacroIconRedirectOldDat = setupDatAccess( "MacroIconRedirectOld", xiv::exd::Language::none );
      m_MainCommandDat = setupDatAccess( "MainCommand", xiv::exd::Language::en );
      m_MainCommandCategoryDat = setupDatAccess( "MainCommandCategory", xiv::exd::Language::en );
      m_MapDat = setupDatAccess( "Map", xiv::exd::Language::none );
      m_MapMarkerDat = setupDatAccess( "MapMarker", xiv::exd::Language::none );
      m_MapSymbolDat = setupDatAccess( "MapSymbol", xiv::exd::Language::none );
      m_MasterpieceSupplyDutyDat = setupDatAccess( "MasterpieceSupplyDuty", xiv::exd::Language::none );
      m_MasterpieceSupplyMultiplierDat = setupDatAccess( "MasterpieceSupplyMultiplier", xiv::exd::Language::none );
      m_MateriaDat = setupDatAccess( "Materia", xiv::exd::Language::none );
      m_MinionRaceDat = setupDatAccess( "MinionRace", xiv::exd::Language::en );
      m_MinionRulesDat = setupDatAccess( "MinionRules", xiv::exd::Language::en );
      m_MinionSkillTypeDat = setupDatAccess( "MinionSkillType", xiv::exd::Language::en );
      m_MobHuntTargetDat = setupDatAccess( "MobHuntTarget", xiv::exd::Language::none );
      m_ModelCharaDat = setupDatAccess( "ModelChara", xiv::exd::Language::none );
      m_MonsterNoteDat = setupDatAccess( "MonsterNote", xiv::exd::Language::en );
      m_MonsterNoteTargetDat = setupDatAccess( "MonsterNoteTarget", xiv::exd::Language::none );
      m_MountDat = setupDatAccess( "Mount", xiv::exd::Language::en );
      m_MountActionDat = setupDatAccess( "MountAction", xiv::exd::Language::none );
      m_NpcEquipDat = setupDatAccess( "NpcEquip", xiv::exd::Language::none );
      m_OmenDat = setupDatAccess( "Omen", xiv::exd::Language::none );
      m_OnlineStatusDat = setupDatAccess( "OnlineStatus", xiv::exd::Language::en );
      m_OrchestrionDat = setupDatAccess( "Orchestrion", xiv::exd::Language::en );
      m_OrchestrionPathDat = setupDatAccess( "OrchestrionPath", xiv::exd::Language::none );
      m_ParamGrowDat = setupDatAccess( "ParamGrow", xiv::exd::Language::none );
      m_PetDat = setupDatAccess( "Pet", xiv::exd::Language::en );
      m_PetActionDat = setupDatAccess( "PetAction", xiv::exd::Language::en );
      m_PictureDat = setupDatAccess( "Picture", xiv::exd::Language::none );
      m_PlaceNameDat = setupDatAccess( "PlaceName", xiv::exd::Language::en );
      m_QuestDat = setupDatAccess( "Quest", xiv::exd::Language::en );
      m_QuestRewardOtherDat = setupDatAccess( "QuestRewardOther", xiv::exd::Language::en );
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
      m_RelicDat = setupDatAccess( "Relic", xiv::exd::Language::none );
      m_Relic3Dat = setupDatAccess( "Relic3", xiv::exd::Language::none );
      m_RelicItemDat = setupDatAccess( "RelicItem", xiv::exd::Language::none );
      m_RelicNoteDat = setupDatAccess( "RelicNote", xiv::exd::Language::none );
      m_RelicNoteCategoryDat = setupDatAccess( "RelicNoteCategory", xiv::exd::Language::en );
      m_RetainerTaskDat = setupDatAccess( "RetainerTask", xiv::exd::Language::none );
      m_RetainerTaskNormalDat = setupDatAccess( "RetainerTaskNormal", xiv::exd::Language::none );
      m_RetainerTaskParameterDat = setupDatAccess( "RetainerTaskParameter", xiv::exd::Language::none );
      m_RetainerTaskRandomDat = setupDatAccess( "RetainerTaskRandom", xiv::exd::Language::en );
      m_SalvageDat = setupDatAccess( "Salvage", xiv::exd::Language::none );
      m_SatisfactionNpcDat = setupDatAccess( "SatisfactionNpc", xiv::exd::Language::none );
      m_SatisfactionSupplyDat = setupDatAccess( "SatisfactionSupply", xiv::exd::Language::none );
      m_SatisfactionSupplyRewardDat = setupDatAccess( "SatisfactionSupplyReward", xiv::exd::Language::none );
      m_ScreenImageDat = setupDatAccess( "ScreenImage", xiv::exd::Language::none );
      m_SecretRecipeBookDat = setupDatAccess( "SecretRecipeBook", xiv::exd::Language::en );
      m_SpearfishingItemDat = setupDatAccess( "SpearfishingItem", xiv::exd::Language::en );
      m_SpearfishingNotebookDat = setupDatAccess( "SpearfishingNotebook", xiv::exd::Language::none );
      m_SpecialShopDat = setupDatAccess( "SpecialShop", xiv::exd::Language::en );
      m_SpecialShopItemCategoryDat = setupDatAccess( "SpecialShopItemCategory", xiv::exd::Language::en );
      m_StainDat = setupDatAccess( "Stain", xiv::exd::Language::en );
      m_StatusDat = setupDatAccess( "Status", xiv::exd::Language::en );
      m_StoryDat = setupDatAccess( "Story", xiv::exd::Language::none );
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
      m_WarpDat = setupDatAccess( "Warp", xiv::exd::Language::en );
      m_WeatherDat = setupDatAccess( "Weather", xiv::exd::Language::en );
      m_WeatherGroupDat = setupDatAccess( "WeatherGroup", xiv::exd::Language::none );
      m_WeatherRateDat = setupDatAccess( "WeatherRate", xiv::exd::Language::none );
      m_WeeklyBingoOrderDataDat = setupDatAccess( "WeeklyBingoOrderData", xiv::exd::Language::none );
      m_WeeklyBingoRewardDataDat = setupDatAccess( "WeeklyBingoRewardData", xiv::exd::Language::none );
      m_WeeklyBingoTextDat = setupDatAccess( "WeeklyBingoText", xiv::exd::Language::en );
      m_WorldDCGroupTypeDat = setupDatAccess( "WorldDCGroupType", xiv::exd::Language::none );

   }
   catch( std::runtime_error )
   {
      return false;
   }

   return true;
}

///////////////////////////////////////////////////////////////
// DIRECT GETTERS
boost::shared_ptr< Core::Data::Achievement >
   Core::Data::ExdDataGenerated::getAchievement( uint32_t AchievementId )
{
   try
   {
      auto row = m_AchievementDat.get_row( AchievementId );
      auto info = boost::make_shared< Achievement >( AchievementId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AchievementCategory >
   Core::Data::ExdDataGenerated::getAchievementCategory( uint32_t AchievementCategoryId )
{
   try
   {
      auto row = m_AchievementCategoryDat.get_row( AchievementCategoryId );
      auto info = boost::make_shared< AchievementCategory >( AchievementCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AchievementKind >
   Core::Data::ExdDataGenerated::getAchievementKind( uint32_t AchievementKindId )
{
   try
   {
      auto row = m_AchievementKindDat.get_row( AchievementKindId );
      auto info = boost::make_shared< AchievementKind >( AchievementKindId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Action >
   Core::Data::ExdDataGenerated::getAction( uint32_t ActionId )
{
   try
   {
      auto row = m_ActionDat.get_row( ActionId );
      auto info = boost::make_shared< Action >( ActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ActionCategory >
   Core::Data::ExdDataGenerated::getActionCategory( uint32_t ActionCategoryId )
{
   try
   {
      auto row = m_ActionCategoryDat.get_row( ActionCategoryId );
      auto info = boost::make_shared< ActionCategory >( ActionCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ActionComboRoute >
   Core::Data::ExdDataGenerated::getActionComboRoute( uint32_t ActionComboRouteId )
{
   try
   {
      auto row = m_ActionComboRouteDat.get_row( ActionComboRouteId );
      auto info = boost::make_shared< ActionComboRoute >( ActionComboRouteId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ActionIndirection >
   Core::Data::ExdDataGenerated::getActionIndirection( uint32_t ActionIndirectionId )
{
   try
   {
      auto row = m_ActionIndirectionDat.get_row( ActionIndirectionId );
      auto info = boost::make_shared< ActionIndirection >( ActionIndirectionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ActionProcStatus >
   Core::Data::ExdDataGenerated::getActionProcStatus( uint32_t ActionProcStatusId )
{
   try
   {
      auto row = m_ActionProcStatusDat.get_row( ActionProcStatusId );
      auto info = boost::make_shared< ActionProcStatus >( ActionProcStatusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ActionTimeline >
   Core::Data::ExdDataGenerated::getActionTimeline( uint32_t ActionTimelineId )
{
   try
   {
      auto row = m_ActionTimelineDat.get_row( ActionTimelineId );
      auto info = boost::make_shared< ActionTimeline >( ActionTimelineId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ActionTransient >
   Core::Data::ExdDataGenerated::getActionTransient( uint32_t ActionTransientId )
{
   try
   {
      auto row = m_ActionTransientDat.get_row( ActionTransientId );
      auto info = boost::make_shared< ActionTransient >( ActionTransientId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Addon >
   Core::Data::ExdDataGenerated::getAddon( uint32_t AddonId )
{
   try
   {
      auto row = m_AddonDat.get_row( AddonId );
      auto info = boost::make_shared< Addon >( AddonId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Adventure >
   Core::Data::ExdDataGenerated::getAdventure( uint32_t AdventureId )
{
   try
   {
      auto row = m_AdventureDat.get_row( AdventureId );
      auto info = boost::make_shared< Adventure >( AdventureId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AdventureExPhase >
   Core::Data::ExdDataGenerated::getAdventureExPhase( uint32_t AdventureExPhaseId )
{
   try
   {
      auto row = m_AdventureExPhaseDat.get_row( AdventureExPhaseId );
      auto info = boost::make_shared< AdventureExPhase >( AdventureExPhaseId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AetherCurrent >
   Core::Data::ExdDataGenerated::getAetherCurrent( uint32_t AetherCurrentId )
{
   try
   {
      auto row = m_AetherCurrentDat.get_row( AetherCurrentId );
      auto info = boost::make_shared< AetherCurrent >( AetherCurrentId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AetherialWheel >
   Core::Data::ExdDataGenerated::getAetherialWheel( uint32_t AetherialWheelId )
{
   try
   {
      auto row = m_AetherialWheelDat.get_row( AetherialWheelId );
      auto info = boost::make_shared< AetherialWheel >( AetherialWheelId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Aetheryte >
   Core::Data::ExdDataGenerated::getAetheryte( uint32_t AetheryteId )
{
   try
   {
      auto row = m_AetheryteDat.get_row( AetheryteId );
      auto info = boost::make_shared< Aetheryte >( AetheryteId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AirshipExplorationLevel >
   Core::Data::ExdDataGenerated::getAirshipExplorationLevel( uint32_t AirshipExplorationLevelId )
{
   try
   {
      auto row = m_AirshipExplorationLevelDat.get_row( AirshipExplorationLevelId );
      auto info = boost::make_shared< AirshipExplorationLevel >( AirshipExplorationLevelId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AirshipExplorationLog >
   Core::Data::ExdDataGenerated::getAirshipExplorationLog( uint32_t AirshipExplorationLogId )
{
   try
   {
      auto row = m_AirshipExplorationLogDat.get_row( AirshipExplorationLogId );
      auto info = boost::make_shared< AirshipExplorationLog >( AirshipExplorationLogId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AirshipExplorationParamType >
   Core::Data::ExdDataGenerated::getAirshipExplorationParamType( uint32_t AirshipExplorationParamTypeId )
{
   try
   {
      auto row = m_AirshipExplorationParamTypeDat.get_row( AirshipExplorationParamTypeId );
      auto info = boost::make_shared< AirshipExplorationParamType >( AirshipExplorationParamTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AirshipExplorationPart >
   Core::Data::ExdDataGenerated::getAirshipExplorationPart( uint32_t AirshipExplorationPartId )
{
   try
   {
      auto row = m_AirshipExplorationPartDat.get_row( AirshipExplorationPartId );
      auto info = boost::make_shared< AirshipExplorationPart >( AirshipExplorationPartId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AirshipExplorationPoint >
   Core::Data::ExdDataGenerated::getAirshipExplorationPoint( uint32_t AirshipExplorationPointId )
{
   try
   {
      auto row = m_AirshipExplorationPointDat.get_row( AirshipExplorationPointId );
      auto info = boost::make_shared< AirshipExplorationPoint >( AirshipExplorationPointId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeapon5 >
   Core::Data::ExdDataGenerated::getAnimaWeapon5( uint32_t AnimaWeapon5Id )
{
   try
   {
      auto row = m_AnimaWeapon5Dat.get_row( AnimaWeapon5Id );
      auto info = boost::make_shared< AnimaWeapon5 >( AnimaWeapon5Id, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeapon5Param >
   Core::Data::ExdDataGenerated::getAnimaWeapon5Param( uint32_t AnimaWeapon5ParamId )
{
   try
   {
      auto row = m_AnimaWeapon5ParamDat.get_row( AnimaWeapon5ParamId );
      auto info = boost::make_shared< AnimaWeapon5Param >( AnimaWeapon5ParamId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeapon5PatternGroup >
   Core::Data::ExdDataGenerated::getAnimaWeapon5PatternGroup( uint32_t AnimaWeapon5PatternGroupId )
{
   try
   {
      auto row = m_AnimaWeapon5PatternGroupDat.get_row( AnimaWeapon5PatternGroupId );
      auto info = boost::make_shared< AnimaWeapon5PatternGroup >( AnimaWeapon5PatternGroupId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeapon5SpiritTalk >
   Core::Data::ExdDataGenerated::getAnimaWeapon5SpiritTalk( uint32_t AnimaWeapon5SpiritTalkId )
{
   try
   {
      auto row = m_AnimaWeapon5SpiritTalkDat.get_row( AnimaWeapon5SpiritTalkId );
      auto info = boost::make_shared< AnimaWeapon5SpiritTalk >( AnimaWeapon5SpiritTalkId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeapon5SpiritTalkParam >
   Core::Data::ExdDataGenerated::getAnimaWeapon5SpiritTalkParam( uint32_t AnimaWeapon5SpiritTalkParamId )
{
   try
   {
      auto row = m_AnimaWeapon5SpiritTalkParamDat.get_row( AnimaWeapon5SpiritTalkParamId );
      auto info = boost::make_shared< AnimaWeapon5SpiritTalkParam >( AnimaWeapon5SpiritTalkParamId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeapon5TradeItem >
   Core::Data::ExdDataGenerated::getAnimaWeapon5TradeItem( uint32_t AnimaWeapon5TradeItemId )
{
   try
   {
      auto row = m_AnimaWeapon5TradeItemDat.get_row( AnimaWeapon5TradeItemId );
      auto info = boost::make_shared< AnimaWeapon5TradeItem >( AnimaWeapon5TradeItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeaponFUITalk >
   Core::Data::ExdDataGenerated::getAnimaWeaponFUITalk( uint32_t AnimaWeaponFUITalkId )
{
   try
   {
      auto row = m_AnimaWeaponFUITalkDat.get_row( AnimaWeaponFUITalkId );
      auto info = boost::make_shared< AnimaWeaponFUITalk >( AnimaWeaponFUITalkId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeaponFUITalkParam >
   Core::Data::ExdDataGenerated::getAnimaWeaponFUITalkParam( uint32_t AnimaWeaponFUITalkParamId )
{
   try
   {
      auto row = m_AnimaWeaponFUITalkParamDat.get_row( AnimaWeaponFUITalkParamId );
      auto info = boost::make_shared< AnimaWeaponFUITalkParam >( AnimaWeaponFUITalkParamId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeaponIcon >
   Core::Data::ExdDataGenerated::getAnimaWeaponIcon( uint32_t AnimaWeaponIconId )
{
   try
   {
      auto row = m_AnimaWeaponIconDat.get_row( AnimaWeaponIconId );
      auto info = boost::make_shared< AnimaWeaponIcon >( AnimaWeaponIconId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AnimaWeaponItem >
   Core::Data::ExdDataGenerated::getAnimaWeaponItem( uint32_t AnimaWeaponItemId )
{
   try
   {
      auto row = m_AnimaWeaponItemDat.get_row( AnimaWeaponItemId );
      auto info = boost::make_shared< AnimaWeaponItem >( AnimaWeaponItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AquariumFish >
   Core::Data::ExdDataGenerated::getAquariumFish( uint32_t AquariumFishId )
{
   try
   {
      auto row = m_AquariumFishDat.get_row( AquariumFishId );
      auto info = boost::make_shared< AquariumFish >( AquariumFishId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AquariumWater >
   Core::Data::ExdDataGenerated::getAquariumWater( uint32_t AquariumWaterId )
{
   try
   {
      auto row = m_AquariumWaterDat.get_row( AquariumWaterId );
      auto info = boost::make_shared< AquariumWater >( AquariumWaterId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::AttackType >
   Core::Data::ExdDataGenerated::getAttackType( uint32_t AttackTypeId )
{
   try
   {
      auto row = m_AttackTypeDat.get_row( AttackTypeId );
      auto info = boost::make_shared< AttackType >( AttackTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Balloon >
   Core::Data::ExdDataGenerated::getBalloon( uint32_t BalloonId )
{
   try
   {
      auto row = m_BalloonDat.get_row( BalloonId );
      auto info = boost::make_shared< Balloon >( BalloonId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BaseParam >
   Core::Data::ExdDataGenerated::getBaseParam( uint32_t BaseParamId )
{
   try
   {
      auto row = m_BaseParamDat.get_row( BaseParamId );
      auto info = boost::make_shared< BaseParam >( BaseParamId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BattleLeve >
   Core::Data::ExdDataGenerated::getBattleLeve( uint32_t BattleLeveId )
{
   try
   {
      auto row = m_BattleLeveDat.get_row( BattleLeveId );
      auto info = boost::make_shared< BattleLeve >( BattleLeveId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BeastRankBonus >
   Core::Data::ExdDataGenerated::getBeastRankBonus( uint32_t BeastRankBonusId )
{
   try
   {
      auto row = m_BeastRankBonusDat.get_row( BeastRankBonusId );
      auto info = boost::make_shared< BeastRankBonus >( BeastRankBonusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BeastReputationRank >
   Core::Data::ExdDataGenerated::getBeastReputationRank( uint32_t BeastReputationRankId )
{
   try
   {
      auto row = m_BeastReputationRankDat.get_row( BeastReputationRankId );
      auto info = boost::make_shared< BeastReputationRank >( BeastReputationRankId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BeastTribe >
   Core::Data::ExdDataGenerated::getBeastTribe( uint32_t BeastTribeId )
{
   try
   {
      auto row = m_BeastTribeDat.get_row( BeastTribeId );
      auto info = boost::make_shared< BeastTribe >( BeastTribeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Behavior >
   Core::Data::ExdDataGenerated::getBehavior( uint32_t BehaviorId )
{
   try
   {
      auto row = m_BehaviorDat.get_row( BehaviorId );
      auto info = boost::make_shared< Behavior >( BehaviorId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BGM >
   Core::Data::ExdDataGenerated::getBGM( uint32_t BGMId )
{
   try
   {
      auto row = m_BGMDat.get_row( BGMId );
      auto info = boost::make_shared< BGM >( BGMId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BNpcAnnounceIcon >
   Core::Data::ExdDataGenerated::getBNpcAnnounceIcon( uint32_t BNpcAnnounceIconId )
{
   try
   {
      auto row = m_BNpcAnnounceIconDat.get_row( BNpcAnnounceIconId );
      auto info = boost::make_shared< BNpcAnnounceIcon >( BNpcAnnounceIconId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BNpcBase >
   Core::Data::ExdDataGenerated::getBNpcBase( uint32_t BNpcBaseId )
{
   try
   {
      auto row = m_BNpcBaseDat.get_row( BNpcBaseId );
      auto info = boost::make_shared< BNpcBase >( BNpcBaseId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BNpcCustomize >
   Core::Data::ExdDataGenerated::getBNpcCustomize( uint32_t BNpcCustomizeId )
{
   try
   {
      auto row = m_BNpcCustomizeDat.get_row( BNpcCustomizeId );
      auto info = boost::make_shared< BNpcCustomize >( BNpcCustomizeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BNpcName >
   Core::Data::ExdDataGenerated::getBNpcName( uint32_t BNpcNameId )
{
   try
   {
      auto row = m_BNpcNameDat.get_row( BNpcNameId );
      auto info = boost::make_shared< BNpcName >( BNpcNameId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BuddyAction >
   Core::Data::ExdDataGenerated::getBuddyAction( uint32_t BuddyActionId )
{
   try
   {
      auto row = m_BuddyActionDat.get_row( BuddyActionId );
      auto info = boost::make_shared< BuddyAction >( BuddyActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BuddyEquip >
   Core::Data::ExdDataGenerated::getBuddyEquip( uint32_t BuddyEquipId )
{
   try
   {
      auto row = m_BuddyEquipDat.get_row( BuddyEquipId );
      auto info = boost::make_shared< BuddyEquip >( BuddyEquipId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BuddyItem >
   Core::Data::ExdDataGenerated::getBuddyItem( uint32_t BuddyItemId )
{
   try
   {
      auto row = m_BuddyItemDat.get_row( BuddyItemId );
      auto info = boost::make_shared< BuddyItem >( BuddyItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BuddyRank >
   Core::Data::ExdDataGenerated::getBuddyRank( uint32_t BuddyRankId )
{
   try
   {
      auto row = m_BuddyRankDat.get_row( BuddyRankId );
      auto info = boost::make_shared< BuddyRank >( BuddyRankId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::BuddySkill >
   Core::Data::ExdDataGenerated::getBuddySkill( uint32_t BuddySkillId )
{
   try
   {
      auto row = m_BuddySkillDat.get_row( BuddySkillId );
      auto info = boost::make_shared< BuddySkill >( BuddySkillId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Cabinet >
   Core::Data::ExdDataGenerated::getCabinet( uint32_t CabinetId )
{
   try
   {
      auto row = m_CabinetDat.get_row( CabinetId );
      auto info = boost::make_shared< Cabinet >( CabinetId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CabinetCategory >
   Core::Data::ExdDataGenerated::getCabinetCategory( uint32_t CabinetCategoryId )
{
   try
   {
      auto row = m_CabinetCategoryDat.get_row( CabinetCategoryId );
      auto info = boost::make_shared< CabinetCategory >( CabinetCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Calendar >
   Core::Data::ExdDataGenerated::getCalendar( uint32_t CalendarId )
{
   try
   {
      auto row = m_CalendarDat.get_row( CalendarId );
      auto info = boost::make_shared< Calendar >( CalendarId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChainBonus >
   Core::Data::ExdDataGenerated::getChainBonus( uint32_t ChainBonusId )
{
   try
   {
      auto row = m_ChainBonusDat.get_row( ChainBonusId );
      auto info = boost::make_shared< ChainBonus >( ChainBonusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CharaMakeCustomize >
   Core::Data::ExdDataGenerated::getCharaMakeCustomize( uint32_t CharaMakeCustomizeId )
{
   try
   {
      auto row = m_CharaMakeCustomizeDat.get_row( CharaMakeCustomizeId );
      auto info = boost::make_shared< CharaMakeCustomize >( CharaMakeCustomizeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CharaMakeType >
   Core::Data::ExdDataGenerated::getCharaMakeType( uint32_t CharaMakeTypeId )
{
   try
   {
      auto row = m_CharaMakeTypeDat.get_row( CharaMakeTypeId );
      auto info = boost::make_shared< CharaMakeType >( CharaMakeTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRace >
   Core::Data::ExdDataGenerated::getChocoboRace( uint32_t ChocoboRaceId )
{
   try
   {
      auto row = m_ChocoboRaceDat.get_row( ChocoboRaceId );
      auto info = boost::make_shared< ChocoboRace >( ChocoboRaceId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRaceAbility >
   Core::Data::ExdDataGenerated::getChocoboRaceAbility( uint32_t ChocoboRaceAbilityId )
{
   try
   {
      auto row = m_ChocoboRaceAbilityDat.get_row( ChocoboRaceAbilityId );
      auto info = boost::make_shared< ChocoboRaceAbility >( ChocoboRaceAbilityId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRaceAbilityType >
   Core::Data::ExdDataGenerated::getChocoboRaceAbilityType( uint32_t ChocoboRaceAbilityTypeId )
{
   try
   {
      auto row = m_ChocoboRaceAbilityTypeDat.get_row( ChocoboRaceAbilityTypeId );
      auto info = boost::make_shared< ChocoboRaceAbilityType >( ChocoboRaceAbilityTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRaceItem >
   Core::Data::ExdDataGenerated::getChocoboRaceItem( uint32_t ChocoboRaceItemId )
{
   try
   {
      auto row = m_ChocoboRaceItemDat.get_row( ChocoboRaceItemId );
      auto info = boost::make_shared< ChocoboRaceItem >( ChocoboRaceItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRaceRank >
   Core::Data::ExdDataGenerated::getChocoboRaceRank( uint32_t ChocoboRaceRankId )
{
   try
   {
      auto row = m_ChocoboRaceRankDat.get_row( ChocoboRaceRankId );
      auto info = boost::make_shared< ChocoboRaceRank >( ChocoboRaceRankId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRaceStatus >
   Core::Data::ExdDataGenerated::getChocoboRaceStatus( uint32_t ChocoboRaceStatusId )
{
   try
   {
      auto row = m_ChocoboRaceStatusDat.get_row( ChocoboRaceStatusId );
      auto info = boost::make_shared< ChocoboRaceStatus >( ChocoboRaceStatusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboRaceTerritory >
   Core::Data::ExdDataGenerated::getChocoboRaceTerritory( uint32_t ChocoboRaceTerritoryId )
{
   try
   {
      auto row = m_ChocoboRaceTerritoryDat.get_row( ChocoboRaceTerritoryId );
      auto info = boost::make_shared< ChocoboRaceTerritory >( ChocoboRaceTerritoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ChocoboTaxiStand >
   Core::Data::ExdDataGenerated::getChocoboTaxiStand( uint32_t ChocoboTaxiStandId )
{
   try
   {
      auto row = m_ChocoboTaxiStandDat.get_row( ChocoboTaxiStandId );
      auto info = boost::make_shared< ChocoboTaxiStand >( ChocoboTaxiStandId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ClassJob >
   Core::Data::ExdDataGenerated::getClassJob( uint32_t ClassJobId )
{
   try
   {
      auto row = m_ClassJobDat.get_row( ClassJobId );
      auto info = boost::make_shared< ClassJob >( ClassJobId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ClassJobCategory >
   Core::Data::ExdDataGenerated::getClassJobCategory( uint32_t ClassJobCategoryId )
{
   try
   {
      auto row = m_ClassJobCategoryDat.get_row( ClassJobCategoryId );
      auto info = boost::make_shared< ClassJobCategory >( ClassJobCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Companion >
   Core::Data::ExdDataGenerated::getCompanion( uint32_t CompanionId )
{
   try
   {
      auto row = m_CompanionDat.get_row( CompanionId );
      auto info = boost::make_shared< Companion >( CompanionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanionMove >
   Core::Data::ExdDataGenerated::getCompanionMove( uint32_t CompanionMoveId )
{
   try
   {
      auto row = m_CompanionMoveDat.get_row( CompanionMoveId );
      auto info = boost::make_shared< CompanionMove >( CompanionMoveId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanionTransient >
   Core::Data::ExdDataGenerated::getCompanionTransient( uint32_t CompanionTransientId )
{
   try
   {
      auto row = m_CompanionTransientDat.get_row( CompanionTransientId );
      auto info = boost::make_shared< CompanionTransient >( CompanionTransientId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyAction >
   Core::Data::ExdDataGenerated::getCompanyAction( uint32_t CompanyActionId )
{
   try
   {
      auto row = m_CompanyActionDat.get_row( CompanyActionId );
      auto info = boost::make_shared< CompanyAction >( CompanyActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftDraft >
   Core::Data::ExdDataGenerated::getCompanyCraftDraft( uint32_t CompanyCraftDraftId )
{
   try
   {
      auto row = m_CompanyCraftDraftDat.get_row( CompanyCraftDraftId );
      auto info = boost::make_shared< CompanyCraftDraft >( CompanyCraftDraftId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftDraftCategory >
   Core::Data::ExdDataGenerated::getCompanyCraftDraftCategory( uint32_t CompanyCraftDraftCategoryId )
{
   try
   {
      auto row = m_CompanyCraftDraftCategoryDat.get_row( CompanyCraftDraftCategoryId );
      auto info = boost::make_shared< CompanyCraftDraftCategory >( CompanyCraftDraftCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftManufactoryState >
   Core::Data::ExdDataGenerated::getCompanyCraftManufactoryState( uint32_t CompanyCraftManufactoryStateId )
{
   try
   {
      auto row = m_CompanyCraftManufactoryStateDat.get_row( CompanyCraftManufactoryStateId );
      auto info = boost::make_shared< CompanyCraftManufactoryState >( CompanyCraftManufactoryStateId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftPart >
   Core::Data::ExdDataGenerated::getCompanyCraftPart( uint32_t CompanyCraftPartId )
{
   try
   {
      auto row = m_CompanyCraftPartDat.get_row( CompanyCraftPartId );
      auto info = boost::make_shared< CompanyCraftPart >( CompanyCraftPartId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftProcess >
   Core::Data::ExdDataGenerated::getCompanyCraftProcess( uint32_t CompanyCraftProcessId )
{
   try
   {
      auto row = m_CompanyCraftProcessDat.get_row( CompanyCraftProcessId );
      auto info = boost::make_shared< CompanyCraftProcess >( CompanyCraftProcessId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftSequence >
   Core::Data::ExdDataGenerated::getCompanyCraftSequence( uint32_t CompanyCraftSequenceId )
{
   try
   {
      auto row = m_CompanyCraftSequenceDat.get_row( CompanyCraftSequenceId );
      auto info = boost::make_shared< CompanyCraftSequence >( CompanyCraftSequenceId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftSupplyItem >
   Core::Data::ExdDataGenerated::getCompanyCraftSupplyItem( uint32_t CompanyCraftSupplyItemId )
{
   try
   {
      auto row = m_CompanyCraftSupplyItemDat.get_row( CompanyCraftSupplyItemId );
      auto info = boost::make_shared< CompanyCraftSupplyItem >( CompanyCraftSupplyItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompanyCraftType >
   Core::Data::ExdDataGenerated::getCompanyCraftType( uint32_t CompanyCraftTypeId )
{
   try
   {
      auto row = m_CompanyCraftTypeDat.get_row( CompanyCraftTypeId );
      auto info = boost::make_shared< CompanyCraftType >( CompanyCraftTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompleteJournal >
   Core::Data::ExdDataGenerated::getCompleteJournal( uint32_t CompleteJournalId )
{
   try
   {
      auto row = m_CompleteJournalDat.get_row( CompleteJournalId );
      auto info = boost::make_shared< CompleteJournal >( CompleteJournalId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CompleteJournalCategory >
   Core::Data::ExdDataGenerated::getCompleteJournalCategory( uint32_t CompleteJournalCategoryId )
{
   try
   {
      auto row = m_CompleteJournalCategoryDat.get_row( CompleteJournalCategoryId );
      auto info = boost::make_shared< CompleteJournalCategory >( CompleteJournalCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ContentExAction >
   Core::Data::ExdDataGenerated::getContentExAction( uint32_t ContentExActionId )
{
   try
   {
      auto row = m_ContentExActionDat.get_row( ContentExActionId );
      auto info = boost::make_shared< ContentExAction >( ContentExActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ContentFinderCondition >
   Core::Data::ExdDataGenerated::getContentFinderCondition( uint32_t ContentFinderConditionId )
{
   try
   {
      auto row = m_ContentFinderConditionDat.get_row( ContentFinderConditionId );
      auto info = boost::make_shared< ContentFinderCondition >( ContentFinderConditionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ContentFinderConditionTransient >
   Core::Data::ExdDataGenerated::getContentFinderConditionTransient( uint32_t ContentFinderConditionTransientId )
{
   try
   {
      auto row = m_ContentFinderConditionTransientDat.get_row( ContentFinderConditionTransientId );
      auto info = boost::make_shared< ContentFinderConditionTransient >( ContentFinderConditionTransientId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ContentMemberType >
   Core::Data::ExdDataGenerated::getContentMemberType( uint32_t ContentMemberTypeId )
{
   try
   {
      auto row = m_ContentMemberTypeDat.get_row( ContentMemberTypeId );
      auto info = boost::make_shared< ContentMemberType >( ContentMemberTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ContentRoulette >
   Core::Data::ExdDataGenerated::getContentRoulette( uint32_t ContentRouletteId )
{
   try
   {
      auto row = m_ContentRouletteDat.get_row( ContentRouletteId );
      auto info = boost::make_shared< ContentRoulette >( ContentRouletteId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ContentType >
   Core::Data::ExdDataGenerated::getContentType( uint32_t ContentTypeId )
{
   try
   {
      auto row = m_ContentTypeDat.get_row( ContentTypeId );
      auto info = boost::make_shared< ContentType >( ContentTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CraftAction >
   Core::Data::ExdDataGenerated::getCraftAction( uint32_t CraftActionId )
{
   try
   {
      auto row = m_CraftActionDat.get_row( CraftActionId );
      auto info = boost::make_shared< CraftAction >( CraftActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CraftLeve >
   Core::Data::ExdDataGenerated::getCraftLeve( uint32_t CraftLeveId )
{
   try
   {
      auto row = m_CraftLeveDat.get_row( CraftLeveId );
      auto info = boost::make_shared< CraftLeve >( CraftLeveId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CraftType >
   Core::Data::ExdDataGenerated::getCraftType( uint32_t CraftTypeId )
{
   try
   {
      auto row = m_CraftTypeDat.get_row( CraftTypeId );
      auto info = boost::make_shared< CraftType >( CraftTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Currency >
   Core::Data::ExdDataGenerated::getCurrency( uint32_t CurrencyId )
{
   try
   {
      auto row = m_CurrencyDat.get_row( CurrencyId );
      auto info = boost::make_shared< Currency >( CurrencyId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CustomTalk >
   Core::Data::ExdDataGenerated::getCustomTalk( uint32_t CustomTalkId )
{
   try
   {
      auto row = m_CustomTalkDat.get_row( CustomTalkId );
      auto info = boost::make_shared< CustomTalk >( CustomTalkId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Cutscene >
   Core::Data::ExdDataGenerated::getCutscene( uint32_t CutsceneId )
{
   try
   {
      auto row = m_CutsceneDat.get_row( CutsceneId );
      auto info = boost::make_shared< Cutscene >( CutsceneId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::CutScreenImage >
   Core::Data::ExdDataGenerated::getCutScreenImage( uint32_t CutScreenImageId )
{
   try
   {
      auto row = m_CutScreenImageDat.get_row( CutScreenImageId );
      auto info = boost::make_shared< CutScreenImage >( CutScreenImageId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DailySupplyItem >
   Core::Data::ExdDataGenerated::getDailySupplyItem( uint32_t DailySupplyItemId )
{
   try
   {
      auto row = m_DailySupplyItemDat.get_row( DailySupplyItemId );
      auto info = boost::make_shared< DailySupplyItem >( DailySupplyItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeepDungeonBan >
   Core::Data::ExdDataGenerated::getDeepDungeonBan( uint32_t DeepDungeonBanId )
{
   try
   {
      auto row = m_DeepDungeonBanDat.get_row( DeepDungeonBanId );
      auto info = boost::make_shared< DeepDungeonBan >( DeepDungeonBanId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeepDungeonDanger >
   Core::Data::ExdDataGenerated::getDeepDungeonDanger( uint32_t DeepDungeonDangerId )
{
   try
   {
      auto row = m_DeepDungeonDangerDat.get_row( DeepDungeonDangerId );
      auto info = boost::make_shared< DeepDungeonDanger >( DeepDungeonDangerId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeepDungeonEquipment >
   Core::Data::ExdDataGenerated::getDeepDungeonEquipment( uint32_t DeepDungeonEquipmentId )
{
   try
   {
      auto row = m_DeepDungeonEquipmentDat.get_row( DeepDungeonEquipmentId );
      auto info = boost::make_shared< DeepDungeonEquipment >( DeepDungeonEquipmentId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeepDungeonFloorEffectUI >
   Core::Data::ExdDataGenerated::getDeepDungeonFloorEffectUI( uint32_t DeepDungeonFloorEffectUIId )
{
   try
   {
      auto row = m_DeepDungeonFloorEffectUIDat.get_row( DeepDungeonFloorEffectUIId );
      auto info = boost::make_shared< DeepDungeonFloorEffectUI >( DeepDungeonFloorEffectUIId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeepDungeonItem >
   Core::Data::ExdDataGenerated::getDeepDungeonItem( uint32_t DeepDungeonItemId )
{
   try
   {
      auto row = m_DeepDungeonItemDat.get_row( DeepDungeonItemId );
      auto info = boost::make_shared< DeepDungeonItem >( DeepDungeonItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeepDungeonStatus >
   Core::Data::ExdDataGenerated::getDeepDungeonStatus( uint32_t DeepDungeonStatusId )
{
   try
   {
      auto row = m_DeepDungeonStatusDat.get_row( DeepDungeonStatusId );
      auto info = boost::make_shared< DeepDungeonStatus >( DeepDungeonStatusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DefaultTalk >
   Core::Data::ExdDataGenerated::getDefaultTalk( uint32_t DefaultTalkId )
{
   try
   {
      auto row = m_DefaultTalkDat.get_row( DefaultTalkId );
      auto info = boost::make_shared< DefaultTalk >( DefaultTalkId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DeliveryQuest >
   Core::Data::ExdDataGenerated::getDeliveryQuest( uint32_t DeliveryQuestId )
{
   try
   {
      auto row = m_DeliveryQuestDat.get_row( DeliveryQuestId );
      auto info = boost::make_shared< DeliveryQuest >( DeliveryQuestId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DisposalShop >
   Core::Data::ExdDataGenerated::getDisposalShop( uint32_t DisposalShopId )
{
   try
   {
      auto row = m_DisposalShopDat.get_row( DisposalShopId );
      auto info = boost::make_shared< DisposalShop >( DisposalShopId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DisposalShopFilterType >
   Core::Data::ExdDataGenerated::getDisposalShopFilterType( uint32_t DisposalShopFilterTypeId )
{
   try
   {
      auto row = m_DisposalShopFilterTypeDat.get_row( DisposalShopFilterTypeId );
      auto info = boost::make_shared< DisposalShopFilterType >( DisposalShopFilterTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DisposalShopItem >
   Core::Data::ExdDataGenerated::getDisposalShopItem( uint32_t DisposalShopItemId )
{
   try
   {
      auto row = m_DisposalShopItemDat.get_row( DisposalShopItemId );
      auto info = boost::make_shared< DisposalShopItem >( DisposalShopItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DpsChallenge >
   Core::Data::ExdDataGenerated::getDpsChallenge( uint32_t DpsChallengeId )
{
   try
   {
      auto row = m_DpsChallengeDat.get_row( DpsChallengeId );
      auto info = boost::make_shared< DpsChallenge >( DpsChallengeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DpsChallengeOfficer >
   Core::Data::ExdDataGenerated::getDpsChallengeOfficer( uint32_t DpsChallengeOfficerId )
{
   try
   {
      auto row = m_DpsChallengeOfficerDat.get_row( DpsChallengeOfficerId );
      auto info = boost::make_shared< DpsChallengeOfficer >( DpsChallengeOfficerId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::DpsChallengeTransient >
   Core::Data::ExdDataGenerated::getDpsChallengeTransient( uint32_t DpsChallengeTransientId )
{
   try
   {
      auto row = m_DpsChallengeTransientDat.get_row( DpsChallengeTransientId );
      auto info = boost::make_shared< DpsChallengeTransient >( DpsChallengeTransientId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Emote >
   Core::Data::ExdDataGenerated::getEmote( uint32_t EmoteId )
{
   try
   {
      auto row = m_EmoteDat.get_row( EmoteId );
      auto info = boost::make_shared< Emote >( EmoteId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EmoteCategory >
   Core::Data::ExdDataGenerated::getEmoteCategory( uint32_t EmoteCategoryId )
{
   try
   {
      auto row = m_EmoteCategoryDat.get_row( EmoteCategoryId );
      auto info = boost::make_shared< EmoteCategory >( EmoteCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ENpcBase >
   Core::Data::ExdDataGenerated::getENpcBase( uint32_t ENpcBaseId )
{
   try
   {
      auto row = m_ENpcBaseDat.get_row( ENpcBaseId );
      auto info = boost::make_shared< ENpcBase >( ENpcBaseId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ENpcResident >
   Core::Data::ExdDataGenerated::getENpcResident( uint32_t ENpcResidentId )
{
   try
   {
      auto row = m_ENpcResidentDat.get_row( ENpcResidentId );
      auto info = boost::make_shared< ENpcResident >( ENpcResidentId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EObj >
   Core::Data::ExdDataGenerated::getEObj( uint32_t EObjId )
{
   try
   {
      auto row = m_EObjDat.get_row( EObjId );
      auto info = boost::make_shared< EObj >( EObjId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EquipRaceCategory >
   Core::Data::ExdDataGenerated::getEquipRaceCategory( uint32_t EquipRaceCategoryId )
{
   try
   {
      auto row = m_EquipRaceCategoryDat.get_row( EquipRaceCategoryId );
      auto info = boost::make_shared< EquipRaceCategory >( EquipRaceCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EquipSlotCategory >
   Core::Data::ExdDataGenerated::getEquipSlotCategory( uint32_t EquipSlotCategoryId )
{
   try
   {
      auto row = m_EquipSlotCategoryDat.get_row( EquipSlotCategoryId );
      auto info = boost::make_shared< EquipSlotCategory >( EquipSlotCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EventAction >
   Core::Data::ExdDataGenerated::getEventAction( uint32_t EventActionId )
{
   try
   {
      auto row = m_EventActionDat.get_row( EventActionId );
      auto info = boost::make_shared< EventAction >( EventActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EventIconPriority >
   Core::Data::ExdDataGenerated::getEventIconPriority( uint32_t EventIconPriorityId )
{
   try
   {
      auto row = m_EventIconPriorityDat.get_row( EventIconPriorityId );
      auto info = boost::make_shared< EventIconPriority >( EventIconPriorityId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EventIconType >
   Core::Data::ExdDataGenerated::getEventIconType( uint32_t EventIconTypeId )
{
   try
   {
      auto row = m_EventIconTypeDat.get_row( EventIconTypeId );
      auto info = boost::make_shared< EventIconType >( EventIconTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EventItem >
   Core::Data::ExdDataGenerated::getEventItem( uint32_t EventItemId )
{
   try
   {
      auto row = m_EventItemDat.get_row( EventItemId );
      auto info = boost::make_shared< EventItem >( EventItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::EventItemHelp >
   Core::Data::ExdDataGenerated::getEventItemHelp( uint32_t EventItemHelpId )
{
   try
   {
      auto row = m_EventItemHelpDat.get_row( EventItemHelpId );
      auto info = boost::make_shared< EventItemHelp >( EventItemHelpId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ExVersion >
   Core::Data::ExdDataGenerated::getExVersion( uint32_t ExVersionId )
{
   try
   {
      auto row = m_ExVersionDat.get_row( ExVersionId );
      auto info = boost::make_shared< ExVersion >( ExVersionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Fate >
   Core::Data::ExdDataGenerated::getFate( uint32_t FateId )
{
   try
   {
      auto row = m_FateDat.get_row( FateId );
      auto info = boost::make_shared< Fate >( FateId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCActivity >
   Core::Data::ExdDataGenerated::getFCActivity( uint32_t FCActivityId )
{
   try
   {
      auto row = m_FCActivityDat.get_row( FCActivityId );
      auto info = boost::make_shared< FCActivity >( FCActivityId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCAuthority >
   Core::Data::ExdDataGenerated::getFCAuthority( uint32_t FCAuthorityId )
{
   try
   {
      auto row = m_FCAuthorityDat.get_row( FCAuthorityId );
      auto info = boost::make_shared< FCAuthority >( FCAuthorityId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCAuthorityCategory >
   Core::Data::ExdDataGenerated::getFCAuthorityCategory( uint32_t FCAuthorityCategoryId )
{
   try
   {
      auto row = m_FCAuthorityCategoryDat.get_row( FCAuthorityCategoryId );
      auto info = boost::make_shared< FCAuthorityCategory >( FCAuthorityCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCChestName >
   Core::Data::ExdDataGenerated::getFCChestName( uint32_t FCChestNameId )
{
   try
   {
      auto row = m_FCChestNameDat.get_row( FCChestNameId );
      auto info = boost::make_shared< FCChestName >( FCChestNameId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FccShop >
   Core::Data::ExdDataGenerated::getFccShop( uint32_t FccShopId )
{
   try
   {
      auto row = m_FccShopDat.get_row( FccShopId );
      auto info = boost::make_shared< FccShop >( FccShopId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCHierarchy >
   Core::Data::ExdDataGenerated::getFCHierarchy( uint32_t FCHierarchyId )
{
   try
   {
      auto row = m_FCHierarchyDat.get_row( FCHierarchyId );
      auto info = boost::make_shared< FCHierarchy >( FCHierarchyId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCReputation >
   Core::Data::ExdDataGenerated::getFCReputation( uint32_t FCReputationId )
{
   try
   {
      auto row = m_FCReputationDat.get_row( FCReputationId );
      auto info = boost::make_shared< FCReputation >( FCReputationId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FCRights >
   Core::Data::ExdDataGenerated::getFCRights( uint32_t FCRightsId )
{
   try
   {
      auto row = m_FCRightsDat.get_row( FCRightsId );
      auto info = boost::make_shared< FCRights >( FCRightsId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FishingSpot >
   Core::Data::ExdDataGenerated::getFishingSpot( uint32_t FishingSpotId )
{
   try
   {
      auto row = m_FishingSpotDat.get_row( FishingSpotId );
      auto info = boost::make_shared< FishingSpot >( FishingSpotId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::FishParameter >
   Core::Data::ExdDataGenerated::getFishParameter( uint32_t FishParameterId )
{
   try
   {
      auto row = m_FishParameterDat.get_row( FishParameterId );
      auto info = boost::make_shared< FishParameter >( FishParameterId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GardeningSeed >
   Core::Data::ExdDataGenerated::getGardeningSeed( uint32_t GardeningSeedId )
{
   try
   {
      auto row = m_GardeningSeedDat.get_row( GardeningSeedId );
      auto info = boost::make_shared< GardeningSeed >( GardeningSeedId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringCondition >
   Core::Data::ExdDataGenerated::getGatheringCondition( uint32_t GatheringConditionId )
{
   try
   {
      auto row = m_GatheringConditionDat.get_row( GatheringConditionId );
      auto info = boost::make_shared< GatheringCondition >( GatheringConditionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringExp >
   Core::Data::ExdDataGenerated::getGatheringExp( uint32_t GatheringExpId )
{
   try
   {
      auto row = m_GatheringExpDat.get_row( GatheringExpId );
      auto info = boost::make_shared< GatheringExp >( GatheringExpId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringItem >
   Core::Data::ExdDataGenerated::getGatheringItem( uint32_t GatheringItemId )
{
   try
   {
      auto row = m_GatheringItemDat.get_row( GatheringItemId );
      auto info = boost::make_shared< GatheringItem >( GatheringItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringItemLevelConvertTable >
   Core::Data::ExdDataGenerated::getGatheringItemLevelConvertTable( uint32_t GatheringItemLevelConvertTableId )
{
   try
   {
      auto row = m_GatheringItemLevelConvertTableDat.get_row( GatheringItemLevelConvertTableId );
      auto info = boost::make_shared< GatheringItemLevelConvertTable >( GatheringItemLevelConvertTableId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringItemPoint >
   Core::Data::ExdDataGenerated::getGatheringItemPoint( uint32_t GatheringItemPointId )
{
   try
   {
      auto row = m_GatheringItemPointDat.get_row( GatheringItemPointId );
      auto info = boost::make_shared< GatheringItemPoint >( GatheringItemPointId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringNotebookList >
   Core::Data::ExdDataGenerated::getGatheringNotebookList( uint32_t GatheringNotebookListId )
{
   try
   {
      auto row = m_GatheringNotebookListDat.get_row( GatheringNotebookListId );
      auto info = boost::make_shared< GatheringNotebookList >( GatheringNotebookListId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringPoint >
   Core::Data::ExdDataGenerated::getGatheringPoint( uint32_t GatheringPointId )
{
   try
   {
      auto row = m_GatheringPointDat.get_row( GatheringPointId );
      auto info = boost::make_shared< GatheringPoint >( GatheringPointId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringPointBase >
   Core::Data::ExdDataGenerated::getGatheringPointBase( uint32_t GatheringPointBaseId )
{
   try
   {
      auto row = m_GatheringPointBaseDat.get_row( GatheringPointBaseId );
      auto info = boost::make_shared< GatheringPointBase >( GatheringPointBaseId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringPointBonus >
   Core::Data::ExdDataGenerated::getGatheringPointBonus( uint32_t GatheringPointBonusId )
{
   try
   {
      auto row = m_GatheringPointBonusDat.get_row( GatheringPointBonusId );
      auto info = boost::make_shared< GatheringPointBonus >( GatheringPointBonusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringPointBonusType >
   Core::Data::ExdDataGenerated::getGatheringPointBonusType( uint32_t GatheringPointBonusTypeId )
{
   try
   {
      auto row = m_GatheringPointBonusTypeDat.get_row( GatheringPointBonusTypeId );
      auto info = boost::make_shared< GatheringPointBonusType >( GatheringPointBonusTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringPointName >
   Core::Data::ExdDataGenerated::getGatheringPointName( uint32_t GatheringPointNameId )
{
   try
   {
      auto row = m_GatheringPointNameDat.get_row( GatheringPointNameId );
      auto info = boost::make_shared< GatheringPointName >( GatheringPointNameId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringSubCategory >
   Core::Data::ExdDataGenerated::getGatheringSubCategory( uint32_t GatheringSubCategoryId )
{
   try
   {
      auto row = m_GatheringSubCategoryDat.get_row( GatheringSubCategoryId );
      auto info = boost::make_shared< GatheringSubCategory >( GatheringSubCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GatheringType >
   Core::Data::ExdDataGenerated::getGatheringType( uint32_t GatheringTypeId )
{
   try
   {
      auto row = m_GatheringTypeDat.get_row( GatheringTypeId );
      auto info = boost::make_shared< GatheringType >( GatheringTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GcArmyExpedition >
   Core::Data::ExdDataGenerated::getGcArmyExpedition( uint32_t GcArmyExpeditionId )
{
   try
   {
      auto row = m_GcArmyExpeditionDat.get_row( GcArmyExpeditionId );
      auto info = boost::make_shared< GcArmyExpedition >( GcArmyExpeditionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GcArmyExpeditionMemberBonus >
   Core::Data::ExdDataGenerated::getGcArmyExpeditionMemberBonus( uint32_t GcArmyExpeditionMemberBonusId )
{
   try
   {
      auto row = m_GcArmyExpeditionMemberBonusDat.get_row( GcArmyExpeditionMemberBonusId );
      auto info = boost::make_shared< GcArmyExpeditionMemberBonus >( GcArmyExpeditionMemberBonusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GcArmyExpeditionType >
   Core::Data::ExdDataGenerated::getGcArmyExpeditionType( uint32_t GcArmyExpeditionTypeId )
{
   try
   {
      auto row = m_GcArmyExpeditionTypeDat.get_row( GcArmyExpeditionTypeId );
      auto info = boost::make_shared< GcArmyExpeditionType >( GcArmyExpeditionTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GcArmyMemberGrow >
   Core::Data::ExdDataGenerated::getGcArmyMemberGrow( uint32_t GcArmyMemberGrowId )
{
   try
   {
      auto row = m_GcArmyMemberGrowDat.get_row( GcArmyMemberGrowId );
      auto info = boost::make_shared< GcArmyMemberGrow >( GcArmyMemberGrowId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GcArmyTraining >
   Core::Data::ExdDataGenerated::getGcArmyTraining( uint32_t GcArmyTrainingId )
{
   try
   {
      auto row = m_GcArmyTrainingDat.get_row( GcArmyTrainingId );
      auto info = boost::make_shared< GcArmyTraining >( GcArmyTrainingId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GCScripShopCategory >
   Core::Data::ExdDataGenerated::getGCScripShopCategory( uint32_t GCScripShopCategoryId )
{
   try
   {
      auto row = m_GCScripShopCategoryDat.get_row( GCScripShopCategoryId );
      auto info = boost::make_shared< GCScripShopCategory >( GCScripShopCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GCScripShopItem >
   Core::Data::ExdDataGenerated::getGCScripShopItem( uint32_t GCScripShopItemId )
{
   try
   {
      auto row = m_GCScripShopItemDat.get_row( GCScripShopItemId );
      auto info = boost::make_shared< GCScripShopItem >( GCScripShopItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GCShop >
   Core::Data::ExdDataGenerated::getGCShop( uint32_t GCShopId )
{
   try
   {
      auto row = m_GCShopDat.get_row( GCShopId );
      auto info = boost::make_shared< GCShop >( GCShopId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GCShopItemCategory >
   Core::Data::ExdDataGenerated::getGCShopItemCategory( uint32_t GCShopItemCategoryId )
{
   try
   {
      auto row = m_GCShopItemCategoryDat.get_row( GCShopItemCategoryId );
      auto info = boost::make_shared< GCShopItemCategory >( GCShopItemCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GCSupplyDuty >
   Core::Data::ExdDataGenerated::getGCSupplyDuty( uint32_t GCSupplyDutyId )
{
   try
   {
      auto row = m_GCSupplyDutyDat.get_row( GCSupplyDutyId );
      auto info = boost::make_shared< GCSupplyDuty >( GCSupplyDutyId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GCSupplyDutyReward >
   Core::Data::ExdDataGenerated::getGCSupplyDutyReward( uint32_t GCSupplyDutyRewardId )
{
   try
   {
      auto row = m_GCSupplyDutyRewardDat.get_row( GCSupplyDutyRewardId );
      auto info = boost::make_shared< GCSupplyDutyReward >( GCSupplyDutyRewardId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GeneralAction >
   Core::Data::ExdDataGenerated::getGeneralAction( uint32_t GeneralActionId )
{
   try
   {
      auto row = m_GeneralActionDat.get_row( GeneralActionId );
      auto info = boost::make_shared< GeneralAction >( GeneralActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GilShop >
   Core::Data::ExdDataGenerated::getGilShop( uint32_t GilShopId )
{
   try
   {
      auto row = m_GilShopDat.get_row( GilShopId );
      auto info = boost::make_shared< GilShop >( GilShopId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GilShopItem >
   Core::Data::ExdDataGenerated::getGilShopItem( uint32_t GilShopItemId )
{
   try
   {
      auto row = m_GilShopItemDat.get_row( GilShopItemId );
      auto info = boost::make_shared< GilShopItem >( GilShopItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GoldSaucerTextData >
   Core::Data::ExdDataGenerated::getGoldSaucerTextData( uint32_t GoldSaucerTextDataId )
{
   try
   {
      auto row = m_GoldSaucerTextDataDat.get_row( GoldSaucerTextDataId );
      auto info = boost::make_shared< GoldSaucerTextData >( GoldSaucerTextDataId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GrandCompany >
   Core::Data::ExdDataGenerated::getGrandCompany( uint32_t GrandCompanyId )
{
   try
   {
      auto row = m_GrandCompanyDat.get_row( GrandCompanyId );
      auto info = boost::make_shared< GrandCompany >( GrandCompanyId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GrandCompanyRank >
   Core::Data::ExdDataGenerated::getGrandCompanyRank( uint32_t GrandCompanyRankId )
{
   try
   {
      auto row = m_GrandCompanyRankDat.get_row( GrandCompanyRankId );
      auto info = boost::make_shared< GrandCompanyRank >( GrandCompanyRankId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GuardianDeity >
   Core::Data::ExdDataGenerated::getGuardianDeity( uint32_t GuardianDeityId )
{
   try
   {
      auto row = m_GuardianDeityDat.get_row( GuardianDeityId );
      auto info = boost::make_shared< GuardianDeity >( GuardianDeityId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GuildleveAssignment >
   Core::Data::ExdDataGenerated::getGuildleveAssignment( uint32_t GuildleveAssignmentId )
{
   try
   {
      auto row = m_GuildleveAssignmentDat.get_row( GuildleveAssignmentId );
      auto info = boost::make_shared< GuildleveAssignment >( GuildleveAssignmentId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GuildOrderGuide >
   Core::Data::ExdDataGenerated::getGuildOrderGuide( uint32_t GuildOrderGuideId )
{
   try
   {
      auto row = m_GuildOrderGuideDat.get_row( GuildOrderGuideId );
      auto info = boost::make_shared< GuildOrderGuide >( GuildOrderGuideId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::GuildOrderOfficer >
   Core::Data::ExdDataGenerated::getGuildOrderOfficer( uint32_t GuildOrderOfficerId )
{
   try
   {
      auto row = m_GuildOrderOfficerDat.get_row( GuildOrderOfficerId );
      auto info = boost::make_shared< GuildOrderOfficer >( GuildOrderOfficerId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::HouseRetainerPose >
   Core::Data::ExdDataGenerated::getHouseRetainerPose( uint32_t HouseRetainerPoseId )
{
   try
   {
      auto row = m_HouseRetainerPoseDat.get_row( HouseRetainerPoseId );
      auto info = boost::make_shared< HouseRetainerPose >( HouseRetainerPoseId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::HousingFurniture >
   Core::Data::ExdDataGenerated::getHousingFurniture( uint32_t HousingFurnitureId )
{
   try
   {
      auto row = m_HousingFurnitureDat.get_row( HousingFurnitureId );
      auto info = boost::make_shared< HousingFurniture >( HousingFurnitureId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::HousingYardObject >
   Core::Data::ExdDataGenerated::getHousingYardObject( uint32_t HousingYardObjectId )
{
   try
   {
      auto row = m_HousingYardObjectDat.get_row( HousingYardObjectId );
      auto info = boost::make_shared< HousingYardObject >( HousingYardObjectId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::InstanceContent >
   Core::Data::ExdDataGenerated::getInstanceContent( uint32_t InstanceContentId )
{
   try
   {
      auto row = m_InstanceContentDat.get_row( InstanceContentId );
      auto info = boost::make_shared< InstanceContent >( InstanceContentId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::InstanceContentBuff >
   Core::Data::ExdDataGenerated::getInstanceContentBuff( uint32_t InstanceContentBuffId )
{
   try
   {
      auto row = m_InstanceContentBuffDat.get_row( InstanceContentBuffId );
      auto info = boost::make_shared< InstanceContentBuff >( InstanceContentBuffId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::InstanceContentTextData >
   Core::Data::ExdDataGenerated::getInstanceContentTextData( uint32_t InstanceContentTextDataId )
{
   try
   {
      auto row = m_InstanceContentTextDataDat.get_row( InstanceContentTextDataId );
      auto info = boost::make_shared< InstanceContentTextData >( InstanceContentTextDataId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::InstanceContentType >
   Core::Data::ExdDataGenerated::getInstanceContentType( uint32_t InstanceContentTypeId )
{
   try
   {
      auto row = m_InstanceContentTypeDat.get_row( InstanceContentTypeId );
      auto info = boost::make_shared< InstanceContentType >( InstanceContentTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Item >
   Core::Data::ExdDataGenerated::getItem( uint32_t ItemId )
{
   try
   {
      auto row = m_ItemDat.get_row( ItemId );
      auto info = boost::make_shared< Item >( ItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ItemAction >
   Core::Data::ExdDataGenerated::getItemAction( uint32_t ItemActionId )
{
   try
   {
      auto row = m_ItemActionDat.get_row( ItemActionId );
      auto info = boost::make_shared< ItemAction >( ItemActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ItemFood >
   Core::Data::ExdDataGenerated::getItemFood( uint32_t ItemFoodId )
{
   try
   {
      auto row = m_ItemFoodDat.get_row( ItemFoodId );
      auto info = boost::make_shared< ItemFood >( ItemFoodId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ItemSearchCategory >
   Core::Data::ExdDataGenerated::getItemSearchCategory( uint32_t ItemSearchCategoryId )
{
   try
   {
      auto row = m_ItemSearchCategoryDat.get_row( ItemSearchCategoryId );
      auto info = boost::make_shared< ItemSearchCategory >( ItemSearchCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ItemSeries >
   Core::Data::ExdDataGenerated::getItemSeries( uint32_t ItemSeriesId )
{
   try
   {
      auto row = m_ItemSeriesDat.get_row( ItemSeriesId );
      auto info = boost::make_shared< ItemSeries >( ItemSeriesId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ItemSpecialBonus >
   Core::Data::ExdDataGenerated::getItemSpecialBonus( uint32_t ItemSpecialBonusId )
{
   try
   {
      auto row = m_ItemSpecialBonusDat.get_row( ItemSpecialBonusId );
      auto info = boost::make_shared< ItemSpecialBonus >( ItemSpecialBonusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ItemUICategory >
   Core::Data::ExdDataGenerated::getItemUICategory( uint32_t ItemUICategoryId )
{
   try
   {
      auto row = m_ItemUICategoryDat.get_row( ItemUICategoryId );
      auto info = boost::make_shared< ItemUICategory >( ItemUICategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::JournalCategory >
   Core::Data::ExdDataGenerated::getJournalCategory( uint32_t JournalCategoryId )
{
   try
   {
      auto row = m_JournalCategoryDat.get_row( JournalCategoryId );
      auto info = boost::make_shared< JournalCategory >( JournalCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::JournalGenre >
   Core::Data::ExdDataGenerated::getJournalGenre( uint32_t JournalGenreId )
{
   try
   {
      auto row = m_JournalGenreDat.get_row( JournalGenreId );
      auto info = boost::make_shared< JournalGenre >( JournalGenreId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::JournalSection >
   Core::Data::ExdDataGenerated::getJournalSection( uint32_t JournalSectionId )
{
   try
   {
      auto row = m_JournalSectionDat.get_row( JournalSectionId );
      auto info = boost::make_shared< JournalSection >( JournalSectionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Leve >
   Core::Data::ExdDataGenerated::getLeve( uint32_t LeveId )
{
   try
   {
      auto row = m_LeveDat.get_row( LeveId );
      auto info = boost::make_shared< Leve >( LeveId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LeveAssignmentType >
   Core::Data::ExdDataGenerated::getLeveAssignmentType( uint32_t LeveAssignmentTypeId )
{
   try
   {
      auto row = m_LeveAssignmentTypeDat.get_row( LeveAssignmentTypeId );
      auto info = boost::make_shared< LeveAssignmentType >( LeveAssignmentTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LeveClient >
   Core::Data::ExdDataGenerated::getLeveClient( uint32_t LeveClientId )
{
   try
   {
      auto row = m_LeveClientDat.get_row( LeveClientId );
      auto info = boost::make_shared< LeveClient >( LeveClientId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Level >
   Core::Data::ExdDataGenerated::getLevel( uint32_t LevelId )
{
   try
   {
      auto row = m_LevelDat.get_row( LevelId );
      auto info = boost::make_shared< Level >( LevelId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LeveRewardItem >
   Core::Data::ExdDataGenerated::getLeveRewardItem( uint32_t LeveRewardItemId )
{
   try
   {
      auto row = m_LeveRewardItemDat.get_row( LeveRewardItemId );
      auto info = boost::make_shared< LeveRewardItem >( LeveRewardItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LeveRewardItemGroup >
   Core::Data::ExdDataGenerated::getLeveRewardItemGroup( uint32_t LeveRewardItemGroupId )
{
   try
   {
      auto row = m_LeveRewardItemGroupDat.get_row( LeveRewardItemGroupId );
      auto info = boost::make_shared< LeveRewardItemGroup >( LeveRewardItemGroupId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LeveVfx >
   Core::Data::ExdDataGenerated::getLeveVfx( uint32_t LeveVfxId )
{
   try
   {
      auto row = m_LeveVfxDat.get_row( LeveVfxId );
      auto info = boost::make_shared< LeveVfx >( LeveVfxId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LogFilter >
   Core::Data::ExdDataGenerated::getLogFilter( uint32_t LogFilterId )
{
   try
   {
      auto row = m_LogFilterDat.get_row( LogFilterId );
      auto info = boost::make_shared< LogFilter >( LogFilterId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LogKind >
   Core::Data::ExdDataGenerated::getLogKind( uint32_t LogKindId )
{
   try
   {
      auto row = m_LogKindDat.get_row( LogKindId );
      auto info = boost::make_shared< LogKind >( LogKindId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LogKindCategoryText >
   Core::Data::ExdDataGenerated::getLogKindCategoryText( uint32_t LogKindCategoryTextId )
{
   try
   {
      auto row = m_LogKindCategoryTextDat.get_row( LogKindCategoryTextId );
      auto info = boost::make_shared< LogKindCategoryText >( LogKindCategoryTextId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::LogMessage >
   Core::Data::ExdDataGenerated::getLogMessage( uint32_t LogMessageId )
{
   try
   {
      auto row = m_LogMessageDat.get_row( LogMessageId );
      auto info = boost::make_shared< LogMessage >( LogMessageId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MacroIcon >
   Core::Data::ExdDataGenerated::getMacroIcon( uint32_t MacroIconId )
{
   try
   {
      auto row = m_MacroIconDat.get_row( MacroIconId );
      auto info = boost::make_shared< MacroIcon >( MacroIconId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MacroIconRedirectOld >
   Core::Data::ExdDataGenerated::getMacroIconRedirectOld( uint32_t MacroIconRedirectOldId )
{
   try
   {
      auto row = m_MacroIconRedirectOldDat.get_row( MacroIconRedirectOldId );
      auto info = boost::make_shared< MacroIconRedirectOld >( MacroIconRedirectOldId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MainCommand >
   Core::Data::ExdDataGenerated::getMainCommand( uint32_t MainCommandId )
{
   try
   {
      auto row = m_MainCommandDat.get_row( MainCommandId );
      auto info = boost::make_shared< MainCommand >( MainCommandId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MainCommandCategory >
   Core::Data::ExdDataGenerated::getMainCommandCategory( uint32_t MainCommandCategoryId )
{
   try
   {
      auto row = m_MainCommandCategoryDat.get_row( MainCommandCategoryId );
      auto info = boost::make_shared< MainCommandCategory >( MainCommandCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Map >
   Core::Data::ExdDataGenerated::getMap( uint32_t MapId )
{
   try
   {
      auto row = m_MapDat.get_row( MapId );
      auto info = boost::make_shared< Map >( MapId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MapMarker >
   Core::Data::ExdDataGenerated::getMapMarker( uint32_t MapMarkerId )
{
   try
   {
      auto row = m_MapMarkerDat.get_row( MapMarkerId );
      auto info = boost::make_shared< MapMarker >( MapMarkerId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MapSymbol >
   Core::Data::ExdDataGenerated::getMapSymbol( uint32_t MapSymbolId )
{
   try
   {
      auto row = m_MapSymbolDat.get_row( MapSymbolId );
      auto info = boost::make_shared< MapSymbol >( MapSymbolId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MasterpieceSupplyDuty >
   Core::Data::ExdDataGenerated::getMasterpieceSupplyDuty( uint32_t MasterpieceSupplyDutyId )
{
   try
   {
      auto row = m_MasterpieceSupplyDutyDat.get_row( MasterpieceSupplyDutyId );
      auto info = boost::make_shared< MasterpieceSupplyDuty >( MasterpieceSupplyDutyId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MasterpieceSupplyMultiplier >
   Core::Data::ExdDataGenerated::getMasterpieceSupplyMultiplier( uint32_t MasterpieceSupplyMultiplierId )
{
   try
   {
      auto row = m_MasterpieceSupplyMultiplierDat.get_row( MasterpieceSupplyMultiplierId );
      auto info = boost::make_shared< MasterpieceSupplyMultiplier >( MasterpieceSupplyMultiplierId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Materia >
   Core::Data::ExdDataGenerated::getMateria( uint32_t MateriaId )
{
   try
   {
      auto row = m_MateriaDat.get_row( MateriaId );
      auto info = boost::make_shared< Materia >( MateriaId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MinionRace >
   Core::Data::ExdDataGenerated::getMinionRace( uint32_t MinionRaceId )
{
   try
   {
      auto row = m_MinionRaceDat.get_row( MinionRaceId );
      auto info = boost::make_shared< MinionRace >( MinionRaceId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MinionRules >
   Core::Data::ExdDataGenerated::getMinionRules( uint32_t MinionRulesId )
{
   try
   {
      auto row = m_MinionRulesDat.get_row( MinionRulesId );
      auto info = boost::make_shared< MinionRules >( MinionRulesId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MinionSkillType >
   Core::Data::ExdDataGenerated::getMinionSkillType( uint32_t MinionSkillTypeId )
{
   try
   {
      auto row = m_MinionSkillTypeDat.get_row( MinionSkillTypeId );
      auto info = boost::make_shared< MinionSkillType >( MinionSkillTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MobHuntTarget >
   Core::Data::ExdDataGenerated::getMobHuntTarget( uint32_t MobHuntTargetId )
{
   try
   {
      auto row = m_MobHuntTargetDat.get_row( MobHuntTargetId );
      auto info = boost::make_shared< MobHuntTarget >( MobHuntTargetId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ModelChara >
   Core::Data::ExdDataGenerated::getModelChara( uint32_t ModelCharaId )
{
   try
   {
      auto row = m_ModelCharaDat.get_row( ModelCharaId );
      auto info = boost::make_shared< ModelChara >( ModelCharaId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MonsterNote >
   Core::Data::ExdDataGenerated::getMonsterNote( uint32_t MonsterNoteId )
{
   try
   {
      auto row = m_MonsterNoteDat.get_row( MonsterNoteId );
      auto info = boost::make_shared< MonsterNote >( MonsterNoteId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MonsterNoteTarget >
   Core::Data::ExdDataGenerated::getMonsterNoteTarget( uint32_t MonsterNoteTargetId )
{
   try
   {
      auto row = m_MonsterNoteTargetDat.get_row( MonsterNoteTargetId );
      auto info = boost::make_shared< MonsterNoteTarget >( MonsterNoteTargetId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Mount >
   Core::Data::ExdDataGenerated::getMount( uint32_t MountId )
{
   try
   {
      auto row = m_MountDat.get_row( MountId );
      auto info = boost::make_shared< Mount >( MountId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::MountAction >
   Core::Data::ExdDataGenerated::getMountAction( uint32_t MountActionId )
{
   try
   {
      auto row = m_MountActionDat.get_row( MountActionId );
      auto info = boost::make_shared< MountAction >( MountActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::NpcEquip >
   Core::Data::ExdDataGenerated::getNpcEquip( uint32_t NpcEquipId )
{
   try
   {
      auto row = m_NpcEquipDat.get_row( NpcEquipId );
      auto info = boost::make_shared< NpcEquip >( NpcEquipId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Omen >
   Core::Data::ExdDataGenerated::getOmen( uint32_t OmenId )
{
   try
   {
      auto row = m_OmenDat.get_row( OmenId );
      auto info = boost::make_shared< Omen >( OmenId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::OnlineStatus >
   Core::Data::ExdDataGenerated::getOnlineStatus( uint32_t OnlineStatusId )
{
   try
   {
      auto row = m_OnlineStatusDat.get_row( OnlineStatusId );
      auto info = boost::make_shared< OnlineStatus >( OnlineStatusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Orchestrion >
   Core::Data::ExdDataGenerated::getOrchestrion( uint32_t OrchestrionId )
{
   try
   {
      auto row = m_OrchestrionDat.get_row( OrchestrionId );
      auto info = boost::make_shared< Orchestrion >( OrchestrionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::OrchestrionPath >
   Core::Data::ExdDataGenerated::getOrchestrionPath( uint32_t OrchestrionPathId )
{
   try
   {
      auto row = m_OrchestrionPathDat.get_row( OrchestrionPathId );
      auto info = boost::make_shared< OrchestrionPath >( OrchestrionPathId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ParamGrow >
   Core::Data::ExdDataGenerated::getParamGrow( uint32_t ParamGrowId )
{
   try
   {
      auto row = m_ParamGrowDat.get_row( ParamGrowId );
      auto info = boost::make_shared< ParamGrow >( ParamGrowId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Pet >
   Core::Data::ExdDataGenerated::getPet( uint32_t PetId )
{
   try
   {
      auto row = m_PetDat.get_row( PetId );
      auto info = boost::make_shared< Pet >( PetId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::PetAction >
   Core::Data::ExdDataGenerated::getPetAction( uint32_t PetActionId )
{
   try
   {
      auto row = m_PetActionDat.get_row( PetActionId );
      auto info = boost::make_shared< PetAction >( PetActionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Picture >
   Core::Data::ExdDataGenerated::getPicture( uint32_t PictureId )
{
   try
   {
      auto row = m_PictureDat.get_row( PictureId );
      auto info = boost::make_shared< Picture >( PictureId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::PlaceName >
   Core::Data::ExdDataGenerated::getPlaceName( uint32_t PlaceNameId )
{
   try
   {
      auto row = m_PlaceNameDat.get_row( PlaceNameId );
      auto info = boost::make_shared< PlaceName >( PlaceNameId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Quest >
   Core::Data::ExdDataGenerated::getQuest( uint32_t QuestId )
{
   try
   {
      auto row = m_QuestDat.get_row( QuestId );
      auto info = boost::make_shared< Quest >( QuestId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::QuestRewardOther >
   Core::Data::ExdDataGenerated::getQuestRewardOther( uint32_t QuestRewardOtherId )
{
   try
   {
      auto row = m_QuestRewardOtherDat.get_row( QuestRewardOtherId );
      auto info = boost::make_shared< QuestRewardOther >( QuestRewardOtherId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Race >
   Core::Data::ExdDataGenerated::getRace( uint32_t RaceId )
{
   try
   {
      auto row = m_RaceDat.get_row( RaceId );
      auto info = boost::make_shared< Race >( RaceId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RacingChocoboItem >
   Core::Data::ExdDataGenerated::getRacingChocoboItem( uint32_t RacingChocoboItemId )
{
   try
   {
      auto row = m_RacingChocoboItemDat.get_row( RacingChocoboItemId );
      auto info = boost::make_shared< RacingChocoboItem >( RacingChocoboItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RacingChocoboName >
   Core::Data::ExdDataGenerated::getRacingChocoboName( uint32_t RacingChocoboNameId )
{
   try
   {
      auto row = m_RacingChocoboNameDat.get_row( RacingChocoboNameId );
      auto info = boost::make_shared< RacingChocoboName >( RacingChocoboNameId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RacingChocoboNameCategory >
   Core::Data::ExdDataGenerated::getRacingChocoboNameCategory( uint32_t RacingChocoboNameCategoryId )
{
   try
   {
      auto row = m_RacingChocoboNameCategoryDat.get_row( RacingChocoboNameCategoryId );
      auto info = boost::make_shared< RacingChocoboNameCategory >( RacingChocoboNameCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RacingChocoboNameInfo >
   Core::Data::ExdDataGenerated::getRacingChocoboNameInfo( uint32_t RacingChocoboNameInfoId )
{
   try
   {
      auto row = m_RacingChocoboNameInfoDat.get_row( RacingChocoboNameInfoId );
      auto info = boost::make_shared< RacingChocoboNameInfo >( RacingChocoboNameInfoId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RacingChocoboParam >
   Core::Data::ExdDataGenerated::getRacingChocoboParam( uint32_t RacingChocoboParamId )
{
   try
   {
      auto row = m_RacingChocoboParamDat.get_row( RacingChocoboParamId );
      auto info = boost::make_shared< RacingChocoboParam >( RacingChocoboParamId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Recipe >
   Core::Data::ExdDataGenerated::getRecipe( uint32_t RecipeId )
{
   try
   {
      auto row = m_RecipeDat.get_row( RecipeId );
      auto info = boost::make_shared< Recipe >( RecipeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RecipeElement >
   Core::Data::ExdDataGenerated::getRecipeElement( uint32_t RecipeElementId )
{
   try
   {
      auto row = m_RecipeElementDat.get_row( RecipeElementId );
      auto info = boost::make_shared< RecipeElement >( RecipeElementId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RecipeLevelTable >
   Core::Data::ExdDataGenerated::getRecipeLevelTable( uint32_t RecipeLevelTableId )
{
   try
   {
      auto row = m_RecipeLevelTableDat.get_row( RecipeLevelTableId );
      auto info = boost::make_shared< RecipeLevelTable >( RecipeLevelTableId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RecipeNotebookList >
   Core::Data::ExdDataGenerated::getRecipeNotebookList( uint32_t RecipeNotebookListId )
{
   try
   {
      auto row = m_RecipeNotebookListDat.get_row( RecipeNotebookListId );
      auto info = boost::make_shared< RecipeNotebookList >( RecipeNotebookListId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Relic >
   Core::Data::ExdDataGenerated::getRelic( uint32_t RelicId )
{
   try
   {
      auto row = m_RelicDat.get_row( RelicId );
      auto info = boost::make_shared< Relic >( RelicId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Relic3 >
   Core::Data::ExdDataGenerated::getRelic3( uint32_t Relic3Id )
{
   try
   {
      auto row = m_Relic3Dat.get_row( Relic3Id );
      auto info = boost::make_shared< Relic3 >( Relic3Id, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RelicItem >
   Core::Data::ExdDataGenerated::getRelicItem( uint32_t RelicItemId )
{
   try
   {
      auto row = m_RelicItemDat.get_row( RelicItemId );
      auto info = boost::make_shared< RelicItem >( RelicItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RelicNote >
   Core::Data::ExdDataGenerated::getRelicNote( uint32_t RelicNoteId )
{
   try
   {
      auto row = m_RelicNoteDat.get_row( RelicNoteId );
      auto info = boost::make_shared< RelicNote >( RelicNoteId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RelicNoteCategory >
   Core::Data::ExdDataGenerated::getRelicNoteCategory( uint32_t RelicNoteCategoryId )
{
   try
   {
      auto row = m_RelicNoteCategoryDat.get_row( RelicNoteCategoryId );
      auto info = boost::make_shared< RelicNoteCategory >( RelicNoteCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RetainerTask >
   Core::Data::ExdDataGenerated::getRetainerTask( uint32_t RetainerTaskId )
{
   try
   {
      auto row = m_RetainerTaskDat.get_row( RetainerTaskId );
      auto info = boost::make_shared< RetainerTask >( RetainerTaskId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RetainerTaskNormal >
   Core::Data::ExdDataGenerated::getRetainerTaskNormal( uint32_t RetainerTaskNormalId )
{
   try
   {
      auto row = m_RetainerTaskNormalDat.get_row( RetainerTaskNormalId );
      auto info = boost::make_shared< RetainerTaskNormal >( RetainerTaskNormalId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RetainerTaskParameter >
   Core::Data::ExdDataGenerated::getRetainerTaskParameter( uint32_t RetainerTaskParameterId )
{
   try
   {
      auto row = m_RetainerTaskParameterDat.get_row( RetainerTaskParameterId );
      auto info = boost::make_shared< RetainerTaskParameter >( RetainerTaskParameterId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::RetainerTaskRandom >
   Core::Data::ExdDataGenerated::getRetainerTaskRandom( uint32_t RetainerTaskRandomId )
{
   try
   {
      auto row = m_RetainerTaskRandomDat.get_row( RetainerTaskRandomId );
      auto info = boost::make_shared< RetainerTaskRandom >( RetainerTaskRandomId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Salvage >
   Core::Data::ExdDataGenerated::getSalvage( uint32_t SalvageId )
{
   try
   {
      auto row = m_SalvageDat.get_row( SalvageId );
      auto info = boost::make_shared< Salvage >( SalvageId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SatisfactionNpc >
   Core::Data::ExdDataGenerated::getSatisfactionNpc( uint32_t SatisfactionNpcId )
{
   try
   {
      auto row = m_SatisfactionNpcDat.get_row( SatisfactionNpcId );
      auto info = boost::make_shared< SatisfactionNpc >( SatisfactionNpcId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SatisfactionSupply >
   Core::Data::ExdDataGenerated::getSatisfactionSupply( uint32_t SatisfactionSupplyId )
{
   try
   {
      auto row = m_SatisfactionSupplyDat.get_row( SatisfactionSupplyId );
      auto info = boost::make_shared< SatisfactionSupply >( SatisfactionSupplyId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SatisfactionSupplyReward >
   Core::Data::ExdDataGenerated::getSatisfactionSupplyReward( uint32_t SatisfactionSupplyRewardId )
{
   try
   {
      auto row = m_SatisfactionSupplyRewardDat.get_row( SatisfactionSupplyRewardId );
      auto info = boost::make_shared< SatisfactionSupplyReward >( SatisfactionSupplyRewardId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::ScreenImage >
   Core::Data::ExdDataGenerated::getScreenImage( uint32_t ScreenImageId )
{
   try
   {
      auto row = m_ScreenImageDat.get_row( ScreenImageId );
      auto info = boost::make_shared< ScreenImage >( ScreenImageId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SecretRecipeBook >
   Core::Data::ExdDataGenerated::getSecretRecipeBook( uint32_t SecretRecipeBookId )
{
   try
   {
      auto row = m_SecretRecipeBookDat.get_row( SecretRecipeBookId );
      auto info = boost::make_shared< SecretRecipeBook >( SecretRecipeBookId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SpearfishingItem >
   Core::Data::ExdDataGenerated::getSpearfishingItem( uint32_t SpearfishingItemId )
{
   try
   {
      auto row = m_SpearfishingItemDat.get_row( SpearfishingItemId );
      auto info = boost::make_shared< SpearfishingItem >( SpearfishingItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SpearfishingNotebook >
   Core::Data::ExdDataGenerated::getSpearfishingNotebook( uint32_t SpearfishingNotebookId )
{
   try
   {
      auto row = m_SpearfishingNotebookDat.get_row( SpearfishingNotebookId );
      auto info = boost::make_shared< SpearfishingNotebook >( SpearfishingNotebookId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SpecialShop >
   Core::Data::ExdDataGenerated::getSpecialShop( uint32_t SpecialShopId )
{
   try
   {
      auto row = m_SpecialShopDat.get_row( SpecialShopId );
      auto info = boost::make_shared< SpecialShop >( SpecialShopId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SpecialShopItemCategory >
   Core::Data::ExdDataGenerated::getSpecialShopItemCategory( uint32_t SpecialShopItemCategoryId )
{
   try
   {
      auto row = m_SpecialShopItemCategoryDat.get_row( SpecialShopItemCategoryId );
      auto info = boost::make_shared< SpecialShopItemCategory >( SpecialShopItemCategoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Stain >
   Core::Data::ExdDataGenerated::getStain( uint32_t StainId )
{
   try
   {
      auto row = m_StainDat.get_row( StainId );
      auto info = boost::make_shared< Stain >( StainId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Status >
   Core::Data::ExdDataGenerated::getStatus( uint32_t StatusId )
{
   try
   {
      auto row = m_StatusDat.get_row( StatusId );
      auto info = boost::make_shared< Status >( StatusId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Story >
   Core::Data::ExdDataGenerated::getStory( uint32_t StoryId )
{
   try
   {
      auto row = m_StoryDat.get_row( StoryId );
      auto info = boost::make_shared< Story >( StoryId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::SwitchTalk >
   Core::Data::ExdDataGenerated::getSwitchTalk( uint32_t SwitchTalkId )
{
   try
   {
      auto row = m_SwitchTalkDat.get_row( SwitchTalkId );
      auto info = boost::make_shared< SwitchTalk >( SwitchTalkId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TerritoryType >
   Core::Data::ExdDataGenerated::getTerritoryType( uint32_t TerritoryTypeId )
{
   try
   {
      auto row = m_TerritoryTypeDat.get_row( TerritoryTypeId );
      auto info = boost::make_shared< TerritoryType >( TerritoryTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TextCommand >
   Core::Data::ExdDataGenerated::getTextCommand( uint32_t TextCommandId )
{
   try
   {
      auto row = m_TextCommandDat.get_row( TextCommandId );
      auto info = boost::make_shared< TextCommand >( TextCommandId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Title >
   Core::Data::ExdDataGenerated::getTitle( uint32_t TitleId )
{
   try
   {
      auto row = m_TitleDat.get_row( TitleId );
      auto info = boost::make_shared< Title >( TitleId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Tomestones >
   Core::Data::ExdDataGenerated::getTomestones( uint32_t TomestonesId )
{
   try
   {
      auto row = m_TomestonesDat.get_row( TomestonesId );
      auto info = boost::make_shared< Tomestones >( TomestonesId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TomestonesItem >
   Core::Data::ExdDataGenerated::getTomestonesItem( uint32_t TomestonesItemId )
{
   try
   {
      auto row = m_TomestonesItemDat.get_row( TomestonesItemId );
      auto info = boost::make_shared< TomestonesItem >( TomestonesItemId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TopicSelect >
   Core::Data::ExdDataGenerated::getTopicSelect( uint32_t TopicSelectId )
{
   try
   {
      auto row = m_TopicSelectDat.get_row( TopicSelectId );
      auto info = boost::make_shared< TopicSelect >( TopicSelectId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Town >
   Core::Data::ExdDataGenerated::getTown( uint32_t TownId )
{
   try
   {
      auto row = m_TownDat.get_row( TownId );
      auto info = boost::make_shared< Town >( TownId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Trait >
   Core::Data::ExdDataGenerated::getTrait( uint32_t TraitId )
{
   try
   {
      auto row = m_TraitDat.get_row( TraitId );
      auto info = boost::make_shared< Trait >( TraitId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TraitRecast >
   Core::Data::ExdDataGenerated::getTraitRecast( uint32_t TraitRecastId )
{
   try
   {
      auto row = m_TraitRecastDat.get_row( TraitRecastId );
      auto info = boost::make_shared< TraitRecast >( TraitRecastId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TraitTransient >
   Core::Data::ExdDataGenerated::getTraitTransient( uint32_t TraitTransientId )
{
   try
   {
      auto row = m_TraitTransientDat.get_row( TraitTransientId );
      auto info = boost::make_shared< TraitTransient >( TraitTransientId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Tribe >
   Core::Data::ExdDataGenerated::getTribe( uint32_t TribeId )
{
   try
   {
      auto row = m_TribeDat.get_row( TribeId );
      auto info = boost::make_shared< Tribe >( TribeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriad >
   Core::Data::ExdDataGenerated::getTripleTriad( uint32_t TripleTriadId )
{
   try
   {
      auto row = m_TripleTriadDat.get_row( TripleTriadId );
      auto info = boost::make_shared< TripleTriad >( TripleTriadId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriadCard >
   Core::Data::ExdDataGenerated::getTripleTriadCard( uint32_t TripleTriadCardId )
{
   try
   {
      auto row = m_TripleTriadCardDat.get_row( TripleTriadCardId );
      auto info = boost::make_shared< TripleTriadCard >( TripleTriadCardId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriadCardRarity >
   Core::Data::ExdDataGenerated::getTripleTriadCardRarity( uint32_t TripleTriadCardRarityId )
{
   try
   {
      auto row = m_TripleTriadCardRarityDat.get_row( TripleTriadCardRarityId );
      auto info = boost::make_shared< TripleTriadCardRarity >( TripleTriadCardRarityId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriadCardResident >
   Core::Data::ExdDataGenerated::getTripleTriadCardResident( uint32_t TripleTriadCardResidentId )
{
   try
   {
      auto row = m_TripleTriadCardResidentDat.get_row( TripleTriadCardResidentId );
      auto info = boost::make_shared< TripleTriadCardResident >( TripleTriadCardResidentId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriadCardType >
   Core::Data::ExdDataGenerated::getTripleTriadCardType( uint32_t TripleTriadCardTypeId )
{
   try
   {
      auto row = m_TripleTriadCardTypeDat.get_row( TripleTriadCardTypeId );
      auto info = boost::make_shared< TripleTriadCardType >( TripleTriadCardTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriadCompetition >
   Core::Data::ExdDataGenerated::getTripleTriadCompetition( uint32_t TripleTriadCompetitionId )
{
   try
   {
      auto row = m_TripleTriadCompetitionDat.get_row( TripleTriadCompetitionId );
      auto info = boost::make_shared< TripleTriadCompetition >( TripleTriadCompetitionId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TripleTriadRule >
   Core::Data::ExdDataGenerated::getTripleTriadRule( uint32_t TripleTriadRuleId )
{
   try
   {
      auto row = m_TripleTriadRuleDat.get_row( TripleTriadRuleId );
      auto info = boost::make_shared< TripleTriadRule >( TripleTriadRuleId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Tutorial >
   Core::Data::ExdDataGenerated::getTutorial( uint32_t TutorialId )
{
   try
   {
      auto row = m_TutorialDat.get_row( TutorialId );
      auto info = boost::make_shared< Tutorial >( TutorialId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TutorialDPS >
   Core::Data::ExdDataGenerated::getTutorialDPS( uint32_t TutorialDPSId )
{
   try
   {
      auto row = m_TutorialDPSDat.get_row( TutorialDPSId );
      auto info = boost::make_shared< TutorialDPS >( TutorialDPSId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TutorialHealer >
   Core::Data::ExdDataGenerated::getTutorialHealer( uint32_t TutorialHealerId )
{
   try
   {
      auto row = m_TutorialHealerDat.get_row( TutorialHealerId );
      auto info = boost::make_shared< TutorialHealer >( TutorialHealerId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::TutorialTank >
   Core::Data::ExdDataGenerated::getTutorialTank( uint32_t TutorialTankId )
{
   try
   {
      auto row = m_TutorialTankDat.get_row( TutorialTankId );
      auto info = boost::make_shared< TutorialTank >( TutorialTankId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Warp >
   Core::Data::ExdDataGenerated::getWarp( uint32_t WarpId )
{
   try
   {
      auto row = m_WarpDat.get_row( WarpId );
      auto info = boost::make_shared< Warp >( WarpId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::Weather >
   Core::Data::ExdDataGenerated::getWeather( uint32_t WeatherId )
{
   try
   {
      auto row = m_WeatherDat.get_row( WeatherId );
      auto info = boost::make_shared< Weather >( WeatherId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::WeatherGroup >
   Core::Data::ExdDataGenerated::getWeatherGroup( uint32_t WeatherGroupId )
{
   try
   {
      auto row = m_WeatherGroupDat.get_row( WeatherGroupId );
      auto info = boost::make_shared< WeatherGroup >( WeatherGroupId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::WeatherRate >
   Core::Data::ExdDataGenerated::getWeatherRate( uint32_t WeatherRateId )
{
   try
   {
      auto row = m_WeatherRateDat.get_row( WeatherRateId );
      auto info = boost::make_shared< WeatherRate >( WeatherRateId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::WeeklyBingoOrderData >
   Core::Data::ExdDataGenerated::getWeeklyBingoOrderData( uint32_t WeeklyBingoOrderDataId )
{
   try
   {
      auto row = m_WeeklyBingoOrderDataDat.get_row( WeeklyBingoOrderDataId );
      auto info = boost::make_shared< WeeklyBingoOrderData >( WeeklyBingoOrderDataId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::WeeklyBingoRewardData >
   Core::Data::ExdDataGenerated::getWeeklyBingoRewardData( uint32_t WeeklyBingoRewardDataId )
{
   try
   {
      auto row = m_WeeklyBingoRewardDataDat.get_row( WeeklyBingoRewardDataId );
      auto info = boost::make_shared< WeeklyBingoRewardData >( WeeklyBingoRewardDataId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::WeeklyBingoText >
   Core::Data::ExdDataGenerated::getWeeklyBingoText( uint32_t WeeklyBingoTextId )
{
   try
   {
      auto row = m_WeeklyBingoTextDat.get_row( WeeklyBingoTextId );
      auto info = boost::make_shared< WeeklyBingoText >( WeeklyBingoTextId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}
boost::shared_ptr< Core::Data::WorldDCGroupType >
   Core::Data::ExdDataGenerated::getWorldDCGroupType( uint32_t WorldDCGroupTypeId )
{
   try
   {
      auto row = m_WorldDCGroupTypeDat.get_row( WorldDCGroupTypeId );
      auto info = boost::make_shared< WorldDCGroupType >( WorldDCGroupTypeId, this );
      return info;
   }
   catch( ... )
   {
      return nullptr;
   }
   return nullptr;
}




