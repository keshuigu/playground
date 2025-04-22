cmake_minimum_required(VERSION 3.14)
project(hot100 VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)

add_executable(chat-client "")
add_executable(chat-client_epoll "")
add_executable(chat-server "")
add_executable(chat-server_epoll "")
target_sources(chat-client
  PRIVATE
  "client.cc"
)

target_sources(chat-client_epoll
  PRIVATE
  "client_epoll.cc"
)

target_sources(chat-server
  PRIVATE
  "server.cc"
)


target_sources(chat-server_epoll
  PRIVATE
  "server_epoll.cc"
)
include_directories(
  "${PROJECT_BINARY_DIR}/include"
  "."
)