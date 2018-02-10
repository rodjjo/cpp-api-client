cmake_minimum_required (VERSION 2.6)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build/bin)

project (ApiTool C CXX)
add_subdirectory("api_tool")
