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

    // static opcode ( the ones that rarely, if ever, change )
    Ping = 0x0065,
    Init = 0x0066,

    ActorFreeSpawn = 0x0191,
    InitZone = 0x019A,

    EffectResult = 0x0141,
    ActorControl142 = 0x0142,
    ActorControl143 = 0x0143,
    ActorControl144 = 0x0144,
    UpdateHpMpTp = 0x0145,

    ///////////////////////////////////////////////////

    ChatBanned = 0x006B,
    Playtime = 0x0100, // updated 5.0
    Logout = 0x0077, // updated 5.0
    CFNotify = 0x0078,
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x007A,
    CFPlayerInNeed = 0x007F,

    SocialRequestError = 0x00AD,

    CFRegistered = 0x00B8, // updated 4.1
    SocialRequestResponse = 0x00BB, // updated 4.1
    CancelAllianceForming = 0x00C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x0104, // updated 5.0

    WorldVisitList = 0x00FE, // added 4.5

    SocialList = 0x010D, // updated 5.0

    ExamineSearchInfo = 0x10F, // added 5.0
    UpdateSearchInfo = 0x0110, // updated 5.0
    InitSearchInfo = 0x0111, // updated 5.0
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x0115, // updated 5.0
    ServerNotice = 0x0116, // updated 5.0
    SetOnlineStatus = 0x0117, // updated 5.0

    CountdownInitiate = 0x011E, // updated 5.0
    CountdownCancel = 0x011F, // updated 5.0

    PlayerAddedToBlacklist = 0x0120, // updated 5.0
    PlayerRemovedFromBlacklist = 0x0121, // updated 5.0
    BlackList = 0x0123, // updated 5.0

    LinkshellList = 0x012A, // updated 5.0

    MailDeleteRequest = 0x012B, // updated 5.0
    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0x0138, // updated 5.0
    ReqMoogleMailLetter = 0x0139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketBoardItemListingCount = 0x0125, // updated 4.5
    MarketBoardItemListing = 0x0126, // updated 4.5
    MarketBoardItemListingHistory = 0x012A, // updated 4.5
    MarketBoardSearchResult = 0x0139, // updated 4.5

    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0x013D, // updated 4.5
    ExamineFreeCompanyInfo = 0x013E, // updated 4.5

    StatusEffectList = 0x015B, // updated 5.0
    EurekaStatusEffectList = 0x015C, // updated 5.0
    Effect = 0x015E, // updated 5.0
    AoeEffect8 = 0x0161, // updated 5.0
    AoeEffect16 = 0x0162, // updated 5.0
    AoeEffect24 = 0x0163, // updated 5.0
    AoeEffect32 = 0x0164, // updated 5.0
    PersistantEffect = 0x0165, // updated 5.0

    GCAffiliation = 0x016F, // updated 5.0

    PlayerSpawn = 0x017F, // updated 5.0
    NpcSpawn = 0x0180, // updated 5.0
    NpcSpawn2 = 0x0181, // ( Bigger statuseffectlist? ) updated 5.0
    ActorMove = 0x0182, // updated 5.0

    ActorSetPos = 0x0184, // updated 5.0

    ActorCast = 0x0187, // updated 5.0

    PartyList = 0x0188, // updated 5.0
    HateRank = 0x0189, // updated 5.0
    HateList = 0x018A, // updated 5.0
    ObjectSpawn = 0x018B, // updated 5.0
    ObjectDespawn = 0x018C, // updated 5.0
    UpdateClassInfo = 0x018D, // updated 5.0
    SilentSetClassJob = 0x018E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x018F, // updated 5.0
    PlayerStats = 0x0190, // updated 5.0
    ActorOwner = 0x0192, // updated 5.0
    PlayerStateFlags = 0x0193, // updated 5.0
    PlayerClassInfo = 0x0194, // updated 5.0

    ModelEquip = 0x0196, // updated 5.0
    Examine = 0x0197, // updated 5.0
    CharaNameReq = 0x0198, // updated 5.0

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0x019F, // updated 5.0

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x01A1, // updated 5.0
    ContainerInfo = 0x01A2, // updated 5.0
    InventoryTransactionFinish = 0x01A3, // updated 5.0
    InventoryTransaction = 0x01A4, // updated 5.0

    CurrencyCrystalInfo = 0x01A5, // updated 5.0

    InventoryActionAck = 0x01A7, // updated 5.0
    UpdateInventorySlot = 0x01A8, // updated 5.0

    HuntingLogEntry = 0x01B3, // updated 5.0

    EventPlay = 0x01B5, // updated 5.0
    DirectorPlayScene = 0x01B9, // updated 5.0
    EventOpenGilShop = 0x01BC, // updated 5.0

    EventStart = 0x01BE, // updated 5.0
    EventFinish = 0x01BF, // updated 5.0

    EventLinkshell = 0x1169,

    QuestActiveList = 0x01D2, // updated 5.0
    QuestUpdate = 0x01D3, // updated 5.0
    QuestCompleteList = 0x01D4, // updated 5.0

    QuestFinish = 0x01D5, // updated 5.0
    MSQTrackerComplete = 0x01D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x01DE, // updated 5.0

    QuestTracker = 0x01E3, // updated 5.0

    Mount = 0x01F3, // updated 5.0

    DirectorVars = 0x01F5, // updated 5.0
    DirectorPopUp = 0x0200, // updated 5.0 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x0210, // updated 5.0
    PlayerTitleList = 0x0211, // updated 5.0
    Discovery = 0x0212, // updated 5.0

    EorzeaTimeOffset = 0x0214, // updated 5.0

    EquipDisplayFlags = 0x0220, // updated 5.0

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0234, // updated 5.0
    LandUpdate = 0x0235, // updated 5.0
    YardObjectSpawn = 0x0236, // updated 5.0
    HousingIndoorInitialize = 0x0237, // updated 5.0
    LandPriceUpdate = 0x0238, // updated 5.0
    LandInfoSign = 0x0239, // updated 5.0
    LandRename = 0x023A, // updated 5.0
    HousingEstateGreeting = 0x023B, // updated 5.0
    HousingUpdateLandFlagsSlot = 0x023C, // updated 5.0
    HousingLandFlags = 0x023D, // updated 5.0
    HousingShowEstateGuestAccess = 0x023E, // updated 5.0

    HousingObjectInitialize = 0x0240, // updated 5.0
    HousingInternalObjectSpawn = 0x241, // updated 5.0

    HousingWardInfo = 0x0243, // updated 5.0
    HousingObjectMove = 0x0244, // updated 5.0

    SharedEstateSettingsResponse = 0x0245, // updated 4.5

    LandUpdateHouseName = 0x0257, // updated 4.5

    LandSetMap = 0x025B, // updated 4.5

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0286, // updated 4.3

    PrepareZoning = 0x02A4, // updated 5.0
    ActorGauge = 0x0292, // updated 4.3

    // Unknown IPC types that still need to be sent
    // TODO: figure all these out properly
    // daily quest related, init seed and current quota probably
    IPCTYPE_UNK_320 = 0x025E, // updated 5.0
    IPCTYPE_UNK_322 = 0x0260, // updated 5.0

    /// Doman Mahjong //////////////////////////////////////
    MahjongOpenGui = 0x02A4, // only available in mahjong instance
    MahjongNextRound = 0x02BD, // initial hands(baipai), # of riichi(wat), winds, honba, score and stuff
    MahjongPlayerAction = 0x02BE, // tsumo(as in drawing a tile) called chi/pon/kan/riichi
    MahjongEndRoundTsumo = 0x02BF, // called tsumo
    MahjongEndRoundRon = 0x2C0, // called ron or double ron (waiting for action must be flagged from discard packet to call)
    MahjongTileDiscard = 0x02C1, // giri (discarding a tile.) chi(1)/pon(2)/kan(4)/ron(8) flags etc..
    MahjongPlayersInfo = 0x02C2, // actor id, name, rating and stuff..
    // 2C3 and 2C4 are currently unknown
    MahjongEndRoundDraw = 0x02C5, // self explanatory
    MahjongEndGame = 0x02C6, // finished oorasu(all-last) round; shows a result screen.
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {

    PingHandler = 0x0065, // unchanged 5.0
    InitHandler = 0x0066, // unchanged 5.0

    FinishLoadingHandler = 0x0069, // unchanged 5.0

    CFCommenceHandler = 0x006F,


    CFRegisterDuty = 0x0071,
    CFRegisterRoulette = 0x0072,
    PlayTimeHandler = 0x0073, // unchanged 5.0
    LogoutHandler = 0x0074, // unchanged 5.0
    CancelLogout = 0x0075, // updated 5.0

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x00AE, // updated 4.1
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x00D9, // updated 5.0

    SocialListHandler = 0x00E1, // updated 5.0
    SetSearchInfoHandler = 0x00E4, // updated 5.0
    ReqSearchInfoHandler = 0x00E6, // updated 5.0
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x00F2, // updated 5.0
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x00FA, // updated 5.0

    MarketBoardRequestItemListingInfo = 0x0102, // updated 4.5
    MarketBoardRequestItemListings = 0x0103, // updated 4.5
    MarketBoardSearch = 0x0107, // updated 4.5

    ReqExamineFcInfo = 0x0113, // updated 4.1

    FcInfoReqHandler = 0x011A, // updated 4.2

    ReqMarketWishList = 0x012C, // updated 4.3

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x0133, // updated 4.5
    ReqCountdownCancel = 0x0134, // updated 4.5
    ClearWaymarks = 0x0135, // updated 4.5

    ZoneLineHandler = 0x0139, // updated 5.0
    ClientTrigger = 0x013A, // updated 5.0
    DiscoveryHandler = 0x013B, // updated 5.0

    AddWaymark = 0x013A, // updated 4.5

    SkillHandler = 0x013D, // updated 5.0
    GMCommand1 = 0x013E, // updated 5.0
    GMCommand2 = 0x013F, // updated 5.0
    AoESkillHandler = 0x140, // updated 5.0

    UpdatePositionHandler = 0x0141, // updated 5.0

    InventoryModifyHandler = 0x0148, // updated 5.0

    ReqPlaceHousingItem = 0x014B, // updated 5.0
    BuildPresetHandler = 0x014F, // updated 5.0

    TalkEventHandler = 0x0151, // updated 5.0
    EmoteEventHandler = 0x0152, // updated 5.0
    WithinRangeEventHandler = 0x0153, // updated 5.0
    OutOfRangeEventHandler = 0x0154, // updated 5.0
    EnterTeriEventHandler = 0x0155, // updated 5.0
    ShopEventHandler = 0x0156, // updated 5.0

    ReturnEventHandler = 0x015A, // updated 5.0?
    TradeReturnEventHandler = 0x015B, // updated 5.0?

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x0175, // updated 5.0

    LandRenameHandler = 0x0177, // updated 5.0
    HousingUpdateHouseGreeting = 0x0178, // updated 5.0
    HousingUpdateObjectPosition = 0x0179, // updated 5.0

    SetSharedEstateSettings = 0x017B, // updated 5.0

    UpdatePositionInstance = 0x0180, // updated 5.0

    PerformNoteHandler = 0x029B, // updated 4.3



  };

  ////////////////////////////////////////////////////////////////////////////////
  /// Chat Connection IPC Codes
  /**
  * Server IPC Chat Type Codes.
  */
  enum ServerChatIpcType : uint16_t
  {
    Tell = 0x0064, // updated for sb
    TellErrNotFound = 0x0066,
  };

  /**
  * Client IPC Chat Type Codes.
  */
  enum ClientChatIpcType : uint16_t
  {
    TellReq = 0x0064,
  };


}

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
