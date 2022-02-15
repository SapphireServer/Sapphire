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
    Ping = 0x00FA, // updated 6.08
    Init = 0x0182, // updated 6.08

    ActorFreeSpawn = 0x0082, // updated 6.08
    InitZone = 0x01EB, // updated 6.08

    EffectResult = 0x00DE, // updated 6.08
    ActorControl = 0x022F, // updated 6.08
    ActorControlSelf = 0x006B, // updated 6.08
    ActorControlTarget = 0x0191, // updated 6.08

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x02C9, // updated 6.08

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x00CE, // updated 6.08
    Logout = 0x03B2, // updated 6.08
    CFNotify = 0x01C5, // updated 6.08
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x0188, // updated 6.08
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x02DA, // updated 6.08
    CFCancel = 0x00EB, // updated 6.08
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x00A9, // updated 6.08
    SocialRequestResponse = 0x024D, // updated 6.08
    SocialMessage = 0x02B4, // updated 6.08
    SocialMessage2 = 0x011C, // updated 6.08
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x0142, // updated 6.08

    Chat = 0x0148, // updated 6.08
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x039C, // updated 6.08

    ExamineSearchInfo = 0x0297, // updated 6.08
    UpdateSearchInfo = 0x03D1, // updated 6.08
    InitSearchInfo = 0x01BB, // updated 6.08
    ExamineSearchComment = 0x02AE, // updated 6.08

    ServerNoticeShort = 0x01D7, // updated 6.08
    ServerNotice = 0x036E, // updated 6.08
    SetOnlineStatus = 0x0308, // updated 6.08

    CountdownInitiate = 0x00E1, // updated 6.08
    CountdownCancel = 0x0284, // updated 6.08

    PlayerAddedToBlacklist = 0x037D, // updated 6.08
    PlayerRemovedFromBlacklist = 0x0342, // updated 6.08
    BlackList = 0x0070, // updated 6.08

    LinkshellList = 0x0304, // updated 6.08

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x00B2, // updated 6.08
    MarketBoardItemListingCount = 0x026A, // updated 6.08
    MarketBoardItemListingHistory = 0x013A, // updated 6.08
    MarketBoardItemListing = 0x01E2, // updated 6.08
    
    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x02F1, // updated 6.08
    FreeCompanyInfo = 0x01A2, // updated 6.08
    ExamineFreeCompanyInfo = 0x011E, // updated 6.08

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x00BC, // updated 6.08
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x03C7, // updated 6.08
    AoeEffect8 = 0x0149, // updated 6.08
    AoeEffect16 = 0x00C1, // updated 6.08
    AoeEffect24 = 0x0213, // updated 6.08
    AoeEffect32 = 0x038B, // updated 6.08
    PersistantEffect = 0x02AF, // updated 6.08

    GCAffiliation = 0x0264, // updated 6.08

    PlayerSpawn = 0x0226, // updated 6.08
    NpcSpawn = 0x032C, // updated 6.08
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x0370, // updated 6.08

    ActorSetPos = 0x0395, // updated 6.08

    ActorCast = 0x0104, // updated 6.08
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x03AF, // updated 6.08
    PartyMessage = 0x0352, // updated 6.08
    HateRank = 0x03C3, // updated 6.08
    HateList = 0x032B, // updated 6.08
    ObjectSpawn = 0x03A3, // updated 6.08
    ObjectDespawn = 0x0137, // updated 6.08
    UpdateClassInfo = 0x00FE, // updated 6.08
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0261, // updated 6.08
    PlayerStats = 0x02C7, // updated 6.08
    ActorOwner = 0x0261, // updated 6.08
    PlayerStateFlags = 0x03CF, // updated 6.08 (or 0x00CB)
    PlayerClassInfo = 0x025A, // updated 6.08
    CharaVisualEffect = 0x01D1, // updated 6.08

    InstanceDecorAnimation = 0x0338, // updated 6.08

    ModelEquip = 0x00E4, // updated 6.08
    Examine = 0x03E2, // updated 6.08
    CharaNameReq = 0x0343, // updated 6.08

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x0066, // updated 6.08
    RetainerInformation = 0x023B, // updated 6.08

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x02A9, // updated 6.08
    ContainerInfo = 0x037A, // updated 6.08
    InventoryTransactionFinish = 0x0299, // updated 6.08
    InventoryTransaction = 0x0382, //updated 6.08
    CurrencyCrystalInfo = 0x02BE, // updated 6.08 hotfix

    InventoryActionAck = 0x008A, // updated 6.08
    UpdateInventorySlot = 0x0375, // updated 6.08

    HuntingLogEntry = 0x0187, // updated 6.08

    EventPlay = 0x0113, // updated for 6.08
    EventPlay4 = 0x0302, // updated for 6.08
    EventPlay8 = 0x0078, // updated for 6.08
    EventPlay16 = 0x0223, // updated for 6.08
    EventPlay32 = 0x02F2, // updated for 6.08
    EventPlay64 = 0x03BC, // updated for 6.08
    EventPlay128 = 0x033E, // updated for 6.08
    EventPlay255 = 0x0079, // updated for 6.08

    EventContinue = 0x00B6, // updated 5.58 hotfix

    EventStart = 0x00AE, // updated 6.08
    EventFinish = 0x0210, // updated 6.08

    EventLinkshell = 0x1169,

    QuestActiveList = 0x03E0, // updated 6.08
    QuestUpdate = 0x029B, // updated 6.08
    QuestCompleteList = 0x0118, // updated 6.08

    QuestFinish = 0x015A, // updated 6.08
    MSQTrackerComplete = 0x00E5, // updated 6.08
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58 hotfix

    QuestTracker = 0x01FB, // updated 6.08

    Mount = 0x0373, // updated 6.08

    DirectorVars = 0x0138, // updated 6.08
    SomeDirectorUnk1 = 0x00EF, // updated 6.08
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x03DD, // updated 5.58 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF, // updated 5.58 hotfix
    DirectorPopUp4 = 0x019B, // updated 5.58 hotfix
    DirectorPopUp8 = 0x0271, // updated 5.58 hotfix

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x00ED, // updated 6.08
    PlayerTitleList = 0x02C2, // updated 6.08
    Discovery = 0x03A4, // updated 6.08

    EorzeaTimeOffset = 0x0074, // updated 6.08

    EquipDisplayFlags = 0x023A, // updated 6.08

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287, // updated 5.58 hotfix
    LootMessage = 0x006C, // updated 6.08
    ResultDialog = 0x0273, // updated 5.58 hotfix
    DesynthResult = 0x0143, // updated 6.08

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0280, // updated 6.08
    LandUpdate = 0x03C6, // updated 6.08
    YardObjectSpawn = 0x01AC, // updated 6.08
    HousingIndoorInitialize = 0x00E6, // updated 6.08
    LandPriceUpdate = 0x03CB, // updated 6.08
    LandInfoSign = 0x0276, // updated 6.08
    LandRename = 0x0158, // updated 6.08
    HousingEstateGreeting = 0x029E, // updated 6.08
    HousingUpdateLandFlagsSlot = 0x01B4, // updated 6.08
    HousingLandFlags = 0x03DD, // updated 6.08
    HousingShowEstateGuestAccess = 0x011B, // updated 6.08

    HousingObjectInitialize = 0x02DF, // updated 6.08
    HousingInternalObjectSpawn = 0x01C2, // updated 6.08

    HousingWardInfo = 0x0145, // updated 6.08
    HousingObjectMove = 0x0242, // updated 6.08

    SharedEstateSettingsResponse = 0x02F0, // updated 6.08

    LandUpdateHouseName = 0x0132, // updated 6.08

    LandSetMap = 0x008B, // updated 6.08

    CeremonySetActorAppearance = 0x0222, // updated 6.08

    //////////////////////////////////////////////////

    DuelChallenge = 0xF277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x009B, // updated 6.08

    PrepareZoning = 0x039A, // updated 6.08
    ActorGauge = 0x03B5, // updated 6.08
    DutyGauge = 0x008B, // updated 6.08

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0136, // updated 6.08
    DailyQuestRepeatFlags = 0x0348, // updated 6.08

    MapUpdate = 0x0364, // updated 6.08
    MapUpdate4 = 0x0128, // updated 6.08
    MapUpdate8 = 0x0286, // updated 6.08
    MapUpdate16 = 0x01AA, // updated 6.08
    MapUpdate32 = 0x0151, // updated 6.08
    MapUpdate64 = 0x00CD, // updated 6.08
    MapUpdate128 = 0x017D, // updated 6.08

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
    AirshipExplorationResult = 0x023E, // updated 6.08
    AirshipStatus = 0x01F5, // updated 6.08
    AirshipStatusList = 0x0250, // updated 6.08
    AirshipTimers = 0x0225, // updated 6.08
    SubmarineExplorationResult = 0x00C9, // updated 6.08
    SubmarineProgressionStatus = 0x0092, // updated 6.08
    SubmarineStatusList = 0x0212, // updated 6.08
    SubmarineTimers = 0x0346, // updated 6.08
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x0315, // updated 6.08
    InitHandler = 0x0068, // updated 6.08

    FinishLoadingHandler = 0x0182, // updated 6.08
    CFCommenceHandler = 0x0381, // updated 5.58 hotfix

    CFCancelHandler = 0x02B2, // updated 5.58 hotfix
    CFRegisterDuty = 0x01BD, // updated 5.58 hotfix
    CFRegisterRoulette = 0x037A, // updated 5.58 hotfix
    PlayTimeHandler = 0x0279, // updated 6.08
    LogoutHandler = 0x0125, // updated 6.08
    CancelLogout = 0x01AC, // updated 5.58 hotfix
    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialReqSendHandler = 0x00D7, // updated 5.58 hotfix
    SocialResponseHandler = 0x0193, // updated 6.08
    CreateCrossWorldLS = 0x035D, // updated 5.58 hotfix

    ChatHandler = 0x01C8, // updated 6.08
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x036C, // updated 5.58 hotfix
    LeavePartyHandler = 0x019D, // updated 5.58 hotfix
    KickPartyMemberHandler = 0x0262, // updated 5.58 hotfix
    DisbandPartyHandler = 0x0276, // updated 5.58 hotfix

    SocialListHandler = 0x012A, // updated 6.08
    SetSearchInfoHandler = 0x02BB, // updated 6.08
    ReqSearchInfoHandler = 0x014F, // updated 5.58 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58 hotfix
    BlackListHandler = 0x019E, // updated 6.08
    PlayerSearchHandler = 0x037D, // updated 5.58 hotfix

    LinkshellListHandler = 0x010C, // updated 6.08

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

    ZoneLineHandler = 0x00C3, // updated 5.58 hotfix
    ClientTrigger = 0x02F1, // updated 6.08
    DiscoveryHandler = 0x038B, // updated 5.58 hotfix

    PlaceFieldMarkerPreset = 0x01FE, // updated 6.08
    PlaceFieldMarker = 0x0067, // updated 6.08
    SkillHandler = 0x008E, // updated 6.08
    GMCommand1 = 0x0290, // updated 6.08
    GMCommand2 = 0x0203, // updated 6.08
    AoESkillHandler = 0x0152, // updated 5.58 hotfix

    UpdatePositionHandler = 0x0147, // updated 6.08

    InventoryModifyHandler = 0x0154, // updated 6.08
    
    InventoryEquipRecommendedItems = 0x01C9, // updated 5.58 hotfix

    ReqPlaceHousingItem = 0x02D4, // updated 5.58 hotfix
    BuildPresetHandler = 0x0223, // updated 5.58 hotfix

    TalkEventHandler = 0x036B, // updated 6.08
    EmoteEventHandler = 0x00B0, // updated 5.58 hotfix
    WithinRangeEventHandler = 0x02B6, // updated 5.58 hotfix
    OutOfRangeEventHandler = 0x03C5, // updated 5.58 hotfix
    EnterTeriEventHandler = 0x03AB, // updated 6.08
    ShopEventHandler = 0x0384, // updated 5.58 hotfix
    ReturnEventHandler = 0x008D, // updated 5.58 hotfix
    TradeReturnEventHandler = 0x0116, // updated 6.08
    TradeReturnEventHandler2 = 0x023C, // updated 5.58 hotfix
    EventYield2Handler = 0x021D, // updated 5.58 hotfix
    EventYield16Handler = 0x0207, // updated 5.58 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x02A5, // updated 5.58 hotfix

    LandRenameHandler = 0x028E, // updated 5.58 hotfix
    HousingUpdateHouseGreeting = 0x0343, // updated 5.58 hotfix
    HousingUpdateObjectPosition = 0x012C, // updated 5.58 hotfix
    HousingEditExterior = 0x027B, // updated 5.58 hotfix
    HousingEditInterior = 0x02E3, // updated 5.58 hotfix

    SetSharedEstateSettings = 0x00D2, // updated 5.58 hotfix

    UpdatePositionInstance = 0x0209, // updated 6.08

    PerformNoteHandler = 0x0243, // updated 5.58 hotfix

    WorldInteractionHandler = 0x0274, // updated 5.58 hotfix
    Dive = 0x0320, // updated 5.58 hotfix
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