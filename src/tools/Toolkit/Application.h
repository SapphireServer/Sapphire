#pragma once

#include <string>
#include <memory>
#include <thread>

#include "Engine/GfxApiCommon.h"
#include "Engine/GfxApi.h"
#include "Engine/State.h"
#include "Engine/Logger.h"


namespace GfxApi
{
  struct Graphics;
}

namespace Engine
{
  class State;
}

namespace Engine::Resources
{
  class ResourceManager;
}

namespace Engine
{

  struct ApplicationContext
  {
    std::shared_ptr< Engine::Rendering::Graphics > pGraphics;
    std::shared_ptr< Engine::State::StateStack > pStateStack;
    std::shared_ptr< Engine::Resources::ResourceManager > pRessourceMgr;
  };

  class Application
  {
  public:

    explicit Application( const std::string& name );

    ~Application() = default;

    bool init();

    void initStates();

    void popState();

    void pushState( Engine::StatePtr state );

    void replaceTopState( Engine::StatePtr state );

    Engine::State::StateStackPtr getStateStack();

    void resetTimers();

    void mainLoop();

    void render( double dt );

    void updateState();

    void exitApplication();

    void setExiting( bool exiting );

    void handleInput( double deltaTime );

    double calculateDeltaTime( uint64_t& lastTick );

    void initImGui();

    std::shared_ptr< ApplicationContext > getContext() const;

    virtual void onInit()
    {
    }

    virtual void onMainLoop()
    {
    }

    virtual void onRender()
    {
    }

    virtual void onInitStates()
    {
    }

    virtual void onGameStep()
    {
    }

    virtual void onInitImGuiPost()
    {
    }

    virtual void parseCommandLineOptions( int argc, char** argv )
    {
    }

    virtual void onDeInit()
    {
    }

  protected:
    std::shared_ptr< ApplicationContext > m_context;

    bool m_bPopState{ false };
    std::string m_applicationName;

    bool m_bShowMouse;
    bool m_fullscreen;

    uint32_t m_resX;
    uint32_t m_resY;

    bool m_exiting;
    uint64_t m_lastRenderTick{ 0 };
    uint64_t m_lastUpdateTick{ 0 };
    float m_updateTimeStep;

  };

}