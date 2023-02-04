#ifndef LOBBY_PACKET_CONTAINER_H_
#define LOBBY_PACKET_CONTAINER_H_

#include <array>
#include <vector>
#include <string.h>

#include <Network/CommonNetwork.h>
#include <Util/Util.h>

#include "Forwards.h"

namespace Sapphire::Network::Packets
{

  using FFXIVPacketBasePtr = std::shared_ptr< Sapphire::Network::Packets::FFXIVPacketBase >;

  class LobbyPacketContainer
  {
  public:
    LobbyPacketContainer( uint8_t* encKey = nullptr );

    ~LobbyPacketContainer();

    void addPacket( FFXIVPacketBasePtr pEntry );

    uint16_t getSize() const;

    uint8_t* getRawData( bool addstuff = true );

  private:
    Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER m_header;

    uint8_t* m_encKey;

    std::vector< FFXIVPacketBasePtr > m_entryList;

    std::array< uint8_t, 0x2000 > m_dataBuf{ 0 };

  };

}
#endif
