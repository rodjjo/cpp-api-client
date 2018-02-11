file(GLOB Sources "*.cc")

add_executable(api-tool ${Sources})

SET_TARGET_PROPERTIES(api-tool PROPERTIES LINKER_LANGUAGE C)