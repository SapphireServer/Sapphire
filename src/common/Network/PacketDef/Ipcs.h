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
    Ping = 0x2f7, // updated 6.35
    Init = 0xa9,  // updated 6.35

    ActorFreeSpawn = 0xcd, // updated 6.35

    InitZone = 0x37d,     // updated 6.35
    PrepareZoning = 0x99, // updated 6.35

    EffectResult = 0x37b,      // updated 6.35
    EffectResultBasic = 0x1fb, // updated 6.35

    ActorControl = 0x1bb,       // updated 6.35
    ActorControlTarget = 0x19d, // updated 6.35
    ActorControlSelf = 0x228,   // updated 6.35
    ActorCast = 0x291,          // updated 6.35
    ActorSetPos = 0x2e5,        // updated 6.35
    ActorMove = 0xb4,           // updated 6.35
    ActorGauge = 0x376,         // updated 6.35

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x394,    // updated 6.35
    UpdateClassInfo = 0x20a, // updated 6.35

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x301,        // updated 6.35
    Logout = 0x181,          // updated 6.35
    CFNotify = 0x3c6,        // updated 6.35
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x3ae,      // updated 6.35
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x2aa, // updated 6.35
    CFCancel = 0x206,        // updated 6.35
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x029F,          // updated 5.58h
    SocialRequestResponse = 0x33b,  // updated 6.35
    SocialMessage = 0x03CB,         // updated 5.58h
    SocialMessage2 = 0x01D7,        // updated 5.58h
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0xea, // updated 6.35

    Chat = 0x118, // updated 6.35
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x222, // updated 6.35

    ExamineSearchInfo = 0xf9,     // updated 6.35
    UpdateSearchInfo = 0x2b8,     // updated 6.35
    InitSearchInfo = 0x17c,       // updated 6.35
    ExamineSearchComment = 0x3a7, // updated 6.35

    ServerNoticeShort = 0x0333,   // updated 5.58h
    ServerNotice = 0x13a,         // updated 6.35
    SystemLogMessage = 0xf7,      // updated 6.35
    SetOnlineStatus = 0x233,      // updated 6.35

    CountdownInitiate = 0x23e,    // updated 6.35
    CountdownCancel = 0x365,      // updated 6.35

    PlayerAddedToBlacklist = 0x1fe,     // updated 6.35
    PlayerRemovedFromBlacklist = 0x19a, // updated 6.35
    BlackList = 0xd2,                   // updated 6.35

    LinkshellList = 0x225,           // updated 6.35
    CrossWorldLinkshellList = 0x2d7, // updated 6.35
    FellowshipList = 0x34c,          // updated 6.35

    MailDeleteRequest = 0x223, // updated 6.35

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138,      // updated 5.0
    ReqMoogleMailLetter = 0xF139,    // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35h

    MarketBoardSearchResult = 0x31e,       // updated 6.35
    MarketBoardItemListingCount = 0x32e,   // updated 6.35
    MarketBoardItemListingHistory = 0x3b1, // updated 6.35
    MarketBoardItemListing = 0x3cb,        // updated 6.35
    MarketBoardPurchase = 0x243,           // updated 6.35
    ItemMarketBoardInfo = 0x130,           // updated 6.35

    CharaFreeCompanyTag = 0x013B,  // updated 4.5
    FreeCompanyBoardMsg = 0x03DB,  // updated 5.58h
    FreeCompanyInfo = 0x177,       // updated 6.35
    FreeCompanyDialog = 0xac,      // updated 6.35
    ExamineFreeCompanyInfo = 0xf1, // updated 6.35

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x2d4,       // updated 6.35
    EurekaStatusEffectList = 0x3d0, // updated 6.35
    BossStatusEffectList = 0x35d,   // updated 6.35
    StatusEffectList2 = 0x3de,      // updated 6.35
    StatusEffectList3 = 0x123,      // updated 6.35
    Effect = 0xd4,                  // updated 6.35
    AoeEffect8 = 0x1a4,             // updated 6.35
    AoeEffect16 = 0x1c9,            // updated 6.35
    AoeEffect24 = 0x252,            // updated 6.35
    AoeEffect32 = 0x2c8,            // updated 6.35
    PersistantEffect = 0x123,       // updated 6.35

    PlaceFieldMarker = 0x160,      // updated 6.35
    PlaceFieldMarkerPreset = 0x90, // updated 6.35

    GCAffiliation = 0x2df, // updated 6.35

    PlayerSpawn = 0x100, // updated 6.35
    NpcSpawn = 0x1c0,    // updated 6.35
    NpcSpawn2 = 0x163,   // updated 6.35

    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x3bb,          // updated 6.35
    PartyMessage = 0x27a,       // updated 6.35
    HateRank = 0x17a,           // updated 6.35
    HateList = 0x205,           // updated 6.35
    ObjectSpawn = 0x1f4,        // updated 6.35
    ObjectDespawn = 0x2cb,      // updated 6.35
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x27f,        // updated 6.35
    PlayerStats = 0xee,         // updated 6.35
    ActorOwner = 0x27f,         // updated 6.35
    PlayerStateFlags = 0x32f,   // updated 6.35
    PlayerClassInfo = 0x3af,    // updated 6.35
    PlayerUpdateLook = 0x224,   // updated 6.35
    CharaVisualEffect = 0x339,  // updated 6.35

    ModelEquip = 0x381,   // updated 6.35
    Examine = 0x3dc,      // updated 6.35
    CharaNameReq = 0x1c4, // updated 6.35

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x79,           // updated 6.35
    RetainerInformation = 0x168,          // updated 6.35

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x220,                   // updated 6.35
    ContainerInfo = 0x1ad,              // updated 6.35
    InventoryTransactionFinish = 0x35b, // updated 6.35
    InventoryTransaction = 0x29f,       // updated 6.35
    CurrencyCrystalInfo = 0x304,        // updated 6.35

    InventoryActionAck = 0x256,  // updated 6.35
    UpdateInventorySlot = 0x20d, // updated 6.35

    HuntingLogEntry = 0x204, // updated 6.35

    EventPlay = 0x17f,    // updated 6.35
    EventPlay4 = 0xca,    // updated 6.35
    EventPlay8 = 0x175,   // updated 6.35
    EventPlay16 = 0x26a,  // updated 6.35
    EventPlay32 = 0x74,   // updated 6.35
    EventPlay64 = 0x255,  // updated 6.35
    EventPlay128 = 0x330, // updated 6.35
    EventPlay255 = 0xdd,  // updated 6.35
    EventStart = 0x8f,    // updated 6.35
    EventFinish = 0x39a,  // updated 6.35

    EventContinue = 0xaf, // updated 6.35

    EventLinkshell = 0x1169,

    QuestActiveList = 0x218,   // updated 6.35
    QuestUpdate = 0x3c2,       // updated 6.35
    QuestCompleteList = 0x29c, // updated 6.35

    QuestFinish = 0x1a7,         // updated 6.35
    MSQTrackerComplete = 0x2bc,  // updated 6.35
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58h

    QuestTracker = 0x2b2, // updated 6.35

    Mount = 0x317, // updated 6.35

    DirectorVars = 0x215,       // updated 6.35
    SomeDirectorUnk1 = 0x0084,  // updated 5.18
    SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
    SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
    SomeDirectorUnk8 = 0x028A,  // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF,     // updated 5.58h
    DirectorPopUp4 = 0x019B,    // updated 5.58h
    DirectorPopUp8 = 0x0271,    // updated 5.58h

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x371,   // updated 6.35
    PlayerTitleList = 0x2b5, // updated 6.35
    Discovery = 0x390,       // updated 6.35

    EorzeaTimeOffset = 0x333, // updated 6.35

    EquipDisplayFlags = 0x22f, // updated 6.35

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287,     // updated 5.58h
    LootMessage = 0x216,      // updated 6.35
    ResultDialog = 0x125,     // updated 6.35
    DesynthResult = 0x1da,    // updated 6.35

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x35a,            // updated 6.35
    LandUpdate = 0x1d6,                   // updated 6.35
    LandAvailability = 0x33c,             // updated 6.35
    YardObjectSpawn = 0x231,              // updated 6.35
    HousingIndoorInitialize = 0x33a,      // updated 6.35
    LandPriceUpdate = 0x33f,              // updated 6.35
    LandInfoSign = 0x245,                 // updated 6.35
    LandRename = 0x10a,                   // updated 6.35
    HousingEstateGreeting = 0x26f,        // updated 6.35
    HousingUpdateLandFlagsSlot = 0x3aa,   // updated 6.35
    HousingLandFlags = 0x124,             // updated 6.35
    HousingShowEstateGuestAccess = 0x332, // updated 6.35

    HousingObjectInitialize = 0x167,   // updated 6.35
    HousingInternalObjectSpawn = 0xc2, // updated 6.35

    HousingWardInfo = 0x1b5,   // updated 6.35
    HousingObjectMove = 0x14a, // updated 6.35
    HousingObjectDye = 0xa1,   // updated 6.35

    SharedEstateSettingsResponse = 0x1ff, // updated 6.35

    LandUpdateHouseName = 0x1f7, // updated 6.35
    LandSetMap = 0x30d,          // updated 6.35

    CeremonySetActorAppearance = 0x368, // updated 6.35

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0xc6,     // updated 6.35

    DutyGauge = 0x02E5, // updated 5.58h

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x98,            // updated 6.35
    DailyQuestRepeatFlags = 0x2a1, // updated 6.35

    MapUpdate = 0x15c,    // updated 6.35
    MapUpdate4 = 0x2fc,   // updated 6.35
    MapUpdate8 = 0xf4,    // updated 6.35
    MapUpdate16 = 0x320,  // updated 6.35
    MapUpdate32 = 0x3e5,  // updated 6.35
    MapUpdate64 = 0x199,  // updated 6.35
    MapUpdate128 = 0x312, // updated 6.35

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
    AirshipTimers = 0x1e5,            // updated 6.35
    AirshipStatus = 0x2f3,            // updated 6.35
    AirshipStatusList = 0x335,        // updated 6.35
    AirshipExplorationResult = 0x28f, // updated 6.35

    SubmarineTimers = 0xa5,             // updated 6.35
    SubmarineProgressionStatus = 0x292, // updated 6.35
    SubmarineStatusList = 0x76,         // updated 6.35
    SubmarineExplorationResult = 0x196, // updated 6.35

    EnvironmentControl = 0x126,         // updated 6.35
    IslandWorkshopSupplyDemand = 0x1b2, // updated 6.35

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
