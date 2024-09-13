cmake_minimum_required(VERSION 3.24.1)
project(cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Optional: Disable compiler-specific extensions

add_executable(cpp
        main.cpp
        )
