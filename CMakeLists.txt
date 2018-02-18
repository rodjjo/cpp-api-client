cmake_minimum_required (VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

project(ApiClient C CXX)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories("${JSONCPP_INCLUDE_DIRS}")
link_libraries(${JSONCPP_LIBRARIES})

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
    "api_client/*.cpp"
    "api_client/*.h"
    "api_client/apiclient/*.h"
    "api_client/test/*.h"
    "api_client/test/*.cpp"
    "api_tool/*.cpp"
    "api_tool/*.h")

add_style_check_target(apiclient_lint ${LintSources})
