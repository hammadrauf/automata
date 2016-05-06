#include <automata.h>
#include <libconfig.h>
#include <stdio.h>
#include "minunit.h"
#include "test_example1.h"
#include "test_example2.h"
#include "test_example3.h"
#include "test_example4.h"

int main(int argc, char **argv) {
    if(argc == 1 || (argc == 2 && strcmp(argv[1], "all") == 0)) {
        MU_RUN_SUITE(example1);
        MU_RUN_SUITE(example2);
        MU_RUN_SUITE(example3);
        MU_RUN_SUITE(example4);
    }

    if(argc == 2) {
        if(strcmp(argv[1], "example1") == 0) {
            MU_RUN_SUITE(example1);
        } else if(strcmp(argv[1], "example2") == 0) {
            MU_RUN_SUITE(example2);
        } else if(strcmp(argv[1], "example3") == 0) {
            MU_RUN_SUITE(example3);
        } else if(strcmp(argv[1], "example4") == 0) {
            MU_RUN_SUITE(example4);
        }
    }

    MU_REPORT();

    return 0;
}
