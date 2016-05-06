#include <automata.h>
#include <libconfig.h>
#include <stdio.h>
#include "minunit.h"
#include "test_example1.h"
#include "test_example2.h"

int main(int argc, char **argv) {
    MU_RUN_SUITE(example_1);
    MU_RUN_SUITE(example_2);
    MU_REPORT();

    return 0;
}
