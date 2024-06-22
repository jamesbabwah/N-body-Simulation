cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

project(NBody
        LANGUAGES CXX C
        DESCRIPTION "Nbody simulation")



set(PROJECT_SOURCES
        src/main.cpp
        src/ArgParser.cpp
        src/Timer.cpp
        include/ArgParser.hpp
        include/Timer.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        include
)



target_link_directories(${PROJECT_NAME} PUBLIC libs)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw3)