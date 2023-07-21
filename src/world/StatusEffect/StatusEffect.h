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
                uint32_t duration, std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, uint32_t tickRate, bool canApplyMultipleTimes );

  StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                uint32_t duration, uint32_t tickRate );

  ~StatusEffect();

  void onTick();

  std::unordered_map< Common::ParamModifier, int32_t >& getModifiers();

  void setModifier( Common::ParamModifier paramModifier, int32_t value );

  void delModifier( Common::ParamModifier paramModifier );

  void applyStatus();

  void removeStatus();

  uint32_t getId() const;

  uint32_t getDuration() const;

  uint32_t getTickRate() const;

  uint32_t getSrcActorId() const;
  Entity::CharaPtr getSrcActor() const;

  uint32_t getTargetActorId() const;

  uint64_t getLastTickMs() const;

  uint64_t getStartTimeMs() const;

  uint16_t getParam() const;

  uint32_t getFlag() const;

  bool getCanApplyMultipleTimes() const;

  std::vector< World::Action::StatusModifier > getStatusModifiers() const;

  void setLastTick( uint64_t lastTick );

  void setParam( uint16_t param );

  void setFlag( uint32_t flag );

  void setCanApplyMultipleTimes( bool canApplyMultipleTimes );

  void registerTickEffect( Common::ParamModifier type, uint32_t param );

  std::pair< Common::ParamModifier, uint32_t > getTickEffect();

  const std::string& getName() const;

  uint8_t getSlot() const;
  void setSlot( uint8_t slot );

private:
  uint32_t m_id;
  Entity::CharaPtr m_sourceActor;
  Entity::CharaPtr m_targetActor;
  uint32_t m_duration;
  uint64_t m_startTime;
  uint32_t m_tickRate;
  uint64_t m_lastTick;
  uint16_t m_param;
  uint32_t m_flag;
  std::string m_name;
  std::pair< Common::ParamModifier, uint32_t > m_currTickEffect;
  std::vector< World::Action::StatusModifier > m_statusModifiers;
  std::unordered_map< Common::ParamModifier, int32_t > m_modifiers;
  uint8_t m_slot;
  bool m_canApplyMultipleTimes;

};

}
}

#endif
