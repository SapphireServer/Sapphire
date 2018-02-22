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
      EventObject( uint32_t objectId, uint32_t mapLinkId );
      EventObject( uint32_t objectId, uint32_t mapLinkId, Common::FFXIVARR_POSITION3 pos );

      uint32_t getMapLinkId() const;
      void setMapLinkId( uint32_t mapLinkId );

      uint8_t getState() const;
      void setState( uint8_t state );

      InstanceContentPtr getParentInstance() const;
      void setParentInstance( InstanceContentPtr instance );

   protected:
      uint32_t m_mapLinkId;
      uint8_t m_state;
      InstanceContentPtr m_parentInstance;
   };
}
}

#endif //SAPPHIRE_INSTANCEOBJECT_H
