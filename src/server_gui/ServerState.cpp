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

ServerState::ServerState( std::shared_ptr< Engine::ApplicationContext > pContext ) : State( pContext )
{

}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
  Engine::Rendering::Graphics::setViewport( 0, 0, width, height );
}

void ServerState::load()
{
  auto& graphics = Engine::Service< Engine::Rendering::Graphics >::ref();
  auto windowHeight = graphics.getWindowHeight();
  auto windowWidth = graphics.getWindowWidth();

  auto& resMgr = Engine::Service< Engine::Resources::ResourceManager >::ref();

  glfwSetFramebufferSizeCallback( graphics.getWindowHandle(), framebuffer_size_callback );

  auto& io = ImGui::GetIO();
  const ImGuiViewport *viewport = ImGui::GetMainViewport();

  Engine::Input::showMouseCursor();

  m_serverGUI.init();


}

void ServerState::update( double deltaTime )
{
}

void ServerState::renderMainMenu()
{
  if( ImGui::BeginMainMenuBar() )
  {
    if( ImGui::BeginMenu( "File" ) )
    {

      if( ImGui::MenuItem( "Exit" ) )
      {
      }
      ImGui::EndMenu();
    }
    ImGui::Separator();


    ImGui::EndMainMenuBar();
  }
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

  m_serverGUI.show();

  if( !dockInitialized )
  {
    ImGui::DockBuilderAddNode( dockspace_id, ImGuiDockNodeFlags_None );

    unsigned int top_id;
    unsigned int down_id;
    ImGui::DockBuilderSplitNode( dockspace_id, ImGuiDir_Down, 0.9, &down_id, &top_id );
    ImGui::DockBuilderDockWindow( "Server Control", top_id );

    unsigned int left_id;
    unsigned int right_id;
    ImGui::DockBuilderSplitNode( down_id, ImGuiDir_Left, 0.7, &left_id, &right_id );
    ImGui::DockBuilderDockWindow( "Console", left_id );
    ImGui::DockBuilderDockWindow( "Players", right_id );

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
