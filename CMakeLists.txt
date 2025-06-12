cmake_minimum_required(VERSION 3.10)
project(mwe_config_file)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
# Add the main executable
add_executable(${PROJECT_NAME} ${SOURCES})


find_package(fmt)
target_link_libraries(${PROJECT_NAME} fmt::fmt)
