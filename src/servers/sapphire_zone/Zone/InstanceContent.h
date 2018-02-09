#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Zone.h"
#include "Event/Director.h"
#include "Forwards.h"
#include <common/Exd/ExdDataGenerated.h>
#include "Actor/InstanceObject.h"

namespace Core
{

class InstanceContent : public Zone, Event::Director
{
public:
   enum InstanceContentState
   {
      Created,
      DutyReset,
      DutyInProgress,
      DutyFinished
   };

   InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                    uint32_t guId,
                    const std::string& internalName,
                    const std::string& contentName,
                    uint32_t instanceContentId );
   virtual ~InstanceContent();

   void onEnterTerritory( Entity::PlayerPtr pPlayer ) override;
   void onLeaveTerritory( Entity::PlayerPtr pPlayer ) override;
   void onFinishLoading( Entity::PlayerPtr pPlayer ) override;
   void onInitDirector( Entity::PlayerPtr pPlayer ) override;
   void onUpdate( uint32_t currTime ) override;

   void setVar( uint8_t index, uint8_t value );

   void registerInstanceObj( Entity::InstanceObjectPtr object );
   Entity::InstanceObjectPtr getInstanceObject( uint32_t objId );
   void updateInstanceObj( Entity::InstanceObjectPtr object );

   Core::Data::ExdDataGenerated::InstanceContentPtr getInstanceContentInfo() const;

   uint32_t getInstanceContentId() const;

private:
   Event::DirectorPtr m_pDirector;
   Core::Data::ExdDataGenerated::InstanceContentPtr m_instanceContentInfo;
   uint32_t m_instanceContentId;
   InstanceContentState m_state;

   int64_t m_instanceExpireTime;

   std::unordered_map< uint32_t, Core::Entity::InstanceObjectPtr > m_instanceObjects;
};

}
#endif //SAPPHIRE_INSTANCECONTENT_H
