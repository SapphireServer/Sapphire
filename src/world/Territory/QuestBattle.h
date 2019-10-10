#ifndef SAPPHIRE_QUESTBATTLE_H
#define SAPPHIRE_QUESTBATTLE_H

#include "Territory.h"
#include "Event/Director.h"
#include "Forwards.h"

namespace Sapphire::Data
{
  struct QuestBattle;
}

namespace Sapphire
{
  class QuestBattle : public Event::Director, public Territory
  {
  public:
    QuestBattle( std::shared_ptr< Sapphire::Data::QuestBattle > pBattleDetails,
                 uint16_t territoryType,
                 uint32_t guId,
                 const std::string& internalName,
                 const std::string& contentName,
                 uint32_t questBattleId,
                 FrameworkPtr pFw );

    virtual ~QuestBattle() = default;

    bool init() override;

    void onBeforePlayerZoneIn( Entity::Player& player ) override;

    void onPlayerZoneIn( Entity::Player& player ) override;

    void onLeaveTerritory( Entity::Player& player ) override;

    void onFinishLoading( Entity::Player& player ) override;

    void onInitDirector( Entity::Player& player ) override;

    void onDirectorSync( Entity::Player& player ) override;

    void onUpdate( uint64_t tickCount ) override;

    void onTalk( Entity::Player& player, uint32_t eventId, uint64_t actorId );

    void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override;

    void onRegisterEObj( Entity::EventObjectPtr object ) override;

    void onEnterSceneFinish( Entity::Player& player );

    void setVar( uint8_t index, uint8_t value );

    void setSequence( uint8_t value );

    void setBranch( uint8_t value );

    void startQte();

    void startEventCutscene();

    void endEventCutscene();

    uint32_t getQuestId() const;

    void fail();
    void success();

    uint32_t getCountEnemyBNpc();

    void clearDirector( Entity::Player& player );

    Event::Director::DirectorState getState() const;

    std::shared_ptr< Sapphire::Data::QuestBattle > getQuestBattleDetails() const;

    uint32_t getQuestBattleId() const;

    Entity::EventObjectPtr getEObjByName( const std::string& name );

    /*! number of milliseconds after all players are ready for the instance to commence (spawn circle removed) */
    const uint32_t instanceStartDelay = 1250;

    Entity::PlayerPtr getPlayerPtr();

  private:
    std::shared_ptr< Sapphire::Data::QuestBattle > m_pBattleDetails;
    uint32_t m_questBattleId;
    Event::Director::DirectorState m_state;

    uint64_t m_instanceExpireTime;
    uint64_t m_instanceCommenceTime;
    uint64_t m_instanceFailTime;

    std::map< std::string, Entity::EventObjectPtr > m_eventObjectMap;
    std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventIdToObjectMap;
    Entity::PlayerPtr m_pPlayer;

  };

}
#endif
