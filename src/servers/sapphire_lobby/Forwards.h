#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <memory>
#include <vector>

#define TYPE_FORWARD( x ) \
class x; \
typedef std::shared_ptr< x > x ## Ptr; \
template< typename...Args > \
x ## Ptr make_ ## x( Args &&...args ) { \
return std::make_shared< x >( std::forward< Args >( args ) ... ); }\
typedef std::vector< x > x ## PtrList;

namespace Core
{
  TYPE_FORWARD( LobbySession );
}

namespace Core::Network
{
  TYPE_FORWARD( Hive );
  TYPE_FORWARD( Acceptor );
  TYPE_FORWARD( Connection );
  TYPE_FORWARD( GameConnection );
}

namespace Core::Network::Packets
{
  TYPE_FORWARD( GamePacket );
  TYPE_FORWARD( FFXIVPacketBase );
}

#endif
