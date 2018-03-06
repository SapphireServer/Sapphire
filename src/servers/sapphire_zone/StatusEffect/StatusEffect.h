#ifndef _STATUSEFFECT_H_
#define _STATUSEFFECT_H_

#include <boost/shared_ptr.hpp>

#include "Forwards.h"

namespace Core
{
namespace StatusEffect
{


class StatusEffect
{
public:
   StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                 uint32_t duration, uint32_t tickRate );

   ~StatusEffect();

   void onTick();
   void applyStatus();
   void removeStatus();

   uint32_t getId() const;
   uint32_t getDuration() const;
   uint32_t getTickRate() const;
   uint32_t getSrcActorId() const;
   uint32_t getTargetActorId() const;
   uint64_t getLastTickMs() const;
   uint64_t getStartTimeMs() const;
   uint16_t getParam() const;
   void setLastTick( uint64_t lastTick );
   void setParam( uint16_t param );
   void registerTickEffect( uint8_t type, uint32_t param );
   std::pair< uint8_t, uint32_t> getTickEffect();
   const std::string& getName() const;

private:
   uint32_t m_id;
   Entity::CharaPtr m_sourceActor;
   Entity::CharaPtr m_targetActor;
   uint32_t m_duration;
   uint64_t m_startTime;
   uint32_t m_tickRate;
   uint64_t m_lastTick;
   uint16_t m_param;
   std::string m_name;
   std::pair< uint8_t, uint32_t> m_currTickEffect;

};

}
}

#endif
