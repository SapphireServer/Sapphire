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

EditorState::EditorState( std::shared_ptr< Engine::ApplicationContext > pContext ) :
  State( pContext )
{
}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
  Engine::Rendering::Graphics::setViewport( 0, 0, width, height );
}

void EditorState::load()
{
  auto& graphics = Engine::Service< Engine::Rendering::Graphics >::ref();
  auto windowHeight = graphics.getWindowHeight();
  auto windowWidth = graphics.getWindowWidth();

  auto& resMgr = Engine::Service< Engine::Resources::ResourceManager >::ref();

  glfwSetFramebufferSizeCallback( graphics.getWindowHandle(), framebuffer_size_callback );

  auto& io = ImGui::GetIO();
  const ImGuiViewport *viewport = ImGui::GetMainViewport();

  Engine::Input::showMouseCursor();

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
    m_zoneEditor.init();
  }



}

void EditorState::update( double deltaTime )
{
}


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

  if( m_editorMode == EditorMode::NONE )
  {

  }
  if( m_editorMode == EditorMode::ZONES )
  {
    m_zoneEditor.show();
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
