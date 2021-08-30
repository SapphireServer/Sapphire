#include <Common.h>
#include <Service.h>

#include <datReader/DatCategories/bg/lgb.h>
#include <Exd/ExdDataGenerated.h>

#include <Event/EventHandler.h>

#include <Network/CommonActorControl.h>
#include <Network/GameConnection.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>

#include <Logging/Logger.h>
#include <Util/Util.cpp>

#include <Actor/Player.h>
#include <Inventory/Item.h>

#include "MapMgr.h"
#include "TerritoryMgr.h"

#include "ServerMgr.h"

using namespace Sapphire::Event;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::World::Manager::MapMgr::MapMgr()
{  
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  size_t count = 0;

  for( auto quest : exdData.m_QuestDat.get_rows() )
  {
    if( exdData.getField< std::string >( quest.second, 1 ).empty() ) // id
      continue;

    auto& questData = m_questData[ quest.first ];

    questData.previousQuestJoin = exdData.getField< uint8_t >( quest.second, 8 );
    questData.previousQuestKeys[ 0 ] = exdData.getField< uint32_t >( quest.second, 9 );
    questData.previousQuest0Sequence = exdData.getField< uint8_t >( quest.second, 10 );
    questData.previousQuestKeys[ 1 ] = exdData.getField< uint32_t >( quest.second, 11 );
    questData.previousQuestKeys[ 2 ] = exdData.getField< uint32_t >( quest.second, 12 );

    questData.questLockJoin = exdData.getField< uint8_t >( quest.second, 13 );
    questData.questLockKeys[ 0 ] = exdData.getField< uint32_t >( quest.second, 14 );
    questData.questLockKeys[ 1 ] = exdData.getField< uint32_t >( quest.second, 15 );

    questData.classJobRequirements[ 0 ].classJobLevel = exdData.getField< uint16_t >( quest.second, 4 );
    auto classJobsCategory = exdData.get< Data::ClassJobCategory >( exdData.getField< uint8_t >( quest.second, 3 ) );
    for( int32_t i = 0; i <= Common::CLASSJOB_TOTAL; i++ )
      questData.classJobRequirements[ 0 ].classJobCategoryMask.set( i, ( &classJobsCategory->aDV )[ i ] );
      
    questData.classJobRequirements[ 1 ].classJobLevel = exdData.getField< uint16_t >( quest.second, 7 );
    classJobsCategory = exdData.get< Data::ClassJobCategory >( exdData.getField< uint8_t >( quest.second, 6 ) );
    for( int32_t i = 0; i <= Common::CLASSJOB_TOTAL; i++ )
      questData.classJobRequirements[ 1 ].classJobCategoryMask.set( i, ( &classJobsCategory->aDV )[ i ] );

    questData.column18 = exdData.getField< uint8_t >( quest.second, 18 );

    questData.classJobUnlock = exdData.getField< uint8_t >( quest.second, 19 );

    questData.requiredGC = exdData.getField< uint8_t >( quest.second, 20 );
    questData.requiredGCRank = exdData.getField< uint8_t >( quest.second, 21 );

    questData.startTown = exdData.getField< uint8_t >( quest.second, 17 );

    questData.header = exdData.getField< uint16_t >( quest.second, 16 );

    questData.instanceContentJoin = exdData.getField< uint8_t >( quest.second, 22 );
    questData.instanceContent[ 0 ] = exdData.getField< uint32_t >( quest.second, 23 );
    questData.instanceContent[ 1 ] = exdData.getField< uint32_t >( quest.second, 24 );
    questData.instanceContent[ 2 ] = exdData.getField< uint32_t >( quest.second, 25 );

    questData.festival = exdData.getField< uint8_t >( quest.second, 26 );
    questData.festivalBegin = exdData.getField< uint8_t >( quest.second, 27 );
    questData.festivalEnd = exdData.getField< uint8_t >( quest.second, 28 );
    questData.bellStart = exdData.getField< uint16_t >( quest.second, 29 );
    questData.bellEnd = exdData.getField< uint16_t >( quest.second, 30 );   

    questData.repeatIntervalType = exdData.getField< uint8_t >( quest.second, 44 );
    questData.questRepeatFlag = exdData.getField< uint8_t >( quest.second, 45 ); 

    questData.beastTribe = exdData.getField< uint8_t >( quest.second, 31 );
    questData.beastReputationRank = exdData.getField< uint8_t >( quest.second, 32 );
    questData.beastReputationValue = exdData.getField< uint16_t >( quest.second, 33 );

    questData.mount = exdData.getField< int32_t >( quest.second, 36 );

    questData.satisfactionNpc = exdData.getField< uint8_t >( quest.second, 34 );
    questData.satisfactionRank = exdData.getField< uint8_t >( quest.second, 35 );

    questData.issuer = exdData.getField< uint32_t >( quest.second, 39 );

    questData.deliveryQuest = exdData.getField< uint8_t >( quest.second, 38 );

    questData.expansion = exdData.getField< uint8_t >( quest.second, 2 );

    questData.type = exdData.getField< uint8_t >(quest.second, 47);

    questData.isRepeatable = exdData.getField< bool >( quest.second, 43 );
    questData.isHouseRequired = exdData.getField< bool >( quest.second, 37 );

    questData.iconValid = exdData.get< Data::EventIconType >( exdData.getField< uint8_t >( quest.second, 1512 ) )->mapIconAvailable + 1 + questData.isRepeatable;
    questData.iconInvalid = exdData.get< Data::EventIconType >( exdData.getField< uint8_t >( quest.second, 1512 ) )->mapIconInvalid + 1 + questData.isRepeatable;

    uint32_t issuerLevelId = exdData.getField< uint32_t >( quest.second, 40 );
    if( issuerLevelId != 0 )
    {
      if( count++ % 100 == 0 )
        std::cout << ".";

      auto level = exdData.get< Data::Level >( issuerLevelId );
      auto territory = level->territory;

      if( territory == 0 )
        territory = exdData.get< Data::Map >( level->map )->territoryType;

      EventData eventData;
      eventData.iconId = questData.iconValid;
      eventData.levelId = issuerLevelId;
      eventData.actorId = questData.issuer;

      m_mapData[ territory ].emplace( quest.first, eventData );
    }
  }
  
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();
  auto m_gameData = new xiv::dat::GameData( serverMgr.getConfig().global.general.dataPath );

  std::set< std::string > bgSet;

  for( auto territoryTypeId : exdData.getTerritoryTypeIdList() )
  {
    auto territoryType = exdData.get< Data::TerritoryType >( territoryTypeId );
    if( territoryType->bg.empty() )
      continue;

    if( bgSet.find( territoryType->bg ) != bgSet.end() )
      continue;
    else
      bgSet.insert( territoryType->bg );

    std::string planeventLgbPath( "bg/" + territoryType->bg.substr( 0, territoryType->bg.rfind( '/' ) ) + "/planevent.lgb" );
    auto planeventFile = m_gameData->getFile( planeventLgbPath );
    auto planeventData = planeventFile->access_data_sections().at( 0 );
    LGB_FILE planeventLgb( &planeventData[ 0 ], "planevent" );

    for( const auto& group : planeventLgb.groups )
    {
      for( const auto& pEntry : group.entries )
      {
        if( pEntry->getType() == LgbEntryType::EventNpc )
        {
          auto pNpc = reinterpret_cast< LGB_ENPC_ENTRY* >( pEntry.get() );

          auto eNpcData = exdData.get< Data::ENpcBase >( pNpc->data.enpcId )->eNpcData;

          for( auto npcData : eNpcData )
          {
            if( npcData == 0 )
              continue; // Some npcs have data gaps, so we have to iterate through the entire array

            if( count++ % 1000 == 0 )
              std::cout << ".";

            EventData eventData;
            eventData.levelId = pNpc->data.instanceId;
            eventData.actorId = pNpc->data.enpcId;

            auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( npcData >> 16 );

            switch( eventHandlerType )
            {
              case EventHandler::EventHandlerType::GuildLeveAssignment:
              {
                eventData.iconId = exdData.get< Data::EventIconType >( 5 )->mapIconAvailable + 1;

                m_mapData[ territoryTypeId ].insert( std::make_pair( npcData, eventData ) );
                break;
              }

              case EventHandler::EventHandlerType::CustomTalk:
              {
                // Include only the beginner arena icon yet. There a few other ones, that aren't referenced in the game files (Some examples are: The Triple Triad Tournament npc which has multiple icons and the ocean fishing icon)
                if( npcData == 721223 )
                {
                  auto customTalk = exdData.get< Data::CustomTalk >( npcData );

                  eventData.iconId = customTalk->iconMap;

                  m_mapData[ territoryTypeId ].insert( std::make_pair( npcData, eventData ) );
                }
                break;
              }

              case EventHandler::EventHandlerType::GuildOrderGuide:
              {
                eventData.iconId = exdData.get< Data::EventIconType >( 6 )->mapIconAvailable + 1;

                m_mapData[ territoryTypeId ].insert( std::make_pair( npcData, eventData ) );
                break;
              }

              case EventHandler::EventHandlerType::TripleTriad:
              {
                eventData.iconId = exdData.get< Data::EventIconType >( 7 )->mapIconAvailable + 1;

                m_mapData[ territoryTypeId ].insert( std::make_pair( npcData, eventData ) );
                break;
              }

              case EventHandler::EventHandlerType::PreHandler:
              {
                //I think this is used in Bozja and Zadnor, need evidence
                //m_mapData[ territoryTypeId ].insert( std::make_pair( eventData, 0 ) );
                break;
              }
            }
          }
        }
      }
    }
  }
  std::cout << "\n";
}

void Sapphire::World::Manager::MapMgr::updateAll( Entity::Player& player )
{
  auto& mapData = m_mapData[ player.getTerritoryTypeId() ];
  std::multimap< uint32_t, EventData, less > newMapData;

  for( auto eventData : mapData )
  {
    switch( static_cast< EventHandler::EventHandlerType >( eventData.first >> 16 ) )
    {
      case EventHandler::EventHandlerType::Quest:
      {
        if( isQuestAvailable( player, eventData ) )
          newMapData.insert( eventData );

        break;
      }

      case EventHandler::EventHandlerType::GuildLeveAssignment:
      {
        auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
        auto guildLeve = exdData.get< Data::GuildleveAssignment >( eventData.first );

        if( player.isActionLearned( 5 )  )
        {
          if( player.isQuestCompleted( guildLeve->quest[ 0 ] ) )
          {
            if( eventData.first >= 393239 && eventData.first <= 393247 )
            {
              if( player.getGc() != 0 )
                newMapData.insert( eventData );
            }
            else
            {
              newMapData.insert( eventData );
            }
          }
          else if( eventData.first == 393217 || eventData.first == 393223 || eventData.first == 393225 ) // Leve npc locations: Bentbranch / Horizon / Swiftperch
          {
            if( player.isQuestCompleted( 220 ) || player.isQuestCompleted( 687 ) || player.isQuestCompleted( 693 ) )
              newMapData.insert( eventData );
          }
        }

        break;
      }

      case EventHandler::EventHandlerType::CustomTalk:
      {
        newMapData.insert( eventData );

        break;
      }

      case EventHandler::EventHandlerType::GuildOrderGuide:
      {
        if( player.isActionLearned( 7 ) )
          newMapData.insert( eventData );

        break;
      }

      case EventHandler::EventHandlerType::TripleTriad:
      {
        if( eventData.first == 2293771 ) // Triple Triad Master npc for now only
          newMapData.insert( eventData );

        break;
      }
    }
  }
  
  sendPackets( player, newMapData, All );
}

void Sapphire::World::Manager::MapMgr::updateQuests( Entity::Player& player )
{
  auto& mapData = m_mapData[ player.getTerritoryTypeId() ];
  std::multimap< uint32_t, EventData, less > newMapData;

  for( auto& eventData : mapData )
  {
    if( ( eventData.first >> 16 ) == static_cast< uint16_t >( EventHandler::EventHandlerType::Quest ) )
    {
      if( isQuestAvailable( player, eventData ) )
        newMapData.insert( eventData );
    }
  }
  
  sendPackets( player, newMapData, Quest );;
}

bool Sapphire::World::Manager::MapMgr::isQuestAvailable( Entity::Player& player, std::pair< const uint32_t, EventData >& eventData )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  auto& quest = m_questData[ eventData.first ];

  if( ( player.isQuestCompleted( eventData.first ) && ( !quest.isRepeatable && eventData.first != 67114 ) ) || player.hasQuest( eventData.first ) ||
      ( quest.repeatIntervalType == 1 && quest.questRepeatFlag == 0 ) ) // Don't show daily beast tribe quests on the map yet.
    return false;

  if( quest.classJobUnlock )
  {
    if( quest.column18 == 3 )
      if( static_cast< uint8_t >( player.getClass() ) != quest.classJobUnlock )
        return false;
    else if( quest.column18 == 4 )
      if ( static_cast< uint8_t >( player.getClass() ) == quest.classJobUnlock )
        return false;
    else
      return false;
  }

  // Was this really ever used?
  if( quest.startTown )
  {
    if( quest.startTown != player.getStartTown() )
      return false;
  }

  if( Common::CURRENT_EXPANSION_ID < quest.expansion )
    return false;

  if( quest.mount )
  {
    if( !player.hasMount( quest.mount ) )
      return false;
  }

  if( eventData.first == 65968 ) // Quest: A Legend for a Legend
  {
    uint16_t requiredMounts[] = { 28, 29, 30, 31, 40, 43 };

    for( int32_t i = 0; i < 6; i++ )
    {
      if( !player.hasMount( requiredMounts[ i ] ) )
        return false;
    }
  }
  else if( eventData.first == 67086 ) // Quest: Fiery Wings, Fiery Hearts
  {
    uint16_t requiredMounts[] = { 75, 76, 77, 78, 90, 98, 104 };

    for( int32_t i = 0; i < 6; i++ )
    {
      if( !player.hasMount( requiredMounts[ i ] ) )
        return false;
    }
  }
  else if( eventData.first == 68736 ) // Quest: A Lone Wolf No More
  {
    uint16_t requiredMounts[] = { 115, 116, 133, 144, 158, 172, 182 };

    for( int32_t i = 0; i < 6; i++ )
    {
      if( !player.hasMount( requiredMounts[ i ] ) )
        return false;
    }
  }

  if( quest.requiredGC || quest.requiredGCRank )
  {
    if( quest.requiredGC != player.getGc() )
      return false;

    if( quest.requiredGCRank > player.getGcRankArray()[ player.getGc() - 1 ] )
      eventData.second.iconId = quest.iconInvalid;
  }

  if( quest.header != 0 )
  {
    if ( !player.isActionLearned( quest.header ) )
      return false;
  }

  //Required previous quests for ARR relic
  if( eventData.first == 66971 ) // Quest: Up in Arms
  {
    for( int32_t i = 0; i <= Common::CLASSJOB_TOTAL; i++ )
    {
      auto classJob = exdData.get< Data::ClassJob >( i );

      if( player.isQuestCompleted( classJob->relicQuest ) )
        break;

      if( i == Common::CLASSJOB_TOTAL )
        return false;
    }
  }
  else if( eventData.first == 65897 ) // Quest: His Dark Materia
  {
    // Quests in the following order: A Ponze of Flesh, Labor of Love, Method in His Malice, A Treasured Mother
    if( !player.isQuestCompleted( 357 ) || !player.isQuestCompleted( 358 ) || !player.isQuestCompleted( 359 ) || !player.isQuestCompleted( 360 ) )
      return false;
  }

  if( quest.previousQuestJoin == 1 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( quest.previousQuestKeys[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( quest.previousQuestKeys[ i ] ) )
      {
        if( i == 0 && quest.previousQuest0Sequence != 0 )
        {
          if( player.getQuestSeq( quest.previousQuestKeys[ i ] ) < quest.previousQuest0Sequence )
            return false;
        }
        else
        {
          return false;
        }
      }
    }
  }
  else if( quest.previousQuestJoin == 2 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( quest.previousQuestKeys[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( quest.previousQuestKeys[ i ] ) )
        break;

      if( i == 2 )
        return false;
    }
  }

  if( quest.questLockJoin == 1 )
  {
    for( int32_t i = 0; i < 2; i++ )
    {
      if( quest.questLockKeys[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( quest.questLockKeys[ i ] ) && !player.hasQuest( quest.questLockKeys[ i ] ) )
        break;

      if( i == 1 )
        return false;
    }
  }
  else if( quest.questLockJoin == 2 )
  {
    for( int32_t i = 0; i < 2; i++ )
    {
      if( quest.questLockKeys[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( quest.questLockKeys[ i ] ) || player.hasQuest( quest.questLockKeys[ i ] ) )
        return false;
    }
  }

  if( quest.instanceContentJoin == 1 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( quest.instanceContent[ i ] == 0 )
        continue;

      eventData.second.iconId = quest.iconInvalid;
    }
  }
  else if( quest.instanceContentJoin == 2 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( quest.instanceContent[ i ] == 0 )
        continue;

      eventData.second.iconId = quest.iconInvalid;
    }
  }

  if( quest.festival )
  {
    auto& territoryMgr = Common::Service< Manager::TerritoryMgr >::ref();
    auto& festival = territoryMgr.getCurrentFestival();

    if( quest.festival != festival.first && quest.festival != festival.second )
      return false;

    // Don't show festivals with begin state other than 0 yet
    if( quest.festivalBegin != 0 )
      return false;
  }

  if( quest.bellStart || quest.bellEnd )
  {
    uint64_t curEorzeaTime = Util::getEorzeanTimeStamp();
    uint32_t convTime = 100 * (curEorzeaTime / 3600 % 24) + curEorzeaTime / 60 % 60;

    if( quest.bellStart <= quest.bellEnd )
    {
      if( convTime < quest.bellStart || convTime >= quest.bellEnd )
        eventData.second.iconId = quest.iconInvalid;
    }
    else
    {
      if( convTime < quest.bellStart && convTime >= quest.bellEnd )
        eventData.second.iconId = quest.iconInvalid;
    }
  }

  if( !quest.classJobRequirements[0].classJobCategoryMask.test( static_cast< uint8_t >( player.getClass() ) ) )
    eventData.second.iconId = quest.iconInvalid;

  if( player.getQuestSeq( eventData.first ) || ( quest.type & 1 ) == 0 )
  {
    for( int32_t i = 1; i <= Common::CLASSJOB_TOTAL; i++ )
    {
      if( quest.classJobRequirements[0].classJobCategoryMask.test( i ) )
      {
        if( player.getLevelForClass( static_cast< Common::ClassJob >( i ) ) >=  quest.classJobRequirements[0].classJobLevel )
          break;
      }

      if( i == Common::CLASSJOB_TOTAL )
        return false;
    }
  }
  else
  {
    if( player.getLevel() < quest.classJobRequirements[0].classJobLevel )
      return false;
  }

  if( quest.classJobRequirements[1].classJobCategoryMask.any() )
  {
    for( int32_t i = 1; i <= Common::CLASSJOB_TOTAL; i++ )
    {
      if( quest.classJobRequirements[1].classJobCategoryMask.test( i ) )
      {
        if( player.getLevelForClass( static_cast< Common::ClassJob >( i ) ) >=  quest.classJobRequirements[1].classJobLevel )
          break;
      }

      if( i == Common::CLASSJOB_TOTAL )
        return false;
    }
  }

  for( int32_t i = 0; i <= Common::CLASSJOB_TOTAL; i++ )
  {
    auto classJob = exdData.get< Data::ClassJob >( i );

    if( classJob->relicQuest == eventData.first )
    {
      for( int32_t j = 0; i <= Common::CLASSJOB_TOTAL; i++ )
      {
        classJob = exdData.get< Data::ClassJob >( i );

        if( player.hasQuest( classJob->relicQuest ) )
          return false;
      }

      break;
    }
  }

  if( quest.beastTribe )
    return false;

  if( quest.satisfactionNpc )
    return false;

  auto isRelicEquipped = [ &player, &eventData ]( uint32_t* mainWeaponId, uint32_t secondaryWeaponId )
  {
    for( int32_t i = 0; i < 10; i++ )
    {
      if( i == 0 )
      {
        if( player.getEquippedSecondaryWeapon() == nullptr )
        {
          if( player.getEquippedWeapon()->getId() == mainWeaponId[ i ] && secondaryWeaponId == 0 )
            return true;
        }
        else if( player.getEquippedWeapon()->getId() == mainWeaponId[ i ] && player.getEquippedSecondaryWeapon()->getId() == secondaryWeaponId )
        {
          return true;
        }
      }
      else
      {
        if( player.getEquippedWeapon()->getId() == mainWeaponId[ i ] )
          return true;
      }
    }

    return false;
  };

  switch( eventData.first )
  {
    case 65742: // Quest: Mmmmmm, Soulglazed Relics
    {
      uint32_t relicItemIds[] = { 7863, 7864, 7865, 7866, 7867, 9253, 7868, 7869, 7870, 7871 };

      if( !isRelicEquipped( relicItemIds, 7872 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 65892: // Quest: Wherefore Art Thou, Zodiac
    case 65897: // Quest: His Dark Materia
    {
      uint32_t relicItemIds[] = { 8649, 8650, 8651, 8652, 8653, 9254, 8654, 8655, 8656, 8657 };

      if( !isRelicEquipped( relicItemIds, 8658 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 66096: // Quest: Rise and Shine
    {
      uint32_t relicItemIds[] = { 9491, 9492, 9493, 9494, 9495, 9501, 9496, 9497, 9498, 9499 };

      if( !isRelicEquipped( relicItemIds, 9500 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 66097: // Quest: The Vital Title
    {
      uint32_t relicItemIds[] = { 10054, 10055, 10056, 10057, 10058, 10064, 10059, 10060, 10061, 10062 };

      if( !isRelicEquipped( relicItemIds, 10063 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 66971: // Quest: Up in Arms
    {
      uint32_t relicItemIds[] = { 6257, 6258, 6259, 6260, 6261, 9250, 6262, 6263, 6264, 6265 };

      if( !isRelicEquipped( relicItemIds, 0 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 66972: // Quest: Trials of the Braves
    {
      uint32_t relicItemIds[] = { 7824, 7825, 7826, 7827, 7828, 9251, 7829, 7830, 7831, 7832 };

      if( !isRelicEquipped( relicItemIds, 7833 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 66998: // Quest: Celestial Radiance
    case 67000: // Quest: Star Light, Star Bright
    {
      uint32_t relicItemIds[] = { 7834, 7835, 7836, 7837, 7838, 9252, 7839, 7840, 7841, 7842 };

      if( !isRelicEquipped( relicItemIds, 7843 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }

    case 67823: // Quest: The Vital Title
    {
      uint32_t relicItemIds[] = { 12124, 12133, 12142, 12151, 12160, 12169, 12178, 12187, 12196 };

      if( !isRelicEquipped( relicItemIds, 12213 ) )
        eventData.second.iconId = quest.iconInvalid;

      break;
    }
  }
    
  if( eventData.first >= 67001 && eventData.first <= 67003 ) // Quest: Call of the Wild
  {
    // Quests in the following order: Martial Perfection / Feathers and Folly / Like Clutchfather, Like Son / Revenge of the Furred / Spread Your Wings and Soar
    if( !player.isQuestCompleted( 1221 ) || !player.isQuestCompleted( 1256 ) || !player.isQuestCompleted( 1378 ) || !player.isQuestCompleted( 1324 ) || !player.isQuestCompleted( 1493 ) )
      return false;
  }
  else if( eventData.first == 67918 ) // Quest: When Good Dragons Go Bad
  {
    // Quests in the following order: The Nest of Honor / A Symbiotic Friendship / The Zenith of Craftsmanship / Heavensward
    if( !player.isQuestCompleted( 2225 ) || !player.isQuestCompleted( 2260 ) || !player.isQuestCompleted( 2327 ) || !player.isQuestCompleted( 1669 ) )
      return false;
  }

  if( eventData.first >= 66968 && eventData.first <= 66970 ) // Quest: An Ill-conceived Venture
    return false;

  if( quest.isHouseRequired )
    return false;

  if( quest.deliveryQuest )
    return false;

  if( eventData.first == 67114 ) // Quest: The Ties That Bind
    return false;

  if( eventData.first == 66112 ) // Quest: Like Sire Like Fledgling
  {
    if( !( player.getHowToArray()[ 198 / 8 ] & ( 1 << ( 198 % 8 ) ) ) )
      return false;
  }

  if( player.getQuestSeq( eventData.first ) == 0 )
  {
    auto questAccept = exdData.get< Data::QuestAcceptAdditionCondition >( eventData.first );

    if( questAccept )
    {
      for( int32_t i = 0; i < 2; i++ )
      {
        if( ( &questAccept->requirement0 )[ i ] >= 65536 )
        {
          if( !player.isActionLearned( 245 ) && !player.isQuestCompleted( ( &questAccept->requirement0 )[ i ] ) )
            return false;
        }
        else
        {
          if( !player.isActionLearned( ( &questAccept->requirement0 )[ i ] ) )
            return false;
        }
      }
    }
  }

  // Quests in the following order: Open and Inviting / The Adventurer with All the Cards
  if( eventData.first == 69566 || eventData.first == 69617 )
    return false;

  return true;
}

bool Sapphire::World::Manager::MapMgr::isTripleTriadAvailable( Entity::Player& player, std::pair< const uint32_t, EventData >& eventData )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto tripleTriad = exdData.get< Data::TripleTriad >( eventData.first );

  if( tripleTriad->previousQuestJoin == 1 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( tripleTriad->previousQuest[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( tripleTriad->previousQuest[ i ] ) )
        return false;
    }
  }
  else if( tripleTriad->previousQuestJoin == 2 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( tripleTriad->previousQuest[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( tripleTriad->previousQuest[ i ] ) )
        break;

      if( i == 2 )
        return false;
    }
  }

  return true;
}

void Sapphire::World::Manager::MapMgr::fillPacket( std::multimap< uint32_t, EventData, less >& mapData, uint32_t* iconIds, uint32_t* levelIds, uint32_t* eventIds )
{
  int32_t i = 0;
  for( auto& eventData : mapData )
  {
    iconIds[ i ] = eventData.second.iconId;
    levelIds[ i ] = eventData.second.levelId;
    eventIds[ i ] = eventData.first;

    i++;
  }
}

void Sapphire::World::Manager::MapMgr::sendPackets( Entity::Player& player, std::multimap< uint32_t, EventData, less >& mapData, UpdateMode updateMode )
{
  player.queuePacket( makeActorControlSelf( player.getId(), Network::ActorControl::BeginMapUpdate, updateMode ) );

  if( mapData.size() <= 2 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }
  else if( mapData.size() <= 4 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate4 >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }
  else if( mapData.size() <= 8 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate8 >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }
  else if( mapData.size() <= 16 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate16 >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }
  else if( mapData.size() <= 32 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate32 >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }
  else if( mapData.size() <= 64 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate64 >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }
  else if( mapData.size() <= 128 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapUpdate128 >( player.getId() );
    mapUpdatePacket->data().entryCount = mapData.size();

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().levelIds, mapUpdatePacket->data().eventIds );
    
    player.queuePacket( mapUpdatePacket );
  }

  player.queuePacket( makeActorControlSelf( player.getId(), Network::ActorControl::FinishMapUpdate ) );
}
