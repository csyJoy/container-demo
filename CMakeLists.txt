cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Container CXX)

add_subdirectory(lib)

file(GLOB_RECURSE SRC ./src CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE mini_container -static-libgcc -static-libstdc++ -static)

target_include_directories(${PROJECT_NAME} PRIVATE include)
