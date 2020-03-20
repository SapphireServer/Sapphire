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
    Ping = 0x012C, // updated 5.21 hotfix
    Init = 0x010D, // updated 5.21 hotfix

    ActorFreeSpawn = 0x006C, // updated 5.21 hotfix
    InitZone = 0x037B, // updated 5.21 hotfix

    EffectResult = 0x0281, // updated 5.21 hotfix
    ActorControl = 0x0380, // updated 5.21 hotfix
    ActorControlSelf = 0x0253, // updated 5.21 hotfix
    ActorControlTarget = 0x0206, // updated 5.21 hotfix

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x01B8, // updated 5.21 hotfix

    ///////////////////////////////////////////////////

    ChatBanned = 0x0000,//0x006B,
    Playtime = 0x0284, // updated 5.21
    Logout = 0x02A8, // updated 5.21 hotfix
    CFNotify = 0x0241, // updated 5.21
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x007A,
    CFPlayerInNeed = 0xF07F,
    CFPreferredRole = 0x00D4, // added 5.21

    SocialRequestError = 0x00AD,

    CFRegistered = 0x00B8, // updated 4.1
    SocialRequestResponse = 0x00BB, // updated 4.1
    CancelAllianceForming = 0x00C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x012B, // updated 5.21 hotfix

    WorldVisitList = 0x0000,//0x00FE, // added 4.5

    SocialList = 0x0172, // updated 5.21 hotfix

    ExamineSearchInfo = 0x032B, // updated 5.21 hotfix
    UpdateSearchInfo = 0x0379, // updated 5.21 hotfix
    InitSearchInfo = 0x00D1, // updated 5.21 hotfix
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x0115, // updated 5.0
    ServerNotice = 0x0192, // updated 5.21 hotfix
    SetOnlineStatus = 0x0109, // updated 5.21 hotfix

    CountdownInitiate = 0x0309, // updated 5.11
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x0224, // updated 5.21 hotfix

    LinkshellList = 0x0395, // updated 5.21 hotfix

    MailDeleteRequest = 0x0000,//0x012B, // updated 5.0

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
    FreeCompanyInfo = 0x0000,//0x013D, // updated 4.5
    ExamineFreeCompanyInfo = 0x013E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0x0157, // added 5.0

    StatusEffectList = 0x0327, // updated 5.21 hotfix
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x0252, // updated 5.21 hotfix
    AoeEffect8 = 0x0140, // updated 5.21 hotfix
    AoeEffect16 = 0x02A2, // updated 5.21 hotfix
    AoeEffect24 = 0x01FD, // updated 5.21 hotfix
    AoeEffect32 = 0x0376, // updated 5.21 hotfix
    PersistantEffect = 0x0110, // updated 5.21 hotfix

    GCAffiliation = 0x0000,//0x016F, // updated 5.0

    PlayerSpawn = 0x033D, // updated 5.21 hotfix
    NpcSpawn = 0x00B3, // updated 5.21 hotfix
    NpcSpawn2 = 0x010C, // ( Bigger statuseffectlist? ) updated 5.18
    ActorMove = 0x0080, // updated 5.21 hotfix

    ActorSetPos = 0x0295, // updated 5.21 hotfix

    ActorCast = 0x02C3, // updated 5.21 hotfix
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x0287, // updated 5.18
    HateRank = 0x0381, // updated 5.21 hotfix
    HateList = 0x01F0, // updated 5.21 hotfix
    ObjectSpawn = 0x0342, // updated 5.21 hotfix
    ObjectDespawn = 0x034B, // updated 5.18
    UpdateClassInfo = 0x0235, // updated 5.21 hotfix
    SilentSetClassJob = 0x018E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0316, // updated 5.21 hotfix
    PlayerStats = 0x03E1, // updated 5.21 hotfix
    ActorOwner = 0x03C8, // updated 5.21 hotfix
    PlayerStateFlags = 0x00AA, // updated 5.21 hotfix
    PlayerClassInfo = 0x016B, // updated 5.21
    CharaVisualEffect = 0x030C, // updated 5.21 hotfix

    ModelEquip = 0x03A2, // updated 5.21 hotfix
    Examine = 0x036E, // updated 5.21 hotfix
    CharaNameReq = 0x02E4, // updated 5.21 hotfix

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0x019F, // updated 5.0

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x0244, // updated 5.21 hotfix
    ContainerInfo = 0x03BB, // updated 5.21 hotfix
    InventoryTransactionFinish = 0x0274, // updated 5.21 hotfix
    InventoryTransaction = 0x00202, // updated 5.21 hotfix
    CurrencyCrystalInfo = 0x017F, // updated 5.21 hotfix

    InventoryActionAck = 0x01B2, // updated 5.21 hotfix
    UpdateInventorySlot = 0x0213, // updated 5.21 hotfix

    HuntingLogEntry = 0x01B3, // updated 5.0

    EventPlay = 0x007F, // updated 5.21 hotfix
    EventPlay4 = 0x03BD, // updated 5.21 hotfix
    EventPlay8 = 0x0119, // updated 5.18
    EventPlay16 = 0x01FB, // updated 5.18
    EventPlay32 = 0x017D, // updated 5.21
    EventPlay64 = 0x00E5, // updated 5.18
    EventPlay128 = 0x02BE, // updated 5.18
    EventPlay255 = 0x00D9, // updated 5.21 hotfix

    EventStart = 0x03E4, // updated 5.21 hotfix
    EventFinish = 0x0197, // updated 5.21 hotfix

    EventLinkshell = 0x1169,

    QuestActiveList = 0x03D7, // updated 5.21 hotfix
    QuestUpdate = 0x01F8, // updated 5.21 hotfix
    QuestCompleteList = 0x0084, // updated 5.21 hotfix

    QuestFinish = 0x01FE, // updated 5.21 hotfix
    MSQTrackerComplete = 0x01D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x0324, // updated 5.21 hotfix

    QuestTracker = 0x02CA, // updated 5.21 hotfix

    Mount = 0x02F1, // updated 5.21 hotfix

    DirectorVars = 0x00E6, // updated 5.18
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0x00C1, // updated 5.18
    SomeDirectorUnk4 = 0x01F3, // updated 5.21 hotfix
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x0000,//0x0162, // updated 5.18 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0x0000,//0xF1FD, // updated 4.2

    WeatherChange = 0x024A, // updated 5.21
    PlayerTitleList = 0x037D, // updated 5.1
    Discovery = 0x0091, // updated 5.2

    EorzeaTimeOffset = 0x03B8, // updated 5.1

    EquipDisplayFlags = 0x006E, // updated 5.21 hotfix

    /// Housing //////////////////////////////////////

    LandSetInitialize = 0x0234, // updated 5.0
    LandUpdate = 0x0235, // updated 5.0
    YardObjectSpawn = 0x0236, // updated 5.0
    HousingIndoorInitialize = 0x0237, // updated 5.0
    LandPriceUpdate = 0x0238, // updated 5.0
    LandInfoSign = 0x0239, // updated 5.0
    LandRename = 0x023A, // updated 5.0
    HousingEstateGreeting = 0x023B, // updated 5.0
    HousingUpdateLandFlagsSlot = 0x023C, // updated 5.0
    HousingLandFlags = 0x02D8, // updated 5.21 hotfix
    HousingShowEstateGuestAccess = 0x023E, // updated 5.0

    HousingObjectInitialize = 0x0240, // updated 5.0
    HousingInternalObjectSpawn = 0x241, // updated 5.0

    HousingWardInfo = 0x0243, // updated 5.0
    HousingObjectMove = 0x0244, // updated 5.0

    SharedEstateSettingsResponse = 0x0245, // updated 4.5

    LandUpdateHouseName = 0x0257, // updated 4.5

    LandSetMap = 0x025B, // updated 4.5

    //////////////////////////////////////////////////

    DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
    PerformNote = 0x0286, // updated 4.3

    PrepareZoning = 0x00B6, // updated 5.21 hotfix
    ActorGauge = 0x00C7, // updated 5.21 hotfix

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x0130, // updated 5.21 hotfix
    DailyQuestRepeatFlags = 0x02BA, // updated 5.21 hotfix

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
    PingHandler = 0x012C, // updated 5.21 hotfix
    InitHandler = 0x010D, // updated 5.21 hotfix

    FinishLoadingHandler = 0x0158, // updated 5.21 hotfix

    CFCommenceHandler = 0x0078, // updated 5.21 hotfix


    CFRegisterDuty = 0x0118, // updated 5.21 hotfix
    CFRegisterRoulette = 0x037A, // updated 5.21 hotfix
    PlayTimeHandler = 0x0276, // updated 5.1
    LogoutHandler = 0x0139, // updated 5.21 hotfix
    CancelLogout = 0x008F, // updated 5.1

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x00AE, // updated 4.1
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x03AB, // updated 5.21 hotfix

    SocialListHandler = 0x02B9, // updated 5.21 hotfix
    SetSearchInfoHandler = 0x025C, // updated 5.21 hotfix
    ReqSearchInfoHandler = 0x026F, // updated 5.21 hotfix
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x0157, // updated 5.21 hotfix
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x01DE, // updated 5.21 hotfix

    MarketBoardRequestItemListingInfo = 0x0102, // updated 4.5
    MarketBoardRequestItemListings = 0x0103, // updated 4.5
    MarketBoardSearch = 0x0107, // updated 4.5

    ReqExamineFcInfo = 0x0113, // updated 4.1

    FcInfoReqHandler = 0x011A, // updated 4.2

    FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

    ReqMarketWishList = 0x012C, // updated 4.3

    ReqJoinNoviceNetwork = 0x0129, // updated 4.2

    ReqCountdownInitiate = 0x0135, // updated 5.0
    ReqCountdownCancel = 0x0136, // updated 5.0

    ZoneLineHandler = 0x025E, // updated 5.21 hotfix
    ClientTrigger = 0x017E, // updated 5.21 hotfix
    DiscoveryHandler = 0x019A, // updated 5.2

    PlaceFieldMarker = 0x013C, // updated 5.0
    SkillHandler = 0x0073, // updated 5.21 hotfix
    GMCommand1 = 0x0302, // updated 5.21 hotfix
    GMCommand2 = 0x01E5, // updated 5.21 hotfix
    AoESkillHandler = 0x0364, // updated 5.21 hotfix

    UpdatePositionHandler = 0x01B1, // updated 5.21 hotfix

    InventoryModifyHandler = 0x0067, // updated 5.21 hotfix
    
    InventoryEquipRecommendedItems = 0x0149, // updated 5.0

    ReqPlaceHousingItem = 0x014B, // updated 5.0
    BuildPresetHandler = 0x0150, // updated 5.0

    TalkEventHandler = 0x0281, // updated 5.21 hotfix
    EmoteEventHandler = 0x0380, // updated 5.21 hotfix
    WithinRangeEventHandler = 0x0253, // updated 5.21 hotfix
    OutOfRangeEventHandler = 0x0206, // updated 5.21 hotfix
    EnterTeriEventHandler = 0x01B8, // updated 5.21 hotfix
    ShopEventHandler = 0x0156, // updated 5.0

    ReturnEventHandler = 0x02A2, // updated 5.21 hotfix
    TradeReturnEventHandler = 0x01FD, // updated 5.21 hotfix

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x00B5, // updated 5.21 hotfix

    LandRenameHandler = 0xF177, // updated 5.0
    HousingUpdateHouseGreeting = 0x0178, // updated 5.0
    HousingUpdateObjectPosition = 0x0179, // updated 5.0

    SetSharedEstateSettings = 0x017B, // updated 5.0

    UpdatePositionInstance = 0x0180, // updated 5.0

    PerformNoteHandler = 0x029B, // updated 4.3

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
