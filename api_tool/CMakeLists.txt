file(GLOB Sources "*.cc")

add_executable(api-tool ${Sources})

target_include_directories (api-tool PUBLIC ${PROJECT_SOURCE_DIR}/api_client)
target_link_libraries(api-tool api-client)

SET_TARGET_PROPERTIES(api-tool PROPERTIES LINKER_LANGUAGE C)