#ifndef _ZONELINE_H
#define _ZONELINE_H

#include <Common.h>

namespace Core {

class ZonePosition
{
protected:
  uint32_t m_id;
  uint32_t m_targetZoneId;
  Common::FFXIVARR_POSITION3 m_targetPos;
  float m_rotation;
  uint32_t m_radius;

public:
  ZonePosition();

  ZonePosition( uint32_t id, uint32_t targetZoneId, const Common::FFXIVARR_POSITION3& targetPosition, uint32_t radius,
                float rotation );

  virtual ~ZonePosition();

  uint32_t getId() const;

  uint32_t getTargetZoneId() const;

  const Common::FFXIVARR_POSITION3& getTargetPosition() const;

  float getTargetRotation() const;

};

}
#endif
