cmake_minimum_required(VERSION 3.1)

option(BUILD_TEST "build test app" BUILD_TEST)

set (JSONWC_GRAMMAR_PATH ${CMAKE_CURRENT_BINARY_DIR}/src/grammar)
file(MAKE_DIRECTORY ${JSONWC_GRAMMAR_PATH})

include_directories(src ${CMAKE_CURRENT_BINARY_DIR}/src)

find_program(BISON_PATH bison)
set(BISON_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/jsonwc.y)
add_custom_command(OUTPUT ${JSONWC_GRAMMAR_PATH}/jsonwc.tab.cpp jsonwc.tab.h
	COMMAND ${BISON_PATH} --defines=jsonwc.tab.h -o jsonwc.tab.cpp ${BISON_SRC}
	DEPENDS ${BISON_SRC}
	WORKING_DIRECTORY ${JSONWC_GRAMMAR_PATH}
)

find_program(FLEX_PATH flex)
set(FLEX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/jsonwc.yy)
add_custom_command(OUTPUT ${JSONWC_GRAMMAR_PATH}/jsonwc.lex.cpp ${JSONWC_GRAMMAR_PATH}/jsonwc.lex.h
	COMMAND ${FLEX_PATH} --header-file=jsonwc.lex.h -o jsonwc.lex.cpp ${FLEX_SRC}
	DEPENDS ${FLEX_SRC}
	WORKING_DIRECTORY ${JSONWC_GRAMMAR_PATH}
)


set (JSONWC_SRC
	${JSONWC_GRAMMAR_PATH}/jsonwc.lex.cpp
	${JSONWC_GRAMMAR_PATH}/jsonwc.tab.cpp
	src/grammar/jsonwc.parser.cpp
	src/jsonwc.cpp
)


add_library(jsonwc STATIC ${JSONWC_SRC})

if (BUILD_TEST)
	add_executable(jsonwc-test test/test.cpp)
	target_link_libraries(jsonwc-test jsonwc)
endif()