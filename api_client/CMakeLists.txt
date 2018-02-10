file(GLOB Sources "*.cc")

add_library(api-client STATIC ${Sources})

SET_TARGET_PROPERTIES(api-client PROPERTIES LINKER_LANGUAGE C)