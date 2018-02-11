cmake_minimum_required (VERSION 2.6)

project(ApiClient C CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

include_directories(ApiClient)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

enable_testing()

include(CppLint)

add_subdirectory("api_client")
add_subdirectory("api_tool")

file(GLOB LintSources 
    "ap_client/*.cpp" 
    "ap_client/*.h" 
    "ap_client/apiclient/*.h" 
    "ap_client/test/*.h" 
    "ap_client/test/*.cpp" 
    "api_tool/*.cpp" 
    "api_tool/*.h")

add_style_check_target(apiclient_lint ${LintSources})