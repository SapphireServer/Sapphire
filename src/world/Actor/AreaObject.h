#pragma once

#include "GameObject.h"

namespace Sapphire::Entity
{

  class AreaObject : public GameObject
  {
  public:
    AreaObject( uint32_t actorId, uint32_t actionId, uint32_t vfxId, uint32_t ownerId, const Common::FFXIVARR_POSITION3& pos );

    void spawn( PlayerPtr pTarget ) override;

    void despawn( PlayerPtr pTarget ) override;

    uint32_t getOwnerId() const;

    void setOwnerId( uint32_t ownerId );

    uint32_t getActionId() const;

  protected:
    uint32_t m_actionId;
    uint32_t m_ownerId;
    uint32_t m_vfxId;
  };
}