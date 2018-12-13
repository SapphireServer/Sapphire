#include "Action.h"

#include <Util/Util.h>


Sapphire::Action::Action::Action()
{
}

Sapphire::Action::Action::~Action()
{

}

uint16_t Sapphire::Action::Action::getId() const
{
  return m_id;
}

Sapphire::Common::HandleActionType Sapphire::Action::Action::getHandleActionType() const
{
  return m_handleActionType;
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getTargetChara() const
{
  return m_pTarget;
}

bool Sapphire::Action::Action::isInterrupted() const
{
  return m_bInterrupt;
}

void Sapphire::Action::Action::setInterrupted()
{
  m_bInterrupt = true;
}

uint64_t Sapphire::Action::Action::getStartTime() const
{
  return m_startTime;
}

void Sapphire::Action::Action::setStartTime( uint64_t startTime )
{
  m_startTime = startTime;
}

uint32_t Sapphire::Action::Action::getCastTime() const
{
  return m_castTime;
}

void Sapphire::Action::Action::setCastTime( uint32_t castTime )
{
  m_castTime = castTime;
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getActionSource() const
{
  return m_pSource;
}

bool Sapphire::Action::Action::update()
{
  // action has not been started yet
  if( m_startTime == 0 )
    return false;

  if( m_bInterrupt )
  {
    onInterrupt();
    return true;
  }

  uint64_t currTime = Util::getTimeMs();

  if( ( currTime - m_startTime ) > m_castTime )
  {
    onFinish();
    return true;
  }
  return false;
}
