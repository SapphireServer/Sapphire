#pragma once
#include <cstdint>
#include "KeyMap.h"

struct GLFWwindow;

namespace Engine
{

  class Input
  {
  public:

    enum MouseButton
    {
      MouseLeft = 0,
      MouseRight = 1,
      MouseMiddle = 2
    };

    enum KeyFlags : uint8_t
    {
      None,
      KeyDown,
      KeyUp,
      KeyHeld,
    };

    static bool init( GLFWwindow *window );

    static int keyHeld( int key );

    /*!
     * @brief Checks whether a key was pressed this frame
     * @param key Keycode to check
     * @return True if a key was pressed this frame
     */
    static bool keyDown( int key );

    /*!
     * @brief Checks whether a key was released this frame.
     * @param key Keycode to check
     * @return True if key was released this frame
     */
    static bool keyUp( int key );

    /*!
     * @brief Clears all KeyDown/KeyUp from the keyStates array.
     *
     * Input::poll() should be called at the beginning of a frame to fill the keyState array with assoicated states
     * as applicable. This will clear transient states at the end of the frame so events such as KeyUp/KeyDown (but not
     * KeyRepeat) are only fired for one frame.
     */
    static void nextFrame();

    static bool mousePressed( MouseButton button );

    static bool mouseClick( MouseButton button );

    static bool mouseReleased( MouseButton button );

    static void poll();

    static void getCursorPos( double& x, double& y );

    static void setCursorPos( const double& x, const double& y );

    static float getMouseDx();

    static float getMouseDy();

    static float getMouseScroll();

    static void updateMousePosition();

    static void resetMousePosition();
    static void resetMousePositionToLast();

    static void showMouseCursor();

    static void hideMouseCursor();
    static void glfwKeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
    static void scrollCallback( GLFWwindow* window, double xoffset, double yoffset );

  private:
    static GLFWwindow *m_pWindow;

    // stolen number from imgui, guess that's 'portable' enough
    static const uint32_t MAX_KEY_STATES = 512;
    static const uint32_t MAX_MOUSE_STATES = 32;
    static KeyFlags m_keyStates[MAX_KEY_STATES];
    static bool m_mouseStates[MAX_MOUSE_STATES];

    static float m_mouseDx;
    static float m_mouseDy;
    static float m_mouseLastX;
    static float m_mouseLastY;

    static float m_scrollOffset;

  };
}
