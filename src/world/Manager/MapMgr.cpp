#include <Common.h>
#include <Service.h>

#include <Exd/ExdDataGenerated.h>

#include <Event/EventHandler.h>

#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>

#include <Util/Util.cpp>

#include <Actor/Player.h>

#include <Script/ScriptMgr.h>
#include <Script/NativeScriptMgr.h>

#include <Territory/InstanceObjectCache.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "MapMgr.h"
#include "TerritoryMgr.h"

using namespace Sapphire::Event;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::World::Manager::MapMgr::MapMgr()
{  
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  for( uint32_t questId = 65536; auto curQuest = exdData.get< Data::Quest >( questId ); questId++ )
    m_quests.emplace( questId, curQuest );
}

void Sapphire::World::Manager::MapMgr::updateAll( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

  EventSet mapData;

  auto eventNpcs = objectCache.getAllEventNpc( player.getZoneId() );
  if( eventNpcs )
  {
    for( const auto& eventNpc : *eventNpcs )
    {
      auto eNpc = exdData.get< Data::ENpcBase >( eventNpc.second->data.enpcId );
      if( eNpc )
      {
        auto eNpcData = eNpc->eNpcData;
        for( auto npcData : eNpcData )
        {
          if( npcData == 0 )
            continue; // Some npcs have data gaps, so we have to iterate through the entire array

          EventData eventData;
          eventData.eventId = npcData;
          eventData.levelId = eventNpc.first;
        
          auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( npcData >> 16 );

          switch( eventHandlerType )
          {
            case EventHandler::EventHandlerType::Quest:
            {
              auto quest = m_quests[ npcData ];

              if( quest->issuerLocation == eventNpc.first )
              {
                insertQuest( player, npcData, mapData );
              }
              break;
            }
            case EventHandler::EventHandlerType::GuildLeveAssignment:
            {
              if( player.isActionLearned( 5 ) )
              {
                auto guildLeve = exdData.get< Data::GuildleveAssignment >( npcData );

                eventData.iconId = exdData.get< Data::EventIconType >( 5 )->mapIconAvailable + 1;

                if( player.isQuestCompleted( guildLeve->quest[ 0 ] ) ||
                    ( ( guildLeve->typeId == 2 || npcData == 393217 || npcData == 393223 || npcData == 393225 ) && // Leve npc locations: Bentbranch / Horizon / Swiftperch
                    ( player.isQuestCompleted( 220 ) || player.isQuestCompleted( 687 ) || player.isQuestCompleted( 693 ) ) ) )
                {
                  if( guildLeve->typeId == 2 )
                  {
                    if( player.getGc() != 0 )
                    {
                      for( int8_t i = 0; i < 3; i++ )
                      {
                        if( player.getGcRankArray()[ i ] >= guildLeve->grandCompanyRank )
                        {
                          mapData.insert( eventData );
                          break;
                        }
                      }
                    }
                  }
                  else
                  {
                    mapData.insert( eventData );
                  }
                }
              }              
              break;
            }
          
            case EventHandler::EventHandlerType::CustomTalk:
            {
              // Include only the beginner arena icon yet. There a few other ones, that aren't referenced in the game files (Some examples are: The Triple Triad Tournament npc which has multiple icons and the ocean fishing icon)
              if( npcData == 721223 )
              {
                auto customTalk = exdData.get< Data::CustomTalk >( npcData );
                
                eventData.iconId = customTalk->iconMap;
                
                mapData.insert( eventData );
              }
              break;
            }
          
            case EventHandler::EventHandlerType::GuildOrderGuide:
            {
              if( player.isActionLearned( 7 ) )
              {
                eventData.iconId = exdData.get< Data::EventIconType >( 6 )->mapIconAvailable + 1;
                
                mapData.insert( eventData );
              }
              break;
            }

            case EventHandler::EventHandlerType::TripleTriad:
            {
              if( npcData == 2293771 ) // Triple Triad Master npc for now only
              {
                eventData.iconId = exdData.get< Data::EventIconType >( 7 )->mapIconAvailable + 1;
                
                mapData.insert( eventData );
              }
              break;
            }
          
            case EventHandler::EventHandlerType::PreHandler:
            {
              //I think this is used in Bozja and Zadnor, need evidence
              break;
            }
          }
        }
      }
    }
  }
  
  auto eventObjs = objectCache.getAllEventObj( player.getZoneId() );
  if( eventObjs )
  {
    for( const auto& eventObj : *eventObjs )
    {
      auto eObj = exdData.get< Data::EObj >( eventObj.second->data.eobjId );
      if( eObj )
      {
        auto eObjData = eObj->data;
        if( eObjData )
        {
          EventData eventData;
          eventData.eventId = eObjData;
          eventData.levelId = eventObj.first;
        
          auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( eObjData >> 16 );

          if( eventHandlerType == EventHandler::EventHandlerType::Quest )
          {
            auto quest = m_quests[ eObjData ];

            if( quest->issuerLocation == eventObj.first )
            {
              insertQuest( player, eObjData, mapData );
            }
          }
        }
      }
    }
  }

  
  sendPackets( player, mapData, All );
}

void Sapphire::World::Manager::MapMgr::updateQuests( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

  EventSet mapData;

  auto eventNpcs = objectCache.getAllEventNpc( player.getZoneId() );
  if( eventNpcs )
  {
    for( const auto& eventNpc : *eventNpcs )
    {
      auto eNpcData = exdData.get< Data::ENpcBase >( eventNpc.second->data.enpcId )->eNpcData;

      for( auto npcData : eNpcData )
      {
        if( npcData == 0 )
          continue; // Some npcs have data gaps, so we have to iterate through the entire array

        EventData eventData;
        eventData.eventId = npcData;
        eventData.levelId = eventNpc.first;
        
        auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( npcData >> 16 );

        if( eventHandlerType == EventHandler::EventHandlerType::Quest )
        {
          auto quest = m_quests[ npcData ];

          if( quest->issuerLocation == eventNpc.first )
          {
            insertQuest( player, npcData, mapData );
          }
        }
      }
    }
  }

  auto eventObjs = objectCache.getAllEventObj( player.getZoneId() );
  if( eventObjs )
  {
    for( const auto& eventObj : *eventObjs )
    {
      auto eObj = exdData.get< Data::EObj >( eventObj.second->data.eobjId );
      if( eObj )
      {
        auto eObjData = eObj->data;
        if( eObjData )
        {
          EventData eventData;
          eventData.eventId = eObjData;
          eventData.levelId = eventObj.first;
        
          auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( eObjData >> 16 );

          if( eventHandlerType == EventHandler::EventHandlerType::Quest )
          {
            auto quest = m_quests[ eObjData ];

            if( quest->issuerLocation == eventObj.first )
            {
              insertQuest( player, eObjData, mapData );
            }
          }
        }
      }
    }
  }

  sendPackets( player, mapData, Quest );
}

void Sapphire::World::Manager::MapMgr::insertQuest( Entity::Player& player, uint32_t questId, EventSet& mapData )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  auto quest = m_quests[ questId ];

  if( isQuestVisible( player, questId, quest ) )
  {
    auto script = scriptMgr.getNativeScriptHandler().getScript< Sapphire::ScriptAPI::EventScript >( questId );

    // Just don't show quests on map, that aren't implemented yet
    if( script )
    {                        
      EventData eventData;
      eventData.eventId = questId;

      auto eventState = script->getQuestAvailability( player, questId );

      if( eventState == Event::EventHandler::QuestAvailability::Available || eventState == Event::EventHandler::QuestAvailability::Locked )
      {
        if( eventState == Event::EventHandler::QuestAvailability::Available && isQuestAvailable( player, questId, quest ) )
        {
          eventData.iconId = exdData.get< Data::EventIconType >( quest->eventIconType )->mapIconAvailable + 1 + quest->isRepeatable;
          eventData.levelId = quest->issuerLocation;
        }
        else
        {
          eventData.iconId = exdData.get< Data::EventIconType >( quest->eventIconType )->mapIconInvalid + 1 + quest->isRepeatable;
          eventData.levelId = quest->issuerLocation;
        }

        mapData.insert( eventData );
      }
    }
  }
}

bool Sapphire::World::Manager::MapMgr::isQuestAvailable( Entity::Player& player, uint32_t questId, Data::ExdDataGenerated::QuestPtr questPtr )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  if( questPtr->grandCompany || questPtr->grandCompanyRank )
  {
    if( questPtr->grandCompany != player.getGc() )
    {
      if( questPtr->grandCompanyRank > player.getGcRankArray()[ player.getGc() - 1 ] )
        return false;
    }
  }  

  if( questPtr->instanceContentJoin == 1 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( questPtr->instanceContent[ i ] == 0 )
        continue;

      return false;
    }

    return true;
  }
  else if( questPtr->instanceContentJoin == 2 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( questPtr->instanceContent[ i ] == 0 )
        continue;

      return false;
    }
  }  

  if( questPtr->bellStart || questPtr->bellEnd )
  {
    uint64_t curEorzeaTime = Util::getEorzeanTimeStamp();
    uint32_t convTime = 100 * ( curEorzeaTime / 3600 % 24 ) + curEorzeaTime / 60 % 60;

    if( questPtr->bellStart <= questPtr->bellEnd )
    {
      if( convTime < questPtr->bellStart || convTime >= questPtr->bellEnd )
        return false;
    }
    else
    {
      if( convTime < questPtr->bellStart && convTime >= questPtr->bellEnd )
        return false;
    }
  }  

  auto classJobCategory = &exdData.get< Data::ClassJobCategory >( questPtr->classJobCategory0 )->aDV;
  if( !classJobCategory[ static_cast< uint8_t >( player.getClass() ) ] )
    return false;

  if( questPtr->classJobCategory1 > 1 )
  {
    classJobCategory = &exdData.get< Data::ClassJobCategory >( questPtr->classJobCategory1 )->aDV;
    if( !classJobCategory[ static_cast< uint8_t >( player.getClass() ) ] )
      return false;
  }

  return true;
}

bool Sapphire::World::Manager::MapMgr::isQuestVisible( Entity::Player& player, uint32_t questId, Data::ExdDataGenerated::QuestPtr questPtr )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

  if( ( player.isQuestCompleted( questId ) && ( !questPtr->isRepeatable && questId != 67114 ) ) || player.hasQuest( questId ) )
    return false;

  if( questPtr->classJobUnlock )
  {
    if( questPtr->classJobUnlockFlag == 3 )
      if( static_cast< uint8_t >( player.getClass() ) != questPtr->classJobUnlock )
        return false;
    else if( questPtr->classJobUnlockFlag == 4 )
      if ( static_cast< uint8_t >( player.getClass() ) == questPtr->classJobUnlock )
        return false;
    else
      return false;
  }

  // Was this really ever used?
  if( questPtr->startTown )
  {
    if( questPtr->startTown != player.getStartTown() )
      return false;
  }

  if( Common::CURRENT_EXPANSION_ID < questPtr->expansion )
    return false;

  if( questPtr->mountRequired )
  {
    if( !player.hasMount( questPtr->mountRequired ) )
      return false;
  }

  if( questPtr->grandCompany )
  {
    if( questPtr->grandCompany != player.getGc() )
      return false;
  }

  if( questPtr->header != 0 )
  {
    if ( !player.isActionLearned( questPtr->header ) )
      return false;
  }

  if( questPtr->previousQuestJoin == 1 )
  {
    for( int32_t i = 0; i < 3; i++ )
    {
      if( questPtr->previousQuest[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( questPtr->previousQuest[ i ] ) )
      {
        if( i == 0 && questPtr->previousQuest0Sequence != 0 )
        {
          if( player.getQuestSeq( questPtr->previousQuest[ i ] ) < questPtr->previousQuest0Sequence )
            return false;
        }
        else
        {
          return false;
        }
      }
    }
  }
  else if( questPtr->previousQuestJoin == 2 )
  {
    for( int32_t i = 0; i <= 3; i++ )
    {
      if( i == 3 )
        return false;

      if( questPtr->previousQuest[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( questPtr->previousQuest[ i ] ) )
        break;
    }
  }

  if( questPtr->questLockJoin == 1 )
  {
    for( int32_t i = 0; i <= 2; i++ )
    {
      if( i == 2 )
        return false;

      if( questPtr->questLock[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( questPtr->questLock[ i ] ) && !player.hasQuest( questPtr->questLock[ i ] ) )
        break;
    }
  }
  else if( questPtr->questLockJoin == 2 )
  {
    for( int32_t i = 0; i < 2; i++ )
    {
      if( questPtr->questLock[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( questPtr->questLock[ i ] ) || player.hasQuest( questPtr->questLock[ i ] ) )
        return false;
    }
  }

  if( questPtr->festival )
  {
    auto& territoryMgr = Common::Service< Manager::TerritoryMgr >::ref();
    auto& festival = territoryMgr.getCurrentFestival();

    if( questPtr->festival != festival.first && questPtr->festival != festival.second )
      return false;

    // Don't show festivals with begin state other than 0 yet
    if( questPtr->festivalBegin != 0 )
      return false;
  }

  if( ( questPtr->type & 1 ) == 0 )
  {
    auto classJobCategory = &exdData.get< Data::ClassJobCategory >( questPtr->classJobCategory0 )->aDV;

    for( int32_t i = 1; i <= Common::CLASSJOB_TOTAL; i++ )
    {
      if( classJobCategory[ i ] )
      {
        if( player.getLevelForClass( static_cast< Common::ClassJob >( i ) ) >=  questPtr->classJobLevel0 )
          break;
      }

      if( i == Common::CLASSJOB_TOTAL )
        return false;
    }
  }
  else
  {
    if( player.getLevel() < questPtr->classJobLevel0 )
      return false;
  }

  for( int32_t i = 0; i <= Common::CLASSJOB_TOTAL; i++ )
  {
    auto classJob = exdData.get< Data::ClassJob >( i );

    if( classJob->relicQuest == questId )
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

  if( questPtr->beastTribe )
    return false;

  if( questPtr->satisfactionNpc )
    return false;
    
  if( questPtr->isHouseRequired )
    return false;

  if( questPtr->deliveryQuest )
    return false;

  if( player.getQuestSeq( questId ) == 0 )
  {
    auto questAccept = exdData.get< Data::QuestAcceptAdditionCondition >( questId );

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

  return true;
}

bool Sapphire::World::Manager::MapMgr::isTripleTriadAvailable( Entity::Player& player, uint32_t tripleTriadId )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto tripleTriad = exdData.get< Data::TripleTriad >( tripleTriadId );

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

void Sapphire::World::Manager::MapMgr::fillPacket( EventSet& mapData, uint32_t* iconIds, uint32_t* levelIds, uint32_t* eventIds )
{
  int32_t i = 0;
  for( auto& eventData : mapData )
  {
    iconIds[ i ] = eventData.iconId;
    levelIds[ i ] = eventData.levelId;
    eventIds[ i ] = eventData.eventId;

    i++;
  }
}

void Sapphire::World::Manager::MapMgr::sendPackets( Entity::Player& player, EventSet& mapData, UpdateMode updateMode )
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
