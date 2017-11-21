#include <src/servers/Server_Common/Util/Util.h>
#include <src/servers/Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>

#include "src/servers/Server_Zone/Actor/Actor.h"
#include "StatusEffect.h"
#include "StatusEffectContainer.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"


using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::StatusEffect::StatusEffectContainer::StatusEffectContainer( Entity::ActorPtr pOwner )
   : m_pOwner( pOwner )
{
   // initialize the free slot queue
   for( uint8_t i = 0; i < MAX_EFFECTS; i++ )
   {
      m_freeEffectSlotQueue.push( i );
   }
}

int8_t Core::StatusEffect::StatusEffectContainer::getFreeSlot()
{
   int8_t freeEffectSlot = -1;

   if( m_freeEffectSlotQueue.empty() )
      return freeEffectSlot;

   freeEffectSlot = m_freeEffectSlotQueue.front();
   m_freeEffectSlotQueue.pop();

   return freeEffectSlot;
}

void Core::StatusEffect::StatusEffectContainer::freeSlot( uint8_t slotId )
{
   m_freeEffectSlotQueue.push( slotId );
}


Core::StatusEffect::StatusEffectContainer::~StatusEffectContainer()
{
}


void Core::StatusEffect::StatusEffectContainer::addStatusEffect( StatusEffectPtr pEffect )
{
   int8_t nextSlot = getFreeSlot();
   // if there is no slot left, do not add the effect
   if( nextSlot == -1 )
      return;

   pEffect->applyStatus();
   m_effectMap[nextSlot] = pEffect;

   ZoneChannelPacket< Server::FFXIVIpcAddStatusEffect > statusEffectAdd( m_pOwner->getId() );
   statusEffectAdd.data().actor_id = pEffect->getTargetActorId();
   statusEffectAdd.data().actor_id1 = pEffect->getSrcActorId(); 
   statusEffectAdd.data().current_hp = m_pOwner->getHp();
   statusEffectAdd.data().current_mp = m_pOwner->getMp();
   statusEffectAdd.data().current_tp = m_pOwner->getTp();
   statusEffectAdd.data().duration = static_cast< float >( pEffect->getDuration() ) / 1000;
   statusEffectAdd.data().effect_id = pEffect->getId();
   statusEffectAdd.data().effect_index = nextSlot;
   statusEffectAdd.data().max_hp = m_pOwner->getMaxHp();
   statusEffectAdd.data().max_mp = m_pOwner->getMaxMp();
   statusEffectAdd.data().max_something = 1;
    //statusEffectAdd.data().unknown2 = 28;
   statusEffectAdd.data().param = pEffect->getParam();


   bool sendToSelf = m_pOwner->isPlayer() ? true : false;
   m_pOwner->sendToInRangeSet( statusEffectAdd, sendToSelf );

}

void Core::StatusEffect::StatusEffectContainer::removeSingleStatusEffectFromId( uint32_t id )
{
   for (auto effectIt : m_effectMap)
   {
      if (effectIt.second->getId() == id)
      {
         removeStatusEffect( effectIt.first );
         break;
      }
   }
}

void Core::StatusEffect::StatusEffectContainer::removeStatusEffect( uint8_t effectSlotId )
{
   auto pEffectIt = m_effectMap.find( effectSlotId );
   if( pEffectIt == m_effectMap.end() )
      return;

   freeSlot( effectSlotId );

   auto pEffect = pEffectIt->second;
   pEffect->removeStatus();

   bool sendToSelf = m_pOwner->isPlayer() ? true : false;
   m_pOwner->sendToInRangeSet( ActorControlPacket142( m_pOwner->getId(), StatusEffectLose, pEffect->getId() ), sendToSelf );

   m_effectMap.erase( effectSlotId );

   sendUpdate();
}

std::map< uint8_t, Core::StatusEffect::StatusEffectPtr > Core::StatusEffect::StatusEffectContainer::getEffectMap() const
{
   return m_effectMap;
}

void Core::StatusEffect::StatusEffectContainer::sendUpdate()
{
   uint64_t currentTimeMs = Util::getTimeMs();

   ZoneChannelPacket< Server::FFXIVIpcStatusEffectList > statusEffectList( m_pOwner->getId() );

   statusEffectList.data().current_hp = m_pOwner->getHp();
   statusEffectList.data().current_mp = m_pOwner->getMp();
   statusEffectList.data().currentTp = m_pOwner->getTp();
   statusEffectList.data().max_hp = m_pOwner->getMaxHp();
   statusEffectList.data().max_mp = m_pOwner->getMaxMp();
   uint8_t slot = 0;
   for( auto effectIt : m_effectMap )
   {
      float timeLeft = static_cast< float >( effectIt.second->getDuration() - ( currentTimeMs - effectIt.second->getStartTimeMs() ) ) / 1000;
      statusEffectList.data().effect[slot].duration = timeLeft;
      statusEffectList.data().effect[slot].effect_id = effectIt.second->getId();
      statusEffectList.data().effect[slot].sourceActorId = effectIt.second->getSrcActorId();
      slot++;
   }

   bool sendToSelf = m_pOwner->isPlayer();
   m_pOwner->sendToInRangeSet( statusEffectList, sendToSelf );

}

void Core::StatusEffect::StatusEffectContainer::update()
{
   uint64_t currentTimeMs = Util::getTimeMs();

   uint32_t thisTickDmg = 0;
   uint32_t thisTickHeal = 0;

   for( auto effectIt : m_effectMap )
   {
      uint8_t effectIndex = effectIt.first;
      auto effect = effectIt.second;

      uint64_t lastTick = effect->getLastTickMs();
      uint64_t startTime = effect->getStartTimeMs();
      uint32_t duration = effect->getDuration();
      uint32_t tickRate = effect->getTickRate();

      if( ( currentTimeMs - startTime ) > duration )
      {
         // remove status effect
         removeStatusEffect( effectIndex );
         // break because removing invalidates iterators
         break;
      }

      if( ( currentTimeMs - lastTick ) > tickRate )
      {
         effect->setLastTick( currentTimeMs );
         effect->onTick();

         auto thisEffect = effect->getTickEffect();

         switch( thisEffect.first )
         {

         case 1:
         {
            thisTickDmg += thisEffect.second;
            break;
         }

         case 2:
         {
            thisTickHeal += thisEffect.second;
            break;
         }

         }
      }

   }

   if( thisTickDmg != 0 )
   {
      m_pOwner->takeDamage( thisTickDmg );
      m_pOwner->sendToInRangeSet( ActorControlPacket142( m_pOwner->getId(), HPFloatingText, 0, static_cast< uint8_t >( ActionEffectType::Damage ), thisTickDmg ) );
   }

   if( thisTickHeal != 0 )
   {
      m_pOwner->heal( thisTickDmg );
      m_pOwner->sendToInRangeSet( ActorControlPacket142( m_pOwner->getId(), HPFloatingText, 0, static_cast< uint8_t >( ActionEffectType::Heal ), thisTickHeal ) );
   }
}

bool Core::StatusEffect::StatusEffectContainer::hasStatusEffect( uint32_t id )
{
   for( auto effectIt : m_effectMap )
   {
      if( effectIt.second->getId() == id )
      {
         return true;
      }
   }

   return false;
}