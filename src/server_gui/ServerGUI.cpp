#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include "ServerGUI.h"

#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include "ServerState.h"

#include "Engine/GfxApi.h"
#include "Engine/ResourceManager.h"
#include "Engine/ShaderResource.h"


#include "imgui.h"
#include <random>
#include <vector>

#include "Engine/Input.h"
#include "Engine/Service.h"
#include "Engine/Logger.h"

#include <math.h>
#include <vector>

#include <algorithm>
#include <unordered_set>
#include <glm/gtx/matrix_decompose.hpp>

#include "Application.h"

#include "Service.h"
#include <algorithm>
#include <cctype>

#include "Common.h"
#include "PreparedResultSet.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "imgui_internal.h"
#include "Util/Paths.h"

#include <../src/world/WorldServer.h>
#include <../src/world/Session.h>
#include <../src/world/Actor/Player.h>
#include <../src/world/Script/ScriptMgr.h>

#include <Util/CrashHandler.h>
#include <Service.h>

#include "Logging/Logger.h"
#include "Util/Util.h"

using namespace Sapphire;
using namespace Sapphire::World;

[[maybe_unused]]
Common::Util::CrashHandler crashHandler;


ServerGUI::ServerGUI()
{
}

ServerGUI::~ServerGUI()
{
}

void ServerGUI::init()
{
  Logger::init( "log/world" );
}


void ServerGUI::startServer()
{
  if( m_serverRunning.load() )
    return;

  m_shouldStopServer.store( false );
  m_serverThread = std::thread( &ServerGUI::serverThreadFunction, this );
}

void ServerGUI::stopServer()
{
  if( !m_serverRunning.load() )
    return;

  m_shouldStopServer.store( true );

  {
    std::lock_guard< std::mutex > lock( m_serverMutex );
    if( m_pServer )
    {
      // Signal the server to stop
      m_pServer->shutdown();
    }
  }

  if( m_serverThread.joinable() )
    m_serverThread.join();

  m_serverRunning.store( false );
}

bool ServerGUI::isServerRunning() const
{
  return m_serverRunning.load();
}

void ServerGUI::serverThreadFunction()
{
  try
  {
    {
      std::lock_guard< std::mutex > lock( m_serverMutex );
      m_pServer = std::make_shared< Sapphire::World::WorldServer >( "world.ini" );
      Common::Service< Sapphire::World::WorldServer >::set( m_pServer );
      m_pServer->init( 0, 0 );
    }

    m_serverRunning.store( true );

    // Server main loop - runs in this thread
    while( m_pServer->isRunning() && !m_shouldStopServer.load() )
    {
      auto tickCount = Common::Util::getTimeMs();

      // Handle script reload request on the server thread to avoid races
      if( m_reloadScriptsRequested.load() )
      {
        try
        {
          auto& scriptMgr = Sapphire::Common::Service< Sapphire::Scripting::ScriptMgr >::ref();
          scriptMgr.shutdown();
          scriptMgr.init();
          Logger::info( "Scripts reloaded via ServerGUI" );
        }
        catch( const std::exception& e )
        {
          Logger::error( "Failed to reload scripts: {}", e.what() );
        }
        m_reloadScriptsRequested.store( false );
      }

      if( !m_paused.load() )
      {
        std::lock_guard< std::mutex > lock( m_serverMutex );
        if( m_pServer )
          m_pServer->update( tickCount );
      }

      // Small sleep to prevent 100% CPU usage
      std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }
  } catch( const std::exception& e )
  {
    Logger::error( "Server thread exception: {}", e.what() );
  }

  {
    std::lock_guard< std::mutex > lock( m_serverMutex );
    if( m_pServer )
    {
      m_pServer->shutdown();
      m_pServer.reset();
    }
  }

  m_serverRunning.store( false );
}


void ServerGUI::show()
{
  ImGui::Begin( "Server Control" );

  if( isServerRunning() )
  {
    ImGui::TextColored( ImVec4( 0, 1, 0, 1 ), "Server Status: Running" );
    if( m_paused.load() )
    {
      ImGui::SameLine();
      ImGui::TextColored( ImVec4( 1.0f, 1.0f, 0.0f, 1.0f ), "[Paused]" );
    }

    if( ImGui::Button( "Stop Server" ) )
    {
      stopServer();
    }
    ImGui::SameLine();
    if( !m_paused.load() )
    {
      if( ImGui::Button( "Pause Server" ) )
      {
        m_paused.store( true );
      }
    }
    else
    {
      if( ImGui::Button( "Unpause Server" ) )
      {
        m_paused.store( false );
      }
    }
    ImGui::SameLine();
    if( ImGui::Button( "Reload Scripts" ) )
    {
      m_reloadScriptsRequested.store( true );
    }
  }
  else
  {
    ImGui::TextColored( ImVec4( 1, 0, 0, 1 ), "Server Status: Stopped" );
    if( ImGui::Button( "Start Server" ) )
    {
      startServer();
    }
  }

  ImGui::End();

  showConsole();
  showPlayers();
  if( m_showPlayerDetails )
    showPlayerDetails();
}


void ServerGUI::showConsole()
{
  ImGui::Begin( "Console" );

  // Log level filter controls
  ImGui::Text( "Log Level Filters:" );
  ImGui::SameLine();
  ImGui::Checkbox( "Trace", &m_showTrace );
  ImGui::SameLine();
  ImGui::Checkbox( "Debug", &m_showDebug );
  ImGui::SameLine();
  ImGui::Checkbox( "Info", &m_showInfo );
  ImGui::SameLine();
  ImGui::Checkbox( "Warn", &m_showWarn );
  ImGui::SameLine();
  ImGui::Checkbox( "Error", &m_showError );
  ImGui::SameLine();
  ImGui::Checkbox( "Fatal", &m_showFatal );

  ImGui::SameLine();
  ImGui::Checkbox( "Auto-scroll", &m_autoScroll );
  ImGui::SameLine();
  ImGui::Checkbox( "Selection mode", &m_selectableConsole );

  ImGui::Separator();

  // Clear and copy buttons
  if( ImGui::Button( "Clear Console" ) )
  {
    Logger::getBufferSink()->clearMessages();
  }
  ImGui::SameLine();
  bool copyRequested = ImGui::Button( "Copy Visible" );

  // Gather and filter messages once
  auto messages = Logger::getBufferSink()->getMessages();
  std::vector<std::string> filtered;
  filtered.reserve( messages.size() );
  for( const auto& msg : messages )
  {
    if( shouldShowLogLevel( msg ) )
      filtered.emplace_back( msg );
  }

  // Provide a concatenated buffer for selection/copy when in selection mode or for the Copy Visible button
  std::string joined;
  if( m_selectableConsole || copyRequested )
  {
    size_t total = 0;
    for( const auto& s : filtered ) total += s.size() + 1; // +1 for '\n'
    joined.reserve( total + 1 );
    for( size_t i = 0; i < filtered.size(); ++i )
    {
      joined += filtered[i];
      if( i + 1 < filtered.size() ) joined += '\n';
    }
  }

  if( copyRequested )
  {
    ImGui::SetClipboardText( joined.c_str() );
  }

  // Console output area
  ImGui::BeginChild( "ScrollingRegion", ImVec2( 0, 0 ), false, ImGuiWindowFlags_HorizontalScrollbar );

  bool shouldScrollToBottom = false;

  if( m_selectableConsole )
  {
    // Build/refresh read-only text buffer for selection
    m_consoleBuffer.assign( joined.begin(), joined.end() );
    m_consoleBuffer.push_back( '\0' ); // Ensure null-terminated and writable buffer

    ImGuiInputTextFlags flags = ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_NoUndoRedo;
    // Note: buffer size includes our appended null terminator
    ImGui::InputTextMultiline( "##ConsoleBuffer", m_consoleBuffer.data(), m_consoleBuffer.size(), ImGui::GetContentRegionAvail(), flags );
  }
  else
  {
    // Colored, non-selectable view
    for( const auto& message : filtered )
    {
      // Color code based on log level
      std::string logLevel = extractLogLevel( message );
      ImVec4 color = ImVec4( 1.0f, 1.0f, 1.0f, 1.0f ); // Default white

      if( logLevel == "trace" )
        color = ImVec4( 0.6f, 0.6f, 0.6f, 1.0f ); // Gray
      else if( logLevel == "debug" )
        color = ImVec4( 0.7f, 0.7f, 1.0f, 1.0f ); // Light blue
      else if( logLevel == "info" )
        color = ImVec4( 1.0f, 1.0f, 1.0f, 1.0f ); // White
      else if( logLevel == "warn" )
        color = ImVec4( 1.0f, 1.0f, 0.0f, 1.0f ); // Yellow
      else if( logLevel == "error" )
        color = ImVec4( 1.0f, 0.5f, 0.5f, 1.0f ); // Light red
      else if( logLevel == "fatal" )
        color = ImVec4( 1.0f, 0.0f, 0.0f, 1.0f ); // Red

      ImGui::TextColored( color, message.c_str() );
      shouldScrollToBottom = true;
    }

    // Auto-scroll to bottom if new messages arrived and auto-scroll is enabled
    if( m_autoScroll && shouldScrollToBottom && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() )
    {
      ImGui::SetScrollHereY( 1.0f );
    }
  }

  ImGui::EndChild();
  ImGui::End();
}

bool ServerGUI::shouldShowLogLevel( const std::string& message ) const
{
  std::string logLevel = extractLogLevel( message );

  if( logLevel == "trace" ) return m_showTrace;
  if( logLevel == "debug" ) return m_showDebug;
  if( logLevel == "info" ) return m_showInfo;
  if( logLevel == "warn" ) return m_showWarn;
  if( logLevel == "error" ) return m_showError;
  if( logLevel == "fatal" ) return m_showFatal;

  // Show unknown log levels by default
  return true;
}

std::string ServerGUI::extractLogLevel( const std::string& message ) const
{
  // Extract log level from format: [HH:MM:SS] [LEVEL] message
  size_t firstBracket = message.find( ']' );
  if( firstBracket == std::string::npos ) return "";

  size_t secondBracket = message.find( '[', firstBracket + 1 );
  if( secondBracket == std::string::npos ) return "";

  size_t thirdBracket = message.find( ']', secondBracket + 1 );
  if( thirdBracket == std::string::npos ) return "";

  return message.substr( secondBracket + 1, thirdBracket - secondBracket - 1 );
}

void ServerGUI::showPlayers()
{
  ImGui::Begin( "Players" );

  if( !isServerRunning() )
  {
    ImGui::Text( "Server not running." );
    ImGui::End();
    return;
  }

  std::vector< std::string > players;
  {
    std::lock_guard< std::mutex > lock( m_serverMutex );
    if( m_pServer )
    {
      players = m_pServer->getLoggedInPlayersSnapshot();
    }
  }

  ImGui::Text( "Logged in players: %d", static_cast< int >( players.size() ) );
  ImGui::Separator();

  // Grid/Table view with selectable rows
  ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable |
                               ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable |
                               ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
                               ImGuiTableFlags_ScrollY;

  const float tableHeight = ImGui::GetContentRegionAvail().y;
  if( ImGui::BeginTable( "PlayersTable", 5, tableFlags, ImVec2( 0, tableHeight ) ) )
  {
    ImGui::TableSetupScrollFreeze( 0, 1 );
    ImGui::TableSetupColumn( "#", ImGuiTableColumnFlags_WidthFixed, 40.0f );
    ImGui::TableSetupColumn( "Name", ImGuiTableColumnFlags_PreferSortAscending, 160.0f );
    ImGui::TableSetupColumn( "Character ID", ImGuiTableColumnFlags_PreferSortAscending, 120.0f );
    ImGui::TableSetupColumn( "Territory", 0, 200.0f );
    ImGui::TableSetupColumn( "Connected", ImGuiTableColumnFlags_PreferSortDescending, 110.0f );
    ImGui::TableHeadersRow();

    // Helper to parse the entry string
    auto parseEntry = []( const std::string& entry )
    {
      struct Parts
      {
        std::string name;
        std::string cid;
        std::string territory;
        std::string connected;
      } p;
      // Expected format: "Name (CID)  —  Territory  —  Connected HH:MM:SS"
      // Split on em-dash separator
      std::string::size_type dash1 = entry.find( " — " );
      std::string::size_type dash2 = std::string::npos;
      if( dash1 != std::string::npos )
        dash2 = entry.find( " — ", dash1 + 3 );

      std::string left = ( dash1 == std::string::npos ) ? entry : entry.substr( 0, dash1 );
      std::string mid = ( dash1 != std::string::npos && dash2 != std::string::npos )
                          ? entry.substr( dash1 + 3, dash2 - ( dash1 + 3 ) )
                          : std::string();
      std::string right = ( dash2 != std::string::npos ) ? entry.substr( dash2 + 3 ) : std::string();

      // left: Name (CID)
      auto lpar = left.rfind( '(' );
      auto rpar = left.rfind( ')' );
      if( lpar != std::string::npos && rpar != std::string::npos && rpar > lpar )
      {
        p.name = left.substr( 0, lpar );
        // trim spaces at end of name
        while( !p.name.empty() && ( p.name.back() == ' ' || p.name.back() == '\t' ) ) p.name.pop_back();
        p.cid = left.substr( lpar + 1, rpar - lpar - 1 );
      }
      else
      {
        p.name = left;
      }

      // mid: Territory
      p.territory = mid;
      // right: Connected ... just keep as-is
      p.connected = right;
      return p;
    };

    for( int i = 0; i < static_cast< int >( players.size() ); ++i )
    {
      const auto& entry = players[ i ];
      auto parts = parseEntry( entry );

      ImGui::TableNextRow();

      // Column 0: index and selectable hit area across row
      ImGui::TableSetColumnIndex( 0 );
      {
        std::string idxStr = std::to_string( i + 1 );
        ImGui::Selectable( idxStr.c_str(), m_selectedPlayerIndex == i, ImGuiSelectableFlags_SpanAllColumns );
      }
      if( ImGui::IsItemClicked() )
      {
        m_selectedPlayerIndex = i;
        m_selectedPlayerString = entry;
      }
      if( ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked( 0 ) )
      {
        m_selectedPlayerIndex = i;
        m_selectedPlayerString = entry;
        m_showPlayerDetails = true;
      }
      if( ImGui::BeginPopupContextItem() )
      {
        if( ImGui::MenuItem( "Open Details" ) )
        {
          m_selectedPlayerIndex = i;
          m_selectedPlayerString = entry;
          m_showPlayerDetails = true;
        }
        ImGui::EndPopup();
      }

      // Column 1: Name
      ImGui::TableSetColumnIndex( 1 );
      ImGui::TextUnformatted( parts.name.c_str() );
      // Column 2: CID
      ImGui::TableSetColumnIndex( 2 );
      ImGui::TextUnformatted( parts.cid.c_str() );
      // Column 3: Territory
      ImGui::TableSetColumnIndex( 3 );
      ImGui::TextUnformatted( parts.territory.c_str() );
      // Column 4: Connected
      ImGui::TableSetColumnIndex( 4 );
      ImGui::TextUnformatted( parts.connected.c_str() );
    }

    ImGui::EndTable();
  }

  ImGui::End();
}


void ServerGUI::showPlayerDetails()
{
  if( !m_showPlayerDetails )
    return;

  // Parse currently selected player string
  auto parseEntry = []( const std::string& entry )
  {
    struct Parts
    {
      std::string name;
      std::string cid;
      std::string territory;
      std::string connected;
    } p;
    std::string::size_type dash1 = entry.find( " — " );
    std::string::size_type dash2 = std::string::npos;
    if( dash1 != std::string::npos )
      dash2 = entry.find( " — ", dash1 + 3 );

    std::string left = ( dash1 == std::string::npos ) ? entry : entry.substr( 0, dash1 );
    std::string mid = ( dash1 != std::string::npos && dash2 != std::string::npos )
                        ? entry.substr( dash1 + 3, dash2 - ( dash1 + 3 ) )
                        : std::string();
    std::string right = ( dash2 != std::string::npos ) ? entry.substr( dash2 + 3 ) : std::string();

    auto lpar = left.rfind( '(' );
    auto rpar = left.rfind( ')' );
    if( lpar != std::string::npos && rpar != std::string::npos && rpar > lpar )
    {
      p.name = left.substr( 0, lpar );
      while( !p.name.empty() && ( p.name.back() == ' ' || p.name.back() == '\t' ) ) p.name.pop_back();
      p.cid = left.substr( lpar + 1, rpar - lpar - 1 );
    }
    else
    {
      p.name = left;
    }
    p.territory = mid;
    p.connected = right;
    return p;
  };

  auto parts = parseEntry( m_selectedPlayerString );

  if( ImGui::Begin( "Player Details", &m_showPlayerDetails ) )
  {
    ImGui::Text( "Name: %s", parts.name.c_str() );
    ImGui::Text( "Character ID: %s", parts.cid.c_str() );
    ImGui::Text( "Territory: %s", parts.territory.c_str() );
    ImGui::Text( "%s", parts.connected.c_str() );

    ImGui::Separator();

    // Try to fetch live player object for richer details
    bool showedLive = false;
    do
    {
      if( parts.cid.empty() ) break;
      uint64_t cidNum = 0;
      try { cidNum = std::stoull( parts.cid ); } catch( ... ) { break; }

      std::lock_guard< std::mutex > lock( m_serverMutex );
      if( !m_pServer ) break;
      auto session = m_pServer->getSession( cidNum );
      if( !session ) break;
      auto player = session->getPlayer();
      if( !player ) break;

      // Basic combat and vitals
      const uint32_t hp = player->getHp();
      const uint32_t maxHp = player->getMaxHp();
      const uint32_t mp = player->getMp();
      const uint32_t maxMp = player->getMaxMp();
      const bool inCombat = player->isInCombat();
      ImGui::Text( "HP: %u / %u", hp, maxHp );
      ImGui::Text( "MP: %u / %u", mp, maxMp );
      ImGui::Text( "In Combat: %s", inCombat ? "Yes" : "No" );

      // Class/Job and Level
      const auto cj = player->getClass();
      const uint8_t level = player->getLevel();
      ImGui::Text( "Class/Job: %u", static_cast< unsigned >( cj ) );
      ImGui::SameLine();
      ImGui::Text( "Level: %u", static_cast< unsigned >( level ) );

      // Position
      const auto& pos = player->getPos();
      ImGui::Text( "Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z );

      // Misc
      ImGui::Text( "Play Time: %u min", static_cast< unsigned >( player->getPlayTime() / 60 ) );

      showedLive = true;
    } while( false );

    if( !showedLive )
    {
      ImGui::TextDisabled( "Live player details unavailable." );
    }

    ImGui::Separator();

    // Contextual actions could be added here later
    if( ImGui::Button( "Close" ) )
    {
      m_showPlayerDetails = false;
    }
  }
  ImGui::End();
}
