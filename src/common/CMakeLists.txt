file(GLOB UTILS_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Crypt/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Exd/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Logging/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Navi/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/PacketDef/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Script/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Random/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp")


add_library( common ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

target_link_libraries( common
        PUBLIC
        xivdat
        mysqlConnector
        mysql
        Detour
        DetourCrowd )

if( UNIX )
    target_link_libraries( common
            PUBLIC
            pthread
            stdc++fs
            Detour
            DetourCrowd )
endif()

target_include_directories( common
                              PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}/"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/asio/asio/include/"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/spdlog/include/"
                                Detour)

