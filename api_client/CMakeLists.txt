file(GLOB Sources "*.cc")
file(GLOB Testing "test/*.cc")
set(APICLIENT_HEADERS "apiclient.h")

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_library(api-client STATIC ${Sources})

install(TARGETS api-client
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        COMPONENT library)

install(FILES ${APICLIENT_HEADERS} 
        DESTINATION include/apiclient)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(apiclienttest ${Sources} ${Testing})

add_test(NAME apiclient COMMAND apiclienttest)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_EXCLUDES '/usr/*' '*/test/*')
    setup_target_for_coverage(NAME apiclient_coverage EXECUTABLE apiclienttest)
endif()

target_link_libraries(apiclienttest
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      gcov
                      )

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(apiclienttest gcov)
endif()

SET_TARGET_PROPERTIES(api-client PROPERTIES LINKER_LANGUAGE C)
