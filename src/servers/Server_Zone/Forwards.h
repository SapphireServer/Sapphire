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
   TYPE_FORWARD( Cell );
   TYPE_FORWARD( Zone );
   TYPE_FORWARD( Item );
   TYPE_FORWARD( ItemContainer );
   TYPE_FORWARD( Inventory );
   TYPE_FORWARD( Session );
   TYPE_FORWARD( XMLConfig );
   TYPE_FORWARD( ZonePosition )

   namespace StatusEffect
   {
      TYPE_FORWARD( StatusEffect );
      TYPE_FORWARD( StatusEffectContainer );
   }

   namespace Entity
   {
      TYPE_FORWARD( Actor );
      TYPE_FORWARD( Player );
      TYPE_FORWARD( BattleNpc );
      TYPE_FORWARD( BattleNpcTemplate );
   }

   namespace Event
   {
      TYPE_FORWARD( Event );
   }

   namespace Action
   {
      TYPE_FORWARD( Action );
      TYPE_FORWARD( ActionTeleport );
      TYPE_FORWARD( ActionCast );
      TYPE_FORWARD( ActionMount );
      TYPE_FORWARD( EventAction );
   }

   namespace Network
   {
      TYPE_FORWARD( Hive );
      TYPE_FORWARD( Acceptor );
      TYPE_FORWARD( Connection );
      TYPE_FORWARD( GameConnection );
      TYPE_FORWARD( SessionConnection );
      TYPE_FORWARD( CustomMsgClientConnection );

      namespace Packets
      {
         TYPE_FORWARD( GamePacket );
      }
   }

   namespace ContentFinder
   {
      TYPE_FORWARD( ContentFinder );
   }

   namespace Scripting
   {
      class NativeScriptManager;
      typedef std::function< void( Entity::Player&, uint32_t, uint16_t, uint16_t, uint16_t ) > EventReturnCallback;
   }

   typedef std::function< void( Entity::Player&, uint32_t, uint64_t ) > ActionCallback;

}


#endif
