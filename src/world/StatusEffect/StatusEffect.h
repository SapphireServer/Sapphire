#ifndef _STATUSEFFECT_H_
#define _STATUSEFFECT_H_

#include "Forwards.h"

#include "Action/ActionLut.h"

namespace Sapphire {
namespace StatusEffect {


class StatusEffect
{
public:
  StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                uint32_t duration, uint32_t tickRate );

  ~StatusEffect();

  void onTick();

  void onBeforeActionStart( World::Action::Action* action );

  void onActionExecute( World::Action::Action* action );

  bool onActionHitTarget( World::Action::Action* action, Entity::CharaPtr victim, int victimCounter );

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

  void setStacks( uint8_t stacks );

  uint8_t getStacks();

  void registerTickEffect( uint8_t type, uint32_t param );

  std::pair< uint8_t, uint32_t > getTickEffect();

  const std::string& getName() const;

  const Sapphire::World::Action::StatusEffectEntry& getEffectEntry() const;

  void replaceEffectEntry( Sapphire::World::Action::StatusEffectEntry entryOverride );

  bool isMarkedToRemove();

  void markToRemove();

  void refresh();
  void refresh( Sapphire::World::Action::StatusEffectEntry newEntry );

private:
  bool checkActionBoostType1( Sapphire::World::Action::Action* action ); // see cpp for more info
  bool checkActionBoostType2( Sapphire::World::Action::Action* action ); // see cpp for more info

  uint32_t m_id;
  Entity::CharaPtr m_sourceActor;
  Entity::CharaPtr m_targetActor;
  uint32_t m_duration;
  uint64_t m_startTime;
  uint32_t m_tickRate;
  uint64_t m_lastTick;
  uint16_t m_param;
  std::string m_name;
  std::pair< uint8_t, uint32_t > m_currTickEffect;
  Sapphire::World::Action::StatusEffectEntry m_effectEntry;
  uint32_t m_value;
  float m_cachedSourceCrit;
  float m_cachedSourceCritBonus;
  bool m_markToRemove;
};

}
}

#endif
