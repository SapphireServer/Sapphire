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
    ActorFreeSpawn = 0x00AD, // updated 6.11
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

    DirectorVars = 0x0306, // updated 6.11 or 0xC6 from my findings
    SomeDirectorUnk1 = 0x00DB, // updated 6.11 or 0xCC, 0x122, 0x1AD, or 0x24F
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x01AD, // Updated 6.11
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18

    DirectorPopUp = 0x03DF, // updated 5.58 hotfix
    DirectorPopUp4 = 0x019B, // updated 5.58 hotfix
    DirectorPopUp8 = 0x0271, // updated 5.58 hotfix
    ///////// These last 3 are 0x0093, 0x00DA and 0x01CB, but don't know which is which
    ///////////////////////////////////////////////////

    PlayerSetup = 0x0312, // Updated 6.11
    PlayerStats = 0x0370, // Updated 6.11
    PlayerSpawn = 0x018F, // Updated 6.11
    PlayerClassInfo = 0x0271, // updated 6.11


    UpdateHpMpTp = 0x028B, // Updated 6.11
    UpdateClassInfo = 0x00D4, // Updated 6.11

    UpdateSearchInfo = 0x0334, // Updated 6.11
    ExamineSearchInfo = 0x022B, // Updated 6.11

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0296, // updated 6.11
    DailyQuestRepeatFlags = 0x00C0, // updated 6.11


    Playtime = 0x009D, // Updated 6.11
    Logout = 0x0109, // updated 6.11
    
    CFNotify = 0x0188, // updated 6.11
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x0383, // updated 6.11
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x02A0, // updated 6.11
    CFCancel = 0x0354, // updated 6.11
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x00EF, // updated 6.11
    SocialRequestResponse = 0x037C, // updated 6.11
    SocialMessage = 0x0239, // updated 6.11
    SocialMessage2 = 0x03CA, // updated 6.11
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x0244, // updated 6.11

    Chat = 0x01C7, // updated 6.11
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x0138, // updated 6.11

    ExamineSearchComment = 0x03A3, // updated 6.11

    ServerNoticeShort = 0x015E, // updated 6.11
    ServerNotice = 0x01FF, // updated 6.11
    SetOnlineStatus = 0x0121, // updated 6.11

    CountdownInitiate = 0x03CB, // updated 6.11
    CountdownCancel = 0x00F0, // updated 6.11

    PlayerAddedToBlacklist = 0x027C, // updated 6.11
    PlayerRemovedFromBlacklist = 0x0069, // updated 6.11
    BlackList = 0x02A3, // updated 6.11

    LinkshellList = 0x010D, // updated 6.11

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
    FreeCompanyBoardMsg = 0x0276, // updated 6.11
    FreeCompanyInfo = 0x0084, // Updated 6.11
    FreeCompanyDialog = 0x03B8, // Updated 6.11
    ExamineFreeCompanyInfo = 0x0197, // updated 6.11

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x00D2, // Updated 6.11
    EurekaStatusEffectList = 0x0182, // updated 6.11
    BossStatusEffectList = 0x0299, // updated 6.11
    Effect = 0x0398, // Updated 6.11
    AoeEffect8 = 0x0359, // Updated 6.11
    AoeEffect16 = 0x0260, // Updated 6.11
    AoeEffect24 = 0x0209, // updated 6.11
    AoeEffect32 = 0x039F, // updated 6.11
    PersistantEffect = 0x0299, // updated 6.11

    GCAffiliation = 0x02B0, // updated 6.11

    NpcSpawn = 0x02B1, // Updated 6.11
    NpcSpawn2 = 0x0083, // updated 6.11

    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x026F, // updated 6.11
    PartyMessage = 0x0222, // updated 6.11
    HateRank = 0x01C5, // updated 6.11
    HateList = 0x024C, // updated 6.11
    ObjectSpawn = 0x02D3, // Updated 6.11
    ObjectDespawn = 0x024D, // updated 6.11
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    ActorOwner = 0x0312, // updated 6.11
    PlayerStateFlags = 0x0367, // updated 6.11

    CharaVisualEffect = 0x010E, // updated 6.11

    InstanceDecorAnimation = 0x03BC, // updated 6.11

    ModelEquip = 0x017A, // updated 6.11
    Examine = 0x0305, // updated 6.11
    CharaNameReq = 0x01E3, // updated 6.11

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x0320, // updated 6.11
    RetainerInformation = 0x029B, // Updated 6.11

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x00E1, // updated 6.11
    ContainerInfo = 0x035D, // Updated 6.11
    InventoryTransactionFinish = 0x00B8, // Updated 6.11
    InventoryTransaction = 0x009B, //updated 6.11
    CurrencyCrystalInfo = 0x01E2,// updated 6.11

    InventoryActionAck = 0x0190, // Updated 6.11
    UpdateInventorySlot = 0x0322, // Updated 6.11

    HuntingLogEntry = 0x0249, // updated 6.11

    EventContinue = 0x00B6, // updated 5.58 hotfix

    EventLinkshell = 0x1169,

    QuestActiveList = 0x0099, // updated 6.11
    QuestUpdate = 0x03B0, // updated 6.11
    QuestCompleteList = 0x0310, // updated 6.11

    QuestFinish = 0x039C, // updated 6.11
    MSQTrackerComplete = 0x0261, // updated 6.11
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58 hotfix

    QuestTracker = 0x01BC, // updated 6.11

    Mount = 0x0268, // updated 6.11

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x02C6, // updated 6.11
    PlayerTitleList = 0x006D, // updated 6.11
    Discovery = 0x0177, // updated 6.11

    EorzeaTimeOffset = 0x03B1, // updated 6.11

    EquipDisplayFlags = 0x0344, // updated 6.11

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287, // updated 5.58 hotfix
    LootMessage = 0x0396, // updated 6.11
    ResultDialog = 0x0361, // Updated 6.11
    DesynthResult = 0x035A, // Updated 6.11

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x03E5, // updated 6.11
    LandUpdate = 0x00D3, // updated 6.11
    YardObjectSpawn = 0x014B, // updated 6.11
    HousingIndoorInitialize = 0x00E6, // updated 6.11
    LandPriceUpdate = 0x00FD, // updated 6.11
    LandInfoSign = 0x0281, // updated 6.11
    LandRename = 0x0343, // updated 6.11
    HousingEstateGreeting = 0x01FE, // updated 6.11
    HousingUpdateLandFlagsSlot = 0x006B, // updated 6.11
    HousingLandFlags = 0x0293, // updated 6.11
    HousingShowEstateGuestAccess = 0x025E, // updated 6.11

    HousingObjectInitialize = 0x01B5, // updated 6.11
    HousingInternalObjectSpawn = 0x006E, // updated 6.11

    HousingWardInfo = 0x0343, // updated 6.11
    HousingObjectMove = 0x02C4, // updated 6.11

    SharedEstateSettingsResponse = 0x006B, // updated 6.11

    LandUpdateHouseName = 0x0240, // updated 6.11

    LandSetMap = 0x03E4, // updated 6.11

    CeremonySetActorAppearance = 0x0241, // updated 6.11

    //////////////////////////////////////////////////

    DuelChallenge = 0xF277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x03AA, // updated 6.11

    DutyGauge = 0x008B, // updated 6.08 - this opcode seems to be wrong, LandSetMap duplicate



    MapUpdate = 0x01FD, // updated 6.11
    MapUpdate4 = 0x0248, // updated 6.11
    MapUpdate8 = 0x01F2, // updated 6.11
    MapUpdate16 = 0x02F6, // updated 6.11
    MapUpdate32 = 0x03C3, // updated 6.11
    MapUpdate64 = 0x0162, // updated 6.11
    MapUpdate128 = 0x0153, // updated 6.11

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
    FinishLoadingHandler = 0x0104, // updated 6.11 testing
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