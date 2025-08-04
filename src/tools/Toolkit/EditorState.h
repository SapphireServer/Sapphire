#pragma once

#include <memory>
#include <vector>

#include "Engine/State.h"

#include "imgui/imgui.h"
#include <GameData.h>
#include <File.h>
#include <Exd/ExdData.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>
#include <Exh.h>

#include <ZoneEditor.h>

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
    void load() override;
    void unload() override;
    void handleInput( double deltaTime ) override;
    void reEnter() override;

  private:
    void onZoneSelectionChanged(uint32_t zoneId, const std::shared_ptr<Excel::ExcelStruct<Excel::TerritoryType>>& zoneInfo);
    void onZoneSelectionCleared();
    bool m_datLoaded{false};

    enum EditorMode
    {
      NONE,
      ZONES,
    } m_editorMode{ZONES};

    std::string m_datLocation{"F:\\client3.3\\game\\sqpack"};
    ImGuiID setupDockspace( bool& p_open, ImGuiIO& io ) const;

    ZoneEditor m_zoneEditor;


  };
}

