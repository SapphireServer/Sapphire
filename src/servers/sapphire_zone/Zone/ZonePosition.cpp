#include "ZonePosition.h"

Core::ZonePosition::ZonePosition()
  :
  m_id( 0 ), m_targetZoneId( 0 ), m_radius( 0 )
{
}

Core::ZonePosition::ZonePosition( uint32_t id, uint32_t targetZoneId, const Common::FFXIVARR_POSITION3& targetPosition,
                                  uint32_t radius, float rotation )
{
  m_id = id;
  m_targetZoneId = targetZoneId;
  m_targetPos = targetPosition;
  m_radius = radius;
  m_rotation = rotation;
}

Core::ZonePosition::~ZonePosition()
{
}

uint32_t Core::ZonePosition::getId() const
{
  return m_id;
}

uint32_t Core::ZonePosition::getTargetZoneId() const
{
  return m_targetZoneId;
}

const Core::Common::FFXIVARR_POSITION3& Core::ZonePosition::getTargetPosition() const
{
  return m_targetPos;
}

float Core::ZonePosition::getTargetRotation() const
{
  return m_rotation;
}


