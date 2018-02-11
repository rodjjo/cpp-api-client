file(GLOB Sources "*.cc")

add_executable(api-tool ${Sources})

target_link_libraries(api-tool api-client)

SET_TARGET_PROPERTIES(api-tool PROPERTIES LINKER_LANGUAGE C)