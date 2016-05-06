#ifndef TEST_EX_4_H
#define TEST_EX_4_H

#include <automata.h>
#include <libconfig.h>
#include "minunit.h"

MU_TEST(example4_aaaa) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example4.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example4.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aaaa");

    config_destroy(&cfg);
    mu_assert(acc, "'aaaa' not accepted as input by example 4");
}

MU_TEST(example4_bbbb) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example4.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example4.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "bbbb");

    config_destroy(&cfg);
    mu_assert(acc, "'bbbb' not accepted as input by example 4");
}

MU_TEST(example4_a) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example4.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example4.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert(!acc, "'a' accepted as input by example 4");
}

MU_TEST(example4_aa) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example4.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example4.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aa");

    config_destroy(&cfg);
    mu_assert(!acc, "'aa' accepted as input by example 4");
}

MU_TEST(example4_aaa) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example4.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example4.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aaa");

    config_destroy(&cfg);
    mu_assert(!acc, "'aaa' accepted as input by example 4");
}



MU_TEST_SUITE(example4) {
    MU_RUN_TEST(example4_aaaa);
    MU_RUN_TEST(example4_bbbb);
    MU_RUN_TEST(example4_a);
    MU_RUN_TEST(example4_aa);
    MU_RUN_TEST(example4_aaa);
}

#endif /* TEST_EX_4_H */
