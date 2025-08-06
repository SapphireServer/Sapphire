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
endif()

if( WIN32 )
  file(
    GLOB MYSQL_INCLUDE_DIRS
    "$ENV{ProgramW6432}/MariaDB */include/mysql"
    "$ENV{ProgramW6432}/MySQL/MySQL Server */include"
  )
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
)

if( UNIX )
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
endif()

if( WIN32 )
  file(
    GLOB MYSQL_LIBRARY_DIRS
    "$ENV{ProgramW6432}/MariaDB */lib"
    "$ENV{ProgramW6432}/MySQL/MySQL Server */lib"
    "$ENV{ProgramW6432}/MySQL/MySQL Server */lib/opt"
  )
  find_library( MYSQL_LIBRARY
    NAMES
      libmysql
      libmariadb
    PATHS
      ${MYSQL_ADD_LIBRARIES_PATH}
      ${MYSQL_LIBRARY_DIRS}
      "$ENV{ProgramW6432}/MySQL/lib"
      "$ENV{MYSQL_ROOT}/lib"
    DOC "Specify the location of the mysql library here."
  )

  STRING( REGEX REPLACE "(.lib)$" ".dll" MYSQL_DLL ${MYSQL_LIBRARY} )

  file( COPY ${MYSQL_DLL} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin" )
endif()

# On Windows you typically don't need to include any extra libraries
# to build MYSQL stuff.

if( NOT WIN32 )
  find_library( MYSQL_EXTRA_LIBRARIES
    NAMES
      z zlib
    PATHS
      /usr/lib
      /usr/local/lib
    DOC
      "if more libraries are necessary to link in a MySQL client (typically zlib), specify them here."
  )
else()
  set( MYSQL_EXTRA_LIBRARIES "" )
endif()

if( UNIX )
  find_program( MYSQL_EXECUTABLE mysql
    PATHS
      ${MYSQL_CONFIG_PREFER_PATH}
      /usr/local/mysql/bin/
      /usr/local/bin/
      /usr/bin/
    DOC
      "path to your mysql binary."
  )
endif()

if( WIN32 )
  file(
    GLOB MYSQL_BIN_DIRS
    "$ENV{ProgramW6432}/MariaDB */bin"
    "$ENV{ProgramW6432}/MySQL/MySQL Server */bin"
    "$ENV{ProgramW6432}/MySQL/MySQL Server */bin/opt"
  )
  find_program( MYSQL_EXECUTABLE mysql
    PATHS
      ${MYSQL_BIN_DIRS}
      "${PROGRAM_FILES_64}/MySQL/bin"
      "$ENV{MYSQL_ROOT}/bin"
    DOC
      "path to your mysql binary."
  )
endif()

if( MYSQL_LIBRARY )
  if( MYSQL_INCLUDE_DIR )
    set( MYSQL_FOUND 1 )
    message( STATUS "Found MySQL library: ${MYSQL_LIBRARY}" )
    message( STATUS "Found MySQL headers: ${MYSQL_INCLUDE_DIR}" )
  else()
    message( FATAL_ERROR "Could not find MySQL headers! Please install the development libraries and headers" )
  endif()
  if( MYSQL_EXECUTABLE )
    message( STATUS "Found MySQL executable: ${MYSQL_EXECUTABLE}" )
  endif()
  mark_as_advanced( MYSQL_FOUND MYSQL_LIBRARY MYSQL_EXTRA_LIBRARIES MYSQL_INCLUDE_DIR MYSQL_EXECUTABLE )
else()
  message( FATAL_ERROR "Could not find the MySQL libraries! Please install the development libraries and headers" )
endif()
