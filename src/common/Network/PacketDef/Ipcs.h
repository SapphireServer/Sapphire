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
    Ping = 0x0108, // updated 6.31
    Init = 0x03d4, // updated 6.31

    ActorFreeSpawn = 0x1c3, // updated 6.31

    InitZone = 0x94,       // updated 6.31
    PrepareZoning = 0x1d7, // updated 6.31

    EffectResult = 0x36c,      // updated 6.31
    EffectResultBasic = 0x2e9, // updated 6.31

    ActorControl = 0x363,       // updated 6.31
    ActorControlTarget = 0x1ec, // updated 6.31
    ActorControlSelf = 0x267,   // updated 6.31
    ActorCast = 0x207,          // updated 6.31
    ActorSetPos = 0x186,        // updated 6.31
    ActorMove = 0x2a1,          // updated 6.31
    ActorGauge = 0xa9,          // updated 6.31

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x10d,   // updated 6.31
    UpdateClassInfo = 0xbd, // updated 6.31

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x171, // updated 6.31
    Logout = 0x243,   // updated 6.31
    CFNotify = 0x3a0, // updated 6.31
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x3a9, // updated 6.31
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x2ef, // updated 6.31
    CFCancel = 0x39a,        // updated 6.31
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x029F,          // updated 5.58 hotfix
    SocialRequestResponse = 0x18c,  // updated 6.31
    SocialMessage = 0x03CB,         // updated 5.58 hotfix
    SocialMessage2 = 0x01D7,        // updated 5.58 hotfix
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x27f, // updated 6.31

    Chat = 0x353, // updated 6.31
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x1f4, // updated 6.31

    ExamineSearchInfo = 0x33e,    // updated 6.31
    UpdateSearchInfo = 0x226,     // updated 6.31
    InitSearchInfo = 0x0321,      // updated 5.58 hotfix
    ExamineSearchComment = 0x279, // updated 6.31

    ServerNoticeShort = 0x0333, // updated 5.58 hotfix
    ServerNotice = 0x0363,      // updated 5.58 hotfix
    SystemLogMessage = 0x174,   // updated 6.31
    SetOnlineStatus = 0x3da,    // updated 6.31

    CountdownInitiate = 0x1ff, // updated 6.31
    CountdownCancel = 0x140,   // updated 6.31

    PlayerAddedToBlacklist = 0x27c,     // updated 6.31
    PlayerRemovedFromBlacklist = 0x21e, // updated 6.31
    BlackList = 0x0282,                 // updated 6.31

    LinkshellList = 0xf2,           // updated 6.31
    CrossWorldLinkshellList = 0x262, // updated 6.31 or 0x2a5 or 0xa7 or 0x168 or 0x1a8 or 0x238 or 0x32b or 0x133 or 0x1b4 or 0x2d4 or 0x218

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138,      // updated 5.0
    ReqMoogleMailLetter = 0xF139,    // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x233,       // updated 6.31
    MarketBoardItemListingCount = 0x3bf,   // updated 6.31
    MarketBoardItemListingHistory = 0x296, // updated 6.31
    MarketBoardItemListing = 0x155,        // updated 6.31
    MarketBoardPurchase = 0x312,           // updated 6.31
    ItemMarketBoardInfo = 0x308,           // updated 6.31

    CharaFreeCompanyTag = 0x013B,   // updated 4.5
    FreeCompanyBoardMsg = 0x03DB,   // updated 5.58 hotfix
    FreeCompanyInfo = 0x68,         // updated 6.31
    FreeCompanyDialog = 0x184,      // updated 6.31
    ExamineFreeCompanyInfo = 0x177, // updated 6.31

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x2a4,       // updated 6.31
    EurekaStatusEffectList = 0x1de, // updated 6.31
    BossStatusEffectList = 0xa6,    // updated 6.31
    StatusEffectList2 = 0x9c,       // updated 6.31
    StatusEffectList3 = 0x24d,      // updated 6.31
    Effect = 0x3c1,                 // updated 6.31
    AoeEffect8 = 0x78,              // updated 6.31
    AoeEffect16 = 0x398,            // updated 6.31
    AoeEffect24 = 0x2ea,            // updated 6.31
    AoeEffect32 = 0x210,            // updated 6.31
    PersistantEffect = 0x24d,       // updated 6.31

    GCAffiliation = 0x114, // updated 6.31

    PlayerSpawn = 0x187, // updated 6.31
    NpcSpawn = 0x391,    // updated 6.31
    NpcSpawn2 = 0x225,   // updated 6.31

    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x211,          // updated 6.31
    PartyMessage = 0x349,       // updated 6.31
    HateRank = 0x250,           // updated 6.31
    HateList = 0x359,           // updated 6.31
    ObjectSpawn = 0x11a,        // updated 6.31
    ObjectDespawn = 0xa4,       // updated 6.31
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x373,        // updated 6.31
    PlayerStats = 0x272,        // updated 6.31
    ActorOwner = 0x373,         // updated 6.31
    PlayerStateFlags = 0x1b7,   // updated 6.31
    PlayerClassInfo = 0x3a5,    // updated 6.31
    PlayerUpdateLook = 0x1ba,   // updated 6.31
    CharaVisualEffect = 0x180,  // updated 6.31

    ModelEquip = 0x212,   // updated 6.31
    Examine = 0x121,      // updated 6.31
    CharaNameReq = 0x2e7, // updated 6.31

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x37c,          // updated 6.31
    RetainerInformation = 0xb0,           // updated 6.31

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x335,                   // updated 6.31
    ContainerInfo = 0x3c3,              // updated 6.31
    InventoryTransactionFinish = 0x317, // updated 6.31
    InventoryTransaction = 0xd3,        // updated 6.31
    CurrencyCrystalInfo = 0x37b,        // updated 6.31

    InventoryActionAck = 0x34a,  // updated 6.31
    UpdateInventorySlot = 0x3e7, // updated 6.31

    HuntingLogEntry = 0x266, // updated 6.31

    EventPlay = 0x1f5,    // updated 6.31
    EventPlay4 = 0x357,   // updated 6.31
    EventPlay8 = 0x269,   // updated 6.31
    EventPlay16 = 0x278,  // updated 6.31
    EventPlay32 = 0x36b,  // updated 6.31
    EventPlay64 = 0x288,  // updated 6.31
    EventPlay128 = 0x73,  // updated 6.31
    EventPlay255 = 0x23a, // updated 6.31
    EventStart = 0x1c5,   // updated 6.31
    EventFinish = 0xb6,   // updated 6.31

    EventContinue = 0x89, // updated 6.31 or 0x2ac or 0x290 or 0x331 or 0x1db or 0x37a or 0x11b or 0x31f

    EventLinkshell = 0x1169,

    QuestActiveList = 0xf3,    // updated 6.31
    QuestUpdate = 0xa3,        // updated 6.31
    QuestCompleteList = 0x31b, // updated 6.31

    QuestFinish = 0x93,          // updated 6.31
    MSQTrackerComplete = 0x9a,   // updated 6.31
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58 hotfix

    QuestTracker = 0x379, // updated 6.31

    Mount = 0x16b, // updated 6.31

    DirectorVars = 0x126,       // updated 6.31
    SomeDirectorUnk1 = 0x0084,  // updated 5.18
    SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
    SomeDirectorUnk4 = 0x03DD,  // updated 5.58 hotfix
    SomeDirectorUnk8 = 0x028A,  // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF,     // updated 5.58 hotfix
    DirectorPopUp4 = 0x019B,    // updated 5.58 hotfix
    DirectorPopUp8 = 0x0271,    // updated 5.58 hotfix

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x163,  // updated 6.31
    PlayerTitleList = 0xe9, // updated 6.31
    Discovery = 0x3d8,      // updated 6.31

    EorzeaTimeOffset = 0x2a8, // updated 6.31

    EquipDisplayFlags = 0x1bf, // updated 6.31

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287,     // updated 5.58 hotfix
    LootMessage = 0x1ac,      // updated 6.31
    ResultDialog = 0x2ac,     // updated 6.31
    DesynthResult = 0x89,     // updated 6.31

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x336,           // updated 6.31
    LandUpdate = 0x29b,                  // updated 6.31
    YardObjectSpawn = 0x2fa,             // updated 6.31
    HousingIndoorInitialize = 0x195,     // updated 6.31
    LandPriceUpdate = 0x2ce,             // updated 6.31
    LandInfoSign = 0x122,                // updated 6.31
    LandRename = 0x36e,                  // updated 6.31
    HousingEstateGreeting = 0x29e,       // updated 6.31
    HousingUpdateLandFlagsSlot = 0x16e,  // updated 6.31
    HousingLandFlags = 0x232,            // updated 6.31
    HousingShowEstateGuestAccess = 0xaf, // updated 6.31

    HousingObjectInitialize = 0x33b,   // updated 6.31
    HousingInternalObjectSpawn = 0xb9, // updated 6.31

    HousingWardInfo = 0xdd,    // updated 6.31
    HousingObjectMove = 0x3c4, // updated 6.31
    HousingObjectDye = 0x2d8,  // updated 6.31

    SharedEstateSettingsResponse = 0x8f, // updated 6.31

    LandUpdateHouseName = 0x214, // updated 6.31
    LandSetMap = 0x2af,          // updated 6.31

    CeremonySetActorAppearance = 0x2f0, // updated 6.31

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x2ab,    // updated 6.31

    DutyGauge = 0x02E5, // updated 5.58 hotfix

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x343,          // updated 6.31
    DailyQuestRepeatFlags = 0x97, // updated 6.31

    MapUpdate = 0x191,   // updated 6.31
    MapUpdate4 = 0x1a1,  // updated 6.31
    MapUpdate8 = 0x77,   // updated 6.31
    MapUpdate16 = 0x2d0, // updated 6.31
    MapUpdate32 = 0x82,  // updated 6.31
    MapUpdate64 = 0x372, // updated 6.31
    MapUpdate128 = 0xc2, // updated 6.31

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
    AirshipTimers = 0xad,             // updated 6.31
    AirshipStatus = 0x28b,            // updated 6.31
    AirshipStatusList = 0x234,        // updated 6.31
    AirshipExplorationResult = 0x1e4, // updated 6.31

    SubmarineTimers = 0x9d,             // updated 6.31
    SubmarineProgressionStatus = 0x30c, // updated 6.31
    SubmarineStatusList = 0x283,        // updated 6.31
    SubmarineExplorationResult = 0x154, // updated 6.31

    EnvironmentControl = 0x2d9,        // updated 6.31
    IslandWorkshopSupplyDemand = 0x80, // updated 6.31

  };

  /**
   * Client IPC Zone Type Codes.
   */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x011B, // updated 6.30h
    InitHandler = 0x01F0, // updated 6.30h

    FinishLoadingHandler = 0x01E4, // updated 6.30h

    CFCommenceHandler = 0x0381, // updated 5.58 hotfix

    CFCancelHandler = 0x02B2,    // updated 5.58 hotfix
    CFRegisterDuty = 0x01BD,     // updated 5.58 hotfix
    CFRegisterRoulette = 0x037A, // updated 5.58 hotfix
    PlayTimeHandler = 0x02B7,    // updated 5.58 hotfix
    LogoutHandler = 0x01C7,      // updated 6.30h
    CancelLogout = 0x0102,       // updated 6.30h
    CFDutyInfoHandler = 0xF078,  // updated 4.2

    SocialReqSendHandler = 0x00D7,  // updated 5.58 hotfix
    SocialResponseHandler = 0x023B, // updated 5.58 hotfix
    CreateCrossWorldLS = 0x035D,    // updated 5.58 hotfix

    ChatHandler = 0x02C6, // Updated 6.30h
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x036C,  // updated 5.58 hotfix
    LeavePartyHandler = 0x019D,      // updated 5.58 hotfix
    KickPartyMemberHandler = 0x0262, // updated 5.58 hotfix
    DisbandPartyHandler = 0x0276,    // updated 5.58 hotfix

    SocialListHandler = 0x0145,              // updated 6.30h
    SetSearchInfoHandler = 0x01D4,           // updated 5.58 hotfix
    ReqSearchInfoHandler = 0x014F,           // updated 5.58 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58 hotfix
    BlackListHandler = 0x0235,             // updated 6.30h
    PlayerSearchHandler = 0x037D,          // updated 5.58 hotfix

    LinkshellListHandler = 0x03B6, // updated 5.58 hotfix

    MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58 hotfix
    MarketBoardRequestItemListings = 0x0122,    // updated 5.58 hotfix
    MarketBoardSearch = 0x0082,                 // updated 5.58 hotfix

    ReqExamineFcInfo = 0x037B, // updated 5.58 hotfix

    FcInfoReqHandler = 0x03D4, // updated 5.58 hotfix

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x00C3, // updated 5.58 hotfix

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x02EC, // updated 5.58 hotfix
    ReqCountdownCancel = 0x0068,   // updated 5.58 hotfix

    ZoneLineHandler = 0x01EC,  // updated 6.30h
    ClientTrigger = 0x0174,    // updated 6.30h
    DiscoveryHandler = 0x038B, // updated 5.58 hotfix

    PlaceFieldMarkerPreset = 0x204, // updated 6.30h
    PlaceFieldMarker = 0x38e,       // updated 6.30h
    SkillHandler = 0x0249,          // updated 6.30h
    GMCommand1 = 0x0182,            // updated 6.30h
    GMCommand2 = 0x02AD,            // updated 6.30h
    AoESkillHandler = 0x0152,       // updated 5.58 hotfix

    UpdatePositionHandler = 0x10F, // Updated 6.30h

    InventoryModifyHandler = 0x008F, // Updated 6.30h

    InventoryEquipRecommendedItems = 0x01C9, // updated 5.58 hotfix

    ReqPlaceHousingItem = 0x02D4, // updated 5.58 hotfix
    BuildPresetHandler = 0x0223,  // updated 5.58 hotfix

    TalkEventHandler = 0x0384,         // updated 6.30h
    EmoteEventHandler = 0x00B0,        // updated 5.58 hotfix
    WithinRangeEventHandler = 0x02B6,  // updated 5.58 hotfix
    OutOfRangeEventHandler = 0x03C5,   // updated 5.58 hotfix
    EnterTeriEventHandler = 0x0332,    // updated 6.30h
    ShopEventHandler = 0x0384,         // updated 5.58 hotfix
    ReturnEventHandler = 0x0383,       // updated 6.30h
    TradeReturnEventHandler = 0x0398,  // updated 6.30h
    TradeReturnEventHandler2 = 0x023C, // updated 5.58 hotfix
    EventYield2Handler = 0x021D,       // updated 5.58 hotfix
    EventYield16Handler = 0x0207,      // updated 5.58 hotfix

    LinkshellEventHandler = 0x016B,  // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x03BC, // updated 6.30h

    LandRenameHandler = 0x028E,           // updated 5.58 hotfix
    HousingUpdateHouseGreeting = 0x0343,  // updated 5.58 hotfix
    HousingUpdateObjectPosition = 0x012C, // updated 5.58 hotfix
    HousingEditExterior = 0x027B,         // updated 5.58 hotfix
    HousingEditInterior = 0x02E3,         // updated 5.58 hotfix

    SetSharedEstateSettings = 0x00D2, // updated 5.58 hotfix

    UpdatePositionInstance = 0x00DB, // Updated 6.30h

    PerformNoteHandler = 0x0243, // updated 5.58 hotfix

    WorldInteractionHandler = 0x0274, // updated 5.58 hotfix
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
