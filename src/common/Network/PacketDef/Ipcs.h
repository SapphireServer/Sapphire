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
  Ping = 0x319, // updated 6.41
  Init = 0x35d, // updated 6.41

  ActorFreeSpawn = 0x72, // updated 6.41

  InitZone = 0x1d5,      // updated 6.41
  PrepareZoning = 0x39c, // updated 6.41

  EffectResult = 0x10c,      // updated 6.41
  EffectResultBasic = 0x39f, // updated 6.41

  ActorControl = 0x19d,       // updated 6.41
  ActorControlTarget = 0x2fe, // updated 6.41
  ActorControlSelf = 0xa6,    // updated 6.41
  ActorCast = 0x1c0,          // updated 6.41
  ActorSetPos = 0x15f,        // updated 6.41
  ActorMove = 0x2c4,          // updated 6.41
  ActorGauge = 0x26d,         // updated 6.41

  /*!
   * @brief Used when resting
   */
  UpdateHpMpTp = 0x316,     // updated 6.41
  UpdateClassInfo = 0xa0, // updated 6.41

  ///////////////////////////////////////////////////

  ChatBanned = 0xF06B,
  Playtime = 0x3a3, // updated 6.41
  Logout = 0x363,   // updated 6.41
  CFNotify = 0x21a, // updated 6.41
  CFMemberStatus = 0x0079,
  CFDutyInfo = 0xba, // updated 6.41
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0xfb,  // updated 6.41
  CFCancel = 0x2ad,        // updated 6.41
  SocialRequestError = 0xF0AD,

  CFRegistered = 0x029F,          // updated 5.58h
  SocialRequestResponse = 0x11c,  // updated 6.41
  SocialMessage = 0x03CB,         // updated 5.58h
  SocialMessage2 = 0x01D7,        // updated 5.58h
  CancelAllianceForming = 0xF0C6, // updated 4.2

  LogMessage = 0x133, // updated 6.41

  Chat = 0x283, // updated 6.41
  PartyChat = 0x0065,

  WorldVisitList = 0xF0FE, // added 4.5

  SocialList = 0x23e, // updated 6.41

  ExamineSearchInfo = 0x3da,   // updated 6.41
  UpdateSearchInfo = 0x92,     // updated 6.41
  InitSearchInfo = 0xd8,       // updated 6.41
  ExamineSearchComment = 0x7e, // updated 6.41

  ServerNoticeShort = 0x0333, // updated 5.58h
  ServerNotice = 0x6f,        // updated 6.41
  SystemLogMessage = 0x39d,   // updated 6.41
  SetOnlineStatus = 0xd9,     // updated 6.41

  CountdownInitiate = 0x128, // updated 6.41
  CountdownCancel = 0x377,   // updated 6.41

  PlayerAddedToBlacklist = 0x3b3,    // updated 6.41
  PlayerRemovedFromBlacklist = 0xe4, // updated 6.41
  BlackList = 0x3cc,                 // updated 6.41

  LinkshellList = 0x1b5,           // updated 6.41
  CrossWorldLinkshellList = 0x113, // updated 6.41
  FellowshipList = 0x2a9,          // updated 6.41

  MailDeleteRequest = 0x2a2, // updated 6.41

  // 12D - 137 - constant gap between 4.5x -> 5.0
  ReqMoogleMailList = 0xF138,      // updated 5.0
  ReqMoogleMailLetter = 0xF139,    // updated 5.0
  MailLetterNotification = 0x013A, // updated 5.0

  MarketTaxRates = 0x01F8, // updated 5.35h

  MarketBoardSearchResult = 0x19f,      // updated 6.41
  MarketBoardItemListingCount = 0x67,   // updated 6.41
  MarketBoardItemListingHistory = 0x69, // updated 6.41
  MarketBoardItemListing = 0x221,       // updated 6.41
  MarketBoardPurchase = 0x1b6,          // updated 6.41
  ItemMarketBoardInfo = 0xfe,           // updated 6.41

  CharaFreeCompanyTag = 0x013B,  // updated 4.5
  FreeCompanyBoardMsg = 0x03DB,  // updated 5.58h
  FreeCompanyInfo = 0xce,        // updated 6.41
  FreeCompanyDialog = 0x33e,     // updated 6.41
  ExamineFreeCompanyInfo = 0x95, // updated 6.41

  FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

  StatusEffectList = 0x171,      // updated 6.41
  EurekaStatusEffectList = 0xff, // updated 6.41
  BossStatusEffectList = 0xda,   // updated 6.41
  StatusEffectList2 = 0x32f,     // updated 6.41
  StatusEffectList3 = 0x9e,      // updated 6.41
  Effect = 0x1bb,                // updated 6.41
  AoeEffect8 = 0x2ba,            // updated 6.41
  AoeEffect16 = 0x27f,           // updated 6.41
  AoeEffect24 = 0x93,            // updated 6.41
  AoeEffect32 = 0x2a6,           // updated 6.41
  PersistantEffect = 0x9e,       // updated 6.41

  PlaceFieldMarker = 0x139,      // updated 6.41
  PlaceFieldMarkerPreset = 0xcc, // updated 6.41

  GCAffiliation = 0x1e0, // updated 6.41

  PlayerSpawn = 0x1a7, // updated 6.41
  NpcSpawn = 0xac,     // updated 6.41
  NpcSpawn2 = 0x9b,    // updated 6.41

  SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

  PartyList = 0x219,          // updated 6.41
  PartyMessage = 0x3cf,       // updated 6.41
  HateRank = 0x2d2,           // updated 6.41
  HateList = 0x17f,           // updated 6.41
  ObjectSpawn = 0x295,        // updated 6.41
  ObjectDespawn = 0x386,      // updated 6.41
  SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x3e6,        // updated 6.41
  PlayerStats = 0x343,        // updated 6.41
  ActorOwner = 0x3e6,         // updated 6.41
  PlayerStateFlags = 0xa2,    // updated 6.41
  PlayerClassInfo = 0x1c5,    // updated 6.41
  PlayerUpdateLook = 0x351,   // updated 6.41
  CharaVisualEffect = 0xf4,   // updated 6.41

  ModelEquip = 0x36e,   // updated 6.41
  Examine = 0x228,      // updated 6.41
  CharaNameReq = 0x1ff, // updated 6.41

  // nb: see #565 on github
  UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
  RetainerSaleHistory = 0xcf,           // updated 6.41
  RetainerInformation = 0x229,          // updated 6.41

  SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

  ItemInfo = 0x388,                   // updated 6.41
  ContainerInfo = 0x21f,              // updated 6.41
  InventoryTransactionFinish = 0x1d1, // updated 6.41
  InventoryTransaction = 0x252,       // updated 6.41
  CurrencyCrystalInfo = 0x1a4,        // updated 6.41

  InventoryActionAck = 0x34c,  // updated 6.41
  UpdateInventorySlot = 0x79,  // updated 6.41

  HuntingLogEntry = 0x138, // updated 6.41

  EventPlay = 0x36f,    // updated 6.41
  EventPlay4 = 0x124,   // updated 6.41
  EventPlay8 = 0x9a,    // updated 6.41
  EventPlay16 = 0x2f2,  // updated 6.41
  EventPlay32 = 0xe3,   // updated 6.41
  EventPlay64 = 0x38f,  // updated 6.41
  EventPlay128 = 0x197, // updated 6.41
  EventPlay255 = 0x202, // updated 6.41
  EventStart = 0x3a6,   // updated 6.41
  EventFinish = 0x2fa,  // updated 6.41

  EventContinue = 0x1f2, // updated 6.41

  EventLinkshell = 0x1169,

  QuestActiveList = 0x257,   // updated 6.41
  QuestUpdate = 0x306,       // updated 6.41
  QuestCompleteList = 0x2aa, // updated 6.41

  QuestFinish = 0xa1,          // updated 6.41
  MSQTrackerComplete = 0x2f8,  // updated 6.41
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x0220, // updated 5.58h

  QuestTracker = 0x109, // updated 6.41

  Mount = 0x244, // updated 6.41

  DirectorVars = 0x192,       // updated 6.41
  SomeDirectorUnk1 = 0x0084,  // updated 5.18
  SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
  SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
  SomeDirectorUnk8 = 0x028A,  // updated 5.18
  SomeDirectorUnk16 = 0x028C, // updated 5.18
  DirectorPopUp = 0x03DF,     // updated 5.58h
  DirectorPopUp4 = 0x019B,    // updated 5.58h
  DirectorPopUp8 = 0x0271,    // updated 5.58h

  CFAvailableContents = 0xF1FD, // updated 4.2

  WeatherChange = 0x2d9,   // updated 6.41
  PlayerTitleList = 0x380, // updated 6.41
  Discovery = 0x1d0,       // updated 6.41

  EorzeaTimeOffset = 0x108, // updated 6.41

  EquipDisplayFlags = 0x259, // updated 6.41

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x0287,     // updated 5.58h
  LootMessage = 0x360,      // updated 6.41
  ResultDialog = 0x7d,      // updated 6.41
  DesynthResult = 0x325,    // updated 6.41

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x2ef,            // updated 6.41
  LandUpdate = 0x1ed,                   // updated 6.41
  LandAvailability = 0x284,             // updated 6.41
  YardObjectSpawn = 0x167,              // updated 6.41
  HousingIndoorInitialize = 0x174,      // updated 6.41
  LandPriceUpdate = 0x16c,              // updated 6.41
  LandInfoSign = 0x2f4,                 // updated 6.41
  LandRename = 0x19b,                   // updated 6.41
  HousingEstateGreeting = 0xa7,         // updated 6.41
  HousingUpdateLandFlagsSlot = 0x333,   // updated 6.41
  HousingLandFlags = 0x1c4,             // updated 6.41
  HousingShowEstateGuestAccess = 0x296, // updated 6.41

  HousingObjectInitialize = 0x251,   // updated 6.41
  HousingInternalObjectSpawn = 0xf1, // updated 6.41

  HousingWardInfo = 0x110,  // updated 6.41
  HousingObjectMove = 0x8b, // updated 6.41
  HousingObjectDye = 0x154, // updated 6.41

  SharedEstateSettingsResponse = 0x254, // updated 6.41

  LandUpdateHouseName = 0x14c, // updated 6.41
  LandSetMap = 0x35e,          // updated 6.41

  CeremonySetActorAppearance = 0xf7, // updated 6.41

  //////////////////////////////////////////////////

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x162,    // updated 6.41

  DutyGauge = 0x02E5, // updated 5.58h

  // daily quest info -> without them sent,  login will take longer...
  DailyQuests = 0x2d6,           // updated 6.41
  DailyQuestRepeatFlags = 0x337, // updated 6.41

  MapUpdate = 0x2ee,   // updated 6.41
  MapUpdate4 = 0x3ba,  // updated 6.41
  MapUpdate8 = 0x272,  // updated 6.41
  MapUpdate16 = 0x1ab, // updated 6.41
  MapUpdate32 = 0x3bc, // updated 6.41
  MapUpdate64 = 0x1ca, // updated 6.41
  MapUpdate128 = 0xc7, // updated 6.41

  /// Doman Mahjong //////////////////////////////////////
  MahjongOpenGui = 0x02A4,       // only available in mahjong instance
  MahjongNextRound = 0x02BD,     // initial hands(baipai), # of riichi(wat), winds, honba, score and stuff
  MahjongPlayerAction = 0x02BE,  // tsumo(as in drawing a tile) called chi/pon/kan/riichi
  MahjongEndRoundTsumo = 0x02BF, // called tsumo
  MahjongEndRoundRon = 0x2C0,    // called ron or double ron (waiting for action must be flagged from discard packet to call)
  MahjongTileDiscard = 0x02C1,   // giri (discarding a tile.) chi(1)/pon(2)/kan(4)/ron(8) flags etc..
  MahjongPlayersInfo = 0xF2C2,   // actor id, name, rating and stuff..
  // 2C3 and 2C4 are currently unknown
  MahjongEndRoundDraw = 0x02C5, // self explanatory
  MahjongEndGame = 0x02C6,      // finished oorasu(all-last) round; shows a result screen.

  /// Airship & Submarine //////////////////////////////////////
  AirshipTimers = 0x3c5,            // updated 6.41
  AirshipStatus = 0x172,            // updated 6.41
  AirshipStatusList = 0x265,        // updated 6.41
  AirshipExplorationResult = 0x21e, // updated 6.41

  SubmarineTimers = 0x372,            // updated 6.41
  SubmarineProgressionStatus = 0x1ea, // updated 6.41
  SubmarineStatusList = 0x383,        // updated 6.41
  SubmarineExplorationResult = 0x1d3, // updated 6.41

  EnvironmentControl = 0x2e0,         // updated 6.41
  RSVData = 0x8e,                     // updated 6.41
  IslandWorkshopSupplyDemand = 0x27c, // updated 6.41
};

/**
 * Client IPC Zone Type Codes.
 */
enum ClientZoneIpcType :
  uint16_t
{
  PingHandler = 0x8f,  // updated 6.41
  InitHandler = 0x260, // updated 6.41

  FinishLoadingHandler = 0x35d, // updated 6.41

  CFCommenceHandler = 0x0381, // updated 5.58h

  CFCancelHandler = 0x02B2,    // updated 5.58h
  CFRegisterDuty = 0x01BD,     // updated 5.58h
  CFRegisterRoulette = 0x037A, // updated 5.58h
  PlayTimeHandler = 0x02B7,    // updated 5.58h
  LogoutHandler = 0x11f,       // updated 6.41
  CancelLogout = 0x01e3,       // updated 6.31h
  CFDutyInfoHandler = 0xF078,  // updated 4.2

  SocialReqSendHandler = 0x00D7,  // updated 5.58h
  SocialResponseHandler = 0x023B, // updated 5.58h
  CreateCrossWorldLS = 0x9999,    // updated 5.58h

  ChatHandler = 0x3c1, // updated 6.41
  PartyChatHandler = 0x0065, PartySetLeaderHandler = 0x036C,  // updated 5.58h
  LeavePartyHandler = 0x019D,      // updated 5.58h
  KickPartyMemberHandler = 0x0262, // updated 5.58h
  DisbandPartyHandler = 0x0276,    // updated 5.58h

  SocialListHandler = 0x206,               // updated 6.40
  SetSearchInfoHandler = 0x84,             // updated 6.41
  ReqSearchInfoHandler = 0x03b0,           // updated 6.31h
  ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

  ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
  BlackListHandler = 0xad,               // updated 6.41
  PlayerSearchHandler = 0x037D,          // updated 5.58h

  LinkshellListHandler = 0x03B6, // updated 5.58h

  MarketBoardRequestItemListingInfo = 0x00F4,  // updated 5.58h
  MarketBoardRequestItemListings = 0x0122,     // updated 5.58h
  MarketBoardSearch = 0x0082,                  // updated 5.58h
  MarketBoardPurchaseHandler = 0x31e,          // updated 6.41

  ReqExamineFcInfo = 0xF37B, // updated 5.58h (prepended F. Conflicts with FinishLoadingHandler 6.38)

  FcInfoReqHandler = 0x9999, // unknown

  FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

  ReqMarketWishList = 0x00C3, // updated 5.58h

  ReqJoinNoviceNetwork = 0x0129, // updated 4.2

  ReqCountdownInitiate = 0x03e1, // updated 6.31h
  ReqCountdownCancel = 0x023a,   // updated 6.31h

  ZoneLineHandler = 0x12b,   // updated 6.41
  ClientTrigger = 0x23f,     // updated 6.41
  DiscoveryHandler = 0x038B, // updated 5.58h

  SkillHandler = 0x94,     // updated 6.41
  GMCommand1 = 0x205,      // updated 6.41
  GMCommand2 = 0x193,      // updated 6.41
  AoESkillHandler = 0x22e, // updated 6.41

  UpdatePositionHandler = 0x2df, // updated 6.41

  InventoryModifyHandler = 0x322, // updated 6.41

  InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

  ReqPlaceHousingItem = 0x02D4, // updated 5.58h
  BuildPresetHandler = 0x0223,  // updated 5.58h

  TalkEventHandler = 0x384,         // updated 6.41
  EmoteEventHandler = 0x00B0,       // updated 5.58h
  WithinRangeEventHandler = 0x1df,  // updated 6.41
  OutOfRangeEventHandler = 0x13b,   // updated 6.41
  EnterTeriEventHandler = 0x248,    // updated 6.41
  ShopEventHandler = 0x0384,        // updated 5.58h
  ReturnEventHandler = 0x2fe,       // updated 6.41
  TradeReturnEventHandler = 0x316,  // updated 6.41
  TradeReturnEventHandler2 = 0x1bb, // updated 6.41
  EventYield2Handler = 0x021D,      // updated 5.58h
  EventYield16Handler = 0x0207,     // updated 5.58h

  LinkshellEventHandler = 0x9999,  // unknown
  LinkshellEventHandler1 = 0x9999, // unknown

  ReqEquipDisplayFlagsChange = 0x03BC, // updated 6.30h

  LandRenameHandler = 0x028E,           // updated 5.58h
  HousingUpdateHouseGreeting = 0x0343,  // updated 5.58h
  HousingUpdateObjectPosition = 0x9999, // unknown
  HousingEditExterior = 0x027B,         // updated 5.58h
  HousingEditInterior = 0x02E3,         // updated 5.58h

  SetSharedEstateSettings = 0x00D2, // updated 5.58h

  UpdatePositionInstance = 0x212, // updated 6.41

  PerformNoteHandler = 0x0243, // updated 5.58h

  WorldInteractionHandler = 0x0274, // updated 5.58h
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
  PublicContentTellReq = 0x0326, // updated 5.35 hotfix, this is used when sending a /tell in PublicContent instances such as Eureka or Bozja
};

}

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
