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
    Ping = 0x02A8, // updated 5.58 hotfix
    Init = 0x013C, // updated 5.58 hotfix

    ActorFreeSpawn = 0x00B5, // updated 5.58 hotfix
    InitZone = 0x0320, // updated 5.58 hotfix

    EffectResult = 0x0387, // updated 5.58 hotfix
    ActorControl = 0x00B0, // updated 5.58 hotfix
    ActorControlSelf = 0x02B6, // updated 5.58 hotfix
    ActorControlTarget = 0x03C5, // updated 5.58 hotfix

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x01A7, // updated 5.58 hotfix

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x0179, // updated 5.58 hotfix
    Logout = 0x0214, // updated 5.58 hotfix
    CFNotify = 0x0327, // updated 5.58 hotfix
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x03AA, // updated 5.58 hotfix
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x024B, // updated 5.58 hotfix
    CFCancel = 0x01AC, // updated 5.58 hotfix
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x029F, // updated 5.58 hotfix
    SocialInviteResponse = 0x0082, // updated 5.58 hotfix
    SocialInviteUpdate = 0x03CB, // updated 5.58 hotfix
    SocialInviteResult = 0x01D7, // updated 5.58 hotfix
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x0118, // updated 5.58 hotfix

    Chat = 0x00FE, // updated 5.58 hotfix

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x015F, // updated 5.58 hotfix

    ExamineSearchInfo = 0x0133, // updated 5.58 hotfix
    UpdateSearchInfo = 0x03E5, // updated 5.58 hotfix
    InitSearchInfo = 0x0321, // updated 5.58 hotfix
    ExamineSearchComment = 0x03AD, // updated 5.58 hotfix

    ServerNoticeShort = 0x0333, // updated 5.58 hotfix
    ServerNotice = 0x0171, // updated 5.58 hotfix
    SetOnlineStatus = 0x037B, // updated 5.58 hotfix

    CountdownInitiate = 0x0111, // updated 5.58 hotfix
    CountdownCancel = 0x0231, // updated 5.58 hotfix

    PlayerAddedToBlacklist = 0x024E, // updated 5.58 hotfix
    PlayerRemovedFromBlacklist = 0x011D, // updated 5.58 hotfix
    BlackList = 0x03C0, // updated 5.58 hotfix

    LinkshellList = 0x02E2, // updated 5.58 hotfix

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x01F1, // updated 5.58 hotfix
    MarketBoardItemListingCount = 0x0068, // updated 5.58 hotfix
    MarketBoardItemListingHistory = 0x01BA, // updated 5.58 hotfix
    MarketBoardItemListing = 0x0076, // updated 5.58 hotfix

    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x03DB, // updated 5.58 hotfix
    FreeCompanyInfo = 0x01F7, // updated 5.58 hotfix
    ExamineFreeCompanyInfo = 0x0324, // updated 5.58 hotfix

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x0074, // updated 5.58 hotfix
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x03CA, // updated 5.58 hotfix
    AoeEffect8 = 0x03C4, // updated 5.58 hotfix
    AoeEffect16 = 0x00FA, // updated 5.58 hotfix
    AoeEffect24 = 0x0339, // updated 5.58 hotfix
    AoeEffect32 = 0x023C, // updated 5.58 hotfix
    PersistantEffect = 0x025D, // updated 5.58 hotfix

    GCAffiliation = 0x0094, // updated 5.58 hotfix

    PlayerSpawn = 0x01D8, // updated 5.58 hotfix
    NpcSpawn = 0x00D2, // updated 5.58 hotfix
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x00F8, // updated 5.58 hotfix

    ActorSetPos = 0x0299, // updated 5.58 hotfix

    ActorCast = 0x015D, // updated 5.58 hotfix
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x0349, // updated 5.58 hotfix
    PartyUpdate = 0x00A4, // updated 5.58 hotfix
    HateRank = 0x0150, // updated 5.58 hotfix
    HateList = 0x0243, // updated 5.58 hotfix
    ObjectSpawn = 0x0125, // updated 5.58 hotfix
    ObjectDespawn = 0x0148, // updated 5.58 hotfix
    UpdateClassInfo = 0x0084, // updated 5.58 hotfix
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x01D5, // updated 5.58 hotfix
    PlayerStats = 0x0295, // updated 5.58 hotfix
    ActorOwner = 0x0260, // updated 5.58 hotfix
    PlayerStateFlags = 0x03BF, // updated 5.58 hotfix
    PlayerClassInfo = 0x0131, // updated 5.58 hotfix
    CharaVisualEffect = 0x0292, // updated 5.58 hotfix

    ModelEquip = 0x03A2, // updated 5.58 hotfix
    Examine = 0x0365, // updated 5.58 hotfix
    CharaNameReq = 0x01F0, // updated 5.58 hotfix

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x03CE, // updated 5.58 hotfix
    RetainerInformation = 0x022F, // updated 5.58 hotfix

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x01CC, // updated 5.58 hotfix
    ContainerInfo = 0x025C, // updated 5.58 hotfix
    InventoryTransactionFinish = 0x0176, // updated 5.58 hotfix
    InventoryTransaction = 0x027F, // updated 5.58 hotfix
    CurrencyCrystalInfo = 0x0345, // updated 5.58 hotfix

    InventoryActionAck = 0x03B8, // updated 5.58 hotfix
    UpdateInventorySlot = 0x02F7, // updated 5.58 hotfix

    HuntingLogEntry = 0x01D9, // updated 5.58 hotfix

    EventPlay = 0x016B, // updated 5.58 hotfix
    EventPlay4 = 0x010A, // updated 5.58 hotfix
    EventPlay8 = 0x0337, // updated 5.58 hotfix
    EventPlay16 = 0x0269, // updated 5.58 hotfix
    EventPlay32 = 0x023E, // updated 5.58 hotfix
    EventPlay64 = 0x00DE, // updated 5.58 hotfix
    EventPlay128 = 0x02D0, // updated 5.58 hotfix
    EventPlay255 = 0x0362, // updated 5.58 hotfix

    EventContinue = 0x00B6, // updated 5.58 hotfix

    EventStart = 0x02DA, // updated 5.58 hotfix
    EventFinish = 0x0235, // updated 5.58 hotfix

    EventLinkshell = 0x1169,

    QuestActiveList = 0x0097, // updated 5.58 hotfix
    QuestUpdate = 0x01B2, // updated 5.58 hotfix
    QuestCompleteList = 0x006D, // updated 5.58 hotfix

    QuestFinish = 0x021B, // updated 5.58 hotfix
    MSQTrackerComplete = 0x0348, // updated 5.58 hotfix
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0220, // updated 5.58 hotfix

    QuestTracker = 0x00D8, // updated 5.58 hotfix

    Mount = 0x01E1, // updated 5.58 hotfix

    DirectorVars = 0x0154, // updated 5.58 hotfix
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x03DD, // updated 5.58 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x03DF, // updated 5.58 hotfix
    DirectorPopUp4 = 0x019B, // updated 5.58 hotfix
    DirectorPopUp8 = 0x0271, // updated 5.58 hotfix

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x0323, // updated 5.58 hotfix
    PlayerTitleList = 0x014E, // updated 5.58 hotfix
    Discovery = 0x01C2, // updated 5.58 hotfix

    EorzeaTimeOffset = 0x0070, // updated 5.58 hotfix

    EquipDisplayFlags = 0x02C6, // updated 5.58 hotfix

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0287, // updated 5.58 hotfix
    LootMessage = 0x0383, // updated 5.58 hotfix
    ResultDialog = 0x0273, // updated 5.58 hotfix
    DesynthResult = 0x0238, // updated 5.58 hotfix

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0159, // updated 5.58 hotfix
    LandUpdate = 0x0228, // updated 5.58 hotfix
    YardObjectSpawn = 0x023D, // updated 5.58 hotfix
    HousingIndoorInitialize = 0x0210, // updated 5.58 hotfix
    LandPriceUpdate = 0x0300, // updated 5.58 hotfix
    LandInfoSign = 0x03E7, // updated 5.58 hotfix
    LandRename = 0x01BF, // updated 5.58 hotfix
    HousingEstateGreeting = 0x0126, // updated 5.58 hotfix
    HousingUpdateLandFlagsSlot = 0x0157, // updated 5.58 hotfix
    HousingLandFlags = 0x03B1, // updated 5.58 hotfix
    HousingShowEstateGuestAccess = 0x00CC, // updated 5.58 hotfix

    HousingObjectInitialize = 0x0112, // updated 5.58 hotfix
    HousingInternalObjectSpawn = 0x02C8, // updated 5.58 hotfix

    HousingWardInfo = 0x012A, // updated 5.58 hotfix
    HousingObjectMove = 0x0265, // updated 5.58 hotfix

    SharedEstateSettingsResponse = 0x030E, // updated 5.58 hotfix

    LandUpdateHouseName = 0x017C, // updated 5.58 hotfix

    LandSetMap = 0x02E5, // updated 5.58 hotfix

    CeremonySetActorAppearance = 0x02ED, // updated 5.58 hotfix

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0127, // updated 5.58 hotfix

    PrepareZoning = 0x02AB, // updated 5.58 hotfix
    ActorGauge = 0x01C1, // updated 5.58 hotfix
    DutyGauge = 0x02E5, // updated 5.58 hotfix

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x02D6, // updated 5.58 hotfix
    DailyQuestRepeatFlags = 0x01AB, // updated 5.58 hotfix

    MapUpdate = 0x0394, // updated 5.58 hotfix
    MapUpdate4 = 0x036F, // updated 5.58 hotfix
    MapUpdate8 = 0x0311, // updated 5.58 hotfix
    MapUpdate16 = 0x0108, // updated 5.58 hotfix
    MapUpdate32 = 0x007A, // updated 5.58 hotfix
    MapUpdate64 = 0x02A0, // updated 5.58 hotfix
    MapUpdate128 = 0x0303, // updated 5.58 hotfix

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
    AirshipExplorationResult = 0x0203, // updated 5.58 hotfix
    AirshipStatus = 0x030C, // updated 5.58 hotfix
    AirshipStatusList = 0x02FE, // updated 5.58 hotfix
    AirshipTimers = 0x0166, // updated 5.58 hotfix
    SubmarineExplorationResult = 0x00AA, // updated 5.58 hotfix
    SubmarineProgressionStatus = 0x0357, // updated 5.58 hotfix
    SubmarineStatusList = 0x01EF, // updated 5.58 hotfix
    SubmarineTimers = 0x0247, // updated 5.58 hotfix
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x0288, // updated 5.58 hotfix
    InitHandler = 0x02EB, // updated 5.58 hotfix

    FinishLoadingHandler = 0x013C, // updated 5.58 hotfix

    CFCommenceHandler = 0x0381, // updated 5.58 hotfix

    CFCancelHandler = 0x02B2, // updated 5.58 hotfix
    CFRegisterDuty = 0x01BD, // updated 5.58 hotfix
    CFRegisterRoulette = 0x037A, // updated 5.58 hotfix
    PlayTimeHandler = 0x02B7, // updated 5.58 hotfix
    LogoutHandler = 0x00A0, // updated 5.58 hotfix
    CancelLogout = 0x01AC, // updated 5.58 hotfix
    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialInviteHandler = 0x00D7, // updated 5.58 hotfix
    SocialReplyHandler = 0x023B, // updated 5.58 hotfix
    CreateCrossWorldLS = 0x035D, // updated 5.58 hotfix

    ChatHandler = 0x03B0, // updated 5.58 hotfix
    PartyChangeLeaderHandler = 0x036C, // updated 5.58 hotfix
    PartyLeaveHandler = 0x019D, // updated 5.58 hotfix
    PartyKickHandler = 0x0262, // updated 5.58 hotfix
    PartyDisbandHandler = 0x0276, // updated 5.58 hotfix

    SocialListHandler = 0x01CA, // updated 5.58 hotfix
    SetSearchInfoHandler = 0x01D4, // updated 5.58 hotfix
    ReqSearchInfoHandler = 0x014F, // updated 5.58 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58 hotfix
    BlackListHandler = 0x00F2, // updated 5.58 hotfix
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

    ZoneLineHandler = 0x008D, // updated 5.58 hotfix
    ClientTrigger = 0x03DB, // updated 5.58 hotfix
    DiscoveryHandler = 0x038B, // updated 5.58 hotfix

    PlaceFieldMarkerPreset = 0x026D, // updated 5.58 hotfix
    PlaceFieldMarker = 0x0371, // updated 5.58 hotfix
    SkillHandler = 0x02DC, // updated 5.58 hotfix
    GMCommand1 = 0x0272, // updated 5.58 hotfix
    GMCommand2 = 0x00E9, // updated 5.58 hotfix
    AoESkillHandler = 0x0152, // updated 5.58 hotfix

    UpdatePositionHandler = 0x01AF, // updated 5.58 hotfix

    InventoryModifyHandler = 0x029E, // updated 5.58 hotfix

    InventoryEquipRecommendedItems = 0x01C9, // updated 5.58 hotfix

    ReqPlaceHousingItem = 0x02D4, // updated 5.58 hotfix
    BuildPresetHandler = 0x0223, // updated 5.58 hotfix

    TalkEventHandler = 0x0387, // updated 5.58 hotfix
    EmoteEventHandler = 0x00B0, // updated 5.58 hotfix
    WithinRangeEventHandler = 0x02B6, // updated 5.58 hotfix
    OutOfRangeEventHandler = 0x03C5, // updated 5.58 hotfix
    EnterTeriEventHandler = 0x01A7, // updated 5.58 hotfix
    ShopEventHandler = 0x0384, // updated 5.58 hotfix
    ReturnEventHandler = 0x00FA, // updated 5.58 hotfix
    TradeReturnEventHandler = 0x0339, // updated 5.58 hotfix
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

    UpdatePositionInstance = 0x00F8, // updated 5.58 hotfix

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
    ChannelChat = 0x0065,
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
    ChannelChatReq = 0x0065,
    PublicContentTellReq = 0x0326, // updated 5.35 hotfix, this is used when sending a /tell in PublicContent instances such as Eureka or Bozja
  };


}
 
#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
