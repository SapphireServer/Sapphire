set( CMAKE_CXX_FLAGS "-std=c++11 -m32")

include_directories("../../")
include_directories("../")

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.cpp")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
add_executable(pcb_parser2 ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
    target_link_libraries (pcb_parser2 Common xivdat pthread mysqlclient dl z)
else()
    target_link_libraries (pcb_parser2 Common xivdat libmysql zlib1)
endif()
target_link_libraries(pcb_parser2 ${Boost_LIBRARIES} ${Boost_LIBRARIES})

