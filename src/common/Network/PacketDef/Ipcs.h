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
    Ping = 0x02CB, // updated 5.58
    Init = 0x02A8, // updated 5.58

    ActorFreeSpawn = 0x0210, // updated 5.58
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
    CFDutyInfo = 0x0083, // updated 5.58
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x02FB, // updated 5.58
    CFCancel = 0x0135, // updated 5.58
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x037E, // updated 5.58
    SocialRequestResponse = 0x0254, // updated 5.58
    SocialMessage = 0x02F2, // updated 5.58
    SocialMessage2 = 0x017A, // updated 5.58
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x020F, // updated 5.58

    Chat = 0x0220, // updated 5.58
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x0396, // updated 5.58

    ExamineSearchInfo = 0x031F, // updated 5.58
    UpdateSearchInfo = 0x0219, // updated 5.58
    InitSearchInfo = 0x01A0, // updated 5.58
    ExamineSearchComment = 0x0315, // updated 5.58

    ServerNoticeShort = 0x0211, // updated 5.58
    ServerNotice = 0x03B9, // updated 5.58
    SetOnlineStatus = 0x0163, // updated 5.58

    CountdownInitiate = 0x01F9, // updated 5.58
    CountdownCancel = 0x0206, // updated 5.58

    PlayerAddedToBlacklist = 0x01FE, // updated 5.58
    PlayerRemovedFromBlacklist = 0x02D6, // updated 5.58
    BlackList = 0x028A, // updated 5.58

    LinkshellList = 0x02DD, // updated 5.58

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
    FreeCompanyBoardMsg = 0x028D, // updated 5.58
    FreeCompanyInfo = 0x0346, // updated 5.58
    ExamineFreeCompanyInfo = 0x00B7, // updated 5.58

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x01C5, // updated 5.58
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x0102, // updated 5.58
    AoeEffect8 = 0x0345, // updated 5.58
    AoeEffect16 = 0x02B6, // updated 5.58
    AoeEffect24 = 0x0298, // updated 5.58
    AoeEffect32 = 0x03A4, // updated 5.58
    PersistantEffect = 0x008D, // updated 5.58

    GCAffiliation = 0x02B1, // updated 5.58

    PlayerSpawn = 0x0249, // updated 5.58
    NpcSpawn = 0x014B, // updated 5.58
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x023D, // updated 5.58

    ActorSetPos = 0x0280, // updated 5.58

    ActorCast = 0x02A7, // updated 5.58
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x02BD, // updated 5.58
    PartyMessage = 0x0318, // updated 5.58
    HateRank = 0x02C0, // updated 5.58
    HateList = 0x01B4, // updated 5.58
    ObjectSpawn = 0x0104, // updated 5.58
    ObjectDespawn = 0x030D, // updated 5.58
    UpdateClassInfo = 0x0198, // updated 5.58
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0296, // updated 5.58
    PlayerStats = 0x00D5, // updated 5.58
    ActorOwner = 0x00AE, // updated 5.58
    PlayerStateFlags = 0x022A, // updated 5.58
    PlayerClassInfo = 0x02DF, // updated 5.58
    CharaVisualEffect = 0x0134, // updated 5.58

    ModelEquip = 0x0312, // updated 5.58
    Examine = 0x00D3, // updated 5.58
    CharaNameReq = 0x031C, // updated 5.58

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x01D3, // updated 5.58
    RetainerInformation = 0x0069, // updated 5.58

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x00A7, // updated 5.58
    ContainerInfo = 0x0208, // updated 5.58
    InventoryTransactionFinish = 0x01A3, // updated 5.58
    InventoryTransaction = 0x03AC, // updated 5.58
    CurrencyCrystalInfo = 0x0394, // updated 5.58

    InventoryActionAck = 0x0305, // updated 5.58
    UpdateInventorySlot = 0x0200, // updated 5.58

    HuntingLogEntry = 0x00C5, // updated 5.58

    EventPlay = 0x01EF, // updated 5.58
    EventPlay4 = 0x021C, // updated 5.58
    EventPlay8 = 0x0337, // updated 5.58
    EventPlay16 = 0x0319, // updated 5.58
    EventPlay32 = 0x01E2, // updated 5.58
    EventPlay64 = 0x02FD, // updated 5.58
    EventPlay128 = 0x026E, // updated 5.58
    EventPlay255 = 0x039E, // updated 5.58

    EventYield = 0x0123, // updated 5.58
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

    QuestActiveList = 0x035D, // updated 5.58
    QuestUpdate = 0x029A, // updated 5.58
    QuestCompleteList = 0x03C5, // updated 5.58

    QuestFinish = 0x0274, // updated 5.58
    MSQTrackerComplete = 0x01C1, // updated 5.58
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0128, // updated 5.58

    QuestTracker = 0x038E, // updated 5.58

    Mount = 0x03C2, // updated 5.58

    DirectorVars = 0x01ED, // updated 5.58
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x01BD, // updated 5.58
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x02E3, // updated 5.58
    DirectorPopUp4 = 0x01DC, // updated 5.58
    DirectorPopUp8 = 0x011D, // updated 5.58

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x01B1, // updated 5.58
    PlayerTitleList = 0x02B4, // updated 5.58
    Discovery = 0x00B8, // updated 5.58

    EorzeaTimeOffset = 0x03D9, // updated 5.58

    EquipDisplayFlags = 0x0199, // updated 5.58

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x00D0, // updated 5.58
    LootMessage = 0x038C, // updated 5.58
    ResultDialog = 0x00DF, // updated 5.58
    DesynthResult = 0x038F, // updated 5.58

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x03E3, // updated 5.58
    LandUpdate = 0x029E, // updated 5.58
    YardObjectSpawn = 0x0367, // updated 5.58
    HousingIndoorInitialize = 0x02A6, // updated 5.58
    LandPriceUpdate = 0x0143, // updated 5.58
    LandInfoSign = 0x0269, // updated 5.58
    LandRename = 0x0107, // updated 5.58
    HousingEstateGreeting = 0x0340, // updated 5.58
    HousingUpdateLandFlagsSlot = 0x02D2, // updated 5.58
    HousingLandFlags = 0x0156, // updated 5.58
    HousingShowEstateGuestAccess = 0x015C, // updated 5.58

    HousingObjectInitialize = 0x0245, // updated 5.58
    HousingInternalObjectSpawn = 0x0194, // updated 5.58

    HousingWardInfo = 0x00A4, // updated 5.58
    HousingObjectMove = 0x01AE, // updated 5.58

    SharedEstateSettingsResponse = 0x0378, // updated 5.58

    LandUpdateHouseName = 0x034B, // updated 5.58

    LandSetMap = 0x02F6, // updated 5.58

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x00BE, // updated 5.58

    PrepareZoning = 0x0171, // updated 5.58
    ActorGauge = 0x0335, // updated 5.58
    DutyGauge = 0x02F6, // updated 5.58

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0331, // updated 5.58
    DailyQuestRepeatFlags = 0x01D1, // updated 5.58

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
    SubmarineProgressionStatus = 0x0377, // updated 5.58
    SubmarineStatusList = 0x0338, // updated 5.58
    SubmarineTimers = 0x0292, // updated 5.58
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x03A3, // updated 5.58
    InitHandler = 0x03B3, // updated 5.58

    FinishLoadingHandler = 0x0217, // updated 5.58

    CFCommenceHandler = 0xF118, // updated 5.35 hotfix

    CFCancelHandler = 0x00A9, // updated 5.58
    CFRegisterDuty = 0x036A, // updated 5.58
    CFRegisterRoulette = 0x038C, // updated 5.58
    PlayTimeHandler = 0x01A8, // updated 5.58
    LogoutHandler = 0x02A5, // updated 5.58
    CancelLogout = 0x03CC, // updated 5.58
    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialReqSendHandler = 0x0366, // updated 5.58
    SocialResponseHandler = 0x0311, // updated 5.58
    CreateCrossWorldLS = 0x0125, // updated 5.58

    ChatHandler = 0x02F4, // updated 5.58
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x03C2, // updated 5.58
    LeavePartyHandler = 0x028A, // updated 5.58
    KickPartyMemberHandler = 0x01D1, // updated 5.58
    DisbandPartyHandler = 0x032B, // updated 5.58

    SocialListHandler = 0x006E, // updated 5.58
    SetSearchInfoHandler = 0x010A, // updated 5.58
    ReqSearchInfoHandler = 0x0255, // updated 5.58
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x015A, // updated 5.58
    BlackListHandler = 0x02C5, // updated 5.58
    PlayerSearchHandler = 0x0259, // updated 5.58

    LinkshellListHandler = 0x01F0, // updated 5.58

    MarketBoardRequestItemListingInfo = 0x02D3, // updated 5.58
    MarketBoardRequestItemListings = 0x00AD, // updated 5.58
    MarketBoardSearch = 0x00D6, // updated 5.58

    ReqExamineFcInfo = 0x0359, // updated 5.58

    FcInfoReqHandler = 0x0078, // updated 5.58

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x0364, // updated 5.58

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x020E, // updated 5.58
    ReqCountdownCancel = 0x03BE, // updated 5.58

    ZoneLineHandler = 0x00B0, // updated 5.58
    ClientTrigger = 0x008B, // updated 5.58
    DiscoveryHandler = 0x01B4, // updated 5.58

    PlaceFieldMarkerPreset = 0x03B0, // updated 5.58
    PlaceFieldMarker = 0x011A, // updated 5.58
    SkillHandler = 0x0175, // updated 5.58
    GMCommand1 = 0x0353, // updated 5.58
    GMCommand2 = 0x03E7, // updated 5.58
    AoESkillHandler = 0x021D, // updated 5.58

    UpdatePositionHandler = 0x0212, // updated 5.58

    InventoryModifyHandler = 0x014A, // updated 5.58
    
    InventoryEquipRecommendedItems = 0x01D7, // updated 5.58

    ReqPlaceHousingItem = 0x0354, // updated 5.58
    BuildPresetHandler = 0x00DC, // updated 5.58

    TalkEventHandler = 0x012D, // updated 5.58
    EmoteEventHandler = 0xF35A, // updated 5.55 hotfix
    WithinRangeEventHandler = 0x022C, // updated 5.58
    OutOfRangeEventHandler = 0x0294, // updated 5.58
    EnterTeriEventHandler = 0x00C1, // updated 5.58
    ShopEventHandler = 0x02B8, // updated 5.58
    EventYieldHandler = 0x03A2, // updated 5.58
    ReturnEventHandler = 0x0333, // updated 5.58
    TradeReturnEventHandler = 0x0179, // updated 5.58
    TradeReturnEventHandler2 = 0x0169, // updated 5.55 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x01AD, // updated 5.58

    LandRenameHandler = 0x0083, // updated 5.58
    HousingUpdateHouseGreeting = 0x031A, // updated 5.58
    HousingUpdateObjectPosition = 0x010E, // updated 5.58
    HousingEditExterior = 0x0324, // updated 5.58
    HousingEditInterior = 0x02F7, // updated 5.58

    SetSharedEstateSettings = 0x0342, // updated 5.58

    UpdatePositionInstance = 0x01A3, // updated 5.58

    PerformNoteHandler = 0x015E, // updated 5.58

    WorldInteractionHandler = 0x03CE, // updated 5.58
    Dive = 0x034C, // updated 5.58
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
