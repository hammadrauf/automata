cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Automata")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig)

include_directories(${LIBCONFIG_INCLUDE_DIRS})
link_directories(${LIBCONFIG_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${LIBCONFIG_CFLAGS_OTHER})
# Add an executable compiled from main.c

add_executable(automata main.c)

# Link the target to the GTK+ libraries
target_link_libraries(automata ${LIBCONFIG_LIBRARIES})
