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

find_package( OpenGL REQUIRED COMPONENTS OpenGL )

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif()

add_executable( Toolkit ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
#  target_link_libraries( Toolkit common xivdat pthread mysql dl z stdc++fs )
    message( "Tool only supported on windows for now" )
else()
    target_link_libraries( Toolkit
            PRIVATE
            ${OPENGL_gl_LIBRARY}
            ${OPENGL_glu_LIBRARY}
            glew32
            glfw3
            kernel32
            user32
            gdi32
            winspool
            comdlg32
            advapi32
            shell32
            ole32
            oleaut32
            uuid
            odbc32
            odbccp32
            common world xivdat mysql zlib
    )

endif()
