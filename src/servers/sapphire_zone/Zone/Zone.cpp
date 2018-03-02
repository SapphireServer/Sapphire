#include <stdio.h>
#include <vector>
#include <time.h>

#include <common/Logging/Logger.h>
#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>
#include <common/Network/GamePacket.h>
#include <common/Network/GamePacketNew.h>
#include <common/Exd/ExdDataGenerated.h>
#include <common/Network/CommonNetwork.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/PacketContainer.h>
#include <common/Database/DatabaseDef.h>

#include "Actor/Actor.h"
#include "Actor/Player.h"
#include "Actor/BattleNpc.h"
#include "Actor/EventNpc.h"

#include "Network/GameConnection.h"

#include "Script/ScriptMgr.h"

#include "Session.h"
#include "Forwards.h"
#include "ServerZone.h"
#include "CellHandler.h"
#include "Zone.h"
#include "TerritoryMgr.h"
#include "Framework.h"

extern Core::Framework g_framework;

/**
* \brief
*/
Core::Zone::Zone() :
   m_territoryId( 0 ),
   m_guId( 0 ),
   m_currentWeather( static_cast< uint8_t >( Common::Weather::FairSkies ) ),
   m_weatherOverride( 0 ),
   m_lastMobUpdate( 0 ),
   m_currentFestivalId( 0 )
{
}

Core::Zone::Zone( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName ) :
   m_currentWeather( static_cast< uint8_t >( Common::Weather::FairSkies ) )
{
   m_guId = guId;

   m_territoryId = territoryId;
   m_internalName = internalName;
   m_placeName = placeName;
   m_lastMobUpdate = 0;

   m_weatherOverride = 0;
   m_territoryTypeInfo = g_framework.getExdDataGen().get< Core::Data::TerritoryType >( territoryId );

   uint8_t weatherRateId = m_territoryTypeInfo->weatherRate > g_framework.getExdDataGen().getWeatherRateIdList().size() ?
                           uint8_t{ 0 } : m_territoryTypeInfo->weatherRate;

   uint8_t sumPc = 0;
   auto weatherRateFields = g_framework.getExdDataGen().m_WeatherRateDat.get_row( weatherRateId );
   for( size_t i = 0; i < 16; )
   {
      int32_t weatherId = boost::get< int32_t >( weatherRateFields[i] );

      if( weatherId == 0 )
         break;

      sumPc += boost::get< uint8_t >( weatherRateFields[i + 1] );
      m_weatherRateMap[sumPc] = weatherId;
      i += 2;
   }

   m_currentWeather = getNextWeather();
}

Core::Zone::~Zone()
{
}

bool Core::Zone::init()
{
   memset( m_pCellCache, 0, sizeof( CellCache* ) * _sizeX );

   if( g_framework.getScriptMgr().onZoneInit( shared_from_this() ) )
   {
      // all good
   }

   loadCellCache();

   return true;
}

void Core::Zone::setWeatherOverride( uint8_t weather )
{
   m_weatherOverride = weather;
}

uint8_t Core::Zone::getCurrentWeather() const
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
}

Core::CellCache* Core::Zone::getCellCacheList( uint32_t cellx, uint32_t celly )
{
   assert( cellx < _sizeX );
   assert( celly < _sizeY );
   if( m_pCellCache[cellx] == nullptr )
      return nullptr;

   return m_pCellCache[cellx][celly];
}

Core::CellCache* Core::Zone::getCellCacheAndCreate( uint32_t cellx, uint32_t celly )
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

void Core::Zone::loadCellCache()
{
   auto pQR = g_framework.getCharaDb().query( "SELECT Id,"
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
                               "FROM battlenpc WHERE ZoneId = " + std::to_string( getTerritoryId() ) + ";" );

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

      Common::FFXIVARR_POSITION3 pos{ posX, posY, posZ };
      auto pBNpc = Entity::make_BattleNpc( modelId, nameId, pos, sizeId, type, level, behaviour, mobType );
      pBNpc->setRotation( static_cast< float >( rotation ) );
      cache.push_back( pBNpc );
   }



   for( auto entry : cache )
   {
      // get cell position
      uint32_t cellX = CellHandler< TerritoryMgr >::getPosX( entry->getPos().x );
      uint32_t cellY = CellHandler< TerritoryMgr >::getPosY( entry->getPos().z );

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

uint8_t Core::Zone::getNextWeather()
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
      auto weatherId = static_cast< uint8_t >( entry.second );

      if( rate <= sRate )
         return weatherId;
   }

   return 1;
}

void Core::Zone::pushActor( Entity::ActorPtr pActor )
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
      auto pPlayer = pActor->getAsPlayer();

      auto pSession = g_framework.getServerZone().getSession( pPlayer->getId() );
      if( pSession )
         m_sessionSet.insert( pSession );
      m_playerMap[pPlayer->getId()] = pPlayer;
      updateCellActivity( cx, cy, 2 );
   }
   else if( pActor->isBattleNpc() )
   {

      Entity::BattleNpcPtr pBNpc = pActor->getAsBattleNpc();
      m_BattleNpcMap[pBNpc->getId()] = pBNpc;
      pBNpc->setPosition( pBNpc->getPos() );

   }
   else if( pActor->isEventNpc() )
   {
      Entity::EventNpcPtr pENpc = pActor->getAsEventNpc();
      m_EventNpcMap[pENpc->getId()] = pENpc;
      pENpc->setPosition( pENpc->getPos() );
   }


}

void Core::Zone::removeActor( Entity::ActorPtr pActor )
{

   if( pActor->m_pCell )
   {
      pActor->m_pCell->removeActor( pActor );
      pActor->m_pCell = nullptr;
   }

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
   else if( pActor->isBattleNpc() )
      m_BattleNpcMap.erase( pActor->getId() );

   // remove from lists of other actors
   pActor->removeFromInRange();
   pActor->clearInRangeSet();

}

void Core::Zone::queueOutPacketForRange( Entity::Player& sourcePlayer, uint32_t range, Network::Packets::GamePacketPtr pPacketEntry )
{
   if( g_framework.getTerritoryMgr().isPrivateTerritory( getTerritoryId() ) )
      return;

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
         auto pSession = g_framework.getServerZone().getSession( ( *it ).second->getId() );
         pPacketEntry->setValAt< uint32_t >( 0x08, ( *it ).second->getId() );
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
   if ( m_weatherOverride != 0 )
   {
      if ( m_weatherOverride != m_currentWeather )
      {
         m_currentWeather = m_weatherOverride;
         g_framework.getLogger().debug( "[Zone:" + m_internalName + "] overriding weather to : " + std::to_string( m_weatherOverride ) );
         return true;
      }
   }
   else
   {
      auto nextWeather = getNextWeather();
      if ( nextWeather != m_currentWeather )
      {
         m_currentWeather = nextWeather;
         g_framework.getLogger().debug( "[Zone:" + m_internalName + "] changing weather to : " + std::to_string( nextWeather ) );
         return true;
      }
   }
   return false;
}

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

bool Core::Zone::update( uint32_t currTime )
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
      if( ( !pSession->getPlayer()->getCurrentZone() )
          || ( pSession->getPlayer()->getCurrentZone() != shared_from_this() ) )
      {
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

   onUpdate( currTime );

   return true;
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
         pCell = getCell( posX, posY );

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

void Core::Zone::updateActorPosition( Entity::Actor &actor )
{

   if( actor.getCurrentZone() != shared_from_this() )
      return;

   actor.checkInRangeActors();

   uint32_t cellX = getPosX( actor.getPos().x );
   uint32_t cellY = getPosY( actor.getPos().z );

   if( cellX >= _sizeX || cellY >= _sizeY )
      return;

   Cell* pCell = getCell( cellX, cellY );
   Cell* pOldCell = actor.m_pCell;
   if( !pCell )
   {
      pCell = create( cellX, cellY );
      pCell->init( cellX, cellY, shared_from_this() );
   }

   // If object moved cell
   if( pCell != pOldCell )
   {

      if( pOldCell )
         pOldCell->removeActor( actor.getAsActor() );

      pCell->addActor( actor.getAsActor() );
      actor.m_pCell = pCell;

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
         pCell = getCell( posX, posY );
         if( pCell )
            updateInRangeSet( actor.getAsActor(), pCell );
      }
   }
}


void Core::Zone::updateInRangeSet( Entity::ActorPtr pActor, Cell* pCell )
{
   if( pCell == nullptr )
      return;

   // TODO: make sure gms can overwrite this. Potentially temporary solution
   if( g_framework.getTerritoryMgr().isPrivateTerritory( getTerritoryId() ) )
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

      float distance = Math::Util::distance( pCurAct->getPos().x, pCurAct->getPos().y, pCurAct->getPos().z,
                                             pActor->getPos().x, pActor->getPos().y, pActor->getPos().z );

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

            // this is a hack to limit actor spawn in one packetset
            count++;
            if( count > 12 )
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
         else if( ( pActor->isBattleNpc() || pActor->isEventNpc() ) && pCurAct->isPlayer() && pActor->isAlive() )
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

void Core::Zone::onEnterTerritory( Entity::Player& player )
{
   g_framework.getLogger().debug( "Zone::onEnterTerritory: Zone#" + std::to_string( getGuId() ) + "|" + std::to_string( getTerritoryId() ) +
                                                + ", Entity#" + std::to_string( player.getId() ) );
}

void Core::Zone::onLeaveTerritory( Entity::Player& player )
{
   g_framework.getLogger().debug( "Zone::onLeaveTerritory: Zone#" + std::to_string( getGuId() ) + "|" + std::to_string( getTerritoryId() ) +
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

void Core::Zone::registerInstanceObj( Entity::InstanceObjectPtr object )
{
   if( !object )
      return;

   //object->setParentInstance( InstanceContentPtr( this ) );

   m_instanceObjects[object->getId()] = object;

   g_framework.getLogger().debug( "Registered instance eobj: " + std::to_string( object->getId() ) );
}

Core::Entity::InstanceObjectPtr Core::Zone::getInstanceObject( uint32_t objId )
{
   auto obj = m_instanceObjects.find( objId );
   if( obj == m_instanceObjects.end() )
      return nullptr;

   return obj->second;
}

void Core::Zone::updateInstanceObj( Core::Entity::InstanceObjectPtr object )
{
   if( !object )
      return;

   for( const auto& playerIt : m_playerMap )
   {
      // send that packet with le data
      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcObjectSpawn > eobjStatePacket( playerIt.second->getId() );
      eobjStatePacket.data().objKind = object->getObjKind();
      eobjStatePacket.data().state = object->getState();
      eobjStatePacket.data().objId = object->getId();
      eobjStatePacket.data().hierachyId = object->getHierachyId();
      eobjStatePacket.data().position = object->getPos();

      // ????
      //eobjStatePacket.data().levelId = 4236873;
      //eobjStatePacket.data().unknown2 = 5;
      //eobjStatePacket.data().unknown1C = 1065353216;
      //eobjStatePacket.data().unknown20 = 2147423605;
      //eobjStatePacket.data().actorId = 1074105831;
      //eobjStatePacket.data().unknown = 1;

      playerIt.second->queuePacket( eobjStatePacket );
   }
}
