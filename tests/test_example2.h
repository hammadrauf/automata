#ifndef TEST_EX_2_H
#define TEST_EX_2_H

#include <automata.h>
#include <libconfig.h>
#include "minunit.h"

MU_TEST(example_2_aa) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example2.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example2.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aa");

    config_destroy(&cfg);
    mu_assert(acc, "'aa' not accepted as input by example 2");
}

MU_TEST(example_2_aba) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example2.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example2.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aba");

    config_destroy(&cfg);
    mu_assert(acc, "'aba' not accepted as input by example 2");
}

MU_TEST(example_2_abbbbbba) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example2.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example2.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "abbbbbba");

    config_destroy(&cfg);
    mu_assert(acc, "'abbbbbba' not accepted as input by example 2");
}

MU_TEST(example_2_a) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example2.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example2.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert(!acc, "'a' accepted as input by example 2");
}

MU_TEST(example_2_ab) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example2.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example2.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "ab");

    config_destroy(&cfg);
    mu_assert(!acc, "'ab' accepted as input by example 2");
}

MU_TEST(example_2_ba) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example2.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example2.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "ba");

    config_destroy(&cfg);
    mu_assert(!acc, "'ba' accepted as input by example 2");
}

MU_TEST_SUITE(example_2) {
    MU_RUN_TEST(example_2_aa);
    MU_RUN_TEST(example_2_aba);
    MU_RUN_TEST(example_2_abbbbbba);
    MU_RUN_TEST(example_2_a);
    MU_RUN_TEST(example_2_ab);
    MU_RUN_TEST(example_2_ba);
}

#endif /* TEST_EX_2_H */
