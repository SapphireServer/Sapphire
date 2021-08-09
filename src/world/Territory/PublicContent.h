#ifndef SAPPHIRE_PUBLICCONTENT_H
#define SAPPHIRE_PUBLICCONTENT_H

#include "Territory.h"
#include "Event/Director.h"
#include "Forwards.h"

namespace Sapphire::Data
{
  struct PublicContent;
}

namespace Sapphire
{
  class PublicContent : public Event::Director, public Territory
  {
  public:
    PublicContent( std::shared_ptr< Sapphire::Data::PublicContent > pConfiguration,
                     uint16_t territoryType,
                     uint32_t guId,
                     const std::string& internalName,
                     const std::string& contentName,
                     uint32_t contentId, uint16_t contentFinderConditionId = 0 );

    virtual ~PublicContent();

    bool init() override;

    void onBeforePlayerZoneIn( Entity::Player& player ) override;

    void onPlayerZoneIn( Entity::Player& player ) override;

    void onLeaveTerritory( Entity::Player& player ) override;

    void onUpdate( uint64_t tickCount ) override;

    void onFinishLoading( Entity::Player& player ) override;

    void onInitDirector( Entity::Player& player ) override;

    void onDirectorSync( Entity::Player& player ) override;

    void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override;

    void onRegisterEObj( Entity::EventObjectPtr object ) override;

    std::shared_ptr< Sapphire::Data::PublicContent > getConfiguration() const;

    uint32_t getContentId() const;

    void clearDirector( Entity::Player& player );

    void onTalk( Entity::Player& player, uint32_t eventId, uint64_t actorId );

    void setSequence( uint8_t value );

    void setBranch( uint8_t value );

    void setVar( uint8_t index, uint8_t value );

  private:
    std::shared_ptr< Sapphire::Data::PublicContent > m_Configuration;
    uint32_t m_ContentId;
    Entity::EventObjectPtr m_pEntranceEObj;
    std::map< std::string, Entity::EventObjectPtr > m_eventObjectMap;
    std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventIdToObjectMap;
  };

}
#endif //SAPPHIRE_PUBLICCONTENT_H
