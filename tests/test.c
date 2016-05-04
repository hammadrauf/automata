#include <automata.h>
#include <libconfig.h>
#include <stdio.h>
#include "minunit.h"

int tests_run = 0;

// int foo = 7;
// int bar = 4;

// static char * test_foo() {
//     mu_assert("error, foo != 7", foo == 7);
//     return 0;
// }
//
// static char * test_bar() {
//     mu_assert("error, bar != 5", bar == 5);
//     return 0;
// }
//

static const char *test_example_1() {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        // fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
        //         config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return config_error_text(&cfg);
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert("error, 'a' not accepted as input", acc);

    return 0;
}

static char *all_tests() {
    // mu_run_test(test_foo);
    // mu_run_test(test_bar);
    mu_run_test(test_example_1);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
