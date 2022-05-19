# set(BINARY ${CMAKE_PROJECT_NAME})

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES_SRC 
    Log.hpp
    LAPTypes.hpp LAPTypes.cpp
    LAPParser.hpp LAPParser.cpp
)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SOURCES_SRC})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# target_link_libraries(${CMAKE_PROJECT_NAME} CustomPerfTools)
