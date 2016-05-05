#include "test_example1.h"

static char *test_example_1_a() {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        return (char *)config_error_text(&cfg);
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert((char *)"error, 'a' not accepted as input by example 1", acc);

    return 0;
}

static char *test_example_1_b() {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        return (char *)config_error_text(&cfg);
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "b");

    config_destroy(&cfg);
    mu_assert((char *)"error, 'b' not accepted as input by example 1", acc);

    return 0;
}

static char *test_example_1_blank() {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        return (char *)config_error_text(&cfg);
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "");

    config_destroy(&cfg);
    mu_assert((char *)"error, empty string accepted as input by example 1", !acc);

    return 0;
}

static char *test_example_1_longer() {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        return (char *)config_error_text(&cfg);
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aabababababababababa");

    config_destroy(&cfg);
    mu_assert((char *)"error, 'aabababababababababa' not accepted as input by example 1", acc);

    return 0;
}

char *example1() {
    mu_run_test(test_example_1_a);
    mu_run_test(test_example_1_b);
    mu_run_test(test_example_1_blank);
    mu_run_test(test_example_1_longer);
    return 0;
}
