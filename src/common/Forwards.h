#ifndef COMMON_FORWARDS_H
#define COMMON_FORWARDS_H

#include <memory>

namespace Sapphire::Common
{
  class ConfigMgr;
  class Framework;
  using ConfigMgrPtr = std::shared_ptr< ConfigMgr >;
  using FrameworkPtr = std::shared_ptr< Framework >;
}

namespace Sapphire::Common::Network
{
  class Hive;
  class Acceptor;
  class Connection;
  using HivePtr = std::shared_ptr< Hive >;
  using AcceptorPtr = std::shared_ptr< Acceptor >;
  using ConnectionPtr = std::shared_ptr< Connection >;
}

namespace Sapphire::Common::Network::Packets
{
  class GamePacket;
  class FFXIVPacketBase;
  using GamePacketPtr = std::shared_ptr< GamePacket >;
  using FFXIVPacketBasePtr = std::shared_ptr< FFXIVPacketBase >;
}

#endif
