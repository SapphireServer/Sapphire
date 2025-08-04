#include "Input.h"

#include <memory>

#include "glcommon.h"

using namespace Engine;

Input::KeyFlags Input::m_keyStates[ MAX_KEY_STATES ];
bool Input::m_mouseStates[ MAX_MOUSE_STATES ];
GLFWwindow* Input::m_pWindow = nullptr;

float Input::m_mouseDx = 0.f;
float Input::m_mouseDy = 0.f;
float Input::m_mouseLastX = 0.f;
float Input::m_mouseLastY = 0.f;
float Input::m_scrollOffset = 0.f;

bool Input::init( GLFWwindow* window )
{
  if (window == nullptr) {
    return false;
  }

  m_pWindow = window;

  std::memset( Input::m_keyStates, 0, MAX_KEY_STATES );
  glfwSetKeyCallback( window, &Input::glfwKeyCallback );

  glfwSetScrollCallback(window, [](GLFWwindow* /*window*/, double /*xoffset*/, double yoffset) {
    Input::m_scrollOffset += yoffset;
  });

  return true;
}



void Input::glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
  switch( action )
  {
    case GLFW_PRESS:
    {
      Input::m_keyStates[ key ] = KeyFlags::KeyDown;
      break;
    }

    case GLFW_REPEAT:
    {
      Input::m_keyStates[ key ] = KeyFlags::KeyHeld;
      break;
    }

    case GLFW_RELEASE:
    {
      Input::m_keyStates[ key ] = KeyFlags::KeyUp;
      break;
    }

    default:
      break;
  }
}

int Input::keyHeld( int key )
{
  return glfwGetKey( m_pWindow, key );
}

bool Input::keyDown( int key )
{
  auto state = m_keyStates[ key ];
  return state == KeyFlags::KeyDown || state == KeyFlags::KeyHeld;
}

bool Input::keyUp( int key )
{
  return m_keyStates[ key ] == KeyFlags::KeyUp;
}

void Input::nextFrame()
{
  for( auto& state : m_keyStates )
  {
    if( state == KeyFlags::KeyDown || state == KeyFlags::KeyUp )
    {
      state = KeyFlags::None;
    }
  }
}

bool Input::mouseClick( MouseButton button )
{
  int state = glfwGetMouseButton( m_pWindow, button );
  if( state == GLFW_PRESS && !m_mouseStates[ button ] )
  {
    m_mouseStates[ button ] = GLFW_PRESS;
    return true;
  }
  return false;
}

bool Input::mousePressed( MouseButton button )
{
  int state = glfwGetMouseButton( m_pWindow, button );
  if( state == GLFW_PRESS )
    m_mouseStates[ button ] = GLFW_PRESS;
  return state == GLFW_PRESS;
}

bool Input::mouseReleased( MouseButton button )
{
  int state = glfwGetMouseButton( m_pWindow, button );
  if( m_mouseStates[ button ] && state == GLFW_RELEASE )
  {
    m_mouseStates[ button ] = false;
    return true;
  }

  return state == GLFW_RELEASE;
}

void Input::poll()
{
  Input::m_scrollOffset = 0;
  glfwPollEvents();
}

void Input::updateMousePosition()
{
  int width, height;
  glfwGetFramebufferSize( m_pWindow, &width, &height );

  double xpos;
  double ypos;
  getCursorPos( xpos, ypos );

  m_mouseDx = -static_cast< float >( m_mouseLastX - xpos );
  m_mouseDy = static_cast< float >( m_mouseLastY - ypos );
  m_mouseLastX = static_cast< float >( xpos );
  m_mouseLastY = static_cast< float >( ypos );

}


void Input::resetMousePositionToLast()
{
  m_mouseDx = m_mouseLastX;
  m_mouseDy = m_mouseLastY;
}


void Input::resetMousePosition()
{
  int width, height;
  glfwGetFramebufferSize( m_pWindow, &width, &height );

  double halfWidth = static_cast< double >( width ) / 2;
  double halfHeight = static_cast< double >( height ) / 2;

  setCursorPos( halfWidth, halfHeight );
}

void Input::getCursorPos( double& x, double& y )
{
  glfwGetCursorPos( m_pWindow, &x, &y );
}

void Input::setCursorPos( const double& x, const double& y )
{
  glfwSetCursorPos( m_pWindow, x, y );
}

float Input::getMouseDx()
{
  return m_mouseDx;
}

float Input::getMouseDy()
{
  return m_mouseDy;
}

void Input::showMouseCursor()
{
  glfwSetInputMode( m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
}

void Input::hideMouseCursor()
{
  glfwSetInputMode( m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
}

void Input::scrollCallback( GLFWwindow *window, double xoffset, double yoffset )
{
  Input::m_scrollOffset = yoffset;
}

float Input::getMouseScroll()
{
  float ret = m_scrollOffset;
  Input::m_scrollOffset = 0;
  return ret;
}
