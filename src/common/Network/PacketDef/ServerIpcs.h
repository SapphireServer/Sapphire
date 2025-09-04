#pragma once

#include <stdint.h>

namespace Sapphire::Network::Packets
{
  namespace LobbyPackets
  {
    ////////////////////////////////////////////////////////////////////////////////
    /// Lobby Connection IPC Codes
    /**
    * Server IPC Lobby Type Codes.
    */
    enum ServerLobbyIpcType : uint16_t
    {
      SyncReply = 0x0001,
      NackReply = 0x0002,
      LoginReply = 0x000C,
      ServiceLoginReply = 0x000D,
      CharaMakeReply = 0x000E,
      GameLoginReply = 0x000F,
      UpdateRetainerSlotsReply = 0x0010,
      DistWorldInfo = 0x0015,
      XiCharacterInfo = 0x0016,
      DistRetainerInfo = 0x0017,

      DebugNullRepl = 0x1F4,
      DebugLoginRepl = 0x1F5,

    };
  }

  namespace WorldPackets::Server
  {
  ////////////////////////////////////////////////////////////////////////////////
  /// Zone Connection IPC Codes
  /**
  * Server IPC Zone Type Codes.
  */
  enum ServerZoneIpcType : uint16_t
  {
    SyncReply = 0x0065,
    LoginReply = 0x0066,
    ChatToChannel = 0x0067,
    RegionInfo = 0x0069,

    MoveTerritory = 0x006A,
    MoveInstance = 0x006B,

    SetPSNId = 0x0073,
    SetBillingTime = 0x0075,

    AllienceInviteResult = 0x0078,
    AllienceInviteReplyResult = 0x0079,
    AllienceInviteUpdate = 0x007A,

    InviteResult = 0x00C9,
    InviteReplyResult = 0x00CA,
    InviteUpdate = 0x00CB,
    GetCommonlistResult = 0x00CC,
    GetCommonlistDetailResult = 0x00CD,
    SetProfileResult = 0x00CE,
    GetProfileResult = 0x00CF,

    GetSearchCommentResult = 0xD0,
    GetCharacterNameResult = 0xD1,
    ChatChannelResult = 0xD2,
    SendSystemMessage = 0xD3,
    SendLoginMessage = 0xD4,
    UpdateOnlineStatus = 0xD5,
    PartyRecruitResult = 0xD6,
    GetRecruitSearchListResult = 0xD7,
    GetRecruitDetailResult = 0xD8,
    RequestItemResult = 0xD9,
    AllianceReadyCheckResult = 0xDA,
    GetFcJoinRequestCommentResult = 0xDB,
    PcPartyResult = 0xDC,
    PcPartyUpdate = 0xDD,
    InviteCancelResult = 0xDE,

    BlacklistAddResult = 0x00E1,
    BlacklistRemoveResult = 0x00E2,
    GetBlacklistResult = 0x00E3,

    FriendlistRemoveResult = 0xE6,

    PcSearchResult = 0xEB,

    LinkshellResult = 0xF0,
    GetLinkshellListResult = 0x00F1,

    LetterResult = 0x00FA,
    GetLetterMessageResult = 0x00FB,
    GetLetterMessageDetailResult = 0x00FC,
    GetLetterStatusResult = 0x00FD,

    ItemSearchResult = 0x104,
    GetItemSearchListResult = 0x105,
    GetRetainerListResult = 0x106,
    BuyMarketRetainerResult = 0x107,
    MarketStorageUpdate = 0x108,
    GetItemHistoryResult = 0x109,
    GetRetainerSalesHistoryResult = 0x10A,
    MarketRetainerUpdate = 0x10B,
    CatalogSearchResult = 0x10C,

    FreeCompanyResult = 0x10E,
    GetFcStatusResult = 0x10F,
    GetFcInviteListResult = 0x110,
    GetFcProfileResult = 0x111,
    GetFcHeaderResult = 0x112,
    GetCompanyBoardResult = 0x113,
    GetFcHierarchyResult = 0x114,
    GetFcActivityListResult = 0x115,
    GetFcHierarchyLiteResult = 0x116,
    GetCompanyMottoResult = 0x117,
    GetFcParamsResult = 0x118,
    GetFcActionResult = 0x119,
    GetFcMemoResult = 0x11A,

    LeaveNoviceNetwork = 0x11D,

    InfoGMCommandResult = 0x122,

    SyncTagHeader = 0x12C,
    SyncTag32 = 0x12D,
    SyncTag64 = 0x12E,
    SyncTag128 = 0x12F,
    SyncTag256 = 0x130,
    SyncTag384 = 0x131,
    SyncTag512 = 0x132,
    SyncTag768 = 0x133,
    SyncTag1024 = 0x134,
    SyncTag1536 = 0x135,
    SyncTag2048 = 0x136,
    SyncTag3072 = 0x137,

    HudParam = 0x140,
    ActionIntegrity = 0x141,
    Order = 0x0142,
    OrderMySelf = 0x0143,
    OrderTarget = 0x0144,
    Resting = 0x0145,
    ActionResult1 = 0x0146,
    ActionResult = 0x0147,
    Status = 0x0148,
    FreeCompany = 0x149,
    RecastGroup = 0x14A,
    UpdateAlliance = 0x14B,
    PartyPos = 0x14C,
    AlliancePos = 0x14D,

    GrandCompany = 0x14F,

    Create = 0x0190,
    Delete = 0x0191,
    ActorMove = 0x0192,
    Transfer = 0x193,
    Warp = 0x0194,

    RequestCast = 0x196,

    UpdateParty = 0x199,
    InitZone = 0x019A,
    HateList = 0x019B,
    HaterList = 0x019C,
    CreateObject = 0x019D,
    DeleteObject = 0x019E,
    PlayerStatusUpdate = 0x019F,
    PlayerStatus = 0x01A0,
    BaseParam = 0x01A1,
    FirstAttack = 0x01A2,
    Condition = 0x01A3,
    ChangeClass = 0x1A4,
    Equip = 0x01A5,
    Inspect = 0x01A6,
    Name = 0x01A7,

    AttachMateriaRequest = 0x1A9,
    RetainerList = 0x1AA,
    RetainerData = 0x1AB,
    MarketPriceHeader = 0x1AC,
    MarketPrice = 0x1AD,
    ItemStorage = 0x01AE,
    NormalItem = 0x01AF,
    ItemSize = 0x01B0,
    ItemOperationBatch = 0x01B1,
    ItemOperation = 0x01B2,
    GilItem = 0x01B3,
    TradeCommand = 0x1B4,
    ItemMessage = 0x1B5,
    UpdateItem = 0x1B6,
    AliasItem = 0x1B7,
    OpenTreasure = 0x1B8,
    LootRight = 0x1B9,
    LootActionResult = 0x1BA,
    GameLog = 0x1BB,
    TreasureOpenRight = 0x1BC,
    OpenTreasureKeyUi = 0x1BD,
    LootItems = 0x1BE,
    CreateTreasure = 0x1BF,
    TreasureFadeOut = 0x1C0,
    MonsterNoteCategory = 0x01C1,
    EventPlayHeader = 0x1C2,
    EventPlay2 = 0x1C3,
    EventPlay4 = 0x1C4,
    EventPlay8 = 0x1C5,
    EventPlay16 = 0x1C6,
    EventPlay32 = 0x1C7,
    EventPlay64 = 0x1C8,
    EventPlay128 = 0x1C9,
    EventPlay255 = 0x1CA,
    DebugActorData = 0x1CB,
    PushEventState = 0x1CC,
    PopEventState = 0x1CD,
    UpdateEventSceneHeader = 0x1CE,
    UpdateEventScene2 = 0x1CF,
    UpdateEventScene4 = 0x1D0,
    UpdateEventScene8 = 0x1D1,
    UpdateEventScene16 = 0x1D2,
    UpdateEventScene32 = 0x1D3,
    UpdateEventScene64 = 0x1D4,
    UpdateEventScene128 = 0x1D5,
    UpdateEventScene255 = 0x1D6,
    ResumeEventSceneHeader = 0x1D7,
    ResumeEventScene2 = 0x1D8,
    ResumeEventScene4 = 0x1D9,
    ResumeEventScene8 = 0x1DA,
    ResumeEventScene16 = 0x1DB,
    ResumeEventScene32 = 0x1DC,
    ResumeEventScene64 = 0x1DD,
    ResumeEventScene128 = 0x1DE,
    ResumeEventScene255 = 0x1DF,
    Quests = 0x1E0,
    Quest = 0x01E1,
    QuestCompleteFlags = 0x01E2,
    QuestCompleteFlag = 0x01E3,
    Guildleves = 0x1E4,
    Guildleve = 0x1E5,
    LeveCompleteFlags = 0x1E6,
    LeveCompleteFlag = 0x1E7,
    NoticeHeader = 0x1E8,
    Notice2 = 0x1E9,
    Notice4 = 0x1EA,
    Notice8 = 0x1EB,
    Notice16 = 0x1EC,
    Notice32 = 0x1ED,
    Tracking = 0x1EE,
    IsMarket = 0x1EF,
    LegacyQuestCompleteFlags = 0x1F0,
    ResumeEventSceneHeaderStr = 0x1F1,
    ResumeEventSceneStr32 = 0x1F2,
    LogText = 0x1F3,
    DebugNull = 0x1F4,
    DebugLog = 0x1F5,
    BigData = 0x1F6,
    DebugOrderHeader = 0x1F7,
    DebugOrder2 = 0x1F8,
    DebugOrder4 = 0x1F9,
    DebugOrder8 = 0x1FA,
    DebugOrder16 = 0x1FB,
    DebugOrder32 = 0x1FC,
    DebugActionRange = 0x1FD,
    ResumeEventSceneHeaderNumStr = 0x1FE,
    ResumeEventScene2Str = 0x1FF,
    Mount = 0x0200,
    ResumeEventScene4Str = 0x201,

    Director = 0x226,

    EventLogMessageHeader = 0x258,
    EventLogMessage2 = 0x259,
    EventLogMessage4 = 0x25A,
    EventLogMessage8 = 0x25B,
    EventLogMessage16 = 0x25C,
    EventLogMessage32 = 0x25D,

    BattleTalkHeader = 0x262,
    BattleTalk2 = 0x263,
    BattleTalk4 = 0x264,
    BattleTalk8 = 0x265,
    EventReject = 0x26C,
    MapMarker2 = 0x26D,
    MapMarker4 = 0x26E,
    MapMarker8 = 0x26F,
    MapMarker16 = 0x270,
    MapMarker32 = 0x271,
    MapMarker64 = 0x272,
    MapMarker128 = 0x273,
    BalloonTalkHeader = 0x276,
    BalloonTalk2 = 0x277,
    BalloonTalk4 = 0x278,
    BalloonTalk8 = 0x279,

    GameLoggerMessage = 0x289,
    WeatherId = 0x28A,
    TitleList = 0x28B,
    DiscoveryReply = 0x28C,
    TimeOffset = 0x28D,
    ChocoboTaxiStart = 0x28E,
    GMOrderHeader = 0x28F,
    GMOrder2 = 0x290,
    GMOrder4 = 0x291,
    GMOrder8 = 0x292,
    GMOrder16 = 0x293,
    GMOrder32 = 0x294,

    InspectQuests = 0x29E,
    InspectGuildleves = 0x29F,
    InspectReward = 0x2A0,
    InspectBeastReputation = 0x2A1,

    Config = 0x2C6,

    NpcYell = 0x2D0,
    SwapSystem = 0x2D1,
    FatePcWork = 0x2D2,
    LootResult = 0x2D3,
    FateAccessCollectionEventObject = 0x2D4,
    FateSyncLimitTime = 0x2D5,
    EnableLogout = 0x02D6,
    LogMessage = 0x2D7,
    FateDebug = 0x2D8,
    FateContextWork = 0x2D9,
    FateActiveRange = 0x2DA,
    UpdateFindContent = 0x2DB,
    Cabinet = 0x2DC,
    Achievement = 0x2DD,
    NotifyFindContentStatus = 0x2DE,
    ColosseumResult44 = 0x2DF,
    ColosseumResult88 = 0x2E0,
    ResponsePenalties = 0x2E1,
    ContentClearFlags = 0x2E2,
    ContentAttainFlags = 0x02E3,
    UpdateContent = 0x2E4,
    Text = 0x2E5,
    SuccessFindContentAsMember5 = 0x2E6,
    CancelLogoutCountdown = 0x2E7,
    SetEventBehavior = 0x2E8,
    BallistaStart = 0x2E9,
    RetainerCustomizePreset = 0x2EA,
    FateReward = 0x2EB,

    HouseList = 0x2EC,
    House = 0x2ED,
    YardObjectList = 0x2EE,

    YardObject = 0x2F0,
    Interior = 0x2F1,
    HousingAuction = 0x2F2,
    HousingProfile = 0x2F3,
    HousingHouseName = 0x2F4,
    HousingGreeting = 0x2F5,
    CharaHousingLandData = 0x2F6,
    CharaHousing = 0x2F7,
    HousingWelcome = 0x2F8,
    FurnitureListS = 0x2F9,
    FurnitureListM = 0x2FA,
    FurnitureListL = 0x2FB,
    Furniture = 0x2FC,
    VoteKickConfirm = 0x2FD,
    HousingProfileList = 0x2FE,
    HousingObjectTransform = 0x2FF,
    HousingObjectColor = 0x300,
    HousingObjectTransformMulti = 0x301,
    ConfusionApproach = 0x302,
    ConfusionTurn = 0x303,
    ConfusionTurnCancel = 0x304,
    ConfusionCancel = 0x305,
    MIPMemberList = 0x306,
    HousingGetPersonalRoomProfileListResult = 0x307,
    HousingGetHouseBuddyStableListResult = 0x308,
    HouseTrainBuddyData = 0x309,

    ContentBonus = 0x311,

    FcChestLog = 0x316,
    SalvageResult = 0x317,

    DailyQuests = 0x0320,
    DailyQuest = 0x0321,
    QuestRepeatFlags = 0x0322,

    HousingObjectTransformMultiResult = 0x32A,
    HousingLogWithHouseName = 0x32B,
    TreasureHuntReward = 0x32C,
    HousingCombinedObjectStatus = 0x32D,
    HouseBuddyModelData = 0x32E,

    Marker = 0x334,
    GroundMarker = 0x335,
    Frontline01Result = 0x336,
    Frontline01BaseInfo = 0x337,

    FinishContentMatchToClient = 0x339,

    UnMountLink = 0x33E,

  };
  }

  ////////////////////////////////////////////////////////////////////////////////
  /// Chat Connection IPC Codes
  /**
  * Server IPC Chat Type Codes.
  */
  enum ServerChatIpcType : uint16_t
  {
    //Sync = 0x01, TODO: Fix this cuz name bullshit...
    LoginReply = 0x02,

    ChatFrom = 0x64,
    Chat = 0x65,
    TellNotFound = 0x66,
    RecvBusyStatus = 0x67,
    GetChannelMemberListResult = 0x68,
    GetChannelListResult = 0x69,
    RecvFinderStatus = 0x6A,

    JoinChannelResult = 0xC8,
    LeaveChannelResult = 0xC9
    //FreeCompanyEvent = 0x012C, // not in 2.3
  };



}

