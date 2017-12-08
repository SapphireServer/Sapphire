#include <stdio.h>
#include <vector>

#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Util/Util.h>
#include <Server_Common/Util/UtilMath.h>
#include <Server_Common/Network/GamePacket.h>
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Network/CommonNetwork.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Common/Network/PacketContainer.h>
#include <Server_Common/Database/DatabaseDef.h>

#include "Zone.h"
#include "ZoneMgr.h"

#include "Session.h"
#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/BattleNpc.h"

#include "Forwards.h"

#include "Network/GameConnection.h"
#include "ServerZone.h"
#include "Script/ScriptManager.h"

#include "CellHandler.h"

#include <time.h>

extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;
extern Core::Data::ExdData g_exdData;
extern Core::Scripting::ScriptManager g_scriptMgr;

namespace Core {

/**
* \brief
*/
Zone::Zone()
   : m_zoneId( 0 )
   , m_layoutId( 0 )
   , m_bPrivate( false )
   , m_type( Common::RegionType::normal )
   , m_currentWeather( static_cast< uint8_t >( Common::Weather::FairSkies ) )
   , m_weatherOverride( 0 )
   , m_lastMobUpdate( 0 )
{
}

Zone::Zone( uint16_t zoneId, uint32_t layoutId, std::string name, std::string interName, bool bPrivate = false )
   : m_type( Common::RegionType::normal )
   , m_currentWeather( static_cast< uint8_t >( Common::Weather::FairSkies ) )
{
   m_layoutId = layoutId;

   m_zoneId = zoneId;
   m_zoneCode = name;
   m_zoneName = interName;
   m_bPrivate = bPrivate;
   m_lastMobUpdate = 0;

   m_currentWeather = getNextWeather();
   m_weatherOverride = 0;
}

Zone::~Zone()
{
}

bool Zone::init()
{
   memset( m_pCellCache, 0, sizeof( CellCache* ) * _sizeX );

   if( g_scriptMgr.onZoneInit( shared_from_this() ) )
   {
      // all good
   }

   loadCellCache();

   return true;
}

bool Zone::isPrivateZone() const
{
   return m_bPrivate;
}

void Zone::setWeatherOverride( uint8_t weather )
{
   m_weatherOverride = weather;
}

uint8_t Zone::getCurrentWeather() const
{
   return m_currentWeather;
}

CellCache* Zone::getCellCacheList( uint32_t cellx, uint32_t celly )
{
   assert( cellx < _sizeX );
   assert( celly < _sizeY );
   if( m_pCellCache[cellx] == nullptr )
      return nullptr;

   return m_pCellCache[cellx][celly];
}

CellCache* Zone::getCellCacheAndCreate( uint32_t cellx, uint32_t celly )
{
   assert( cellx < _sizeX );
   assert( celly < _sizeY );
   if( m_pCellCache[cellx] == nullptr )
   {
      m_pCellCache[cellx] = new CellCache*[_sizeY];
      memset(m_pCellCache[cellx], 0, sizeof( CellCache* ) * _sizeY);
   }

   if( m_pCellCache[cellx][celly] == nullptr )
   {
      //m_pCellCache[cellx][celly] = new CellCache;
   }

   return m_pCellCache[cellx][celly];
}

void Zone::loadCellCache()
{
   auto pQR = g_charaDb.query( "SELECT Id,"
                               "Zoneid,"
                               "NameId,"
                               "SizeId,"
                               "ClassJob,"
                               "DisplayFlags1,"
                               "DisplayFlags2,"
                               "Level,"
                               "Pos_0_0,"
                               "Pos_0_1,"
                               "Pos_0_2,"
                               "Rotation,"
                               "MobType,"
                               "Behaviour,"
                               "ModelMainWeapon,"
                               "ModelSubWeapon,"
                               "ModelId,"
                               "Look,"
                               "Models,"
                               "type "
                               "FROM battlenpc WHERE ZoneId = " + std::to_string( getId() ) + ";" );

   std::vector< Entity::BattleNpcPtr > cache;

   while( pQR->next() )
   {
      uint32_t id = pQR->getUInt( 1 );
      uint32_t targetZoneId = pQR->getUInt( 2 );
      uint32_t nameId = pQR->getUInt( 3 );
      uint32_t sizeId = pQR->getUInt( 4 );
      uint32_t classJob = pQR->getUInt( 5 );
      uint32_t displayFlags1 = pQR->getUInt( 6 );
      uint32_t displayFlags2 = pQR->getUInt( 7 );
      uint32_t level = pQR->getUInt( 8 );
      float posX = pQR->getFloat( 9 );
      float posY = pQR->getFloat( 10 );
      float posZ = pQR->getFloat( 11 );
      uint32_t rotation = pQR->getUInt( 12 );
      uint32_t mobType = pQR->getUInt( 13 );
      uint32_t behaviour = pQR->getUInt( 14 );
      uint64_t modelMainWeapon = pQR->getUInt( 15 );
      uint64_t modelSubWeapon = pQR->getUInt( 16 );
      uint32_t modelId = pQR->getUInt( 17 );
      uint32_t type = pQR->getUInt( 18 );

      Common::FFXIVARR_POSITION3 pos;
      pos.x = posX;
      pos.y = posY;
      pos.z = posZ;
      Entity::BattleNpcPtr pBNpc( new Entity::BattleNpc( modelId, nameId, pos,
                                                         sizeId, type, level, behaviour, mobType ) );
      pBNpc->setRotation( static_cast< float >( rotation ) );
      cache.push_back( pBNpc );
   }



   for( auto entry : cache )
   {
      // get cell position
      uint32_t cellX = CellHandler< ZoneMgr >::getPosX( entry->getPos().x );
      uint32_t cellY = CellHandler< ZoneMgr >::getPosY( entry->getPos().z );

      // find the right cell, create it if not existing yet
      if( m_pCellCache[cellX] == nullptr )
      {
         m_pCellCache[cellX] = new CellCache*[_sizeY];
         memset( m_pCellCache[cellX], 0, sizeof( CellCache* ) * _sizeY );
      }

      if( !m_pCellCache[cellX][cellY] )
         m_pCellCache[cellX][cellY] = new CellCache;

      // add the populace cache object to the cells list
      m_pCellCache[cellX][cellY]->battleNpcCache.push_back( entry );
   }

}

uint8_t Zone::getNextWeather()
{
   auto zoneInfo = g_exdData.m_zoneInfoMap[ getLayoutId() ];

   uint32_t unixTime = static_cast< uint32_t >( time( nullptr ) );
   // Get Eorzea hour for weather start
   uint32_t bell = unixTime / 175;
   // Do the magic 'cause for calculations 16:00 is 0, 00:00 is 8 and 08:00 is 16
   int32_t increment = ( ( bell + 8 - ( bell % 8 ) ) ) % 24;

   // Take Eorzea days since unix epoch
   uint32_t totalDays = ( unixTime / 4200 );

   uint32_t calcBase = ( totalDays * 0x64 ) + increment;

   uint32_t step1 = ( calcBase << 0xB ) ^ calcBase;
   uint32_t step2 = ( step1 >> 8 ) ^ step1;

   uint8_t rate = static_cast< uint8_t >(step2 % 0x64);

   for( auto entry : zoneInfo.weather_rate_map )
   {
      uint8_t sRate = entry.first;
      int32_t weatherId = entry.second;

      if( rate <= sRate )
         return weatherId;
   }

   return 1;
}

void Zone::pushActor( Entity::ActorPtr pActor )
{
   float mx = pActor->getPos().x;
   float my = pActor->getPos().z;
   uint32_t cx = getPosX( mx );
   uint32_t cy = getPosY( my );

   Cell* pCell = getCell( cx, cy );
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
         pCell = getCell( posX, posY );
         if( pCell )
            updateInRangeSet( pActor, pCell );
      }
   }

   if( pActor->isPlayer() )
   {
      g_log.debug( "[Zone:" + m_zoneCode + "] Adding player [" + std::to_string( pActor->getId() ) + "]" );
      auto pPlayer = pActor->getAsPlayer();

      auto pSession = g_serverZone.getSession( pPlayer->getId() );
      if( pSession )
         m_sessionSet.insert( pSession );
      m_playerMap[pPlayer->getId()] = pPlayer;
      updateCellActivity( cx, cy, 2 );

   }
   else if( pActor->isMob() )
   {

      Entity::BattleNpcPtr pBNpc = pActor->getAsBattleNpc();
      m_BattleNpcMap[pBNpc->getId()] = pBNpc;
      pBNpc->setPosition( pBNpc->getPos() );

   }

}

void Zone::removeActor( Entity::ActorPtr pActor )
{

   if( pActor->m_pCell )
   {
      pActor->m_pCell->removeActor( pActor );
      pActor->m_pCell = nullptr;
   }

   if( pActor->isPlayer() )
   {

      g_log.debug( "[Zone:" + m_zoneCode + "] Removing player [" + std::to_string( pActor->getId() ) + "]" );
      // If it's a player and he's inside boundaries - update his nearby cells
      if( pActor->getPos().x <= _maxX && pActor->getPos().x >= _minX &&
          pActor->getPos().z <= _maxY && pActor->getPos().z >= _minY )
      {
         uint32_t x = getPosX( pActor->getPos().x );
         uint32_t y = getPosY( pActor->getPos().z );
         updateCellActivity( x, y, 3 );
      }
      m_playerMap.erase( pActor->getId() );

   }
   else if( pActor->isMob() )
      m_BattleNpcMap.erase( pActor->getId() );

   // remove from lists of other actors
   if( pActor->hasInRangeActor() )
   {
      Entity::ActorPtr pCurAct;

      for( auto iter = pActor->m_inRangeActors.begin(); iter != pActor->m_inRangeActors.end(); )
      {
         pCurAct = *iter;
         auto iter2 = iter++;
         pCurAct->removeInRangeActor( pActor );
      }
   }
   pActor->clearInRangeSet();

}

void Zone::queueOutPacketForRange( Entity::Player& sourcePlayer, uint32_t range, Network::Packets::GamePacketPtr pPacketEntry )
{
   for( auto it = m_playerMap.begin(); it != m_playerMap.end(); ++it )
   {
      float distance = Math::Util::distance( sourcePlayer.getPos().x,
                                             sourcePlayer.getPos().y,
                                             sourcePlayer.getPos().z,
                                             ( *it ).second->getPos().x,
                                             ( *it ).second->getPos().y,
                                             ( *it ).second->getPos().z );

      if( ( distance < range ) && sourcePlayer.getId() != ( *it ).second->getId() )
      {
         auto pSession = g_serverZone.getSession( ( *it ).second->getId() );
         pPacketEntry->setValAt< uint32_t >( 0x08, ( *it ).second->getId() );
         if( pSession )
            pSession->getZoneConnection()->queueOutPacket( pPacketEntry );
      }
   }
}

uint32_t Zone::getId()
{
   return m_zoneId;
}

Common::RegionType Zone::getType() const
{
   return m_type;
}

uint16_t Zone::getLayoutId() const
{
   return m_layoutId;
}

bool Zone::isInstance() const
{
   return m_type == Common::RegionType::instance;
}

const std::string& Zone::getName() const
{
   return m_zoneName;
}

const std::string& Zone::getInternalName() const
{
   return m_zoneCode;
}

std::size_t Zone::getPopCount() const
{
   return m_playerMap.size();
}

bool Zone::checkWeather()
{
   if ( m_weatherOverride != 0 )
   {
      if ( m_weatherOverride != m_currentWeather )
      {
         m_currentWeather = m_weatherOverride;
         g_log.debug( "[Zone:" + m_zoneCode + "] overriding weather to : " + std::to_string( m_weatherOverride ) );
         return true;
      }
   }
   else
   {
      auto nextWeather = getNextWeather();
      if ( nextWeather != m_currentWeather )
      {
         m_currentWeather = nextWeather;
         g_log.debug( "[Zone:" + m_zoneCode + "] changing weather to : " + std::to_string( nextWeather ) );
         return true;
      }
   }
   return false;
}

void Zone::updateBnpcs( int64_t tickCount )
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

bool Zone::runZoneLogic()
{
   int64_t tickCount = Util::getTimeMs();

   bool changedWeather = checkWeather();

   auto it = m_sessionSet.begin();
   
   // update sessions in this zone
   for( ; it != m_sessionSet.end(); )
   {

      auto pSession = ( *it );
      
      if( !pSession )
      {
         it = m_sessionSet.erase( it );
         continue;
      }

      // this session is not linked to this area anymore, remove it from zone session list
      if( ( !pSession->getPlayer()->getCurrentZone() ) || ( pSession->getPlayer()->getCurrentZone() != shared_from_this() ) )
      {
         g_log.debug( "[Zone:" + m_zoneCode + "] removing session " + std::to_string( pSession->getId() ) );

         if( pSession->getPlayer()->getCell() )
            removeActor( pSession->getPlayer() );

         it = m_sessionSet.erase( it );
         continue;
      }

      if( changedWeather )
      {
         Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcWeatherChange  >
                 weatherChangePacket( pSession->getPlayer()->getId() );
         weatherChangePacket.data().weatherId = m_currentWeather;
         weatherChangePacket.data().delay = 5.0f;
         pSession->getPlayer()->queuePacket( weatherChangePacket );
      }

      // perform session duties
      pSession->update();
      ++it;
   }

   updateBnpcs( tickCount );

   return true;
}

bool Zone::isCellActive( uint32_t x, uint32_t y )
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
         pCell = getCell( posX, posY );

         if( pCell && ( pCell->hasPlayers() || pCell->isForcedActive() ) )
            return true;
      }
   }

   return false;
}

void Zone::updateCellActivity( uint32_t x, uint32_t y, int32_t radius )
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
         pCell = getCell( posX, posY );

         if( !pCell )
         {
            if( isCellActive( posX, posY ) )
            {
               pCell = create( posX, posY );
               pCell->init( posX, posY, shared_from_this() );

               pCell->setActivity( true );

               assert( !pCell->isLoaded() );

               CellCache * pCC = getCellCacheAndCreate( posX, posY );
               if( pCC )
                  pCell->loadActors( pCC );
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
                  CellCache * pCC = getCellCacheAndCreate( posX, posY );
                  if( pCC )
                     pCell->loadActors( pCC );
               }
            }
            else if( !isCellActive( posX, posY ) && pCell->isActive() )
               pCell->setActivity( false );
         }
      }
   }
}

void Zone::changeActorPosition( Entity::ActorPtr pActor )
{

   if( pActor->getCurrentZone() != shared_from_this() )
      return;

   if( pActor->hasInRangeActor() )
   {
      Entity::ActorPtr pCurAct;

      float fRange = 70.0f;
      for( auto iter = pActor->m_inRangeActors.begin(); iter != pActor->m_inRangeActors.end();)
      {
         pCurAct = *iter;
         auto iter2 = iter++;

         float distance = Math::Util::distance( pCurAct->getPos().x,
                                                pCurAct->getPos().y,
                                                pCurAct->getPos().z,
                                                pActor->getPos().x,
                                                pActor->getPos().y,
                                                pActor->getPos().z );

         if( fRange > 0.0f && distance > fRange )
         {
            pCurAct->removeInRangeActor( pActor );

            if( pActor->getCurrentZone() != shared_from_this() )
               return;

            pActor->removeInRangeActor( *iter2 );

            // @TODO FIXME! 
            // this break is more or less a hack, iteration will break otherwise after removing 
            break;
         }
      }
   }

   uint32_t cellX = getPosX( pActor->getPos().x );
   uint32_t cellY = getPosY( pActor->getPos().z );

   if( cellX >= _sizeX || cellY >= _sizeY )
   {
      return;
   }

   Cell* pCell = getCell( cellX, cellY );
   Cell* pOldCell = pActor->m_pCell;
   if( !pCell )
   {
      pCell = create( cellX, cellY );
      pCell->init( cellX, cellY, shared_from_this() );
   }

   // If object moved cell
   if( pCell != pOldCell )
   {

      if( pOldCell )
         pOldCell->removeActor( pActor );

      pCell->addActor( pActor );
      pActor->m_pCell = pCell;

      // if player we need to update cell activity
      // radius = 2 is used in order to update both
      // old and new cells
      if( pActor->isPlayer() )
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
         pCell = getCell( posX, posY );
         if( pCell )
            updateInRangeSet( pActor, pCell );
      }
   }
}


void Zone::updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell )
{
   if( pCell == nullptr )
      return;

   Entity::ActorPtr pCurAct;

   auto iter = pCell->m_actors.begin();

   float fRange = 70.0f;
   int32_t count = 0;
   while( iter != pCell->m_actors.end() )
   {
      pCurAct = *iter;
      ++iter;

      if( !pCurAct )
         continue;

      float distance = Math::Util::distance( pCurAct->getPos().x,
                                             pCurAct->getPos().y,
                                             pCurAct->getPos().z,
                                             pActor->getPos().x,
                                             pActor->getPos().y,
                                             pActor->getPos().z );

      // Add if we are not ourself and  range == 0 or distance is withing range.
      if( pCurAct != pActor && ( fRange == 0.0f || distance <= fRange ) )
      {

         if( pActor->isInRangeSet( pCurAct ) )
            // Actor already in range set, skip
            continue;

         if( pActor->isPlayer() )
         {
            auto pOwnPlayer = pActor->getAsPlayer();

            if( !pOwnPlayer->isLoadingComplete() )
               continue;

            count++;
            if( count > 15 )
               break;

            pActor->addInRangeActor( pCurAct );
            pCurAct->addInRangeActor( pActor );
            // spawn the actor for the player
            pCurAct->spawn( pOwnPlayer );

            if( pCurAct->isPlayer() )
            {
               auto pPlayer = pCurAct->getAsPlayer();
               if( !pPlayer->isLoadingComplete() )
                  continue;

               pActor->spawn( pPlayer );
            }

         }
         else if( pActor->isMob() && pCurAct->isPlayer() && pActor->isAlive() )
         {
            auto pPlayer = pCurAct->getAsPlayer();
            if( pPlayer->isLoadingComplete() )
            {
               pActor->spawn( pPlayer );
               pCurAct->addInRangeActor( pActor );
               pActor->addInRangeActor( pCurAct );
            }
         }
         else
         {
            pActor->addInRangeActor( pCurAct );
            pCurAct->addInRangeActor( pActor );
         }
      }
   }
}

}
