cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project(Tool_QuestBattle_BruteForce)

file(GLOB SERVER_PUBLIC_INCLUDE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB SERVER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}*.c*")

add_executable(questbattle_bruteforce ${SERVER_PUBLIC_INCLUDE_FILES} ${SERVER_SOURCE_FILES})

if (UNIX)
  target_link_libraries (questbattle_bruteforce common xivdat pthread mysql dl z stdc++fs )
else()
  target_link_libraries (questbattle_bruteforce common xivdat mysql zlib)
endif()

