#include <stdio.h>
#include <vector>
#include <time.h>

#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/GamePacket.h>
#include <Network/GamePacketNew.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonNetwork.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketContainer.h>
#include <Database/DatabaseDef.h>
#include <Network/PacketWrappers/ActorControlPacket143.h>

#include "Zone.h"
#include "InstanceContent.h"
#include "TerritoryMgr.h"

#include "Session.h"
#include "Actor/Chara.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/EventObject.h"

#include "Network/GameConnection.h"

#include "Script/ScriptMgr.h"

#include "Session.h"
#include "Forwards.h"
#include "ServerZone.h"
#include "CellHandler.h"
#include "Zone.h"
#include "TerritoryMgr.h"
#include "Framework.h"

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Framework g_fw;


/**
* \brief
*/
Core::Zone::Zone() :
   m_territoryId( 0 ),
   m_guId( 0 ),
   m_currentWeather( Weather::FairSkies ),
   m_weatherOverride( Weather::None ),
   m_lastMobUpdate( 0 ),
   m_currentFestivalId( 0 ),
   m_nextEObjId( 0x400D0000 )
{
}

Core::Zone::Zone( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName ) :
   m_currentWeather( Weather::FairSkies ),
   m_nextEObjId( 0x400D0000 )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   m_guId = guId;

   m_territoryId = territoryId;
   m_internalName = internalName;
   m_placeName = placeName;
   m_lastMobUpdate = 0;

   m_weatherOverride = Weather::None;
   m_territoryTypeInfo = pExdData->get< Core::Data::TerritoryType >( territoryId );

   loadWeatherRates();

   m_currentWeather = getNextWeather();
}

void Core::Zone::loadWeatherRates()
{
   if( !m_territoryTypeInfo )
      return;

   auto pExdData = g_fw.get< Data::ExdDataGenerated >();

   uint8_t weatherRateId = m_territoryTypeInfo->weatherRate > pExdData->getWeatherRateIdList().size() ?
                           uint8_t{ 0 } : m_territoryTypeInfo->weatherRate;

   uint8_t sumPc = 0;
   auto weatherRateFields = pExdData->m_WeatherRateDat.get_row( weatherRateId );
   for( size_t i = 0; i < 16; )
   {
      int32_t weatherId = boost::get< int32_t >( weatherRateFields[i] );

      if( weatherId == 0 )
         break;

      sumPc += boost::get< uint8_t >( weatherRateFields[i + 1] );
      m_weatherRateMap[sumPc] = weatherId;
      i += 2;
   }
}

Core::Zone::~Zone()
{
}

bool Core::Zone::init()
{
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();

   if( pScriptMgr->onZoneInit( shared_from_this() ) )
   {
      // all good
   }


   return true;
}

void Core::Zone::setWeatherOverride( Weather weather )
{
   m_weatherOverride = weather;
}

Weather Core::Zone::getCurrentWeather() const
{
   return m_currentWeather;
}

uint16_t Core::Zone::getCurrentFestival() const
{
   return m_currentFestivalId;
}

void Core::Zone::setCurrentFestival( uint16_t festivalId )
{
   m_currentFestivalId = festivalId;

   for( const auto& playerEntry : m_playerMap )
   {
      auto player = playerEntry.second;

      ActorControlPacket143 enableFestival( player->getId(), SetFestival, m_currentFestivalId );
      playerEntry.second->queuePacket( enableFestival );
   }
}

void Core::Zone::loadCellCache()
{
}

Weather Core::Zone::getNextWeather()
{
   uint32_t unixTime = static_cast< uint32_t >( Util::getTimeSeconds() );
   // Get Eorzea hour for weather start
   uint32_t bell = unixTime / 175;
   // Do the magic 'cause for calculations 16:00 is 0, 00:00 is 8 and 08:00 is 16
   int32_t increment = ( ( bell + 8 - ( bell % 8 ) ) ) % 24;

   // Take Eorzea days since unix epoch
   uint32_t totalDays = ( unixTime / 4200 );

   uint32_t calcBase = ( totalDays * 0x64 ) + increment;

   uint32_t step1 = ( calcBase << 0xB ) ^ calcBase;
   uint32_t step2 = ( step1 >> 8 ) ^ step1;

   auto rate = static_cast< uint8_t >( step2 % 0x64 );

   for( auto entry : m_weatherRateMap )
   {
      uint8_t sRate = entry.first;
      auto weatherId = static_cast< Weather >( entry.second );

      if( rate <= sRate )
         return weatherId;
   }

   return Weather::FairSkies;
}

void Core::Zone::pushActor( Entity::ActorPtr pActor )
{
   float mx = pActor->getPos().x;
   float my = pActor->getPos().z;
   uint32_t cx = getPosX( mx );
   uint32_t cy = getPosY( my );

   Cell* pCell = getCellPtr(cx, cy);
   if( !pCell )
   {
      pCell = create( cx, cy );
      pCell->init( cx, cy, shared_from_this() );
   }

   pCell->addActor( pActor );

   pActor->setCell( pCell );

   uint32_t cellX = getPosX( pActor->getPos().x );
   uint32_t cellY = getPosY( pActor->getPos().z );

   uint32_t endX = cellX <= _sizeX ? cellX + 1 : ( _sizeX - 1 );
   uint32_t endY = cellY <= _sizeY ? cellY + 1 : ( _sizeY - 1 );
   uint32_t startX = cellX > 0 ? cellX - 1 : 0;
   uint32_t startY = cellY > 0 ? cellY - 1 : 0;
   uint32_t posX, posY;

   for( posX = startX; posX <= endX; ++posX )
   {
      for( posY = startY; posY <= endY; ++posY )
      {
         pCell = getCellPtr(posX, posY);
         if( pCell )
            updateInRangeSet( pActor, pCell );
      }
   }

   if( pActor->isPlayer() )
   {
      auto pPlayer = pActor->getAsPlayer();

      auto pServerZone = g_fw.get< ServerZone >();
      auto pSession = pServerZone->getSession( pPlayer->getId() );
      if( pSession )
         m_sessionSet.insert( pSession );
      m_playerMap[pPlayer->getId()] = pPlayer;
      updateCellActivity( cx, cy, 2 );
   }
 }

void Core::Zone::removeActor( Entity::ActorPtr pActor )
{
   float mx = pActor->getPos().x;
   float my = pActor->getPos().z;
   uint32_t cx = getPosX( mx );
   uint32_t cy = getPosY( my );

   Cell* pCell = getCellPtr(cx, cy);
   if( pCell && pCell->hasActor( pActor ) )
      pCell->removeActor( pActor );

   if( pActor->isPlayer() )
   {

      // If it's a player and he's inside boundaries - update his nearby cells
      if( pActor->getPos().x <= _maxX && pActor->getPos().x >= _minX &&
          pActor->getPos().z <= _maxY && pActor->getPos().z >= _minY )
      {
         uint32_t x = getPosX( pActor->getPos().x );
         uint32_t y = getPosY( pActor->getPos().z );
         updateCellActivity( x, y, 3 );
      }
      m_playerMap.erase( pActor->getId() );

      onLeaveTerritory( *pActor->getAsPlayer() );

   }

   // remove from lists of other actors
   pActor->removeFromInRange();
   pActor->clearInRangeSet();

}

void Core::Zone::queueOutPacketForRange( Entity::Player& sourcePlayer, uint32_t range, GamePacketPtr pPacketEntry )
{
   auto pTeriMgr = g_fw.get< TerritoryMgr >();
   if( pTeriMgr->isPrivateTerritory( getTerritoryId() ) )
      return;

   auto pServerZone = g_fw.get< ServerZone >();
   for( auto entry : m_playerMap )
   {
      auto player = entry.second;
      float distance = Math::Util::distance( sourcePlayer.getPos().x,
                                             sourcePlayer.getPos().y,
                                             sourcePlayer.getPos().z,
                                             player->getPos().x,
                                             player->getPos().y,
                                             player->getPos().z );

      if( ( distance < range ) && sourcePlayer.getId() != player->getId() )
      {

         auto pSession = pServerZone->getSession( player->getId() );
         pPacketEntry->setValAt< uint32_t >( 0x08, player->getId() );
         if( pSession )
            pSession->getZoneConnection()->queueOutPacket( pPacketEntry );
      }
   }
}

uint32_t Core::Zone::getTerritoryId() const
{
   return m_territoryId;
}

uint32_t Core::Zone::getGuId() const
{
   return m_guId;
}

const std::string& Core::Zone::getName() const
{
   return m_placeName;
}

const std::string& Core::Zone::getInternalName() const
{
   return m_internalName;
}

std::size_t Core::Zone::getPopCount() const
{
   return m_playerMap.size();
}

bool Core::Zone::checkWeather()
{
   if( m_weatherOverride != Weather::None )
   {
      if( m_weatherOverride != m_currentWeather )
      {
         m_currentWeather = m_weatherOverride;
         return true;
      }
   }
   else
   {
      auto nextWeather = getNextWeather();
      if( nextWeather != m_currentWeather )
      {
         m_currentWeather = nextWeather;
         return true;
      }
   }
   return false;
}

/*
void Core::Zone::updateBnpcs( int64_t tickCount )
{
   if( ( tickCount - m_lastMobUpdate ) > 250 )
   {

      m_lastMobUpdate = tickCount;
      uint32_t currTime = static_cast< uint32_t >( time( nullptr ) );

      for( auto it3 = m_BattleNpcDeadMap.begin(); it3 != m_BattleNpcDeadMap.end(); ++it3 )
      {

         Entity::BattleNpcPtr pBNpc = *it3;

         if( ( currTime - pBNpc->getTimeOfDeath() ) > 60 )
         {

            pBNpc->resetHp();
            pBNpc->resetMp();
            pBNpc->resetPos();
            pushActor( pBNpc );

            m_BattleNpcDeadMap.erase( it3 );

            break;
         }
      }


      for( auto entry : m_BattleNpcMap )
      {
         Entity::BattleNpcPtr pBNpc = entry.second;

         if( !pBNpc )
            continue;

         if( !pBNpc->isAlive() && currTime - pBNpc->getTimeOfDeath() > ( 10 ) )
         {
            removeActor( pBNpc );
            m_BattleNpcDeadMap.insert( pBNpc );
            break;
         }

         pBNpc->update( tickCount );

      }
   }
}
*/

bool Core::Zone::update( uint32_t currTime )
{
   int64_t tickCount = Util::getTimeMs();

   //TODO: this should be moved to a updateWeather call and pulled out of updateSessions
   bool changedWeather = checkWeather();

   updateSessions( changedWeather );
   //updateBnpcs( tickCount );
   onUpdate( currTime );

   return true;
}

void Core::Zone::updateSessions( bool changedWeather )
{
   auto it = m_sessionSet.begin();

   // update sessions in this zone
   for( ; it != m_sessionSet.end(); )
   {

      auto pSession = ( *it );

      if( !pSession )
      {
         it = m_sessionSet.erase(it );
         continue;
      }

      auto pPlayer = pSession->getPlayer();

      // this session is not linked to this area anymore, remove it from zone session list
      if( ( !pPlayer->getCurrentZone() ) || ( pPlayer->getCurrentZone() != shared_from_this() ) )
      {
         removeActor( pSession->getPlayer() );

         it = m_sessionSet.erase(it );
         continue;
      }

      if( changedWeather )
      {
         ZoneChannelPacket< FFXIVIpcWeatherChange  > weatherChangePacket( pPlayer->getId() );
         weatherChangePacket.data().weatherId = static_cast< uint8_t >( m_currentWeather );
         weatherChangePacket.data().delay = 5.0f;
         pSession->getPlayer()->queuePacket( weatherChangePacket );
      }

      // perform session duties
      pSession->update();
      ++it;
   }
}

bool Core::Zone::isCellActive( uint32_t x, uint32_t y )
{
   uint32_t endX = ( ( x + 1 ) <= _sizeX ) ? x + 1 : ( _sizeX - 1 );
   uint32_t endY = ( ( y + 1 ) <= _sizeY ) ? y + 1 : ( _sizeY - 1 );
   uint32_t startX = x > 0 ? x - 1 : 0;
   uint32_t startY = y > 0 ? y - 1 : 0;
   uint32_t posX;
   uint32_t posY;

   Cell* pCell;

   for( posX = startX; posX <= endX; posX++ )
   {
      for( posY = startY; posY <= endY; posY++ )
      {
         pCell = getCellPtr(posX, posY);

         if( pCell && ( pCell->hasPlayers() || pCell->isForcedActive() ) )
            return true;
      }
   }

   return false;
}

void Core::Zone::updateCellActivity( uint32_t x, uint32_t y, int32_t radius )
{

   uint32_t endX = ( x + radius ) <= _sizeX ? x + radius : ( _sizeX - 1 );
   uint32_t endY = ( y + radius ) <= _sizeY ? y + radius : ( _sizeY - 1 );
   uint32_t startX = x - radius > 0 ? x - radius : 0;
   uint32_t startY = y - radius > 0 ? y - radius : 0;
   uint32_t posX, posY;

   Cell* pCell;

   for( posX = startX; posX <= endX; posX++ )
   {
      for( posY = startY; posY <= endY; posY++ )
      {
         pCell = getCellPtr(posX, posY);

         if( !pCell )
         {
            if( isCellActive( posX, posY ) )
            {
               pCell = create( posX, posY );
               pCell->init( posX, posY, shared_from_this() );

               pCell->setActivity( true );

               assert( !pCell->isLoaded() );

            }
         }
         else
         {
            //Cell is now active
            if( isCellActive( posX, posY ) && !pCell->isActive() )
            {
               pCell->setActivity( true );

               if( !pCell->isLoaded() )
               {

               }
            }
            else if( !isCellActive( posX, posY ) && pCell->isActive() )
               pCell->setActivity( false );
         }
      }
   }
}

void Core::Zone::updateActorPosition( Entity::Actor &actor )
{

   if( actor.getCurrentZone() != shared_from_this() )
      return;

   //actor.checkInRangeActors();

   uint32_t cellX = getPosX( actor.getPos().x );
   uint32_t cellY = getPosY( actor.getPos().z );

   if( cellX >= _sizeX || cellY >= _sizeY )
      return;

   auto pCell = getCellPtr(cellX, cellY);

   auto pOldCell = actor.getCellPtr();
   if( !pCell )
   {
      pCell = create( cellX, cellY );
      pCell->init( cellX, cellY, shared_from_this() );
   }

   // If object moved cell
   if( pCell != pOldCell )
   {

      if( pOldCell )
      {
         auto pLog = g_fw.get< Logger >();
         pLog->debug( std::string( __FUNCTION__ ) + " -> removeActor() ...moving cell..." );
         pOldCell->removeActor( actor.shared_from_this() );
      }

      pCell->addActor( actor.shared_from_this() );
      actor.setCell( pCell );
      pOldCell = pCell;

      // if player we need to update cell activity
      // radius = 2 is used in order to update both
      // old and new cells
      if( actor.isPlayer() )
      {
         updateCellActivity( cellX, cellY, 2 );
         if( pOldCell != nullptr )
         {
            // only do the second check if theres -/+ 2 difference
            if( abs( ( int32_t ) cellX - ( int32_t ) pOldCell->m_posX ) > 2 ||
                abs( ( int32_t ) cellY - ( int32_t ) pOldCell->m_posY ) > 2 )
               updateCellActivity( pOldCell->m_posX, pOldCell->m_posY, 2 );
         }
      }
   }

   // update in range actor set
   uint32_t endX = cellX <= _sizeX ? cellX + 1 : ( _sizeX - 1 );
   uint32_t endY = cellY <= _sizeY ? cellY + 1 : ( _sizeY - 1 );
   uint32_t startX = cellX > 0 ? cellX - 1 : 0;
   uint32_t startY = cellY > 0 ? cellY - 1 : 0;
   uint32_t posX, posY;

   for( posX = startX; posX <= endX; ++posX )
   {
      for( posY = startY; posY <= endY; ++posY )
      {
         pCell = getCellPtr(posX, posY);
         if( pCell )
            updateInRangeSet( actor.shared_from_this(), pCell );
      }
   }
}


void Core::Zone::updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell )
{
   if( pCell == nullptr )
      return;

   auto pTeriMgr = g_fw.get< TerritoryMgr >();
   // TODO: make sure gms can overwrite this. Potentially temporary solution
   if( pTeriMgr->isPrivateTerritory( getTerritoryId() ) )
      return;

   auto iter = pCell->m_actors.begin();

   float fRange = 70.0f;
   int32_t count = 0;
   while( iter != pCell->m_actors.end() )
   {
      auto pCurAct = *iter;
      ++iter;

      if( !pCurAct || pCurAct == pActor )
         continue;

      float distance = Math::Util::distance( pCurAct->getPos().x, pCurAct->getPos().y, pCurAct->getPos().z,
                                             pActor->getPos().x, pActor->getPos().y, pActor->getPos().z );

      bool isInRange = ( fRange == 0.0f || distance <= fRange );
      bool isInRangeSet = pActor->isInRangeSet( pCurAct );

      // Add if range == 0 or distance is withing range.
      if( isInRange && !isInRangeSet )
      {

         if( pActor->isPlayer() && !pActor->getAsPlayer()->isLoadingComplete() )
            continue;

         if( pCurAct->isPlayer() && !pCurAct->getAsPlayer()->isLoadingComplete() )
            continue;

         pActor->addInRangeActor( pCurAct );
         pCurAct->addInRangeActor( pActor );

         // this is a hack to limit actor spawn in one packetset
         if( count++ > 12 )
            break;
      }
      else if( !isInRange && isInRangeSet )
      {
         pCurAct->removeInRangeActor( *pActor );
         pActor->removeInRangeActor( *pCurAct );
      }
   }
}

void Core::Zone::onPlayerZoneIn( Entity::Player &player )
{
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "Zone::onEnterTerritory: Zone#" + std::to_string( getGuId() ) + "|" + std::to_string( getTerritoryId() ) +
                                                + ", Entity#" + std::to_string( player.getId() ) );
}

void Core::Zone::onLeaveTerritory( Entity::Player& player )
{
   auto pLog = g_fw.get< Logger >();
   pLog->debug( "Zone::onLeaveTerritory: Zone#" + std::to_string( getGuId() ) + "|" + std::to_string( getTerritoryId() ) +
                                                + ", Entity#" + std::to_string( player.getId() ) );
}

void Core::Zone::onUpdate( uint32_t currTime )
{

}

void Core::Zone::onFinishLoading( Entity::Player& player )
{

}

void Core::Zone::onInitDirector( Entity::Player& player )
{

}

void Core::Zone::onEnterTerritory( Core::Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{

}

void Core::Zone::registerEObj( Entity::EventObjectPtr object )
{
   if( !object )
      return;
   auto pLog = g_fw.get< Logger >();
   object->setId( getNextEObjId() );
   pushActor( object );

   m_eventObjects[object->getId()] = object;

   onRegisterEObj( object );

   pLog->debug( "Registered instance eobj: " + std::to_string( object->getId() ) );
}

Core::Entity::EventObjectPtr Core::Zone::getEObj( uint32_t objId )
{
   auto obj = m_eventObjects.find( objId );
   if( obj == m_eventObjects.end() )
      return nullptr;

   return obj->second;
}

Core::InstanceContentPtr Core::Zone::getAsInstanceContent()
{
   return boost::dynamic_pointer_cast< InstanceContent, Zone >( shared_from_this() );
}

uint32_t Core::Zone::getNextEObjId()
{
   return ++m_nextEObjId;
}

Core::Entity::EventObjectPtr Core::Zone::registerEObj( const std::string &name, uint32_t objectId, uint32_t mapLink,
                                                       uint8_t state, FFXIVARR_POSITION3 pos, float scale, float rotation )
{
   auto eObj = Entity::make_EventObject( getNextEObjId(), objectId, mapLink, state, pos, rotation, name );
   eObj->setScale( scale );
   registerEObj( eObj );

   return eObj;
}
