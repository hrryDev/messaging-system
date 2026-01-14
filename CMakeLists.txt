cmake_minimum_required(VERSION 4.2.1)
project(messaging_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
	include
)

add_executable(system)
target_sources(system
  PRIVATE
	src/main.cpp
)
