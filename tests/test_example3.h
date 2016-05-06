#ifndef TEST_EX_3_H
#define TEST_EX_3_H

#include <automata.h>
#include <libconfig.h>
#include "minunit.h"

MU_TEST(example3_a) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example3.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example3.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert(!acc, "'a' accepted as input by example 3");
}

MU_TEST(example3_ab) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example3.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example3.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "ab");

    config_destroy(&cfg);
    mu_assert(!acc, "'ab' accepted as input by example 3");
}

MU_TEST(example3_b) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example3.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example3.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "b");

    config_destroy(&cfg);
    mu_assert(acc, "'b' not accepted as input by example 3");
}

MU_TEST(example3_ba) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example3.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example3.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "ba");

    config_destroy(&cfg);
    mu_assert(acc, "'ba' not accepted as input by example 3");
}

MU_TEST(example3_aba) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example3.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example3.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "b");

    config_destroy(&cfg);
    mu_assert(acc, "'aba' not accepted as input by example 3");
}

MU_TEST_SUITE(example3) {
    MU_RUN_TEST(example3_a);
    MU_RUN_TEST(example3_ab);
    MU_RUN_TEST(example3_b);
    MU_RUN_TEST(example3_ba);
    MU_RUN_TEST(example3_aba);
}

#endif /* TEST_EX_3_H */
