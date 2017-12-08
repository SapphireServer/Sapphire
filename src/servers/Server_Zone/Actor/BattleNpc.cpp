#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <cmath>

#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Util/Util.h>
#include <Server_Common/Util/UtilMath.h>

#include "Player.h"
#include "BattleNpc.h"

#include "Network/PacketWrappers/MoveActorPacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

extern Core::Logger g_log;
extern Core::Data::ExdData g_exdData;

uint32_t Core::Entity::BattleNpc::m_nextID = 1149241694;

Core::Entity::BattleNpc::BattleNpc()
{
   m_id = 0;
   m_objKind = ObjKind::BattleNpc;
   m_status = ActorStatus::Idle;
}

Core::Entity::BattleNpc::~BattleNpc()
{

}

Core::Entity::BattleNpc::BattleNpc( uint16_t modelId, uint16_t nameid, const Common::FFXIVARR_POSITION3& spawnPos,
                                    uint16_t bnpcBaseId, uint32_t type, uint8_t level, uint8_t behaviour,
                                    uint32_t mobType ) : Actor()
{
   BattleNpc::m_nextID++;
   m_id = BattleNpc::m_nextID;
   //strcpy( m_name, pBNpc->m_name.c_str() );

   m_pos = spawnPos;
   m_posOrigin = spawnPos;

   m_objKind = ObjKind::BattleNpc;

   m_mode = MODE_IDLE;
   m_targetId = static_cast< uint64_t >( INVALID_GAME_OBJECT_ID );

   m_maxHp = 150;
   m_maxMp = 100;

   m_baseStats.max_hp = m_maxHp;
   m_baseStats.max_mp = m_maxMp;

   m_hp = m_maxHp;
   m_mp = m_maxMp;

   m_currentStance = Stance::Passive;

   m_class = ClassJob::Gladiator;
   m_level = level > uint8_t{0} ? level : uint8_t{70};

   m_modelId = modelId;
   m_nameId = nameid;

   m_behavior = behaviour;

   m_bnpcBaseId = bnpcBaseId;

   m_status = ActorStatus::Idle;

   m_pOwner = nullptr;

   m_mobType = mobType;

   m_invincibilityType = InvincibilityType::InvincibilityNone;

   //m_type = static_cast< Common::ObjKind >( type );

}

// spawn this player for pTarget
void Core::Entity::BattleNpc::spawn( PlayerPtr pTarget )
{
   //GamePacketNew< FFXIVIpcActorSpawn > spawnPacket( getId(), pTarget->getId() );

   //spawnPacket.data().unknown_0 = 0;
   //spawnPacket.data().ownerId = m_pOwner == nullptr ? INVALID_GAME_OBJECT_ID : m_pOwner->getId();
   //spawnPacket.data().targetId = INVALID_GAME_OBJECT_ID & 0xFFFFFFFF;
   //spawnPacket.data().hPCurr = m_hp;
   //spawnPacket.data().hPMax = m_baseStats.max_hp;
   //spawnPacket.data().level = m_level;
   ////spawnPacket.data().tPCurr = 1000;
   //spawnPacket.data().model = m_modelId;
   //spawnPacket.data().bnpcBaseId = m_bnpcBaseId;
   //spawnPacket.data().nameId = m_nameId;
   //spawnPacket.data().spawnIndex = pTarget->getSpawnIdForActorId( getId() );
   //g_log.info(std::to_string(spawnPacket.data().spawnIndex) + " " + std::to_string(getId()));
   //spawnPacket.data().status = static_cast< uint8_t >( m_status );
   //spawnPacket.data().mobAgressive = m_behavior;
   //spawnPacket.data().type = static_cast< uint8_t >( m_type );
   //spawnPacket.data().mobTypeIcon = m_mobType;
   //spawnPacket.data().unknown_33 = 5;
   //spawnPacket.data().typeFlags = 4;
   //spawnPacket.data().pos.x = m_pos.x;
   //spawnPacket.data().pos.y = m_pos.y;
   //spawnPacket.data().pos.z = m_pos.z;
   //spawnPacket.data().rotation = Math::Util::floatToUInt16Rot( getRotation() );
   ////spawnPacket.data().unknown_B0[11] = 1;
   ////spawnPacket.data().unknown_B0[12] = 4;
   ////spawnPacket.data().unknown_B0[14] = 20;

   //pTarget->queuePacket( spawnPacket );

   ZoneChannelPacket< FFXIVIpcNpcSpawn > spawnPacket( getId(), pTarget->getId() );


   spawnPacket.data().pos.x = m_pos.x;
   spawnPacket.data().pos.y = m_pos.y;
   spawnPacket.data().pos.z = m_pos.z;

   spawnPacket.data().targetId = INVALID_GAME_OBJECT_ID & 0xFFFFFFFF;
   spawnPacket.data().hPCurr = m_hp;
   spawnPacket.data().hPMax = m_baseStats.max_hp;
   spawnPacket.data().level = m_level;

   spawnPacket.data().subtype = 5;
   spawnPacket.data().enemyType = 4;

   spawnPacket.data().modelChara = m_modelId;
   spawnPacket.data().bNPCBase = m_bnpcBaseId;
   spawnPacket.data().bNPCName = m_nameId;
   spawnPacket.data().spawnIndex = pTarget->getSpawnIdForActorId( getId() );

   spawnPacket.data().rotation = Math::Util::floatToUInt16Rot( getRotation() );

   spawnPacket.data().type = static_cast< uint8_t >( m_objKind );

   spawnPacket.data().state = static_cast< uint8_t >( m_status );

   pTarget->queuePacket( spawnPacket );
}

// despawn
void Core::Entity::BattleNpc::despawn( ActorPtr pTarget )
{

   auto pPlayer = pTarget->getAsPlayer();

   pPlayer->freePlayerSpawnId( getId() );

   ActorControlPacket143 controlPacket( m_id, DespawnZoneScreenMsg, 0x04, getId(), 0x01 );
   pPlayer->queuePacket( controlPacket );

}

uint8_t Core::Entity::BattleNpc::getLevel() const
{
   return m_level;
}

Core::Entity::StateMode Core::Entity::BattleNpc::getMode() const
{
   return m_mode;
}

void Core::Entity::BattleNpc::setMode( StateMode mode )
{
   m_mode = mode;
}

uint8_t Core::Entity::BattleNpc::getbehavior() const
{
   return m_behavior;
}

void Core::Entity::BattleNpc::hateListAdd( ActorPtr pActor, int32_t hateAmount )
{
   auto hateEntry = new HateListEntry();
   hateEntry->m_hateAmount = hateAmount;
   hateEntry->m_pActor = pActor;

   m_hateList.insert( hateEntry );
}

Core::Entity::ActorPtr Core::Entity::BattleNpc::hateListGetHighest()
{

   auto it = m_hateList.begin();
   uint32_t maxHate = 0;
   HateListEntry* entry = nullptr;
   for( ; it != m_hateList.end(); ++it )
   {
      if( ( *it )->m_hateAmount > maxHate )
      {
         maxHate = ( *it )->m_hateAmount;
         entry = *it;
      }
   }

   if( entry && maxHate != 0 )
      return entry->m_pActor;

   return nullptr;
}

void Core::Entity::BattleNpc::setOwner( PlayerPtr pPlayer )
{
   m_pOwner = pPlayer;

   if( pPlayer != nullptr )
   {
      ZoneChannelPacket< FFXIVIpcActorOwner > setOwnerPacket( getId(), pPlayer->getId() );
      setOwnerPacket.data().type = 0x01;
      setOwnerPacket.data().actorId = pPlayer->getId();
      sendToInRangeSet( setOwnerPacket );
   }
   else
   {
      ZoneChannelPacket< FFXIVIpcActorOwner > setOwnerPacket(getId(), INVALID_GAME_OBJECT_ID );
      setOwnerPacket.data().type = 0x01;
      setOwnerPacket.data().actorId = INVALID_GAME_OBJECT_ID;
      sendToInRangeSet( setOwnerPacket );
   }

}

void Core::Entity::BattleNpc::sendPositionUpdate()
{
   MoveActorPacket movePacket( *this, 0x3A, 0x00, 0, 0x5A );
   sendToInRangeSet( movePacket );
}

bool Core::Entity::BattleNpc::moveTo( Common::FFXIVARR_POSITION3& pos )
{

   if( Math::Util::distance( getPos().x, getPos().y, getPos().z, 
                             pos.x, pos.y, pos.z ) <= 4 )
      // reached destination
      return true;

   float rot = Math::Util::calcAngFrom( getPos().x, getPos().z, pos.x, pos.z );
   float newRot = PI - rot + ( PI / 2 );

   face( pos );
   float angle = Math::Util::calcAngFrom( getPos().x, getPos().z, pos.x, pos.z ) + PI;
   
   float x = static_cast< float >( cosf( angle ) * 1.1f );
   float y = ( getPos().y + pos.y ) * 0.5f; // fake value while there is no collision
   float z = static_cast< float >( sinf( angle ) * 1.1f );

   Common::FFXIVARR_POSITION3 newPos{};

   newPos.x = getPos().x + x;
   newPos.y = y;
   newPos.z = getPos().z + z;

   setPosition( newPos );

   Common::FFXIVARR_POSITION3 tmpPos{};
   tmpPos.x = getPos().x + x;
   tmpPos.y = y;
   tmpPos.z = getPos().z + z;

   setPosition( tmpPos );
   setRotation(newRot);

   sendPositionUpdate();

   return false;

}

void Core::Entity::BattleNpc::aggro( ActorPtr pActor )
{

   m_lastAttack = Util::getTimeMs();
   hateListUpdate( pActor, 1 );

   changeTarget( pActor->getId() );
   setStance( Stance::Active );
   m_mode = MODE_COMBAT;

   if( pActor->isPlayer() )
   {
      PlayerPtr tmpPlayer = pActor->getAsPlayer();
      tmpPlayer->queuePacket( ActorControlPacket142( getId(), 0, 1, 1 ) );
      tmpPlayer->onMobAggro( getAsBattleNpc() );
   }
}

void Core::Entity::BattleNpc::deaggro( ActorPtr pActor )
{
   if( !hateListHasActor( pActor ) )
      hateListRemove( pActor );

   if( pActor->isPlayer() )
   {
      PlayerPtr tmpPlayer = pActor->getAsPlayer();
      tmpPlayer->onMobDeaggro( getAsBattleNpc() );
   }
}

void Core::Entity::BattleNpc::hateListClear()
{
   auto it = m_hateList.begin();
   for( ; it != m_hateList.end(); ++it )
   {
      if( isInRangeSet( ( *it )->m_pActor ) )
         deaggro( ( *it )->m_pActor );
      HateListEntry* tmpListEntry = ( *it );
      delete tmpListEntry;
   }
   m_hateList.clear();
}


void Core::Entity::BattleNpc::hateListRemove( ActorPtr pActor )
{
   auto it = m_hateList.begin();
   for( ; it != m_hateList.end(); ++it )
   {
      if( ( *it )->m_pActor == pActor )
      {
         HateListEntry* pEntry = *it;
         m_hateList.erase( it );
         delete pEntry;
         if( pActor->isPlayer() )
         {
            PlayerPtr tmpPlayer = pActor->getAsPlayer();
            tmpPlayer->onMobDeaggro( getAsBattleNpc() );
         }
         return;
      }
   }
}

bool Core::Entity::BattleNpc::hateListHasActor( ActorPtr pActor )
{
   auto it = m_hateList.begin();
   for( ; it != m_hateList.end(); ++it )
   {
      if( ( *it )->m_pActor == pActor )
         return true;
   }
   return false;
}

void Core::Entity::BattleNpc::resetPos()
{
   m_pos = m_posOrigin;
}

uint32_t Core::Entity::BattleNpc::getNameId() const
{
   return m_nameId;
}

void Core::Entity::BattleNpc::hateListUpdate( ActorPtr pActor, int32_t hateAmount )
{

   auto it = m_hateList.begin();
   for( ; it != m_hateList.end(); ++it )
   {
      if( ( *it )->m_pActor == pActor )
      {
         ( *it )->m_hateAmount += hateAmount;
         return;
      }
   }

   auto hateEntry = new HateListEntry();
   hateEntry->m_hateAmount = hateAmount;
   hateEntry->m_pActor = pActor;
   m_hateList.insert( hateEntry );
}

void Core::Entity::BattleNpc::onDeath()
{
   //LuaManager->onMobDeath( this );

   setTimeOfDeath( static_cast< uint32_t >( time( nullptr ) ) );
   setTargetId( INVALID_GAME_OBJECT_ID );
   m_currentStance = Stance::Passive;
   m_mode = MODE_IDLE;
   m_hp = 0;
   setOwner( nullptr );

   // todo: fully ghetto retarded exp reward pls fix
   {
      uint32_t minHate = -1;
      uint32_t maxHate = 0;
      uint32_t totalHate = 0;
      for( auto& pHateEntry : m_hateList )
      {
         if( pHateEntry->m_pActor->isPlayer() )
         {
            if( pHateEntry->m_hateAmount < minHate )
               minHate = pHateEntry->m_hateAmount;
            else if( pHateEntry->m_hateAmount > maxHate )
               maxHate = pHateEntry->m_hateAmount;
         }
         totalHate += pHateEntry->m_hateAmount;
      }

      //uint32_t plsBeHatedThisMuchAtLeast = totalHate / ( maxHate + 2 ) / clamp( m_hateList.size(), 1.0f, 1.5f );

      for( auto& pHateEntry : m_hateList )
      {
         // todo: this is pure retarded
         // todo: check for companion
         if( pHateEntry->m_pActor->isPlayer()  ) // && pHateEntry->m_hateAmount >= plsBeHatedThisMuchAtLeast )
         {
            uint8_t level = pHateEntry->m_pActor->getLevel();
            auto levelDiff = static_cast< int32_t >( this->m_level ) - level;
            auto cappedLevelDiff = Math::Util::clamp( levelDiff, 1, 6 );

            auto expNeeded = g_exdData.m_paramGrowthInfoMap[m_level + cappedLevelDiff - 1].needed_exp;
            int32_t exp = 0;

            // todo: arbitrary numbers pulled out of my ass
            if( m_level <= 14 )
               exp = ( expNeeded / ( 100 - levelDiff) ) + cappedLevelDiff + ( cappedLevelDiff * ( ( rand() % ( cappedLevelDiff * 9 ) ) + 1 ) );
            else if( m_level <= 24 )
               exp = ( expNeeded / ( 150 - levelDiff) ) + cappedLevelDiff + ( cappedLevelDiff * ( ( rand() % ( cappedLevelDiff * 8 ) ) + 1 ) );
            else if( m_level <= 34 )
               exp = ( expNeeded / ( 350 - levelDiff ) ) + cappedLevelDiff + ( cappedLevelDiff * ( ( rand() % ( cappedLevelDiff * 7 ) ) + 1 ) );
            else if( m_level <= 44 )
               exp = ( expNeeded / ( 550 - levelDiff ) ) + cappedLevelDiff + ( cappedLevelDiff *  ( ( rand() % ( cappedLevelDiff * 6  ) ) + 1 ) );
            else if( m_level <= 50 )
               exp = ( expNeeded / ( 750 - levelDiff ) ) + cappedLevelDiff + ( cappedLevelDiff * ( ( rand() % ( cappedLevelDiff * 5 ) ) + 1 ) );
            else
               exp = ( expNeeded / ( 1200 - levelDiff ) ) + cappedLevelDiff + ( cappedLevelDiff * ( ( rand() % ( cappedLevelDiff * 4 ) ) + 1 ) );
            

            // todo: this is actually retarded, we need real rand()
            srand( static_cast< uint32_t > ( time( nullptr ) ) );

            auto pPlayer = pHateEntry->m_pActor->getAsPlayer();
            pPlayer->gainExp( exp );
            pPlayer->onMobKill( m_nameId );
         }
      }
   }
   hateListClear();
}

void Core::Entity::BattleNpc::onActionHostile( ActorPtr pSource )
{

   if( hateListGetHighest() == nullptr )
      aggro( pSource );

   if( getClaimer() == nullptr )
      setOwner( pSource->getAsPlayer() );
}

Core::Entity::ActorPtr Core::Entity::BattleNpc::getClaimer() const
{
   return m_pOwner;
}


// HACK: this is highly experimental code, will have to be changed eventually
// since there are different types of mobs... (stationary, moving...) likely to be 
// handled by scripts entirely.
void Core::Entity::BattleNpc::update( int64_t currTime )
{

   if( !isAlive() )
   {
      m_status = ActorStatus::Idle;
      m_mode = MODE_IDLE;
      return;
   }

   updateStatusEffects();
   float distance = Math::Util::distance( m_pos.x, m_pos.y, m_pos.z,
                                          m_posOrigin.x, m_posOrigin.y, m_posOrigin.z );

   if( ( distance > 70 ) && m_mode != MODE_RETREAT )
   {
      changeTarget( INVALID_GAME_OBJECT_ID );
      m_mode = MODE_RETREAT;
      hateListClear();
      setOwner( nullptr );
   }

   switch( m_mode )
   {

   case MODE_RETREAT:
   {
      if( moveTo( m_posOrigin ) )
         m_mode = MODE_IDLE;
   }
   break;

   case MODE_IDLE:
   {
      ActorPtr pClosestActor = getClosestActor();

      if( pClosestActor && pClosestActor->isAlive() )
      {
         distance = Math::Util::distance( getPos().x, getPos().y, getPos().z,
                                          pClosestActor->getPos().x,
                                          pClosestActor->getPos().y,
                                          pClosestActor->getPos().z );

         //if( distance < 8 && getbehavior() == 2 )
         //   aggro( pClosestActor );
      }
   }
   break;

   case MODE_COMBAT:
   {
      ActorPtr pClosestActor = hateListGetHighest();

      if( pClosestActor != nullptr && !pClosestActor->isAlive() )
      {
         hateListRemove( pClosestActor );
         pClosestActor = hateListGetHighest();
      }

      if( pClosestActor != nullptr )
      {
         distance = Math::Util::distance( getPos().x, getPos().y, getPos().z,
                                          pClosestActor->getPos().x,
                                          pClosestActor->getPos().y,
                                          pClosestActor->getPos().z );

         if( distance > 4 )
            moveTo( pClosestActor->getPos() );
         else
         {
            if( face( pClosestActor->getPos() ) )
               sendPositionUpdate();
            // in combat range. ATTACK!
            autoAttack( pClosestActor );
         }
      }
      else
      {
         changeTarget( INVALID_GAME_OBJECT_ID );
         setStance( Stance::Passive );
         setOwner( nullptr );
         m_mode = MODE_RETREAT;
      }

   }
   break;
   }

}

uint32_t Core::Entity::BattleNpc::getTimeOfDeath() const
{
   return m_timeOfDeath;
}

void Core::Entity::BattleNpc::setTimeOfDeath( uint32_t tod )
{
   m_timeOfDeath = tod;
}

