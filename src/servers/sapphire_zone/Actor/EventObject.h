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
      EventObject( uint32_t objectId, uint32_t mapLinkId, uint8_t initialState, Common::FFXIVARR_POSITION3 pos,
                   const std::string& givenName = "none" );

      uint32_t getMapLinkId() const;
      void setMapLinkId( uint32_t mapLinkId );

      uint8_t getState() const;
      void setState( uint8_t state );

      uint32_t getObjectId() const;

      const std::string& getName() const;

      InstanceContentPtr getParentInstance() const;
      void setParentInstance( InstanceContentPtr instance );

      void spawn( PlayerPtr pTarget ) override;
      void despawn( PlayerPtr pTarget ) override;

   protected:
      uint32_t m_mapLinkId;
      uint32_t m_objectId;
      uint8_t m_state;
      std::string m_name;
      InstanceContentPtr m_parentInstance;
   };
}
}

#endif //SAPPHIRE_INSTANCEOBJECT_H
