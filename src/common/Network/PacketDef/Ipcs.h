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
    Ping = 0x0106, // updated 5.2
    Init = 0x0308, // updated 5.2

    ActorFreeSpawn = 0x009B, // updated 5.18
    InitZone = 0x033A, // updated 5.2

    EffectResult = 0x0267, // updated 5.18
    ActorControl = 0x03BE, // updated 5.18
    ActorControlSelf = 0x010E, // updated 5.2
    ActorControlTarget = 0x24d, // updated 5.18

    /*!
     * @brief Used when resting
     */
    UpdateHpMpTp = 0x00C1, // updated 5.2

    ///////////////////////////////////////////////////

    ChatBanned = 0x006B,
    Playtime = 0x00E7, // updated 5.18
    Logout = 0x142, // updated 5.18
    CFNotify = 0x01F8, // updated 5.18
    CFMemberStatus = 0x0079,
    CFDutyInfo = 0x007A,
    CFPlayerInNeed = 0x007F,
    CFPreferredRole = 0x032A, // added 5.18

    SocialRequestError = 0x00AD,

    CFRegistered = 0x00B8, // updated 4.1
    SocialRequestResponse = 0x00BB, // updated 4.1
    CancelAllianceForming = 0x00C6, // updated 4.2

    LogMessage = 0x00D0,

    Chat = 0x02A3, // updated 5.18

    WorldVisitList = 0x00FE, // added 4.5

    SocialList = 0x033E, // updated 5.2

    ExamineSearchInfo = 0x012B, // updated 5.18
    UpdateSearchInfo = 0x01E5, // updated 5.18
    InitSearchInfo = 0x021C, // updated 5.2
    ExamineSearchComment = 0x0102, // updated 4.1

    ServerNoticeShort = 0x0115, // updated 5.0
    ServerNotice = 0x0308, // updated 5.2
    SetOnlineStatus = 0x0185, // updated 5.2

    CountdownInitiate = 0x0309, // updated 5.11
    CountdownCancel = 0x00D9, // updated 5.18

    PlayerAddedToBlacklist = 0x033F, // updated 5.1
    PlayerRemovedFromBlacklist = 0x0385, // updated 5.1
    BlackList = 0x01A2, // updated 5.2

    LinkshellList = 0x028C, // updated 5.2

    MailDeleteRequest = 0x012B, // updated 5.0

    // 12D - 137 - constant gap between 4.5x -> 5.0
    ReqMoogleMailList = 0x0138, // updated 5.0
    ReqMoogleMailLetter = 0x0139, // updated 5.0
    MailLetterNotification = 0x013A, // updated 5.0

    MarketTaxRates = 0x025E, // updated 5.18

    MarketBoardItemListingCount = 0x0328, // updated 5.18
    MarketBoardItemListing = 0x015F, // updated 5.18
    MarketBoardItemListingHistory = 0x0113, // updated 5.18
    MarketBoardSearchResult = 0x01EA, // updated 5.18

    CharaFreeCompanyTag = 0x013B, // updated 4.5
    FreeCompanyBoardMsg = 0x013C, // updated 4.5
    FreeCompanyInfo = 0x013D, // updated 4.5
    ExamineFreeCompanyInfo = 0x013E, // updated 4.5

    FreeCompanyUpdateShortMessage = 0x0157, // added 5.0

    StatusEffectList = 0x0183, // updated 5.18
    EurekaStatusEffectList = 0x0167, // updated 5.18
    BossStatusEffectList = 0x0312, // added 5.1
    Effect = 0x026B, // updated 5.18
    AoeEffect8 = 0x033E, // updated 5.18
    AoeEffect16 = 0x0305, // updated 5.18
    AoeEffect24 = 0x023F, // updated 5.18
    AoeEffect32 = 0x0352, // updated 5.18
    PersistantEffect = 0x00CE, // updated 5.2

    GCAffiliation = 0x016F, // updated 5.0

    PlayerSpawn = 0x027D, // updated 5.2
    NpcSpawn = 0x034B, // updated 5.2
    NpcSpawn2 = 0x010C, // ( Bigger statuseffectlist? ) updated 5.18
    ActorMove = 0x021B, // updated 5.18

    ActorSetPos = 0x0068, // updated 5.18

    ActorCast = 0x03B1, // updated 5.18
    SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

    PartyList = 0x0287, // updated 5.18
    HateRank = 0x0226, // updated 5.18
    HateList = 0x0361, // updated 5.18
    ObjectSpawn = 0x01B3, // updated 5.2
    ObjectDespawn = 0x034B, // updated 5.18
    UpdateClassInfo = 0x0131, // updated 5.2
    SilentSetClassJob = 0x018E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
    PlayerSetup = 0x0278, // updated 5.2
    PlayerStats = 0x03C8, // updated 5.2
    ActorOwner = 0x03BB, // updated 5.18
    PlayerStateFlags = 0x032B, // updated 5.2
    PlayerClassInfo = 0x039A, // updated 5.2
    Effect037F = 0x037F, // 5.18

    ModelEquip = 0x02E6, // updated 5.18
    Examine = 0x0366, // updated 5.18
    CharaNameReq = 0x0116, // updated 5.18

    // nb: see #565 on github
    UpdateRetainerItemSalePrice = 0x019F, // updated 5.0

    SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

    ItemInfo = 0x03D4, // updated 5.2
    ContainerInfo = 0x01A5, // updated 5.2
    InventoryTransactionFinish = 0x00D2, // updated 5.18
    InventoryTransaction = 0x01D8, // updated 5.2
    CurrencyCrystalInfo = 0x02BF, // updated 5.18

    InventoryActionAck = 0x0094, // updated 5.2
    UpdateInventorySlot = 0x0370, // updated 5.18

    HuntingLogEntry = 0x01B3, // updated 5.0

    EventPlay = 0x0279, // updated 5.18
    EventPlay4 = 0x02F7, // updated 5.18
    EventPlay8 = 0x0119, // updated 5.18
    EventPlay16 = 0x01FB, // updated 5.18
    EventPlay32 = 0x0364, // updated 5.18
    EventPlay64 = 0x00E5, // updated 5.18
    EventPlay128 = 0x02BE, // updated 5.18
    EventPlay255 = 0x01B1, // updated 5.18

    EventStart = 0x0230, // updated 5.18
    EventFinish = 0x01E4, // updated 5.18
    UseMooch = 0x0233, // updated 5.18

    EventLinkshell = 0x1169,

    QuestActiveList = 0x017B, // updated 5.2
    QuestUpdate = 0x0066, // updated 5.18
    QuestCompleteList = 0x0255, // updated 5.2

    QuestFinish = 0x013A, // updated 5.18
    MSQTrackerComplete = 0x01D6, // updated 5.0
    MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

    QuestMessage = 0x00BF, // updated 5.18

    QuestTracker = 0x0306, // updated 5.2

    Mount = 0x038F, // updated 5.18

    DirectorVars = 0x00E6, // updated 5.18
    SomeDirectorUnk1 = 0x0084, // updated 5.18
    SomeDirectorUnk2 = 0x00C1, // updated 5.18
    SomeDirectorUnk4 = 0x0100, // updated 5.18
    SomeDirectorUnk8 = 0x028A, // updated 5.18
    SomeDirectorUnk16 = 0x028C, // updated 5.18
    DirectorPopUp = 0x0162, // updated 5.18 - display dialogue pop-ups in duties and FATEs, for example, Teraflare's countdown
    DirectorPopUp4 = 0x0214, // updated 5.18
    DirectorPopUp8 = 0x00F8, // updated 5.18

    CFAvailableContents = 0xF1FD, // updated 4.2

    WeatherChange = 0x02FB, // updated 5.11
    PlayerTitleList = 0x037D, // updated 5.1
    Discovery = 0x02E7, // updated 5.18

    EorzeaTimeOffset = 0x03B8, // updated 5.1

    EquipDisplayFlags = 0x00FF, // updated 5.18

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
    HousingLandFlags = 0x00FE, // updated 5.2
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

    PrepareZoning = 0x035C, // updated 5.18
    ActorGauge = 0x0162, // updated 5.2

    // daily quest info -> without them sent,  login will take longer...
    DailyQuests = 0x00A2, // updated 5.2
    DailyQuestRepeatFlags = 0x013D, // updated 5.2

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
    PingHandler = 0x0106, // updated 5.2
    InitHandler = 0x0307, // updated 5.2

    FinishLoadingHandler = 0x012B, // updated 5.2

    CFCommenceHandler = 0x006F,


    CFRegisterDuty = 0x0071,
    CFRegisterRoulette = 0xFF72,
    PlayTimeHandler = 0x0276, // updated 5.1
    LogoutHandler = 0x015D, // updated 5.18
    CancelLogout = 0x008F, // updated 5.1

    CFDutyInfoHandler = 0x0078, // updated 4.2

    SocialReqSendHandler = 0x00AE, // updated 4.1
    CreateCrossWorldLS = 0x00AF, // updated 4.3

    ChatHandler = 0x0130, // updated 5.18

    SocialListHandler = 0x03E7, // updated 5.2
    SetSearchInfoHandler = 0x0320, // updated 5.18
    ReqSearchInfoHandler = 0x007B, // updated 5.2
    ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

    ReqRemovePlayerFromBlacklist = 0x00F1, // updated 5.0
    BlackListHandler = 0x0329, // updated 5.2
    PlayerSearchHandler = 0x00F4, // updated 5.0

    LinkshellListHandler = 0x00A7, // updated 5.2

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

    ZoneLineHandler = 0x0174, // updated 5.18
    ClientTrigger = 0x017C, // updated 5.2
    DiscoveryHandler = 0x017B, // updated 5.18

    PlaceFieldMarker = 0x013C, // updated 5.0
    SkillHandler = 0x01BE, // updated 5.18
    GMCommand1 = 0x014D, // updated 5.18
    GMCommand2 = 0x03C2, // updated 5.18
    AoESkillHandler = 0x0072, // updated 5.18

    UpdatePositionHandler = 0x0318, // updated 5.18

    InventoryModifyHandler = 0x03C5, // updated 5.18
    
    InventoryEquipRecommendedItems = 0x0149, // updated 5.0

    ReqPlaceHousingItem = 0x014B, // updated 5.0
    BuildPresetHandler = 0x0150, // updated 5.0

    TalkEventHandler = 0x02FD, // updated 5.18
    EmoteEventHandler = 0x0183, // updated 5.18
    WithinRangeEventHandler = 0x0167, // updated 5.18
    OutOfRangeEventHandler = 0x02B5, // updated 5.18
    EnterTeriEventHandler = 0x0267, // updated 5.18
    ShopEventHandler = 0x0156, // updated 5.0

    ReturnEventHandler = 0x026B, // updated 5.18
    TradeReturnEventHandler = 0x02DD, // updated 5.18

    LinkshellEventHandler = 0x016B, // updated 4.5
    LinkshellEventHandler1 = 0x016C, // updated 4.5

    ReqEquipDisplayFlagsChange = 0x01FE, // updated 5.18

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
