#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include <GameData.h>
#include <File.h>
#include <Exd/ExdData.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include "EditorState.h"

#include "Engine/GfxApi.h"
#include "Engine/ResourceManager.h"
#include "Engine/ShaderResource.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/IconsFontAwesome5.h"
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

using namespace Client;

Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;

EditorState::EditorState( std::shared_ptr< Engine::ApplicationContext > pContext ) :
  State( pContext )
{
}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
  Engine::Rendering::Graphics::setViewport( 0, 0, width, height );
}

bool EditorState::initGameData()
{
  auto exdData = std::make_shared< Sapphire::Data::ExdData >();
  if( !exdData->init( m_datLocation ) )
  {
    Engine::Logger::critical( "Error loading EXD data" );
  }
  else
  {
    m_datLoaded = true;
    auto gameData = std::make_shared< xiv::dat::GameData >( m_datLocation );
    Engine::Service< Sapphire::Data::ExdData >::set( exdData );
    Engine::Service< xiv::dat::GameData >::set( gameData );

    return true;
  }
  return false;
}

bool EditorState::initMySQLConnection()
{
  Sapphire::Db::DbLoader loader;
  Sapphire::Db::ConnectionInfo database;

  database.host = m_mysqlHost;
  database.user = m_mysqlUser;
  database.password = m_mysqlPassword;
  database.database = m_mysqlDatabase;
  database.port = m_mysqlPort;
  database.asyncThreads = 2;
  database.syncThreads = 2;

  loader.addDb( g_charaDb, database );
  if( !loader.initDbs() )
    return false;

  m_mysqlConnected = true;
  return true;

}

void EditorState::load()
{
  Sapphire::Logger::init( "api" );
  auto& graphics = Engine::Service< Engine::Rendering::Graphics >::ref();
  auto windowHeight = graphics.getWindowHeight();
  auto windowWidth = graphics.getWindowWidth();

  auto& resMgr = Engine::Service< Engine::Resources::ResourceManager >::ref();

  glfwSetFramebufferSizeCallback( graphics.getWindowHandle(), framebuffer_size_callback );

  auto& io = ImGui::GetIO();
  const ImGuiViewport *viewport = ImGui::GetMainViewport();

  Engine::Input::showMouseCursor();

  loadConfig(); // Load config first

  if( !initGameData() )
  {
    // Handle initialization failure
    Engine::Logger::warn( "Failed to initialize game data from: {}", m_datLocation );
  }
  else
  {
    m_zoneEditor.init();
  }

  if( !initMySQLConnection() )
  {
    // Handle initialization failure
    Engine::Logger::warn( "Failed to initialize MySQL connection" );
  }

}

void EditorState::update( double deltaTime )
{
}

void EditorState::loadConfig()
{
  std::ifstream configFile( CONFIG_FILE );
  if( configFile.is_open() )
  {
    std::string line;
    while( std::getline( configFile, line ) )
    {
      // Simple key=value parsing
      size_t equalPos = line.find( '=' );
      if( equalPos != std::string::npos )
      {
        std::string key = line.substr( 0, equalPos );
        std::string value = line.substr( equalPos + 1 );

        if( key == "dat_location" )
        {
          m_datLocation = value;
        }
        else if( key == "mysql_host" )
        {
          m_mysqlHost = value;
        }
        else if( key == "mysql_user" )
        {
          m_mysqlUser = value;
        }
        else if( key == "mysql_password" )
        {
          m_mysqlPassword = value;
        }
        else if( key == "mysql_database" )
        {
          m_mysqlDatabase = value;
        }
        else if( key == "mysql_port" )
        {
          m_mysqlPort = std::stoi( value );
        }
      }
    }
    configFile.close();
  }

  // Initialize input buffers
  strncpy( m_datLocationBuffer, m_datLocation.c_str(), sizeof( m_datLocationBuffer ) - 1 );
  m_datLocationBuffer[ sizeof( m_datLocationBuffer ) - 1 ] = '\0';

  strncpy( m_mysqlHostBuffer, m_mysqlHost.c_str(), sizeof( m_mysqlHostBuffer ) - 1 );
  m_mysqlHostBuffer[ sizeof( m_mysqlHostBuffer ) - 1 ] = '\0';

  strncpy( m_mysqlUserBuffer, m_mysqlUser.c_str(), sizeof( m_mysqlUserBuffer ) - 1 );
  m_mysqlUserBuffer[ sizeof( m_mysqlUserBuffer ) - 1 ] = '\0';

  strncpy( m_mysqlPasswordBuffer, m_mysqlPassword.c_str(), sizeof( m_mysqlPasswordBuffer ) - 1 );
  m_mysqlPasswordBuffer[ sizeof( m_mysqlPasswordBuffer ) - 1 ] = '\0';

  strncpy( m_mysqlDatabaseBuffer, m_mysqlDatabase.c_str(), sizeof( m_mysqlDatabaseBuffer ) - 1 );
  m_mysqlDatabaseBuffer[ sizeof( m_mysqlDatabaseBuffer ) - 1 ] = '\0';

  m_mysqlPortBuffer = m_mysqlPort;
}

void EditorState::saveConfig()
{
  std::ofstream configFile( CONFIG_FILE );
  if( configFile.is_open() )
  {
    configFile << "dat_location=" << m_datLocation << std::endl;
    configFile << "mysql_host=" << m_mysqlHost << std::endl;
    configFile << "mysql_user=" << m_mysqlUser << std::endl;
    configFile << "mysql_password=" << m_mysqlPassword << std::endl;
    configFile << "mysql_database=" << m_mysqlDatabase << std::endl;
    configFile << "mysql_port=" << m_mysqlPort << std::endl;
    configFile.close();
  }
}

void EditorState::showSettingsDialog()
{
  if( !m_showSettingsDialog ) return;

  ImGui::Begin( "Settings", &m_showSettingsDialog, ImGuiWindowFlags_AlwaysAutoResize );

  if( ImGui::BeginTabBar( "SettingsTabs" ) )
  {
    // Game Data Tab
    if( ImGui::BeginTabItem( "Game Data" ) )
    {
      ImGui::Text( "Game Data Configuration" );
      ImGui::Separator();

      ImGui::Text( "DAT Location:" );
      ImGui::SetNextItemWidth( 400 );
      ImGui::InputText( "##DatLocation", m_datLocationBuffer, sizeof( m_datLocationBuffer ) );

      ImGui::SameLine();
      if( ImGui::Button( "Browse..." ) )
      {
        ImGui::OpenPopup( "Browse Info" );
      }

      if( ImGui::BeginPopup( "Browse Info" ) )
      {
        ImGui::Text( "Please manually enter the path to your FFXIV sqpack folder" );
        ImGui::Text( "Example: C:\\Program Files (x86)\\SquareEnix\\FINAL FANTASY XIV - A Realm Reborn\\game\\sqpack" );
        if( ImGui::Button( "OK" ) )
        {
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }

      ImGui::Separator();
      ImGui::Text( "Status: %s", m_datLoaded ? "Loaded Successfully" : "Not Loaded / Failed" );
      if( m_datLoaded )
      {
        ImGui::TextColored( ImVec4( 0, 1, 0, 1 ), "Current Location: %s", m_datLocation.c_str() );
      }
      else
      {
        ImGui::TextColored( ImVec4( 1, 0, 0, 1 ), "Failed Location: %s", m_datLocation.c_str() );
      }

      ImGui::EndTabItem();
    }

    // MySQL Tab
    if( ImGui::BeginTabItem( "Database" ) )
    {
      ImGui::Text( "MySQL Connection Settings" );
      ImGui::Separator();

      ImGui::Text( "Host:" );
      ImGui::SetNextItemWidth( 200 );
      ImGui::InputText( "##MySQLHost", m_mysqlHostBuffer, sizeof( m_mysqlHostBuffer ) );

      ImGui::Text( "Port:" );
      ImGui::SetNextItemWidth( 100 );
      ImGui::InputInt( "##MySQLPort", &m_mysqlPortBuffer );

      ImGui::Text( "Username:" );
      ImGui::SetNextItemWidth( 200 );
      ImGui::InputText( "##MySQLUser", m_mysqlUserBuffer, sizeof( m_mysqlUserBuffer ) );

      ImGui::Text( "Password:" );
      ImGui::SetNextItemWidth( 200 );
      ImGui::InputText( "##MySQLPassword", m_mysqlPasswordBuffer, sizeof( m_mysqlPasswordBuffer ),
                        ImGuiInputTextFlags_Password );

      ImGui::Text( "Database:" );
      ImGui::SetNextItemWidth( 200 );
      ImGui::InputText( "##MySQLDatabase", m_mysqlDatabaseBuffer, sizeof( m_mysqlDatabaseBuffer ) );

      ImGui::Separator();

      if( ImGui::Button( "Test Connection" ) )
      {
        // Test MySQL connection here
        // You would implement testMySQLConnection() method
        // m_mysqlConnected = testMySQLConnection();
        ImGui::OpenPopup( "Connection Test" );
      }

      if( ImGui::BeginPopup( "Connection Test" ) )
      {
        if( m_mysqlConnected )
        {
          ImGui::TextColored( ImVec4( 0, 1, 0, 1 ), "Connection successful!" );
        }
        else
        {
          ImGui::TextColored( ImVec4( 1, 0, 0, 1 ), "Connection failed!" );
        }
        if( ImGui::Button( "Close" ) )
        {
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }

      ImGui::Text( "Connection Status: %s", m_mysqlConnected ? "Connected" : "Disconnected" );

      if( ImGui::Button( "Reset to Defaults" ) )
      {
        strcpy( m_mysqlHostBuffer, "localhost" );
        strcpy( m_mysqlUserBuffer, "root" );
        strcpy( m_mysqlPasswordBuffer, "" );
        strcpy( m_mysqlDatabaseBuffer, "sapphire" );
        m_mysqlPortBuffer = 3306;
      }

      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }

  ImGui::Separator();

  // Apply/Cancel buttons
  if( ImGui::Button( "Apply" ) )
  {
    bool settingsChanged = false;

    // Check DAT location changes
    std::string newDatLocation = std::string( m_datLocationBuffer );
    if( newDatLocation != m_datLocation )
    {
      m_datLocation = newDatLocation;
      settingsChanged = true;

      // Reinitialize game data
      if( initGameData() )
      {
        m_zoneEditor.refresh();
      }
    }

    // Check MySQL settings changes
    std::string newHost = std::string( m_mysqlHostBuffer );
    std::string newUser = std::string( m_mysqlUserBuffer );
    std::string newPassword = std::string( m_mysqlPasswordBuffer );
    std::string newDatabase = std::string( m_mysqlDatabaseBuffer );
    int newPort = m_mysqlPortBuffer;

    if( newHost != m_mysqlHost || newUser != m_mysqlUser ||
        newPassword != m_mysqlPassword || newDatabase != m_mysqlDatabase ||
        newPort != m_mysqlPort )
    {
      m_mysqlHost = newHost;
      m_mysqlUser = newUser;
      m_mysqlPassword = newPassword;
      m_mysqlDatabase = newDatabase;
      m_mysqlPort = newPort;
      settingsChanged = true;

      // Reinitialize MySQL connection here if needed
      initMySQLConnection();
    }

    if( settingsChanged )
    {
      saveConfig();
    }
  }

  ImGui::SameLine();
  if( ImGui::Button( "Cancel" ) )
  {
    // Revert all buffers to current values
    strncpy( m_datLocationBuffer, m_datLocation.c_str(), sizeof( m_datLocationBuffer ) - 1 );
    m_datLocationBuffer[ sizeof( m_datLocationBuffer ) - 1 ] = '\0';

    strncpy( m_mysqlHostBuffer, m_mysqlHost.c_str(), sizeof( m_mysqlHostBuffer ) - 1 );
    m_mysqlHostBuffer[ sizeof( m_mysqlHostBuffer ) - 1 ] = '\0';

    strncpy( m_mysqlUserBuffer, m_mysqlUser.c_str(), sizeof( m_mysqlUserBuffer ) - 1 );
    m_mysqlUserBuffer[ sizeof( m_mysqlUserBuffer ) - 1 ] = '\0';

    strncpy( m_mysqlPasswordBuffer, m_mysqlPassword.c_str(), sizeof( m_mysqlPasswordBuffer ) - 1 );
    m_mysqlPasswordBuffer[ sizeof( m_mysqlPasswordBuffer ) - 1 ] = '\0';

    strncpy( m_mysqlDatabaseBuffer, m_mysqlDatabase.c_str(), sizeof( m_mysqlDatabaseBuffer ) - 1 );
    m_mysqlDatabaseBuffer[ sizeof( m_mysqlDatabaseBuffer ) - 1 ] = '\0';

    m_mysqlPortBuffer = m_mysqlPort;

    m_showSettingsDialog = false;
  }

  ImGui::End();
}

void EditorState::renderMainMenu()
{
  if( ImGui::BeginMainMenuBar() )
  {
    if( ImGui::BeginMenu( "File" ) )
    {
      if( ImGui::MenuItem( "Settings" ) )
      {
        m_showSettingsDialog = true;
      }
      ImGui::Separator();

      if( ImGui::MenuItem( "Exit" ) )
      {
      }
      ImGui::EndMenu();
    }
    ImGui::Separator();
    if( ImGui::BeginMenu( "Tools" ) )
    {
      if( ImGui::MenuItem( "Zones" ) )
      {
        m_editorMode = EditorMode::ZONES;
      }

      ImGui::EndMenu();
    }


    ImGui::EndMainMenuBar();
  }
  // Show settings dialog if open
  showSettingsDialog();
}

bool dockInitialized = false;
void EditorState::render( double deltaTime )
{
  auto ident = Engine::mat4( 1.0f );

  Engine::Rendering::Graphics::clear( true, true, true );

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  auto p_open = true;
  auto& io = ImGui::GetIO();
  ImGuiID dockspace_id = setupDockspace( p_open, io );

  renderMainMenu();

  if( m_editorMode == EditorMode::NONE )
  {
  }
  if( m_editorMode == EditorMode::ZONES )
  {
    if( m_datLoaded )
      m_zoneEditor.show();

    if( !dockInitialized )
    {
      ImGui::DockBuilderAddNode( dockspace_id, ImGuiDockNodeFlags_None );
      unsigned int right_id;
      unsigned int right1_id;
      unsigned int left1_id;
      unsigned int left_id;

      ImGui::DockBuilderSplitNode( dockspace_id, ImGuiDir_Left, 0.2, &left_id, &right_id );
      ImGui::DockBuilderDockWindow( "Zone Editor", left_id );


      ImGui::DockBuilderSplitNode( right_id, ImGuiDir_Left, 0.6, &left1_id, &right1_id );
      ImGui::DockBuilderDockWindow( "BNPC Information", right1_id );
      ImGui::DockBuilderDockWindow( "Map Viewer", left1_id );
      dockInitialized = true;
    }


  }

  ImGui::End();

  static auto first_time = true;
  if( first_time )
  {
    first_time = false;
    //  setupDockingLayout( dockspace_id );
  }

  ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}


ImGuiID EditorState::setupDockspace( bool& p_open, ImGuiIO& io ) const
{
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
  const ImGuiViewport *viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos( viewport->Pos );
  ImGui::SetNextWindowSize( viewport->Size );
  ImGui::SetNextWindowViewport( viewport->ID );
  ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
  ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
  ImGui::Begin( "DockSpace", &p_open, window_flags );
  ImGui::PopStyleVar( 2 );

  ImGuiID dockspace_id = ImGui::GetID( "DockSpace" );
  //if( ImGui::DockBuilderGetNode( dockspace_id ) == NULL )
  {
    ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
  }
  ImGui::End();


  return dockspace_id;
}

void EditorState::unload()
{
}


void EditorState::handleInput( double deltaTime )
{
  Engine::Input::updateMousePosition();
  // if( m_modelViewActive )
  {
    //  updateCamera( deltaTime );
  }


  if( !Engine::Input::keyHeld( GLFW_KEY_LEFT_SHIFT ) )
  {
  }
}

void EditorState::reEnter()
{
  Engine::Input::showMouseCursor();
}
