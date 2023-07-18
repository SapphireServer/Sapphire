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
  Ping = 0x349, // updated 6.45
  Init = 0x3bd, // updated 6.45

  ActorFreeSpawn = 0x3a6, // updated 6.45

  InitZone = 0xd8,       // updated 6.45
  PrepareZoning = 0x3a8, // updated 6.45

  EffectResult = 0xd2,       // updated 6.45
  EffectResultBasic = 0x34f, // updated 6.45

  ActorControl = 0x88,       // updated 6.45
  ActorControlTarget = 0xa1, // updated 6.45
  ActorControlSelf = 0x2f7,  // updated 6.45
  ActorCast = 0x330,         // updated 6.45
  ActorSetPos = 0x196,       // updated 6.45
  ActorMove = 0x1f1,         // updated 6.45
  ActorGauge = 0x80,         // updated 6.45

  /*!
   * @brief Used when resting
   */
  UpdateHpMpTp = 0x2fa,     // updated 6.45
  UpdateClassInfo = 0x3a5, // updated 6.45

  ///////////////////////////////////////////////////

  ChatBanned = 0xF06B,
  Playtime = 0x2e5,         // updated 6.45
  Logout = 0x132,           // updated 6.45
  CFNotify = 0x126,         // updated 6.45
  CFMemberStatus = 0x0079,
  CFDutyInfo = 0x105,       // updated 6.45
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0x211,  // updated 6.45
  CFCancel = 0xcc,          // updated 6.45
  SocialRequestError = 0xF0AD,

  CFRegistered = 0x029F,          // updated 5.58h
  SocialRequestResponse = 0x27f,  // updated 6.45
  SocialMessage = 0x03CB,         // updated 5.58h
  SocialMessage2 = 0x01D7,        // updated 5.58h
  CancelAllianceForming = 0xF0C6, // updated 4.2

  LogMessage = 0x16b, // updated 6.45

  Chat = 0x218, // updated 6.45
  PartyChat = 0x0065,

  WorldVisitList = 0xF0FE, // added 4.5

  SocialList = 0x208, // updated 6.45

  ExamineSearchInfo = 0x6b,    // updated 6.45
  UpdateSearchInfo = 0x2ce,    // updated 6.45
  InitSearchInfo = 0xf9,       // updated 6.45
  ExamineSearchComment = 0xce, // updated 6.45

  ServerNoticeShort = 0x0333, // updated 5.58h
  ServerNotice = 0x194,       // updated 6.45
  SystemLogMessage = 0x100,   // updated 6.45
  SetOnlineStatus = 0x21d,    // updated 6.45

  CountdownInitiate = 0x351, // updated 6.45
  CountdownCancel = 0xc8,    // updated 6.45

  PlayerAddedToBlacklist = 0x305,     // updated 6.45
  PlayerRemovedFromBlacklist = 0x160, // updated 6.45
  BlackList = 0x85,                   // updated 6.45

  LinkshellList = 0x2f0,           // updated 6.45
  CrossWorldLinkshellList = 0x11a, // updated 6.45
  FellowshipList = 0x23a,          // updated 6.45

  MailDeleteRequest = 0x236, // updated 6.45

  // 12D - 137 - constant gap between 4.5x -> 5.0
  ReqMoogleMailList = 0xF138,      // updated 5.0
  ReqMoogleMailLetter = 0xF139,    // updated 5.0
  MailLetterNotification = 0x013A, // updated 5.0

  MarketTaxRates = 0x01F8, // updated 5.35h

  MarketBoardSearchResult = 0x2fd,       // updated 6.45
  MarketBoardItemListingCount = 0x26b,   // updated 6.45
  MarketBoardItemListingHistory = 0x3cb, // updated 6.45
  MarketBoardItemListing = 0xeb,         // updated 6.45
  MarketBoardPurchase = 0x17b,           // updated 6.45
  ItemMarketBoardInfo = 0x143,           // updated 6.45

  CharaFreeCompanyTag = 0x013B,   // updated 4.5
  FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
  FreeCompanyInfo = 0x231,        // updated 6.45
  FreeCompanyDialog = 0x23e,      // updated 6.45
  ExamineFreeCompanyInfo = 0x202, // updated 6.45

  FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

  StatusEffectList = 0x3ce,       // updated 6.45
  EurekaStatusEffectList = 0x198, // updated 6.45
  BossStatusEffectList = 0x2eb,   // updated 6.45
  StatusEffectList2 = 0x2b7,      // updated 6.45
  StatusEffectList3 = 0xee,       // updated 6.45
  Effect = 0x1e1,                 // updated 6.45
  AoeEffect8 = 0x181,             // updated 6.45
  AoeEffect16 = 0x365,            // updated 6.45
  AoeEffect24 = 0x2ec,            // updated 6.45
  AoeEffect32 = 0x103,            // updated 6.45
  PersistantEffect = 0xee,        // updated 6.45

  PlaceFieldMarker = 0x172,      // updated 6.45
  PlaceFieldMarkerPreset = 0xd3, // updated 6.45

  GCAffiliation = 0x1b9, // updated 6.45

  PlayerSpawn = 0x2d3, // updated 6.45
  NpcSpawn = 0x179,    // updated 6.45
  NpcSpawn2 = 0x3d6,   // updated 6.45

  SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

  PartyList = 0x36d,          // updated 6.45
  PartyMessage = 0x13e,       // updated 6.45
  HateRank = 0x8f,            // updated 6.45
  HateList = 0xe3,            // updated 6.45
  ObjectSpawn = 0x240,        // updated 6.45
  ObjectDespawn = 0x2e1,      // updated 6.45
  SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x2c5,        // updated 6.45
  PlayerStats = 0x30c,        // updated 6.45
  ActorOwner = 0x2c5,         // updated 6.45
  PlayerStateFlags = 0x127,   // updated 6.45
  PlayerClassInfo = 0x1a2,    // updated 6.45
  PlayerUpdateLook = 0x335,   // updated 6.45
  CharaVisualEffect = 0x252,  // updated 6.45

  ModelEquip = 0x9c,    // updated 6.45
  Examine = 0xed,       // updated 6.45
  CharaNameReq = 0x1c5, // updated 6.45

  // nb: see #565 on github
  UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
  RetainerSaleHistory = 0x111,          // updated 6.45
  RetainerInformation = 0x2f8,          // updated 6.45

  SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

  ItemInfo = 0x333,                   // updated 6.45
  ContainerInfo = 0x343,              // updated 6.45
  InventoryTransactionFinish = 0x2ee, // updated 6.45
  InventoryTransaction = 0x1d2,       // updated 6.45
  CurrencyCrystalInfo = 0x26a,        // updated 6.45

  InventoryActionAck = 0xbd,   // updated 6.45
  UpdateInventorySlot = 0x13f, // updated 6.45

  HuntingLogEntry = 0x15a, // updated 6.45

  EventPlay = 0x14a,    // updated 6.45
  EventPlay4 = 0x1a5,   // updated 6.45
  EventPlay8 = 0x3b7,   // updated 6.45
  EventPlay16 = 0x3c4,  // updated 6.45
  EventPlay32 = 0x108,  // updated 6.45
  EventPlay64 = 0x3e4,  // updated 6.45
  EventPlay128 = 0x320, // updated 6.45
  EventPlay255 = 0x151, // updated 6.45
  EventStart = 0x133,   // updated 6.45
  EventFinish = 0x125,  // updated 6.45

  EventContinue = 0x11d, // updated 6.45

  EventLinkshell = 0x1169,

  QuestActiveList = 0x10c,   // updated 6.45
  QuestUpdate = 0x227,       // updated 6.45
  QuestCompleteList = 0x239, // updated 6.45

  QuestFinish = 0x24f,         // updated 6.45
  MSQTrackerComplete = 0x232,  // updated 6.45
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x0220, // updated 5.58h

  QuestTracker = 0x192, // updated 6.45

  Mount = 0x15e, // updated 6.45

  DirectorVars = 0x27e,       // updated 6.45
  SomeDirectorUnk1 = 0x0084,  // updated 5.18
  SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
  SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
  SomeDirectorUnk8 = 0x028A,  // updated 5.18
  SomeDirectorUnk16 = 0x028C, // updated 5.18
  DirectorPopUp = 0x03DF,     // updated 5.58h
  DirectorPopUp4 = 0x019B,    // updated 5.58h
  DirectorPopUp8 = 0x0271,    // updated 5.58h

  CFAvailableContents = 0xF1FD, // updated 4.2

  WeatherChange = 0xf0,    // updated 6.45
  PlayerTitleList = 0x144, // updated 6.45
  Discovery = 0x1a4,       // updated 6.45

  EorzeaTimeOffset = 0x18f, // updated 6.45

  EquipDisplayFlags = 0x69, // updated 6.45

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x0287,     // updated 5.58h
  LootMessage = 0x14b,      // updated 6.45
  ResultDialog = 0xc2,      // updated 6.45
  DesynthResult = 0x1df,    // updated 6.45

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x3d2,            // updated 6.45
  LandUpdate = 0x101,                   // updated 6.45
  LandAvailability = 0x273,             // updated 6.45
  YardObjectSpawn = 0x2ba,              // updated 6.45
  HousingIndoorInitialize = 0x2fe,      // updated 6.45
  LandPriceUpdate = 0x1b4,              // updated 6.45
  LandInfoSign = 0x13d,                 // updated 6.45
  LandRename = 0x27b,                   // updated 6.45
  HousingEstateGreeting = 0x1c9,        // updated 6.45
  HousingUpdateLandFlagsSlot = 0x34b,   // updated 6.45
  HousingLandFlags = 0x12b,             // updated 6.45
  HousingShowEstateGuestAccess = 0xfc,  // updated 6.45

  HousingObjectInitialize = 0x19c,    // updated 6.45
  HousingInternalObjectSpawn = 0x1a0, // updated 6.45

  HousingWardInfo = 0x284,  // updated 6.45
  HousingObjectMove = 0xaa, // updated 6.45
  HousingObjectDye = 0x33d, // updated 6.45

  SharedEstateSettingsResponse = 0x32c, // updated 6.45

  LandUpdateHouseName = 0x2d2, // updated 6.45
  LandSetMap = 0x36f,          // updated 6.45

  CeremonySetActorAppearance = 0x2e7, // updated 6.45

  //////////////////////////////////////////////////

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x2a8,    // updated 6.45

  DutyGauge = 0x02E5, // updated 5.58h

  // daily quest info -> without them sent,  login will take longer...
  DailyQuests = 0x301,           // updated 6.45
  DailyQuestRepeatFlags = 0x36a, // updated 6.45

  MapUpdate = 0x2f5,    // updated 6.45
  MapUpdate4 = 0x185,   // updated 6.45
  MapUpdate8 = 0x32e,   // updated 6.45
  MapUpdate16 = 0x329,  // updated 6.45
  MapUpdate32 = 0x11c,  // updated 6.45
  MapUpdate64 = 0x2be,  // updated 6.45
  MapUpdate128 = 0x1f8, // updated 6.45

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
  AirshipTimers = 0x75,             // updated 6.45
  AirshipStatus = 0x7b,             // updated 6.45
  AirshipStatusList = 0x391,        // updated 6.45
  AirshipExplorationResult = 0x304, // updated 6.45

  SubmarineTimers = 0xcd,             // updated 6.45
  SubmarineProgressionStatus = 0x22d, // updated 6.45
  SubmarineStatusList = 0x1bc,        // updated 6.45
  SubmarineExplorationResult = 0x34a, // updated 6.45

  EnvironmentControl = 0x29f,         // updated 6.45
  RSVData = 0x3ca,                    // updated 6.45
  IslandWorkshopSupplyDemand = 0x1f4, // updated 6.45
};

/**
 * Client IPC Zone Type Codes.
 */
enum ClientZoneIpcType :
  uint16_t
{
  PingHandler = 0x3bc, // updated 6.45
  InitHandler = 0x372, // updated 6.45

  FinishLoadingHandler = 0x3bd, // updated 6.45

  CFCommenceHandler = 0x0381, // updated 5.58h

  CFCancelHandler = 0x02B2,    // updated 5.58h
  CFRegisterDuty = 0x01BD,     // updated 5.58h
  CFRegisterRoulette = 0x037A, // updated 5.58h
  PlayTimeHandler = 0x02B7,    // updated 5.58h
  LogoutHandler = 0x2b3,       // updated 6.45
  CancelLogout = 0x01e3,       // updated 6.31h
  CFDutyInfoHandler = 0xF078,  // updated 4.2

  SocialReqSendHandler = 0x00D7,  // updated 5.58h
  SocialResponseHandler = 0x023B, // updated 5.58h
  CreateCrossWorldLS = 0x9999,    // updated 5.58h

  ChatHandler = 0x31f, // updated 6.45
  PartyChatHandler = 0x0065, PartySetLeaderHandler = 0x036C,  // updated 5.58h
  LeavePartyHandler = 0x019D,      // updated 5.58h
  KickPartyMemberHandler = 0x0262, // updated 5.58h
  DisbandPartyHandler = 0x0276,    // updated 5.58h

  SocialListHandler = 0x206,               // updated 6.40
  SetSearchInfoHandler = 0x129,            // updated 6.45
  ReqSearchInfoHandler = 0x03b0,           // updated 6.31h
  ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

  ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
  BlackListHandler = 0x204,              // updated 6.45
  PlayerSearchHandler = 0x037D,          // updated 5.58h

  LinkshellListHandler = 0x03B6, // updated 5.58h

  MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58h
  MarketBoardRequestItemListings = 0x0122,    // updated 5.58h
  MarketBoardSearch = 0x0082,                 // updated 5.58h
  MarketBoardPurchaseHandler = 0x66,          // updated 6.45

  ReqExamineFcInfo = 0xF37B, // updated 5.58h (prepended F. Conflicts with FinishLoadingHandler 6.38)

  FcInfoReqHandler = 0x9999, // unknown

  FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

  ReqMarketWishList = 0x00C3, // updated 5.58h

  ReqJoinNoviceNetwork = 0x0129, // updated 4.2

  ReqCountdownInitiate = 0x03e1, // updated 6.31h
  ReqCountdownCancel = 0x023a,   // updated 6.31h

  ZoneLineHandler = 0x251,   // updated 6.45
  ClientTrigger = 0xdf,      // updated 6.45
  DiscoveryHandler = 0x038B, // updated 5.58h

  SkillHandler = 0x1eb,   // updated 6.45
  GMCommand1 = 0xf5,      // updated 6.45
  GMCommand2 = 0x2ea,     // updated 6.45
  AoESkillHandler = 0x78, // updated 6.45

  UpdatePositionHandler = 0xa5, // updated 6.45

  InventoryModifyHandler = 0x140, // updated 6.45

  InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

  ReqPlaceHousingItem = 0x02D4, // updated 5.58h
  BuildPresetHandler = 0x0223,  // updated 5.58h

  TalkEventHandler = 0x1f6,         // updated 6.45
  EmoteEventHandler = 0x00B0,       // updated 5.58h
  WithinRangeEventHandler = 0x36e,  // updated 6.45
  OutOfRangeEventHandler = 0x2dd,   // updated 6.45
  EnterTeriEventHandler = 0x165,    // updated 6.45
  ShopEventHandler = 0x0384,        // updated 5.58h
  ReturnEventHandler = 0xa1,        // updated 6.45
  TradeReturnEventHandler = 0x2fa,  // updated 6.45
  TradeReturnEventHandler2 = 0x1e1, // updated 6.45
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

  UpdatePositionInstance = 0x95, // updated 6.45

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
