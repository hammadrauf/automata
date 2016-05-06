#ifndef TEST_EX_5_H
#define TEST_EX_5_H

#include <automata.h>
#include <libconfig.h>
#include "minunit.h"

MU_TEST(example5_aaaaab) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example5.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example5.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aaaaab");

    config_destroy(&cfg);
    mu_assert(acc, "'aaaaab' not accepted as input by example 5");
}

MU_TEST(example5_aaaaaa) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example5.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example5.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "aaaaaa");

    config_destroy(&cfg);
    mu_assert(!acc, "'aaaaaa' accepted as input by example 5");
}

MU_TEST(example5_a) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example5.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example5.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "a");

    config_destroy(&cfg);
    mu_assert(!acc, "'a' accepted as input by example 5");
}

MU_TEST(example5_bbbbbb) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../examples/example5.aut")) {
        config_destroy(&cfg);
        mu_fail("Could not read example5.aut");
    }

    bool acc = automata_is_accepted(&cfg, "q_0", "bbbbbb");

    config_destroy(&cfg);
    mu_assert(!acc, "'bbbbbb' accepted as input by example 5");
}

MU_TEST_SUITE(example5) {
    MU_RUN_TEST(example5_aaaaab);
    MU_RUN_TEST(example5_aaaaaa);
    MU_RUN_TEST(example5_a);
    MU_RUN_TEST(example5_bbbbbb);
}



#endif /* TEST_EX_5_H */
