#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include <datReaderPs3/GameData.h>
#include <datReaderPs3/File.h>
#include <datReaderPs3/DatCat.h>
#include <datReaderPs3/ExdData.h>
#include <datReaderPs3/ExdCat.h>
#include <datReaderPs3/Exd.h>
#include <datReaderPs3/Exh.h>
#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <datReaderPs3/Exd/Structs.h>

#include "ServerState.h"

#include "Engine/GfxApi.h"
#include "Engine/ResourceManager.h"
#include "Engine/ShaderResource.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <random>
#include <vector>

#include "Engine/Input.h"
#include "Engine/Service.h"
#include "Engine/Logger.h"

#include <Navi/NaviMgr.h>
#include <Config/ConfigMgr.h>
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

#include "commonshader.h"

using namespace Client;

Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;

ServerState::ServerState( std::shared_ptr< Engine::ApplicationContext > pContext ) : State( pContext )
{
  // Load config defaults from the server config
  auto executableDir = Sapphire::Common::Util::executableDir();
  m_configFile = executableDir / "editor_config_ps3.txt";
  auto serverDir = executableDir.parent_path();
  Sapphire::Common::ConfigMgr configMgr( serverDir / "config" );
  Sapphire::Common::Config::GlobalConfig globalConfig;
  if( configMgr.loadGlobalConfig( globalConfig ) )
  {
    m_datLocation = globalConfig.general.dataPath;
    m_mysqlHost = globalConfig.database.host;
    m_mysqlUser = globalConfig.database.user;
    m_mysqlPassword = globalConfig.database.password;
    m_mysqlDatabase = globalConfig.database.database;
    m_mysqlPort = globalConfig.database.port;
    m_navMeshPath = configMgr.getValue( "Navigation", "MeshPath", ( serverDir / "navi" ).string() );
  }
}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
  Engine::Rendering::Graphics::setViewport( 0, 0, width, height );
}

bool ServerState::initGameData()
{
  auto exdData = std::make_shared< Data::ExdData >();
  if( !exdData->init( m_datLocation ) )
  {
    Engine::Logger::critical( "Error loading EXD data" );
  }
  else
  {
    m_datLoaded = true;
    auto gameData = std::make_shared< xivps3::dat::GameData >( m_datLocation );
    Engine::Service< Data::ExdData >::set( exdData );
    Engine::Service< xivps3::dat::GameData >::set( gameData );

    auto pNaviMgr = std::make_shared< Sapphire::Common::Navi::NaviMgr >( m_navMeshPath );
    Engine::Service< Sapphire::Common::Navi::NaviMgr >::set( pNaviMgr );

    return true;
  }
  return false;
}

bool ServerState::initMySQLConnection()
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

void ServerState::load()
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
    m_lgbViewer.init();
  }

  if( !initMySQLConnection() )
  {
    // Handle initialization failure
    Engine::Logger::warn( "Failed to initialize MySQL connection" );
  }
}

void ServerState::update( double deltaTime )
{
}

void ServerState::loadConfig()
{
  std::ifstream configFile( m_configFile );
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

void ServerState::saveConfig()
{
  std::ofstream configFile( m_configFile );
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
std::string ServerState::openFolderDialog( const std::string& title )
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

void ServerState::showSettingsDialog()
{
    if (!m_showSettingsDialog) return;

    ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings", &m_showSettingsDialog, ImGuiWindowFlags_NoCollapse);

    static bool hasUnsavedChanges = false;
    static bool showConfirmDialog = false;

    if (ImGui::BeginTabBar("SettingsTabs", ImGuiTabBarFlags_None))
    {
        // Game Data Tab
        if (ImGui::BeginTabItem("Game Data"))
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
            ImGui::TextWrapped("Configure the path to your FFXIV game data files (sqpack folder).");
            ImGui::PopStyleColor();
            ImGui::Separator();

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Game Data Path:");
            ImGui::SetNextItemWidth(-120.0f);
            if (ImGui::InputText("##DatLocation", m_datLocationBuffer, sizeof(m_datLocationBuffer)))
            {
                hasUnsavedChanges = true;
            }

            ImGui::SameLine();
            if (ImGui::Button("Browse...##GameData"))
            {
#ifdef _WIN32
                std::string selectedPath = openFolderDialog("Select Game Data Directory (containing 'sqpack' folder)");
                if (!selectedPath.empty())
                {
                    strncpy(m_datLocationBuffer, selectedPath.c_str(), sizeof(m_datLocationBuffer) - 1);
                    m_datLocationBuffer[sizeof(m_datLocationBuffer) - 1] = '\0';
                    hasUnsavedChanges = true;
                }
#endif
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            // Status display
            if (m_datLoaded)
            {
                ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "✓ Status: Loaded Successfully");
                ImGui::TextWrapped("Current path: %s", m_datLocation.c_str());
            }
            else
            {
                ImGui::TextColored(ImVec4(0.8f, 0.2f, 0.2f, 1.0f), "✗ Status: Not Loaded or Failed");
                if (!m_datLocation.empty())
                {
                    ImGui::TextWrapped("Failed to load from: %s", m_datLocation.c_str());
                    ImGui::TextColored(ImVec4(0.8f, 0.6f, 0.2f, 1.0f), "Make sure the path contains the 'sqpack' folder.");
                }
            }

            ImGui::Spacing();
            if (ImGui::Button("Reload Game Data"))
            {
                m_datLocation = std::string(m_datLocationBuffer);
                initGameData();
            }

            ImGui::EndTabItem();
        }

        // Database Tab
        if (ImGui::BeginTabItem("Database"))
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
            ImGui::TextWrapped("Configure MySQL database connection settings.");
            ImGui::PopStyleColor();
            ImGui::Separator();

            ImGui::Columns(2, "DatabaseColumns", false);
            ImGui::SetColumnWidth(0, 120);

            // Host
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Host:");
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1.0f);
            if (ImGui::InputText("##MySQLHost", m_mysqlHostBuffer, sizeof(m_mysqlHostBuffer)))
            {
                hasUnsavedChanges = true;
            }
            ImGui::NextColumn();

            // Port
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Port:");
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1.0f);
            if (ImGui::InputInt("##MySQLPort", &m_mysqlPortBuffer))
            {
                hasUnsavedChanges = true;
                // Clamp port to valid range
                if (m_mysqlPortBuffer < 1) m_mysqlPortBuffer = 1;
                if (m_mysqlPortBuffer > 65535) m_mysqlPortBuffer = 65535;
            }
            ImGui::NextColumn();

            // Username
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Username:");
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1.0f);
            if (ImGui::InputText("##MySQLUser", m_mysqlUserBuffer, sizeof(m_mysqlUserBuffer)))
            {
                hasUnsavedChanges = true;
            }
            ImGui::NextColumn();

            // Password
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Password:");
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1.0f);
            if (ImGui::InputText("##MySQLPassword", m_mysqlPasswordBuffer, sizeof(m_mysqlPasswordBuffer),
                               ImGuiInputTextFlags_Password))
            {
                hasUnsavedChanges = true;
            }
            ImGui::NextColumn();

            // Database
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Database:");
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1.0f);
            if (ImGui::InputText("##MySQLDatabase", m_mysqlDatabaseBuffer, sizeof(m_mysqlDatabaseBuffer)))
            {
                hasUnsavedChanges = true;
            }

            ImGui::Columns(1);
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            // Connection test and status
            if (ImGui::Button("Test Connection"))
            {
                // Store current values
                std::string tempHost = m_mysqlHost;
                std::string tempUser = m_mysqlUser;
                std::string tempPassword = m_mysqlPassword;
                std::string tempDatabase = m_mysqlDatabase;
                int tempPort = m_mysqlPort;

                // Apply test values
                m_mysqlHost = std::string(m_mysqlHostBuffer);
                m_mysqlUser = std::string(m_mysqlUserBuffer);
                m_mysqlPassword = std::string(m_mysqlPasswordBuffer);
                m_mysqlDatabase = std::string(m_mysqlDatabaseBuffer);
                m_mysqlPort = m_mysqlPortBuffer;

                bool testResult = initMySQLConnection();

                // Restore original values
                m_mysqlHost = tempHost;
                m_mysqlUser = tempUser;
                m_mysqlPassword = tempPassword;
                m_mysqlDatabase = tempDatabase;
                m_mysqlPort = tempPort;

                // Show result
                ImGui::OpenPopup("Connection Test Result");
            }

            // Connection test popup
            if (ImGui::BeginPopupModal("Connection Test Result", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
            {
                if (m_mysqlConnected)
                {
                    ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "✓ Connection successful!");
                }
                else
                {
                    ImGui::TextColored(ImVec4(0.8f, 0.2f, 0.2f, 1.0f), "✗ Connection failed!");
                    ImGui::TextWrapped("Please check your connection settings and ensure the MySQL server is running.");
                }

                ImGui::Spacing();
                if (ImGui::Button("Close"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Reset to Defaults"))
            {
                strcpy(m_mysqlHostBuffer, "localhost");
                strcpy(m_mysqlUserBuffer, "root");
                strcpy(m_mysqlPasswordBuffer, "");
                strcpy(m_mysqlDatabaseBuffer, "sapphire");
                m_mysqlPortBuffer = 3306;
                hasUnsavedChanges = true;
            }

            ImGui::Spacing();
            // Status display
            if (m_mysqlConnected)
            {
                ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "✓ Status: Connected");
                ImGui::TextWrapped("Connected to: %s@%s:%d/%s", m_mysqlUser.c_str(), m_mysqlHost.c_str(), m_mysqlPort, m_mysqlDatabase.c_str());
            }
            else
            {
                ImGui::TextColored(ImVec4(0.8f, 0.2f, 0.2f, 1.0f), "✗ Status: Disconnected");
            }

            ImGui::EndTabItem();
        }

        // Navigation Mesh Tab
        if (ImGui::BeginTabItem("Navigation"))
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
            ImGui::TextWrapped("Configure the path to navigation mesh files used for pathfinding.");
            ImGui::PopStyleColor();
            ImGui::Separator();

            ImGui::AlignTextToFramePadding();
            ImGui::Text("NavMesh Path:");
            ImGui::SetNextItemWidth(-120.0f);
            if (ImGui::InputText("##NavMeshPath", m_navMeshPathBuffer, sizeof(m_navMeshPathBuffer)))
            {
                hasUnsavedChanges = true;
            }

            ImGui::SameLine();
            if (ImGui::Button("Browse...##NavMesh"))
            {
#ifdef _WIN32
                std::string selectedPath = openFolderDialog("Select Navigation Mesh Directory");
                if (!selectedPath.empty())
                {
                    strncpy(m_navMeshPathBuffer, selectedPath.c_str(), sizeof(m_navMeshPathBuffer) - 1);
                    m_navMeshPathBuffer[sizeof(m_navMeshPathBuffer) - 1] = '\0';
                    hasUnsavedChanges = true;
                }
#else
                ImGui::OpenPopup("NavMesh Browse Help");
#endif
            }

            if (ImGui::BeginPopup("NavMesh Browse Help"))
            {
                ImGui::TextWrapped("Please manually enter the path to the directory containing navigation mesh files.");
                ImGui::TextWrapped("Expected structure: <path>/<zone_internal_name>/<zone_internal_name>.nav");
                ImGui::EndPopup();
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            // Path information
            ImGui::TextWrapped("Current Path: %s", m_navMeshPath.c_str());

            if (!m_navMeshPath.empty())
            {
                // You could add directory validation here
                ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "✓ Path configured");

                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.6f, 0.6f, 1.0f, 1.0f), "File Structure:");
                ImGui::BulletText("Each zone should have its own folder");
                ImGui::BulletText("Navigation files should be named '<internal_name>.nav'");
                ImGui::BulletText("This path should point to the parent directory");
            }
            else
            {
                ImGui::TextColored(ImVec4(0.8f, 0.6f, 0.2f, 1.0f), "⚠ No path configured");
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::Separator();
    ImGui::Spacing();

    // Unsaved changes indicator
    if (hasUnsavedChanges)
    {
        ImGui::TextColored(ImVec4(1.0f, 0.6f, 0.2f, 1.0f), "⚠ You have unsaved changes");
        ImGui::Spacing();
    }

    // Bottom buttons
    ImGui::BeginGroup();
    if (ImGui::Button("Apply Settings", ImVec2(120, 0)))
    {
        // Apply all changes
        bool needsRestart = false;

        // Check and apply DAT location changes
        std::string newDatLocation = std::string(m_datLocationBuffer);
        if (newDatLocation != m_datLocation)
        {
            m_datLocation = newDatLocation;
            needsRestart = true;
        }

        // Check and apply MySQL settings changes
        std::string newHost = std::string(m_mysqlHostBuffer);
        std::string newUser = std::string(m_mysqlUserBuffer);
        std::string newPassword = std::string(m_mysqlPasswordBuffer);
        std::string newDatabase = std::string(m_mysqlDatabaseBuffer);
        int newPort = m_mysqlPortBuffer;

        if (newHost != m_mysqlHost || newUser != m_mysqlUser ||
            newPassword != m_mysqlPassword || newDatabase != m_mysqlDatabase ||
            newPort != m_mysqlPort)
        {
            m_mysqlHost = newHost;
            m_mysqlUser = newUser;
            m_mysqlPassword = newPassword;
            m_mysqlDatabase = newDatabase;
            m_mysqlPort = newPort;
            needsRestart = true;
        }

        // Check and apply nav mesh path changes
        std::string newNavMeshPath = std::string(m_navMeshPathBuffer);
        if (newNavMeshPath != m_navMeshPath)
        {
            m_navMeshPath = newNavMeshPath;
            needsRestart = true;
        }

        if (needsRestart)
        {
            saveConfig();
            hasUnsavedChanges = false;
            ImGui::OpenPopup("Settings Applied");
        }
        else
        {
            hasUnsavedChanges = false;
        }
    }

    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0)))
    {
        if (hasUnsavedChanges)
        {
            showConfirmDialog = true;
            ImGui::OpenPopup("Discard Changes?");
        }
        else
        {
            m_showSettingsDialog = false;
        }
    }

    ImGui::SameLine();
    ImGui::Dummy(ImVec2(10, 0));
    ImGui::SameLine();

    if (ImGui::Button("Restore Defaults", ImVec2(120, 0)))
    {
        ImGui::OpenPopup("Restore Defaults?");
    }
    ImGui::EndGroup();

    // Confirmation dialogs
    if (ImGui::BeginPopupModal("Settings Applied", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "✓ Settings have been saved successfully!");
        ImGui::TextWrapped("Some changes may require restarting the application to take effect.");
        ImGui::Spacing();
        if (ImGui::Button("OK"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Discard Changes?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("You have unsaved changes. Are you sure you want to discard them?");
        ImGui::Spacing();
        if (ImGui::Button("Yes, Discard"))
        {
            // Revert all buffers to current values
            revertSettingsBuffers();
            hasUnsavedChanges = false;
            m_showSettingsDialog = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Restore Defaults?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("This will reset all settings to their default values.");
        ImGui::Text("Are you sure you want to continue?");
        ImGui::Spacing();
        if (ImGui::Button("Yes, Restore Defaults"))
        {
            restoreDefaultSettings();
            hasUnsavedChanges = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

// Helper method to revert settings buffers
void ServerState::revertSettingsBuffers()
{
    strncpy(m_datLocationBuffer, m_datLocation.c_str(), sizeof(m_datLocationBuffer) - 1);
    m_datLocationBuffer[sizeof(m_datLocationBuffer) - 1] = '\0';

    strncpy(m_mysqlHostBuffer, m_mysqlHost.c_str(), sizeof(m_mysqlHostBuffer) - 1);
    m_mysqlHostBuffer[sizeof(m_mysqlHostBuffer) - 1] = '\0';

    strncpy(m_mysqlUserBuffer, m_mysqlUser.c_str(), sizeof(m_mysqlUserBuffer) - 1);
    m_mysqlUserBuffer[sizeof(m_mysqlUserBuffer) - 1] = '\0';

    strncpy(m_mysqlPasswordBuffer, m_mysqlPassword.c_str(), sizeof(m_mysqlPasswordBuffer) - 1);
    m_mysqlPasswordBuffer[sizeof(m_mysqlPasswordBuffer) - 1] = '\0';

    strncpy(m_mysqlDatabaseBuffer, m_mysqlDatabase.c_str(), sizeof(m_mysqlDatabaseBuffer) - 1);
    m_mysqlDatabaseBuffer[sizeof(m_mysqlDatabaseBuffer) - 1] = '\0';

    m_mysqlPortBuffer = m_mysqlPort;

    strncpy(m_navMeshPathBuffer, m_navMeshPath.c_str(), sizeof(m_navMeshPathBuffer) - 1);
    m_navMeshPathBuffer[sizeof(m_navMeshPathBuffer) - 1] = '\0';
}

// Helper method to restore default settings
void ServerState::restoreDefaultSettings()
{
    // Game Data defaults
    strcpy(m_datLocationBuffer, "");

    // MySQL defaults
    strcpy(m_mysqlHostBuffer, "localhost");
    strcpy(m_mysqlUserBuffer, "root");
    strcpy(m_mysqlPasswordBuffer, "");
    strcpy(m_mysqlDatabaseBuffer, "sapphire");
    m_mysqlPortBuffer = 3306;

    // Navigation defaults
    strcpy(m_navMeshPathBuffer, "navi");
}

void ServerState::renderMainMenu()
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
      if( ImGui::MenuItem( "Lgb" ) )
      {
        m_editorMode = EditorMode::LGB;
      }

      ImGui::EndMenu();
    }


    ImGui::EndMainMenuBar();
  }
  // Show settings dialog if open
  showSettingsDialog();
}

bool dockInitialized = false;

void ServerState::render( double deltaTime )
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

  }
  else if( m_editorMode == EditorMode::LGB )
  {
    if( m_datLoaded )
      m_lgbViewer.show();
  }

  if( !dockInitialized )
  {
    ImGui::DockBuilderAddNode( dockspace_id, ImGuiDockNodeFlags_None );
    unsigned int right_id;
    unsigned int right1_id;
    unsigned int left1_id;
    unsigned int left_id;

    ImGui::DockBuilderSplitNode( dockspace_id, ImGuiDir_Left, 0.2, &left_id, &right_id );
    ImGui::DockBuilderDockWindow( "Zone Editor", left_id );
    ImGui::DockBuilderDockWindow( "Lgb Viewer", left_id );


    ImGui::DockBuilderSplitNode( right_id, ImGuiDir_Left, 0.6, &left1_id, &right1_id );
    ImGui::DockBuilderDockWindow( "Navmesh Viewer", left1_id );

    unsigned int top_id;
    unsigned int down_id;

    ImGui::DockBuilderSplitNode( right1_id, ImGuiDir_Down, 0.6, &top_id, &down_id );
    ImGui::DockBuilderDockWindow( "Map Viewer", down_id );
    ImGui::DockBuilderDockWindow( "BNPC Information", top_id );
    ImGui::DockBuilderDockWindow( "LGB Groups", top_id );


    dockInitialized = true;
  }

  ImGui::End();

  static auto first_time = true;
  if( first_time )
  {
    first_time = false;
    //  setupDockingLayout( dockspace_id );
  }
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
}


ImGuiID ServerState::setupDockspace( bool& p_open, ImGuiIO& io ) const
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



  return dockspace_id;
}

void ServerState::unload()
{
}


void ServerState::handleInput( double deltaTime )
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

void ServerState::reEnter()
{
  Engine::Input::showMouseCursor();
}
