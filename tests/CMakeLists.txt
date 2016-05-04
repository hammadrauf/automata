# enable_testing()
#
# add_test(NoArguments automata)
# set_tests_properties(NoArguments
# PROPERTIES PASS_REGULAR_EXPRESSION "Usage: *")
#
# add_test(Example1 automata)
# set_tests_properties(NoArguments
# PROPERTIES PASS_REGULAR_EXPRESSION "Usage: *")

# include_directories("${CMAKE_SOURCE_DIR}/include")
# add_library(automata_incl "${CMAKE_SOURCE_DIR}/include/automata.c")

# include_directories(${LIBCONFIG_INCLUDE_DIRS})
# link_directories(${LIBCONFIG_LIBRARY_DIRS})

add_executable (unit_test test.c)

target_link_libraries(unit_test ${LIBCONFIG_LIBRARIES} automata_incl)

# enable_testing()
