
if( UNIX )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC" )
else()
  add_definitions( -D_WIN32_WINNT=0x601 )
  add_definitions( -D_CRT_SECURE_NO_WARNINGS )
  add_definitions( -DNOMINMAX )
      
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj" )
  set( CMAKE_CXX_STANDARD 17 )
  set( CMAKE_CXX_STANDARD_REQUIRED ON )
  set( CMAKE_CXX_EXTENSIONS ON )

  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/bin/" )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/bin/" )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_BINARY_DIR}/bin/" )
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_BINARY_DIR}/bin/" )

  set( VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/" )

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

    # enable building with multiple processes
    message( STATUS "Enabling Build with Multiple Processes.." )
    add_definitions( /MP )
  endif()
endif()

# force standalone asio
add_definitions( -DASIO_STANDALONE )
