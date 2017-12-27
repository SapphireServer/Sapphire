#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <boost/shared_ptr.hpp>
#include <vector>

#define TYPE_FORWARD( x ) \
class x; \
typedef boost::shared_ptr< x > x ## Ptr; \
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