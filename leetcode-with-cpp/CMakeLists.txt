cmake_minimum_required(VERSION 3.14)
project(leetcode-with-cpp VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  hello_test
  hello_test.cc
)


target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)

add_subdirectory(solutions)

add_executable(
  test_main
  test_main.cc
)

target_link_libraries(
  test_main
  PUBLIC
  solutions
)

target_include_directories(
  test_main
  PUBLIC
  ${PROJECT_SOURCE_DIR}/solutions
)