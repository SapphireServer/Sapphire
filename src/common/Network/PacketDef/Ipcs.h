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
  Ping = 0x1D9, // updated 6.58 hotfix 2
  Init = 0x12A, // updated 6.58 hotfix 2

  ActorFreeSpawn = 0x195, // updated 6.58 hotfix 2

  InitZone = 0x02D1, // updated 6.58 hotfix 2
  PrepareZoning = 0x0124, // updated 6.58 hotfix 2

  EffectResult = 0x0336, // updated 6.58 hotfix 2
  EffectResultBasic = 0x023A, // updated 6.58 hotfix 2

  ActorControl = 0x0148, // updated 6.58 hotfix 2
  ActorControlTarget = 0x032C, // updated 6.58 hotfix 2
  ActorControlSelf = 0x025D, // updated 6.58 hotfix 2
  ActorCast = 0x01BB, // updated 6.58 hotfix 2
  ActorSetPos = 0x029D, // updated 6.58 hotfix 2
  ActorMove = 0x011C, // updated 6.58 hotfix 2
  ActorGauge = 0x03B3, // updated 6.58 hotfix 2

  /*!
   * @brief Used when resting
   */
  UpdateHpMpTp = 0x007D, // updated 6.58 hotfix 2
  UpdateClassInfo = 0x0172, // updated 6.58 hotfix 2

  ///////////////////////////////////////////////////

  ChatBanned = 0xF06B,
  Playtime = 0x03DE, // updated 6.58 hotfix 2
  Logout = 0x0378, // updated 6.58 hotfix 2
  CFNotify = 0x0279, // updated 6.58 hotfix 2
  CFMemberStatus = 0x0079,
  CFDutyInfo = 0x1be, // updated 6.48
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0x282,  // updated 6.58 hotfix 2
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

  SocialList = 0x1F2, // updated 6.58 hotfix 2

  ExamineSearchInfo = 0x014A, // updated 6.58 hotfix 2
  UpdateSearchInfo = 0x00CF, // updated 6.58 hotfix 2
  InitSearchInfo = 0x329,       // updated 6.58 hotfix 2
  ExamineSearchComment = 0x199, // updated 6.48

  ServerNoticeShort = 0x0333, // updated 5.58h
  ServerNotice = 0x33B,       // updated 6.58 hotfix 2
  SystemLogMessage = 0x03A9, // updated 6.58 hotfix 2
  SetOnlineStatus = 0x285,    // updated 6.58 hotfix 2

  CountdownInitiate = 0x376, // updated 6.58 hotfix 2
  CountdownCancel = 0x2B7,    // updated 6.58 hotfix 2

  PlayerAddedToBlacklist = 0xe2,     // updated 6.48
  PlayerRemovedFromBlacklist = 0xd0, // updated 6.48
  BlackList = 0x38A,                   // updated 6.58 hotfix 2

  LinkshellList = 0x2B2,           // updated 6.58 hotfix 2
  CrossWorldLinkshellList = 0x3cc, // updated 6.48
  FellowshipList = 0x1c5,          // updated 6.48

  MailDeleteRequest = 0x1b6, // updated 6.48

  // 12D - 137 - constant gap between 4.5x -> 5.0
  ReqMoogleMailList = 0xF138,      // updated 5.0
  ReqMoogleMailLetter = 0xF139,    // updated 5.0
  MailLetterNotification = 0x013A, // updated 5.0

  MarketTaxRates = 0x01F8, // updated 5.35h

  MarketBoardSearchResult = 0x0161, // updated 6.58 hotfix 2
  MarketBoardItemListingCount = 0x0286, // updated 6.58 hotfix 2
  MarketBoardItemListingHistory = 0x0229, // updated 6.58 hotfix 2
  MarketBoardItemListing = 0x03E3, // updated 6.58 hotfix 2
  MarketBoardPurchase = 0x0143, // updated 6.58 hotfix 2
  ItemMarketBoardInfo = 0x01BC, // updated 6.58 hotfix 2

  CharaFreeCompanyTag = 0x013B,   // updated 4.5
  FreeCompanyBoardMsg = 0x03DB,   // updated 5.58h
  FreeCompanyInfo = 0x02D5, // updated 6.58 hotfix 2
  FreeCompanyDialog = 0x029F, // updated 6.58 hotfix 2
  ExamineFreeCompanyInfo = 0x158, // updated 6.48

  FreeCompanyUpdateShortMessage = 0xF157, // added 5.0

  StatusEffectList = 0x0383, // updated 6.58 hotfix 2
  EurekaStatusEffectList = 0x3A8, // updated 6.58 hotfix 2
  BossStatusEffectList = 0x28C,   // updated 6.58 hotfix 2
  StatusEffectList2 = 0x0369, // updated 6.58 hotfix 2
  StatusEffectList3 = 0x0163, // updated 6.58 hotfix 2
  Effect = 0x037D, // updated 6.58 hotfix 2
  AoeEffect8 = 0x0F4, // updated 6.58 hotfix 2
  AoeEffect16 = 0x121, // updated 6.58 hotfix 2
  AoeEffect24 = 0x2E3, // updated 6.58 hotfix 2
  AoeEffect32 = 0x1FB, // updated 6.58 hotfix 2
  PersistantEffect = 0x163, // updated 6.58 hotfix 2

  PlaceFieldMarker = 0x02E4, // updated 6.58 hotfix 2
  PlaceFieldMarkerPreset = 0x030A, // updated 6.58 hotfix 2

  GCAffiliation = 0x35D, // updated 6.58 hotfix 2

  PlayerSpawn = 0x039C, // updated 6.58 hotfix 2
  NpcSpawn = 0x00A7, // updated 6.58 hotfix 2
  NpcSpawn2 = 0x338,   // updated 6.58 hotfix 2?

  SomeCustomiseChangePacketProbably = 0x00CD, // added 5.18

  PartyList = 0x16f,          // updated 6.48
  PartyMessage = 0x336,       // updated 6.48
  HateRank = 0x2A7,            // updated 6.58 hotfix 2
  HateList = 0x26B,            // updated 6.58 hotfix 2
  ObjectSpawn = 0x03B8, // updated 6.58 hotfix 2
  ObjectDespawn = 0x1D8,      // updated 6.58 hotfix 2
  SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x035F, // updated 6.58 hotfix 2
  PlayerStats = 0x034F, // updated 6.58 hotfix 2
  ActorOwner = 0x2c3,         // updated 6.58 hotfix 2?
  PlayerStateFlags = 0x1B6,   // updated 6.58 hotfix 2
  PlayerClassInfo = 0x238,    // updated 6.58 hotfix 2
  PlayerUpdateLook = 0xa8,    // updated 6.48
  CharaVisualEffect = 0x0C1,  // updated 6.58 hotfix 2

  ModelEquip = 0x27D,    // updated 6.58 hotfix 2
  Examine = 0x02C0, // updated 6.58 hotfix 2
  CharaNameReq = 0x267, // updated 6.48

  // nb: see #565 on github
  UpdateRetainerItemSalePrice = 0xF19F, // updated 5.0
  RetainerSaleHistory = 0x23d,          // updated 6.48
  RetainerInformation = 0x00ED, // updated 6.58 hotfix 2

  SetLevelSync = 0x1186, // not updated for 4.4, not sure what it is anymore

  ItemInfo = 0x02F0, // updated 6.58 hotfix 2
  ContainerInfo = 0x0069, // updated 6.58 hotfix 2
  InventoryTransactionFinish = 0x009C, // updated 6.58 hotfix 2
  InventoryTransaction = 0x02BD, // updated 6.58 hotfix 2
  CurrencyCrystalInfo = 0x02DE, // updated 6.58 hotfix 2

  InventoryActionAck = 0x00DD, // updated 6.58 hotfix 2
  UpdateInventorySlot = 0x034D, // updated 6.58 hotfix 2

  HuntingLogEntry = 0x388, // updated 6.58 hotfix 2

  EventPlay = 0x0155, // updated 6.58 hotfix 2
  EventPlay4 = 0x00D0, // updated 6.58 hotfix 2
  EventPlay8 = 0x022B, // updated 6.58 hotfix 2
  EventPlay16 = 0x00D2, // updated 6.58 hotfix 2
  EventPlay32 = 0x02CF, // updated 6.58 hotfix 2
  EventPlay64 = 0x01D4, // updated 6.58 hotfix 2
  EventPlay128 = 0x039F, // updated 6.58 hotfix 2
  EventPlay255 = 0x0073, // updated 6.58 hotfix 2
  EventStart = 0x0146, // updated 6.58 hotfix 2
  EventFinish = 0x0339, // updated 6.58 hotfix 2

  EventReturn = 0xd9, // updated 6.48

  EventLinkshell = 0x1169,

  QuestActiveList = 0x247,   // updated 6.58 hotfix 2
  QuestUpdate = 0x2f0,       // updated 6.48
  QuestCompleteList = 0x352, // updated 6.58 hotfix 2

  QuestFinish = 0xf4,          // updated 6.48
  MSQTrackerComplete = 0x1A9,  // updated 6.58 hotfix 2
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x0220, // updated 5.58h

  QuestTracker = 0x27C, // updated 6.58 hotfix 2

  Mount = 0x09F, // updated 6.58 hotfix 2

  DirectorVars = 0x3A6,       // updated 6.58 hotfix 2
  SomeDirectorUnk1 = 0x0084,  // updated 5.18
  SomeDirectorUnk2 = 0xF0C1,  // updated 5.18
  SomeDirectorUnk4 = 0x03DD,  // updated 5.58h
  SomeDirectorUnk8 = 0x028A,  // updated 5.18
  SomeDirectorUnk16 = 0x028C, // updated 5.18
  DirectorPopUp = 0x03DF,     // updated 5.58h
  DirectorPopUp4 = 0x019B,    // updated 5.58h
  DirectorPopUp8 = 0x0271,    // updated 5.58h

  CFAvailableContents = 0xF1FD, // updated 4.2

  WeatherChange = 0x021D, // updated 6.58 hotfix 2
  PlayerTitleList = 0x17c, // updated 6.48
  Discovery = 0x14f,       // updated 6.48

  EorzeaTimeOffset = 0x1a2, // updated 6.48

  EquipDisplayFlags = 0x33A, // updated 6.58 hotfix 2

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x016F,     // updated 6.58 hotfix 2
  LootMessage = 0x219,      // updated 6.48
  ResultDialog = 0x0362, // updated 6.58 hotfix 2
  DesynthResult = 0x007F, // updated 6.58 hotfix 2

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x1C9,            // updated 6.58 hotfix 2
  LandUpdate = 0x26c,                   // updated 6.48
  LandAvailability = 0x258,             // updated 6.48
  YardObjectSpawn = 0x2c0,              // updated 6.48
  HousingIndoorInitialize = 0x24f,      // updated 6.48
  LandPriceUpdate = 0x94,               // updated 6.48
  LandInfoSign = 0x330,                 // updated 6.48
  LandRename = 0x255,                   // updated 6.48
  HousingEstateGreeting = 0x253,        // updated 6.48
  HousingUpdateLandFlagsSlot = 0x3a1,   // updated 6.48
  HousingLandFlags = 0x330,             // updated 6.58 hotfix 2
  HousingShowEstateGuestAccess = 0x2f2, // updated 6.48

  HousingObjectInitialize = 0x1AA,    // updated 6.58 hotfix 2
  HousingInternalObjectSpawn = 0x31c, // updated 6.48

  HousingWardInfo = 0x327,  // updated 6.58 hotfix 2?
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
  DailyQuests = 0x2EF,           // updated 6.58 hotfix 2
  DailyQuestRepeatFlags = 0x134, // updated 6.58 hotfix 2

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
  AirshipTimers = 0x0123, // updated 6.58 hotfix 2
  AirshipStatus = 0x0291, // updated 6.58 hotfix 2
  AirshipStatusList = 0x023B, // updated 6.58 hotfix 2
  AirshipExplorationResult = 0x01BD, // updated 6.58 hotfix 2

  SubmarineTimers = 0x0185, // updated 6.58 hotfix 2
  SubmarineProgressionStatus = 0x02DD, // updated 6.58 hotfix 2
  SubmarineStatusList = 0x03E2, // updated 6.58 hotfix 2
  SubmarineExplorationResult = 0x02AA, // updated 6.58 hotfix 2

  EnvironmentControl = 0x02FC, // updated 6.58 hotfix 2
  RSVData = 0x212,                   // updated 6.48
  IslandWorkshopSupplyDemand = 0x013C, // updated 6.58 hotfix 2
};

/**
 * Client IPC Zone Type Codes.
 */
enum ClientZoneIpcType :
  uint16_t
{
  PingHandler = 0x2AE, // updated 6.58 hotfix 2
  InitHandler = 0x1CE, // updated 6.58 hotfix 2

  FinishLoadingHandler = 0x12A, // updated 6.58 hotfix 2

  CFCommenceHandler = 0x0381, // updated 5.58h

  CFCancelHandler = 0x02B2,    // updated 5.58h
  CFRegisterDuty = 0x01BD,     // updated 5.58h
  CFRegisterRoulette = 0x037A, // updated 5.58h
  PlayTimeHandler = 0x02B7,    // updated 5.58h
  LogoutHandler = 0x384,       // updated 6.58 hotfix 2
  CancelLogout = 0x01e3,       // updated 6.31h
  CFDutyInfoHandler = 0xF078,  // updated 4.2

  SocialReqSendHandler = 0x00D7,  // updated 5.58h
  SocialResponseHandler = 0x023B, // updated 5.58h
  CreateCrossWorldLS = 0x9999,    // updated 5.58h

  ChatHandler = 0x246, // updated 6.58 hotfix 2
  PartyChatHandler = 0x0065, PartySetLeaderHandler = 0x036C,  // updated 5.58h
  LeavePartyHandler = 0x019D,      // updated 5.58h
  KickPartyMemberHandler = 0x0262, // updated 5.58h
  DisbandPartyHandler = 0x0276,    // updated 5.58h

  SocialListHandler = 0x10B,               // updated 6.58 hotfix 2
  SetSearchInfoHandler = 0x01A0, // updated 6.58 hotfix 2
  ReqSearchInfoHandler = 0x0235,           // updated 6.58 hotfix 2
  ReqExamineSearchCommentHandler = 0x00E7, // updated 5.0

  ReqRemovePlayerFromBlacklist = 0x00B4, // updated 5.58h
  BlackListHandler = 0x284,              // updated 6.58 hotfix 2
  PlayerSearchHandler = 0x037D,          // updated 5.58h

  LinkshellListHandler = 0x0302, // updated 6.58 hotfix 2

  MarketBoardRequestItemListingInfo = 0x00F4,  // updated 5.58h
  MarketBoardRequestItemListings = 0x0122,     // updated 5.58h
  MarketBoardSearch = 0x0082,                  // updated 5.58h
  MarketBoardPurchaseHandler = 0x0322, // updated 6.58 hotfix 2

  ReqExamineFcInfo = 0xF37B, // updated 5.58h (prepended F. Conflicts with FinishLoadingHandler 6.38)

  FcInfoReqHandler = 0x33B, // updated 6.58 hotfix 2

  FreeCompanyUpdateShortMessageHandler = 0x0123, // added 5.0

  ReqMarketWishList = 0x00C3, // updated 5.58h

  ReqJoinNoviceNetwork = 0x0129, // updated 4.2

  ReqCountdownInitiate = 0x03E3, // updated 6.58 hotfix 2
  ReqCountdownCancel = 0x023a,   // updated 6.31h

  ZoneLineHandler = 0x326,   // updated 6.58 hotfix 2
  ClientTrigger = 0x035C, // updated 6.58 hotfix 2
  DiscoveryHandler = 0x038B, // updated 5.58h

  SkillHandler = 0x07C,   // updated 6.58 hotfix 2
  GMCommand1 = 0x152,      // updated 6.58 hotfix 2
  GMCommand2 = 0x299,     // updated 6.48
  AoESkillHandler = 0x0FC, // updated 6.58 hotfix 2

  UpdatePositionHandler = 0x0256, // updated 6.58 hotfix 2

  InventoryModifyHandler = 0x023E, // updated 6.58 hotfix 2

  InventoryEquipRecommendedItems = 0x01C9, // updated 5.58h

  ReqPlaceHousingItem = 0x02D4, // updated 5.58h
  BuildPresetHandler = 0x0223,  // updated 5.58h

  TalkEventHandler = 0x23A,         // updated 6.58 hotfix 2
  EmoteEventHandler = 0x00B0,       // updated 5.58h
  WithinRangeEventHandler = 0x1b9,  // updated 6.48
  OutOfRangeEventHandler = 0x263,   // updated 6.48
  EnterTeriEventHandler = 0x105,    // updated 6.58 hotfix 2
  ShopEventHandler = 0x0384,        // updated 5.58h
  ReturnEventHandler = 0x07D,        // updated 6.58 hotfix 2
  TradeReturnEventHandler = 0x37D,  // updated 6.58 hotfix 2
  TradeReturnEventHandler2 = 0x354, // updated 6.48
  EventYield2Handler = 0x021D,      // updated 5.58h
  EventYield16Handler = 0x0207,     // updated 5.58h

  LinkshellEventHandler = 0x9999,  // unknown
  LinkshellEventHandler1 = 0x9999, // unknown

  ReqEquipDisplayFlagsChange = 0x0150, // updated 6.58 hotfix 2

  LandRenameHandler = 0x028E,           // updated 5.58h
  HousingUpdateHouseGreeting = 0x0343,  // updated 5.58h
  HousingUpdateObjectPosition = 0x9999, // unknown
  HousingEditExterior = 0x027B,         // updated 5.58h
  HousingEditInterior = 0x02E3,         // updated 5.58h

  SetSharedEstateSettings = 0x00D2, // updated 5.58h

  UpdatePositionInstance = 0x0227, // updated 6.58 hotfix 2

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
