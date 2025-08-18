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
add_library( imgui1 STATIC ${imgui_SOURCES} )
target_link_libraries( imgui1 PUBLIC glfw  )
target_include_directories( imgui1 PUBLIC
  ${PROJECT_SOURCE_DIR}/deps/imgui
  ${PROJECT_SOURCE_DIR}/deps/imgui/examples
)

file( GLOB_RECURSE SOURCES
  *.cpp
  *.h
)

add_executable( ToolkitPs3 ${SOURCES} )
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
target_link_libraries( ToolkitPs3 PRIVATE
  common
  imgui1
  libglew_static
  glm
  xivdatps3
)
target_include_directories( ToolkitPs3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )
