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
    Ping = 0x0289, // updated 5.55 hotfix
    Init = 0x0203, // updated 5.55 hotfix

    ActorFreeSpawn = 0x0210, // updated 5.58 diff
    InitZone = 0x0100, // updated 5.58

    EffectResult = 0x0151, // updated 5.58
    ActorControl = 0x0264, // updated 5.58
    ActorControlSelf = 0x0314, // updated 5.58
    ActorControlTarget = 0x00FC, // updated 5.58

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x039B, // updated 5.58

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x02BE, // updated 5.58
    Logout = 0x0297, // updated 5.58
    CFNotify = 0x01AC, // updated 5.58
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x0083, // updated 5.58 diff
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x02FB, // updated 5.58 diff
    CFCancel = 0x0135, // updated 5.58 diff
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x037E, // updated 5.58 diff
    SocialRequestResponse = 0x0254, // updated 5.58 diff
    SocialMessage = 0x02F2, // updated 5.58 diff
    SocialMessage2 = 0x017A, // updated 5.58 diff
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x0220, // updated 5.58 diff
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x0396, // updated 5.58 diff

    ExamineSearchInfo = 0x031F, // updated 5.58
    UpdateSearchInfo = 0x0219, // updated 5.58
    InitSearchInfo = 0x01A0, // updated 5.58 diff
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x0211, // updated 5.58 diff
    ServerNotice = 0x03B9, // updated 5.58 diff
    SetOnlineStatus = 0x0163, // updated 5.58 diff

    CountdownInitiate = 0x0237, // updated 5.25
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x028A, // updated 5.58 diff

    LinkshellList = 0x02DD, // updated 5.58 diff

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x0355, // updated 5.58
    MarketBoardItemListingCount = 0x0275, // updated 5.58
    MarketBoardItemListingHistory = 0x0112, // updated 5.58
    MarketBoardItemListing = 0x00F5, // updated 5.58
    
    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0x0346, // updated 5.58
    ExamineFreeCompanyInfo = 0xF13E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x01C5, // updated 5.58
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x0102, // updated 5.58
    AoeEffect8 = 0x0345, // updated 5.58 diff
    AoeEffect16 = 0x02B6, // updated 5.58 diff
    AoeEffect24 = 0x0298, // updated 5.58 diff
    AoeEffect32 = 0x03A4, // updated 5.58 diff
    PersistantEffect = 0x008D, // updated 5.58 diff

    GCAffiliation = 0x02B1, // updated 5.58 diff

    PlayerSpawn = 0x0249, // updated 5.58
    NpcSpawn = 0x014B, // updated 5.58
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x023D, // updated 5.58

    ActorSetPos = 0x0280, // updated 5.58

    ActorCast = 0x02A7, // updated 5.58
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x02BD, // updated 5.58 diff
    PartyMessage = 0x0318, // updated 5.58 diff
    HateRank = 0x02C0, // updated 5.58 diff
    HateList = 0x01B4, // updated 5.58 diff
    ObjectSpawn = 0x0104, // updated 5.58
    ObjectDespawn = 0x030D, // updated 5.58 diff
    UpdateClassInfo = 0x0198, // updated 5.58
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0296, // updated 5.58
    PlayerStats = 0x00D5, // updated 5.58
    ActorOwner = 0x00AE, // updated 5.58 diff
    PlayerStateFlags = 0x022A, // updated 5.58 diff
    PlayerClassInfo = 0x02DF, // updated 5.58 diff
    CharaVisualEffect = 0x0134, // updated 5.58 diff

    ModelEquip = 0x0312, // updated 5.58 diff
    Examine = 0x00D3, // updated 5.58
    CharaNameReq = 0x031C, // updated 5.58 diff

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x020E, // updated 5.21 hotfix
    RetainerInformation = 0x0069, // updated 5.58

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x00A7, // updated 5.58
    ContainerInfo = 0x0208, // updated 5.58
    InventoryTransactionFinish = 0x01A3, // updated 5.58
    InventoryTransaction = 0x03AC, // updated 5.58
    CurrencyCrystalInfo = 0x0394, // updated 5.58

    InventoryActionAck = 0x0305, // updated 5.58
    UpdateInventorySlot = 0x0200, // updated 5.58

    HuntingLogEntry = 0x00C5, // updated 5.58 diff

    EventPlay = 0x01EF, // updated 5.58
    EventPlay4 = 0x021C, // updated 5.58
    EventPlay8 = 0x0337, // updated 5.58
    EventPlay16 = 0x0319, // updated 5.58
    EventPlay32 = 0x01E2, // updated 5.58
    EventPlay64 = 0x02FD, // updated 5.58
    EventPlay128 = 0x026E, // updated 5.58
    EventPlay255 = 0x039E, // updated 5.58

    EventYield = 0x02CB, // updated 5.55 hotfix
    //EventYield4 = 0x0000,
    //EventYield8 = 0x0000,
    //EventYield16 = 0x0000,
    //EventYield32 = 0x0000,
    //EventYield64 = 0x0000,
    //EventYield128 = 0x0000,
    //EventYield255 = 0x0000,

    EventStart = 0x01CC, // updated 5.58
    EventFinish = 0x0180, // updated 5.58

    EventLinkshell = 0x1169,

    QuestActiveList = 0x035D, // updated 5.58 diff
    QuestUpdate = 0x029A, // updated 5.58 diff
    QuestCompleteList = 0x03C5, // updated 5.58 diff

    QuestFinish = 0x0274, // updated 5.58 diff
    MSQTrackerComplete = 0xF1D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x036E, // updated 5.55 hotfix

    QuestTracker = 0x038E, // updated 5.58 diff

    Mount = 0x03C2, // updated 5.58 diff

    DirectorVars = 0x01ED, // updated 5.58 diff
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x01BD, // updated 5.58
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0xF162, // updated 5.18 (could be 0x02C2 in 5.55, needs confirmation - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x01B1, // updated 5.58
    PlayerTitleList = 0x018C, // updated 5.58 diff
    Discovery = 0x00B8, // updated 5.58 diff

    EorzeaTimeOffset = 0x03D9, // updated 5.58 diff

    EquipDisplayFlags = 0x0199, // updated 5.58 diff

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0162, // updated 5.55 hotfix
    LootMessage = 0x038C, // updated 5.58 diff
    ResultDialog = 0x00DF, // updated 5.58
    DesynthResult = 0x038F, // updated 5.58

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x03E3, // updated 5.58 diff
    LandUpdate = 0x029E, // updated 5.58 diff
    YardObjectSpawn = 0x0367, // updated 5.58 diff
    HousingIndoorInitialize = 0x02A6, // updated 5.58 diff
    LandPriceUpdate = 0x0143, // updated 5.58 diff
    LandInfoSign = 0x0269, // updated 5.58 diff
    LandRename = 0x0107, // updated 5.58 diff
    HousingEstateGreeting = 0x0340, // updated 5.58 diff
    HousingUpdateLandFlagsSlot = 0x02D2, // updated 5.58 diff
    HousingLandFlags = 0x0156, // updated 5.58 diff
    HousingShowEstateGuestAccess = 0x015C, // updated 5.58 diff

    HousingObjectInitialize = 0x0245, // updated 5.58 diff
    HousingInternalObjectSpawn = 0x0194, // updated 5.58 diff

    HousingWardInfo = 0x00A4, // updated 5.58
    HousingObjectMove = 0x01AE, // updated 5.58 diff

    SharedEstateSettingsResponse = 0x01E9, // updated 5.58 diff

    LandUpdateHouseName = 0x034B, // updated 5.58 diff

    LandSetMap = 0x02F6, // updated 5.58 diff

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x00BE, // updated 5.58 diff

    PrepareZoning = 0x0171, // updated 5.58
    ActorGauge = 0x0335, // updated 5.58
    DutyGauge = 0x02F6, // updated 5.58 diff

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0331, // updated 5.58 diff
    DailyQuestRepeatFlags = 0x01D1, // updated 5.58 diff

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
    AirshipExplorationResult = 0x036C, // updated 5.58
    AirshipStatus = 0x021F, // updated 5.58
    AirshipStatusList = 0x0073, // updated 5.58
    AirshipTimers = 0x0250, // updated 5.58
    SubmarineExplorationResult = 0x01D0, // updated 5.58
    SubmarineProgressionStatus = 0x03C0, // updated 5.58
    SubmarineStatusList = 0x0338, // updated 5.58
    SubmarineTimers = 0x0292, // updated 5.58
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x03AD, // updated 5.55 hotfix
    InitHandler = 0x03DA, // updated 5.55 hotfix

    FinishLoadingHandler = 0x0203, // updated 5.55 hotfix

    CFCommenceHandler = 0xF118, // updated 5.35 hotfix

    CFCancelHandler = 0x0332, // updated 5.35 hotfix
    CFRegisterDuty = 0x033C, // updated 5.45 hotfix
    CFRegisterRoulette = 0x0121, // updated 5.45 hotfix
    PlayTimeHandler = 0x0365, // updated 5.55 hotfix
    LogoutHandler = 0x039B, // updated 5.55 hotfix
    CancelLogout = 0x010F, // updated 5.55 hotfix
    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialReqSendHandler = 0x028E, // updated 5.55 hotfix
    SocialResponseHandler = 0x0373, // updated 5.55 hotfix
    CreateCrossWorldLS = 0x028D, // updated 5.55 hotfix

    ChatHandler = 0x02F4, // updated 5.58
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x0142, // updated 5.55 hotfix
    LeavePartyHandler = 0x026C, // updated 5.55 hotfix
    KickPartyMemberHandler = 0x0379, // updated 5.55 hotfix
    DisbandPartyHandler = 0x037A, // updated 5.45 hotfix

    SocialListHandler = 0x00F2, // updated 5.55 hotfix
    SetSearchInfoHandler = 0x010A, // updated 5.58
    ReqSearchInfoHandler = 0x00B1, // updated 5.55 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x03DE, // updated 5.55 hotfix
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x0291, // updated 5.55 hotfix

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

    ZoneLineHandler = 0x01C2, // updated 5.55 hotfix
    ClientTrigger = 0x008B, // updated 5.58
    DiscoveryHandler = 0x00E3, // updated 5.35 hotfix

    PlaceFieldMarkerPreset = 0x03B0, // updated 5.58
    PlaceFieldMarker = 0x011A, // updated 5.58
    SkillHandler = 0x02A2, // updated 5.55 hotfix
    GMCommand1 = 0x01F0, // updated 5.55 hotfix
    GMCommand2 = 0x0068, // updated 5.55 hotfix
    AoESkillHandler = 0x02F6, // updated 5.55 hotfix

    UpdatePositionHandler = 0x0212, // updated 5.58

    InventoryModifyHandler = 0x014A, // updated 5.58
    
    InventoryEquipRecommendedItems = 0x0186, // updated 5.45 hotfix

    ReqPlaceHousingItem = 0x023E, // updated 5.55 hotfix
    BuildPresetHandler = 0x0374, // updated 5.55 hotfix

    TalkEventHandler = 0x01E9, // updated 5.55 hotfix
    EmoteEventHandler = 0xF35A, // updated 5.55 hotfix
    WithinRangeEventHandler = 0x035A, // updated 5.55 hotfix
    OutOfRangeEventHandler = 0x0338, // updated 5.55 hotfix
    EnterTeriEventHandler = 0x0077, // updated 5.55 hotfix
    ShopEventHandler = 0x0168, // updated 5.55 hotfix
    EventYieldHandler = 0x02A0, // updated 5.55 hotfix
    ReturnEventHandler = 0x015D, // updated 5.55 hotfix
    TradeReturnEventHandler = 0x0091, // updated 5.55 hotfix
    TradeReturnEventHandler2 = 0x0169, // updated 5.55 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x032B, // updated 5.55 hotfix

    LandRenameHandler = 0x0206, // updated 5.55 hotfix
    HousingUpdateHouseGreeting = 0x0330, // updated 5.55 hotfix
    HousingUpdateObjectPosition = 0x03A5, // updated 5.55 hotfix
    HousingEditAppearance = 0x00D7, // updated 5.55 hotfix

    SetSharedEstateSettings = 0x03DC, // updated 5.55 hotfix

    UpdatePositionInstance = 0x01A3, // updated 5.58

    PerformNoteHandler = 0x01F1, // updated 5.55 hotfix

    WorldInteractionHandler = 0x0343, // updated 5.55 hotfix
    Dive = 0x021C, // updated 5.55 hotfix
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
