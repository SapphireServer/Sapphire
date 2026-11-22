#pragma once

#include "EventSignal.h"

namespace Sapphire::Entity
{
  class Player;
}

namespace Sapphire::World
{
  class Session;
}

namespace Sapphire::World::Notifications
{
  struct PlayerLoggedIn
  {
    Entity::Player& player;
    const Session& session;
  };

  struct PlayerLoggedOut
  {
    Entity::Player& player;
    const Session& session;
  };

  struct SessionEvents
  {
    EventSignal< PlayerLoggedIn > loggedIn;
    EventSignal< PlayerLoggedOut > loggedOut;
  };
}
