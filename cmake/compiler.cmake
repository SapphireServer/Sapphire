if( UNIX )
  # override policy CMP0069 to NEW
  set( CMAKE_POLICY_DEFAULT_CMP0069 NEW )
  cmake_policy( SET CMP0069 NEW )

  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC" )
  set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3" )

  # enable parallel builds for GCC/Clang with Make
  if(${CMAKE_GENERATOR} MATCHES "Make")
    set( CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j$(nproc)" )
  endif()

  # enable Link Time Optimization (LTO)
  include( CheckIPOSupported )
  check_ipo_supported( RESULT result )
  if( result )
    set( CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE )
  else()
    message( WARNING "IPO is not supported on this platform." )
  endif()
else()
  add_definitions( -D_WIN32_WINNT=0x601 )
  add_definitions( -D_CRT_SECURE_NO_WARNINGS )
  add_definitions( -DNOMINMAX )
      
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc" )
  message( STATUS "Enabling Build with Multiple Processes.." )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4834" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17" )

  set( CMAKE_CXX_STANDARD 17 )
  set( CMAKE_CXX_STANDARD_REQUIRED ON )
  set( CMAKE_CXX_EXTENSIONS ON )

  if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    # disabling SAFESEH
    message( STATUS "Disabling Safe Exception Handlers.." )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO" )

    # edit and continue
    message( STATUS "Enabling Edit and Continue.." )
    add_definitions( /Zi )

    # incremental linking
    message( STATUS "Enabling Incremental Linking.." )
    set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL" )
  endif()
endif()

# force standalone asio
add_definitions( -DASIO_STANDALONE )
