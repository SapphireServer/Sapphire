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

    ActorFreeSpawn = 0x01C5, // updated 5.55 hotfix
    InitZone = 0x021C, // updated 5.55 hotfix diff

    EffectResult = 0x01E9, // updated 5.55 hotfix diff
    ActorControl = 0x01C8, // updated 5.55 hotfix diff
    ActorControlSelf = 0x035A, // updated 5.55 hotfix diff
    ActorControlTarget = 0x0338, // updated 5.55 hotfix diff

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x0077, // updated 5.55 hotfix diff

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x0348, // updated 5.55 hotfix diff
    Logout = 0x0292, // updated 5.55 hotfix diff
    CFNotify = 0x00DC, // updated 5.55 hotfix diff
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x02A3, // updated 5.55 hotfix diff
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x02B6, // updated 5.55 hotfix diff
    CFCancel = 0x01BE, // updated 5.55 hotfix diff
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x0114, // updated 5.55 hotfix diff
    SocialRequestResponse = 0x033C, // updated 5.55 hotfix diff
    SocialMessage = 0x0304, // updated 5.55 hotfix diff
    SocialMessage2 = 0x01B4, // updated 5.55 hotfix diff
    CancelAllianceForming = 0xF0C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x0384, // updated 5.55 hotfix diff
    PartyChat = 0xF065,

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x00DD, // updated 5.55 hotfix diff

    ExamineSearchInfo = 0x022A, // updated 5.55 hotfix diff
    UpdateSearchInfo = 0x03DF, // updated 5.55 hotfix diff
    InitSearchInfo = 0x00F8, // updated 5.55 hotfix diff
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x032D, // updated 5.55 hotfix diff
    ServerNotice = 0x02CA, // updated 5.55 hotfix
    SetOnlineStatus = 0x03A9, // updated 5.55 hotfix diff

    CountdownInitiate = 0x0237, // updated 5.25
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x0093, // updated 5.55 hotfix diff

    LinkshellList = 0x0160, // updated 5.55 hotfix diff

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0xF138, // updated 5.0
    ReqMoogleMailLetter = 0xF139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x01F8, // updated 5.35 hotfix

    MarketBoardSearchResult = 0x039D, // updated 5.55 hotfix diff
    MarketBoardItemListingCount = 0x0277, // updated 5.55 hotfix diff
    MarketBoardItemListingHistory = 0x0320, // updated 5.55 hotfix diff
    MarketBoardItemListing = 0x026B, // updated 5.55 hotfix diff
    
    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0x0332, // updated 5.55 hotfix
    ExamineFreeCompanyInfo = 0xF13E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x018A, // updated 5.55 hotfix diff
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x0283, // updated 5.55 hotfix diff
    AoeEffect8 = 0x025B, // updated 5.55 hotfix diff
    AoeEffect16 = 0x015D, // updated 5.55 hotfix diff
    AoeEffect24 = 0x0091, // updated 5.55 hotfix diff
    AoeEffect32 = 0x0169, // updated 5.55 hotfix diff
    PersistantEffect = 0x035E, // updated 5.55 hotfix diff

    GCAffiliation = 0x0258, // updated 5.55 hotfix diff

    PlayerSpawn = 0x02C1, // updated 5.55 hotfix diff
    NpcSpawn = 0x00F1, // updated 5.55 hotfix diff
    NpcSpawn2 = 0x01CB, // ( Bigger statuseffectlist? ) updated 5.3
    ActorMove = 0x009D, // updated 5.55 hotfix diff

    ActorSetPos = 0x0266, // updated 5.55 hotfix diff

    ActorCast = 0x00A9, // updated 5.55 hotfix diff
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x01B7, // updated 5.55 hotfix diff
    PartyMessage = 0x01C1, // updated 5.55 hotfix diff
    HateRank = 0x006E, // updated 5.55 hotfix diff
    HateList = 0x01F1, // updated 5.55 hotfix diff
    ObjectSpawn = 0x00FE, // updated 5.55 hotfix diff
    ObjectDespawn = 0x0201, // updated 5.55 hotfix diff
    UpdateClassInfo = 0x0065, // updated 5.55 hotfix
    SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x01E7, // updated 5.55 hotfix diff
    PlayerStats = 0x012E, // updated 5.55 hotfix diff
    ActorOwner = 0x00EB, // updated 5.55 hotfix diff
    PlayerStateFlags = 0x0190, // updated 5.55 hotfix diff
    PlayerClassInfo = 0x022B, // updated 5.55 hotfix diff
    CharaVisualEffect = 0x033A, // updated 5.55 hotfix diff

    ModelEquip = 0x0264, // updated 5.55 hotfix diff
    Examine = 0x027C, // updated 5.55 hotfix diff
    CharaNameReq = 0x02EC, // updated 5.55 hotfix diff

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
    RetainerSaleHistory = 0x020E, // updated 5.21 hotfix
    RetainerInformation = 0x02DE, // updated 5.55 hotfix

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x02D3, // updated 5.55 hotfix
    ContainerInfo = 0x00CF, // updated 5.55 hotfix
    InventoryTransactionFinish = 0x02EE, // updated 5.55 hotfix
    InventoryTransaction = 0x02FA, // updated 5.55 hotfix
    CurrencyCrystalInfo = 0x0166, // updated 5.55 hotfix

    InventoryActionAck = 0x027D, // updated 5.55 hotfix diff
    UpdateInventorySlot = 0x0073, // updated 5.55 hotfix diff

    HuntingLogEntry = 0x0080, // updated 5.55 hotfix diff

    EventPlay = 0x0369, // updated 5.55 hotfix
    EventPlay4 = 0x0247, // updated 5.55 hotfix
    EventPlay8 = 0x0227, // updated 5.55 hotfix
    EventPlay16 = 0x00C5, // updated 5.55 hotfix
    EventPlay32 = 0x0184, // updated 5.55 hotfix
    EventPlay64 = 0x011A, // updated 5.55 hotfix
    EventPlay128 = 0x01B3, // updated 5.55 hotfix
    EventPlay255 = 0x0240, // updated 5.55 hotfix

    EventYield = 0x02CB, // updated 5.55 hotfix diff
    //EventYield4 = 0x0000,
    //EventYield8 = 0x0000,
    //EventYield16 = 0x0000,
    //EventYield32 = 0x0000,
    //EventYield64 = 0x0000,
    //EventYield128 = 0x0000,
    //EventYield255 = 0x0000,

    EventStart = 0x0145, // updated 5.55 hotfix diff
    EventFinish = 0x0174, // updated 5.55 hotfix diff

    EventLinkshell = 0x1169,

    QuestActiveList = 0x0381, // updated 5.55 hotfix diff
    QuestUpdate = 0x031B, // updated 5.55 hotfix diff
    QuestCompleteList = 0x031A, // updated 5.55 hotfix diff

    QuestFinish = 0x00E0, // updated 5.55 hotfix diff
    MSQTrackerComplete = 0xF1D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x036E, // updated 5.55 hotfix diff

    QuestTracker = 0x0294, // updated 5.55 hotfix diff

    Mount = 0x016B, // updated 5.55 hotfix diff

    DirectorVars = 0x0391, // updated 5.55 hotfix diff
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x0101, // updated 5.55 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0xF162, // updated 5.18 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x0386, // updated 5.55 hotfix diff
    PlayerTitleList = 0x0181, // updated 5.55 hotfix diff
    Discovery = 0x019E, // updated 5.55 hotfix diff

    EorzeaTimeOffset = 0x01AE, // updated 5.55 hotfix diff

    EquipDisplayFlags = 0x01C5, // updated 5.55 hotfix diff

    MiniCactpotInit = 0x0286, // added 5.31
    ShopMessage = 0x0162, // updated 5.55 hotfix diff
    LootMessage = 0x0065, // updated 5.55 hotfix diff
    ResultDialog = 0x025D, // updated 5.55 hotfix
    DesynthResult = 0x0323, // updated 5.55 hotfix

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x01E4, // updated 5.55 hotfix
    LandUpdate = 0xF1E4, // updated 5.55 hotfix diff
    YardObjectSpawn = 0x0219, // updated 5.55 hotfix diff
    HousingIndoorInitialize = 0x00EE, // updated 5.55 hotfix diff
    LandPriceUpdate = 0x00EE, // updated 5.55 hotfix diff
    LandInfoSign = 0x02D9, // updated 5.55 hotfix diff
    LandRename = 0x02D9, // updated 5.55 hotfix diff
    HousingEstateGreeting = 0x011C, // updated 5.55 hotfix diff
    HousingUpdateLandFlagsSlot = 0x03C8, // updated 5.55 hotfix diff
    HousingLandFlags = 0x037E, // updated 5.55 hotfix
    HousingShowEstateGuestAccess = 0xF25F, // updated 5.55 hotfix diff

    HousingObjectInitialize = 0x0331, // updated 5.55 hotfix
    HousingInternalObjectSpawn = 0x0084, // updated 5.55 hotfix diff

    HousingWardInfo = 0x0234, // updated 5.55 hotfix diff
    HousingObjectMove = 0x0234, // updated 5.55 hotfix diff

    SharedEstateSettingsResponse = 0x0263, // updated 5.55 hotfix diff

    LandUpdateHouseName = 0x01C6, // updated 5.55 hotfix diff

    LandSetMap = 0x00EE, // updated 5.55 hotfix diff

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x038B, // updated 5.55 hotfix diff

    PrepareZoning = 0x00A4, // updated 5.55 hotfix
    ActorGauge = 0x03B1, // updated 5.55 hotfix
    DutyGauge = 0x01D3, // updated 5.55 hotfix diff

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0371, // updated 5.55 hotfix diff
    DailyQuestRepeatFlags = 0x021F, // updated 5.55 hotfix diff

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
    AirshipExplorationResult = 0x007C, // updated 5.55 hotfix
    AirshipStatus = 0x00AB, // updated 5.55 hotfix
    AirshipStatusList = 0x027B, // updated 5.55 hotfix
    AirshipTimers = 0x02A5, // updated 5.55 hotfix diff
    SubmarineExplorationResult = 0x0099, // updated 5.55 hotfix
    SubmarineProgressionStatus = 0x0081, // updated 5.55 hotfix diff
    SubmarineStatusList = 0x0072, // updated 5.55 hotfix diff
    SubmarineTimers = 0x037A, // updated 5.55 hotfix
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

    CFCancelHandler = 0xF332, // updated 5.35 hotfix
    CFRegisterDuty = 0xF33C, // updated 5.45 hotfix
    CFRegisterRoulette = 0xF121, // updated 5.45 hotfix
    PlayTimeHandler = 0xF365, // updated 5.55 hotfix diff
    LogoutHandler = 0x039B, // updated 5.55 hotfix
    CancelLogout = 0xF10F, // updated 5.55 hotfix diff

    CFDutyInfoHandler = 0xF078, // updated 4.2

    SocialReqSendHandler = 0xF1B1, // updated 5.55 hotfix diff
    SocialResponseHandler = 0xF29B, // updated 5.45 hotfix
    CreateCrossWorldLS = 0xF0AF, // updated 4.3

    ChatHandler = 0x01B8, // updated 5.55 hotfix
    PartyChatHandler = 0x0065,
    PartySetLeaderHandler = 0xF2EF, // updated 5.45 hotfix
    LeavePartyHandler = 0x01A4, // updated 5.55 hotfix diff
    KickPartyMemberHandler = 0xF070, // updated 5.45 hotfix
    DisbandPartyHandler = 0xF37A, // updated 5.45 hotfix

    SocialListHandler = 0x00F2, // updated 5.55 hotfix
    SetSearchInfoHandler = 0x009C, // updated 5.55 hotfix
    ReqSearchInfoHandler = 0x00B1, // updated 5.55 hotfix
    ReqExamineSearchCommentHandler = 0xF0E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0xF0F1, // updated 5.0
    BlackListHandler = 0x03DE, // updated 5.55 hotfix
    PlayerSearchHandler = 0xF0F4, // updated 5.0

    LinkshellListHandler = 0x0291, // updated 5.55 hotfix

    MarketBoardRequestItemListingInfo = 0xF102, // updated 4.5
    MarketBoardRequestItemListings = 0xF103, // updated 4.5
    MarketBoardSearch = 0xF107, // updated 4.5

    ReqExamineFcInfo = 0xF113, // updated 4.1

    FcInfoReqHandler = 0xF11A, // updated 4.2

    FreeCompanyUpdateShortMessageHandler = 0xF123, // added 5.0

    ReqMarketWishList = 0xF12C, // updated 4.3

    ReqJoinNoviceNetwork = 0xF129, // updated 4.2

    ReqCountdownInitiate = 0xF25F, // updated 5.35 hotfix
    ReqCountdownCancel = 0xF244, // updated 5.25

    ZoneLineHandler = 0xF337, // updated 5.55 hotfix diff
    ClientTrigger = 0x0337, // updated 5.55 hotfix
    DiscoveryHandler = 0xF0E3, // updated 5.35 hotfix

    PlaceFieldMarkerPreset = 0xF10C, // updated 5.55 hotfix diff
    PlaceFieldMarker = 0xF2E2, // updated 5.55 hotfix diff
    SkillHandler = 0x02A2, // updated 5.55 hotfix
    GMCommand1 = 0xF3DC, // updated 5.55 hotfix diff
    GMCommand2 = 0xF13D, // updated 5.55 hotfix diff
    AoESkillHandler = 0xF24B, // updated 5.55 hotfix diff

    UpdatePositionHandler = 0x024B, // updated 5.55 hotfix

    InventoryModifyHandler = 0x01D7, // updated 5.55 hotfix
    
    InventoryEquipRecommendedItems = 0x0186, // updated 5.45 hotfix

    ReqPlaceHousingItem = 0xF313, // updated 5.55 hotfix diff
    BuildPresetHandler = 0xF1E9, // updated 5.55 hotfix diff

    TalkEventHandler = 0x01E9, // updated 5.55 hotfix
    EmoteEventHandler = 0xF35A, // updated 5.55 hotfix diff
    WithinRangeEventHandler = 0xF338, // updated 5.55 hotfix diff
    OutOfRangeEventHandler = 0xF077, // updated 5.55 hotfix diff
    EnterTeriEventHandler = 0xF283, // updated 5.55 hotfix diff
    ShopEventHandler = 0x03D4, // updated 5.45 hotfix
    EventYieldHandler = 0xF2A0, // updated 5.55 hotfix diff
    ReturnEventHandler = 0x015D, // updated 5.55 hotfix
    TradeReturnEventHandler = 0x0091, // updated 5.55 hotfix
    TradeMultipleReturnEventHander = 0xF35C, // updated 5.35 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0xF25E, // updated 5.55 hotfix diff

    LandRenameHandler = 0xF330, // updated 5.55 hotfix diff
    HousingUpdateHouseGreeting = 0xF1BD, // updated 5.55 hotfix diff
    HousingUpdateObjectPosition = 0xF3A5, // updated 5.55 hotfix diff
    HousingEditExterior = 0xF1D7, // updated 5.55 hotfix diff

    SetSharedEstateSettings = 0xF3DC, // updated 5.55 hotfix diff

    UpdatePositionInstance = 0x009D, // updated 5.55 hotfix

    PerformNoteHandler = 0xF0FE, // updated 5.55 hotfix diff

    WorldInteractionHandler = 0xF07D, // updated 5.55 hotfix diff
    Dive = 0x0306, // updated 5.55 hotfix diff
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
