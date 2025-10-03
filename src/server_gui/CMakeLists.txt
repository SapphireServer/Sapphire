# Create imgui library target
file( GLOB imgui_SOURCES
  ${PROJECT_SOURCE_DIR}/deps/imgui/*.cpp
  ${PROJECT_SOURCE_DIR}/deps/imgui/*.h
        ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_opengl3.h
        ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_opengl3_loader.h
        ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_glfw.h
)
if( WIN32 )
  list( APPEND imgui_SOURCES
          ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_win32.cpp
          ${PROJECT_SOURCE_DIR}/deps/imgui/backends/imgui_impl_win32.h
  )
endif()
add_library( imgui2 STATIC ${imgui_SOURCES} )
target_link_libraries( imgui2 PUBLIC glfw  )
target_include_directories( imgui2 PUBLIC
  ${PROJECT_SOURCE_DIR}/deps/imgui
  ${PROJECT_SOURCE_DIR}/deps/imgui/examples
)

file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( ServerGUI ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries( ServerGUI PRIVATE
  common
  imgui
  libglew_static
  glm
  world
)
target_include_directories( ServerGUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
