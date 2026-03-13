#pragma once

#include <memory>
#include <vector>
#include <filesystem>

#include "Engine/State.h"

#include "imgui.h"
#include <GameData.h>
#include <File.h>
#include <Exd/ExdData.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>

#include <Database/DbLoader.h>
#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Database/PreparedStatement.h>

#include <ServerGUI.h>

namespace Client
{
  class ServerState : public Engine::State, public std::enable_shared_from_this< ServerState >
  {
  public:
    ServerState( std::shared_ptr< Engine::ApplicationContext > pContext );

    ~ServerState() = default;

    void update( double deltaTime ) override;

    void showZoneEditor();

    void render( double deltaTime ) override;

    void load() override;

    void unload() override;

    void handleInput( double deltaTime ) override;

    void reEnter() override;

    void renderMainMenu();

  private:
    ImGuiID setupDockspace( bool& p_open, ImGuiIO& io ) const;

    ServerGUI m_serverGUI;
  };
}
