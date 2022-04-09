#ifndef TEST_EX_1_H
#define TEST_EX_1_H

#include <automata.h>
#include <libconfig.h>
#include <stdio.h>
#include "minunit.h"

MU_TEST(example1_a) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example1.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert(acc, "'a' not accepted as input by example 1");
}

MU_TEST(example1_b) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example1.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "b");

    config_destroy(&cfg);
    mu_assert(acc, "'b' not accepted as input by example 1");
}

MU_TEST(example1_blank) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example1.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "");

    config_destroy(&cfg);
    mu_assert(!acc, "Empty string accepted as input by example 1");
}

MU_TEST(example1_longer) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example1.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example1.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aabababababababababa");

    config_destroy(&cfg);
    mu_assert(acc, "'aabababababababababa' not accepted as input by example 1");
}

MU_TEST_SUITE(example1) {
    MU_RUN_TEST(example1_a);
    MU_RUN_TEST(example1_b);
    MU_RUN_TEST(example1_blank);
    MU_RUN_TEST(example1_longer);
}

#endif /* TEST_EX_1_H */
