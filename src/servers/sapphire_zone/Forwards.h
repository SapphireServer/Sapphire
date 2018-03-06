#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <utility>
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
   TYPE_FORWARD( Cell );
   TYPE_FORWARD( Zone );
   TYPE_FORWARD( InstanceContent );
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
      TYPE_FORWARD( Chara );
      TYPE_FORWARD( Player );
      TYPE_FORWARD( EventObject );
   }

   namespace Event
   {
      TYPE_FORWARD( Director );
      TYPE_FORWARD( EventHandler );
   }

   namespace Action
   {
      TYPE_FORWARD( Action );
      TYPE_FORWARD( ActionTeleport );
      TYPE_FORWARD( ActionCast );
      TYPE_FORWARD( ActionMount );
      TYPE_FORWARD( EventAction );
      TYPE_FORWARD( EventItemAction );
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
      class NativeScriptMgr;
   }

   typedef std::function< void( Entity::Player&, uint32_t, uint64_t ) > ActionCallback;

}


#endif
