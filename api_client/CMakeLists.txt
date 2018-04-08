file(GLOB Sources "*.cpp")
file(GLOB Testing "test/*.cpp" "test/mocks/*.cpp")
set(APICLIENT_HEADERS "apiclient/apiclient.h")

add_library(api-client STATIC ${Sources})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(apiclienttest ${Testing} ${Sources})

add_test(NAME apiclient COMMAND apiclienttest)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage(NAME coverage EXECUTABLE apiclienttest)
    # APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_EXCLUDES '/usr/*' '*/test/*')
endif()

target_link_libraries(apiclienttest
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      gcov
                      ${CMAKE_THREAD_LIBS_INIT}
                      )

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(apiclienttest gcov)
endif()

SET_TARGET_PROPERTIES(api-client PROPERTIES LINKER_LANGUAGE C)
set_target_properties(apiclienttest PROPERTIES COMPILE_DEFINITIONS "UNIT_TEST=1")

install(TARGETS api-client
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        COMPONENT library)

install(FILES ${APICLIENT_HEADERS}
        DESTINATION include/apiclient)
