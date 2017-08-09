/**
* Structural definitions common to all FFXIV:ARR packets.
*/
#ifndef _CORE_NETWORK_PACKETS_COMMON_H
#define _CORE_NETWORK_PACKETS_COMMON_H

#include <iostream>

#include <vector>

using namespace std;

namespace Core {
namespace Network {
namespace Packets {

   /**
   * Anticipated usage:
   * ==================
   * Set up a stream buffer to collect the bytes to be transmitted as a packet.
   * Now, you can do the following (given you have the structs filled out already).
   *
   * FFXIVARR_PACKET_HEADER pkt_hdr = { . . . };
   * FFXIVARR_PACKET_SEGMENT_HEADER pkt_seg_hdr[n] = { . . . };
   *
   * std::stringstream buf;
   * buf << pkt_hdr;
   * for (int i = 0; i < n; i++)
   * {
   *     buf << pkt_seg_hdr[i];
   *     buf << {pkt_seg_data[i]};
   * }
   *
   * The reverse can be done parsing a packet. Remember to validate the packet
   * type before parsing the headers.
   *
   * Compression and Encryption:
   * ===========================
   * By using std::iostream's, you can support stream filters. Simply create a
   * stream that performs the compression or encryption, and use that stream to
   * read and write.
   */

   /**
   * Structure representing the common header for all FFXIVARR packets.
   *
   * 0               4               8              12      14      16
   * +-------------------------------+---------------+-------+-------+
   * | timestamp                     | size          | cType | count |
   * +---+---+-------+---------------+---------------+-------+-------+
   * | ? |CMP|   ?   | ?             |
   * +---+---+-------+---------------+
   * (followed by /count/ FFXIVARR_PACKET_SEGMENTs)
   */
   struct FFXIVARR_PACKET_HEADER
   {

      uint64_t unknown_0;
      uint64_t unknown_8;
      /**
      * Represents the number of milliseconds since epoch that the packet was
      * sent.
      */
      uint64_t timestamp;
      /** The size of the packet header and its payload */
      uint32_t size;
      /** The type of this connection - 1 zone, 2 chat*/
      uint16_t connectionType;
      /** The number of packet segments that follow. */
      uint16_t count;
      uint8_t unknown_20;
      /** Indicates if the data segments of this packet are compressed. */
      uint8_t isCompressed;
      uint32_t unknown_24;
   };

   inline ostream& operator<<(ostream& os, const FFXIVARR_PACKET_HEADER& hdr)
   {
      return os.write(reinterpret_cast<const char*>(&hdr), sizeof hdr);
   }

   inline istream& operator>>(istream& is, FFXIVARR_PACKET_HEADER& hdr)
   {
      return is.read(reinterpret_cast<char*>(&hdr), sizeof hdr);
   }

   /**
   * Structure representing the header portion of a packet segment.
   *
   * NOTE: If the main packet header indicated the packet is compressed, this
   * header will be compressed as well! The header will NOT ever be encrypted.
   *
   * 0               4               8              12              16
   * +---------------+---------------+---------------+-------+-------+
   * | size          | source_actor  | target_actor  | type  |   ?   |
   * +---------------+---------------+---------------+-------+-------+
   * |                                                               |
   * :          type-specific data of length, size, follows          :
   * |          (NOTE: Some segments MAY be encrypted)               |
   * +---------------------------------------------------------------+
   */
   struct FFXIVARR_PACKET_SEGMENT_HEADER
   {
      /** The size of the segment header and its data. */
      uint32_t size;
      /** The session ID this segment describes. */
      uint32_t source_actor;
      /** The session ID this packet is being delivered to. */
      uint32_t target_actor;
      /** The segment type. (1, 2, 3, 7, 8, 9, 10) */
      uint16_t type;
      uint16_t _reserved_E;
   };

   inline ostream& operator<<(ostream& os, const FFXIVARR_PACKET_SEGMENT_HEADER& hdr)
   {
      return os.write(reinterpret_cast<const char*>(&hdr), sizeof hdr);
   }

   inline istream& operator>>(istream& is, FFXIVARR_PACKET_SEGMENT_HEADER& hdr)
   {
      return is.read(reinterpret_cast<char*>(&hdr), sizeof hdr);
   }

   // TODO: Include structures for the individual packet segment types

   /**
   * Server IPC Type Codes.
   */
   enum ServerIpcType : uint16_t
   {
      LobbyError                 = 0x0002,
      LobbyServiceAccountList    = 0x000C,
      LobbyCharList              = 0x000D,
      LobbyCharCreate            = 0x000E,
      LobbyEnterWorld            = 0x000F,
      LobbyServerList            = 0x0015,
      LobbyRetainerList          = 0x0017,

      Ping                       = 0x0065, // updated for sb
      Init                       = 0x0066, // updated for sb
      Chat                       = 0x0067, // updated for sb
      Logout                     = 0x0077, // updated for sb
      Playtime                   = 0x00AF, // updated for sb
      SocialRequestError         = 0x00AD,
      SocialRequestResponse      = 0x11AF,
      SocialList                 = 0x00B4, // updated for sb
      UpdateSearchInfo           = 0x00B2,
      InitSearchInfo             = 0x00B7, // updated for sb
      ServerNotice               = 0x00BC, // updated for sb
      SetOnlineStatus            = 0x00B9,
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
   * Client IPC Type Codes.
   */
   enum ClientIpcType : uint16_t
   {
      ReqCharList              = 0x0003,
      ReqEnterWorld            = 0x0004,
      ReqServiceAccountList    = 0x0005,

      ReqCharDelete            = 0x000A,
      ReqCharCreate            = 0x000B,

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
      SetSearchInfoHandler     = 0x00AC,

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


   struct FFXIVARR_PACKET_RAW
   {
      FFXIVARR_PACKET_SEGMENT_HEADER segHdr;
      std::vector<uint8_t> data;
   };

   /**
   * Structural representation of the common header for IPC packet segments.
   * NOTE: This is packet segment type 3.
   *
   * 0               4      6          8              12              16
   * +-------+-------+------+----------+---------------+---------------+
   * | 14 00 | type  |  ??  | serverId |   timestamp   |      ???      |
   * +-------+-------+------+----------+---------------+---------------+
   * |                                                                 |
   * :                             data                                :
   * |                                                                 |
   * +-----------------------------------------------------------------+
   */
   struct FFXIVARR_IPC_HEADER
   {
      uint16_t reserved;
      ServerIpcType type;
      uint16_t unknown_2;
      uint16_t serverId;
      uint32_t timestamp;
      uint32_t unknown_C;
   };

   inline ostream& operator<<(ostream& os, const FFXIVARR_IPC_HEADER& hdr)
   {
      return os.write(reinterpret_cast<const char*>(&hdr), sizeof hdr);
   }

   inline istream& operator>>(istream& is, FFXIVARR_IPC_HEADER& hdr)
   {
      return is.read(reinterpret_cast<char*>(&hdr), sizeof hdr);
   }

} /* Packets */
} /* Network */
} /* Core */

#endif /*_CORE_NETWORK_PACKETS_COMMON_H*/
