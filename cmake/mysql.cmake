
if(UNIX)
    find_path(MYSQL_INCLUDE_DIR mysql.h
        /usr/include/mysql
        /usr/local/include/mysql
        /opt/mysql/mysql/include
        /opt/mysql/mysql/include/mysql
        /opt/mysql/include
        /opt/local/include/mysql5
        /usr/local/mysql/include
        /usr/local/mysql/include/mysql
        $ENV{ProgramFiles}/MySQL/*/include
        $ENV{SystemDrive}/MySQL/*/include
        ${LIBRARY_DIR}/external/MySQL/
    )

    if(MYSQL_INCLUDE_DIR)
        set(MYSQL_FOUND TRUE)

        include_directories(${MYSQL_INCLUDE_DIR})
    endif(MYSQL_INCLUDE_DIR)

    if(MYSQL_FOUND)
        message(STATUS "MySQL include dir: ${MYSQL_INCLUDE_DIR}")
    else(MYSQL_FOUND)
        message(FATAL_ERROR "Could not find MySQL headers.")
    endif(MYSQL_FOUND)
else()
    include_directories("${LIBRARY_DIR}/external/MySQL/")
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        # 32 bit link
        link_directories(${LIBRARY_DIR}/external/MySQL/x86)
        link_directories(${LIBRARY_DIR}/external/zlib/x86)
    else()
        # 64 bit link
        link_directories(${LIBRARY_DIR}/external/MySQL/x64)
        link_directories(${LIBRARY_DIR}/external/zlib/x64)
    endif()
endif()
