cmake_minimum_required(VERSION 3.14)
project(hot100 VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)


add_executable(redisdemo "")
target_sources(redisdemo
  PRIVATE
  "redis.cc"
)

target_link_libraries(redisdemo hiredis)


include_directories(
  "${PROJECT_BINARY_DIR}/include"
  "."
)
