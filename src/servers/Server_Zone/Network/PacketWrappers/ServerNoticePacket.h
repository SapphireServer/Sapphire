#ifndef _SERVERNOTICEPACKET_H
#define _SERVERNOTICEPACKET_H

#include "Forwards.h"
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>

namespace Core {
namespace Network {
   namespace Packets {
      namespace Server {

         /**
          * @brief The Ping response packet.
          */
         class ServerNoticePacket : public ZoneChannelPacket< FFXIVIpcServerNotice >
         {
         public:
            ServerNoticePacket( uint32_t playerId, const std::string& message ) :
                ZoneChannelPacket< FFXIVIpcServerNotice >( playerId, playerId )
            {
               initialize( message );
            };

         private:
            void initialize( const std::string& message ) { strcpy( m_data.message, message.c_str() ); };
         };

      } // namespace Server
   }    // namespace Packets
} // namespace Network
} // namespace Core

#endif /*_SERVERNOTICEPACKET_H*/