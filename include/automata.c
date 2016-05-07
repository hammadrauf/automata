#include "automata.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libconfig.h>
#include <math.h>

unsigned int can_transition(config_t *cfg, const char *path, const char *input) {
    config_setting_t *accepts = config_lookup(cfg, path);
    int length = config_setting_length(accepts);
    int i;
    for(i = 0; i < length; ++i) {
        const char *cur = config_setting_get_string_elem(accepts, i);
        if(*cur == input[0]) {
            return 1;
        } else if(*cur == '~') {
            return 2;
        }
    }

    return 0;
}

bool automata_is_accepted(config_t *cfg, const char *start, const char *input) {
    // char path[160] = "automaton.nodes."; // 16 chars
    /** Allocate memory for:
      * "automaton.nodes."
      * The string length of start
      * \0
     **/
    size_t path_len = 16 + 12 + strlen(start);
    char *path = (char *)calloc(path_len + 1, sizeof(char));
    snprintf(path, path_len, "automaton.nodes.%s", start);
    // strcat(path, start); // arbitrary

    config_setting_t *cur_node = config_lookup(cfg, path);
    if(cur_node == NULL) {
        free(path);
        fprintf(stderr, "Couldn't find node %s", start);
        return false;
    }

    int end_node = false;
    config_setting_lookup_bool(cur_node, "accepted", &end_node);
    if(end_node && input[0] == '\0') {
        free(path);
        return true;
    }

    // config_setting_t *trans = config_setting_lookup(cur_node, "transitions");
    // char trans_path[171];
    // snprintf(trans_path, 171, "%s.transitions", path); // 11 chars
    strcat(path, ".transitions");
    config_setting_t *trans = config_lookup(cfg, path);
    if(trans == NULL) {
        free(path);
        return false;
    }

    bool any_path_found = false;

    int num_paths = config_setting_length(trans);

    // printf("\n===\n%d\n===\n", num_paths);

    int i;
    #pragma omp parallel for private(i)
    for(i = 0; i < num_paths; ++i) {
        #pragma omp flush(any_path_found)
        if(!any_path_found) {
            config_setting_t *cur_path = config_setting_get_elem(trans, i);
            // char cur_path_str[200];
            // snprintf(cur_path_str, 200, "%s.[%d].accepts", trans_path, i); // 8 chars + digit length (floor(log10(abs(the_integer))) + 1)
            int digit_len = (i == 0) ? 1 : floor(log10(abs(i))) + 1;
            /** Allocate memory for:
              * ".[].accepts"
              * The string length of i
              * The length of the current path
              * \0
             **/
            size_t cur_path_len = path_len + 12 + digit_len;
            char *cur_path_str = (char *)calloc(cur_path_len + 1, sizeof(char));
            snprintf(cur_path_str, cur_path_len, "%s.[%d].accepts", path, i);
            unsigned int ct = can_transition(cfg, cur_path_str, input);
            free(cur_path_str);
            if(ct) {
                const char *next_input = (ct == 1) ? input + 1 : input;
                const char *next_start;
                config_setting_lookup_string(cur_path, "to", &next_start);
                bool next = automata_is_accepted(cfg, next_start, next_input);
                if(next) {
                    any_path_found = true;
                    #pragma omp flush(any_path_found)
                }
            }
        }
    }

    free(path);

    return any_path_found;
}

int automata_to_dot(config_t *cfg, const char *start, char *dest, int dest_size) {
    // char path[80] = "automaton.nodes.";
    // strcat(path, start);
    const char *fmt_str = "digraph automaton {\n"
                           "\tgraph [rankdir=LR];\n\tstart [shape=plaintext];\n"
                           "\tstart -> %s;\n"; // start_node

    config_setting_t *nodes = config_lookup(cfg, "automaton.nodes");
    int node_count = config_setting_length(nodes);

    const char *start_node;
    config_lookup_string(cfg, "automaton.start", &start_node);

    int cur_length = snprintf(dest, dest_size, fmt_str, start_node);

    int i;
    for(i = 0; i < node_count; ++i) {
        config_setting_t *cur_node = config_setting_get_elem(nodes, i);
        if(cur_node == NULL) {
            fprintf(stderr, "Couldn't find node %s", start);
            return false;
        }

        // config_setting_t *trans = config_setting_lookup(cur_node, "transitions");
        char trans_path[91];
        snprintf(trans_path, 91, "automaton.nodes.[%d].transitions", i);
        config_setting_t *trans = config_lookup(cfg, trans_path);
        if(trans == NULL) return false;

        int accepted_state;
        config_setting_lookup_bool(cur_node, "accepted", &accepted_state);

        char *cur_node_txt = config_setting_name(cur_node);
        const char *cur_node_shape = accepted_state ? " [shape=doublecircle];\n" : "";
        cur_length += snprintf(dest + cur_length, dest_size, "%s%s%s", accepted_state ? "\t" : "", accepted_state ? cur_node_txt : "", cur_node_shape);

        int num_paths = config_setting_length(trans);
        int j;
        const char *loop_fmt_str = "\t%s -> %s [label=\"%s\"];\n";
        for(j = 0; j < num_paths; ++j) {
            config_setting_t *cur_path = config_setting_get_elem(trans, j);
            const char *next_start;
            config_setting_lookup_string(cur_path, "to", &next_start);

            char cur_path_str[120];
            snprintf(cur_path_str, 120, "%s.[%d].accepts", trans_path, j);
            config_setting_t *accepted = config_lookup(cfg, cur_path_str);
            if(accepted == NULL) printf("REEEEE\n");
            int num_accepted = config_setting_length(accepted);
            char *label = (char *)calloc(2 * num_accepted, sizeof(char));
            int k;
            for(k = 0; k < num_accepted; ++k) {
                if(k > 0) {
                    strcat(label, ",");
                }

                config_setting_t *cur_acc = config_setting_get_elem(accepted, k);
                strcat(label, config_setting_get_string(cur_acc));
            }

            cur_length += snprintf(dest + cur_length, dest_size, loop_fmt_str, cur_node_txt, next_start, label);
            free(label);
        }
    }

    snprintf(dest + cur_length, dest_size, "}\n");

    return 0;
}
