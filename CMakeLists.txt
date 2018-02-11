cmake_minimum_required (VERSION 2.6)

project(ApiClient C CXX)

include_directories(ApiClient)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

enable_testing()

add_subdirectory("api_client")
add_subdirectory("api_tool")
