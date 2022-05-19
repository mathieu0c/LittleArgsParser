cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME_CUSTOM LittleArgsParser)
project(${PROJECT_NAME_CUSTOM} VERSION 0.1.0)
set(PROJECT_EXE_NAME ${CMAKE_PROJECT_NAME}_bin)

set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    add_compile_definitions(COMPILE_DEBUG)
    message("debug mode")
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

# add_subdirectory(Src/PerfTools)
add_subdirectory(Src)

add_executable(${PROJECT_EXE_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_EXE_NAME} ${CMAKE_PROJECT_NAME})



set(CPACK_PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(Tests)