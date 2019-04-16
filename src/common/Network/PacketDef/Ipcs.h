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

    AddStatusEffect = 0x0141,
    ActorControl142 = 0x0142,
    ActorControl143 = 0x0143,
    ActorControl144 = 0x0144,
    UpdateHpMpTp = 0x0145,

    ///////////////////////////////////////////////////

    ChatBanned = 0x006B,
    Playtime = 0x006C, // updated 4.5
    Logout = 0x0077, // updated 4.5
    CFNotify = 0x0078,
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x007A,
    CFPlayerInNeed = 0x007F,

    SocialRequestError = 0x00AD,

    CFRegistered = 0x00B8, // updated 4.1
    SocialRequestResponse = 0x00BB, // updated 4.1
    CancelAllianceForming = 0x00C6, // updated 4.2

    Chat = 0x00F7, // updated 4.5?
    SocialList = 0x0103, // updated 4.5

    UpdateSearchInfo = 0x0106, // updated 4.5
    InitSearchInfo = 0x0107, // updated 4.4
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x010B, // added 4.5
    ServerNotice = 0x010C, // updated 4.5
    SetOnlineStatus = 0x010D, // updated 4.5

    CountdownInitiate = 0x0114, // updated 4.5
    CountdownCancel = 0x0115, // updated 4.5

    BlackList = 0x0118, // updated 4.5

    LogMessage = 0x00D0,

    LinkshellList = 0x011F, // updated 4.5

    MailDeleteRequest = 0x0120, // updated 4.5
    ReqMoogleMailList = 0x0121, // updated 4.5
    ReqMoogleMailLetter = 0x0122, // updated 4.5
    MailLetterNotification = 0x0123, // updated 4.5

    MarketBoardItemListingCount = 0x0125, // updated 4.5
    MarketBoardItemListing = 0x0126, // updated 4.5
    MarketBoardItemListingHistory = 0x012A, // updated 4.5
    MarketBoardSearchResult = 0x0139, // updated 4.5

    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0x013D, // updated 4.5
    ExamineFreeCompanyInfo = 0x013E, // updated 4.5

    StatusEffectList = 0x0151, // updated 4.5
    Effect = 0x0154, // updated 4.5
    AoeEffect8 = 0x0157, // updated 4.5
    AoeEffect16 = 0x0158, // updated 4.5
    AoeEffect24 = 0x0159, // updated 4.5
    AoeEffect32 = 0x015A, // updated 4.5
    PersistantEffect = 0x015B, // updated 4.5

    GCAffiliation = 0x0165, // updated 4.5

    PlayerSpawn = 0x0175, // updated 4.5
    NpcSpawn = 0x0176, // updated 4.5
    NpcSpawn2 = 0x0177, // ( Bigger statuseffectlist? ) updated 4.5
    ActorMove = 0x0178, // updated 4.5

    ActorSetPos = 0x017A, // updated 4.5

    ActorCast = 0x017C, // updated 4.5

    PartyList = 0x017E, // updated 4.5

    HateList = 0x0180, // updated 4.5
    ObjectSpawn = 0x0181, // updated 4.5
    ObjectDespawn = 0x0182, // updated 4.5
    UpdateClassInfo = 0x0183, // updated 4.5
    SilentSetClassJob = 0x0184, // updated 4.5 - seems to be the case, not sure if it's actually used for anything
    InitUI = 0x0185, // updated 4.5
    PlayerStats = 0x0186, // updated 4.5
    ActorOwner = 0x0187, // updated 4.5
    PlayerStateFlags = 0x0188, // updated 4.5
    PlayerClassInfo = 0x0189, // updated 4.5

    ModelEquip = 0x018B, // updated 4.5
    Examine = 0x018C, // updated 4.5
    CharaNameReq = 0x018D, // updated 4.5

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x0196, // updated 4.5
    ContainerInfo = 0x0197, // updated 4.5
    InventoryTransactionFinish = 0x0198, // updated 4.5
    InventoryTransaction = 0x0199, // updated 4.5

    CurrencyCrystalInfo = 0x019B, // updated 4.5

    InventoryActionAck = 0x019D, // updated 4.5
    UpdateInventorySlot = 0x019E, // updated 4.5

    HuntingLogEntry = 0x01A9, // added 4.5

    EventPlay = 0x01AB, // updated 4.5
    DirectorPlayScene = 0x01AF, // updated 4.5
    EventOpenGilShop = 0x01B2, // updated 4.5

    EventStart = 0x01B4, // updated 4.5
    EventFinish = 0x01B5, // updated 4.5

    EventLinkshell = 0x1169,

    QuestActiveList = 0x01C8, // updated 4.5
    QuestUpdate = 0x01C9, // updated 4.5
    QuestCompleteList = 0x01CA, // updated 4.5

    QuestFinish = 0x01CB, // updated 4.5
    MSQTrackerComplete = 0x01CC, // updated 4.5
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x01D3, // updated 4.5

    QuestTracker = 0x01D8, // updated 4.5

    Mount = 0x01E8, // updated 4.5

    DirectorVars = 0x01EA, // updated 4.5
    DirectorPopUp = 0x01F5, // display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x0205, // updated 4.5
    PlayerTitleList = 0x0206, // updated 4.5?
    Discovery = 0x0207, // updated 4.5?

    EorzeaTimeOffset = 0x0209, // updated 4.5

    EquipDisplayFlags = 0x0215, // updated 4.5

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0229, // updated 4.5
    LandUpdate = 0x022A, // updated 4.5
    YardObjectSpawn = 0x022B, // updated 4.5
    HousingIndoorInitialize = 0x022C, // updated 4.5
    LandPriceUpdate = 0x022D, // updated 4.5
    LandInfoSign = 0x022E, // updated 4.5
    LandRename = 0x022F, // updated 4.5
    HousingEstateGreeting = 0x0230, // updated 4.5
    HousingUpdateLandFlagsSlot = 0x0231, // updated 4.5
    HousingLandFlags = 0x0232, // updated 4.5
    HousingShowEstateGuestAccess = 0x0233, // updated 4.5

    HousingObjectInitialize = 0x0235, // updated 4.45
    HousingInternalObjectSpawn = 0x236, // updated 4.5

    HousingWardInfo = 0x0238, // updated 4.5
    HousingObjectMove = 0x0239, // updated 4.5

    SharedEstateSettingsResponse = 0x0245, // updated 4.5

    LandUpdateHouseName = 0x0257, // updated 4.5

    LandSetMap = 0x025B, // updated 4.5

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0286, // updated 4.3

    PrepareZoning = 0x0299, // updated 4.5
    ActorGauge = 0x0292, // updated 4.3

    // Unknown IPC types that still need to be sent
    // TODO: figure all these out properly
    IPCTYPE_UNK_320 = 0x0253, // updated 4.5
    IPCTYPE_UNK_322 = 0x0255, // updated 4.5

    /// Doman Mahjong //////////////////////////////////////
    MahjongOpenGui = 0x02BC, // only available in mahjong instance
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

    PingHandler = 0x0065, // unchanged 4.5
    InitHandler = 0x0066, // unchanged 4.5

    FinishLoadingHandler = 0x0069, // unchanged 4.5

    CFCommenceHandler = 0x006F,


    CFRegisterDuty = 0x0071,
    CFRegisterRoulette = 0x0072,
    PlayTimeHandler = 0x0073, // unchanged 4.5
    LogoutHandler = 0x0074, // unchanged 4.5

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x00AE, // updated 4.1
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x00D7, // updated 4.5

    SocialListHandler = 0x00DF, // updated 4.5
    ReqSearchInfoHandler = 0x00E4, // updated 4.5
    ReqExamineSearchCommentHandler = 0x00E5, // updated 4.5

    SetSearchInfoHandler = 0x00E2, // unchanged 4.5

    BlackListHandler = 0x00F0, // updated 4.5
    PlayerSearchHandler = 0x00E6, // updated 4.5

    LinkshellListHandler = 0x00F8, // updated 4.5

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

    ZoneLineHandler = 0x0137, // updated 4.5
    ClientTrigger = 0x0138, // updated 4.5
    DiscoveryHandler = 0x0139, // updated 4.5

    AddWaymark = 0x013A, // updated 4.5

    SkillHandler = 0x013B, // updated 4.5
    GMCommand1 = 0x013C, // updated 4.5
    GMCommand2 = 0x013D, // updated 4.5
    AoESkillHandler = 0x13E, // updated 4.5

    UpdatePositionHandler = 0x013F, // updated 4.5
    UpdatePositionInstance = 0x0183, // updated 4.3

    InventoryModifyHandler = 0x0146, // updated 4.5 ( +4 )

    ReqPlaceHousingItem = 0x149, // updated 4.5

    BuildPresetHandler = 0x014E, // updated 4.5
    TalkEventHandler = 0x014F, // updated 4.5
    EmoteEventHandler = 0x0150, // updated 4.5
    WithinRangeEventHandler = 0x0151, // updated 4.5
    OutOfRangeEventHandler = 0x0152, // updated 4.5
    EnterTeriEventHandler = 0x0153, // updated 4.5

    ShopEventHandler = 0x0155, // updated 4.5

    ReturnEventHandler = 0x0158, // updated 4.5
    TradeReturnEventHandler = 0x0159, // updated 4.5

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    LandRenameHandler = 0x0175, // updated 4.5
    HousingUpdateHouseGreeting = 0x0176, // updated 4.5
    HousingUpdateObjectPosition = 0x0177, // updated 4.5

    SetSharedEstateSettings = 0x017B, // updated 4.5

    PerformNoteHandler = 0x029B, // updated 4.3

    ReqEquipDisplayFlagsChange = 0x0173, // updated 4.5


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
