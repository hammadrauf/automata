cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project("automata")
set(automata_VERSION "1.0.1")
set(automata_VERSION_MAJOR "1")
set(automata_VERSION_MINOR "0")
set(automata_VERSION_PATCH "1")

# include("tests/CMakeLists.txt")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig)

include_directories("${CMAKE_SOURCE_DIR}/include")
add_library(automata_incl "${CMAKE_SOURCE_DIR}/include/automata.c")

# Add other flags to the compiler
add_definitions(${LIBCONFIG_CFLAGS_OTHER})

message(STATUS "LIBCONFIG LIBRARIES: " ${LIBCONFIG_LIBRARIES})

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# Add an executable compiled from main.c
add_executable(automata main.c)

# Link the target to the config libraries
target_link_libraries(automata ${LIBCONFIG_LIBRARIES} automata_incl)

install(TARGETS automata DESTINATION bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE DESTINATION share/licenses/${PROJECT_NAME})

add_subdirectory("tests")
enable_testing()
add_test(Example1 tests/unit_test example1)
add_test(Example2 tests/unit_test example2)
add_test(Example3 tests/unit_test example3)
add_test(Example4 tests/unit_test example4)

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
