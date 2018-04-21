cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)

project(ApiClient C CXX)

find_package(Threads)
find_package(OpenSSL)
find_package(Boost
            COMPONENTS
            system
            filesystem
            unit_test_framework
            thread
            REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_check_modules(JSONCPP jsoncpp)
include_directories("${JSONCPP_INCLUDE_DIRS}")
link_libraries(${JSONCPP_LIBRARIES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

include_directories(ApiClient ${PROJECT_SOURCE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

set(PLATFORM_SPECIFIC_LIBS "-lpthread")

enable_testing()

include(CppLint)

add_subdirectory("api_client")
add_subdirectory("api_tool")

file(GLOB LintSources
    "api_client/*.h"
    "api_client/*.cpp"
    "api_client/apiclient/*.h"
    "api_client/test/*.h"
    "api_client/test/*.cpp"
    "api_tool/*.cpp"
    "api_tool/*.h")


add_style_check_target(lint "${LintSources}")
