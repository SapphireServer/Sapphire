#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <utility>
#include <memory>
#include <vector>
#include <functional>
#include "Common.h"

#define TYPE_FORWARD( x ) \
class x; \
using x ## Ptr = std::shared_ptr< x >; \
using x ## UPtr = std::unique_ptr< x >; \
template< typename...Args > \
x ## Ptr make_ ## x( Args &&...args ) { \
return std::make_shared< x >( std::forward< Args >( args ) ... ); }\
using x ## PtrList = std::vector< x >;

namespace Sapphire
{
TYPE_FORWARD( Cell );
TYPE_FORWARD( Territory );
TYPE_FORWARD( HousingZone );
TYPE_FORWARD( House );
TYPE_FORWARD( InstanceContent );
TYPE_FORWARD( QuestBattle );
TYPE_FORWARD( Item );
TYPE_FORWARD( ItemContainer );
TYPE_FORWARD( Land );
TYPE_FORWARD( Linkshell );
TYPE_FORWARD( FreeCompany );

namespace World
{
TYPE_FORWARD( Session );
TYPE_FORWARD( Quest );
TYPE_FORWARD( Task );
}

namespace World::Navi
{
TYPE_FORWARD( NaviProvider );
}

namespace World::Territory::Housing
{
TYPE_FORWARD( HousingInteriorTerritory );
}

namespace Inventory
{
using InventoryContainerPair = std::pair< Common::InventoryType, uint8_t >;
using InventoryTypeList = std::vector< Common::InventoryType >;
TYPE_FORWARD( HousingItem );
}

namespace World::Manager
{
TYPE_FORWARD( HousingMgr );
}

namespace StatusEffect
{
TYPE_FORWARD( StatusEffect );
TYPE_FORWARD( StatusEffectContainer );
}

namespace Entity
{
TYPE_FORWARD( GameObject );
TYPE_FORWARD( Chara );
TYPE_FORWARD( Player );
TYPE_FORWARD( EventObject );
TYPE_FORWARD( BNpc );
}

namespace Event
{
TYPE_FORWARD( Director );
TYPE_FORWARD( EventHandler );
}

namespace World::Action
{
TYPE_FORWARD( Action );
TYPE_FORWARD( EventAction );
TYPE_FORWARD( ItemAction );
TYPE_FORWARD( EventItemAction );
TYPE_FORWARD( MountAction );
TYPE_FORWARD( ItemManipulationAction );
TYPE_FORWARD( EffectBuilder );
TYPE_FORWARD( EffectResult );

using ActionCallback = std::function< void( Entity::Player&, uint32_t, uint64_t ) >;
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
TYPE_FORWARD( FFXIVPacketBase );
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

}


#endif
