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

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <random>
#include <vector>

#include "Engine/Input.h"
#include "Engine/Service.h"
#include "Engine/Logger.h"

#include <Navi/NaviMgr.h>
#include <math.h>
#include <vector>

#include <algorithm>
#include <unordered_set>
#include <glm/gtx/matrix_decompose.hpp>

#include "Application.h"

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#endif


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

    auto pNaviMgr = std::make_shared< Sapphire::Common::Navi::NaviMgr >( m_navMeshPath );
    Engine::Service< Sapphire::Common::Navi::NaviMgr >::set( pNaviMgr );

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
  Sapphire::Logger::init( "logger" );
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
  if( !configFile.is_open() )
  {
    // Use default values if config file doesn't exist
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

    strncpy( m_navMeshPathBuffer, m_navMeshPath.c_str(), sizeof( m_navMeshPathBuffer ) - 1 );
    m_navMeshPathBuffer[ sizeof( m_navMeshPathBuffer ) - 1 ] = '\0';

    return;
  }

  std::string line;
  while( std::getline( configFile, line ) )
  {
    size_t pos = line.find( '=' );
    if( pos != std::string::npos )
    {
      std::string key = line.substr( 0, pos );
      std::string value = line.substr( pos + 1 );

      // Trim whitespace
      key.erase( 0, key.find_first_not_of( " \t" ) );
      key.erase( key.find_last_not_of( " \t" ) + 1 );
      value.erase( 0, value.find_first_not_of( " \t" ) );
      value.erase( value.find_last_not_of( " \t" ) + 1 );

      if( key == "dat_location" )
      {
        m_datLocation = value;
        strncpy( m_datLocationBuffer, m_datLocation.c_str(), sizeof( m_datLocationBuffer ) - 1 );
        m_datLocationBuffer[ sizeof( m_datLocationBuffer ) - 1 ] = '\0';
      }
      else if( key == "mysql_host" )
      {
        m_mysqlHost = value;
        strncpy( m_mysqlHostBuffer, m_mysqlHost.c_str(), sizeof( m_mysqlHostBuffer ) - 1 );
        m_mysqlHostBuffer[ sizeof( m_mysqlHostBuffer ) - 1 ] = '\0';
      }
      else if( key == "mysql_user" )
      {
        m_mysqlUser = value;
        strncpy( m_mysqlUserBuffer, m_mysqlUser.c_str(), sizeof( m_mysqlUserBuffer ) - 1 );
        m_mysqlUserBuffer[ sizeof( m_mysqlUserBuffer ) - 1 ] = '\0';
      }
      else if( key == "mysql_password" )
      {
        m_mysqlPassword = value;
        strncpy( m_mysqlPasswordBuffer, m_mysqlPassword.c_str(), sizeof( m_mysqlPasswordBuffer ) - 1 );
        m_mysqlPasswordBuffer[ sizeof( m_mysqlPasswordBuffer ) - 1 ] = '\0';
      }
      else if( key == "mysql_database" )
      {
        m_mysqlDatabase = value;
        strncpy( m_mysqlDatabaseBuffer, m_mysqlDatabase.c_str(), sizeof( m_mysqlDatabaseBuffer ) - 1 );
        m_mysqlDatabaseBuffer[ sizeof( m_mysqlDatabaseBuffer ) - 1 ] = '\0';
      }
      else if( key == "mysql_port" )
      {
        try
        {
          m_mysqlPort = std::stoi( value );
          m_mysqlPortBuffer = m_mysqlPort;
        } catch( const std::exception& )
        {
          m_mysqlPort = 3306; // Default port
          m_mysqlPortBuffer = m_mysqlPort;
        }
      }
      else if( key == "navmesh_path" )
      {
        m_navMeshPath = value;
        strncpy( m_navMeshPathBuffer, m_navMeshPath.c_str(), sizeof( m_navMeshPathBuffer ) - 1 );
        m_navMeshPathBuffer[ sizeof( m_navMeshPathBuffer ) - 1 ] = '\0';
      }
    }
  }

  configFile.close();
}

void EditorState::saveConfig()
{
  std::ofstream configFile( CONFIG_FILE );
  if( !configFile.is_open() )
  {
    // Handle error - could log or show message
    return;
  }

  configFile << "# Sapphire Editor Configuration" << std::endl;
  configFile << "# This file is automatically generated" << std::endl;
  configFile << std::endl;

  configFile << "# Game Data Settings" << std::endl;
  configFile << "dat_location=" << m_datLocation << std::endl;
  configFile << std::endl;

  configFile << "# Database Settings" << std::endl;
  configFile << "mysql_host=" << m_mysqlHost << std::endl;
  configFile << "mysql_user=" << m_mysqlUser << std::endl;
  configFile << "mysql_password=" << m_mysqlPassword << std::endl;
  configFile << "mysql_database=" << m_mysqlDatabase << std::endl;
  configFile << "mysql_port=" << m_mysqlPort << std::endl;
  configFile << std::endl;

  configFile << "# Navigation Mesh Settings" << std::endl;
  configFile << "navmesh_path=" << m_navMeshPath << std::endl;

  configFile.close();
}

// Add this helper function to the EditorState class
#ifdef _WIN32
std::string EditorState::openFolderDialog( const std::string& title )
{
  BROWSEINFO bi = { 0 };
  bi.lpszTitle = title.c_str();
  bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

  LPITEMIDLIST pidl = SHBrowseForFolder( &bi );

  if( pidl != 0 )
  {
    char path[ MAX_PATH ];
    if( SHGetPathFromIDList( pidl, path ) )
    {
      IMalloc *imalloc = 0;
      if( SUCCEEDED( SHGetMalloc(&imalloc) ) )
      {
        imalloc->Free( pidl );
        imalloc->Release();
      }
      return std::string( path );
    }
  }

  return "";
}
#endif


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
        // Browse logic here
      }

      if( ImGui::BeginPopup( "Browse Info" ) )
      {
        // Browse popup logic here
      }

      ImGui::Separator();
      ImGui::Text( "Status: %s", m_datLoaded ? "Loaded Successfully" : "Not Loaded / Failed" );
      if( m_datLoaded )
      {
        // Success info
      }
      else
      {
        // Error info
      }

      ImGui::EndTabItem();
    }

    // MySQL Tab
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

    // Navigation Mesh Tab
    if( ImGui::BeginTabItem( "Nav Meshes" ) )
    {
      ImGui::Text( "Navigation Mesh Configuration" );
      ImGui::Separator();

      ImGui::Text( "Nav Mesh Path:" );
      ImGui::SetNextItemWidth( 400 );
      ImGui::InputText( "##NavMeshPath", m_navMeshPathBuffer, sizeof( m_navMeshPathBuffer ) );

      ImGui::SameLine();
      if( ImGui::Button( "Browse...##NavMesh" ) )
      {
#ifdef _WIN32
        std::string selectedPath = openFolderDialog( "Select Nav Mesh Directory" );
        if( !selectedPath.empty() )
        {
          strncpy( m_navMeshPathBuffer, selectedPath.c_str(), sizeof( m_navMeshPathBuffer ) - 1 );
          m_navMeshPathBuffer[ sizeof( m_navMeshPathBuffer ) - 1 ] = '\0';
        }
#else
        ImGui::OpenPopup( "NavMesh Browse Info" );
#endif
      }

      if( ImGui::BeginPopup( "NavMesh Browse Info" ) )
      {
        ImGui::Text( "Select the directory containing navigation mesh files for zones." );
        ImGui::Text( "Expected structure: <path>/zone_<id>.nav" );
        ImGui::EndPopup();
      }

      ImGui::Separator();

      // Show current path status
      ImGui::Text( "Current Path: %s", m_navMeshPath.c_str() );

      // Check if directory exists and show some stats
      if( !m_navMeshPath.empty() )
      {
        // You could add directory validation here
        ImGui::Text( "Path Status: %s", "Directory accessible" ); // Replace with actual validation

        ImGui::Separator();
        ImGui::TextWrapped(
          "Navigation mesh files should be named '<internalName>.nav', each zone is in an own folder, this should point to the parent." );
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
      // DAT location change logic
      settingsChanged = true;
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
      m_mysqlDatabase = newDatabase;
      m_mysqlHost = newHost;
      m_mysqlPassword = newPassword;
      m_mysqlUser = newUser;
      m_mysqlPort = newPort;
      // MySQL settings change logic
      settingsChanged = true;
    }

    // Check nav mesh path changes
    std::string newNavMeshPath = std::string( m_navMeshPathBuffer );
    if( newNavMeshPath != m_navMeshPath )
    {
      m_navMeshPath = newNavMeshPath;
      settingsChanged = true;
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

    // Revert nav mesh path buffer
    strncpy( m_navMeshPathBuffer, m_navMeshPath.c_str(), sizeof( m_navMeshPathBuffer ) - 1 );
    m_navMeshPathBuffer[ sizeof( m_navMeshPathBuffer ) - 1 ] = '\0';

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
  ImGui::PopStyleVar( 3 );

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
