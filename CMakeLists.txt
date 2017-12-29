cmake_minimum_required(VERSION 3.2.0)
project(loteca)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE APP_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(loteca ${APP_SRCS})
