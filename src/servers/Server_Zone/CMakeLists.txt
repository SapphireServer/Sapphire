cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0014 OLD)

project(Sapphire_Zone)

include_directories("../../libraries/external/ChaiScript-6.0.0/include/")
include_directories("../../libraries/sapphire/datReader/")
include_directories("../")

file(GLOB SERVER_PUBLIC_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/* ${CMAKE_CURRENT_SOURCE_DIR}/Script/*)
file(GLOB SERVER_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.c*
        Actor/*.c*
        Action/*.c*
        DebugCommand/*.c*
        Event/*.c*
        Inventory/*.c*
        Linkshell/*.c*
        Network/*.c*
        Network/Handlers/*.c*
        Network/PacketWrappers/*.c*
        Script/*.c*
        StatusEffect/*.c*
        Zone/*.c*)

set(SERVER_COMMON_DIR ../Server_Common)
set(Boost_USE_STATIC_LIBS ON)

if(UNIX)
  include_directories("/usr/include/mysql/")
  message(STATUS "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

  find_package(Boost ${SAPPHIRE_BOOST_VER} COMPONENTS log log_setup thread date_time filesystem system)
  if(Boost_FOUND)
    set(BOOST_LIBRARY_DIR ${Boost_LIBRARY_DIR})
  else()
    if (EXISTS /opt/build_libs/${SAPPHIRE_BOOST_FOLDER_NAME})
      set(Boost_INCLUDE_DIR /opt/build_libs/${SAPPHIRE_BOOST_FOLDER_NAME})
      set(BOOST_LIBRARYDIR /opt/build_libs/${SAPPHIRE_BOOST_FOLDER_NAME}/stage/lib)
      find_package(Boost ${SAPPHIRE_BOOST_VER} COMPONENTS log log_setup thread date_time filesystem system)
    else()
      message(FATAL_ERROR "Unable to find boost ${SAPPHIRE_BOOST_VER} package!")
    endif()
  endif()
else()
  add_definitions(-D_WIN32_WINNT=0x601)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/")
  message(STATUS "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/${SAPPHIRE_BOOST_FOLDER_NAME})
    message(STATUS "Using boost in /libraries/external")
	  set(Boost_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/${SAPPHIRE_BOOST_FOLDER_NAME})
    set(BOOST_LIBRARYDIR ${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/${SAPPHIRE_BOOST_FOLDER_NAME}/lib32-msvc-14.0)
  else()
      find_package(Boost ${SAPPHIRE_BOOST_VER} COMPONENTS log log_setup thread date_time filesystem system)
      if(Boost_FOUND)
        set(BOOST_LIBRARY_DIR ${Boost_LIBRARY_DIR})
      elseif ((EXISTS $ENV{BOOST_ROOT_DIR}) AND (EXISTS $ENV{BOOST_LIB_DIR}))
        set(Boost_INCLUDE_DIR $ENV{BOOST_ROOT_DIR})
	      set(BOOST_LIBRARYDIR $ENV{BOOST_LIB_DIR})
      else()
        message(FATAL_ERROR "SapphireError: Unable to find boost ${SAPPHIRE_BOOST_VER} package and environment variables BOOST_ROOT_DIR and BOOST_LIB_DIR not set!")
      endif()
  endif()
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Script)

include_directories(${Boost_INCLUDE_DIR})

link_directories(${BOOST_LIBRARYDIR})
link_directories(${SERVER_COMMON_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sapphire/datReader)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  # 32 bit link
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/x86)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/zlib/x86)
else()
  # 64 bit link
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/MySQL/x64)
  link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/zlib/x64)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/")

add_executable(server_zone ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES} Linkshell/Linkshell.cpp Linkshell/Linkshell.h)
add_dependencies(server_zone Common xivdat)

set_target_properties(server_zone PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
)

if (UNIX)
  target_link_libraries (server_zone Common xivdat pthread mysqlclient dl z)
else()
  target_link_libraries (server_zone Common xivdat libmysql zlib1)
endif()

target_link_libraries(server_zone ${Boost_LIBRARIES} ${Boost_LIBRARIES})
