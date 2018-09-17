#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <boost/shared_ptr.hpp>

namespace Core {

class Cell;

class Zone;

class Item;

class ItemContainer;

class Inventory;

class Session;

class ZonePosition;

typedef boost::shared_ptr< Zone > ZonePtr;
typedef boost::shared_ptr< Item > ItemPtr;
typedef boost::shared_ptr< ItemContainer > ItemContainerPtr;
typedef boost::shared_ptr< Inventory > InventoryPtr;
typedef boost::shared_ptr< Session > SessionPtr;
typedef boost::shared_ptr< ZonePosition > ZonePositionPtr;

namespace StatusEffect {
class StatusEffect;

class StatusEffectContainer;

typedef boost::shared_ptr< StatusEffect > StatusEffectPtr;
typedef boost::shared_ptr< StatusEffectContainer > StatusEffectContainerPtr;
}

namespace Entity {
class Chara;

class Player;

class BattleNpc;

typedef boost::shared_ptr< Chara > ActorPtr;
typedef boost::shared_ptr< Player > PlayerPtr;
typedef boost::shared_ptr< BattleNpc > BattleNpcPtr;
}

namespace Event {
class EventHandler;

typedef boost::shared_ptr< EventHandler > EventPtr;
}

namespace Action {
class Action;

class ActionTeleport;

class EventAction;

typedef boost::shared_ptr< Action > ActionPtr;
typedef boost::shared_ptr< ActionTeleport > ActionTeleportPtr;
typedef boost::shared_ptr< EventAction > EventActionPtr;
}


namespace Network {
class Hive;

class Acceptor;

class Connection;

class WorldConnection;

class SessionConnection;

class ZoneConnection;

typedef boost::shared_ptr< Hive > HivePtr;
typedef boost::shared_ptr< Acceptor > AcceptorPtr;
typedef boost::shared_ptr< Connection > ConnectionPtr;
typedef boost::shared_ptr< WorldConnection > WorldConnectionPtr;
typedef boost::shared_ptr< ZoneConnection > ZoneConnectionPtr;
typedef boost::shared_ptr< SessionConnection > SessionConnectionPtr;

namespace Packets {
class GamePacket;


typedef boost::shared_ptr< GamePacket > GamePacketPtr;


}
}

namespace Scripting {
using EventReturnCallback = std::function< void( Entity::Player&, uint32_t, uint16_t, uint16_t, uint16_t,
                                                 uint16_t ) >;
}

using ActionCallback = std::function< void( Entity::Player&, uint32_t, uint64_t ) >;

}


#endif
