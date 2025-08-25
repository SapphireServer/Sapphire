#include <Common.h>
#include <Service.h>

#include <Exd/ExdData.h>

#include <Event/EventHandler.h>
#include <Event/Director.h>

#include <Network/CommonActorControl.h>
#include <Network/GameConnection.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>

#include <Logging/Logger.h>
#include <Util/Util.h>

#include <Actor/Player.h>
#include <Inventory/Item.h>

#include "Territory/InstanceObjectCache.h"
#include "Script/ScriptMgr.h"
#include "Script/NativeScriptMgr.h"

#include "MapMgr.h"

#include "Session.h"
#include "WorldServer.h"
#include "DatCategories/InstanceObjectParser.h"

using namespace Sapphire::Event;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

bool MapMgr::loadQuests()
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  auto questList = exdData.getRows< Excel::Quest >();
  auto eNpcList = exdData.getRows< Excel::ENpcBase >();
  auto eObjList = exdData.getRows< Excel::EObj >();

  for( auto& [ id, questExdData ] : questList )
  {
    m_questCacheMap.emplace( id, std::move( questExdData ) );
  }

  for( auto& [ id, eNpcExdData ] : eNpcList )
  {
    m_eNpcCacheMap.emplace( id, std::move( eNpcExdData ) );
  }

  for( auto& [ id, eObjExdData ] : eObjList )
  {
    m_eObjCacheMap.emplace( id, std::move( eObjExdData ) );
  }

  return true;
}

void MapMgr::updateAll( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

  EventSet mapData;

  auto eventNpcs = objectCache.getAllENpc( player.getTerritoryTypeId() );
  if( !eventNpcs )
    return;
  
  for( const auto& eventNpc : *eventNpcs )
  {
    auto eNpcIt = m_eNpcCacheMap.find( eventNpc.second->header.BaseId );
    if( eNpcIt == std::end( m_eNpcCacheMap ) )
      continue;

    auto eNpcData = eNpcIt->second->data().EventHandler;
    for( auto npcEvent = 0; npcEvent < 32; ++npcEvent )
    {
      auto npcData = eNpcData[ npcEvent ].EventHandler;

      if( npcData == 0 )
        continue; // Some npcs have data gaps, so we have to iterate through the entire array

      EventData eventData;
      eventData.layoutId = npcData;
      eventData.handlerId = eventNpc.first;
    
      auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( npcData >> 16 );

      switch( eventHandlerType )
      {
        case EventHandler::EventHandlerType::Quest:
        {
          auto& quest = m_questCacheMap[ npcData ]->data();

          if( quest.Client == eventNpc.second->header.BaseId )
          {
            insertQuest( player, npcData, eventNpc.first, mapData );
          }
          break;
        }
        case EventHandler::EventHandlerType::GuildLeveAssignment:
        {
          if( player.hasReward( static_cast< Common::UnlockEntry >( 5 ) ) )
          {
            auto guildLeve = exdData.getRow< Excel::GuildleveAssignment >( npcData )->data();

            eventData.iconId = exdData.getRow< Excel::EventIconType >( 5 )->data().MapAvailable + 1;

            if( player.isQuestCompleted( guildLeve.UnlockQuest ) ||
                ( ( guildLeve.NeedGrandCompanyRank > 0 || npcData == 393217 || npcData == 393223 || npcData == 393225 ) && // Leve npc locations: Bentbranch / Horizon / Swiftperch
                ( player.isQuestCompleted( 220 ) || player.isQuestCompleted( 687 ) || player.isQuestCompleted( 693 ) ) ) )
            {
              if( guildLeve.NeedGrandCompanyRank > 0 && player.getGc() != 0 )
              {
                for( int8_t i = 0; i < 3; ++i )
                {
                  if( player.getGcRankArray()[ i ] >= guildLeve.NeedGrandCompanyRank )
                  {
                    mapData.insert( eventData );
                    break;
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
            auto customTalk = exdData.getRow< Excel::CustomTalk >( npcData )->data();
            
            eventData.iconId = customTalk.MapIcon;
            
            mapData.insert( eventData );
          }
          break;
        }  
        case EventHandler::EventHandlerType::GuildOrderGuide:
        {
          if( player.hasReward( static_cast< Common::UnlockEntry>( 7 ) ) )
          {
            eventData.iconId = exdData.getRow< Excel::EventIconType >( 6 )->data().MapAvailable + 1;
            
            mapData.insert( eventData );
          }
          break;
        }
        case EventHandler::EventHandlerType::TripleTriad:
        {
          if( npcData == 2293771 ) // Triple Triad Master npc for now only
          {
            eventData.iconId = exdData.getRow< Excel::EventIconType >( 7 )->data().MapAvailable + 1;
            
            mapData.insert( eventData );
          }
          break;
        }
      }
    }
  }
  
  auto eventObjs = objectCache.getAllEObj( player.getTerritoryTypeId() );
  if( !eventObjs )
    return;

  for( const auto& eventObj : *eventObjs )
  {
    auto eObjIt = m_eObjCacheMap.find( eventObj.second->header.BaseId );
    if( eObjIt == std::end( m_eObjCacheMap ) )
      continue;

    auto eObjData = eObjIt->second->data();
    EventData eventData;
    eventData.handlerId = eObjData.EventHandler;
    eventData.layoutId = eventObj.first;
    
    auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( eObjData.EventHandler >> 16 );

    if( eventHandlerType == EventHandler::EventHandlerType::Quest )
    {
      auto& quest = m_questCacheMap[ eObjData.EventHandler ]->data();

      if( quest.Client == eventObj.second->header.BaseId )
      {
        insertQuest( player, eObjData.EventHandler, eventObj.first, mapData );
      }
    }
  }
  
  sendPackets( player, mapData, All );
}

void MapMgr::updateQuests( Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

  EventSet mapData;

  auto eventNpcs = objectCache.getAllENpc( player.getTerritoryTypeId() );
  if( !eventNpcs )
    return;

  for( const auto& eventNpc : *eventNpcs )
  {
    auto eNpcIt = m_eNpcCacheMap.find( eventNpc.second->header.BaseId );
    if( eNpcIt == std::end( m_eNpcCacheMap ) )
      continue;

    auto eNpcData = eNpcIt->second->data().EventHandler;

    for( auto npcEvent = 0; npcEvent < 32; ++npcEvent )
    {
      auto npcData = eNpcData[ npcEvent ].EventHandler;

      if( npcData == 0 )
        continue; // Some npcs have data gaps, so we have to iterate through the entire array

      EventData eventData;
      eventData.handlerId = npcData;
      eventData.layoutId = eventNpc.first;
      
      auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( npcData >> 16 );

      if( eventHandlerType == EventHandler::EventHandlerType::Quest )
      {
        auto& quest = m_questCacheMap[ npcData ]->data();

        if( quest.Client == eventNpc.second->header.BaseId )
        {
          insertQuest( player, npcData, eventNpc.first, mapData );
        }
      }
    }
  }

  auto eventObjs = objectCache.getAllEObj( player.getTerritoryTypeId() );
  if( !eventObjs )
    return;

  for( const auto& eventObj : *eventObjs )
  {
    auto eObjIt = m_eObjCacheMap.find( eventObj.second->header.BaseId );
    if( eObjIt == std::end( m_eObjCacheMap ) )
      continue;

    auto eObjData = eObjIt->second->data();
    EventData eventData;
    eventData.handlerId = eObjData.EventHandler;
    eventData.layoutId = eventObj.first;
  
    auto eventHandlerType = static_cast< EventHandler::EventHandlerType >( eObjData.EventHandler >> 16 );

    if( eventHandlerType == EventHandler::EventHandlerType::Quest )
    {
      auto& quest = m_questCacheMap[ eObjData.EventHandler ]->data();

      if( quest.Client == eventObj.second->header.BaseId )
      {
        insertQuest( player, eObjData.EventHandler, eventObj.first, mapData );
      }
    }
  }

  sendPackets( player, mapData, Quest );
}

void MapMgr::insertQuest( Entity::Player& player, uint32_t questId, uint32_t layoutId, EventSet& mapData )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  auto& quest = m_questCacheMap[ questId ]->data();

  if( isQuestVisible( player, questId, quest ) )
  {
    auto script = scriptMgr.getNativeScriptHandler().getScript< Sapphire::ScriptAPI::QuestScript >( questId );

    // Just don't show quests on map, that aren't implemented yet
    if( !script )
      return;
             
    EventData eventData;
    eventData.handlerId = questId;
    eventData.layoutId = layoutId;

    auto eventState = script->getQuestAvailability( player, questId );

    if( eventState == Event::EventHandler::QuestAvailability::Available || eventState == Event::EventHandler::QuestAvailability::Locked )
    {
      if( eventState == Event::EventHandler::QuestAvailability::Available && isQuestAvailable( player, questId, quest ) )
        eventData.iconId = exdData.getRow< Excel::EventIconType >( quest.IconType )->data().MapAvailable + 1 + quest.Repeatable;
      else
        eventData.iconId = exdData.getRow< Excel::EventIconType >( quest.IconType )->data().MapInvalid + 1 + quest.Repeatable;

      mapData.insert( eventData );
    }
  }
}

bool MapMgr::isQuestAvailable( Entity::Player& player, uint32_t questId, Excel::Quest& quest )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  if( quest.GrandCompany || quest.GrandCompanyRank )
  {
    if( quest.GrandCompany != player.getGc() && quest.GrandCompanyRank > player.getGcRankArray()[ player.getGc() - 1 ] )
      return false;
  }  

  if( quest.InstanceContentOperator == 1 )
  {
    for( int32_t i = 0; i < 3; ++i )
    {
      if( quest.InstanceContent[ i ] == 0 )
        continue;

      return false;
    }

    return true;
  }
  else if( quest.InstanceContentOperator == 2 )
  {
    for( int32_t i = 0; i < 3; ++i )
    {
      if( quest.InstanceContent[ i ] == 0 )
        continue;

      return false;
    }
  }  

  if( quest.TimeBegin || quest.TimeEnd )
  {
    uint64_t curEorzeaTime = Sapphire::Common::Util::getEorzeanTimeStamp();
    uint32_t convTime = 100 * ( curEorzeaTime / 3600 % 24 ) + curEorzeaTime / 60 % 60;

    if( quest.TimeBegin <= quest.TimeEnd )
    {
      if( convTime < quest.TimeBegin || convTime >= quest.TimeEnd )
        return false;
    }
    else
    {
      if( convTime < quest.TimeBegin && convTime >= quest.TimeEnd )
        return false;
    }
  }  

  auto classJobCategory = exdData.getRow< Excel::ClassJobCategory >( quest.ClassJob );
  if( !classJobCategory->data().ClassJob[ static_cast< uint8_t >( player.getClass() ) ] )
    return false;

  if( quest.ClassJob2 > 1 )
  {
    classJobCategory = exdData.getRow< Excel::ClassJobCategory >( quest.ClassJob2 );
    if( !classJobCategory->data().ClassJob[ static_cast< uint8_t >( player.getClass() ) ] )
      return false;
  }

  return true;
}

bool MapMgr::isQuestVisible( Entity::Player& player, uint32_t questId, Excel::Quest& quest )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();

  if( ( player.isQuestCompleted( questId ) && ( !quest.Repeatable && questId != 67114 ) ) || player.hasQuest( questId ) )
    return false;

  if( quest.ClassJobUnlock && quest.ClassJob != 1 )
  {
    uint8_t classJobIndex = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( player.getClass() ) )->data().WorkIndex;
    if( quest.ClassJobUnlockFlag == 3 )
      if( classJobIndex != quest.ClassJobUnlock )
        return false;
    else if( quest.ClassJobUnlockFlag == 4 )
      if ( static_cast< uint8_t >( player.getClass() ) == quest.ClassJobUnlock )
        return false;
    else
      return false;
  }

  // Was this really ever used?
  if( quest.StartTown && quest.StartTown != player.getStartTown() )
    return false;

  if( Common::CURRENT_EXPANSION_ID < quest.Expansion )
    return false;

  if( quest.Mount && !player.hasMount( quest.Mount ) )
    return false;

  if( quest.GrandCompany && quest.GrandCompany != player.getGc() )
    return false;

  if( quest.Header != 0 && !player.hasReward( static_cast< Common::UnlockEntry >( quest.Header ) ) )
    return false;

  if( quest.PrevQuestOperator == 1 )
  {
    for( auto i = 0; i < 3; ++i )
    {
      if( quest.PrevQuest[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( quest.PrevQuest[ i ] ) )
      {
        // todo: see if this can be done in 3.x
        /*if( i == 0 && questPtr->previousQuest0Sequence != 0 )
        {
          if( player.getQuestSeq( questPtr->previousQuest[ i ] ) < questPtr->previousQuest0Sequence )
            return false;
        }
        else
        {
          return false;
        }*/
        return false;
      }
    }
  }
  else if( quest.PrevQuestOperator == 2 )
  {
    for( auto i = 0; i <= 3; ++i )
    {
      if( i == 3 )
        return false;

      if( quest.PrevQuest[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( quest.PrevQuest[ i ] ) )
        break;
    }
  }

  if( quest.ExcludeQuestOperator == 1 )
  {
    for( auto i = 0; i <= 2; ++i )
    {
      if( i == 2 )
        return false;

      if( quest.ExcludeQuest[ i ] == 0 )
        continue;

      if( !player.isQuestCompleted( quest.ExcludeQuest[ i ] ) && !player.hasQuest( quest.ExcludeQuest[ i ] ) )
        break;
    }
  }
  else if( quest.ExcludeQuestOperator == 2 )
  {
    for( auto i = 0; i < 2; ++i )
    {
      if( quest.ExcludeQuest[ i ] == 0 )
        continue;

      if( player.isQuestCompleted( quest.ExcludeQuest[ i ] ) || player.hasQuest( quest.ExcludeQuest[ i ] ) )
        return false;
    }
  }

  if( quest.Festival )
  {
    auto& territoryMgr = Common::Service< Manager::TerritoryMgr >::ref();
    auto& festival = territoryMgr.getCurrentFestival();

    if( quest.Festival != festival.first && quest.Festival != festival.second )
      return false;

    // Don't show festivals with begin state other than 0 yet
    if( quest.FestivalPhaseBegin != 0 )
      return false;
  }

  if( ( quest.Type & 1 ) == 0 )
  {
    auto classJobCategory = exdData.getRow< Excel::ClassJobCategory >( quest.ClassJob );

    for( auto i = 1; i <= Common::CLASSJOB_TOTAL; ++i )
    {
      if( i == Common::CLASSJOB_TOTAL )
        return false;

      if( classJobCategory->data().ClassJob[ i ] )
      {
        if( player.getLevelForClass( static_cast< Common::ClassJob >( i ) ) >=  quest.ClassLevel )
          break;
      }
    }
  }
  else
  {
    if( player.getLevel() < quest.ClassLevel )
      return false;
  }

  // TODO: I think this changed in 3.x to be for all relics, more research is needed.
  // todo: fix this inner j loop
  for( auto i = 0; i < Common::CLASSJOB_TOTAL; ++i )
  {
    auto classJob = exdData.getRow< Excel::ClassJob >( i );

    if( classJob->data().ARRRelicQuestId == questId )
    {
      if( player.hasQuest( classJob->data().ARRRelicQuestId ) )
        return false;
    }
  }

  if( quest.BeastTribe )
    return false;
    
  if( quest.House )
    return false;

  if( quest.DeliveryQuest )
    return false;

  // TODO: dunno if 3.x has this, have to check
  /*if( player.getQuestSeq( questId ) == 0 )
  {
    auto& questAccept = exdData.getRow< Excel::QuestAcceptAdditionCondition >( questId );

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
  }*/

  return true;
}

bool MapMgr::isTripleTriadAvailable( Entity::Player& player, uint32_t tripleTriadId )
{
  // TODO: map out Triple Triad sheet
  /*auto& exdData = Common::Service< Data::ExdData >::ref();
  auto tripleTriad = exdData.getRow< Excel::TripleTriad >( tripleTriadId );

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
  }*/

  return true;
}

void MapMgr::fillPacket( EventSet& mapData, uint32_t* iconIds, uint32_t* layoutIds, uint32_t* handlerIds )
{
  int32_t i = 0;
  for( auto& eventData : mapData )
  {
    iconIds[ i ] = eventData.iconId;
    layoutIds[ i ] = eventData.layoutId;
    handlerIds[ i ] = eventData.handlerId;

    i++;
  }
}

void MapMgr::sendPackets( Entity::Player& player, EventSet& mapData, UpdateMode updateMode )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), Network::ActorControl::BeginMapUpdate, updateMode ) );

  if( mapData.size() <= 2 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker2 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }
  else if( mapData.size() <= 4 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker4 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }
  else if( mapData.size() <= 8 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker8 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }
  else if( mapData.size() <= 16 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker16 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }
  else if( mapData.size() <= 32 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker32 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }
  else if( mapData.size() <= 64 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker64 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }
  else if( mapData.size() <= 128 )
  {
    auto mapUpdatePacket = makeZonePacket< FFXIVIpcMapMarker128 >( player.getId() );
    mapUpdatePacket->data().numOfMarkers = static_cast< uint8_t >( mapData.size() );

    fillPacket( mapData, mapUpdatePacket->data().iconIds, mapUpdatePacket->data().layoutIds, mapUpdatePacket->data().handlerIds );

    server.queueForPlayer( player.getCharacterId(), mapUpdatePacket );
  }

  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), Network::ActorControl::FinishMapUpdate ) );
}