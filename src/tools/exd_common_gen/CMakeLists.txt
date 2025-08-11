add_executable( exd_common_gen
  main.cpp
  generated.h
)
target_link_libraries( exd_common_gen PRIVATE common )
