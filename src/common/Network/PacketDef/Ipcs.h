#ifndef _CORE_NETWORK_PACKETS_IPCS_H
#define _CORE_NETWORK_PACKETS_IPCS_H

#include <stdint.h>

namespace Core {
namespace Network {
namespace Packets {

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
  ReqCharList = 0x0003,
  ReqEnterWorld = 0x0004,
  ReqServiceAccountList = 0x0005,

  ReqCharDelete = 0x000A,
  ReqCharCreate = 0x000B,
};

////////////////////////////////////////////////////////////////////////////////
/// Zone Connection IPC Codes
/**
* Server IPC Zone Type Codes.
*/
enum ServerZoneIpcType :
  uint16_t
{

  // static opcode ( the ones that rarely, if ever, change )
  Ping = 0x0065,
  Init = 0x0066,

  ActorFreeSpawn = 0x0191,
  InitZone = 0x019A,

  AddStatusEffect = 0x0141,
  ActorControl142 = 0x0142,
  ActorControl143 = 0x0143,
  ActorControl144 = 0x0144,
  UpdateHpMpTp = 0x0145,

  ///////////////////////////////////////////////////

  ChatBanned = 0x006B,
  Logout = 0x0077, // updated 4.4
  CFNotify = 0x0078,
  CFMemberStatus = 0x0079,
  CFDutyInfo = 0x007A,
  CFPlayerInNeed = 0x007F,

  SocialRequestError = 0x00AD,

  CFRegistered = 0x00B8, // updated 4.1
  SocialRequestResponse = 0x00BB, // updated 4.1
  CancelAllianceForming = 0x00C6, // updated 4.2



  Playtime = 0x00F5, // updated 4.3
  Chat = 0x00F4, // updated 4.4
  SocialList = 0x00FB, // updated 4.4

  UpdateSearchInfo = 0x00FE, // updated 4.4
  InitSearchInfo = 0x00FF, // updated 4.4
  ExamineSearchComment = 0x0102, // updated 4.1

  ServerNotice = 0x0104, // updated 4.4
  SetOnlineStatus = 0x0105, // updated 4.4


  CountdownInitiate = 0x010C, // updated 4.4
  CountdownCancel = 0x010D, // updated 4.4

  BlackList = 0x0110, // updated 4.4

  LogMessage = 0x00D0,

  LinkshellList = 0x0117, // updated 4.4

  ExamineFreeCompanyInfo = 0x013A, // updated 4.1
  CharaFreeCompanyTag = 0x0127, // updated 4.4
  FreeCompanyBoardMsg = 0x0128, // updated 4.4
  FreeCompanyInfo = 0x0129, // updated 4.4

  StatusEffectList = 0x0149, // updated 4.4
  Effect = 0x014C, // updated 4.4
  AoeEffect8 = 0x014F, // updated 4.4
  AoeEffect16 = 0x0150, // updated 4.4
  AoeEffect24 = 0x0151, // updated 4.4
  AoeEffect32 = 0x0152, // updated 4.4
  PersistantEffect = 0x0153, // updated 4.4

  GCAffiliation = 0x015D, // updated 4.4

  PlayerSpawn = 0x016D, // updated 4.4
  NpcSpawn = 0x016E, // updated 4.4
  ActorMove = 0x0170, // updated 4.4
  ActorSetPos = 0x0172, // updated 4.4

  ActorCast = 0x0174, // updated 4.4

  PartyList = 0x0176, // updated 4.4
  HateList = 0x0177, // updated 4.4

  ObjectSpawn = 0x0179, // updated 4.4
  ObjectDespawn = 0x017A, // updated 4.4

  SetLevelSync = 0x017B, // updated 4.4
  SilentSetClassJob = 0x017C, // updated 4.4 - seems to be the case, not sure if it's actually used for anything

  InitUI = 0x017D, // updated 4.4
  PlayerStats = 0x017E, // updated 4.4
  ActorOwner = 0x017F, // updated 4.4 ?
  PlayerStateFlags = 0x0180, // updated 4.4
  PlayerClassInfo = 0x0181, // updated 4.4
  ModelEquip = 0x0182, // updated 4.4
  Examine = 0x0183, // updated 4.4
  CharaNameReq = 0x0185, // updated 4.4
  UpdateClassInfo = 0x0186, // updated 4.4

  ItemInfo = 0x018C, // updated 4.4
  ContainerInfo = 0x018D, // updated 4.4
  InventoryTransactionFinish = 0x018E, // updated 4.4
  InventoryTransaction = 0x018F, // updated 4.4
  CurrencyCrystalInfo = 0x0190, // updated 4.4
  InventoryActionAck = 0x0193, // updated 4.4
  UpdateInventorySlot = 0x0194, // updated 4.4

  EventPlay = 0x01A2, // updated 4.4
  EventOpenGilShop = 0x01A9, // updated 4.4
  DirectorPlayScene = 0x01A6, // updated 4.4

  EventStart = 0x01AB, // updated 4.4
  EventFinish = 0x01AC, // updated 4.4

  EventLinkshell = 0x1169,

  QuestActiveList = 0x01BF, // updated 4.4
  QuestUpdate = 0x01C0, // updated 4.4
  QuestCompleteList = 0x01C1, // updated 4.4

  QuestFinish = 0x01C2, // updated 4.4
  MSQTrackerComplete = 0x01C3, // updated 4.4
  MSQTrackerProgress = 0x01C4, // updated 4.4

  QuestMessage = 0x01CA, // updated 4.4

  QuestTracker = 0x01CF, // updated 4.4

  Mount = 0x01DF, // updated 4.4

  DirectorVars = 0x01E1, // updated 4.4

  CFAvailableContents = 0x01FD, // updated 4.2

  WeatherChange = 0x01FC, // updated 4.4
  PlayerTitleList = 0x01FD, // updated 4.4
  Discovery = 0x01FE, // updated 4.4

  EorzeaTimeOffset = 0x01FF, // updated 4.4

  EquipDisplayFlags = 0x020C, // updated 4.4

  WardInfo = 0x0220, // updated 4.4
  WardHousingPermission = 0x0229, // updated 4.4
  WardYardInfo = 0x022B, // updated 4.4

  DuelChallenge = 0x0277, // 4.2; this is responsible for opening the ui
  PerformNote = 0x0286, // updated 4.3

  PrepareZoning = 0x028F, // updated 4.4
  ActorGauge = 0x0292, // updated 4.3



  // Unknown IPC types that still need to be sent
  // TODO: figure all these out properly
  IPCTYPE_UNK_320 = 0x0249, // updated 4.4
  IPCTYPE_UNK_322 = 0x024B, // updated 4.4

};

/**
* Client IPC Zone Type Codes.
*/
enum ClientZoneIpcType :
  uint16_t
{

  PingHandler = 0x0065, // unchanged 4.3
  InitHandler = 0x0066, // unchanged 4.3

  FinishLoadingHandler = 0x0069, // unchanged 4.3

  CFCommenceHandler = 0x006F,


  CFRegisterDuty = 0x0071,
  CFRegisterRoulette = 0x0072,
  PlayTimeHandler = 0x0073, // unchanged 4.3
  LogoutHandler = 0x0074, // unchanged 4.3

  CFDutyInfoHandler = 0x0078, // updated 4.2

  SocialReqSendHandler = 0x00AE, // updated 4.1
  CreateCrossWorldLS = 0x00AF, // updated 4.3

  ChatHandler = 0x00D3, // updated 4.3

  SocialListHandler = 0x00DB, // updated 4.3
  ReqSearchInfoHandler = 0x00E0, // updated 4.3
  ReqExamineSearchCommentHandler = 0x00E1, // updated 4.1

  SetSearchInfoHandler = 0x00DE, // updated 4.3

  BlackListHandler = 0x00EC, // updated 4.3
  PlayerSearchHandler = 0x00E2, // updated 4.2

  LinkshellListHandler = 0x00F4, // updated 4.3

  SearchMarketboard = 0x0103, // updated 4.3
  ReqExamineFcInfo = 0x010F, // updated 4.1

  FcInfoReqHandler = 0x011A, // updated 4.2

  ReqMarketWishList = 0x012C, // updated 4.3

  ReqJoinNoviceNetwork = 0x0129, // updated 4.2

  ReqCountdownInitiate = 0x012F, // updated 4.4
  ReqCountdownCancel = 0x0130, // updated 4.4
  ClearWaymarks = 0x0131, // updated 4.4

  ZoneLineHandler = 0x0133, // updated 4.4
  ClientTrigger = 0x0134, // updated 4.4 was 13D in 4.3
  DiscoveryHandler = 0x0135, // updated 4.4

  AddWaymark = 0x013F, // updated 4.3

  SkillHandler = 0x0137, // updated 4.4
  GMCommand1 = 0x0138, // updated 4.4
  GMCommand2 = 0x0139, // updated 4.4

  UpdatePositionHandler = 0x013B, // updated 4.4 was 144
  UpdatePositionInstance = 0x0183, // updated 4.3

  InventoryModifyHandler = 0x0142, // updated 4.4

  TalkEventHandler = 0x014B, // updated 4.4
  EmoteEventHandler = 0x014C, // updated 4.4
  WithinRangeEventHandler = 0x014D, // updated 4.4
  OutOfRangeEventHandler = 0x014E, // updated 4.4
  EnterTeriEventHandler = 0x014F, // updated 4.4

  ReturnEventHandler = 0x0154, // updated 4.4
  TradeReturnEventHandler = 0x0155, // updated 4.4

  LinkshellEventHandler = 0x0150, // updated 4.1 ??
  LinkshellEventHandler1 = 0x0151, // updated 4.1 ??

  PerformNoteHandler = 0x029B, // updated 4.3

  ReqEquipDisplayFlagsChange = 0x016F, // updated 4.4


};

////////////////////////////////////////////////////////////////////////////////
/// Chat Connection IPC Codes
/**
* Server IPC Chat Type Codes.
*/
enum ServerChatIpcType :
  uint16_t
{
  Tell = 0x0064, // updated for sb
  TellErrNotFound = 0x0066,
};

/**
* Client IPC Chat Type Codes.
*/
enum ClientChatIpcType :
  uint16_t
{
  TellReq = 0x0064,
};


} /* Packets */
} /* Network */
} /* Core */

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
