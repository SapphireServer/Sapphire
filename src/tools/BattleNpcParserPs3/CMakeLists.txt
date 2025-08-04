#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_CURRENT_BINARY_DIR}/bin/tools")

file(GLOB SERVER_PUBLIC_INCLUDE_FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/*"
  "${CMAKE_CURRENT_SOURCE_DIR}/BMP-DDS_Converter/*"
)
file(GLOB SERVER_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}*.c*"
  "${CMAKE_CURRENT_SOURCE_DIR}/BMP-DDS_Converter/*.c*"
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/")
add_executable(bnpc_parserps3 ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

#set_target_properties(discovery_parser PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../bin/"
#)

if (UNIX)
    target_link_libraries (bnpc_parserps3 common xivdatps3 pthread mysql dl z stdc++fs)
else()
    target_link_libraries (bnpc_parserps3 common xivdatps3 mysql zlib)
endif()



