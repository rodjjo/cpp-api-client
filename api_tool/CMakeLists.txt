file(GLOB Sources "*.cpp")

add_executable(api-tool ${Sources})

target_include_directories (api-tool PUBLIC ${PROJECT_SOURCE_DIR}/api_client)

target_link_libraries(api-tool
                      api-client
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${OPENSSL_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT})

SET_TARGET_PROPERTIES(api-tool PROPERTIES LINKER_LANGUAGE C)
