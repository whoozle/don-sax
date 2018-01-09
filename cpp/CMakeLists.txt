cmake_minimum_required(VERSION 3.1)

set (JSONWC_SRC
#	src/jsonwc.c
#	jsonwc.lex.c
#	jsonwc.tab.c
	src/jsonwc.cpp
)


set (JSONWC_GRAMMAR_PATH ${CMAKE_CURRENT_BINARY_DIR}/src/grammar)
file(MAKE_DIRECTORY ${JSONWC_GRAMMAR_PATH})

include_directories(src ${CMAKE_CURRENT_BINARY_DIR}/src)

find_program(BISON_PATH bison)
find_program(FLEX_PATH flex)

set(BISON_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/jsonwc.y)
set(FLEX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/jsonwc.yy)
add_custom_command(OUTPUT jsonwc.tab.c
	COMMAND ${BISON_PATH} --defines=jsonwc.tab.h -o jsonwc.tab.c ${BISON_SRC}
	DEPENDS ${BISON_SRC}
	WORKING_DIRECTORY ${JSONWC_GRAMMAR_PATH}
)

add_custom_command(OUTPUT jsonwc.lex.c
	COMMAND ${FLEX_PATH} -f --header-file=jsonwc.lex.h -o jsonwc.lex.c ${FLEX_SRC}
	DEPENDS ${FLEX_SRC}
	WORKING_DIRECTORY ${JSONWC_GRAMMAR_PATH}
)
add_library(jsonwc STATIC ${JSONWC_SRC})
