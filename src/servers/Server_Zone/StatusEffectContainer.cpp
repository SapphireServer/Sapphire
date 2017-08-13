#include <Server_Common/Util.h>
#include <Server_Common/ServerPacketDef.h>

#include "Actor.h"
#include "StatusEffect.h"
#include "StatusEffectContainer.h"
#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"


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
   uint8_t nextSlot = getFreeSlot();
   // if there is no slot left, do not add the effect
   if( nextSlot == -1 )
      return;

   pEffect->applyStatus();
   m_effectMap[nextSlot] = pEffect;

   GamePacketNew< Server::FFXIVIpcAddStatusEffect > statusEffectAdd( m_pOwner->getId() );
   statusEffectAdd.data().actor_id = m_pOwner->getId();
   statusEffectAdd.data().actor_id1 = m_pOwner->getId();
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
   statusEffectAdd.data().unkpower1 = pEffect->getPower();
   statusEffectAdd.data().unkpower2 = pEffect->getPower_2();

   bool sendToSelf = m_pOwner->isPlayer() ? true : false;
   m_pOwner->sendToInRangeSet( statusEffectAdd, sendToSelf );

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

void Core::StatusEffect::StatusEffectContainer::sendUpdate()
{
   uint64_t currentTimeMs = Util::getTimeMs();

   GamePacketNew< Server::FFXIVIpcStatusEffectList > statusEffectList( m_pOwner->getId() );

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

   bool sendToSelf = m_pOwner->isPlayer() ? true : false;
   m_pOwner->sendToInRangeSet( statusEffectList, sendToSelf );

}

void Core::StatusEffect::StatusEffectContainer::update()
{
   uint64_t currentTimeMs = Util::getTimeMs();

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
      }

   }
}
