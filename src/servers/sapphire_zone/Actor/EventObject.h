#ifndef SAPPHIRE_INSTANCEOBJECT_H
#define SAPPHIRE_INSTANCEOBJECT_H

#include "Actor.h"

namespace Core
{
namespace Entity
{
   class EventObject : public Actor
   {
   public:
      EventObject( uint32_t actorId, uint32_t objectId, uint32_t gimmickId, uint8_t initialState, Common::FFXIVARR_POSITION3 pos,
                   float rotation, const std::string& givenName = "none" );

      using OnTalkEventHandler = std::function< void( Entity::Player&, Entity::EventObjectPtr, InstanceContentPtr, uint64_t ) >;

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

      InstanceContentPtr getParentInstance() const;
      void setParentInstance( InstanceContentPtr instance );

      void spawn( PlayerPtr pTarget ) override;
      void despawn( PlayerPtr pTarget ) override;

   protected:
      uint32_t m_gimmickId;
      uint32_t m_objectId;
      uint8_t m_state;
      float m_scale;
      std::string m_name;
      InstanceContentPtr m_parentInstance;
      OnTalkEventHandler m_onTalkEventHandler;
   };
}
}

#endif //SAPPHIRE_INSTANCEOBJECT_H
