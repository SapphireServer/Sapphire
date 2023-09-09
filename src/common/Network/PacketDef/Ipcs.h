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
  Ping = 0x378, // updated 6.48
  Init = 0x2ac, // updated 6.48

  ActorFreeSpawn = 0x112, // updated 6.48

  InitZone = 0x71,       // updated 6.48
  PrepareZoning = 0x188, // updated 6.48

  EffectResult = 0x2a3,      // updated 6.48
  EffectResultBasic = 0xfa,  // updated 6.48

  ActorControl = 0xd4,       // updated 6.48
  ActorControlTarget = 0xef, // updated 6.48
  ActorControlSelf = 0x3c1,  // updated 6.48
  ActorCast = 0xc8,          // updated 6.48
  ActorSetPos = 0x32c,       // updated 6.48
  ActorMove = 0x1aa,         // updated 6.48
  ActorGauge = 0x2a4,        // updated 6.48

  /*!
   * @brief Used when resting
   */
  UpdateHpMpTp = 0x1fb,    // updated 6.48
  UpdateClassInfo = 0x3e3, // updated 6.48

  ///////////////////////////////////////////////////

  ChatBanned = 0xF06B,
  Playtime = 0x313, // updated 6.48
  Logout = 0x116,   // updated 6.48
  CFNotify = 0x69,  // updated 6.48
  CFMemberStatus = 0x0079,
  CFDutyInfo = 0x1be, // updated 6.48
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0x160, // updated 6.48
  CFCancel = 0x1bb,        // updated 6.48
  SocialRequestError = 0xF0AD,

  CFRegistered = 0x029F,          // updated 5.58h
  SocialRequestResponse = 0x373,  // updated 6.48
  SocialMessage = 0x03CB,         // updated 5.58h
  SocialMessage2 = 0x01D7,        // updated 5.58h
  CancelAllianceForming = 0xF0C6, // updated 4.2

  LogMessage = 0x316, // updated 6.48

  Chat = 0x2d7, // updated 6.48
  PartyChat = 0x0065,

  WorldVisitList = 0xF0FE, // added 4.5

  SocialList = 0xb1, // updated 6.48

  ExamineSearchInfo = 0x357,    // updated 6.48
  UpdateSearchInfo = 0x115,     // updated 6.48
  InitSearchInfo = 0x70,        // updated 6.48
  ExamineSearchComment = 0x199, // updated 6.48

  ServerNoticeShort = 0x0333, // updated 5.58h
  ServerNotice = 0x2b1,       // updated 6.48
  SystemLogMessage = 0x3c8,   // updated 6.48
  SetOnlineStatus = 0x17a,    // updated 6.48

  CountdownInitiate = 0x399, // updated 6.48
  CountdownCancel = 0x342,   // updated 6.48

  PlayerAddedToBlacklist = 0xe2,     // updated 6.48
  PlayerRemovedFromBlacklist = 0xd0, // updated 6.48
  BlackList = 0x233,                 // updated 6.48

  LinkshellList = 0x1f8,           // updated 6.48
  CrossWorldLinkshellList = 0x3cc, // updated 6.48
  FellowshipList = 0x1c5,          // updated 6.48

  MailDeleteRequest = 0x1b6, // updated 6.48

  // 12D - 137 - constant gap between 4.5x -> 5.0
  ReqMoogleMailList = 0xF138,      // updated 5.0
  ReqMoogleMailLetter = 0xF139,    // updated 5.0
  MailLetterNotification = 0x013A, // updated 5.0

  MarketTaxRates = 0x01F8, // updated 5.35h

  MarketBoardSearchResult = 0x3d6,       // updated 6.48
  MarketBoardItemListingCount = 0x306,   // updated 6.48
  MarketBoardItemListingHistory = 0x2f4, // updated 6.48
  MarketBoardItemListing = 0x1db,        // updated 6.48
  MarketBoardPurchase = 0x1f0,           // updated 6.48
  ItemMarketBoardInfo = 0x11b,           // updated 6.48

  CharaFreeCompanyTag = 0x013B,   // updated 4.5
  FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
  FreeCompanyInfo = 0x30f,        // updated 6.48
  FreeCompanyDialog = 0x1b4,      // updated 6.48
  ExamineFreeCompanyInfo = 0x158, // updated 6.48

  FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

  StatusEffectList = 0x1dd,       // updated 6.48
  EurekaStatusEffectList = 0x192, // updated 6.48
  BossStatusEffectList = 0x2cb,   // updated 6.48
  StatusEffectList2 = 0x166,      // updated 6.48
  StatusEffectList3 = 0x31f,      // updated 6.48
  Effect = 0x354,                 // updated 6.48
  AoeEffect8 = 0x18f,             // updated 6.48
  AoeEffect16 = 0x38f,            // updated 6.48
  AoeEffect24 = 0xd1,             // updated 6.48
  AoeEffect32 = 0x340,            // updated 6.48
  PersistantEffect = 0x31f,       // updated 6.48

  PlaceFieldMarker = 0x194,       // updated 6.48
  PlaceFieldMarkerPreset = 0x221, // updated 6.48

  GCAffiliation = 0x280, // updated 6.48

  PlayerSpawn = 0x10e, // updated 6.48
  NpcSpawn = 0x91,     // updated 6.48
  NpcSpawn2 = 0x2b6,   // updated 6.48

  SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

  PartyList = 0x16f,          // updated 6.48
  PartyMessage = 0x336,       // updated 6.48
  HateRank = 0x33f,           // updated 6.48
  HateList = 0x356,           // updated 6.48
  ObjectSpawn = 0x190,        // updated 6.48
  ObjectDespawn = 0xd2,       // updated 6.48
  SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x20e,        // updated 6.48
  PlayerStats = 0x2f3,        // updated 6.48
  ActorOwner = 0x20e,         // updated 6.48
  PlayerStateFlags = 0x2ed,   // updated 6.48
  PlayerClassInfo = 0xfb,     // updated 6.48
  PlayerUpdateLook = 0xa8,    // updated 6.48
  CharaVisualEffect = 0x2fc,  // updated 6.48

  ModelEquip = 0x82,    // updated 6.48
  Examine = 0x200,      // updated 6.48
  CharaNameReq = 0x267, // updated 6.48

  // nb: see #565 on github
  UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
  RetainerSaleHistory = 0x23d,          // updated 6.48
  RetainerInformation = 0x2fe,          // updated 6.48

  SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

  ItemInfo = 0x3a4,                   // updated 6.48
  ContainerInfo = 0x208,              // updated 6.48
  InventoryTransactionFinish = 0x298, // updated 6.48
  InventoryTransaction = 0x3db,       // updated 6.48
  CurrencyCrystalInfo = 0x389,        // updated 6.48

  InventoryActionAck = 0x134,  // updated 6.48
  UpdateInventorySlot = 0xa4,  // updated 6.48

  HuntingLogEntry = 0xb9, // updated 6.48

  EventPlay = 0x2db,    // updated 6.48
  EventPlay4 = 0xe8,    // updated 6.48
  EventPlay8 = 0xfe,    // updated 6.48
  EventPlay16 = 0x8f,   // updated 6.48
  EventPlay32 = 0x374,  // updated 6.48
  EventPlay64 = 0x27f,  // updated 6.48
  EventPlay128 = 0x365, // updated 6.48
  EventPlay255 = 0xdb,  // updated 6.48
  EventStart = 0x2be,   // updated 6.48
  EventFinish = 0x289,  // updated 6.48

  EventContinue = 0xd9, // updated 6.48

  EventLinkshell = 0x1169,

  QuestActiveList = 0x108,   // updated 6.48
  QuestUpdate = 0x2f0,       // updated 6.48
  QuestCompleteList = 0x17f, // updated 6.48

  QuestFinish = 0xf4,          // updated 6.48
  MSQTrackerComplete = 0x20a,  // updated 6.48
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x0220, // updated 5.58h

  QuestTracker = 0x2ec, // updated 6.48

  Mount = 0x242, // updated 6.48

  DirectorVars = 0x114,       // updated 6.48
  SomeDirectorUnk1 = 0x0084,  // updated 5.18
  SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
  SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
  SomeDirectorUnk8 = 0x028A,  // updated 5.18
  SomeDirectorUnk16 = 0x028C, // updated 5.18
  DirectorPopUp = 0x03DF,     // updated 5.58h
  DirectorPopUp4 = 0x019B,    // updated 5.58h
  DirectorPopUp8 = 0x0271,    // updated 5.58h

  CFAvailableContents = 0xF1FD, // updated 4.2

  WeatherChange = 0x21c,   // updated 6.48
  PlayerTitleList = 0x17c, // updated 6.48
  Discovery = 0x14f,       // updated 6.48

  EorzeaTimeOffset = 0x1a2, // updated 6.48

  EquipDisplayFlags = 0x24e, // updated 6.48

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x0287,     // updated 5.58h
  LootMessage = 0x219,      // updated 6.48
  ResultDialog = 0x21f,     // updated 6.48
  DesynthResult = 0x296,    // updated 6.48

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x228,            // updated 6.48
  LandUpdate = 0x26c,                   // updated 6.48
  LandAvailability = 0x258,             // updated 6.48
  YardObjectSpawn = 0x2c0,              // updated 6.48
  HousingIndoorInitialize = 0x24f,      // updated 6.48
  LandPriceUpdate = 0x94,               // updated 6.48
  LandInfoSign = 0x330,                 // updated 6.48
  LandRename = 0x255,                   // updated 6.48
  HousingEstateGreeting = 0x253,        // updated 6.48
  HousingUpdateLandFlagsSlot = 0x3a1,   // updated 6.48
  HousingLandFlags = 0x197,             // updated 6.48
  HousingShowEstateGuestAccess = 0x2f2, // updated 6.48

  HousingObjectInitialize = 0x39e,    // updated 6.48
  HousingInternalObjectSpawn = 0x31c, // updated 6.48

  HousingWardInfo = 0x395,   // updated 6.48
  HousingObjectMove = 0x21b, // updated 6.48
  HousingObjectDye = 0x2a6,  // updated 6.48

  SharedEstateSettingsResponse = 0x2d1, // updated 6.48

  LandUpdateHouseName = 0x98, // updated 6.48
  LandSetMap = 0x366,         // updated 6.48

  CeremonySetActorAppearance = 0x3be, // updated 6.48

  //////////////////////////////////////////////////

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x12a,    // updated 6.48

  DutyGauge = 0x02E5, // updated 5.58h

  // daily quest info -> without them sent,  login will take longer...
  DailyQuests = 0x90,           // updated 6.48
  DailyQuestRepeatFlags = 0x382, // updated 6.48

  MapUpdate = 0xa3,    // updated 6.48
  MapUpdate4 = 0x345,  // updated 6.48
  MapUpdate8 = 0x10c,  // updated 6.48
  MapUpdate16 = 0x360, // updated 6.48
  MapUpdate32 = 0x1b1, // updated 6.48
  MapUpdate64 = 0x325, // updated 6.48
  MapUpdate128 = 0x9c, // updated 6.48

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
  AirshipTimers = 0x34f,            // updated 6.48
  AirshipStatus = 0x16b,            // updated 6.48
  AirshipStatusList = 0x2e4,        // updated 6.48
  AirshipExplorationResult = 0x359, // updated 6.48

  SubmarineTimers = 0x3af,            // updated 6.48
  SubmarineProgressionStatus = 0x152, // updated 6.48
  SubmarineStatusList = 0xc4,         // updated 6.48
  SubmarineExplorationResult = 0x376, // updated 6.48

  EnvironmentControl = 0x137,        // updated 6.48
  RSVData = 0x212,                   // updated 6.48
  IslandWorkshopSupplyDemand = 0xf9, // updated 6.48
};

/**
 * Client IPC Zone Type Codes.
 */
enum ClientZoneIpcType :
  uint16_t
{
  PingHandler = 0x238,  // updated 6.48
  InitHandler = 0x3b6, // updated 6.48

  FinishLoadingHandler = 0x2ac, // updated 6.48

  CFCommenceHandler = 0x0381, // updated 5.58h

  CFCancelHandler = 0x02B2,    // updated 5.58h
  CFRegisterDuty = 0x01BD,     // updated 5.58h
  CFRegisterRoulette = 0x037A, // updated 5.58h
  PlayTimeHandler = 0x02B7,    // updated 5.58h
  LogoutHandler = 0x1ad,       // updated 6.48
  CancelLogout = 0x01e3,       // updated 6.31h
  CFDutyInfoHandler = 0xF078,  // updated 4.2

  SocialReqSendHandler = 0x00D7,  // updated 5.58h
  SocialResponseHandler = 0x023B, // updated 5.58h
  CreateCrossWorldLS = 0x9999,    // updated 5.58h

  ChatHandler = 0x1df, // updated 6.48
  PartyChatHandler = 0x0065, PartySetLeaderHandler = 0x036C,  // updated 5.58h
  LeavePartyHandler = 0x019D,      // updated 5.58h
  KickPartyMemberHandler = 0x0262, // updated 5.58h
  DisbandPartyHandler = 0x0276,    // updated 5.58h

  SocialListHandler = 0x206,               // updated 6.40
  SetSearchInfoHandler = 0x230,            // updated 6.48
  ReqSearchInfoHandler = 0x03b0,           // updated 6.31h
  ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

  ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
  BlackListHandler = 0x153,              // updated 6.48
  PlayerSearchHandler = 0x037D,          // updated 5.58h

  LinkshellListHandler = 0x03B6, // updated 5.58h

  MarketBoardRequestItemListingInfo = 0x00F4,  // updated 5.58h
  MarketBoardRequestItemListings = 0x0122,     // updated 5.58h
  MarketBoardSearch = 0x0082,                  // updated 5.58h
  MarketBoardPurchaseHandler = 0x15b,          // updated 6.48

  ReqExamineFcInfo = 0xF37B, // updated 5.58h (prepended F. Conflicts with FinishLoadingHandler 6.38)

  FcInfoReqHandler = 0x9999, // unknown

  FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

  ReqMarketWishList = 0x00C3, // updated 5.58h

  ReqJoinNoviceNetwork = 0x0129, // updated 4.2

  ReqCountdownInitiate = 0x03e1, // updated 6.31h
  ReqCountdownCancel = 0x023a,   // updated 6.31h

  ZoneLineHandler = 0x34e,   // updated 6.48
  ClientTrigger = 0x186,     // updated 6.48
  DiscoveryHandler = 0x038B, // updated 5.58h

  SkillHandler = 0xa7,    // updated 6.48
  GMCommand1 = 0x2f9,     // updated 6.48
  GMCommand2 = 0x299,     // updated 6.48
  AoESkillHandler = 0x65, // updated 6.48

  UpdatePositionHandler = 0x3b5, // updated 6.48

  InventoryModifyHandler = 0x2da, // updated 6.48

  InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

  ReqPlaceHousingItem = 0x02D4, // updated 5.58h
  BuildPresetHandler = 0x0223,  // updated 5.58h

  TalkEventHandler = 0x1a8,         // updated 6.48
  EmoteEventHandler = 0x00B0,       // updated 5.58h
  WithinRangeEventHandler = 0x1b9,  // updated 6.48
  OutOfRangeEventHandler = 0x263,   // updated 6.48
  EnterTeriEventHandler = 0x370,    // updated 6.48
  ShopEventHandler = 0x0384,        // updated 5.58h
  ReturnEventHandler = 0xef,        // updated 6.48
  TradeReturnEventHandler = 0x1fb,  // updated 6.48
  TradeReturnEventHandler2 = 0x354, // updated 6.48
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

  UpdatePositionInstance = 0xa5, // updated 6.48

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
