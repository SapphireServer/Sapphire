#ifndef _FORWARDS_H
#define _FORWARDS_H

#include <memory>

namespace Sapphire
{
  class Cell;
  class Zone;
  class Item;
  class ItemContainer;
  class Inventory;
  class Session;
  class ZonePosition;
  using ZonePtr = std::shared_ptr< Zone >;
  using ItemPtr =  std::shared_ptr< Item >;
  using ItemContainerPtr = std::shared_ptr< ItemContainer >;
  using InventoryPtr = std::shared_ptr< Inventory >;
  using SessionPtr = std::shared_ptr< Session >;
  using ZonePositionPtr = std::shared_ptr< ZonePosition >;

  namespace StatusEffect
  {
    class StatusEffect;
    class StatusEffectContainer;
    using StatusEffectPtr = std::shared_ptr< StatusEffect >;
    using StatusEffectContainerPtr = std::shared_ptr< StatusEffectContainer >;
  }

  namespace Entity
  {
    class Chara;
    class Player;
    class BattleNpc;
    using ActorPtr = std::shared_ptr< Chara >;
    using PlayerPtr = std::shared_ptr< Player >;
    using BattleNpcPtr = std::shared_ptr< BattleNpc >;
  }

  namespace Event
  {
    class EventHandler;
    using EventPtr = std::shared_ptr< EventHandler >;
  }

  namespace Action
  {
    class Action;
    class ActionTeleport;
    class EventAction;
    using ActionPtr = std::shared_ptr< Action >;
    using ActionTeleportPtr = std::shared_ptr< ActionTeleport >;
    using EventActionPtr = std::shared_ptr< EventAction >;
  }

  namespace Network
  {
    class Hive;
    class Acceptor;
    class Connection;
    class WorldConnection;
    class SessionConnection;
    class ZoneConnection;
    using HivePtr = std::shared_ptr< Hive >;
    using AcceptorPtr = std::shared_ptr< Acceptor >;
    using ConnectionPtr = std::shared_ptr< Connection >;
    using WorldConnectionPtr = std::shared_ptr< WorldConnection >;
    using ZoneConnectionPtr = std::shared_ptr< ZoneConnection >;
    using SessionConnectionPtr = std::shared_ptr< SessionConnection >;

    namespace Packets
    {
      class GamePacket;
      using GamePacketPtr = std::shared_ptr< GamePacket >;
    }

  }

  namespace Scripting
  {
  using EventReturnCallback = std::function< void( Entity::Player&, uint32_t, uint16_t, uint16_t, uint16_t,
                                                   uint16_t ) >;
  }

  using ActionCallback = std::function< void( Entity::Player&, uint32_t, uint64_t ) >;

}

#endif
