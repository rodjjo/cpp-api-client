file(GLOB Sources "*.cc")
file(GLOB Testing "test/*.cc")
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_library(api-client STATIC ${Sources})


add_executable(apiclienttest ${Sources} ${Testing})

target_link_libraries(apiclienttest
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )

add_test(NAME apiclient COMMAND apiclienttest)

SET_TARGET_PROPERTIES(api-client PROPERTIES LINKER_LANGUAGE C)