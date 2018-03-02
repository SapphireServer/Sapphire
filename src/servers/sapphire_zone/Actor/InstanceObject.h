#ifndef SAPPHIRE_INSTANCEOBJECT_H
#define SAPPHIRE_INSTANCEOBJECT_H

#include "GameObject.h"

namespace Core
{
namespace Entity
{
   class InstanceObject : public GameObject
   {
   public:
      InstanceObject( uint32_t objectId, uint32_t mapLinkId );
      InstanceObject( uint32_t objectId, uint32_t mapLinkId, Common::FFXIVARR_POSITION3 pos );

      uint32_t getHierachyId() const;
      void setHierachyId( uint32_t hierachyId );

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
