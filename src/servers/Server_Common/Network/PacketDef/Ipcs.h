#ifndef _CORE_NETWORK_PACKETS_IPCS_H
#define _CORE_NETWORK_PACKETS_IPCS_H

#include<stdint.h>

namespace Core {
namespace Network {
namespace Packets {

   ////////////////////////////////////////////////////////////////////////////////
   /// Lobby Connection IPC Codes
   /**
   * Server IPC Lobby Type Codes.
   */
   enum ServerLobbyIpcType : uint16_t
   {
      LobbyError                 = 0x0002,
      LobbyServiceAccountList    = 0x000C,
      LobbyCharList              = 0x000D,
      LobbyCharCreate            = 0x000E,
      LobbyEnterWorld            = 0x000F,
      LobbyServerList            = 0x0015,
      LobbyRetainerList          = 0x0017,

   };

   /**
   * Client IPC Lobby Type Codes.
   */
   enum ClientLobbyIpcType : uint16_t
   {
      ReqCharList                = 0x0003,
      ReqEnterWorld              = 0x0004,
      ReqServiceAccountList      = 0x0005,

      ReqCharDelete              = 0x000A,
      ReqCharCreate              = 0x000B,
   };

   ////////////////////////////////////////////////////////////////////////////////
   /// Zone Connection IPC Codes
   /**
   * Server IPC Zone Type Codes.
   */
   enum ServerZoneIpcType : uint16_t
   {
      Ping                       = 0x0065,
      Init                       = 0x0066,
      Chat                       = 0x00B9,
      ChatBanned                 = 0x006B,
      Logout                     = 0x0077,
      CFNotify                   = 0x0078,
      CFMemberStatus             = 0x0079,
      CFDutyInfo                 = 0x007A,
      CFPlayerInNeed             = 0x007F,


      SocialRequestError         = 0x00AD,
      Playtime                   = 0x00B7, // updated 4.1
      CFRegistered               = 0x00B8, // updated 4.1
      SocialRequestResponse      = 0x00BB, // updated 4.1
      SocialList                 = 0x00BE, // updated 4.1
      UpdateSearchInfo           = 0x10BB,
      InitSearchInfo             = 0x00C1, // updated 4.1
      ServerNotice               = 0x00C6, // updated 4.1
      SetOnlineStatus            = 0x00C7, // updated 4.1

      LogMessage                 = 0x00D0,
      BlackList                  = 0x00D4, // updated 4.1

      LinkshellList              = 0x00DC, // updated 4.1
      StatusEffectList           = 0x00FA, // updated 4.1
      Effect                     = 0x00FB, // updated 4.1
      GCAffiliation              = 0x00FC,

      PlayerSpawn                = 0x011C, // updated 4.1
      NpcSpawn                   = 0x011D, // updated 4.1
      ActorMove                  = 0x011E, // updated 4.1
      ActorSetPos                = 0x0120, // updated 4.1
      ActorCast                  = 0x0123, // updated 4.1
      HateList                   = 0x0126, // updated 4.1
      UpdateClassInfo            = 0x012A, // updated 4.1
      InitUI                     = 0x012B, // updated 4.1
      ActorOwner                 = 0x012D, // updated 4.1
      PlayerStats                = 0x0138, // updated 4.1
      PlayerStateFlags           = 0x013A, // updated 4.1
      PlayerClassInfo            = 0x013B, // updated 4.1
      ModelEquip                 = 0x013C, // updated 4.1

      AddStatusEffect            = 0x0141,
      ActorControl142            = 0x0142, // updated 4.1
      ActorControl143            = 0x0143, // updated 4.1
      ActorControl144            = 0x0144, // updated 4.1
      UpdateHpMpTp               = 0x0145, // updated 4.1

      ItemInfo                   = 0x014C, // updated 4.1
      ContainerInfo              = 0x014D, // updated 4.1
      InventoryTransactionFinish = 0x014E, // updated 4.1
      InventoryTransaction       = 0x014F, // updated 4.1
      CurrencyCrystalInfo        = 0x0150, // updated 4.1
      InventoryActionAck         = 0x1139,
      UpdateInventorySlot        = 0x0153, // updated 4.1

      EventPlay                  = 0x0160, // updated 4.1
      EventStart                 = 0x0169, // updated 4.1
      EventFinish                = 0x016A, // updated 4.1

      EventLinkshell             = 0x1169,

      QuestMessage               = 0x0179,
      QuestActiveList            = 0x017D, // updated 4.1
      QuestUpdate                = 0x017E, // updated 4.1
      QuestCompleteList          = 0x017F, // updated 4.1

      QuestFinish                = 0x0180, // updated 4.1

      QuestTracker               = 0x018D, // updated 4.1
      ActorSpawn                 = 0x0190, // todo: split into playerspawn/actorspawn and use opcode 0x110/0x111
      ActorFreeSpawn             = 0x0191, // unchanged for sb
      InitZone                   = 0x019A, // unchanged for sb
      Mount                      = 0x019F,
      WeatherChange              = 0x01AF, // updated for sb
      PlayerTitleList            = 0x01BD, // updated for 4.1
      Discovery                  = 0x01BE, // updated for 4.1

      EorzeaTimeOffset           = 0x01C0, // updated 4.1

      EquipDisplayFlags          = 0x01CC, // updated 4.1

      CFAvailableContents        = 0x01CF,

      PrepareZoning              = 0x0248, // updated 4.1

      // Unknown IPC types that still need to be sent
      // TODO: figure all these out properly
      IPCTYPE_UNK_320            = 0x0207, // updated 4.1
      IPCTYPE_UNK_322            = 0x0209, // updated 4.1

      ActorGauge                 = 0x249
   };

   // TODO: Include structures for the individual packet segment types

   /**
   * Client IPC Zone Type Codes.
   */
   enum ClientZoneIpcType : uint16_t
   {

      PingHandler              = 0x0065, // updated for sb
      InitHandler              = 0x0066, // updated 4.1
      ChatHandler              = 0x00AD, // updated 4.1

      FinishLoadingHandler     = 0x0069, // updated 4.1

      CFCommenceHandler        = 0x006F,
      CFRegisterDuty           = 0x0071,
      CFRegisterRoulette       = 0x0072,
      PlayTimeHandler          = 0x0073, // updated 4.1
      LogoutHandler            = 0x0074, // updated 4.1

      CFDutyInfoHandler        = 0x0078, // updated 4.1 ??

      SocialReqSendHandler     = 0x00AF, // updated 4.1
      SocialListHandler        = 0x00B3, // updated 4.1
      SetSearchInfoHandler     = 0x00B5, // updated 4.1

      ReqSearchInfoHandler     = 0x00B6, // updated 4.1

      BlackListHandler         = 0x00C0, // updated 4.1

      LinkshellListHandler     = 0x00C8, // updated 4.1

      FcInfoReqHandler         = 0x0109, // updated 4.1

      ZoneLineHandler          = 0x0110, // updated 4.1
      ActionHandler            = 0x0111, // updated 4.1
      DiscoveryHandler         = 0x0112, // updated 4.1

      SkillHandler             = 0x0114, // updated 4.1
      GMCommand1               = 0x0115, // updated 4.1 ??
      GMCommand2               = 0x0116, // updated 4.1 ??
      UpdatePositionHandler    = 0x0118, // updated 4.1

      InventoryModifyHandler   = 0x011F, // updated 4.1

      TalkEventHandler         = 0x0128, // updated 4.1
      EmoteEventHandler        = 0x0129, // updated 4.1
      WithinRangeEventHandler  = 0x012A, // updated 4.1
      OutOfRangeEventHandler   = 0x012B, // updated 4.1
      EnterTeriEventHandler    = 0x012C, // updated 4.1

      ReturnEventHandler       = 0x0131, // updated 4.1
      TradeReturnEventHandler  = 0x0132, // updated 4.1


      LinkshellEventHandler    = 0x0144, // updated 4.1 ??
      LinkshellEventHandler1   = 0x0145, // updated 4.1 ??

      ReqEquipDisplayFlagsChange  = 0x014C, // updated 4.1 ??

   };

   ////////////////////////////////////////////////////////////////////////////////
   /// Chat Connection IPC Codes
   /**
   * Server IPC Chat Type Codes.
   */
   enum ServerChatIpcType : uint16_t
   {
      Tell                     = 0x0064, // updated for sb
      TellErrNotFound          = 0x0066,
   };

   /**
   * Client IPC Chat Type Codes.
   */
   enum ClientChatIpcType : uint16_t
   {
      TellReq                  = 0x0064,
   };


} /* Packets */
} /* Network */
} /* Core */

#endif /*_CORE_NETWORK_PACKETS_IPCS_H*/
