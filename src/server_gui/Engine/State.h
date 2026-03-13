#pragma once

#include <stack>
#include "Engine/KeyMap.h"
#include <memory>

namespace Engine
{
  struct ApplicationContext;
}

namespace Engine
{
  class State
  {
  public:
    using StateStack = std::stack< std::shared_ptr< State > >;
    using StateStackPtr = std::shared_ptr< StateStack >;

    State( std::shared_ptr< ApplicationContext > pContext );
    virtual ~State() {};

    bool shouldFinish() { return m_bShouldFinish; };
    bool shouldQuit() { return m_bQuit; };

    virtual void update( double deltaTime ) = 0;
    virtual void render( double deltaTime ) = 0;
    virtual void renderDebugLayer( double deltaTime ) {};
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void handleInput( double deltaTime ) = 0;
    virtual void reEnter() {};

    virtual void clear() {};

    virtual void onFinishState();

  protected:
    bool m_bShouldFinish{ false };
    bool m_bQuit{ false };
    Engine::KeyBindMap m_keyBinds;
    std::shared_ptr< ApplicationContext > m_context;
  };
  using StatePtr = std::shared_ptr< State >;
}

