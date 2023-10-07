cmake_minimum_required(VERSION 3.0)

project(mini_container CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC ./src CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(TestCmd test/TestCmd.cpp)
target_include_directories(TestCmd PRIVATE include)
target_link_libraries(TestCmd PRIVATE ${PROJECT_NAME})
