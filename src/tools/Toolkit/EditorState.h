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

#include <ZoneEditor.h>
#include <LgbViewer.h>

namespace Client
{
  class EditorState : public Engine::State, public std::enable_shared_from_this< EditorState >
  {
  public:
    EditorState( std::shared_ptr< Engine::ApplicationContext > pContext );

    ~EditorState() = default;

    void update( double deltaTime ) override;

    void showZoneEditor();

    void render( double deltaTime ) override;

    bool initGameData();

    bool initMySQLConnection();

    void load() override;

    void unload() override;

    void handleInput( double deltaTime ) override;

    void reEnter() override;

    void renderMainMenu();

  private:
    void onZoneSelectionChanged( uint32_t zoneId,
                                 const std::shared_ptr< Excel::ExcelStruct< Excel::TerritoryType > >& zoneInfo );

    void onZoneSelectionCleared();

    bool m_datLoaded{ false };

    void loadConfig();

    void saveConfig();

    void showSettingsDialog();
    void restoreDefaultSettings();
    void revertSettingsBuffers();

#ifdef _WIN32
    std::string openFolderDialog( const std::string& title );
#endif

    // Add these members
    bool m_showSettingsDialog = false;
    char m_datLocationBuffer[ 512 ]; // Buffer for ImGui input
    std::filesystem::path m_configFile;

    enum EditorMode
    {
      NONE,
      ZONES,
      LGB,
    } m_editorMode{ ZONES };

    std::string m_datLocation{ "F:\\client3.3\\game\\sqpack" };

    ImGuiID setupDockspace( bool& p_open, ImGuiIO& io ) const;

    ZoneEditor m_zoneEditor;
    LgbViewer m_lgbViewer;

    std::string m_mysqlHost{ "localhost" };
    std::string m_mysqlUser{ "root" };
    std::string m_mysqlPassword{ "" };
    std::string m_mysqlDatabase{ "sapphire" };
    int m_mysqlPort{ 3306 };

    char m_mysqlHostBuffer[ 256 ];
    char m_mysqlUserBuffer[ 256 ];
    char m_mysqlPasswordBuffer[ 256 ];
    char m_mysqlDatabaseBuffer[ 256 ];
    int m_mysqlPortBuffer;
    bool m_mysqlConnected = false;

    // Navigation mesh configuration
    std::string m_navMeshPath{ "./navmesh" };
    char m_navMeshPathBuffer[ 512 ];
  };
}
