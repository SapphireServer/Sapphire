cmake_minimum_required(VERSION 2.6)
project(Sapphire)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sapphire/datReader/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/external/ChaiScript-6.0.0/include/")

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
    else()
      message(FATAL_ERROR "Unable to find boost ${SAPPHIRE_BOOST_VER} package!")
    endif()
  endif()
else()
  add_definitions(-D_WIN32_WINNT=0x601)
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

set(Boost_USE_STATIC_LIBS ON)


file(GLOB UTILS_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB UTILS_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Crypt/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Exd/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Logging/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/PacketDef/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Script/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp")


find_package(Boost ${SAPPHIRE_BOOST_VER} COMPONENTS log log_setup thread date_time filesystem system)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${BOOST_LIBRARYDIR})
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../libraries/sapphire/datReader/")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Common ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} Network/PacketDef/Lobby/ServerLobbyDef.h)

set_target_properties(Common PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/"
)

if (UNIX)
  target_link_libraries(Common xivdat mysqlclient)
else()
  target_link_libraries(Common xivdat libmysql)
endif()
