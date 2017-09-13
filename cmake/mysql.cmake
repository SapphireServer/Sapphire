
if(UNIX)
    include_directories("/usr/include/mysql/")
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


