#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Territory.h"
#include "Event/Director.h"
#include "Forwards.h"
#include <Exd/Structs.h>
#include <memory>

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

    /*0x40000001 - INSTANCE_CONTENT_ORDER_SYSTEM_START
      0x40000002 - INSTANCE_CONTENT_ORDER_SYSTEM_CLEAR_NORMAL
      0x40000003 - INSTANCE_CONTENT_ORDER_SYSTEM_RESET_???? ( not really sure about that, seems like reset, arg1 must be 1 )
      0x40000004 - INSTANCE_CONTENT_ORDER_PVP_READY ( unsure )
      0x40000005 - INSTANCE_CONTENT_ORDER_SYSTEM_RESET
      0x40000006 - INSTANCE_CONTENT_ORDER_SYSTEM_RESTART
      0x40000007 - INSTANCE_CONTENT_ORDER_SYSTEM_VOTE_ENABLE
      0x40000008 - INSTANCE_CONTENT_ORDER_SYSTEM_VOTE_START
      0x40000009 - INSTANCE_CONTENT_ORDER_SYSTEM_VOTE_RESULT
      0x4000000A - INSTANCE_CONTENT_ORDER_SYSTEM_VOTE_CANCEL
      0x4000000B - INSTANCE_CONTENT_ORDER_SYSTEM_UPDATE_CLEAR_MEMBER
      0x4000000C - INSTANCE_CONTENT_ORDER_SYSTEM_PLAY_SHARED_GROUP
      0x4000000D - INSTANCE_CONTENT_ORDER_SYSTEM_SyncTime?
      0x4000000E - INSTANCE_CONTENT_ORDER_SYSTEM_Unknown - no args - some timer set */
    enum DirectorEventId : uint32_t
    {
      DEBUG_TimeSync = 0xC0000001,
      DutyCommence = 0x40000001,
      DutyComplete = 0x40000002,
      SetStringendoMode = 0x40000003,
      SetDutyTime = 0x40000004,
      LoadingScreen = 0x40000005,
      Forward = 0x40000006,
      BattleGroundMusic = 0x40000007,
      InvalidateTodoList = 0x40000008,
      VoteState = 0x40000009,
      VoteStart = 0x4000000A,
      VoteResult = 0x4000000B,
      VoteFinish = 0x4000000C,
      FirstTimeNotify = 0x4000000D,
      TreasureVoteRefresh = 0x4000000E,
      SetSharedGroupId = 0x4000000F,
    };

    enum EventHandlerOrderId : uint32_t
    {
      SheetDataReady = 0x80000000,
      AbortContent = 0x40000001, //forceFlag
      LuaOnStartCutscene = 0x40000002, //returnCode
      VoteRequest = 0x40000003, //voteType
      VoteReplay = 0x40000004 //voteType, accept
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

    InstanceContent( std::shared_ptr< Excel::ExcelStruct< Excel::InstanceContent > > pInstanceConfiguration,
                     std::shared_ptr< Excel::ExcelStruct< Excel::ContentFinderCondition > > pContentFinderCondition,
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

    void onAddEObj( Entity::EventObjectPtr object ) override;

    void sendSharedGroup( uint32_t sharedGroupId, uint32_t timeIndex );

    void sendInvalidateTodoList();

    void sendDutyComplete();

    void sendDutyCommence();

    void sendDutyReset();

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

    std::shared_ptr< Excel::ExcelStruct< Excel::InstanceContent > > getInstanceConfiguration() const;

    uint32_t getInstanceContentId() const;

    Entity::EventObjectPtr getEObjByName( const std::string& name );

    Entity::EventObjectPtr getEObjById( uint32_t eobjId );

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

    std::set< uint32_t > getSpawnedPlayerIds() const;

    void movePlayerToEntrance( Entity::Player& player );
  private:
    std::shared_ptr< Excel::ExcelStruct< Excel::InstanceContent > > m_instanceConfiguration;
    std::shared_ptr< Excel::ExcelStruct< Excel::ContentFinderCondition > > m_contentFinderCondition;
    std::shared_ptr< Excel::ExcelStruct< Excel::ContentMemberType > > m_contentMemberType;
    uint32_t m_instanceContentId;
    InstanceContentState m_state;
    uint16_t m_currentBgm;

    uint32_t m_instanceExpireTime;
    uint64_t m_instanceTerminateTime;
    uint64_t m_instanceCommenceTime;
    uint64_t m_instanceResetTime;
    uint64_t m_instanceResetFinishTime;

    bool m_voteState;
    bool m_instanceTerminate;

    Entity::EventObjectPtr m_pEntranceEObj;

    std::map< std::string, Entity::EventObjectPtr > m_eventObjectMap;
    std::unordered_map< uint32_t, Entity::EventObjectPtr > m_eventIdToObjectMap;
    std::set< uint32_t > m_spawnedPlayers;

    // the players which are bound to the instance, regardless of inside or offline
    std::set< uint32_t > m_boundPlayerIds;

    EncounterFightPtr m_pEncounter;
  };

}
#endif //SAPPHIRE_INSTANCECONTENT_H
