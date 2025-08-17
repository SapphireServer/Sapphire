option( ENABLE_SANITIZERS "Enable sanitizers" OFF )
if( ENABLE_SANITIZERS )
  if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    if( CMAKE_CXX_COMPILER_FRONTEND_VARIANT MATCHES "^MSVC$")
      # NOTE: There is bug in Clang-CL that makes address sanitizers not work for all projects.
      # The main issue is the 'world' project, which has WINDOWS_EXPORT_ALL_SYMBOLS.
      # This issue will likely be fixed in a later version of Clang-CL, but for now you should
      # configure with -DCMAKE_C_COMPILER=clang.exe -DCMAKE_CXX_COMPILER=clang++.exe to enable
      # UB sanitizers.
      message( WARNING "Enabling Clang-CL sanitizers (Clang works better)..." )
      add_compile_options( -fsanitize=address,undefined )

      # Reference: https://devblogs.microsoft.com/cppblog/addresssanitizer-asan-for-windows-with-msvc/
      if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
        set( ASAN_LIB_SUFFIX "x86_64" )
      else()
        set( ASAN_LIB_SUFFIX "i386" )
      endif()
      set( ASAN_LINKER_FLAGS "/wholearchive:clang_rt.asan-${ASAN_LIB_SUFFIX}.lib /wholearchive:clang_rt.asan_cxx-${ASAN_LIB_SUFFIX}.lib" )
    else()
      message( STATUS "Enabling Clang sanitizers..." )
      add_compile_options( -fsanitize=address,undefined -fno-omit-frame-pointer )
      set( ASAN_LINKER_FLAGS "-fsanitize=address,undefined" )
    endif()

    # NOTE: Only set linker flags for executables and shared libraries
    # the add_link_options command would add flags to static libraries as well
    # which causes issues with symbols being defined in multiple places.
    set( CMAKE_EXE_LINKER_FLAGS "${ASAN_LINKER_FLAGS}" )
    set( CMAKE_SHARED_LINKER_FLAGS "${ASAN_LINKER_FLAGS}" )

    if( WIN32 )
      # NOTE: The sanitizer library only supports the static release runtime
      set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" )
    endif()
  elseif( MSVC )
    # Reference: https://learn.microsoft.com/en-us/cpp/build/reference/fsanitize
    message( WARNING "Enabling MSVC sanitizers (Clang has better support)..." )
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

  # Disable CRT security warnings (easier to linux compatibility)
  add_compile_definitions( _CRT_SECURE_NO_WARNINGS )

  # Disable extension iterator warnings for outdated fmt
  add_compile_definitions( _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING )
  add_compile_definitions( _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING )

  if( MSVC )
    # Disable warning about nodiscard for boost asio
    add_compile_options( /wd4834 )

    # Increase number of sections in .obj file
    add_compile_options( /bigobj )

    # Disable permissive mode
    add_compile_options( /permissive- )
  endif()

  # Visual Studio generator specific flags
  if (CMAKE_GENERATOR MATCHES "Visual Studio")
    message( STATUS "Enabling Build with Multiple Processes.." )
    add_compile_options( /MP )
  endif()
endif()

# Force standalone asio
add_compile_definitions( ASIO_STANDALONE )
