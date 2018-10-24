#ifndef COMMON_FORWARDS_H
#define COMMON_FORWARDS_H

#include <memory>

namespace Core {

class ConfigMgr;

typedef std::shared_ptr< ConfigMgr > ConfigMgrPtr;


namespace Network {
class Hive;

class Acceptor;

class Connection;

typedef std::shared_ptr< Hive > HivePtr;
typedef std::shared_ptr< Acceptor > AcceptorPtr;
typedef std::shared_ptr< Connection > ConnectionPtr;

namespace Packets {
class GamePacket;

class FFXIVPacketBase;

typedef std::shared_ptr< GamePacket > GamePacketPtr;
typedef std::shared_ptr< FFXIVPacketBase > FFXIVPacketBasePtr;
}

}


}


#endif
