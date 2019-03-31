#ifndef SAPPHIRE_QUESTBATTLE_H
#define SAPPHIRE_QUESTBATTLE_H

#include "Zone.h"
#include "Event/Director.h"
#include "Forwards.h"

namespace Sapphire::Data
{
  struct QuestBattle;
}

namespace Sapphire
{
  class QuestBattle : public Event::Director, public Zone
  {
  public:
    QuestBattle( std::shared_ptr< Sapphire::Data::QuestBattle > pBattleDetails,
                 uint16_t territoryType,
                 uint32_t guId,
                 const std::string& internalName,
                 const std::string& contentName,
                 uint32_t questBattleId,
                 FrameworkPtr pFw );

    virtual ~QuestBattle();

    bool init() override;

    void onBeforePlayerZoneIn( Entity::Player& player ) override;

    void onPlayerZoneIn( Entity::Player& player ) override;

    void onLeaveTerritory( Entity::Player& player ) override;

    void onFinishLoading( Entity::Player& player ) override;

    void onInitDirector( Entity::Player& player ) override;

    void onDirectorSync( Entity::Player& player ) override;

    void onUpdate( uint32_t currTime ) override;

    void onTalk( Entity::Player& player, uint32_t eventId, uint64_t actorId );

    void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override;

    void onRegisterEObj( Entity::EventObjectPtr object ) override;

    void setVar( uint8_t index, uint8_t value );

    void setSequence( uint8_t value );

    void setBranch( uint8_t value );

    void startQte();

    void startEventCutscene();

    void endEventCutscene();

    void clearDirector( Entity::Player& player );

    /*! set the current bgm index (inside bgm.exd) */
    void setCurrentBGM( uint16_t bgmId );

    /*! set the current bgm for a specific player */
    void setPlayerBGM( Entity::Player& player, uint16_t bgmId );

    /*! get the currently playing bgm index */
    uint16_t getCurrentBGM() const;

    Event::Director::DirectorState getState() const;

    std::shared_ptr< Sapphire::Data::QuestBattle > getQuestBattleDetails() const;

    uint32_t getQuestBattleId() const;

    Entity::EventObjectPtr getEObjByName( const std::string& name );

    /*! binds a player to the instance */
    bool bindPlayer( uint32_t playerId );

    /*! removes bind of player from the instance */
    void unbindPlayer( uint32_t playerId );

    /*! return true if the player is bound to the instance */
    bool isPlayerBound( uint32_t playerId ) const;

    /*! number of milliseconds after all players are ready for the instance to commence (spawn circle removed) */
    const uint32_t instanceStartDelay = 1250;

  private:
    std::shared_ptr< Sapphire::Data::QuestBattle > m_pBattleDetails;
    uint32_t m_questBattleId;
    Event::Director::DirectorState m_state;
    uint16_t m_currentBgm;

    int64_t m_instanceExpireTime;
    uint64_t m_instanceCommenceTime;

    std::map< std::string, Entity::EventObjectPtr > m_eventObjectMap;
    std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventIdToObjectMap;
    std::set< uint32_t > m_spawnedPlayers;

    uint32_t m_boundPlayerId;
  };

}
#endif
