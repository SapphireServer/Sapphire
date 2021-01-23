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
    Ping = 0x0219, // updated 5.35 hotfix
    Init = 0x0185, // updated 5.35 hotfix

    ActorFreeSpawn = 0x0239, // updated 5.35 hotfix
    InitZone = 0x03CD, // updated 5.35 hotfix

    EffectResult = 0x01C2, // updated 5.35 hotfix
    ActorControl = 0x02A4, // updated 5.35 hotfix
    ActorControlSelf = 0x02C8, // updated 5.35 hotfix
    ActorControlTarget = 0x0209, // updated 5.35 hotfix

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x0319, // updated 5.35 hotfix

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x03A4, // updated 5.35 hotfix
    Logout = 0x02AD, // updated 5.35 hotfix
    CFNotify = 0x02C4, // updated 5.35 hotfix
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x0193, // updated 5.35 hotfix
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x0196, // updated 5.35 hotfix
    CFCancel = 0x00EC, // updated 5.35 hotfix
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x010C, // updated 5.35 hotfix
    SocialRequestResponse = 0x01C7, // updated 5.35 hotfix
    SocialMessage = 0x0308, // updated 5.35 hotfix
    SocialMessage2 = 0x037C, // updated 5.35 hotfix
    CancelAllianceForming = 0x00C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x0349, // updated 5.35 hotfix
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x0216, // updated 5.35 hotfix

    ExamineSearchInfo = 0x03C3, // updated 5.35 hotfix
    UpdateSearchInfo = 0x0121, // updated 5.35 hotfix
    InitSearchInfo = 0x036F, // updated 5.35 hotfix
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x017A, // updated 5.35 hotfix
    ServerNotice = 0x02F8, // updated 5.35 hotfix
    SetOnlineStatus = 0x03D7, // updated 5.35 hotfix

    CountdownInitiate = 0x0237, // updated 5.25
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x02DB, // updated 5.35 hotfix

    LinkshellList = 0x01F0, // updated 5.35 hotfix

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x032C, // updated 5.35 hotfix
    MarketBoardItemListingCount = 0x038F, // updated 5.35 hotfix
    MarketBoardItemListingHistory = 0x0186, // updated 5.35 hotfix
    MarketBoardItemListing = 0x025F, // updated 5.35 hotfix
    
    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0xF13D, // updated 4.5
    ExamineFreeCompanyInfo = 0xF13E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x0382, // updated 5.35 hotfix
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x0192, // updated 5.35 hotfix
    AoeEffect8 = 0x012C, // updated 5.35 hotfix
    AoeEffect16 = 0x01B9, // updated 5.35 hotfix
    AoeEffect24 = 0x02B4, // updated 5.35 hotfix
    AoeEffect32 = 0x00A4, // updated 5.35 hotfix
    PersistantEffect = 0x0317, // updated 5.35 hotfix

    GCAffiliation = 0x0105, // updated 5.35 hotfix

    PlayerSpawn = 0x0179, // updated 5.35 hotfix
    NpcSpawn = 0x03A8, // updated 5.35 hotfix
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x01BF, // updated 5.35 hotfix

    ActorSetPos = 0x03DF, // updated 5.35 hotfix

    ActorCast = 0x0302, // updated 5.35 hotfix
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x02B2, // updated 5.35 hotfix
    PartyMessage = 0x00AE, // updated 5.35 hotfix
    HateRank = 0x02CC, // updated 5.35 hotfix
    HateList = 0x0198, // updated 5.35 hotfix
    ObjectSpawn = 0x02B8, // updated 5.35 hotfix
    ObjectDespawn = 0x00C0, // updated 5.35 hotfix
    UpdateClassInfo = 0x0235, // updated 5.35 hotfix
    SilentSetClassJob = 0x018E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0290, // updated 5.35 hotfix
    PlayerStats = 0x023B, // updated 5.35 hotfix
    ActorOwner = 0x00E8, // updated 5.35 hotfix
    PlayerStateFlags = 0x00F8, // updated 5.35 hotfix
    PlayerClassInfo = 0x02C3, // updated 5.35 hotfix
    CharaVisualEffect = 0x02E2, // updated 5.35 hotfix

    ModelEquip = 0x0277, // updated 5.35 hotfix
    Examine = 0x00BC, // updated 5.35 hotfix
    CharaNameReq = 0x008E, // updated 5.35 hotfix

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x020E, // updated 5.21 hotfix
    RetainerInformation = 0x01F9, // updated 5.35 hotfix

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x0214, // updated 5.35 hotfix
    ContainerInfo = 0x00C5, // updated 5.35 hotfix
    InventoryTransactionFinish = 0x02F0, // updated 5.35 hotfix
    InventoryTransaction = 0x01FD, // updated 5.35 hotfix
    CurrencyCrystalInfo = 0x0379, // updated 5.35 hotfix

    InventoryActionAck = 0x03E4, // updated 5.35 hotfix
    UpdateInventorySlot = 0x036A, // updated 5.35 hotfix

    HuntingLogEntry = 0x0146, // updated 5.35 hotfix

    EventPlay = 0x00F3, // updated 5.35 hotfix
    EventPlay4 = 0x00AC, // updated 5.35 hotfix
    EventPlay8 = 0x023F, // updated 5.35 hotfix
    EventPlay16 = 0x025B, // updated 5.35 hotfix
    EventPlay32 = 0x029A, // updated 5.35 hotfix
    EventPlay64 = 0x02C1, // updated 5.35 hotfix
    EventPlay128 = 0x038A, // updated 5.35 hotfix
    EventPlay255 = 0x034B, // updated 5.35 hotfix

    EventStart = 0x009A, // updated 5.35 hotfix
    EventFinish = 0x007E, // updated 5.35 hotfix

    EventLinkshell = 0x1169,

    QuestActiveList = 0x0117, // updated 5.35 hotfix
    QuestUpdate = 0x0073, // updated 5.35 hotfix
    QuestCompleteList = 0x0240, // updated 5.35 hotfix

    QuestFinish = 0x00E9, // updated 5.35 hotfix
    MSQTrackerComplete = 0xF1D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0381, // updated 5.35 hotfix

    QuestTracker = 0x018B, // updated 5.35 hotfix

    Mount = 0x01B5, // updated 5.35 hotfix

    DirectorVars = 0x011D, // updated 5.35 hotfix
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x0202, // updated 5.35 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0xF162, // updated 5.18 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x027B, // updated 5.35 hotfix
    PlayerTitleList = 0x0251, // updated 5.35 hotfix
    Discovery = 0x031B, // updated 5.35 hotfix

    EorzeaTimeOffset = 0x01D4, // updated 5.35 hotfix

    EquipDisplayFlags = 0x00BE, // updated 5.35 hotfix

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0197, // updated 5.35 hotfix
    LootMessage = 0x01B7, // updated 5.35 hotfix

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0095, // updated 5.35 hotfix
    LandUpdate = 0x00BF, // updated 5.35 hotfix
    YardObjectSpawn = 0x01CA, // updated 5.35 hotfix
    HousingIndoorInitialize = 0x01FF, // updated 5.35 hotfix
    LandPriceUpdate = 0x0380, // updated 5.35 hotfix
    LandInfoSign = 0x023D, // updated 5.35 hotfix
    LandRename = 0x0140, // updated 5.35 hotfix
    HousingEstateGreeting = 0x00C7, // updated 5.35 hotfix
    HousingUpdateLandFlagsSlot = 0x027E, // updated 5.35 hotfix
    HousingLandFlags = 0x022F, // updated 5.35 hotfix
    HousingShowEstateGuestAccess = 0x03B5, // updated 5.35 hotfix

    HousingObjectInitialize = 0x01AA, // updated 5.35 hotfix
    HousingInternalObjectSpawn = 0x0234, // updated 5.35 hotfix

    HousingWardInfo = 0x02FD, // updated 5.35 hotfix
    HousingObjectMove = 0x022C, // updated 5.35 hotfix

    SharedEstateSettingsResponse = 0x006A, // updated 5.35 hotfix

    LandUpdateHouseName = 0x00B1, // updated 5.35 hotfix

    LandSetMap = 0x0149, // updated 5.35 hotfix

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0286, // updated 4.3

    PrepareZoning = 0x026C, // updated 5.35 hotfix
    ActorGauge = 0x0112, // updated 5.35 hotfix

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0139, // updated 5.35 hotfix
    DailyQuestRepeatFlags = 0x024C, // updated 5.35 hotfix

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
    PingHandler = 0x0219, // updated 5.35 hotfix
    InitHandler = 0x0185, // updated 5.35 hotfix

    FinishLoadingHandler = 0x01BE, // updated 5.35 hotfix

    CFCommenceHandler = 0x0118, // updated 5.35 hotfix

    CFCancelHandler = 0x0332, // updated 5.35 hotfix
    CFRegisterDuty = 0x0289, // updated 5.35 hotfix
    CFRegisterRoulette = 0x0088, // updated 5.35 hotfix
    PlayTimeHandler = 0x02A8, // updated 5.35 hotfix
    LogoutHandler = 0x00EC, // updated 5.35 hotfix
    CancelLogout = 0x03DB, // updated 5.35 hotfix

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x0387, // updated 5.35 hotfix
    SocialResponseHandler = 0x028D, // updated 5.35 hotfix
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x0131, // updated 5.35 hotfix
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x0208, // updated 5.35 hotfix
    LeavePartyHandler = 0x0337, // updated 5.35 hotfix
    KickPartyMemberHandler = 0x014C, // updated 5.35 hotfix
    DisbandPartyHandler = 0x0205, // updated 5.35 hotfix

    SocialListHandler = 0x0340, // updated 5.35 hotfix
    SetSearchInfoHandler = 0x0314, // updated 5.35 hotfix
    ReqSearchInfoHandler = 0x01E9, // updated 5.35 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x0079, // updated 5.35 hotfix
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x024B, // updated 5.35 hotfix

    MarketBoardRequestItemListingInfo = 0x0102, // updated 4.5
    MarketBoardRequestItemListings = 0x0103, // updated 4.5
    MarketBoardSearch = 0x0107, // updated 4.5

    ReqExamineFcInfo = 0x0113, // updated 4.1

    FcInfoReqHandler = 0x011A, // updated 4.2

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x012C, // updated 4.3

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x025F, // updated 5.35 hotfix
    ReqCountdownCancel = 0x0244, // updated 5.25

    ZoneLineHandler = 0x0279, // updated 5.35 hotfix
    ClientTrigger = 0x03D3, // updated 5.35 hotfix
    DiscoveryHandler = 0x00E3, // updated 5.35 hotfix

    PlaceFieldMarkerPreset = 0x023F, // updated 5.25
    PlaceFieldMarker = 0x01BA, // updated 5.25
    SkillHandler = 0x01CD, // updated 5.35 hotfix
    GMCommand1 = 0x02AC, // updated 5.35 hotfix
    GMCommand2 = 0x029F, // updated 5.35 hotfix
    AoESkillHandler = 0x030C, // updated 5.35 hotfix

    UpdatePositionHandler = 0x0236, // updated 5.35 hotfix

    InventoryModifyHandler = 0x0135, // updated 5.35 hotfix
    
    InventoryEquipRecommendedItems = 0x0116, // updated 5.35 hotfix

    ReqPlaceHousingItem = 0x02AE, // updated 5.35 hotfix
    BuildPresetHandler = 0x01C2, // updated 5.35 hotfix

    TalkEventHandler = 0x02A4, // updated 5.35 hotfix
    EmoteEventHandler = 0x02C8, // updated 5.35 hotfix
    WithinRangeEventHandler = 0x0209, // updated 5.35 hotfix
    OutOfRangeEventHandler = 0x0319, // updated 5.35 hotfix
    EnterTeriEventHandler = 0x0192, // updated 5.35 hotfix
    ShopEventHandler = 0x01F6, // updated 5.35 hotfix

    ReturnEventHandler = 0x02B4, // updated 5.35 hotfix
    TradeReturnEventHandler = 0x00A4, // updated 5.35 hotfix
    TradeMultipleReturnEventHander = 0x035C, // updated 5.35 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x02F6, // updated 5.35 hotfix

    LandRenameHandler = 0x0155, // updated 5.35 hotfix
    HousingUpdateHouseGreeting = 0x02EA, // updated 5.35 hotfix
    HousingUpdateObjectPosition = 0x00D5, // updated 5.35 hotfix

    SetSharedEstateSettings = 0x017B, // updated 5.0

    UpdatePositionInstance = 0x0345, // updated 5.35 hotfix

    PerformNoteHandler = 0x029B, // updated 4.3

    WorldInteractionHandler = 0x00A9, // updated 5.35 hotfix
    Dive = 0x02CC, // updated 5.35 hotfix
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
