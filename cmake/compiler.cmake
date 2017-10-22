
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
else()
  add_definitions(-D_WIN32_WINNT=0x601)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")

  # edit and continue
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Enabling Edit and Continue..")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL /ZI")
  endif()
endif()


