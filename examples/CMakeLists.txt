cmake_minimum_required(VERSION 3.14)
project(Example VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

# demos
add_subdirectory(apis)
add_subdirectory(chatroom)
add_subdirectory(processpools)
add_subdirectory(threadpools)
add_subdirectory(redis)