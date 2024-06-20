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
  CFMemberStatus = 0x21F, // updated 6.58 hotfix 2?
  CFDutyInfo = 0x2E8, // updated 6.58 hotfix 2?
  CFPlayerInNeed = 0xF07F,
  CFPreferredRole = 0x282,  // updated 6.58 hotfix 2
  CFCancel = 0x384,        // updated 6.58 hotfix 2
  CFUnk = 0x196, // updated 6.58 hotfix 2
  SocialRequestError = 0xF0AD,

  CFRegistered = 0x029F,          // updated 5.58h
  SocialInviteResponse = 0x322,  // updated 6.58 hotfix 2
  SocialInviteUpdate = 0x01C1, // updated 6.58 hotfix 2
  SocialInviteResult = 0x031B, // updated 6.58 hotfix 2
  CancelAllianceForming = 0xF0C6, // updated 4.2

  LogMessage = 0x19C, // updated 6.58 hotfix 2?

  Chat = 0x0325, // updated 6.58 hotfix 2

  WorldVisitList = 0xF0FE, // added 4.5

  SocialList = 0x1F2, // updated 6.58 hotfix 2

  ExamineSearchInfo = 0x014A, // updated 6.58 hotfix 2
  UpdateSearchInfo = 0x00CF, // updated 6.58 hotfix 2
  InitSearchInfo = 0x329,       // updated 6.58 hotfix 2
  ExamineSearchComment = 0x244, // updated 6.58 hotfix 2?

  ServerNoticeShort = 0xF333, // updated 5.58h
  ServerNotice = 0x33B,       // updated 6.58 hotfix 2
  SetOnlineStatus = 0x285,    // updated 6.58 hotfix 2

  CountdownInitiate = 0x376, // updated 6.58 hotfix 2
  CountdownCancel = 0x2B7,    // updated 6.58 hotfix 2

  PlayerAddedToBlacklist = 0xe2,     // updated 6.48
  PlayerRemovedFromBlacklist = 0x201, // updated 6.58 hotfix 2?
  BlackList = 0x38A,                   // updated 6.58 hotfix 2

  LinkshellList = 0x2B2,           // updated 6.58 hotfix 2
  CrossWorldLinkshellList = 0x3D5, // updated 6.58 hotfix 2
  FellowshipList = 0x373,          // updated 6.58 hotfix 2

  MailDeleteRequest = 0x168, // updated 6.58 hotfix 2?

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

  PartyList = 0x164,         // updated 6.58 hotfix 2
  PartyUpdate = 0x2D8,       // updated 6.58 hotfix 2
  HateRank = 0x2A7,            // updated 6.58 hotfix 2
  HateList = 0x26B,            // updated 6.58 hotfix 2
  ObjectSpawn = 0x03B8, // updated 6.58 hotfix 2
  ObjectDespawn = 0x1D8,      // updated 6.58 hotfix 2
  SilentSetClassJob = 0xF18E, // updated 5.0 - seems to be the case, not sure if it's actually used for anything
  PlayerSetup = 0x035F, // updated 6.58 hotfix 2
  PlayerStats = 0x034F, // updated 6.58 hotfix 2
  ActorOwner = 0x2c3,         // updated 6.58 hotfix 2
  PlayerStateFlags = 0x1B6,   // updated 6.58 hotfix 2
  PlayerClassInfo = 0x238,    // updated 6.58 hotfix 2
  PlayerUpdateLook = 0xa8,    // updated 6.48
  CharaVisualEffect = 0x0C1,  // updated 6.58 hotfix 2

  ModelEquip = 0x27D,    // updated 6.58 hotfix 2
  Examine = 0x02C0, // updated 6.58 hotfix 2
  CharaNameReq = 0x33C, // updated 6.58 hotfix 2?

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

  EventReturn = 0x1F3, // updated 6.58 hotfix 2

  EventLinkshell = 0x1169,

  QuestActiveList = 0x247,   // updated 6.58 hotfix 2
  QuestUpdate = 0x1A4,       // updated 6.58 hotfix 2
  QuestCompleteList = 0x352, // updated 6.58 hotfix 2

  QuestFinish = 0x2BB,         // updated 6.58 hotfix 2
  MSQTrackerComplete = 0x1A9,  // updated 6.58 hotfix 2
  MSQTrackerProgress = 0xF1CD, // updated 4.5 ? this actually looks like the two opcodes have been combined, see #474

  QuestMessage = 0x06B, // updated 6.58 hotfix 2

  QuestTracker = 0x27C, // updated 6.58 hotfix 2

  Mount = 0x09F, // updated 6.58 hotfix 2

  DirectorVars = 0x3A6,   // updated 6.58 hotfix 2
  DirectorMsg1 = 0xF084,  // updated 5.18
  DirectorMsg2 = 0xF0C1,  // updated 5.18
  DirectorMsg4 = 0x3A9,  // updated 6.58 hotfix 2
  DirectorMsg8 = 0xF28A,  // updated 5.18
  DirectorMsg16 = 0xF28C, // updated 5.18
  DirectorPopUp2 = 0x300,     // updated 6.58 hotfix 2
  DirectorPopUp4 = 0xF19B,    // updated 5.58h
  DirectorPopUp8 = 0xF271,    // updated 5.58h

  CFAvailableContents = 0xF1FD, // updated 4.2

  WeatherChange = 0x021D, // updated 6.58 hotfix 2
  PlayerTitleList = 0x1FF, // updated 6.58 hotfix 2?
  Discovery = 0x11E,       // updated 6.58 hotfix 2

  EorzeaTimeOffset = 0x398, // updated 6.58 hotfix 2?

  EquipDisplayFlags = 0x33A, // updated 6.58 hotfix 2

  MiniCactpotInit = 0x0286, // added 5.31
  ShopMessage = 0x016F,     // updated 6.58 hotfix 2
  LootMessage = 0x265,      // updated 6.58 hotfix 2
  ResultDialog = 0x0362, // updated 6.58 hotfix 2
  DesynthResult = 0x007F, // updated 6.58 hotfix 2

  /// Housing //////////////////////////////////////

  LandSetInitialize = 0x1C9,            // updated 6.58 hotfix 2
  LandUpdate = 0x1AB,                   // updated 6.58 hotfix 2?
  LandAvailability = 0x236,            // updated 6.58 hotfix 2
  YardObjectSpawn = 0x0D1,              // updated 6.58 hotfix 2?
  HousingIndoorInitialize = 0x084,      // updated 6.58 hotfix 2?
  LandPriceUpdate = 0x0F1,              // updated 6.58 hotfix 2
  LandInfoSign = 0x15F,                 // updated 6.58 hotfix 2
  LandRename = 0x09B,                   // updated 6.58 hotfix 2?
  HousingEstateGreeting = 0x298,        // updated 6.58 hotfix 2?
  HousingUpdateLandFlagsSlot = 0x151,   // updated 6.58 hotfix 2?
  HousingLandFlags = 0x330,             // updated 6.58 hotfix 2
  HousingShowEstateGuestAccess = 0x0E6, // updated 6.58 hotfix 2?

  HousingObjectInitialize = 0x1AA,    // updated 6.58 hotfix 2
  HousingInternalObjectSpawn = 0x2D7, // updated 6.58 hotfix 2?

  HousingWardInfo = 0x327,  // updated 6.58 hotfix 2?
  HousingObjectMove = 0x21b, // updated 6.48
  HousingObjectDye = 0x333,  // updated 6.58 hotfix 2?

  SharedEstateSettingsResponse = 0x25B, // updated 6.58 hotfix 2?

  LandUpdateHouseName = 0x0B5, // updated 6.58 hotfix 2?
  LandSetMap = 0x32B,         // updated 6.58 hotfix 2

  CeremonySetActorAppearance = 0x140, // updated 6.58 hotfix 2?

  //////////////////////////////////////////////////

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x266,    // updated 6.58 hotfix 2?

  DutyGauge = 0x02E5, // updated 5.58h

  // daily quest info -> without them sent,  login will take longer...
  DailyQuests = 0x2EF,           // updated 6.58 hotfix 2
  DailyQuestRepeatFlags = 0x134, // updated 6.58 hotfix 2

  MapUpdate = 0x0FF,    // updated 6.58 hotfix 2
  MapUpdate4 = 0x345,  // updated 6.58 hotfix 2
  MapUpdate8 = 0x114,  // updated 6.58 hotfix 2
  MapUpdate16 = 0x2CE, // updated 6.58 hotfix 2
  MapUpdate32 = 0x205, // updated 6.58 hotfix 2
  MapUpdate64 = 0x1FC, // updated 6.58 hotfix 2
  MapUpdate128 = 0x158, // updated 6.58 hotfix 2

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
  RSVData = 0x065,             // updated 6.58 hotfix 2?
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

  CFCommenceHandler = 0x0242, // updated 6.58 hotfix 2

  CFCancelHandler = 0x02B2,    // updated 5.58h
  CFRegisterDuty = 0x0312,     // updated 6.58 hotfix 2
  CFRegisterRoulette = 0x037A, // updated 5.58h
  PlayTimeHandler = 0x0378,    // updated 6.58 hotfix 2
  LogoutHandler = 0x384,       // updated 6.58 hotfix 2
  CancelLogout = 0x01e3,       // updated 6.31h
  CFDutyInfoHandler = 0xF078,  // updated 4.2

  SocialInviteHandler = 0x00F5, // updated 6.58 hotfix 2
  SocialReplyHandler = 0x0160, // updated 6.58 hotfix 2
  CreateCrossWorldLS = 0x9999,    // updated 5.58h

  ChatHandler = 0x246, // updated 6.58 hotfix 2
  PartyChangeLeaderHandler = 0x0E4, // updated 6.58 hotfix 2
  PartyLeaveHandler = 0x0373, // updated 6.58 hotfix 2
  PartyKickHandler = 0x013F, // updated 6.58 hotfix 2
  PartyDisbandHandler = 0x03BF, // updated 6.58 hotfix 2

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
  ReqCountdownCancel = 0xF23a,   // updated 6.31h

  ZoneLineHandler = 0x326,   // updated 6.58 hotfix 2
  ClientTrigger = 0x035C, // updated 6.58 hotfix 2
  ClientTriggerEnvironment = 0x0295, // updated 6.58 hotfix 2
  DiscoveryHandler = 0x0129, // updated 6.58 hotfix 2

  SkillHandler = 0x07C,   // updated 6.58 hotfix 2
  GMCommand1 = 0x152,      // updated 6.58 hotfix 2
  GMCommand2 = 0x306,     // updated 6.58 hotfix 2
  AoESkillHandler = 0x0FC, // updated 6.58 hotfix 2

  UpdatePositionHandler = 0x0256, // updated 6.58 hotfix 2

  InventoryModifyHandler = 0x023E, // updated 6.58 hotfix 2

  InventoryEquipRecommendedItems = 0x355, // updated 6.58 hotfix 2

  ReqPlaceHousingItem = 0x032D, // updated 6.58 hotfix 2
  BuildPresetHandler = 0x0D9,  // updated 6.58 hotfix 2

  TalkEventHandler = 0x23A,         // updated 6.58 hotfix 2
  EmoteEventHandler = 0x1B5,        // updated 6.58 hotfix 2
  WithinRangeEventHandler = 0x38E,  // updated 6.58 hotfix 2
  OutOfRangeEventHandler = 0x200,   // updated 6.58 hotfix 2
  EnterTeriEventHandler = 0x105,    // updated 6.58 hotfix 2
  ShopEventHandler = 0x0148,        // updated 6.58 hotfix 2
  ReturnEventHandler = 0x07D,       // updated 6.58 hotfix 2
  TradeReturnEventHandler = 0x166,  // updated 6.58 hotfix 2
  TradeReturnEventHandler2 = 0x37D, // updated 6.58 hotfix 2
  EventYield2Handler = 0x0273,      // updated 6.58 hotfix 2
  EventYield16Handler = 0x0207,     // updated 5.58h

  LinkshellEventHandler = 0x9999,  // unknown
  LinkshellEventHandler1 = 0x9999, // unknown

  ReqEquipDisplayFlagsChange = 0x0150, // updated 6.58 hotfix 2

  LandRenameHandler = 0x03B7,           // updated 6.58 hotfix 2
  HousingUpdateHouseGreeting = 0x03A7,  // updated 6.58 hotfix 2
  HousingUpdateObjectPosition = 0x0157, // updated 6.58 hotfix 2
  HousingEditExterior = 0x028C,         // updated 6.58 hotfix 2
  HousingEditInterior = 0x0336,         // updated 6.58 hotfix 2

  SetSharedEstateSettings = 0x00D2, // updated 5.58h

  UpdatePositionInstance = 0x0227, // updated 6.58 hotfix 2

  PerformNoteHandler = 0x0243, // updated 5.58h
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
