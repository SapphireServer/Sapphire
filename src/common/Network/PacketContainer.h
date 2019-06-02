#ifndef _PacketContainer_H_
#define _PacketContainer_H_

#include <vector>

#include "Common.h"
#include "CommonNetwork.h"
#include "GamePacket.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets
{

  using FFXIVPacketBasePtr = std::shared_ptr< FFXIVPacketBase >;
  class PacketContainer
  {
  public:
    PacketContainer( uint32_t segmentTargetOverride = 0 );

    ~PacketContainer();

    void addPacket( FFXIVPacketBasePtr entry );

    FFXIVARR_PACKET_HEADER m_ipcHdr;

    std::vector< FFXIVPacketBasePtr > m_entryList;

    std::string toString();

    void fillSendBuffer( std::vector< uint8_t >& sendBuffer );

  private:
    uint32_t m_segmentTargetOverride;

  };

}

#endif
