file(GLOB Sources "*.cc")

add_executable(ApiTool ${Sources})

SET_TARGET_PROPERTIES(ApiTool PROPERTIES LINKER_LANGUAGE C)