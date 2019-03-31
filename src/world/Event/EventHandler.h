#ifndef _EVENT_H
#define _EVENT_H

#include "ForwardsZone.h"

namespace Sapphire::Event
{

  struct SceneResult
  {
    uint64_t actorId;
    uint32_t eventId;
    uint16_t param1;
    uint16_t param2;
    uint16_t param3;
    uint16_t param4;
  };

  class EventHandler
  {
  public:
    enum EventType : uint8_t
    {
      Talk = 1,
      Emote = 2,
      DistanceBelow = 3,
      DistanceOver = 4,
      BattleReward = 5,
      Craft = 6,
      Nest = 7,
      Item = 8,
      Drop = 9,
      WithinRange = 10,
      OutsideRange = 11,
      GameStart = 12,
      GameProgress = 13,
      EnterTerritory = 15,
      GameComeBack = 17,
      ActionResult = 18,
      MateriaCraft = 19,
      Fishing = 20,
      UI = 21,
      Housing = 22,
      Say = 23,
      TableGame = 24,
    };

    enum EventHandlerType : uint16_t
    {
      Quest = 0x0001,
      Warp = 0x0002,
      Unknown = 0x0003, // Came up in the client with "Begin" unsure that means
      Shop = 0x0004,
      Aetheryte = 0x0005,
      GuildLeveAssignment = 0x0006,
      DefaultTalk = 0x0009,
      CustomTalk = 0x000B,
      CompanyLeveOfficer = 0x000C,
      CraftLeve = 0x000E,
      GimmickAccessor = 0x000F,
      GimmickBill = 0x0010,
      GimmickRect = 0x0011,
      ChocoboTaxiStand = 0x0012,
      Opening = 0x0013,
      ExitRange = 0x0014,
      GCShop = 0x0016,
      GuildOrderGuide = 0x0017,
      GuildOrderOfficer = 0x0018,
      ContentNpc = 0x0019,
      Story = 0x001A,
      SpecialShop = 0x001B,
      BahamutGuide = 0x001C,
      HousingAethernet = 0x001E,
      FcTalk = 0x001F,
      ICDirector = 0x8003,
      QuestBattleDirector = 0x8006,
    };

    using SceneReturnCallback = std::function< void( Entity::Player&, const SceneResult& ) >;
    using SceneChainCallback = std::function< void( Entity::Player& ) >;
    using EventFinishCallback = std::function< void( Entity::Player&, uint64_t ) >;

    EventHandler( uint64_t actorId, uint32_t eventId, EventType eventType, uint32_t eventParam );

    ~EventHandler()
    {
    }

    uint64_t getActorId() const;

    uint32_t getId() const;

    uint16_t getType() const;

    uint16_t getEntryId() const;

    uint8_t getEventType() const;

    uint32_t getEventParam() const;

    bool hasPlayedScene() const;

    void setPlayedScene( bool playedScene );

    SceneReturnCallback getEventReturnCallback() const;

    void setEventReturnCallback( SceneReturnCallback callback );

    SceneChainCallback getSceneChainCallback() const;

    void setSceneChainCallback( SceneChainCallback callback );

    EventFinishCallback getEventFinishCallback() const;

    void setEventFinishCallback( EventFinishCallback callback );

    bool hasNestedEvent() const;

    void removeNestedEvent();

  protected:
    uint64_t m_actorId;
    uint32_t m_eventId;
    uint16_t m_entryId;
    uint16_t m_type;
    uint8_t m_eventType;
    uint32_t m_eventParam;
    EventHandlerPtr m_pNestedEvent;
    bool m_playedScene;
    SceneReturnCallback m_returnCallback;
    SceneChainCallback m_chainCallback;
    EventFinishCallback m_finishCallback;
  };

}
#endif
