#ifndef _CORE_NETWORK_PACKETS_IPCS_H
#define _CORE_NETWORK_PACKETS_IPCS_H

#include <stdint.h>

namespace Sapphire::Network::Packets
{

  ////////////////////////////////////////////////////////////////////////////////
  /// Lobby Connection IPC Codes
  /**
   * Server IPC Lobby Type Codes.
   */
  enum ServerLobbyIpcType : uint16_t
  {
    LobbyError = 0x0002,
    LobbyServiceAccountList = 0x000C,
    LobbyCharList = 0x000D,
    LobbyCharCreate = 0x000E,
    LobbyEnterWorld = 0x000F,
    LobbyServerList = 0x0015,
    LobbyRetainerList = 0x0017,

  };

  /**
   * Client IPC Lobby Type Codes.
   */
  enum ClientLobbyIpcType : uint16_t
  {
    ReqCharList = 0x0003,
    ReqEnterWorld = 0x0004,
    ClientVersionInfo = 0x0005,

    ReqCharDelete = 0x000A,
    ReqCharCreate = 0x000B,
  };

  ////////////////////////////////////////////////////////////////////////////////
  /// Zone Connection IPC Codes
  /**
   * Server IPC Zone Type Codes.
   */
  enum ServerZoneIpcType : uint16_t
  {
    Ping = 0x020a, // updated 6.31h
    Init = 0x032d, // updated 6.31h

    ActorFreeSpawn = 0x282, // updated 6.31h

    InitZone = 0x118, // updated 6.31h
    PrepareZoning = 0x27c, // updated 6.31h

    EffectResult = 0x214, // updated 6.31h
    EffectResultBasic = 0x205, // updated 6.31h

    ActorControl = 0x1a4, // updated 6.31h
    ActorControlTarget = 0x7e, // updated 6.31h
    ActorControlSelf = 0x203, // updated 6.31h
    ActorCast = 0x185, // updated 6.31h
    ActorSetPos = 0x99, // updated 6.31h
    ActorMove = 0x155, // updated 6.31h
    ActorGauge = 0x238, // updated 6.31h

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x119,   // updated 6.31h
    UpdateClassInfo = 0x2c5, // updated 6.31h

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x26c, // updated 6.31h
    Logout = 0x072,   // updated 6.31h
    CFNotify = 0x2a1, // updated 6.31h
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x21a, // updated 6.31h
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x26b, // updated 6.31h
    CFCancel = 0x1e3,        // updated 6.31h
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x029F,          // updated 5.58h
    SocialRequestResponse = 0x2c3,  // updated 6.31h
    SocialMessage = 0x03CB,         // updated 5.58h
    SocialMessage2 = 0x01D7,        // updated 5.58h
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x1a7, // updated 6.31h

    Chat = 0x00c5, // updated 6.31h
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x1f4, // updated 6.31h

    ExamineSearchInfo = 0x156, // updated 6.31h
    UpdateSearchInfo = 0xc8, // updated 6.31h
    InitSearchInfo = 0x00b7,      // updated 6.31h
    ExamineSearchComment = 0x102, // updated 6.31h

    ServerNoticeShort = 0x0333, // updated 5.58h
    ServerNotice = 0x03b0,      // updated 6.31h
    SystemLogMessage = 0x1a6, // updated 6.31h
    SetOnlineStatus = 0x2b7, // updated 6.31h

    CountdownInitiate = 0x3e1, // updated 6.31h
    CountdownCancel = 0x23a, // updated 6.31h

    PlayerAddedToBlacklist = 0x1cb, // updated 6.31h
    PlayerRemovedFromBlacklist = 0x37c, // updated 6.31h
    BlackList = 0x033d,                 // updated 6.31h

    LinkshellList = 0x3be, // updated 6.31h
    CrossWorldLinkshellList = 0xb8, // updated 6.31h
    FellowshipList = 0x2a3, // updated 6.31h

    MailDeleteRequest = 0x0117, // updated 6.31h

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138,      // updated 5.0
    ReqMoogleMailLetter = 0xF139,    // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35h

    MarketBoardSearchResult = 0x115, // updated 6.31h
    MarketBoardItemListingCount = 0x31a, // updated 6.31h
    MarketBoardItemListingHistory = 0x176, // updated 6.31h
    MarketBoardItemListing = 0x1ed, // updated 6.31h
    MarketBoardPurchase = 0x30b, // updated 6.31h
    ItemMarketBoardInfo = 0x23f, // updated 6.31h

    CharaFreeCompanyTag = 0x013B,   // updated 4.5
    FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
    FreeCompanyInfo = 0x29c, // updated 6.31h
    FreeCompanyDialog = 0x285, // updated 6.31h
    ExamineFreeCompanyInfo = 0x171, // updated 6.31h

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x305, // updated 6.31h
    EurekaStatusEffectList = 0x3a6, // updated 6.31h
    BossStatusEffectList = 0x1e4, // updated 6.31h
    StatusEffectList2 = 0x197, // updated 6.31h
    StatusEffectList3 = 0x2a7, // updated 6.31h
    Effect = 0x100, // updated 6.31h
    AoeEffect8 = 0x2b9, // updated 6.31h
    AoeEffect16 = 0x390, // updated 6.31h
    AoeEffect24 = 0x22a, // updated 6.31h
    AoeEffect32 = 0x120, // updated 6.31h
    PersistantEffect = 0x2a7, // updated 6.31h

    GCAffiliation = 0x184, // updated 6.31h

    PlayerSpawn = 0xf9, // updated 6.31h
    NpcSpawn = 0x3d5, // updated 6.31h
    NpcSpawn2 = 0x3b6, // updated 6.31h

    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x24e, // updated 6.31h
    PartyMessage = 0x297, // updated 6.31h
    HateRank = 0x1dd, // updated 6.31h
    HateList = 0x3a5, // updated 6.31h
    ObjectSpawn = 0x277, // updated 6.31h
    ObjectDespawn = 0x2de, // updated 6.31h
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x287, // updated 6.31h
    PlayerStats = 0x2b6, // updated 6.31h
    ActorOwner = 0x287, // updated 6.31h
    PlayerStateFlags = 0x395, // updated 6.31h
    PlayerClassInfo = 0x17c, // updated 6.31h
    PlayerUpdateLook = 0x1cc, // updated 6.31h
    CharaVisualEffect = 0x355, // updated 6.31h

    ModelEquip = 0xe1, // updated 6.31h
    Examine = 0x246, // updated 6.31h
    CharaNameReq = 0x1c4, // updated 6.31h

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x1ae, // updated 6.31h
    RetainerInformation = 0x139, // updated 6.31h

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x1c2, // updated 6.31h
    ContainerInfo = 0x93, // updated 6.31h
    InventoryTransactionFinish = 0x290, // updated 6.31h
    InventoryTransaction = 0x6e, // updated 6.31h
    CurrencyCrystalInfo = 0x385, // updated 6.31h

    InventoryActionAck = 0xd0, // updated 6.31h
    UpdateInventorySlot = 0xc2, // updated 6.31h

    HuntingLogEntry = 0xb0, // updated 6.31h

    EventPlay = 0x3b8, // updated 6.31h
    EventPlay4 = 0x1ec, // updated 6.31h
    EventPlay8 = 0x333, // updated 6.31h
    EventPlay16 = 0x3ae, // updated 6.31h
    EventPlay32 = 0x160, // updated 6.31h
    EventPlay64 = 0x2f2, // updated 6.31h
    EventPlay128 = 0x8b, // updated 6.31h
    EventPlay255 = 0x10b, // updated 6.31h
    EventStart = 0x92, // updated 6.31h
    EventFinish = 0x8c, // updated 6.31h

    EventContinue = 0x200, // updated 6.31h

    EventLinkshell = 0x1169,

    QuestActiveList = 0x82, // updated 6.31h
    QuestUpdate = 0xa7, // updated 6.31h
    QuestCompleteList = 0x227, // updated 6.31h

    QuestFinish = 0x30a, // updated 6.31h
    MSQTrackerComplete = 0xba, // updated 6.31h
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58h

    QuestTracker = 0x1c1, // updated 6.31h

    Mount = 0x116, // updated 6.31h

    DirectorVars = 0x105, // updated 6.31h
    SomeDirectorUnk1 = 0x0084,  // updated 5.18
    SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
    SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
    SomeDirectorUnk8 = 0x028A,  // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF,     // updated 5.58h
    DirectorPopUp4 = 0x019B,    // updated 5.58h
    DirectorPopUp8 = 0x0271,    // updated 5.58h

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x148, // updated 6.31h
    PlayerTitleList = 0x365, // updated 6.31h
    Discovery = 0x14b, // updated 6.31h

    EorzeaTimeOffset = 0x3d2, // updated 6.31h

    EquipDisplayFlags = 0x35e, // updated 6.31h

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287,     // updated 5.58h
    LootMessage = 0x191, // updated 6.31h
    ResultDialog = 0x394, // updated 6.31h
    DesynthResult = 0x16a, // updated 6.31h

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x69, // updated 6.31h
    LandUpdate = 0x32a, // updated 6.31h
    LandAvailability = 0x8f, // updated 6.31h
    YardObjectSpawn = 0x183, // updated 6.31h
    HousingIndoorInitialize = 0x206, // updated 6.31h
    LandPriceUpdate = 0x330, // updated 6.31h
    LandInfoSign = 0x220, // updated 6.31h
    LandRename = 0x304, // updated 6.31h
    HousingEstateGreeting = 0x1b6, // updated 6.31h
    HousingUpdateLandFlagsSlot = 0x2a2, // updated 6.31h
    HousingLandFlags = 0x1a0, // updated 6.31h
    HousingShowEstateGuestAccess = 0x369, // updated 6.31h

    HousingObjectInitialize = 0x3a7, // updated 6.31h
    HousingInternalObjectSpawn = 0x251, // updated 6.31h

    HousingWardInfo = 0x2bb, // updated 6.31h
    HousingObjectMove = 0xcb, // updated 6.31h
    HousingObjectDye = 0x328, // updated 6.31h

    SharedEstateSettingsResponse = 0x3a1, // updated 6.31h

    LandUpdateHouseName = 0x24d, // updated 6.31h
    LandSetMap = 0x2ce, // updated 6.31h

    CeremonySetActorAppearance = 0x2cb, // updated 6.31h

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x1e1, // updated 6.31h

    DutyGauge = 0x02E5, // updated 5.58h

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0xd4, // updated 6.31h
    DailyQuestRepeatFlags = 0x21c, // updated 6.31h

    MapUpdate = 0x31f, // updated 6.31h
    MapUpdate4 = 0x2ff, // updated 6.31h
    MapUpdate8 = 0xff, // updated 6.31h
    MapUpdate16 = 0x1d0, // updated 6.31h
    MapUpdate32 = 0x151, // updated 6.31h
    MapUpdate64 = 0x392, // updated 6.31h
    MapUpdate128 = 0x222, // updated 6.31h

    /// Doman Mahjong //////////////////////////////////////
    MahjongOpenGui = 0x02A4,       // only available in mahjong instance
    MahjongNextRound = 0x02BD,     // initial hands(baipai), # of riichi(wat), winds, honba, score and stuff
    MahjongPlayerAction = 0x02BE,  // tsumo(as in drawing a tile) called chi/pon/kan/riichi
    MahjongEndRoundTsumo = 0x02BF, // called tsumo
    MahjongEndRoundRon = 0x2C0,    // called ron or double ron (waiting for action must be flagged from discard packet to call)
    MahjongTileDiscard = 0x02C1,   // giri (discarding a tile.) chi(1)/pon(2)/kan(4)/ron(8) flags etc..
    MahjongPlayersInfo = 0xF2C2,   // actor id, name, rating and stuff..
    // 2C3 and 2C4 are currently unknown
    MahjongEndRoundDraw = 0x02C5, // self explanatory
    MahjongEndGame = 0x02C6,      // finished oorasu(all-last) round; shows a result screen.

    /// Airship & Submarine //////////////////////////////////////
    AirshipTimers = 0xda, // updated 6.31h
    AirshipStatus = 0x2f1, // updated 6.31h
    AirshipStatusList = 0x39d, // updated 6.31h
    AirshipExplorationResult = 0x3c4, // updated 6.31h

    SubmarineTimers = 0x263, // updated 6.31h
    SubmarineProgressionStatus = 0x25a, // updated 6.31h
    SubmarineStatusList = 0xac, // updated 6.31h
    SubmarineExplorationResult = 0x194, // updated 6.31h

    EnvironmentControl = 0xef, // updated 6.31h
    IslandWorkshopSupplyDemand = 0x190, // updated 6.31h

  };

  /**
   * Client IPC Zone Type Codes.
   */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x0273, // updated 6.31h
    InitHandler = 0x03a8, // updated 6.31h

    FinishLoadingHandler = 0x032d, // updated 6.31h

    CFCommenceHandler = 0x0381, // updated 5.58h

    CFCancelHandler = 0x02B2,    // updated 5.58h
    CFRegisterDuty = 0x01BD,     // updated 5.58h
    CFRegisterRoulette = 0x037A, // updated 5.58h
    PlayTimeHandler = 0x02B7,    // updated 5.58h
    LogoutHandler = 0x0387,      // updated 6.31h
    CancelLogout = 0x01e3,       // updated 6.31h
    CFDutyInfoHandler = 0xF078,  // updated 4.2

    SocialReqSendHandler = 0x00D7,  // updated 5.58h
    SocialResponseHandler = 0x023B, // updated 5.58h
    CreateCrossWorldLS = 0x035D,    // updated 5.58h

    ChatHandler = 0x00f1, // Updated 6.31h
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x036C,  // updated 5.58h
    LeavePartyHandler = 0x019D,      // updated 5.58h
    KickPartyMemberHandler = 0x0262, // updated 5.58h
    DisbandPartyHandler = 0x0276,    // updated 5.58h

    SocialListHandler = 0x0200,              // updated 6.31
    SetSearchInfoHandler = 0x0368,           // updated 6.31h
    ReqSearchInfoHandler = 0x03b0,           // updated 6.31h
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
    BlackListHandler = 0x010c,             // updated 6.31h
    PlayerSearchHandler = 0x037D,          // updated 5.58h

    LinkshellListHandler = 0x03B6, // updated 5.58h

    MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58h
    MarketBoardRequestItemListings = 0x0122,    // updated 5.58h
    MarketBoardSearch = 0x0082,                 // updated 5.58h

    ReqExamineFcInfo = 0x037B, // updated 5.58h

    FcInfoReqHandler = 0x9999, // unknown

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x00C3, // updated 5.58h

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x03e1, // updated 6.31h
    ReqCountdownCancel = 0x023a,   // updated 6.31h

    ZoneLineHandler = 0x00ce,  // updated 6.31h
    ClientTrigger = 0x0244,    // updated 6.31h
    DiscoveryHandler = 0x038B, // updated 5.58h

    PlaceFieldMarkerPreset = 0x204, // updated 6.30h
    PlaceFieldMarker = 0x38e,       // updated 6.30h
    SkillHandler = 0x0133,          // updated 6.31h
    GMCommand1 = 0x0278,            // updated 6.31h
    GMCommand2 = 0x03d8,            // updated 6.31h
    AoESkillHandler = 0x0152,       // updated 5.58h

    UpdatePositionHandler = 0x01f7, // updated 6.31h

    InventoryModifyHandler = 0x01a2, // updated 6.31h

    InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

    ReqPlaceHousingItem = 0x02D4, // updated 5.58h
    BuildPresetHandler = 0x0223,  // updated 5.58h

    TalkEventHandler = 0x0205,         // updated 6.31h
    EmoteEventHandler = 0x00B0,        // updated 5.58h
    WithinRangeEventHandler = 0x02B6,  // updated 5.58h
    OutOfRangeEventHandler = 0x00b4,   // updated 6.31h
    EnterTeriEventHandler = 0x014e,    // updated 6.31h
    ShopEventHandler = 0x0384,         // updated 5.58h
    ReturnEventHandler = 0x0119,       // updated 6.31h
    TradeReturnEventHandler = 0x0100,  // updated 6.31h
    TradeReturnEventHandler2 = 0x023C, // updated 5.58h
    EventYield2Handler = 0x021D,       // updated 5.58h
    EventYield16Handler = 0x0207,      // updated 5.58h

    LinkshellEventHandler = 0x9999,  // unknown
    LinkshellEventHandler1 = 0x9999, // unknown

    ReqEquipDisplayFlagsChange = 0x03BC, // updated 6.30h

    LandRenameHandler = 0x028E,           // updated 5.58h
    HousingUpdateHouseGreeting = 0x0343,  // updated 5.58h
    HousingUpdateObjectPosition = 0x9999, // unknown
    HousingEditExterior = 0x027B,         // updated 5.58h
    HousingEditInterior = 0x02E3,         // updated 5.58h

    SetSharedEstateSettings = 0x00D2, // updated 5.58h

    UpdatePositionInstance = 0x03bd, // Updated 6.31h

    PerformNoteHandler = 0x0243, // updated 5.58h

    WorldInteractionHandler = 0x0274, // updated 5.58h
    Dive = 0x018C,                    // updated 6.30h
  };

  ////////////////////////////////////////////////////////////////////////////////
  /// Chat Connection IPC Codes
  /**
   * Server IPC Chat Type Codes.
   */
  enum ServerChatIpcType : uint16_t
  {
    Tell = 0x0064,              // updated for sb
    PublicContentTell = 0x00FB, // added 4.5, this is used when receiving a /tell in PublicContent instances such as Eureka or Bozja
    TellErrNotFound = 0x0066,

    FreeCompanyEvent = 0x012C, // added 5.0
  };

  /**
   * Client IPC Chat Type Codes.
   */
  enum ClientChatIpcType : uint16_t
  {
    TellReq = 0x0064,
    PublicContentTellReq = 0x0326, // updated 5.35 hotfix, this is used when sending a /tell in PublicContent instances such as Eureka or Bozja
  };

}

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
