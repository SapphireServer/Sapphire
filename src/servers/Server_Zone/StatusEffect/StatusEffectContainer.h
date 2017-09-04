#ifndef _STATUSEFFECTCONTAINER_H_
#define _STATUSEFFECTCONTAINER_H_

#include <boost/shared_ptr.hpp>

#include <queue>
#include <map>

#include "src/servers/Server_Zone/Forwards.h"

namespace Core
{
namespace StatusEffect
{

class StatusEffectContainer
{
public:
   StatusEffectContainer( Entity::ActorPtr pOwner );
   ~StatusEffectContainer();

   void addStatusEffect( StatusEffectPtr pEffect );
   void removeStatusEffect( uint8_t effectSlotId );
   void removeSingleStatusEffectFromId( uint32_t id );
   void update();

   bool hasStatusEffect( uint32_t id );

   int8_t getFreeSlot();
   void freeSlot( uint8_t slotId );

   void sendUpdate();


private:
   const uint8_t MAX_EFFECTS = 30;

   Entity::ActorPtr m_pOwner;
   std::queue< uint8_t > m_freeEffectSlotQueue;

   std::vector< StatusEffectPtr > m_effectList;
   std::vector< std::pair< uint8_t, uint32_t> > m_tickEffectList;
   std::map< uint8_t, StatusEffectPtr > m_effectMap;
};

}
}
#endif
