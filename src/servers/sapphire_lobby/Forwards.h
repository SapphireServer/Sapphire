#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <vector>

#define TYPE_FORWARD( x ) \
class x; \
typedef boost::shared_ptr< x > x ## Ptr; \
template< typename...Args > \
x ## Ptr make_ ## x( Args &&...args ) { \
return boost::make_shared< x >( std::forward< Args >( args ) ... ); }\
typedef std::vector< x > x ## PtrList;

namespace Core 
{
   TYPE_FORWARD( LobbySession );

   namespace Network
   {
      TYPE_FORWARD( Hive );
      TYPE_FORWARD( Acceptor );
      TYPE_FORWARD( Connection );
      TYPE_FORWARD( GameConnection );

      namespace Packets
      {
         TYPE_FORWARD( GamePacket );
      }
   }


}


#endif