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
  Ping = 0x80,  // updated 6.40h
  Init = 0x281, // updated 6.40h

  ActorFreeSpawn = 0x227, // updated 6.40h

  InitZone = 0x2d0,      // updated 6.40h
  PrepareZoning = 0x18a, // updated 6.40h

  EffectResult = 0x140,      // updated 6.40h
  EffectResultBasic = 0x366, // updated 6.40h

  ActorControl = 0x3a0,       // updated 6.40h
  ActorControlTarget = 0x3bd, // updated 6.40h
  ActorControlSelf = 0x286,   // updated 6.40h
  ActorCast = 0x34d,          // updated 6.40h
  ActorSetPos = 0x2bb,        // updated 6.40h
  ActorMove = 0x38d,          // updated 6.40h
  ActorGauge = 0x24f,         // updated 6.40h

  /*!
   * @brief Used when resting
   */
  UpdateHpMpTp = 0x8e,     // updated 6.40h
  UpdateClassInfo = 0x158, // updated 6.40h

  ///////////////////////////////////////////////////

  ChatBanned = 0xF06B,
  Playtime = 0x18f, // updated 6.40h
  Logout = 0x18b,   // updated 6.40h
  CFNotify = 0x2d6, // updated 6.40h
  CFMemberStatus = 0x0079,
  CFDutyInfo = 0x189, // updated 6.40h
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0x2f3, // updated 6.40h
  CFCancel = 0x1c5,        // updated 6.40h
  SocialRequestError = 0xF0AD,

  CFRegistered = 0x029F,          // updated 5.58h
  SocialRequestResponse = 0x29b,  // updated 6.40h
  SocialMessage = 0x03CB,         // updated 5.58h
  SocialMessage2 = 0x01D7,        // updated 5.58h
  CancelAllianceForming = 0xF0C6, // updated 4.2

  LogMessage = 0x2aa, // updated 6.40h

  Chat = 0x38a, // updated 6.40h
  PartyChat = 0x0065,

  WorldVisitList = 0xF0FE, // added 4.5

  SocialList = 0x37d, // updated 6.40h

  ExamineSearchInfo = 0x11b,    // updated 6.40h
  UpdateSearchInfo = 0xae,      // updated 6.40h
  InitSearchInfo = 0x273,       // updated 6.40h
  ExamineSearchComment = 0x39b, // updated 6.40h

  ServerNoticeShort = 0x0333, // updated 5.58h
  ServerNotice = 0x177,       // updated 6.40h
  SystemLogMessage = 0x193,   // updated 6.40h
  SetOnlineStatus = 0x127,    // updated 6.40h

  CountdownInitiate = 0x29f, // updated 6.40h
  CountdownCancel = 0xe5,    // updated 6.40h

  PlayerAddedToBlacklist = 0x1c3,     // updated 6.40h
  PlayerRemovedFromBlacklist = 0x14f, // updated 6.40h
  BlackList = 0x1d0,                  // updated 6.40h

  LinkshellList = 0x337,          // updated 6.40h
  CrossWorldLinkshellList = 0x83, // updated 6.40h
  FellowshipList = 0xdb,          // updated 6.40h

  MailDeleteRequest = 0xfc, // updated 6.40h

  // 12D - 137 - constant gap between 4.5x -> 5.0
  ReqMoogleMailList = 0xF138,      // updated 5.0
  ReqMoogleMailLetter = 0xF139,    // updated 5.0
  MailLetterNotification = 0x013A, // updated 5.0

  MarketTaxRates = 0x01F8, // updated 5.35h

  MarketBoardSearchResult = 0x81,        // updated 6.40h
  MarketBoardItemListingCount = 0x97,    // updated 6.40h
  MarketBoardItemListingHistory = 0x3e3, // updated 6.40h
  MarketBoardItemListing = 0x122,        // updated 6.40h
  MarketBoardPurchase = 0x24e,           // updated 6.40h
  ItemMarketBoardInfo = 0x2af,           // updated 6.40h

  CharaFreeCompanyTag = 0x013B,   // updated 4.5
  FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
  FreeCompanyInfo = 0x182,        // updated 6.40h
  FreeCompanyDialog = 0x21e,      // updated 6.40h
  ExamineFreeCompanyInfo = 0x3ae, // updated 6.40h

  FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

  StatusEffectList = 0x1cb,       // updated 6.40h
  EurekaStatusEffectList = 0x349, // updated 6.40h
  BossStatusEffectList = 0x2cb,   // updated 6.40h
  StatusEffectList2 = 0x18d,      // updated 6.40h
  StatusEffectList3 = 0x39e,      // updated 6.40h
  Effect = 0x28a,                 // updated 6.40h
  AoeEffect8 = 0x15d,             // updated 6.40h
  AoeEffect16 = 0x1b4,            // updated 6.40h
  AoeEffect24 = 0x34a,            // updated 6.40h
  AoeEffect32 = 0x10c,            // updated 6.40h
  PersistantEffect = 0x39e,       // updated 6.40h

  PlaceFieldMarker = 0x2f8,      // updated 6.40h
  PlaceFieldMarkerPreset = 0xb0, // updated 6.40h

  GCAffiliation = 0x68, // updated 6.40h

  PlayerSpawn = 0x251, // updated 6.40h
  NpcSpawn = 0x11c,    // updated 6.40h
  NpcSpawn2 = 0x384,   // updated 6.40h

  SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

  PartyList = 0x1f9,          // updated 6.40h
  PartyMessage = 0x38f,       // updated 6.40h
  HateRank = 0x1a3,           // updated 6.40h
  HateList = 0x1da,           // updated 6.40h
  ObjectSpawn = 0x12a,        // updated 6.40h
  ObjectDespawn = 0x3b1,      // updated 6.40h
  SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x263,        // updated 6.40h
  PlayerStats = 0x26c,        // updated 6.40h
  ActorOwner = 0x263,         // updated 6.40h
  PlayerStateFlags = 0x2a6,   // updated 6.40h
  PlayerClassInfo = 0x383,    // updated 6.40h
  PlayerUpdateLook = 0x1bb,   // updated 6.40h
  CharaVisualEffect = 0x2f9,  // updated 6.40h

  ModelEquip = 0x3b0,   // updated 6.40h
  Examine = 0x75,       // updated 6.40h
  CharaNameReq = 0x25e, // updated 6.40h

  // nb: see #565 on github
  UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
  RetainerSaleHistory = 0x129,          // updated 6.40h
  RetainerInformation = 0x233,          // updated 6.40h

  SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

  ItemInfo = 0x103,                   // updated 6.40h
  ContainerInfo = 0x21c,              // updated 6.40h
  InventoryTransactionFinish = 0x16f, // updated 6.40h
  InventoryTransaction = 0x2df,       // updated 6.40h
  CurrencyCrystalInfo = 0x350,        // updated 6.40h

  InventoryActionAck = 0x162,  // updated 6.40h
  UpdateInventorySlot = 0x37a, // updated 6.40h

  HuntingLogEntry = 0x3a4, // updated 6.40h

  EventPlay = 0x2d2,    // updated 6.40h
  EventPlay4 = 0xbc,    // updated 6.40h
  EventPlay8 = 0x250,   // updated 6.40h
  EventPlay16 = 0x391,  // updated 6.40h
  EventPlay32 = 0x1ff,  // updated 6.40h
  EventPlay64 = 0x1be,  // updated 6.40h
  EventPlay128 = 0x32f, // updated 6.40h
  EventPlay255 = 0xe4,  // updated 6.40h
  EventStart = 0xaf,    // updated 6.40h
  EventFinish = 0x14c,  // updated 6.40h

  EventContinue = 0x2b5, // updated 6.40h

  EventLinkshell = 0x1169,

  QuestActiveList = 0x15e,   // updated 6.40h
  QuestUpdate = 0x3bb,       // updated 6.40h
  QuestCompleteList = 0x102, // updated 6.40h

  QuestFinish = 0xbd,          // updated 6.40h
  MSQTrackerComplete = 0x2c6,  // updated 6.40h
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x0220, // updated 5.58h

  QuestTracker = 0x2b7, // updated 6.40h

  Mount = 0x245, // updated 6.40h

  DirectorVars = 0x169,       // updated 6.40h
  SomeDirectorUnk1 = 0x0084,  // updated 5.18
  SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
  SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
  SomeDirectorUnk8 = 0x028A,  // updated 5.18
  SomeDirectorUnk16 = 0x028C, // updated 5.18
  DirectorPopUp = 0x03DF,     // updated 5.58h
  DirectorPopUp4 = 0x019B,    // updated 5.58h
  DirectorPopUp8 = 0x0271,    // updated 5.58h

  CFAvailableContents = 0xF1FD, // updated 4.2

  WeatherChange = 0x172,   // updated 6.40h
  PlayerTitleList = 0x214, // updated 6.40h
  Discovery = 0x2dc,       // updated 6.40h

  EorzeaTimeOffset = 0xe6, // updated 6.40h

  EquipDisplayFlags = 0x191, // updated 6.40h

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x0287,     // updated 5.58h
  LootMessage = 0x10d,      // updated 6.40h
  ResultDialog = 0x3dc,     // updated 6.40h
  DesynthResult = 0x90,     // updated 6.40h

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x2da,           // updated 6.40h
  LandUpdate = 0x85,                   // updated 6.40h
  LandAvailability = 0x248,            // updated 6.40h
  YardObjectSpawn = 0x2cc,             // updated 6.40h
  HousingIndoorInitialize = 0x329,     // updated 6.40h
  LandPriceUpdate = 0x2fe,             // updated 6.40h
  LandInfoSign = 0xd0,                 // updated 6.40h
  LandRename = 0x268,                  // updated 6.40h
  HousingEstateGreeting = 0x221,       // updated 6.40h
  HousingUpdateLandFlagsSlot = 0x3ce,  // updated 6.40h
  HousingLandFlags = 0x255,            // updated 6.40h
  HousingShowEstateGuestAccess = 0x7c, // updated 6.40h

  HousingObjectInitialize = 0x17c,    // updated 6.40h
  HousingInternalObjectSpawn = 0x2e0, // updated 6.40h

  HousingWardInfo = 0x190,   // updated 6.40h
  HousingObjectMove = 0x32d, // updated 6.40h
  HousingObjectDye = 0x21a,  // updated 6.40h

  SharedEstateSettingsResponse = 0x207, // updated 6.40h

  LandUpdateHouseName = 0x6a, // updated 6.40h
  LandSetMap = 0x24d,         // updated 6.40h

  CeremonySetActorAppearance = 0x259, // updated 6.40h

  //////////////////////////////////////////////////

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x29e,    // updated 6.40h

  DutyGauge = 0x02E5, // updated 5.58h

  // daily quest info -> without them sent,  login will take longer...
  DailyQuests = 0xa8,            // updated 6.40h
  DailyQuestRepeatFlags = 0x272, // updated 6.40h

  MapUpdate = 0x348,   // updated 6.40h
  MapUpdate4 = 0x19b,  // updated 6.40h
  MapUpdate8 = 0x30a,  // updated 6.40h
  MapUpdate16 = 0x2ae, // updated 6.40h
  MapUpdate32 = 0x1c0, // updated 6.40h
  MapUpdate64 = 0x35c, // updated 6.40h
  MapUpdate128 = 0xed, // updated 6.40h

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
  AirshipTimers = 0x3af,           // updated 6.40h
  AirshipStatus = 0x3e0,           // updated 6.40h
  AirshipStatusList = 0xd6,        // updated 6.40h
  AirshipExplorationResult = 0xb5, // updated 6.40h

  SubmarineTimers = 0x2ef,            // updated 6.40h
  SubmarineProgressionStatus = 0x181, // updated 6.40h
  SubmarineStatusList = 0x13d,        // updated 6.40h
  SubmarineExplorationResult = 0x15f, // updated 6.40h

  EnvironmentControl = 0xf9,          // updated 6.40h
  RSVData = 0x1ae,                    // updated 6.40h
  IslandWorkshopSupplyDemand = 0x16d, // updated 6.40h
};

/**
 * Client IPC Zone Type Codes.
 */
enum ClientZoneIpcType :
  uint16_t
{
  PingHandler = 0x72,  // updated 6.40h
  InitHandler = 0x1cc, // updated 6.40h

  FinishLoadingHandler = 0x281, // updated 6.40h

  CFCommenceHandler = 0x0381, // updated 5.58h

  CFCancelHandler = 0x02B2,    // updated 5.58h
  CFRegisterDuty = 0x01BD,     // updated 5.58h
  CFRegisterRoulette = 0x037A, // updated 5.58h
  PlayTimeHandler = 0x02B7,    // updated 5.58h
  LogoutHandler = 0x1ba,       // updated 6.40h
  CancelLogout = 0x01e3,       // updated 6.31h
  CFDutyInfoHandler = 0xF078,  // updated 4.2

  SocialReqSendHandler = 0x00D7,  // updated 5.58h
  SocialResponseHandler = 0x023B, // updated 5.58h
  CreateCrossWorldLS = 0x9999,    // updated 5.58h

  ChatHandler = 0x31b, // updated 6.40h
  PartyChatHandler = 0x0065, PartySetLeaderHandler = 0x036C,  // updated 5.58h
  LeavePartyHandler = 0x019D,      // updated 5.58h
  KickPartyMemberHandler = 0x0262, // updated 5.58h
  DisbandPartyHandler = 0x0276,    // updated 5.58h

  SocialListHandler = 0x206,               // updated 6.40
  SetSearchInfoHandler = 0x10b,            // updated 6.40h
  ReqSearchInfoHandler = 0x03b0,           // updated 6.31h
  ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

  ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
  BlackListHandler = 0x24c,              // updated 6.40h
  PlayerSearchHandler = 0x037D,          // updated 5.58h

  LinkshellListHandler = 0x03B6, // updated 5.58h

  MarketBoardRequestItemListingInfo = 0x00F4, // updated 5.58h
  MarketBoardRequestItemListings = 0x0122,    // updated 5.58h
  MarketBoardSearch = 0x0082,                 // updated 5.58h
  MarketBoardPurchaseHandler = 0x8d,          // updated 6.40h

  ReqExamineFcInfo = 0xF37B, // updated 5.58h (prepended F. Conflicts with FinishLoadingHandler 6.38)

  FcInfoReqHandler = 0x9999, // unknown

  FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

  ReqMarketWishList = 0x00C3, // updated 5.58h

  ReqJoinNoviceNetwork = 0x0129, // updated 4.2

  ReqCountdownInitiate = 0x03e1, // updated 6.31h
  ReqCountdownCancel = 0x023a,   // updated 6.31h

  ZoneLineHandler = 0x20c,   // updated 6.40h
  ClientTrigger = 0xda,      // updated 6.40h
  DiscoveryHandler = 0x038B, // updated 5.58h

  SkillHandler = 0x73,     // updated 6.40h
  GMCommand1 = 0xab,       // updated 6.40h
  GMCommand2 = 0x1a9,      // updated 6.40h
  AoESkillHandler = 0x3a5, // updated 6.40h

  UpdatePositionHandler = 0x215, // updated 6.40h

  InventoryModifyHandler = 0x283, // updated 6.40h

  InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

  ReqPlaceHousingItem = 0x02D4, // updated 5.58h
  BuildPresetHandler = 0x0223,  // updated 5.58h

  TalkEventHandler = 0x1a4,         // updated 6.40h
  EmoteEventHandler = 0x00B0,       // updated 5.58h
  WithinRangeEventHandler = 0x1fe,  // updated 6.40h
  OutOfRangeEventHandler = 0x6f,    // updated 6.40h
  EnterTeriEventHandler = 0x6d,     // updated 6.40h
  ShopEventHandler = 0x0384,        // updated 5.58h
  ReturnEventHandler = 0x3bd,       // updated 6.40h
  TradeReturnEventHandler = 0x8e,   // updated 6.40h
  TradeReturnEventHandler2 = 0x28a, // updated 6.40h
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

  UpdatePositionInstance = 0x147, // updated 6.40h

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
