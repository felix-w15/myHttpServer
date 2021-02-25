cmake_minimum_required(VERSION 3.17)
project(myHttpServer_)

set(CMAKE_CXX_STANDARD 11)


#include_directories(.)

add_executable(myHttpServer_ main.cpp Epoll.cpp ThreadPool.cpp util.cpp requestData.cpp)

find_package(Threads REQUIRED)
target_link_libraries(myHttpServer_ Threads::Threads)