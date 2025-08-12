#include "Application.h"

#include <Engine/GfxApi.h>

#include <Engine/Input.h>


#include "Engine/ResourceManager.h"


#include <chrono>
#include <Engine/Service.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <utility>

#include "EditorState.h"


const char *sourceToString( GLenum source )
{
  switch( source )
  {
    case GL_DEBUG_SOURCE_API:
      return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      return "Window System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      return "Third Party";
    case GL_DEBUG_SOURCE_APPLICATION:
      return "Application";
    case GL_DEBUG_SOURCE_OTHER:
      return "Other";
    default:
      return "Unknown";
  }
}

const char *typeToString( GLenum type )
{
  switch( type )
  {
    case GL_DEBUG_TYPE_ERROR:
      return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      return "Deprecated Behavior";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      return "Undefined Behavior";
    case GL_DEBUG_TYPE_PORTABILITY:
      return "Portability Issue";
    case GL_DEBUG_TYPE_PERFORMANCE:
      return "Performance Issue";
    case GL_DEBUG_TYPE_MARKER:
      return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP:
      return "Push Group";
    case GL_DEBUG_TYPE_POP_GROUP:
      return "Pop Group";
    case GL_DEBUG_TYPE_OTHER:
      return "Other";
    default:
      return "Unknown";
  }
}

const char *severityToString( GLenum severity )
{
  switch( severity )
  {
    case GL_DEBUG_SEVERITY_HIGH:
      return "High";
    case GL_DEBUG_SEVERITY_MEDIUM:
      return "Medium";
    case GL_DEBUG_SEVERITY_LOW:
      return "Low";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      return "Notification";
    default:
      return "Unknown";
  }
}

void APIENTRY MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam )
{

  auto msg = fmt::format(
          "GL DEBUG MESSAGE:\n"
          " Source: {}\n"
          " Type: {}\n"
          " ID: {}\n"
          " Severity: {}\n"
          " Message: {}",
          sourceToString( source ), typeToString( type ), id, severityToString( severity ), message );

  if( severity == GL_DEBUG_SEVERITY_NOTIFICATION  )
  {
    Engine::Logger::info( msg );
  }
  else
    Engine::Logger::error( msg );
}

Engine::Application::Application( const std::string& name ) :
        m_applicationName( name ),
        m_exiting( false ),
        m_bShowMouse( false ),
        m_lastRenderTick( 0 ),
        m_lastUpdateTick( 0 ),
        m_updateTimeStep( 1.f / 120.f )
{
  m_context = std::make_shared< ApplicationContext >();



  m_fullscreen = false;
  m_resX = 1920;
  m_resY = 1080;
  auto now = std::chrono::steady_clock::now();
  m_lastRenderTick = std::chrono::time_point_cast< std::chrono::milliseconds >( now ).time_since_epoch().count();
  m_lastUpdateTick = std::chrono::time_point_cast< std::chrono::milliseconds >( now ).time_since_epoch().count();
}

void Engine::Application::exitApplication()
{
  m_context->pGraphics->terminate();
}

void Engine::Application::setExiting( bool exiting )
{
  m_exiting = exiting;
}

bool Engine::Application::init()
{
  using namespace Engine::Rendering;

  m_context->pGraphics = std::make_shared< Graphics >();
  auto glsl_version = m_context->pGraphics->init( m_applicationName, m_resX, m_resY, m_fullscreen, !m_fullscreen ? true : false );
  Engine::Service< Graphics >::set( m_context->pGraphics );

  auto device = m_context->pGraphics->getDeviceString();
  Engine::Logger::info( "{}", device );

 // Engine::Rendering::Graphics::enable( EnableAttribute::DebugOutput );
 // glDebugMessageCallback( MessageCallback, nullptr );

  if( !Engine::Input::init( m_context->pGraphics->getWindowHandle() ) )
  {
    Engine::Logger::critical( "Error initializing input system" );
    //return false;
  }

  Graphics::enable( EnableAttribute::DepthTest );
  Graphics::setDepthFunc( DepthFunc::Less );
  Graphics::enable( EnableAttribute::CullFace );
  Graphics::setCullMode( CullMode::Back );
  Graphics::setCullOrder( CullOrder::CounterClockWise );


  m_context->pRessourceMgr = std::make_shared< Engine::Resources::ResourceManager >();
  Engine::Service< Engine::Resources::ResourceManager >::set( m_context->pRessourceMgr );

  m_context->pStateStack = std::make_shared< Engine::State::StateStack >();


  onInit();
  initImGui( glsl_version );
  initStates();

  return true;
}

void Engine::Application::initStates()
{
  onInitStates();
  auto menuState = std::make_shared< Client::EditorState >( m_context );
  menuState->load();
  m_context->pStateStack->push( menuState );
}

void Engine::Application::pushState( Engine::StatePtr state )
{
  m_context->pStateStack->push( state );
}

Engine::State::StateStackPtr Engine::Application::getStateStack()
{
  return m_context->pStateStack;
}

void Engine::Application::resetTimers()
{
  auto now = std::chrono::steady_clock::now();
  m_lastRenderTick = std::chrono::time_point_cast< std::chrono::milliseconds >( now ).time_since_epoch().count();
  m_lastUpdateTick = std::chrono::time_point_cast< std::chrono::milliseconds >( now ).time_since_epoch().count();
}

void Engine::Application::mainLoop()
{
  bool exit = false;
  resetTimers();
  while( !exit && !m_exiting && !m_context->pGraphics->shouldWindowClose() )
  {

    onMainLoop();


    onGameStep();
    updateState();

    auto dt = calculateDeltaTime( m_lastRenderTick );

    handleInput( dt );

    render( dt );

  }
  onDeInit();
  exitApplication();
}

void Engine::Application::replaceTopState( Engine::StatePtr state )
{
  m_context->pStateStack->top()->unload();
  m_context->pStateStack->pop();
  pushState( std::move( state ) );
}


void Engine::Application::handleInput( double deltaTime )
{
  Input::poll();
  auto editorEnabled = m_bShowMouse;
  if( Engine::Input::keyDown( GLFW_KEY_Q ) )
  {
    Engine::Input::resetMousePosition();
    m_bShowMouse = !m_bShowMouse;

    if( editorEnabled )
    {
      Engine::Input::hideMouseCursor();
    }
    else
    {
      Engine::Input::showMouseCursor();
    }
  }

  if( m_context->pGraphics->isWindowFocused() )
  {
    if( !m_context->pStateStack->empty() )
    {
      m_context->pStateStack->top()->handleInput( deltaTime );
    }
  }
  Input::nextFrame();
}

void Engine::Application::render( double dt )
{
  using namespace Engine::Rendering;
  Graphics::disable( EnableAttribute::Blend );

  if( !m_context->pStateStack->empty() )
  {
    m_context->pStateStack->top()->render( dt );
  }

  onRender();

  Graphics::enable( EnableAttribute::Blend );
  Graphics::enable( EnableAttribute::DepthTest );
  Graphics::setDepthFunc( DepthFunc::Lequal );

  if( !m_context->pStateStack->empty() )
  {
    Graphics::disable( EnableAttribute::Blend );
    Graphics::disable( EnableAttribute::DepthTest );
    m_context->pStateStack->top()->renderDebugLayer( dt );
  }

  // Swap front and back buffers
  m_context->pGraphics->makeContextCurrent();
  m_context->pGraphics->swapBuffers();

}

void Engine::Application::updateState()
{
  auto dt = calculateDeltaTime( m_lastUpdateTick );

  if( !m_context->pStateStack->empty() )
  {
    if( auto state = m_context->pStateStack->top() )
    {
      if( state->shouldFinish() )
        m_context->pStateStack->pop();
      state->update(dt);
    }
  }

  if( m_bPopState )
  {
    if( auto state = m_context->pStateStack->top() )
    {
      state->unload();
      m_context->pStateStack->pop();

      if( auto nextState = m_context->pStateStack->top() )
        nextState->reEnter();
    }
    m_bPopState = false;
  }
}

double Engine::Application::calculateDeltaTime( uint64_t& lastTick )
{
  auto now = std::chrono::steady_clock::now();
  uint64_t deltaTime =
          std::chrono::time_point_cast< std::chrono::milliseconds >( now ).time_since_epoch().count() - lastTick;

  lastTick = std::chrono::time_point_cast< std::chrono::milliseconds >( now ).time_since_epoch().count();
  return static_cast< double >( deltaTime ) / 1000.0;
}

void Engine::Application::initImGui(const char* glsl_version)
{
  auto& graphics = *m_context->pGraphics;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  ImGui_ImplGlfw_InitForOpenGL( graphics.getWindowHandle(), true );
  ImGui_ImplOpenGL3_Init( glsl_version );

  ImGui::StyleColorsDark();

  onInitImGuiPost();
}

void Engine::Application::popState()
{
  m_bPopState = true;
}

std::shared_ptr< Engine::ApplicationContext > Engine::Application::getContext() const
{
  return m_context;
}

