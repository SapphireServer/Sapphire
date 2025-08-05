option( ENABLE_SANITIZERS "Enable sanitizers" OFF )
if( ENABLE_SANITIZERS )
  if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    message( STATUS "Enabling Clang sanitizers..." )
    add_compile_options( -fsanitize=address,undefined -fno-omit-frame-pointer )
    add_link_options( -fsanitize=address,undefined )
  elseif( MSVC )
    # Reference: https://learn.microsoft.com/en-us/cpp/build/reference/fsanitize
    message( WARNING "Enabling MSVC sanitizers (-T ClangCL has better support)..." )
    add_compile_options( /fsanitize=address )
    add_link_options( /INCREMENTAL:NO )
  else()
    message ( FATAL_ERROR "Unsupported compiler for sanitizers: ${CMAKE_CXX_COMPILER_ID}" )
  endif()
endif()

# C++ standard
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS ON )

if( UNIX )
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
elseif( WIN32 )
  # Do not collide with std::min/max
  add_compile_definitions( NOMINMAX )

  # Required for boost asio
  add_compile_definitions( _WIN32_WINNT=0x601 )

  if( MSVC )
    # Disable CRT security warnings (easier to linux compatibility)
    add_compile_definitions( _CRT_SECURE_NO_WARNINGS )

    # Disable extension iterator warnings for outdated fmt
    add_compile_definitions( _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING )

    # Disable warning about nodiscard for boost asio
    add_compile_options( /wd4834 )

    # Increase number of sections in .obj file
    add_compile_options( /bigobj )
  endif()

  # Visual Studio generator specific flags
  if (CMAKE_GENERATOR MATCHES "Visual Studio")
    message( STATUS "Enabling Build with Multiple Processes.." )
    add_compile_options( /MP )
  endif()
endif()

# Force standalone asio
add_compile_definitions( ASIO_STANDALONE )
