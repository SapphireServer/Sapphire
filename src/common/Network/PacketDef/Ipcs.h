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
    Ping = 0x017A, // updated 5.25
    Init = 0x03B9, // updated 5.25

    ActorFreeSpawn = 0x0194, // updated 5.25
    InitZone = 0x01CD, // updated 5.25

    EffectResult = 0x030F, // updated 5.25
    ActorControl = 0x01DD, // updated 5.25
    ActorControlSelf = 0x0165, // updated 5.25
    ActorControlTarget = 0x01EB, // updated 5.25

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x00F8, // updated 5.25

    ///////////////////////////////////////////////////

    ChatBanned = 0xF06B,
    Playtime = 0x0286, // updated 5.25
    Logout = 0x00CD, // updated 5.25
    CFNotify = 0x0145, // updated 5.25
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x007A,
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x0186, // added 5.25
    CFCancel = 0x00B7, // updated 5.25
    SocialRequestError = 0xF0AD,

    CFRegistered = 0x00B8, // updated 4.1
    SocialRequestResponse = 0x00BB, // updated 4.1
    CancelAllianceForming = 0x00C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x0161, // updated 5.25

    WorldVisitList = 0xF0FE, // added 4.5

    SocialList = 0x0269, // updated 5.25

    ExamineSearchInfo = 0x032B, // updated 5.21 hotfix
    UpdateSearchInfo = 0x00B3, // updated 5.25
    InitSearchInfo = 0x0347, // updated 5.25
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x0115, // updated 5.0
    ServerNotice = 0x00E9, // updated 5.25
    SetOnlineStatus = 0x0381, // updated 5.25

    CountdownInitiate = 0x0237, // updated 5.25
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x027A, // updated 5.25

    LinkshellList = 0x00A9, // updated 5.25

    MailDeleteRequest = 0xF12B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0x0138, // updated 5.0
    ReqMoogleMailLetter = 0x0139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x034C, // updated 5.21 hotfix

    MarketBoardItemListingCount = 0x030A, // updated 5.2
    MarketBoardItemListing = 0x023E, // updated 5.2
    MarketBoardItemListingHistory = 0x03C0, // updated 5.2
    MarketBoardSearchResult = 0x01DD, // updated 5.21

    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0xF13D, // updated 4.5
    ExamineFreeCompanyInfo = 0xF13E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

    StatusEffectList = 0x01D7, // updated 5.25
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x0087, // updated 5.25
    AoeEffect8 = 0x01A6, // updated 5.25
    AoeEffect16 = 0x02A2, // updated 5.21 hotfix
    AoeEffect24 = 0x01FD, // updated 5.21 hotfix
    AoeEffect32 = 0x0376, // updated 5.21 hotfix
    PersistantEffect = 0x032E, // updated 5.25

    GCAffiliation = 0xF16F, // updated 5.0

    PlayerSpawn = 0x00B9, // updated 5.25
    NpcSpawn = 0x038D, // updated 5.25
    NpcSpawn2 = 0x010C, // ( Bigger statuseffectlist? ) updated 5.18
    ActorMove = 0x0290, // updated 5.25

    ActorSetPos = 0x028E, // updated 5.25

    ActorCast = 0x00C4, // updated 5.25
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x0287, // updated 5.18
    HateRank = 0x012E, // updated 5.25
    HateList = 0x02C4, // updated 5.25
    ObjectSpawn = 0x00D2, // updated 5.25
    ObjectDespawn = 0x034B, // updated 5.18
    UpdateClassInfo = 0x00DC, // updated 5.25
    SilentSetClassJob = 0x018E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0071, // updated 5.25
    PlayerStats = 0x007C, // updated 5.25
    ActorOwner = 0x0149, // updated 5.25
    PlayerStateFlags = 0x0125, // updated 5.25
    PlayerClassInfo = 0x034F, // updated 5.25
    CharaVisualEffect = 0x0258, // updated 5.25

    ModelEquip = 0x01E5, // updated 5.25
    Examine = 0x036E, // updated 5.21 hotfix
    CharaNameReq = 0x0145, // updated 5.25

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0x019F, // updated 5.0
    RetainerInformation = 0x0169, // updated 5.25

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x02AA, // updated 5.25
    ContainerInfo = 0x02A8, // updated 5.25
    InventoryTransactionFinish = 0x0193, // updated 5.25
    InventoryTransaction = 0x0119, // updated 5.25
    CurrencyCrystalInfo = 0x018A, // updated 5.25

    InventoryActionAck = 0x01AE, // updated 5.25
    UpdateInventorySlot = 0x0151, // updated 5.25

    HuntingLogEntry = 0xF1B3, // updated 5.0

    EventPlay = 0x02C3, // updated 5.25
    EventPlay4 = 0x029A, // updated 5.25
    EventPlay8 = 0x0119, // updated 5.18
    EventPlay16 = 0x01FB, // updated 5.18
    EventPlay32 = 0x02D9, // updated 5.25
    EventPlay64 = 0x00E5, // updated 5.18
    EventPlay128 = 0x02BE, // updated 5.18
    EventPlay255 = 0x01AC, // updated 5.25

    EventStart = 0x0360, // updated 5.25
    EventFinish = 0x0239, // updated 5.25

    EventLinkshell = 0x1169,

    QuestActiveList = 0x0391, // updated 5.25
    QuestUpdate = 0x0352, // updated 5.25
    QuestCompleteList = 0x0231, // updated 5.25

    QuestFinish = 0x02B6, // updated 5.25
    MSQTrackerComplete = 0x01D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0093, // updated 5.25

    QuestTracker = 0x00AD, // updated 5.25

    Mount = 0x02BE, // updated 5.25

    DirectorVars = 0x00E6, // updated 5.18
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0xF0C1, // updated 5.18
    SomeDirectorUnk4 = 0x01F3, // updated 5.21 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0xF162, // updated 5.18 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x0157, // updated 5.25
    PlayerTitleList = 0x037D, // updated 5.1
    Discovery = 0x0173, // updated 5.25

    EorzeaTimeOffset = 0x03B8, // updated 5.1

    EquipDisplayFlags = 0x010D, // updated 5.25

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0234, // updated 5.0
    LandUpdate = 0x0235, // updated 5.0
    YardObjectSpawn = 0x0236, // updated 5.0
    HousingIndoorInitialize = 0x0237, // updated 5.0
    LandPriceUpdate = 0x0238, // updated 5.0
    LandInfoSign = 0x037F, // updated 5.25
    LandRename = 0x023A, // updated 5.0
    HousingEstateGreeting = 0x023B, // updated 5.0
    HousingUpdateLandFlagsSlot = 0x023C, // updated 5.0
    HousingLandFlags = 0x0177, // updated 5.25
    HousingShowEstateGuestAccess = 0x023E, // updated 5.0

    HousingObjectInitialize = 0x0333, // updated 5.25
    HousingInternalObjectSpawn = 0x241, // updated 5.0

    HousingWardInfo = 0x01D1, // updated 5.25
    HousingObjectMove = 0x0244, // updated 5.0

    SharedEstateSettingsResponse = 0x0245, // updated 4.5

    LandUpdateHouseName = 0x0257, // updated 4.5

    LandSetMap = 0x025B, // updated 4.5

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0286, // updated 4.3

    PrepareZoning = 0x03B3, // updated 5.25
    ActorGauge = 0x007D, // updated 5.25

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x031E, // updated 5.25
    DailyQuestRepeatFlags = 0x00A7, // updated 5.25

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
    PingHandler = 0x017A, // updated 5.25
    InitHandler = 0x03B9, // updated 5.25

    FinishLoadingHandler = 0x008A, // updated 5.25

    CFCommenceHandler = 0x0228, // updated 5.25

    CFCancelHandler = 0x013E, // updated 5.25
    CFRegisterDuty = 0x0180, // updated 5.25
    CFRegisterRoulette = 0x0395, // updated 5.25
    PlayTimeHandler = 0x02FE, // updated 5.25
    LogoutHandler = 0x00B7, // updated 5.25
    CancelLogout = 0x008F, // updated 5.1

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x00AE, // updated 4.1
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x0189, // updated 5.25

    SocialListHandler = 0x0371, // updated 5.25
    SetSearchInfoHandler = 0x00FA, // updated 5.25
    ReqSearchInfoHandler = 0x0366, // updated 5.25
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x0354, // updated 5.25
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x01D4, // updated 5.25

    MarketBoardRequestItemListingInfo = 0x0102, // updated 4.5
    MarketBoardRequestItemListings = 0x0103, // updated 4.5
    MarketBoardSearch = 0x0107, // updated 4.5

    ReqExamineFcInfo = 0x0113, // updated 4.1

    FcInfoReqHandler = 0x011A, // updated 4.2

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x012C, // updated 4.3

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x009A, // updated 5.25
    ReqCountdownCancel = 0x0244, // updated 5.25

    ZoneLineHandler = 0x0214, // updated 5.25
    ClientTrigger = 0x017D, // updated 5.25
    DiscoveryHandler = 0x02C8, // updated 5.25

    PlaceFieldMarkerPreset = 0x023F, // updated 5.25
    PlaceFieldMarker = 0x01BA, // updated 5.25
    SkillHandler = 0x0241, // updated 5.25
    GMCommand1 = 0x01EC, // updated 5.25
    GMCommand2 = 0x0368, // updated 5.25
    AoESkillHandler = 0x0364, // updated 5.21 hotfix

    UpdatePositionHandler = 0x014D, // updated 5.25

    InventoryModifyHandler = 0x0179, // updated 5.25
    
    InventoryEquipRecommendedItems = 0x0149, // updated 5.0

    ReqPlaceHousingItem = 0x014B, // updated 5.0
    BuildPresetHandler = 0x0150, // updated 5.0

    TalkEventHandler = 0x030F, // updated 5.25
    EmoteEventHandler = 0x01DD, // updated 5.25
    WithinRangeEventHandler = 0x0165, // updated 5.25
    OutOfRangeEventHandler = 0x01EB, // updated 5.25
    EnterTeriEventHandler = 0x00F8, // updated 5.25
    ShopEventHandler = 0x0156, // updated 5.0

    ReturnEventHandler = 0x00BB, // updated 5.25
    TradeReturnEventHandler = 0x03B6, // updated 5.25
    TradeMultipleReturnEventHander = 0x02B0, // updated 5.25

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x0202, // updated 5.25

    LandRenameHandler = 0xF177, // updated 5.0
    HousingUpdateHouseGreeting = 0x0178, // updated 5.0
    HousingUpdateObjectPosition = 0x0159, // updated 5.25

    SetSharedEstateSettings = 0x017B, // updated 5.0

    UpdatePositionInstance = 0x0080, // updated 5.21 hotfix

    PerformNoteHandler = 0x029B, // updated 4.3

    WorldInteractionHandler = 0x0285, // updated 5.25
    ShopMessage = 0x00C1, // updated 5.25
    LootMessage = 0x00B1, // updated 5.25
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

    FreeCompanyEvent = 0x012C, // added 5.0
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
