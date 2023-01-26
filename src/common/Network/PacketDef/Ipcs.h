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
    Ping = 0x00DA, // updated 6.30h
    Init = 0x01E4, // updated 6.30h

    ActorFreeSpawn = 0x28a, // updated 6.30h
    InitZone = 0x222, // updated 6.30h

    EffectResult = 0x22c, // updated 6.30h
    EffectResultBasic = 0x384, // updated 6.30h
    
    ActorControl = 0x179, // updated 6.30h
    ActorControlSelf = 0x26f, // updated 6.30h
    ActorControlTarget = 0x220, // updated 6.30h

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x383, // updated 6.30h

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x326, // updated 6.30h
    Logout = 0x1d0, // updated 6.30h
    CFNotify = 0x38b, // updated 6.30h
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x1f8, // updated 6.30h
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0xde, // updated 6.30h
    CFCancel = 0x102, // updated 6.30h
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x029F, // updated 5.58 hotfix
    SocialRequestResponse = 0x95, // updated 6.30h
    SocialMessage = 0x03CB, // updated 5.58 hotfix
    SocialMessage2 = 0x01D7, // updated 5.58 hotfix
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x343, // updated 6.30h

    Chat = 0x10a, // updated 6.30h
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x01f1, // updated 6.30h

    ExamineSearchInfo = 0x30e, // updated 6.30h
    UpdateSearchInfo = 0x34a, // updated 6.30h
    InitSearchInfo = 0x0321, // updated 5.58 hotfix
    ExamineSearchComment = 0x30c, // updated 6.30h

    ServerNoticeShort = 0x0333, // updated 5.58 hotfix
    ServerNotice = 0x0363, // updated 5.58 hotfix
    SetOnlineStatus = 0x324, // updated 6.30h

    CountdownInitiate = 0x3b1, // updated 6.30h
    CountdownCancel = 0xb6, // updated 6.30h

    PlayerAddedToBlacklist = 0x399, // updated 6.30h
    PlayerRemovedFromBlacklist = 0x1dc, // updated 6.30h
    BlackList = 0x016B, // updated 6.30h

    LinkshellList = 0x1e2, // updated 6.30h

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x21e, // updated 6.30h
    MarketBoardItemListingCount = 0xaa, // updated 6.30h
    MarketBoardItemListingHistory = 0xa8, // updated 6.30h
    MarketBoardItemListing = 0x2f1, // updated 6.30h

    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x03DB, // updated 5.58 hotfix
    FreeCompanyInfo = 0x1dd, // updated 5.58 hotfix
    ExamineFreeCompanyInfo = 0xcd, // updated 5.58 hotfix

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x2bc, // updated 6.30h
    EurekaStatusEffectList = 0x353, // updated 6.30h
    BossStatusEffectList = 0x1ee, // updated 6.30h
    Effect = 0x1c9, // updated 6.30h
    AoeEffect8 = 0x24a, // updated 6.30h
    AoeEffect16 = 0x38a, // updated 6.30h
    AoeEffect24 = 0xc8, // updated 6.30h
    AoeEffect32 = 0x32b, // updated 6.30h
    PersistantEffect = 0x24c, // updated 6.30h

    GCAffiliation = 0x372, // updated 6.30h

    PlayerSpawn = 0x007f, // updated 6.30h
    NpcSpawn = 0x39e, // updated 6.30h
    NpcSpawn2 = 0x2e5, // updated 6.30h
    ActorMove = 0x1db, // updated 6.30h

    ActorSetPos = 0x18c, // updated 6.30h

    ActorCast = 0x29c, // updated 6.30h
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x1f6, // updated 6.30h
    PartyMessage = 0x1e8, // updated 6.30h
    HateRank = 0x134, // updated 6.30h
    HateList = 0x2f9, // updated 6.30h
    ObjectSpawn = 0x31b, // updated 6.30h
    ObjectDespawn = 0x1b3, // updated 6.30h
    UpdateClassInfo = 0x2d9, // updated 6.30h
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x2b3, // updated 6.30h
    PlayerStats = 0x1b8, // updated 6.30h
    ActorOwner = 0x2b3, // updated 6.30h
    PlayerStateFlags = 0xd5, // updated 6.30h
    PlayerClassInfo = 0x2a6, // updated 6.30h
    CharaVisualEffect = 0x1e9, // updated 6.30h

    ModelEquip = 0x286, // updated 6.30h
    Examine = 0x1BC, // updated 6.30h
    CharaNameReq = 0x35c, // updated 6.30h

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x14a, // updated 6.30h
    RetainerInformation = 0x39c, // Updated 6.30h

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x302, // updated 6.30h
    ContainerInfo = 0x255, // updated 6.30h
    InventoryTransactionFinish = 0x1be, // updated 6.30h
    InventoryTransaction = 0x77, // updated 6.30h
    CurrencyCrystalInfo = 0x2bb, // updated 6.30h

    InventoryActionAck = 0x1eb, // updated 6.30h
    UpdateInventorySlot = 0x10e, // updated 6.30h

    HuntingLogEntry = 0x2ca, // updated 6.30h

    EventPlay = 0x2de, // updated 6.30h
    EventPlay4 = 0x317, // updated 6.30h
    EventPlay8 = 0x1cd, // updated 6.30h
    EventPlay16 = 0x1fe, // updated 6.30h
    EventPlay32 = 0x2fc, // updated 6.30h
    EventPlay64 = 0x7c, // updated 6.30h
    EventPlay128 = 0x337, // updated 6.30h
    EventPlay255 = 0x1d2, // updated 6.30h

    EventContinue = 0x240, // updated 6.30h or 0x3a2 or 0x3c3 or 0x270 or 0x391 or 0x159 or 0x2da or 0x3bb

    EventStart = 0x1a1, // updated 6.30h
    EventFinish = 0x194, // updated 6.30h

    EventLinkshell = 0x1169,

    QuestActiveList = 0x140, // updated 6.30h
    QuestUpdate = 0x382, // updated 6.30h
    QuestCompleteList = 0x39a, // updated 6.30h

    QuestFinish = 0x237, // updated 6.30h
    MSQTrackerComplete = 0xf0, // updated 6.30h
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58 hotfix

    QuestTracker = 0x2d5, // updated 6.30h

    Mount = 0x322, // updated 6.30h

    DirectorVars = 0x27b, // updated 6.30h
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x03DD, // updated 5.58 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF, // updated 5.58 hotfix
    DirectorPopUp4 = 0x019B, // updated 5.58 hotfix
    DirectorPopUp8 = 0x0271, // updated 5.58 hotfix

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0xc7, // updated 6.30h
    PlayerTitleList = 0x1ab, // updated 6.30h
    Discovery = 0x3ca, // updated 6.30h

    EorzeaTimeOffset = 0x96, // updated 6.30h

    EquipDisplayFlags = 0x303, // updated 6.30h

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287, // updated 5.58 hotfix
    LootMessage = 0x2c0, // updated 6.30h
    ResultDialog = 0x3bb, // updated 6.30h
    DesynthResult = 0x270, // updated 6.30h

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x1fc, // updated 6.30h
    LandUpdate = 0x30d, // updated 6.30h
    YardObjectSpawn = 0x30b, // updated 6.30h
    HousingIndoorInitialize = 0xa3, // updated 6.30h
    LandPriceUpdate = 0x3d2, // updated 6.30h
    LandInfoSign = 0xf9, // updated 6.30h
    LandRename = 0x16d, // updated 6.30h
    HousingEstateGreeting = 0x193, // updated 6.30h
    HousingUpdateLandFlagsSlot = 0x1ff, // updated 6.30h
    HousingLandFlags = 0x1f7, // updated 6.30h
    HousingShowEstateGuestAccess = 0x71, // updated 6.30h

    HousingObjectInitialize = 0x11d, // updated 6.30h
    HousingInternalObjectSpawn = 0x378, // updated 6.30h

    HousingWardInfo = 0xe4, // updated 6.30h
    HousingObjectMove = 0x2b9, // updated 6.30h

    SharedEstateSettingsResponse = 0x144, // updated 6.30h

    LandUpdateHouseName = 0x22b, // updated 6.30h

    LandSetMap = 0xbc, // updated 6.30h

    CeremonySetActorAppearance = 0xba, // updated 6.30h

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0xe9, // updated 6.30h

    PrepareZoning = 0x195, // updated 6.30h
    ActorGauge = 0x171, // updated 6.30h
    DutyGauge = 0x02E5, // updated 5.58 hotfix

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x17e, // updated 6.30h
    DailyQuestRepeatFlags = 0x3cc, // updated 6.30h

    MapUpdate = 0x1b7, // updated 6.30h
    MapUpdate4 = 0x1c4, // updated 6.30h
    MapUpdate8 = 0x35e, // updated 6.30h
    MapUpdate16 = 0x293, // updated 6.30h
    MapUpdate32 = 0x67, // updated 6.30h
    MapUpdate64 = 0x1ad, // updated 6.30h
    MapUpdate128 = 0x323, // updated 6.30h

    /// Doman Mahjong //////////////////////////////////////
    MahjongOpenGui = 0x02A4, // only available in mahjong instance
    MahjongNextRound = 0x02BD, // initial hands(baipai), # of riichi(wat), winds, honba, score and stuff
    MahjongPlayerAction = 0x02BE, // tsumo(as in drawing a tile) called chi/pon/kan/riichi
    MahjongEndRoundTsumo = 0x02BF, // called tsumo
    MahjongEndRoundRon = 0x2C0, // called ron or double ron (waiting for action must be flagged from discard packet to call)
    MahjongTileDiscard = 0x02C1, // giri (discarding a tile.) chi(1)/pon(2)/kan(4)/ron(8) flags etc..
    MahjongPlayersInfo = 0xF2C2, // actor id, name, rating and stuff..
    // 2C3 and 2C4 are currently unknown
    MahjongEndRoundDraw = 0x02C5, // self explanatory
    MahjongEndGame = 0x02C6, // finished oorasu(all-last) round; shows a result screen.

    /// Airship & Submarine //////////////////////////////////////
    AirshipExplorationResult = 0x34f, // updated 6.30h
    AirshipStatus = 0x142, // updated 6.30h
    AirshipStatusList = 0x70, // updated 6.30h
    AirshipTimers = 0x26b, // updated 6.30h
    SubmarineExplorationResult = 0x1a8, // updated 6.30h
    SubmarineProgressionStatus = 0x148, // updated 6.30h
    SubmarineStatusList = 0x232, // updated 6.30h
    SubmarineTimers = 0x103, // updated 6.30h
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

    CFCancelHandler = 0x02B2, // updated 5.58 hotfix
    CFRegisterDuty = 0x01BD, // updated 5.58 hotfix
    CFRegisterRoulette = 0x037A, // updated 5.58 hotfix
    PlayTimeHandler = 0x02B7, // updated 5.58 hotfix
    LogoutHandler = 0x01C7, // updated 6.30h
    CancelLogout = 0x0102, // updated 6.30h
    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialReqSendHandler = 0x00D7, // updated 5.58 hotfix
    SocialResponseHandler = 0x023B, // updated 5.58 hotfix
    CreateCrossWorldLS = 0x035D, // updated 5.58 hotfix

    ChatHandler = 0x02C6, // Updated 6.30h
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x036C, // updated 5.58 hotfix
    LeavePartyHandler = 0x019D, // updated 5.58 hotfix
    KickPartyMemberHandler = 0x0262, // updated 5.58 hotfix
    DisbandPartyHandler = 0x0276, // updated 5.58 hotfix

    SocialListHandler = 0x0145, // updated 6.30h
    SetSearchInfoHandler = 0x01D4, // updated 5.58 hotfix
    ReqSearchInfoHandler = 0x014F, // updated 5.58 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58 hotfix
    BlackListHandler = 0x0235, // updated 6.30h
    PlayerSearchHandler = 0x037D, // updated 5.58 hotfix

    LinkshellListHandler = 0x03B6, // updated 5.58 hotfix

    MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58 hotfix
    MarketBoardRequestItemListings = 0x0122, // updated 5.58 hotfix
    MarketBoardSearch = 0x0082, // updated 5.58 hotfix

    ReqExamineFcInfo = 0x037B, // updated 5.58 hotfix

    FcInfoReqHandler = 0x03D4, // updated 5.58 hotfix

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x00C3, // updated 5.58 hotfix

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x02EC, // updated 5.58 hotfix
    ReqCountdownCancel = 0x0068, // updated 5.58 hotfix

    ZoneLineHandler = 0x01EC, // updated 6.30h
    ClientTrigger = 0x0174, // updated 6.30h
    DiscoveryHandler = 0x038B, // updated 5.58 hotfix

    PlaceFieldMarkerPreset = 0x204, // updated 6.30h
    PlaceFieldMarker = 0x38e, // updated 6.30h
    SkillHandler = 0x0249, // updated 6.30h 
    GMCommand1 = 0x0182, // updated 6.30h
    GMCommand2 = 0x02AD, // updated 6.30h
    AoESkillHandler = 0x0152, // updated 5.58 hotfix

    UpdatePositionHandler = 0x10F, // Updated 6.30h

    InventoryModifyHandler = 0x008F, // Updated 6.30h

    InventoryEquipRecommendedItems = 0x01C9, // updated 5.58 hotfix

    ReqPlaceHousingItem = 0x02D4, // updated 5.58 hotfix
    BuildPresetHandler = 0x0223, // updated 5.58 hotfix

    TalkEventHandler = 0x0384, // updated 6.30h
    EmoteEventHandler = 0x00B0, // updated 5.58 hotfix
    WithinRangeEventHandler = 0x02B6, // updated 5.58 hotfix
    OutOfRangeEventHandler = 0x03C5, // updated 5.58 hotfix
    EnterTeriEventHandler = 0x0332, // updated 6.30h
    ShopEventHandler = 0x0384, // updated 5.58 hotfix
    ReturnEventHandler = 0x0383, // updated 6.30h
    TradeReturnEventHandler = 0x0398, // updated 6.30h
    TradeReturnEventHandler2 = 0x023C, // updated 5.58 hotfix
    EventYield2Handler = 0x021D, // updated 5.58 hotfix
    EventYield16Handler = 0x0207, // updated 5.58 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x03BC, // updated 6.30h

    LandRenameHandler = 0x028E, // updated 5.58 hotfix
    HousingUpdateHouseGreeting = 0x0343, // updated 5.58 hotfix
    HousingUpdateObjectPosition = 0x012C, // updated 5.58 hotfix
    HousingEditExterior = 0x027B, // updated 5.58 hotfix
    HousingEditInterior = 0x02E3, // updated 5.58 hotfix

    SetSharedEstateSettings = 0x00D2, // updated 5.58 hotfix

    UpdatePositionInstance = 0x00DB, // Updated 6.30h

    PerformNoteHandler = 0x0243, // updated 5.58 hotfix

    WorldInteractionHandler = 0x0274, // updated 5.58 hotfix
    Dive = 0x018C, // updated 6.30h
  };

  ////////////////////////////////////////////////////////////////////////////////
  /// Chat Connection IPC Codes
  /**
  * Server IPC Chat Type Codes.
  */
  enum ServerChatIpcType : uint16_t
  {
    Tell = 0x0064, // updated for sb
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
