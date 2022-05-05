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

    // Old Definitions that need to be here to compile
    ActorFreeSpawn = 0x0082, // updated 6.08
    ChatBanned = 0xF06B,
    InitSearchInfo = 0x010D, // updated 6.11

    /////////////////////////////////////////////////

    Ping = 0x10F4, // updated 6.11
    Init = 0x0104, // updated 6.11

    InitZone = 0x01F5, // Updated 6.11
    PrepareZoning = 0x01CF, // Updated 6.11

    EffectResult = 0x0309, // Updated 6.11
    EffectResultBasic = 0x00A8, // updated 6.11

    ActorControl = 0x016F, // Updated 6.11
    ActorControlSelf = 0x03AE, // Updated 6.11
    ActorControlTarget = 0x01B2, // Updated 6.11
    ActorCast = 0x0163, // Updated 6.11
    ActorMove = 0x0397, // Updated 6.11
    ActorSetPos = 0x0317, // Updated 6.11
    ActorGauge = 0x02A7, // Updated 6.11

    EventPlay = 0x313,    // Updated for 6.11
    EventPlay4 = 0x36D,   // Updated for 6.11
    EventPlay8 = 0x364,   // Updated for 6.11
    EventPlay16 = 0x9E,   // Updated for 6.11
    EventPlay32 = 0x3C8,  // Updated for 6.11
    EventPlay64 = 0x16B,  // Updated for 6.11
    EventPlay128 = 0x2FB, // Updated for 6.11
    EventPlay255 = 0xD8,  // Updated for 6.11
    EventStart = 0x0217, // Updated 6.11
    EventFinish = 0x0096, // Updated 6.11

    DirectorVars = 0x0138, // updated 6.08
    SomeDirectorUnk1 = 0x00EF, // updated 6.08
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x01AD, // Updated 6.11
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF, // updated 5.58 hotfix
    DirectorPopUp4 = 0x019B, // updated 5.58 hotfix
    DirectorPopUp8 = 0x0271, // updated 5.58 hotfix

    ///////////////////////////////////////////////////

    PlayerSetup = 0x0312, // Updated 6.11
    PlayerStats = 0x0370, // Updated 6.11
    PlayerSpawn = 0x018F, // Updated 6.11
    PlayerClassInfo = 0x0370, // updated 6.11


    UpdateHpMpTp = 0x028B, // Updated 6.11
    UpdateClassInfo = 0x00D4, // Updated 6.11

    UpdateSearchInfo = 0x0334, // Updated 6.11
    ExamineSearchInfo = 0x022B, // Updated 6.11

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0296, // updated 6.11
    DailyQuestRepeatFlags = 0x00C0, // updated 6.11


    Playtime = 0x009D, // Updated 6.11
    Logout = 0x0109, // updated 6.11
    CFNotify = 0x01C5, // updated 6.08
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x0188, // updated 6.08
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x02DA, // updated 6.08
    CFCancel = 0x00EB, // updated 6.08
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x00A9, // updated 6.08
    SocialRequestResponse = 0x037C, // updated 6.11
    SocialMessage = 0x02B4, // updated 6.08
    SocialMessage2 = 0x03CA, // updated 6.11
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x0142, // updated 6.08

    Chat = 0x0148, // updated 6.08
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x039C, // updated 6.08

    ExamineSearchComment = 0x02AE, // updated 6.08

    ServerNoticeShort = 0x01D7, // updated 6.08
    ServerNotice = 0x036E, // updated 6.08
    SetOnlineStatus = 0x0121, // updated 6.11

    CountdownInitiate = 0x9999, // updated 6.08 Overwrites Item Info
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

    MarketBoardSearchResult = 0x0389, // Updated 6.11
    MarketBoardItemListingCount = 0x01AC, // Updated 6.11
    MarketBoardItemListingHistory = 0x02E5, // Updated 6.11
    MarketBoardItemListing = 0x03AC, // Updated 6.11
    
    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x02F1, // updated 6.08
    FreeCompanyInfo = 0x0084, // Updated 6.11
    FreeCompanyDialog = 0x03B8, // Updated 6.11
    ExamineFreeCompanyInfo = 0x011E, // updated 6.08

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x00D2, // Updated 6.11
    EurekaStatusEffectList = 0x0182, // updated 6.11
    BossStatusEffectList = 0x0299, // updated 6.11
    Effect = 0x0398, // Updated 6.11
    AoeEffect8 = 0x0359, // Updated 6.11
    AoeEffect16 = 0x0260, // Updated 6.11
    AoeEffect24 = 0x0209, // updated 6.11
    AoeEffect32 = 0x039F, // updated 6.11
    PersistantEffect = 0x02AF, // updated 6.08

    GCAffiliation = 0x0264, // updated 6.08

    NpcSpawn = 0x02B1, // Updated 6.11
    NpcSpawn2 = 0x0083, // updated 6.11

    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x03AF, // updated 6.08
    PartyMessage = 0x0352, // updated 6.08
    HateRank = 0x03C3, // updated 6.08
    HateList = 0x032B, // updated 6.08
    ObjectSpawn = 0x02D3, // Updated 6.11
    ObjectDespawn = 0x0137, // updated 6.08
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    ActorOwner = 0x0261, // updated 6.08
    PlayerStateFlags = 0x0367, // updated 6.11

    CharaVisualEffect = 0x01D1, // updated 6.08

    InstanceDecorAnimation = 0x0338, // updated 6.08

    ModelEquip = 0x00E4, // updated 6.08
    Examine = 0x03E2, // updated 6.08
    CharaNameReq = 0x0343, // updated 6.08

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x0066, // updated 6.08
    RetainerInformation = 0x029B, // Updated 6.11

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x00E1, // updated 6.11
    ContainerInfo = 0x035D, // Updated 6.11
    InventoryTransactionFinish = 0x00B8, // Updated 6.11
    InventoryTransaction = 0x009B, //updated 6.11
    CurrencyCrystalInfo = 0x03AC,// updated 6.11

    InventoryActionAck = 0x0190, // Updated 6.11
    UpdateInventorySlot = 0x0322, // Updated 6.11

    HuntingLogEntry = 0x0187, // updated 6.08

    EventContinue = 0x00B6, // updated 5.58 hotfix

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

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x02C6, // updated 6.11
    PlayerTitleList = 0x02C2, // updated 6.08
    Discovery = 0x03A4, // updated 6.08

    EorzeaTimeOffset = 0x0074, // updated 6.08

    EquipDisplayFlags = 0x023A, // updated 6.08

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287, // updated 5.58 hotfix
    LootMessage = 0x006C, // updated 6.08
    ResultDialog = 0x0361, // Updated 6.11
    DesynthResult = 0x035A, // Updated 6.11

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

    DutyGauge = 0x008B, // updated 6.08



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
    MahjongEndGame = 0x9999, // finished oorasu(all-last) round; shows a result screen. Changed to 9999 since a 6.11 packet uses the opcode value in 6.08

    /// Airship & Submarine //////////////////////////////////////
    AirshipExplorationResult = 0x0328, // Updated 6.11
    AirshipStatus = 0x011B, // Updated 6.11
    AirshipStatusList = 0x01B4, // Updated 6.11
    AirshipTimers = 0x024B, // Updated 6.11
    SubmarineExplorationResult = 0x00B9, // Updated 6.11
    SubmarineProgressionStatus = 0x00C7, // Updated 6.11
    SubmarineStatusList = 0x0236, // Updated 6.11
    SubmarineTimers = 0x0254, // Updated 6.11
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x00B6, // updated 6.11 testing
    InitHandler = 0x0216, // updated 6.11 testing
    FinishLoadingHandler = 0x0082, // updated 6.11 testing
    SocialListHandler = 0x0999, // updated 6.11 testing
    BlackListHandler = 0x0999, // updated 6.11 testing
    LinkshellListHandler = 0x9999, // updated 6.11 testing
    MarketBoardSearch = 0x9999, // updated 5.58 hotfix

    LogoutHandler = 0x02CE, // updated 6.11

    CancelLogout = 0x0354, // updated 6.11

    UpdatePositionHandler = 0x0187, // Updated 6.11
    ClientTrigger = 0x0283, // Updated 6.11
    ChatHandler = 0x0133, // Updated 6.11
    SetSearchInfoHandler = 0x01F0, // Updated 6.11
    MarketBoardPurchaseHandler = 0x037C, // Updated 6.11
    InventoryModifyHandler = 0x0350, // Updated 6.11 (Base offset: 0x0357)
    UpdatePositionInstance = 0x031E, // Updated 6.11
    PlaceFieldMarkerPreset = 0x0068, // Updated 6.11
    PlaceFieldMarker = 0x028F, // Updated 6.11
    GMCommand1 = 0x0145, // updated 6.11

    CFCommenceHandler = 0x0381, // updated 5.58 hotfix

    CFCancelHandler = 0x02B2, // updated 5.58 hotfix
    CFRegisterDuty = 0x01BD, // updated 5.58 hotfix
    CFRegisterRoulette = 0x037A, // updated 5.58 hotfix
    PlayTimeHandler = 0x0279, // updated 6.08

    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialReqSendHandler = 0x021C, // updated 6.08
    SocialResponseHandler = 0x0193, // updated 6.08
    CreateCrossWorldLS = 0x035D, // updated 5.58 hotfix

    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x036C, // updated 5.58 hotfix
    LeavePartyHandler = 0x019D, // updated 5.58 hotfix
    KickPartyMemberHandler = 0x0262, // updated 5.58 hotfix
    DisbandPartyHandler = 0x0276, // updated 5.58 hotfix

    ReqSearchInfoHandler = 0x014F, // updated 5.58 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58 hotfix
    PlayerSearchHandler = 0x037D, // updated 5.58 hotfix

    MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58 hotfix
    MarketBoardRequestItemListings = 0x0122, // updated 5.58 hotfix

    ReqExamineFcInfo = 0x037B, // updated 5.58 hotfix

    FcInfoReqHandler = 0x03D4, // updated 5.58 hotfix

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x00C3, // updated 5.58 hotfix

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x02EC, // updated 5.58 hotfix
    ReqCountdownCancel = 0x0068, // updated 5.58 hotfix

    ZoneLineHandler = 0x00C3, // updated 5.58 hotfix
    DiscoveryHandler = 0x00D9, // updated 6.08

    GMCommand2 = 0x0203, // updated 6.08

    SkillHandler = 0x008E, // updated 6.08
    AoESkillHandler = 0x0152, // updated 5.58 hotfix


    
    InventoryEquipRecommendedItems = 0x01C9, // updated 5.58 hotfix

    ReqPlaceHousingItem = 0x0192, // updated 6.08
    BuildPresetHandler = 0x0223, // updated 5.58 hotfix

    TalkEventHandler = 0x036B, // updated 6.08
    EmoteEventHandler = 0x00B0, // updated 5.58 hotfix
    WithinRangeEventHandler = 0x02B6, // updated 5.58 hotfix
    OutOfRangeEventHandler = 0x03C5, // updated 5.58 hotfix
    EnterTeriEventHandler = 0x03AB, // updated 6.08
    ShopEventHandler = 0x0384, // updated 5.58 hotfix

    ReturnEventHandler = 0x008D, // updated 6.08 
    TradeReturnEventHandler = 0x0116, // updated 6.08
    TradeReturnEventHandler2 = 0x0388, // updated 6.08 

    EventYield2Handler = 0x021D, // updated 5.58 hotfix
    EventYield16Handler = 0x0213, // updated 6.08

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x0252, // updated 6.08

    LandRenameHandler = 0x028E, // updated 5.58 hotfix
    HousingUpdateHouseGreeting = 0x0343, // updated 5.58 hotfix
    HousingUpdateObjectPosition = 0x012C, // updated 5.58 hotfix
    HousingEditExterior = 0x03B6, // updated 6.08
    HousingEditInterior = 0x0249, // updated 6.08

    SetSharedEstateSettings = 0x00D2, // updated 5.58 hotfix

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