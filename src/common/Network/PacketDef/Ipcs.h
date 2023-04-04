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
    Ping = 0x2c6, // updated 6.38
    Init = 0x37b, // updated 6.38

    ActorFreeSpawn = 0x3a2, // updated 6.38

    InitZone = 0x1fe,      // updated 6.38
    PrepareZoning = 0x267, // updated 6.38

    EffectResult = 0x3b5,      // updated 6.38
    EffectResultBasic = 0x2c4, // updated 6.38

    ActorControl = 0x2c2,       // updated 6.38
    ActorControlTarget = 0x1b8, // updated 6.38
    ActorControlSelf = 0x256,   // updated 6.38
    ActorCast = 0x15f,          // updated 6.38
    ActorSetPos = 0x2f0,        // updated 6.38
    ActorMove = 0x25b,          // updated 6.38
    ActorGauge = 0x136,         // updated 6.38

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x268,    // updated 6.38
    UpdateClassInfo = 0x2f7, // updated 6.38

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0xa3,  // updated 6.38
    Logout = 0x146,   // updated 6.38
    CFNotify = 0x38a, // updated 6.38
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x21d, // updated 6.38
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0xbb, // updated 6.38
    CFCancel = 0x227,       // updated 6.38
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x029F,          // updated 5.58h
    SocialRequestResponse = 0x397,  // updated 6.38
    SocialMessage = 0x03CB,         // updated 5.58h
    SocialMessage2 = 0x01D7,        // updated 5.58h
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x30f, // updated 6.38

    Chat = 0x1e4, // updated 6.38
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x219, // updated 6.38

    ExamineSearchInfo = 0x213,    // updated 6.38
    UpdateSearchInfo = 0x3dc,     // updated 6.38
    InitSearchInfo = 0x1eb,       // updated 6.38
    ExamineSearchComment = 0x357, // updated 6.38

    ServerNoticeShort = 0x0333, // updated 5.58h
    ServerNotice = 0x92,        // updated 6.38
    SystemLogMessage = 0x1a6,   // updated 6.38
    SetOnlineStatus = 0x2e9,    // updated 6.38

    CountdownInitiate = 0x3b0, // updated 6.38
    CountdownCancel = 0x194,   // updated 6.38

    PlayerAddedToBlacklist = 0x2e6,     // updated 6.38
    PlayerRemovedFromBlacklist = 0x2b5, // updated 6.38
    BlackList = 0xde,                   // updated 6.38

    LinkshellList = 0x241,           // updated 6.38
    CrossWorldLinkshellList = 0x240, // updated 6.38
    FellowshipList = 0x26d,          // updated 6.38

    MailDeleteRequest = 0x1b7, // updated 6.38

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138,      // updated 5.0
    ReqMoogleMailLetter = 0xF139,    // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35h

    MarketBoardSearchResult = 0xea,        // updated 6.38
    MarketBoardItemListingCount = 0x174,   // updated 6.38
    MarketBoardItemListingHistory = 0x3cd, // updated 6.38
    MarketBoardItemListing = 0x379,        // updated 6.38
    MarketBoardPurchase = 0x370,           // updated 6.38
    ItemMarketBoardInfo = 0x209,           // updated 6.38

    CharaFreeCompanyTag = 0x013B,   // updated 4.5
    FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
    FreeCompanyInfo = 0x199,        // updated 6.38
    FreeCompanyDialog = 0x1d6,      // updated 6.38
    ExamineFreeCompanyInfo = 0x29a, // updated 6.38

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x317,       // updated 6.38
    EurekaStatusEffectList = 0x23b, // updated 6.38
    BossStatusEffectList = 0xc8,    // updated 6.38
    StatusEffectList2 = 0x30d,      // updated 6.38
    StatusEffectList3 = 0x12b,      // updated 6.38
    Effect = 0xfb,                  // updated 6.38
    AoeEffect8 = 0x2ef,             // updated 6.38
    AoeEffect16 = 0x3c6,            // updated 6.38
    AoeEffect24 = 0x97,             // updated 6.38
    AoeEffect32 = 0x24b,            // updated 6.38
    PersistantEffect = 0x12b,       // updated 6.38

    PlaceFieldMarker = 0x354,       // updated 6.38
    PlaceFieldMarkerPreset = 0x286, // updated 6.38

    GCAffiliation = 0x264, // updated 6.38

    PlayerSpawn = 0x94, // updated 6.38
    NpcSpawn = 0x269,   // updated 6.38
    NpcSpawn2 = 0x196,  // updated 6.38

    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x186,          // updated 6.38
    PartyMessage = 0x75,        // updated 6.38
    HateRank = 0xe5,            // updated 6.38
    HateList = 0x99,            // updated 6.38
    ObjectSpawn = 0x2d1,        // updated 6.38
    ObjectDespawn = 0x132,      // updated 6.38
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x2bf,        // updated 6.38
    PlayerStats = 0x2d8,        // updated 6.38
    ActorOwner = 0x2bf,         // updated 6.38
    PlayerStateFlags = 0x3e5,   // updated 6.38
    PlayerClassInfo = 0x27b,    // updated 6.38
    PlayerUpdateLook = 0x114,   // updated 6.38
    CharaVisualEffect = 0x121,  // updated 6.38

    ModelEquip = 0x2e2,   // updated 6.38
    Examine = 0x22f,      // updated 6.38
    CharaNameReq = 0x170, // updated 6.38

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x1e1,          // updated 6.38
    RetainerInformation = 0x260,          // updated 6.38

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x34d,                   // updated 6.38
    ContainerInfo = 0x2e4,              // updated 6.38
    InventoryTransactionFinish = 0x2fc, // updated 6.38
    InventoryTransaction = 0x31b,       // updated 6.38
    CurrencyCrystalInfo = 0x39a,        // updated 6.38

    InventoryActionAck = 0x2cf,  // updated 6.38
    UpdateInventorySlot = 0x335, // updated 6.38

    HuntingLogEntry = 0x2f3, // updated 6.38

    EventPlay = 0x284,    // updated 6.38
    EventPlay4 = 0xe2,    // updated 6.38
    EventPlay8 = 0x2c1,   // updated 6.38
    EventPlay16 = 0x7f,   // updated 6.38
    EventPlay32 = 0xd3,   // updated 6.38
    EventPlay64 = 0xc1,   // updated 6.38
    EventPlay128 = 0x29d, // updated 6.38
    EventPlay255 = 0x326, // updated 6.38
    EventStart = 0x8b,    // updated 6.38
    EventFinish = 0x362,  // updated 6.38

    EventContinue = 0x33e, // updated 6.38

    EventLinkshell = 0x1169,

    QuestActiveList = 0xcf,    // updated 6.38
    QuestUpdate = 0x17c,       // updated 6.38
    QuestCompleteList = 0x2f2, // updated 6.38

    QuestFinish = 0x25c,         // updated 6.38
    MSQTrackerComplete = 0x3bb,  // updated 6.38
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58h

    QuestTracker = 0xa8, // updated 6.38

    Mount = 0x2df, // updated 6.38

    DirectorVars = 0x1c7,       // updated 6.38
    SomeDirectorUnk1 = 0x0084,  // updated 5.18
    SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
    SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
    SomeDirectorUnk8 = 0x028A,  // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF,     // updated 5.58h
    DirectorPopUp4 = 0x019B,    // updated 5.58h
    DirectorPopUp8 = 0x0271,    // updated 5.58h

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x17a,   // updated 6.38
    PlayerTitleList = 0x2b3, // updated 6.38
    Discovery = 0x1f7,       // updated 6.38

    EorzeaTimeOffset = 0x2bc, // updated 6.38

    EquipDisplayFlags = 0x248, // updated 6.38

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287,     // updated 5.58h
    LootMessage = 0x65,       // updated 6.38
    ResultDialog = 0x113,     // updated 6.38
    DesynthResult = 0x308,    // updated 6.38

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0xd4,             // updated 6.38
    LandUpdate = 0x151,                   // updated 6.38
    LandAvailability = 0x81,              // updated 6.38
    YardObjectSpawn = 0x3b9,              // updated 6.38
    HousingIndoorInitialize = 0x271,      // updated 6.38
    LandPriceUpdate = 0x215,              // updated 6.38
    LandInfoSign = 0xa9,                  // updated 6.38
    LandRename = 0x22c,                   // updated 6.38
    HousingEstateGreeting = 0xa7,         // updated 6.38
    HousingUpdateLandFlagsSlot = 0x177,   // updated 6.38
    HousingLandFlags = 0x3ba,             // updated 6.38
    HousingShowEstateGuestAccess = 0x2ec, // updated 6.38

    HousingObjectInitialize = 0xc7,     // updated 6.38
    HousingInternalObjectSpawn = 0x1d3, // updated 6.38

    HousingWardInfo = 0x28e,   // updated 6.38
    HousingObjectMove = 0x282, // updated 6.38
    HousingObjectDye = 0x3ce,  // updated 6.38

    SharedEstateSettingsResponse = 0x3a0, // updated 6.38

    LandUpdateHouseName = 0x1a7, // updated 6.38
    LandSetMap = 0x1b0,          // updated 6.38

    CeremonySetActorAppearance = 0x1a9, // updated 6.38

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0xb3,     // updated 6.38

    DutyGauge = 0x02E5, // updated 5.58h

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x21f,           // updated 6.38
    DailyQuestRepeatFlags = 0x184, // updated 6.38

    MapUpdate = 0x2cd,    // updated 6.38
    MapUpdate4 = 0x3c8,   // updated 6.38
    MapUpdate8 = 0x1d9,   // updated 6.38
    MapUpdate16 = 0x389,  // updated 6.38
    MapUpdate32 = 0x9a,   // updated 6.38
    MapUpdate64 = 0x361,  // updated 6.38
    MapUpdate128 = 0x1c9, // updated 6.38

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
    AirshipTimers = 0x3d0,            // updated 6.38
    AirshipStatus = 0x314,            // updated 6.38
    AirshipStatusList = 0x257,        // updated 6.38
    AirshipExplorationResult = 0x288, // updated 6.38

    SubmarineTimers = 0x16d,            // updated 6.38
    SubmarineProgressionStatus = 0x31a, // updated 6.38
    SubmarineStatusList = 0x1a4,        // updated 6.38
    SubmarineExplorationResult = 0x147, // updated 6.38

    EnvironmentControl = 0x118,         // updated 6.38
    IslandWorkshopSupplyDemand = 0x168, // updated 6.38

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
