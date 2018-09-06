#ifndef COMMON_FORWARDS_H
#define COMMON_FORWARDS_H

#include <boost/shared_ptr.hpp>

namespace Core {

class ConfigMgr;

typedef boost::shared_ptr< ConfigMgr > ConfigMgrPtr;


namespace Network {
class Hive;

class Acceptor;

class Connection;

typedef boost::shared_ptr< Hive > HivePtr;
typedef boost::shared_ptr< Acceptor > AcceptorPtr;
typedef boost::shared_ptr< Connection > ConnectionPtr;

namespace Packets {
class GamePacket;

class FFXIVPacketBase;

typedef boost::shared_ptr< GamePacket > GamePacketPtr;
typedef boost::shared_ptr< FFXIVPacketBase > FFXIVPacketBasePtr;
}

}


}


#endif