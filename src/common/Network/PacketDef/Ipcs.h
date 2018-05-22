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

      // static opcode ( the ones that rarely if ever change )
      Ping                       = 0x0065,
      Init                       = 0x0066,

      ActorSpawn                 = 0x0190, // DEPRECATED
      ActorFreeSpawn             = 0x0191,
      InitZone                   = 0x019A,

      AddStatusEffect            = 0x0141,
      ActorControl142            = 0x0142,
      ActorControl143            = 0x0143,
      ActorControl144            = 0x0144,
      UpdateHpMpTp               = 0x0145,

      ///////////////////////////////////////////////////

      ChatBanned                 = 0x006B,
      Logout                     = 0x0077,
      CFNotify                   = 0x0078,
      CFMemberStatus             = 0x0079,
      CFDutyInfo                 = 0x007A,
      CFPlayerInNeed             = 0x007F,

      SocialRequestError         = 0x00AD,

      Playtime                   = 0x00DF, // updated 4.2
      CFRegistered               = 0x00B8, // updated 4.1
      SocialRequestResponse      = 0x00BB, // updated 4.1
      CancelAllianceForming      = 0x00C6, // updated 4.2
      Chat                       = 0x00E1, // updated 4.2
      SocialList                 = 0x00E7, // updated 4.2

      UpdateSearchInfo           = 0x00EA, // updated 4.2
      InitSearchInfo             = 0x00EB, // updated 4.2

      ServerNotice               = 0x00F0, // updated 4.2
      SetOnlineStatus            = 0x00F1, // updated 4.2

      CountdownInitiate          = 0x0111, // updated 4.3
      CountdownCancel            = 0x0112, // updated 4.3

      BlackList                  = 0x00FF, // updated 4.2

      LogMessage                 = 0x00D0,

      LinkshellList              = 0x0106, // updated 4.2
      SetCharacterFCInfo         = 0x0114, // updated 4.2
      StatusEffectList           = 0x0150, // updated 4.3
      Effect                     = 0x0151, // updated 4.3
      PersistantEffect           = 0x0158, // updated 4.3

      GCAffiliation              = 0xCCFC, // OUTDATED

      PlayerSpawn                = 0x0172, // updated 4.3
      NpcSpawn                   = 0x0173, // updated 4.3
      ActorMove                  = 0x0174, // updated 4.3
      ActorSetPos                = 0x0176, // updated 4.3

      ActorCast                  = 0x0178, // updated 4.3

      HateList                   = 0x017B, // updated 4.3

      ObjectSpawn                = 0x017D, // updated 4.3
      ObjectDespawn              = 0x017E, // updated 4.3
      UpdateClassInfo            = 0x018A, // updated 4.3

      InitUI                     = 0x0181, // updated 4.3
      PlayerStats                = 0x0182, // updated 4.3
      ActorOwner                 = 0x0183, // updated 4.3 ?
      PlayerStateFlags           = 0x0184, // updated 4.3
      PlayerClassInfo            = 0x0185, // updated 4.3
      ModelEquip                 = 0x0186, // updated 4.3

      ItemInfo                   = 0x0190, // updated 4.3
      ContainerInfo              = 0x0191, // updated 4.3
      InventoryTransactionFinish = 0x0192, // updated 4.3
      InventoryTransaction       = 0x0193, // updated 4.3
      CurrencyCrystalInfo        = 0x0197, // updated 4.3

      InventoryActionAck         = 0x0180, // updated 4.2 ?
      UpdateInventorySlot        = 0x0181, // updated 4.2

      EventPlay                  = 0x018E, // updated 4.2
      DirectorPlayScene          = 0x0192, // updated 4.2

      EventStart                 = 0x0198, // updated 4.2
      EventFinish                = 0x0199, // updated 4.2

      EventLinkshell             = 0x1169,

      QuestMessage               = 0x01CE, // updated 4.3
      QuestTracker               = 0x01D3, // updated 4.3

      QuestFinish                = 0x01C6, // updated 4.3 ?
      MSQTrackerComplete         = 0x01C7, // updated 4.3 ?
      MSQTrackerProgress         = 0x01C8, // updated 4.3 ?

      QuestActiveList            = 0x01C3, // updated 4.3
      QuestUpdate                = 0x01C4, // updated 4.3
      QuestCompleteList          = 0x01C5, // updated 4.3

      Mount                      = 0x01E3, // updated 4.3

      DirectorVars               = 0x01E5, // updated 4.3

      WeatherChange              = 0x0200, // updated 4.3
      PlayerTitleList            = 0x0201, // updated 4.3
      Discovery                  = 0x0202, // updated 4.3

      EorzeaTimeOffset           = 0x0204, // updated 4.3

      EquipDisplayFlags          = 0x01FA, // updated 4.2

      CFAvailableContents        = 0x01FD, // updated 4.2

      PrepareZoning              = 0x0291, // updated 4.3
      ActorGauge                 = 0x0292, // updated 4.3

      DuelChallenge              = 0x0277, // 4.2; this is the responsible for opening an ui
      PerformNote                = 0x0286, // updated 4.3

      // Unknown IPC types that still need to be sent
      // TODO: figure all these out properly
      IPCTYPE_UNK_320            = 0x024C, // updated 4.3
      IPCTYPE_UNK_322            = 0x024E, // updated 4.3

   };

   // TODO: Include structures for the individual packet segment types

   /**
   * Client IPC Zone Type Codes.
   */
   enum ClientZoneIpcType : uint16_t
   {

      PingHandler              = 0x0065, // unchanged 4.2
      InitHandler              = 0x0066, // unchanged 4.2

      FinishLoadingHandler     = 0x0069, // unchanged 4.2

      CFCommenceHandler        = 0x006F,



      CFRegisterDuty           = 0x0071,
      CFRegisterRoulette       = 0x0072,
      PlayTimeHandler          = 0x0073, // unchanged 4.2
      LogoutHandler            = 0x0074, // unchanged 4.2

      CFDutyInfoHandler        = 0x0078, // updated 4.2

      SocialReqSendHandler     = 0x00AE, // updated 4.1

      ChatHandler              = 0x00D3, // updated 4.3

      SocialListHandler        = 0x00DB, // updated 4.3
      ReqSearchInfoHandler     = 0x00E0, // updated 4.3
      SetSearchInfoHandler     = 0x00DE, // updated 4.3

      BlackListHandler         = 0x00EC, // updated 4.3
      PlayerSearchHandler      = 0x00E2, // updated 4.2

      LinkshellListHandler     = 0x00F4, // updated 4.3

      FcInfoReqHandler         = 0x011A, // updated 4.2


      ReqJoinNoviceNetwork     = 0x0129, // updated 4.2
      ReqCountdownInitiate     = 0x012C, // updated 4.2
      ReqCountdownCancel       = 0x012D, // updated 4.2

      ZoneLineHandler          = 0x013C, // updated 4.3
      ActionHandler            = 0x013D, // updated 4.3
      DiscoveryHandler         = 0x013E, // updated 4.3

      SkillHandler             = 0x0140, // updated 4.3
      GMCommand1               = 0x0141, // updated 4.3
      GMCommand2               = 0x0142, // updated 4.3

      UpdatePositionHandler    = 0x0144, // updated 4.3
      UpdatePositionInstance   = 0x0183, // updated 4.3

      InventoryModifyHandler   = 0x013F, // updated 4.2

      TalkEventHandler         = 0x0154, // updated 4.3
      EmoteEventHandler        = 0x0155, // updated 4.3
      WithinRangeEventHandler  = 0x0156, // updated 4.3
      OutOfRangeEventHandler   = 0x0157, // updated 4.3
      EnterTeriEventHandler    = 0x0158, // updated 4.3

      ReturnEventHandler       = 0x015D, // updated 4.3
      TradeReturnEventHandler  = 0x015E, // updated 4.3

      LinkshellEventHandler    = 0x0150, // updated 4.1 ??
      LinkshellEventHandler1   = 0x0151, // updated 4.1 ??

      PerformNoteHandler       = 0x0160, // updated 4.2

      ReqEquipDisplayFlagsChange  = 0x0178, // updated 4.3


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
