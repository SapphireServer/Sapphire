#
# Find the MySQL client includes and library
#

# This module defines
# MYSQL_INCLUDE_DIR, where to find mysql.h
# MYSQL_LIBRARIES, the libraries to link against to connect to MySQL
# MYSQL_EXECUTABLE, the MySQL executable.
# MYSQL_FOUND, if false, you cannot build anything that requires MySQL.

# also defined, but not for general use are
# MYSQL_LIBRARY, where to find the MySQL library.

set( MYSQL_FOUND 0 )

if( UNIX )
  set( MYSQL_CONFIG_PREFER_PATH "$ENV{MYSQL_HOME}/bin" CACHE FILEPATH
       "preferred path to MySQL (mysql_config)"
  )

  # try mariadb first
  find_program( MYSQL_CONFIG mariadb_config
    ${MYSQL_CONFIG_PREFER_PATH}
    /usr/local/mysql/bin/
    /usr/local/bin/
    /usr/bin/
  )

  if( NOT MYSQL_CONFIG )
    # fallback to mysql
    find_program( MYSQL_CONFIG mysql_config
      ${MYSQL_CONFIG_PREFER_PATH}
      /usr/local/mysql/bin/
      /usr/local/bin/
      /usr/bin/
    )
  endif()

  if( MYSQL_CONFIG )
    message( STATUS "Using mysql-config: ${MYSQL_CONFIG}" )
    # set INCLUDE_DIR
    execute_process(
      COMMAND ${MYSQL_CONFIG} --include
      OUTPUT_VARIABLE MY_TMP
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    string( REGEX REPLACE "-I([^ ]*)( .*)?" "\\1" MY_TMP "${MY_TMP}" )
    set( MYSQL_ADD_INCLUDE_PATH ${MY_TMP} CACHE FILEPATH INTERNAL )
    # set LIBRARY_DIR
    execute_process(
      COMMAND ${MYSQL_CONFIG} --libs_r
      OUTPUT_VARIABLE MY_TMP
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set( MYSQL_ADD_LIBRARIES "" )
    string( REGEX MATCHALL "-l[^ ]*" MYSQL_LIB_LIST "${MY_TMP}" )
    foreach( LIB ${MYSQL_LIB_LIST} )
      string( REGEX REPLACE "[ ]*-l([^ ]*)" "\\1" LIB "${LIB}" )
      list( APPEND MYSQL_ADD_LIBRARIES "${LIB}" )
    endforeach()

    set( MYSQL_ADD_LIBRARIES_PATH "" )
    string( REGEX MATCHALL "-L[^ ]*" MYSQL_LIBDIR_LIST "${MY_TMP}" )
    foreach( LIB ${MYSQL_LIBDIR_LIST} )
      string( REGEX REPLACE "[ ]*-L([^ ]*)" "\\1" LIB "${LIB}" )
      list( APPEND MYSQL_ADD_LIBRARIES_PATH "${LIB}" )
    endforeach()
  else()
    set( MYSQL_ADD_LIBRARIES "" )
    list( APPEND MYSQL_ADD_LIBRARIES "mysqlclient_r" )
    list( APPEND MYSQL_ADD_LIBRARIES "mariadbclient" )
  endif()

  find_path( MYSQL_INCLUDE_DIR
    NAMES
      mysql.h
    PATHS
      ${MYSQL_ADD_INCLUDE_PATH}
      /usr/include
      /usr/include/mariadb
      /usr/include/mysql
      /usr/local/include
      /usr/local/include/mysql
      /usr/local/mysql/include
      ${MYSQL_INCLUDE_DIRS}
      "$ENV{MYSQL_ROOT}/include"
    DOC
      "Specify the directory containing mysql.h."
    REQUIRED
  )

  foreach( LIB ${MYSQL_ADD_LIBRARIES} )
    find_library( MYSQL_LIBRARY
      NAMES
        mysql libmysql libmariadb ${LIB}
      PATHS
        ${MYSQL_ADD_LIBRARIES_PATH}
        /usr/lib
        /usr/lib/mysql
        /usr/local/lib
        /usr/local/lib/mysql
        /usr/local/mysql/lib
        /usr/lib/x86_64-linux-gnu
      DOC "Specify the location of the mysql library here."
    )
  endforeach()

  if( NOT MYSQL_LIBRARY )
    message( FATAL_ERROR "Could not find the MySQL libraries! Please install the development libraries and headers" )
  endif()

  # On Windows you typically don't need to include any extra libraries
  # to build MYSQL stuff.

  find_library( MYSQL_EXTRA_LIBRARIES
    NAMES
      z zlib
    PATHS
      /usr/lib
      /usr/local/lib
    DOC
      "if more libraries are necessary to link in a MySQL client (typically zlib), specify them here."
  )

  find_program( MYSQL_EXECUTABLE mysql
    PATHS
      ${MYSQL_CONFIG_PREFER_PATH}
      /usr/local/mysql/bin/
      /usr/local/bin/
      /usr/bin/
    DOC
      "path to your mysql binary."
    REQUIRED
  )
elseif( WIN32 )
  function( check_mysql dir out_found out_include out_library out_executable )
    set( MYSQL_INCLUDE_DIR "${dir}/include/mysql" )
    if( NOT EXISTS "${MYSQL_INCLUDE_DIR}/mysql.h" )
      set( ${out_found} FALSE PARENT_SCOPE )
      return()
    endif()

    set( MYSQL_LIBRARY "${dir}/lib/libmysql.lib" )
    if( NOT EXISTS "${MYSQL_LIBRARY}" )
      set( MYSQL_LIBRARY "${dir}/lib/libmariadb.lib" )
      if( NOT EXISTS "${MYSQL_LIBRARY}" )
        set( ${out_found} OFF PARENT_SCOPE )
        return()
      endif()
    endif()

    set( MYSQL_EXECUTABLE "${dir}/bin/mysql.exe" )
    if( NOT EXISTS "${MYSQL_EXECUTABLE}" )
      set( ${out_found} OFF PARENT_SCOPE )
      return()
    endif()

    set( ${out_include} "${MYSQL_INCLUDE_DIR}" PARENT_SCOPE )
    set( ${out_library} "${MYSQL_LIBRARY}" PARENT_SCOPE )
    set( ${out_executable} "${MYSQL_EXECUTABLE}" PARENT_SCOPE )
    set( ${out_found} ON PARENT_SCOPE )
  endfunction()

  if( NOT MYSQL_ROOT AND DEFINED ENV{MYSQL_ROOT} )
    message( STATUS "Using MySQL root from environment variable MYSQL_ROOT" )
    set( MYSQL_ROOT $ENV{MYSQL_ROOT} )
  endif()
  if( MYSQL_ROOT )
    check_mysql( "${MYSQL_ROOT}" MYSQL_FOUND MYSQL_INCLUDE_DIR MYSQL_LIBRARY MYSQL_EXECUTABLE )
    if( NOT MYSQL_FOUND )
      message( FATAL_ERROR "Invalid MySQL root: ${MYSQL_ROOT}" )
    endif()
    set( MYSQL_DIR ${MYSQL_ROOT} )
  else()
    file( GLOB MYSQL_DIRS "$ENV{ProgramW6432}/MariaDB *" )
    if( MYSQL_DIRS )
      set( MYSQL_HIGHEST_VERSION "" )
      foreach( MYSQL_DIR ${MYSQL_DIRS} )
        string( REPLACE "\\" "/" MYSQL_DIR ${MYSQL_DIR} )
        string( REGEX MATCH "MariaDB ([0-9.]+)" MYSQL_VERSION_MATCH "${MYSQL_DIR}" )
        if( NOT MYSQL_DIR MATCHES "MariaDB ([0-9.]+)" )
          continue()
        endif()
        set( MYSQL_VERSION ${CMAKE_MATCH_1} )

        check_mysql( "${MYSQL_DIR}" MYSQL_FOUND MYSQL_INCLUDE_DIR MYSQL_LIBRARY MYSQL_EXECUTABLE )
        if( NOT MYSQL_FOUND )
          continue()
        endif()
        
        if( NOT MYSQL_HIGHEST_VERSION OR MYSQL_VERSION VERSION_GREATER MYSQL_HIGHEST_VERSION )
          set( MYSQL_HIGHEST_VERSION ${MYSQL_VERSION} )
          set( MYSQL_HIGHEST_DIR ${MYSQL_DIR} )
        endif()
      endforeach()

      set( MYSQL_DIR ${MYSQL_HIGHEST_DIR} )
    endif()

    if( NOT MYSQL_DIR )
      file( GLOB MYSQL_DIRS "$ENV{ProgramW6432}/MySQL/MySQL Server *" )
      if( MYSQL_DIRS )
        set( MYSQL_HIGHEST_VERSION "" )
        foreach( MYSQL_DIR ${MYSQL_DIRS} )
          string( REPLACE "\\" "/" MYSQL_DIR ${MYSQL_DIR} )
          string( REGEX MATCH "MySQL Server ([0-9.]+)" MYSQL_VERSION_MATCH "${MYSQL_DIR}" )
          if( NOT MYSQL_DIR MATCHES "MySQL Server ([0-9.]+)" )
            continue()
          endif()
          set( MYSQL_VERSION ${CMAKE_MATCH_1} )

          check_mysql( "${MYSQL_DIR}" MYSQL_FOUND MYSQL_INCLUDE_DIR MYSQL_LIBRARY MYSQL_EXECUTABLE )
          if( NOT MYSQL_FOUND )
            continue()
          endif()
          
          if( NOT MYSQL_HIGHEST_VERSION OR MYSQL_VERSION VERSION_GREATER MYSQL_HIGHEST_VERSION )
            set( MYSQL_HIGHEST_VERSION ${MYSQL_VERSION} )
            set( MYSQL_HIGHEST_DIR ${MYSQL_DIR} )
          endif()
        endforeach()

        set( MYSQL_DIR ${MYSQL_HIGHEST_DIR} )
      endif()
    endif()
  endif()

  check_mysql( "${MYSQL_DIR}" MYSQL_FOUND MYSQL_INCLUDE_DIR MYSQL_LIBRARY MYSQL_EXECUTABLE )
  if( NOT MYSQL_FOUND )
    message( FATAL_ERROR "Could not find MySQL!" )
  endif()

  STRING( REGEX REPLACE "(.lib)$" ".dll" MYSQL_DLL ${MYSQL_LIBRARY} )
  file( COPY ${MYSQL_DLL} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin" )
else()
  message( FATAL_ERROR "Unsupported platform!" )
endif()

set( MYSQL_FOUND 1 )
message( STATUS "Found MySQL library: ${MYSQL_LIBRARY}" )
message( STATUS "Found MySQL headers: ${MYSQL_INCLUDE_DIR}" )
message( STATUS "Found MySQL executable: ${MYSQL_EXECUTABLE}" )
mark_as_advanced( MYSQL_FOUND MYSQL_LIBRARY MYSQL_EXTRA_LIBRARIES MYSQL_INCLUDE_DIR MYSQL_EXECUTABLE )
