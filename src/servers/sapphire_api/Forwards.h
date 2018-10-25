#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <memory>

namespace Core {

class Cell;

class Zone;

class Item;

class ItemContainer;

class Inventory;

class Session;

class ZonePosition;

typedef std::shared_ptr< Zone > ZonePtr;
typedef std::shared_ptr< Item > ItemPtr;
typedef std::shared_ptr< ItemContainer > ItemContainerPtr;
typedef std::shared_ptr< Inventory > InventoryPtr;
typedef std::shared_ptr< Session > SessionPtr;
typedef std::shared_ptr< ZonePosition > ZonePositionPtr;

namespace StatusEffect {
class StatusEffect;

class StatusEffectContainer;

typedef std::shared_ptr< StatusEffect > StatusEffectPtr;
typedef std::shared_ptr< StatusEffectContainer > StatusEffectContainerPtr;
}

namespace Entity {
class Chara;

class Player;

class BattleNpc;

typedef std::shared_ptr< Chara > ActorPtr;
typedef std::shared_ptr< Player > PlayerPtr;
typedef std::shared_ptr< BattleNpc > BattleNpcPtr;
}

namespace Event {
class EventHandler;

typedef std::shared_ptr< EventHandler > EventPtr;
}

namespace Action {
class Action;

class ActionTeleport;

class EventAction;

typedef std::shared_ptr< Action > ActionPtr;
typedef std::shared_ptr< ActionTeleport > ActionTeleportPtr;
typedef std::shared_ptr< EventAction > EventActionPtr;
}


namespace Network {
class Hive;

class Acceptor;

class Connection;

class WorldConnection;

class SessionConnection;

class ZoneConnection;

typedef std::shared_ptr< Hive > HivePtr;
typedef std::shared_ptr< Acceptor > AcceptorPtr;
typedef std::shared_ptr< Connection > ConnectionPtr;
typedef std::shared_ptr< WorldConnection > WorldConnectionPtr;
typedef std::shared_ptr< ZoneConnection > ZoneConnectionPtr;
typedef std::shared_ptr< SessionConnection > SessionConnectionPtr;

namespace Packets {
class GamePacket;


typedef std::shared_ptr< GamePacket > GamePacketPtr;


}
}

namespace Scripting {
using EventReturnCallback = std::function< void( Entity::Player&, uint32_t, uint16_t, uint16_t, uint16_t,
                                                 uint16_t ) >;
}

using ActionCallback = std::function< void( Entity::Player&, uint32_t, uint64_t ) >;

}


#endif
