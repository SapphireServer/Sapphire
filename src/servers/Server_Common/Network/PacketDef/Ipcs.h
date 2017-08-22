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
      Ping                       = 0x0065, // updated for sb
      Init                       = 0x0066, // updated for sb
      Chat                       = 0x0067, // updated for sb
      Logout                     = 0x0077, // updated for sb
      Playtime                   = 0x00AF, // updated for sb
      SocialRequestError         = 0x00AD,
      SocialRequestResponse      = 0x11AF,
      SocialList                 = 0x00B4, // updated for sb
      UpdateSearchInfo           = 0x00B6, // updated for sb
      InitSearchInfo             = 0x00B7, // updated for sb
      ServerNotice               = 0x00BC, // updated for sb
      SetOnlineStatus            = 0x00BD, // updated for sb
      BlackList                  = 0x00CA, // updated for sb
      LinkshellList              = 0x00D1, // updated for sb
      StatusEffectList           = 0x00F0, // updated for sb
      Effect                     = 0x00F1, // updated for sb
      GCAffiliation              = 0x00FC,

      ActorSetPos                = 0x0114, // updated for sb
      ActorCast                  = 0x0116, // updated for sb
      PlayerSpawn                = 0x0110, // updated for sb
      NpcSpawn                   = 0x0111, // updated for sb
      ActorMove                  = 0x0112, // updated for sb
      HateList                   = 0x011A, // updated for sb borked
      UpdateClassInfo            = 0x011D, // updated for sb
      InitUI                     = 0x011E, // updated for sb
      PlayerStats                = 0x011F, // updated for sb
      ActorOwner                 = 0x0120, // updated for sb
      PlayerStateFlags           = 0x0121, // updated for sb
      PlayerClassInfo            = 0x0123, // updated for sb
      ModelEquip                 = 0x0124, // updated for sb
      ItemInfo                   = 0x0139, // updated for sb
      ContainerInfo              = 0x013A, // updated for sb
      InventoryTransactionFinish = 0x013B,
      InventoryTransaction       = 0x012A,
      CurrencyCrystalInfo        = 0x013D,
      InventoryActionAck         = 0x0139,
      UpdateInventorySlot        = 0x0140, // updated for sb
      AddStatusEffect            = 0x0141,
      ActorControl142            = 0x0142, // unchanged for sb
      ActorControl143            = 0x0143, // unchanged for sb
      ActorControl144            = 0x0144, // unchanged for sb
      UpdateHpMpTp               = 0x0145, // unchanged for sb

      CFNotify                   = 0x0078,
      CFMemberStatus             = 0x0079,
      CFDutyInfo                 = 0x007A,
      CFPlayerInNeed             = 0x007F,
      CFRegistered               = 0x00B0,
      CFAvailableContents        = 0x01CF,

      EventPlay                  = 0x0154, // updated for sb
      EventStart                 = 0x015D, // updated for sb
      EventFinish                = 0x015E, // updated for sb
      QuestActiveList            = 0x0171, // updated for sb
      QuestUpdate                = 0x0172, // updated for sb
      QuestCompleteList          = 0x0173, // updated for sb
      QuestFinish                = 0x0174, // updated for sb
      QuestMessage               = 0x0179,
      QuestTracker               = 0x0181, // updated for sb
      ActorSpawn                 = 0x0190, // todo: split into playerspawn/actorspawn and use opcode 0x110/0x111
      ActorFreeSpawn             = 0x0191, // unchanged for sb
      InitZone                   = 0x019A, // unchanged for sb
      WeatherChange              = 0x01AF, // updated for sb
      Discovery                  = 0x01B2, // updated for sb

      PrepareZoning              = 0x0239, // updated for sb

      // Unknown IPC types that still need to be sent
      // TODO: figure all these out properly
      IPCTYPE_UNK_320             = 0x1FB,
      IPCTYPE_UNK_322             = 0x1FD,

   };

   // TODO: Include structures for the individual packet segment types

   /**
   * Client IPC Zone Type Codes.
   */
   enum ClientZoneIpcType : uint16_t
   {

      TellChatHandler          = 0x0064,// updated for sb

      PingHandler              = 0x0065,// updated for sb
      InitHandler              = 0x0066,// updated for sb
      ChatHandler              = 0x0067,// updated for sb

      FinishLoadingHandler     = 0x0069,// updated for sb

      CFCommenceHandler        = 0x006F,
      CFRegisterDuty           = 0x0071,
      CFRegisterRoulette       = 0x0072,

      PlayTimeHandler          = 0x0073,// updated for sb
      LogoutHandler            = 0x0074,// updated for sb

      CFDutyInfoHandler        = 0x0078,

      SocialReqSendHandler     = 0x00A5,
      SocialListHandler        = 0x00AA,// updated for sb
      SetSearchInfoHandler     = 0x00AC,// updated for sb

      ReqSearchInfoHandler     = 0x00AD,

      BlackListHandler         = 0x00B7,// updated for sb

      LinkshellListHandler     = 0x00BF,// updated for sb

      FcInfoReqHandler         = 0x0100,// updated for sb

      ZoneLineHandler          = 0x0107, // updated for sb
      ActionHandler            = 0x0108,// updated for sb

      DiscoveryHandler         = 0x0109,// updated for sb

      SkillHandler             = 0x010B, // updated for sb
      GMCommand1               = 0x010C,// updated for sb
      GMCommand2               = 0x010D,// updated for sb
      UpdatePositionHandler    = 0x010F, // updated for sb

      InventoryModifyHandler   = 0x0116, // updated for sb

      TalkEventHandler         = 0x011F, // updated for sb
      EmoteEventHandler        = 0x0120, // updated for sb
      WithinRangeEventHandler  = 0x0121, // updated for sb
      OutOfRangeEventHandler   = 0x0122, // updated for sb
      EnterTeriEventHandler    = 0x0123, // updated for sb

      ReturnEventHandler       = 0x0128,
      TradeReturnEventHandler  = 0x0129,
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
