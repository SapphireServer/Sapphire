#ifndef _CORE_NETWORK_PACKETS_IPCS_H
#define _CORE_NETWORK_PACKETS_IPCS_H

#include <stdint.h>

namespace Sapphire::Network::Packets {

////////////////////////////////////////////////////////////////////////////////
/// Lobby Connection IPC Codes
/**
 * Server IPC Lobby Type Codes.
 */
enum ServerLobbyIpcType :
  uint16_t
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
enum ClientLobbyIpcType :
  uint16_t
{
  ReqCharList = 0x0003, ReqEnterWorld = 0x0004, ClientVersionInfo = 0x0005,

  ReqCharDelete = 0x000A, ReqCharCreate = 0x000B,
};

////////////////////////////////////////////////////////////////////////////////
/// Zone Connection IPC Codes
/**
 * Server IPC Zone Type Codes.
 */
enum ServerZoneIpcType :
  uint16_t
{
  Ping = 0x1D9, // Endwalker Definition
  Init = 0x277, // updated 7.38

  ActorFreeSpawn = 0x195, // Endwalker Definition

  InitZone = 0x02B1, // Endwalker Definition
  PrepareZoning = 0x0124, // Endwalker Definition

  EffectResult = 0x0336, // Endwalker Definition
  EffectResultBasic = 0x023A, // Endwalker Definition

  ActorControl = 0x0148, // Endwalker Definition
  ActorControlTarget = 0x032C, // Endwalker Definition
  ActorControlSelf = 0x0254, // updated 7.38
  ActorCast = 0x01BB, // Endwalker Definition
  ActorSetPos = 0x029D, // Endwalker Definition
  ActorMove = 0x011C, // Endwalker Definition
  ActorGauge = 0x0365,  // updated 7.38

  /*!
   * @brief Used when resting
   */
  UpdateHpMpTp = 0x007D, // Endwalker Definition
  UpdateClassInfo = 0x0204,  // updated 7.38

  ///////////////////////////////////////////////////

  ChatBanned = 0xF06B,
  Playtime = 0x03DE, // Endwalker Definition
  Logout = 0x0312, // updated 7.38
  CFNotify = 0x0279, // Endwalker Definition
  CFMemberStatus = 0x21F, // Endwalker Definition?
  CFDutyInfo = 0x2E8, // Endwalker Definition?
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0x282,  // Endwalker Definition
  CFCancel = 0x384,        // Endwalker Definition
  CFUnk = 0x196, // Endwalker Definition
  SocialRequestError = 0xF0AD,

  CFRegistered = 0x029F,          // Legacy Definition
  SocialInviteResponse = 0x322,  // Endwalker Definition
  SocialInviteUpdate = 0x01C1, // Endwalker Definition
  SocialInviteResult = 0x031B, // Endwalker Definition
  CancelAllianceForming = 0xF0C6, // Legacy Definition

  LogMessage = 0x19C, // Endwalker Definition?

  Chat = 0x0325, // Endwalker Definition

  WorldVisitList = 0xF0FE, // added 4.5

  SocialList = 0x25E, // updated 7.38

  ExamineSearchInfo = 0x014A, // Endwalker Definition
  UpdateSearchInfo = 0x00CF, // Endwalker Definition
  InitSearchInfo = 0x329,       // Endwalker Definition
  ExamineSearchComment = 0x244, // Endwalker Definition?

  ServerNoticeShort = 0xF333, // Legacy Definition
  ServerNotice = 0x1CD,       // updated 7.38
  SetOnlineStatus = 0x3CF,   // updated 7.38

  CountdownInitiate = 0x376, // Endwalker Definition
  CountdownCancel = 0x2B7,    // Endwalker Definition

  PlayerAddedToBlacklist = 0xe2,     // Endwalker Definition
  PlayerRemovedFromBlacklist = 0x201, // Endwalker Definition?
  BlackList = 0xF38A,                   // Endwalker Definition

  LinkshellList = 0x2B2,           // Endwalker Definition
  CrossWorldLinkshellList = 0x2C8, // updated 7.38
  FellowshipList = 0x373,          // Endwalker Definition

  MailDeleteRequest = 0x168, // Endwalker Definition?

  // 12D - 137 - constant gap between 4.5x -> 5.0
  ReqMoogleMailList = 0xF138,      // Legacy Definition
  ReqMoogleMailLetter = 0xF139,    // Legacy Definition
  MailLetterNotification = 0x013A, // Legacy Definition

  MarketTaxRates = 0x01F8, // updated 5.35h

  MarketBoardSearchResult = 0x0161, // Endwalker Definition
  MarketBoardItemListingCount = 0x0286, // Endwalker Definition
  MarketBoardItemListingHistory = 0x0229, // Endwalker Definition
  MarketBoardItemListing = 0x03E3, // Endwalker Definition
  MarketBoardPurchase = 0x0143, // Endwalker Definition
  ItemMarketBoardInfo = 0x01BC, // Endwalker Definition

  CharaFreeCompanyTag = 0x013B,   // updated 4.5
  FreeCompanyBoardMsg = 0x023B,   // updated 7.38
  FreeCompanyInfo = 0x02D5, // Endwalker Definition
  FreeCompanyDialog = 0x029F, // Endwalker Definition
  ExamineFreeCompanyInfo = 0x158, // Endwalker Definition

  FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

  StatusEffectList = 0x0383, // Endwalker Definition
  EurekaStatusEffectList = 0x3A8, // Endwalker Definition
  BossStatusEffectList = 0x28C,   // Endwalker Definition
  StatusEffectList2 = 0x0369, // Endwalker Definition
  StatusEffectList3 = 0x010A, // Endwalker Definition
  Effect = 0x037D, // Endwalker Definition
  AoeEffect8 = 0x0F4, // Endwalker Definition
  AoeEffect16 = 0x121, // Endwalker Definition
  AoeEffect24 = 0x2E3, // Endwalker Definition
  AoeEffect32 = 0x1FB, // Endwalker Definition
  PersistantEffect = 0x163, // Endwalker Definition

  PlaceFieldMarker = 0xF2E4, // Endwalker Definition
  PlaceFieldMarkerPreset = 0xF30A, // Endwalker Definition

  GCAffiliation = 0x06A, // updated 7.38

  PlayerSpawn = 0x0270, // updated 7.38
  NpcSpawn = 0x02C9,  // updated 7.38
  NpcSpawn2 = 0x338,   // Endwalker Definition?

  SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

  PartyList = 0x164,         // Endwalker Definition
  PartyUpdate = 0x2D8,       // Endwalker Definition
  HateRank = 0x2A7,            // Endwalker Definition
  HateList = 0x26B,            // Endwalker Definition
  ObjectSpawn = 0x02B9,  // updated 7.38
  ObjectDespawn = 0x1D8,      // Endwalker Definition
  SilentSetClassJob = 0xF18E, // Legacy Definition - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x039A, // updated 7.38
  PlayerStats = 0x02C4, // updated 7.38
  ActorOwner = 0x2c3,         // Endwalker Definition
  PlayerStateFlags = 0x1DF,   // updated 7.38
  PlayerClassInfo = 0x0125,    // updated 7.38
  PlayerUpdateLook = 0xa8,    // Endwalker Definition
  CharaVisualEffect = 0x0C1,  // Endwalker Definition

  ModelEquip = 0x27D,    // Endwalker Definition
  Examine = 0x02C0, // Endwalker Definition
  CharaNameReq = 0x33C, // Endwalker Definition?

  // nb: see #565 on github
  UpdateRetainerItemSalePrice = 0xF19F, // Legacy Definition
  RetainerSaleHistory = 0xf23d,          // Endwalker Definition
  RetainerInformation = 0x00ED, // Endwalker Definition

  SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

  ItemInfo = 0x01E7, // updated 7.38
  ContainerInfo = 0x021E, // updated 7.38
  InventoryTransactionFinish = 0x00EC, // updated 7.38
  InventoryTransaction = 0x0117, // updated 7.38
  CurrencyCrystalInfo = 0x03C1, // updated 7.38

  InventoryActionAck = 0x02CC, // updated 7.38
  UpdateInventorySlot = 0xF34D, // Endwalker Definition

  HuntingLogEntry = 0x1E3, // updated 7.38

  EventPlay = 0x0155, // Endwalker Definition
  EventPlay4 = 0x00D0, // Endwalker Definition
  EventPlay8 = 0x022B, // Endwalker Definition
  EventPlay16 = 0x00D2, // Endwalker Definition
  EventPlay32 = 0x02CF, // Endwalker Definition
  EventPlay64 = 0x01D4, // Endwalker Definition
  EventPlay128 = 0x039F, // Endwalker Definition
  EventPlay255 = 0x0073, // Endwalker Definition
  EventStart = 0x0146, // Endwalker Definition
  EventFinish = 0x0339, // Endwalker Definition

  EventReturn = 0x1F3, // Endwalker Definition

  EventLinkshell = 0x1169,

  QuestActiveList = 0x2DD,   // updated 7.38
  QuestUpdate = 0x1A4,       // Endwalker Definition
  QuestCompleteList = 0x38A, // updated 7.38

  QuestFinish = 0x2BB,         // Endwalker Definition
  MSQTrackerComplete = 0x166,  // updated 7.38
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x06B, // Endwalker Definition

  QuestTracker = 0x3A7, // updated 7.38

  Mount = 0x09F, // Endwalker Definition

  DirectorVars = 0x3A6,   // Endwalker Definition
  DirectorMsg1 = 0xF084,  // Legacy Definition
  DirectorMsg2 = 0xF0C1,  // Legacy Definition
  DirectorMsg4 = 0x3A9,  // Endwalker Definition
  DirectorMsg8 = 0xF28A,  // Legacy Definition
  DirectorMsg16 = 0xF28C, // Legacy Definition
  DirectorPopUp2 = 0x300,     // Endwalker Definition
  DirectorPopUp4 = 0xF19B,    // Legacy Definition
  DirectorPopUp8 = 0xF271,    // Legacy Definition

  CFAvailableContents = 0xF1FD, // Legacy Definition

  WeatherChange = 0x02F8, // updated 7.38
  PlayerTitleList = 0x1FF, // Endwalker Definition?
  Discovery = 0x11E,       // Endwalker Definition

  EorzeaTimeOffset = 0x398, // Endwalker Definition?

  EquipDisplayFlags = 0x33A, // Endwalker Definition

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x016F,     // Endwalker Definition
  LootMessage = 0x265,      // Endwalker Definition
  ResultDialog = 0x0362, // Endwalker Definition
  DesynthResult = 0x007F, // Endwalker Definition

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x1CC,            // updated 7.38
  LandUpdate = 0x1AB,                   // Endwalker Definition?
  LandAvailability = 0x236,            // Endwalker Definition
  YardObjectSpawn = 0x0D1,              // Endwalker Definition?
  HousingIndoorInitialize = 0x084,      // Endwalker Definition?
  LandPriceUpdate = 0x0F1,              // Endwalker Definition
  LandInfoSign = 0x15F,                 // Endwalker Definition
  LandRename = 0x09B,                   // Endwalker Definition?
  HousingEstateGreeting = 0x298,        // Endwalker Definition?
  HousingUpdateLandFlagsSlot = 0x151,   // Endwalker Definition?
  HousingLandFlags = 0x214,             // updated 7.38
  HousingShowEstateGuestAccess = 0x0E6, // Endwalker Definition?

  HousingObjectInitialize = 0x260,    // updated 7.38
  HousingInternalObjectSpawn = 0x2D7, // Endwalker Definition?

  HousingWardInfo = 0x327,  // Endwalker Definition?
  HousingObjectMove = 0x21b, // Endwalker Definition
  HousingObjectDye = 0x333,  // Endwalker Definition?

  SharedEstateSettingsResponse = 0x25B, // Endwalker Definition?

  LandUpdateHouseName = 0x0B5, // Endwalker Definition?
  LandSetMap = 0x386,         // updated 7.38

  CeremonySetActorAppearance = 0x140, // Endwalker Definition?

  //////////////////////////////////////////////////

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x266,    // Endwalker Definition?

  DutyGauge = 0x02E5, // Legacy Definition

  // daily quest info -> without them sent,  login will take longer...
  DailyQuests = 0x11D,           // updated 7.38
  DailyQuestRepeatFlags = 0x122, // updated 7.38

  MapUpdate = 0x0FF,    // Endwalker Definition
  MapUpdate4 = 0x345,  // Endwalker Definition
  MapUpdate8 = 0x114,  // Endwalker Definition
  MapUpdate16 = 0x2CE, // Endwalker Definition
  MapUpdate32 = 0x205, // Endwalker Definition
  MapUpdate64 = 0x1FC, // Endwalker Definition
  MapUpdate128 = 0x158, // Endwalker Definition

  /// Doman Mahjong //////////////////////////////////////
  MahjongOpenGui = 0x02A4,       // only available in mahjong instance
  MahjongNextRound = 0xF2BD,     // initial hands(baipai), # of riichi(wat), winds, honba, score and stuff
  MahjongPlayerAction = 0x02BE,  // tsumo(as in drawing a tile) called chi/pon/kan/riichi
  MahjongEndRoundTsumo = 0x02BF, // called tsumo
  MahjongEndRoundRon = 0x2C0,    // called ron or double ron (waiting for action must be flagged from discard packet to call)
  MahjongTileDiscard = 0x02C1,   // giri (discarding a tile.) chi(1)/pon(2)/kan(4)/ron(8) flags etc..
  MahjongPlayersInfo = 0xF2C2,   // actor id, name, rating and stuff..
  // 2C3 and 2C4 are currently unknown
  MahjongEndRoundDraw = 0x02C5, // self explanatory
  MahjongEndGame = 0x02C6,      // finished oorasu(all-last) round; shows a result screen.

  /// Airship & Submarine //////////////////////////////////////
  AirshipTimers = 0x0123, // Endwalker Definition
  AirshipStatus = 0x0291, // Endwalker Definition
  AirshipStatusList = 0x023B, // Endwalker Definition
  AirshipExplorationResult = 0x01BD, // Endwalker Definition

  SubmarineTimers = 0x0185, // Endwalker Definition
  SubmarineProgressionStatus = 0xF2DD, // Endwalker Definition
  SubmarineStatusList = 0x03E2, // Endwalker Definition
  SubmarineExplorationResult = 0x02AA, // Endwalker Definition

  EnvironmentControl = 0x02FC, // Endwalker Definition
  RSVData = 0x065,             // Endwalker Definition?
  IslandWorkshopSupplyDemand = 0x013C, // Endwalker Definition
};

/**
 * Client IPC Zone Type Codes.
 */
enum ClientZoneIpcType :
  uint16_t
{
  PingHandler = 0x2AE, // Endwalker Definition
  InitHandler = 0x157, // updated 7.38

  FinishLoadingHandler = 0x3E2, // updated 7.38

  CFCommenceHandler = 0x0242, // Endwalker Definition

  CFCancelHandler = 0x02B2,    // Legacy Definition
  CFRegisterDuty = 0x0312,     // Endwalker Definition
  CFRegisterRoulette = 0x037A, // Legacy Definition
  PlayTimeHandler = 0x0378,    // Endwalker Definition
  LogoutHandler = 0x1CF,       // updated 7.38
  CancelLogout = 0x01e3,       // Endwalker Definition
  CFDutyInfoHandler = 0xF078,  // Legacy Definition

  SocialInviteHandler = 0x00F5, // Endwalker Definition
  SocialReplyHandler = 0x0160, // Endwalker Definition
  CreateCrossWorldLS = 0x9999,    // Legacy Definition

  ChatHandler = 0x246, // Endwalker Definition
  PartyChangeLeaderHandler = 0x0E4, // Endwalker Definition
  PartyLeaveHandler = 0x0373, // Endwalker Definition
  PartyKickHandler = 0x013F, // Endwalker Definition
  PartyDisbandHandler = 0x03BF, // Endwalker Definition

  SocialListHandler = 0x0CD,     // updated 7.38
  SetSearchInfoHandler = 0x01A0, // Endwalker Definition
  ReqSearchInfoHandler = 0x0235,           // Endwalker Definition
  ReqExamineSearchCommentHandler = 0x00E7, // Legacy Definition

  ReqRemovePlayerFromBlacklist = 0x00B4, // Legacy Definition
  BlackListHandler = 0x284,              // Endwalker Definition
  PlayerSearchHandler = 0x037D,          // Legacy Definition

  LinkshellListHandler = 0x0302, // Endwalker Definition

  MarketBoardRequestItemListingInfo = 0x00F4,  // Legacy Definition
  MarketBoardRequestItemListings = 0x0122,     // Legacy Definition
  MarketBoardSearch = 0x0082,                  // Legacy Definition
  MarketBoardPurchaseHandler = 0x0322, // Endwalker Definition

  ReqExamineFcInfo = 0xF37B, // Legacy Definition (prepended F. Conflicts with FinishLoadingHandler 6.38)

  FcInfoReqHandler = 0x33B, // Endwalker Definition

  FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

  ReqMarketWishList = 0x00C3, // Legacy Definition

  ReqJoinNoviceNetwork = 0x0129, // Legacy Definition

  ReqCountdownInitiate = 0x03E3, // Endwalker Definition
  ReqCountdownCancel = 0xF23a,   // Endwalker Definition

  ZoneLineHandler = 0x326,   // Endwalker Definition
  ClientTrigger = 0x0215, // updated 7.38
  ClientTriggerEnvironment = 0x0295, // Endwalker Definition
  DiscoveryHandler = 0x0129, // Endwalker Definition

  SkillHandler = 0x07C,   // Endwalker Definition
  GMCommand1 = 0x02D4,      // updated 7.38
  GMCommand2 = 0x306,     // Endwalker Definition
  AoESkillHandler = 0x0FC, // Endwalker Definition

  UpdatePositionHandler = 0x0256, // Endwalker Definition

  InventoryModifyHandler = 0x023E, // Endwalker Definition

  InventoryEquipRecommendedItems = 0x355, // Endwalker Definition

  ReqPlaceHousingItem = 0x032D, // Endwalker Definition
  BuildPresetHandler = 0x0D9,  // Endwalker Definition

  TalkEventHandler = 0x23A,         // Endwalker Definition
  SayEventHandler = 0x25D,         // Endwalker Definition
  EmoteEventHandler = 0x1B5,        // Endwalker Definition
  WithinRangeEventHandler = 0x38E,  // Endwalker Definition
  OutOfRangeEventHandler = 0x200,   // Endwalker Definition
  EnterTeriEventHandler = 0x105,    // Endwalker Definition
  ShopEventHandler = 0x0148,        // Endwalker Definition
  ReturnEventHandler = 0x07D,       // Endwalker Definition
  TradeReturnEventHandler = 0x166,  // Endwalker Definition
  TradeReturnEventHandler2 = 0x37D, // Endwalker Definition
  EventYield2Handler = 0x0273,      // Endwalker Definition
  EventYield16Handler = 0x0207,     // Legacy Definition

  LinkshellEventHandler = 0x9999,  // unknown
  LinkshellEventHandler1 = 0x9999, // unknown

  ReqEquipDisplayFlagsChange = 0x0150, // Endwalker Definition

  LandRenameHandler = 0x03B7,           // Endwalker Definition
  HousingUpdateHouseGreeting = 0x03A7,  // Endwalker Definition
  HousingUpdateObjectPosition = 0xF157, // Endwalker Definition
  HousingEditExterior = 0x028C,         // Endwalker Definition
  HousingEditInterior = 0x0336,         // Endwalker Definition

  SetSharedEstateSettings = 0x00D2, // Legacy Definition

  UpdatePositionInstance = 0x0227, // Endwalker Definition

  PerformNoteHandler = 0x0243, // Legacy Definition
  Dive = 0x018C,                    // updated 6.30h
};

////////////////////////////////////////////////////////////////////////////////
/// Chat Connection IPC Codes
/**
 * Server IPC Chat Type Codes.
 */
enum ServerChatIpcType :
  uint16_t
{
  Tell = 0x0064,              // updated for sb
  ChannelChat = 0x0065,
  PublicContentTell = 0xF0FB, // added 4.5, this is used when receiving a /tell in PublicContent instances such as Eureka or Bozja (prepended F conflicts with TradeReturnEventHandler 6.38)
  TellErrNotFound = 0x0066,

  FreeCompanyEvent = 0x012C, // added 5.0
};

/**
 * Client IPC Chat Type Codes.
 */
enum ClientChatIpcType :
  uint16_t
{
  TellReq = 0x0064,
  ChannelChatReq = 0x0065,
  PublicContentTellReq = 0x0326, // updated 5.35 hotfix, this is used when sending a /tell in PublicContent instances such as Eureka or Bozja
};

}

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
