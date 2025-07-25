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
  set(MYSQL_CONFIG_PREFER_PATH "$ENV{MYSQL_HOME}/bin" CACHE FILEPATH
    "preferred path to MySQL (mysql_config)"
  )

  # try mariadb first
  find_program(MYSQL_CONFIG mariadb_config
    ${MYSQL_CONFIG_PREFER_PATH}
    /usr/local/mysql/bin/
    /usr/local/bin/
    /usr/bin/
  )

  if( NOT MYSQL_CONFIG )
    # fallback to mysql
    find_program(MYSQL_CONFIG mysql_config
      ${MYSQL_CONFIG_PREFER_PATH}
      /usr/local/mysql/bin/
      /usr/local/bin/
      /usr/bin/
    )
  endif()

  if( MYSQL_CONFIG )
    message(STATUS "Using mysql-config: ${MYSQL_CONFIG}")
    # set INCLUDE_DIR
    execute_process(COMMAND ${MYSQL_CONFIG} --include
      OUTPUT_VARIABLE MY_TMP
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    string(REGEX REPLACE "-I([^ ]*)( .*)?" "\\1" MY_TMP "${MY_TMP}")
    set(MYSQL_ADD_INCLUDE_PATH ${MY_TMP} CACHE FILEPATH INTERNAL)
    #message("[DEBUG] MYSQL ADD_INCLUDE_PATH : ${MYSQL_ADD_INCLUDE_PATH}")
    # set LIBRARY_DIR
    execute_process(COMMAND ${MYSQL_CONFIG} --libs_r
      OUTPUT_VARIABLE MY_TMP
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(MYSQL_ADD_LIBRARIES "")
    string(REGEX MATCHALL "-l[^ ]*" MYSQL_LIB_LIST "${MY_TMP}")
    foreach(LIB ${MYSQL_LIB_LIST})
      string(REGEX REPLACE "[ ]*-l([^ ]*)" "\\1" LIB "${LIB}")
      list(APPEND MYSQL_ADD_LIBRARIES "${LIB}")
      #message("[DEBUG] MYSQL ADD_LIBRARIES : ${MYSQL_ADD_LIBRARIES}")
    endforeach(LIB ${MYSQL_LIB_LIST})

    set(MYSQL_ADD_LIBRARIES_PATH "")
    string(REGEX MATCHALL "-L[^ ]*" MYSQL_LIBDIR_LIST "${MY_TMP}")
    foreach(LIB ${MYSQL_LIBDIR_LIST})
      string(REGEX REPLACE "[ ]*-L([^ ]*)" "\\1" LIB "${LIB}")
      list(APPEND MYSQL_ADD_LIBRARIES_PATH "${LIB}")
      #message("[DEBUG] MYSQL ADD_LIBRARIES_PATH : ${MYSQL_ADD_LIBRARIES_PATH}")
    endforeach(LIB ${MYSQL_LIBS})

  else( MYSQL_CONFIG )
    set(MYSQL_ADD_LIBRARIES "")
    list(APPEND MYSQL_ADD_LIBRARIES "mysqlclient_r")
    list(APPEND MYSQL_ADD_LIBRARIES "mariadbclient")
  endif( MYSQL_CONFIG )
endif( UNIX )

if( WIN32 )
  SET(PROGRAM_FILES_64 $ENV{ProgramW6432})
  if (${PROGRAM_FILES_64})
     STRING(REPLACE "\\\\" "/" PROGRAM_FILES_64 ${PROGRAM_FILES_64})
  endif(${PROGRAM_FILES_64})
endif ( WIN32 )

find_path(MYSQL_INCLUDE_DIR
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
    "${PROGRAM_FILES_64}/MariaDB 10.3/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 10.4/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 10.5/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 10.6/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 10.7/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 10.8/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 10.9/include/mysql"
    "${PROGRAM_FILES_64}/MariaDB 11.8/include/mysql"
    "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/include"
    "${PROGRAM_FILES_64}/MySQL/include"
    "C:/MySQL/include"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/include"
    "$ENV{ProgramFiles}/MySQL/MySQL Server 5.7/include"
    "$ENV{SystemDrive}/MySQL/MySQL Server 5.7/include"
    "c:/msys/local/include"
    "$ENV{MYSQL_ROOT}/include"
  DOC
    "Specify the directory containing mysql.h."
)

if( UNIX )
  foreach(LIB ${MYSQL_ADD_LIBRARIES})
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
  endforeach(LIB ${MYSQL_ADD_LIBRARY})
endif( UNIX )

if( WIN32 )
  find_library( MYSQL_LIBRARY
    NAMES
      libmysql
      libmariadb
    PATHS
      ${MYSQL_ADD_LIBRARIES_PATH}
      "${PROGRAM_FILES_64}/MariaDB 10.3/lib"
      "${PROGRAM_FILES_64}/MariaDB 10.4/lib"
      "${PROGRAM_FILES_64}/MariaDB 10.5/lib"
      "${PROGRAM_FILES_64}/MariaDB 10.6/lib"
      "${PROGRAM_FILES_64}/MariaDB 10.7/lib"
      "${PROGRAM_FILES_64}/MariaDB 10.8/lib"
      "${PROGRAM_FILES_64}/MariaDB 10.9/lib"
      "${PROGRAM_FILES_64}/MariaDB 11.8/lib"
      "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/lib"
      "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/lib/opt"
      "${PROGRAM_FILES_64}/MySQL/lib"
      "C:/MySQL/lib/debug"
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/lib"
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/lib/opt"
      "$ENV{ProgramFiles}/MySQL/MySQL Server 5.7/lib/opt"
      "$ENV{SystemDrive}/MySQL/MySQL Server 5.7/lib/opt"
      "c:/msys/local/include"
      "$ENV{MYSQL_ROOT}/lib"
    DOC "Specify the location of the mysql library here."
  )

  STRING( REGEX REPLACE "(.lib)$" ".dll" MYSQL_DLL ${MYSQL_LIBRARY} )

  file(COPY ${MYSQL_DLL}
            DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/bin/" )

endif( WIN32 )

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
else( NOT WIN32 )
  set( MYSQL_EXTRA_LIBRARIES "" )
endif( NOT WIN32 )

if( UNIX )
    find_program(MYSQL_EXECUTABLE mysql
    PATHS
        ${MYSQL_CONFIG_PREFER_PATH}
        /usr/local/mysql/bin/
        /usr/local/bin/
        /usr/bin/
    DOC
        "path to your mysql binary."
    )
endif( UNIX )

if( WIN32 )
    find_program(MYSQL_EXECUTABLE mysql
      PATHS
        "${PROGRAM_FILES_64}/MariaDB 10.3/bin"
        "${PROGRAM_FILES_64}/MariaDB 10.4/bin"
        "${PROGRAM_FILES_64}/MariaDB 10.5/bin"
        "${PROGRAM_FILES_64}/MariaDB 10.6/bin"
        "${PROGRAM_FILES_64}/MariaDB 10.7/bin"
        "${PROGRAM_FILES_64}/MariaDB 11.8/bin"
        "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/bin"
        "${PROGRAM_FILES_64}/MySQL/MySQL Server 5.7/bin/opt"
        "${PROGRAM_FILES_64}/MySQL/bin"
        "C:/MySQL/bin/debug"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/bin"
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.7;Location]/bin/opt"
        "$ENV{ProgramFiles}/MySQL/MySQL Server 5.7/bin/opt"
        "$ENV{SystemDrive}/MySQL/MySQL Server 5.7/bin/opt"
        "c:/msys/local/include"
        "$ENV{MYSQL_ROOT}/bin"
     DOC
        "path to your mysql binary."
    )
endif( WIN32 )

if( MYSQL_LIBRARY )
  if( MYSQL_INCLUDE_DIR )
    set( MYSQL_FOUND 1 )
    message(STATUS "Found MySQL library: ${MYSQL_LIBRARY}")
    message(STATUS "Found MySQL headers: ${MYSQL_INCLUDE_DIR}")
  else( MYSQL_INCLUDE_DIR )
    message(FATAL_ERROR "Could not find MySQL headers! Please install the development libraries and headers")
  endif( MYSQL_INCLUDE_DIR )
  if( MYSQL_EXECUTABLE )
    message(STATUS "Found MySQL executable: ${MYSQL_EXECUTABLE}")
  endif( MYSQL_EXECUTABLE )
  mark_as_advanced( MYSQL_FOUND MYSQL_LIBRARY MYSQL_EXTRA_LIBRARIES MYSQL_INCLUDE_DIR MYSQL_EXECUTABLE)
else( MYSQL_LIBRARY )
  message(FATAL_ERROR "Could not find the MySQL libraries! Please install the development libraries and headers")
endif( MYSQL_LIBRARY )

