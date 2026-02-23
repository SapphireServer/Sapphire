#pragma once

#include "GameObject.h"

namespace Sapphire::Entity
{
  enum EventObjectType : uint32_t
  {
    Obstacle,
    Door
  };

  class EventObject : public GameObject
  {
  public:
    EventObject( uint32_t actorId, uint32_t baseId, uint32_t boundInstanceId, uint32_t instanceId, uint8_t initialState,
                 Common::Vector3 pos, float rotation, const std::string& givenName, uint8_t permissionInv );

    using OnTalkEventHandler = std::function< void( Entity::Player&, Entity::EventObjectPtr, TerritoryPtr, uint64_t ) >;

    void setEventObjectType( EventObjectType type );

    uint32_t getBoundInstanceId() const;

    void setBoundInstanceId( uint32_t boundInstanceId );

    uint8_t getState() const;

    void setState( uint8_t state );

    float getScale() const;

    void setScale( float scale );

    void setOnTalkHandler( OnTalkEventHandler handler );

    OnTalkEventHandler getOnTalkHandler() const;

    uint32_t getBaseId() const;

    const std::string& getName() const;

    TerritoryPtr getParentInstance() const;

    void setParentInstance( TerritoryPtr instance );

    void spawn( PlayerPtr pTarget ) override;

    void despawn( PlayerPtr pTarget ) override;

    void playSharedGroupTimeline( uint32_t flag, uint32_t animationFlag );

    void setHousingLink( uint32_t housingLink );

    uint32_t getHousingLink() const;

    uint32_t getInstanceId() const;

    void setPermissionInvisibility( uint8_t permissionInvisibility ) override;

    uint32_t getOwnerId() const;


  protected:
    EventObjectType m_eobjType;
    uint32_t m_instanceId;
    uint32_t m_housingLink;
    uint32_t m_boundInstanceId;
    uint32_t m_baseId;
    uint32_t m_ownerId;
    uint8_t m_state;
    float m_scale{};
    std::string m_name;
    TerritoryPtr m_parentInstance;
    OnTalkEventHandler m_onTalkEventHandler;


  };
}