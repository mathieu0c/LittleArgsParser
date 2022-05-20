# set(BINARY ${CMAKE_PROJECT_NAME})

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES_SRC 
    Log.hpp
    LAPTypes.hpp LAPTypes.cpp
    LAPParser.hpp LAPParser.cpp
)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES_SRC})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wno-string-plus-int)

#----- Used to get the current filename

# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-D_FILE_=(__FILE__ + ${SOURCE_PATH_SIZE})")