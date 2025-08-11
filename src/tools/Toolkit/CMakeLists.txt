cmake_minimum_required( VERSION 3.10 )
cmake_policy(SET CMP0015 NEW)
project(Tool_Toolkit)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/deps/imgui/imgui.cpp"
        "${CMAKE_SOURCE_DIR}/deps/imgui/*.c*"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Engine/*.cpp")

include_directories( "." "../"  "../../" )

add_executable( Toolkit ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

target_link_libraries( Toolkit 
        PRIVATE
        libglew_static
        glfw
        common world xivdat mysql zlib )