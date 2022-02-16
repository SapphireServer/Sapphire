#pragma once

#include "GameObject.h"

namespace Sapphire::Entity
{

  class EventObject : public GameObject
  {
  public:
    EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId, uint32_t instanceId, uint8_t initialState,
                 Common::FFXIVARR_POSITION3 pos, float rotation, const std::string& givenName, uint8_t permissionInv );

    using OnTalkEventHandler = std::function< void( Entity::Player&, Entity::EventObjectPtr, TerritoryPtr, uint64_t ) >;

    uint32_t getGimmickId() const;

    void setGimmickId( uint32_t gimmickId );

    uint8_t getState() const;

    void setState( uint8_t state );

    float getScale() const;

    void setScale( float scale );

    void setOnTalkHandler( OnTalkEventHandler handler );

    OnTalkEventHandler getOnTalkHandler() const;

    uint32_t getObjectId() const;

    const std::string& getName() const;

    TerritoryPtr getParentInstance() const;

    void setParentInstance( TerritoryPtr instance );

    void spawn( PlayerPtr pTarget ) override;

    void despawn( PlayerPtr pTarget ) override;

    void setAnimationFlag( uint32_t flag, uint32_t animationFlag );

    void setHousingLink( uint32_t housingLink );

    uint32_t getHousingLink() const;

    uint32_t getInstanceId() const;

    uint8_t getPermissionInvisibility() const;
    void setPermissionInvisibility( uint8_t permissionInvisibility );

    uint32_t getOwnerId() const;

  protected:
    uint32_t m_instanceId;
    uint32_t m_housingLink;
    uint32_t m_gimmickId;
    uint32_t m_objectId;
    uint32_t m_ownerId;
    uint8_t m_state;
    uint8_t m_permissionInvisibility;
    float m_scale;
    std::string m_name;
    TerritoryPtr m_parentInstance;
    OnTalkEventHandler m_onTalkEventHandler;


  };
}