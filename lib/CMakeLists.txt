cmake_minimum_required(VERSION 3.0)

project(mini_container CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC ./src CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME}  -static)

target_include_directories(${PROJECT_NAME} PUBLIC include)
