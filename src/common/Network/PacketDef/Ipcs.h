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
    Ping = 0x0183, // updated 5.45 hotfix
    Init = 0x01EA, // updated 5.45 hotfix

    ActorFreeSpawn = 0x0185, // updated 5.45 hotfix
    InitZone = 0x0233, // updated 5.45 hotfix

    EffectResult = 0x01D7, // updated 5.45 hotfix
    ActorControl = 0x00C2, // updated 5.45 hotfix
    ActorControlSelf = 0x03D5, // updated 5.45 hotfix
    ActorControlTarget = 0x0171, // updated 5.45 hotfix

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x019B, // updated 5.45 hotfix

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x0302, // updated 5.45 hotfix
    Logout = 0x012A, // updated 5.45 hotfix
    CFNotify = 0x026E, // updated 5.45 hotfix
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x0145, // updated 5.45 hotfix
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x012E, // updated 5.45 hotfix
    CFCancel = 0x0312, // updated 5.45 hotfix
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x01FB, // updated 5.45 hotfix
    SocialRequestResponse = 0x03A5, // updated 5.45 hotfix
    SocialMessage = 0x030C, // updated 5.45 hotfix
    SocialMessage2 = 0x00BB, // updated 5.45 hotfix
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x01BA, // updated 5.45 hotfix
    PartyChat = 0x0065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x0315, // updated 5.45 hotfix

    ExamineSearchInfo = 0x035F, // updated 5.45 hotfix
    UpdateSearchInfo = 0x0310, // updated 5.45 hotfix
    InitSearchInfo = 0x01ED, // updated 5.45 hotfix
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x03B4, // updated 5.45 hotfix
    ServerNotice = 0x0354, // updated 5.45 hotfix
    SetOnlineStatus = 0x0166, // updated 5.45 hotfix

    CountdownInitiate = 0x0237, // updated 5.25
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x02BD, // updated 5.45 hotfix

    LinkshellList = 0x021A, // updated 5.45 hotfix

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x01D6, // updated 5.45 hotfix
    MarketBoardItemListingCount = 0x00C0, // updated 5.45 hotfix
    MarketBoardItemListingHistory = 0x01C3, // updated 5.45 hotfix
    MarketBoardItemListing = 0x016B, // updated 5.45 hotfix
    
    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0x03D0, // updated 5.45 hotfix
    ExamineFreeCompanyInfo = 0xF13E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x0243, // updated 5.45 hotfix
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x027F, // updated 5.45 hotfix
    AoeEffect8 = 0x009B, // updated 5.45 hotfix
    AoeEffect16 = 0x028C, // updated 5.45 hotfix
    AoeEffect24 = 0x02AD, // updated 5.45 hotfix
    AoeEffect32 = 0x00A7, // updated 5.45 hotfix
    PersistantEffect = 0x0244, // updated 5.45 hotfix

    GCAffiliation = 0x0155, // updated 5.45 hotfix

    PlayerSpawn = 0x01AB, // updated 5.45 hotfix
    NpcSpawn = 0x02C9, // updated 5.45 hotfix
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x006B, // updated 5.45 hotfix

    ActorSetPos = 0x00C6, // updated 5.45 hotfix

    ActorCast = 0x034C, // updated 5.45 hotfix
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x00F5, // updated 5.45 hotfix
    PartyMessage = 0x01BC, // updated 5.45 hotfix
    HateRank = 0x0217, // updated 5.45 hotfix
    HateList = 0x00E5, // updated 5.45 hotfix
    ObjectSpawn = 0x0336, // updated 5.45 hotfix
    ObjectDespawn = 0x02D0, // updated 5.45 hotfix
    UpdateClassInfo = 0x0179, // updated 5.45 hotfix
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x01E9, // updated 5.45 hotfix
    PlayerStats = 0x01CC, // updated 5.45 hotfix
    ActorOwner = 0x0153, // updated 5.45 hotfix
    PlayerStateFlags = 0x02DC, // updated 5.45 hotfix
    PlayerClassInfo = 0x02F0, // updated 5.45 hotfix
    CharaVisualEffect = 0x026A, // updated 5.45 hotfix

    ModelEquip = 0x024A, // updated 5.45 hotfix
    Examine = 0x0261, // updated 5.45 hotfix
    CharaNameReq = 0x0380, // updated 5.45 hotfix

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x020E, // updated 5.21 hotfix
    RetainerInformation = 0x026B, // updated 5.45 hotfix

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x0175, // updated 5.45 hotfix
    ContainerInfo = 0x0193, // updated 5.45 hotfix
    InventoryTransactionFinish = 0x00BD, // updated 5.45 hotfix
    InventoryTransaction = 0x02EE, // updated 5.45 hotfix
    CurrencyCrystalInfo = 0x0363, // updated 5.45 hotfix

    InventoryActionAck = 0x02FA, // updated 5.45 hotfix
    UpdateInventorySlot = 0x017D, // updated 5.45 hotfix

    HuntingLogEntry = 0x0232, // updated 5.45 hotfix

    EventPlay = 0x0276, // updated 5.45 hotfix
    EventPlay4 = 0x028D, // updated 5.45 hotfix
    EventPlay8 = 0x0318, // updated 5.45 hotfix
    EventPlay16 = 0x020D, // updated 5.45 hotfix
    EventPlay32 = 0x03B5, // updated 5.45 hotfix
    EventPlay64 = 0x039E, // updated 5.45 hotfix
    EventPlay128 = 0x02F4, // updated 5.45 hotfix
    EventPlay255 = 0x009D, // updated 5.45 hotfix

    EventYield = 0x0268, // updated 5.45 hotfix
    //EventYield4 = 0x0000,
    //EventYield8 = 0x0000,
    //EventYield16 = 0x0000,
    //EventYield32 = 0x0000,
    //EventYield64 = 0x0000,
    //EventYield128 = 0x0000,
    //EventYield255 = 0x0000,

    EventStart = 0x02DE, // updated 5.45 hotfix
    EventFinish = 0x01A3, // updated 5.45 hotfix

    EventLinkshell = 0x1169,

    QuestActiveList = 0x015A, // updated 5.45 hotfix
    QuestUpdate = 0x037B, // updated 5.45 hotfix
    QuestCompleteList = 0x0287, // updated 5.45 hotfix

    QuestFinish = 0x0066, // updated 5.45 hotfix
    MSQTrackerComplete = 0xF1D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x017B, // updated 5.45 hotfix

    QuestTracker = 0x01E8, // updated 5.45 hotfix

    Mount = 0x0122, // updated 5.45 hotfix

    DirectorVars = 0x0252, // updated 5.45 hotfix
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x0071, // updated 5.45 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0xF162, // updated 5.18 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x0167, // updated 5.45 hotfix
    PlayerTitleList = 0x00F3, // updated 5.45 hotfix
    Discovery = 0x0247, // updated 5.45 hotfix

    EorzeaTimeOffset = 0x00C5, // updated 5.45 hotfix

    EquipDisplayFlags = 0x0316, // updated 5.45 hotfix

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x02FC, // updated 5.45 hotfix
    LootMessage = 0x03B8, // updated 5.45 hotfix
    ResultDialog = 0x0296, // updated 5.45 hotfix
    DesynthResult = 0x0323, // updated 5.45 hotfix

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x03E2, // updated 5.45 hotfix
    LandUpdate = 0x027E, // updated 5.45 hotfix
    YardObjectSpawn = 0x010E, // updated 5.45 hotfix
    HousingIndoorInitialize = 0x01A9, // updated 5.45 hotfix
    LandPriceUpdate = 0x0379, // updated 5.45 hotfix
    LandInfoSign = 0x0398, // updated 5.45 hotfix
    LandRename = 0x00F6, // updated 5.45 hotfix
    HousingEstateGreeting = 0x037D, // updated 5.45 hotfix
    HousingUpdateLandFlagsSlot = 0x03AF, // updated 5.45 hotfix
    HousingLandFlags = 0x033B, // updated 5.45 hotfix
    HousingShowEstateGuestAccess = 0x01B3, // updated 5.45 hotfix

    HousingObjectInitialize = 0x00B5, // updated 5.45 hotfix
    HousingInternalObjectSpawn = 0x00BC, // updated 5.45 hotfix

    HousingWardInfo = 0x015E, // updated 5.45 hotfix
    HousingObjectMove = 0x03E6, // updated 5.45 hotfix

    SharedEstateSettingsResponse = 0x03A4, // updated 5.45 hotfix

    LandUpdateHouseName = 0x0215, // updated 5.45 hotfix

    LandSetMap = 0x0103, // updated 5.45 hotfix

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0248, // updated 5.45 hotfix

    PrepareZoning = 0x01EE, // updated 5.45 hotfix
    ActorGauge = 0x018E, // updated 5.45 hotfix
    DutyGauge = 0x00D2, // updated 5.45 hotfix

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x02C4, // updated 5.45 hotfix
    DailyQuestRepeatFlags = 0x024D, // updated 5.45 hotfix

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

    /// Airship & Submarine //////////////////////////////////////
    AirshipExplorationResult = 0x0131, // updated 5.45 hotfix
    AirshipStatus = 0x0253, // updated 5.45 hotfix
    AirshipStatusList = 0x0391, // updated 5.45 hotfix
    AirshipTimers = 0x0206, // updated 5.45 hotfix
    SubmarineExplorationResult = 0x00EB, // updated 5.45 hotfix
    SubmarineProgressionStatus = 0x0333, // updated 5.45 hotfix
    SubmarineStatusList = 0x01F2, // updated 5.45 hotfix
    SubmarineTimers = 0x013B, // updated 5.45 hotfix
  };

  /**
  * Client IPC Zone Type Codes.
  */
  enum ClientZoneIpcType : uint16_t
  {
    PingHandler = 0x0183, // updated 5.45 hotfix
    InitHandler = 0x01EA, // updated 5.45 hotfix

    FinishLoadingHandler = 0x023F, // updated 5.45 hotfix

    CFCommenceHandler = 0x0118, // updated 5.35 hotfix

    CFCancelHandler = 0x0332, // updated 5.35 hotfix
    CFRegisterDuty = 0x033C, // updated 5.45 hotfix
    CFRegisterRoulette = 0x0121, // updated 5.45 hotfix
    PlayTimeHandler = 0x0096, // updated 5.45 hotfix
    LogoutHandler = 0x0312, // updated 5.45 hotfix
    CancelLogout = 0x0307, // updated 5.45 hotfix

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x0288, // updated 5.45 hotfix
    SocialResponseHandler = 0x029B, // updated 5.45 hotfix
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x00A4, // updated 5.45 hotfix
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0x02EF, // updated 5.45 hotfix
    LeavePartyHandler = 0x017E, // updated 5.45 hotfix
    KickPartyMemberHandler = 0x0070, // updated 5.45 hotfix
    DisbandPartyHandler = 0x037A, // updated 5.45 hotfix

    SocialListHandler = 0x02B0, // updated 5.45 hotfix
    SetSearchInfoHandler = 0x0111, // updated 5.45 hotfix
    ReqSearchInfoHandler = 0x03AC, // updated 5.45 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x02CD, // updated 5.45 hotfix
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x0258, // updated 5.45 hotfix

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

    ZoneLineHandler = 0x00BA, // updated 5.45 hotfix
    ClientTrigger = 0x0146, // updated 5.45 hotfix
    DiscoveryHandler = 0x00E3, // updated 5.35 hotfix

    PlaceFieldMarkerPreset = 0x01D3, // updated 5.45 hotfix
    PlaceFieldMarker = 0x0392, // updated 5.45 hotfix
    SkillHandler = 0x0388, // updated 5.45 hotfix
    GMCommand1 = 0x01E0, // updated 5.45 hotfix
    GMCommand2 = 0x0114, // updated 5.45 hotfix
    AoESkillHandler = 0x03A0, // updated 5.45 hotfix

    UpdatePositionHandler = 0x031A, // updated 5.45 hotfix

    InventoryModifyHandler = 0x0110, // updated 5.45 hotfix
    
    InventoryEquipRecommendedItems = 0x0186, // updated 5.45 hotfix

    ReqPlaceHousingItem = 0x0360, // updated 5.45 hotfix
    BuildPresetHandler = 0x01D7, // updated 5.45 hotfix

    TalkEventHandler = 0x00C2, // updated 5.45 hotfix
    EmoteEventHandler = 0x03D5, // updated 5.45 hotfix
    WithinRangeEventHandler = 0x0171, // updated 5.45 hotfix
    OutOfRangeEventHandler = 0x019B, // updated 5.45 hotfix
    EnterTeriEventHandler = 0x027F, // updated 5.45 hotfix
    ShopEventHandler = 0x03D4, // updated 5.45 hotfix
    EventYieldHandler = 0x0230, // updated 5.45 hotfix
    ReturnEventHandler = 0x02AD, // updated 5.45 hotfix
    TradeReturnEventHandler = 0x00A7, // updated 5.45 hotfix
    TradeMultipleReturnEventHander = 0x035C, // updated 5.35 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x03B0, // updated 5.45 hotfix

    LandRenameHandler = 0x0187, // updated 5.45 hotfix
    HousingUpdateHouseGreeting = 0x0367, // updated 5.45 hotfix
    HousingUpdateObjectPosition = 0x0265, // updated 5.45 hotfix
    HousingEditExterior = 0x0297, // updated 5.45 hotfix

    SetSharedEstateSettings = 0x0146, // updated 5.45 hotfix

    UpdatePositionInstance = 0x034E, // updated 5.45 hotfix

    PerformNoteHandler = 0x0336, // updated 5.45 hotfix

    WorldInteractionHandler = 0x02E4, // updated 5.45 hotfix
    Dive = 0x00F1, // updated 5.45 hotfix
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
