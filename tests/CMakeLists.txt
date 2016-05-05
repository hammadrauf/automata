set(TEST_SRCS test_example1.c)

add_executable (unit_test test.c ${TEST_SRCS})

target_link_libraries(unit_test ${LIBCONFIG_LIBRARIES} automata_incl)
