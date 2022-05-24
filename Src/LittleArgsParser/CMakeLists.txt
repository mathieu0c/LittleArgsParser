# set(BINARY ${CMAKE_PROJECT_NAME})

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES_SRC
    LAPTypes.hpp LAPTypes.cpp
    LAPParser.hpp LAPParser.cpp
    LAPHelper.hpp LAPHelper.cpp
)

set(LITTLE_ARGS_PARSER_LIB_NAME LittleArgsParser)

add_library(${LITTLE_ARGS_PARSER_LIB_NAME} STATIC ${SOURCES_SRC})
set_target_properties(${LITTLE_ARGS_PARSER_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(${LITTLE_ARGS_PARSER_LIB_NAME} PRIVATE -Wno-string-plus-int)

#----- Used to get the current filename

# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-D_FILE_=(__FILE__ + ${SOURCE_PATH_SIZE})")
#test