cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project("automata")
set(automata_VERSION "1.0.1")
set(automata_VERSION_MAJOR "1")
set(automata_VERSION_MINOR "0")
set(automata_VERSION_PATCH "1")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig)

include_directories(${LIBCONFIG_INCLUDE_DIRS})
link_directories(${LIBCONFIG_LIBRARY_DIRS})

# Add other flags to the compiler
add_definitions(${LIBCONFIG_CFLAGS_OTHER})

# Add an executable compiled from main.c
add_executable(automata main.c)

# Link the target to the config libraries
target_link_libraries(automata ${LIBCONFIG_LIBRARIES})

install(TARGETS automata DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE DESTINATION share/licenses/${PROJECT_NAME})

# Taken from CMake wiki
# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# CPack Configuration
    set(CPACK_PACKAGE_NAME "Automata")
    set(CPACK_PACKAGE_VENDOR "Colin Atkinson")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A C implementation of finite automata")
    set(CPACK_PACKAGE_VERSION "${automata_VERSION}")
    set(CPACK_PACKAGE_VERSION_MAJOR "${automata_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${automata_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${automata_VERSION_PATCH}")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/.gitignore"
                                  "${CMAKE_CURRENT_SOURCE_DIR}/.git"
                                  "${CMAKE_CURRENT_SOURCE_DIR}/build")

    include(CPack)
