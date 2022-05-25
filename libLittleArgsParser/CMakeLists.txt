cmake_minimum_required(VERSION 3.13...3.19 FATAL_ERROR)
project(libLittleArgsParser VERSION 1.0.0 LANGUAGES CXX)

#Make sure that custom modules like FindRapidJSON are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Find system dependencies
set(CMAKE_CXX_STANDARD 20)

##############################################
# Create target and set properties

add_library(littleArgsParser
    Src/LittleArgsParser.cpp
    Src/LAPTypes.cpp
    Src/LAPParser.hpp Src/LAPParser.cpp
    Src/LAPHelper.cpp
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(LittleArgsParser::LittleArgsParser ALIAS littleArgsParser)

#Set target properties
target_include_directories(littleArgsParser
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(littleArgsParser PRIVATE cxx_auto_type)
target_compile_options(littleArgsParser PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic>)

# target_link_libraries(littleArgsParser
#     PUBLIC
#         RapidJSON::RapidJSON
# )

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/LittleArgsParser)

install(TARGETS littleArgsParser
    EXPORT littleArgsParser-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name LittleArgsParser and not littleArgsParser
set_target_properties(littleArgsParser PROPERTIES EXPORT_NAME LittleArgsParser)

install(DIRECTORY Include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT littleArgsParser-targets
    FILE
        LittleArgsParserTargets.cmake
    NAMESPACE
        LittleArgsParser::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LittleArgsParserConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/LittleArgsParserConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/LittleArgsParserConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
#    ${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/LittleArgsParserConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/LittleArgsParserConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
# configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#     ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#     COPYONLY)

export(EXPORT littleArgsParser-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/LittleArgsParserTargets.cmake
    NAMESPACE LittleArgsParser::)

#Register package in the User Package Registry
export(PACKAGE LittleArgsParser)

##############################################
## Add test
enable_testing()
add_subdirectory(Tests)