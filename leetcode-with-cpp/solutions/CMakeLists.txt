add_library(solutions data_struct.cc solution_1_500.cc solution_501_1000.cc solution_1001_1500.cc solution_2001_2500.cc solution_2501_3000.cc )
target_include_directories(
  solutions
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)