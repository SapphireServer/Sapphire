#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Zone.h"
#include "Event/Director.h"
#include "Forwards.h"

namespace Core
{
   namespace Data
   {
      struct InstanceContent;
   }
class InstanceContent : public Event::Director, public Zone
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

   bool init() override;
   void onBeforePlayerZoneIn( Entity::Player& player ) override;
   void onPlayerZoneIn( Entity::Player& player ) override;
   void onLeaveTerritory( Entity::Player& player ) override;
   void onFinishLoading( Entity::Player& player ) override;
   void onInitDirector( Entity::Player& player ) override;
   void onSomeDirectorEvent( Entity::Player& player ) override;
   void onUpdate( uint32_t currTime ) override;
   void onTalk( Entity::Player& player, uint32_t eventId, uint64_t actorId );
   void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override;

   void onRegisterEObj( Entity::EventObjectPtr object ) override;

   void setVar( uint8_t index, uint8_t value );
   void setSequence( uint8_t value );
   void setBranch( uint8_t value );

   boost::shared_ptr< Core::Data::InstanceContent > getInstanceContentInfo() const;

   uint32_t getInstanceContentId() const;

   Entity::EventObjectPtr getEObjByName( const std::string& name );

   /*! number of milliseconds after all players are ready for the instance to commence (spawn circle removed) */
   const uint32_t instanceStartDelay = 1250;
private:
   Event::DirectorPtr m_pDirector;
   boost::shared_ptr< Core::Data::InstanceContent > m_instanceContentInfo;
   uint32_t m_instanceContentId;
   InstanceContentState m_state;

   int64_t m_instanceExpireTime;
   int64_t m_instanceCommenceTime;

   Entity::EventObjectPtr m_pEntranceEObj;

   std::map< std::string, Entity::EventObjectPtr > m_eventObjectMap;
   std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventIdToObjectMap;
   std::set< uint32_t > m_spawnedPlayers;
};

}
#endif //SAPPHIRE_INSTANCECONTENT_H
