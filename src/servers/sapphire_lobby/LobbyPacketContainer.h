#ifndef _LobbyPacketContainer_H_
#define _LobbyPacketContainer_H_

#include <vector>
#include <string.h>

#include <Network/CommonNetwork.h>
#include <Util/Util.h>

#include "Forwards.h"

namespace Core {
   namespace Network {
      namespace Packets {
         class GamePacket;

         class LobbyPacketContainer 
         {
         public:
            LobbyPacketContainer( uint8_t* encKey = nullptr );
            ~LobbyPacketContainer();

            void addPacket( GamePacketPtr pEntry );

            uint16_t getSize() const;
            
            uint8_t* getRawData( bool addstuff = true );
            
         private:
            Core::Network::Packets::FFXIVARR_PACKET_HEADER m_header;

            uint8_t * m_encKey;

            std::vector<GamePacket> m_entryList;

            uint8_t	m_dataBuf[0x2000];

         };

      }
   }
}
#endif
