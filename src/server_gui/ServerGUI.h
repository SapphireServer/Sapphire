#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "commonshader.h"
#include "Exd/ExdData.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <Navi/NaviProvider.h>
#include "Engine/GfxApi.h"


#include "imgui.h"
#include "datReader/DatCategories/bg/lgb.h"

#include <../src/world/WorldServer.h>

class ServerGUI
{
public:
  ServerGUI();

  ~ServerGUI();

  void init();

  // Main interface
  void show();

  // Server control methods
  void startServer();

  void stopServer();

  bool isServerRunning() const;

private:
  void serverThreadFunction();

  void showConsole();

  void showPlayers();

  void showPlayerDetails();

  std::shared_ptr< Sapphire::World::WorldServer > m_pServer;

  // Threading components
  std::thread m_serverThread;
  std::atomic< bool > m_serverRunning{ false };
  std::atomic< bool > m_shouldStopServer{ false };

  // Pause/reload controls
  std::atomic< bool > m_paused{ false };
  std::atomic< bool > m_reloadScriptsRequested{ false };

  // Console filtering state
  bool m_showTrace = true;
  bool m_showDebug = true;
  bool m_showInfo = true;
  bool m_showWarn = true;
  bool m_showError = true;
  bool m_showFatal = true;
  bool m_autoScroll = true;
  // When enabled, render console as selectable read-only text for copy operations
  bool m_selectableConsole = false;
  // Backing buffer for the selectable console view
  std::string m_consoleBuffer;

  // Player selection/details state
  int m_selectedPlayerIndex = -1;
  std::string m_selectedPlayerString;
  bool m_showPlayerDetails = false;

  // Helper function for log level filtering
  bool shouldShowLogLevel( const std::string& message ) const;

  std::string extractLogLevel( const std::string& message ) const;


  // Thread safety for server communication
  mutable std::mutex m_serverMutex;
};
