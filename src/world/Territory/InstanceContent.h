#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Territory.h"
#include "Event/Director.h"
#include "Forwards.h"
#include <Exd/Structs.h>

namespace Sapphire
{
  class InstanceContent : public Event::Director, public Territory
  {
  public:
    enum InstanceContentState
    {
      Created,
      DutyReset,
      DutyInProgress,
      DutyFinished,
      Terminate
    };

    enum DirectorEventId : uint32_t
    {
      DEBUG_TimeSync = 0xC0000001,
      DutyCommence = 0x80000001,
      BattleGroundMusic = 0x80000002,
      SetStringendoMode = 0x80000003,
      DutyComplete = 0x80000004,
      InvalidateTodoList = 0x80000005,
      LoadingScreen = 0x80000007,
      Forward = 0x80000008,
      VoteState = 0x80000009,
      VoteStart = 0x8000000A,
      VoteResult = 0x8000000B,
      VoteFinish = 0x8000000C,
      TreasureVoteRefresh = 0x8000000D,
      SetSharedGroupId = 0x8000000E,
      FirstTimeNotify = 0x8000000F
    };

    enum EventHandlerOrderId : uint32_t
    {
      SheetDataReady = 0x80000000,
      AbortContent = 0x80000001, //forceFlag
      LuaOnStartCutscene = 0x80000002, //returnCode
      VoteRequest = 0x80000003, //voteType
      VoteReplay = 0x80000004 //voteType, accept
    };

    enum DirectorSceneId
    {
        None = 0,
        SetupEventArgsOnStart = 1,
        SetupEventArgsInProgress = 2,

        DutyFailed = 5
    };

    enum TerminateReason : uint8_t
    {
      TimeExpired,
      TimeLimitReached,
      Abandoned,
      Ended
    };

    InstanceContent( std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::InstanceContent > > pInstanceConfiguration,
                     uint16_t territoryType,
                     uint32_t guId,
                     const std::string& internalName,
                     const std::string& contentName,
                     uint32_t instanceContentId );

    virtual ~InstanceContent();

    bool init() override;

    void onBeforePlayerZoneIn( Entity::Player& player ) override;

    void onPlayerZoneIn( Entity::Player& player ) override;

    void onLeaveTerritory( Entity::Player& player ) override;

    void onInitDirector( Entity::Player& player ) override;

    void onDirectorSync( Entity::Player& player ) override;

    void onUpdate( uint64_t tickCount ) override;

    void onEventHandlerOrder( Entity::Player& player, uint32_t arg0, uint32_t arg1, uint32_t arg2, uint32_t arg3,
                              uint32_t arg4 ) override;

    void onTalk( Entity::Player& player, uint32_t eventId, uint64_t actorId );

    void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override;

    void onRegisterEObj( Entity::EventObjectPtr object ) override;

    void sendSharedGroup( uint32_t sharedGroupId, uint32_t timeIndex );

    void sendInvalidateTodoList();

    void sendDutyComplete();

    void sendDutyCommence();

    void sendForward();

    void sendDutyFailed( bool force );

    void sendVoteState();

    void sendStringendoMode( uint16_t mode );

    void setVar( uint8_t index, uint8_t value );

    void setSequence( uint8_t value );

    void setFlags( uint8_t value );

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

    void setVoteState( bool state );

    bool getVoteState() const;

    bool hasPlayerPreviouslySpawned( Entity::Player& player ) const;

    InstanceContentState getState() const;

    std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::InstanceContent > > getInstanceConfiguration() const;

    uint32_t getInstanceContentId() const;

    Entity::EventObjectPtr getEObjByName( const std::string& name );

    /*! binds a player to the instance */
    bool bindPlayer( uint32_t playerId );

    /*! removes bind of player from the instance */
    void unbindPlayer( uint32_t playerId );

    /*! return true if the player is bound to the instance */
    bool isPlayerBound( uint32_t playerId ) const;

    /*! number of milliseconds after all players are ready for the instance to commence (spawn circle removed) */
    const uint32_t instanceStartDelay = 1250;

    void setExpireValue( uint32_t value );

    /*! return remaining time of instance lifetime */
    uint32_t getExpireValue();

    /*! return bitmask for current state of instance e.g. is vote active or single player instance */
    uint32_t getOptionFlags();

    void terminate( uint8_t reason );

    bool isTerminationReady() const;

    size_t getInstancePlayerCount() const;
  private:
    std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::InstanceContent > > m_instanceConfiguration;
    uint32_t m_instanceContentId;
    InstanceContentState m_state;
    uint16_t m_currentBgm;

    uint32_t m_instanceExpireTime;
    uint64_t m_instanceTerminateTime;
    uint64_t m_instanceCommenceTime;

    bool m_voteState;
    bool m_instanceTerminate;

    Entity::EventObjectPtr m_pEntranceEObj;

    std::map< std::string, Entity::EventObjectPtr > m_eventObjectMap;
    std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventIdToObjectMap;
    std::set< uint32_t > m_spawnedPlayers;

    // the players which are bound to the instance, regardless of inside or offline
    std::set< uint32_t > m_boundPlayerIds;
  };

}
#endif //SAPPHIRE_INSTANCECONTENT_H
