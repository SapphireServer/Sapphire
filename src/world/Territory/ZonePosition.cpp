#include "ZonePosition.h"

Sapphire::ZonePosition::ZonePosition()
  :
  m_id( 0 ), m_targetZoneId( 0 ), m_radius( 0 )
{
}

Sapphire::ZonePosition::ZonePosition( uint32_t id, uint32_t targetZoneId, const Common::FFXIVARR_POSITION3& targetPosition,
                                  uint32_t radius, float rotation )
{
  m_id = id;
  m_targetZoneId = targetZoneId;
  m_targetPos = targetPosition;
  m_radius = radius;
  m_rotation = rotation;
}

Sapphire::ZonePosition::~ZonePosition()
{
}

uint32_t Sapphire::ZonePosition::getId() const
{
  return m_id;
}

uint32_t Sapphire::ZonePosition::getTargetZoneId() const
{
  return m_targetZoneId;
}

const Sapphire::Common::FFXIVARR_POSITION3& Sapphire::ZonePosition::getTargetPosition() const
{
  return m_targetPos;
}

float Sapphire::ZonePosition::getTargetRotation() const
{
  return m_rotation;
}


