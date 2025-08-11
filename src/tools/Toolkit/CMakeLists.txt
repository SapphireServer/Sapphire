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
add_library( imgui STATIC ${imgui_SOURCES} )
target_link_libraries( imgui PUBLIC glfw )
target_include_directories( imgui PUBLIC
  ${PROJECT_SOURCE_DIR}/deps/imgui
  ${PROJECT_SOURCE_DIR}/deps/imgui/backends
)

file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( Toolkit ${SOURCES} )

if( NOT TARGET imgui OR NOT TARGET glfw OR NOT TARGET libglew_static OR NOT TARGET glm )
  message( FATAL_ERROR "Missing dependencies for Toolkit" )
endif()

target_link_libraries( Toolkit PRIVATE
  common
  imgui
  libglew_static
  glm
)

target_include_directories( Toolkit PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
