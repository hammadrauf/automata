#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libconfig.h>

unsigned int willAccept(config_setting_t *transition, const char *input) {
    config_setting_t *accepts = config_setting_lookup(transition, "accepts");
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

bool isValid(config_t *cfg, const char *start, const char *input) {
    char path[80] = "automaton.nodes.";
    strcat(path, start);

    config_setting_t *cur_node = config_lookup(cfg, path);
    if(cur_node == NULL) {
        fprintf(stderr, "Couldn't find node %s", start);
        return false;
    }

    int end_node = false;
    config_setting_lookup_bool(cur_node, "accepted", &end_node);
    if(end_node && input[0] == '\0') return true;

    config_setting_t *trans = config_setting_lookup(cur_node, "transitions");
    if(trans == NULL) return false;

    int num_paths = config_setting_length(trans);
    int i;
    for(i = 0; i < num_paths; ++i) {
        config_setting_t *cur_path = config_setting_get_elem(trans, i);
        unsigned int wa = willAccept(cur_path, input);
        if(wa) {
            const char *next_input = (wa == 1) ? input + 1 : input;
            const char *next_start;
            config_setting_lookup_string(cur_path, "to", &next_start);
            bool next = isValid(cfg, next_start, next_input);
            if(next) return true;
        }
    }

    return false;
}

int to_dot(config_t *cfg, const char *start, char *dest) {
    const char *fmt_str = "digraph automaton {\n"
                           "\tgraph [rankdir=LR];\n\tstart [shape=plaintext];\n"
                           "\tstart -> %s;\n"; // start_node
    // strcat(dest, "digraph automaton {\n");

    config_setting_t *nodes = config_lookup(cfg, "automaton.nodes");
    int node_count = config_setting_length(nodes);
    int i;

    // strcat(dest, "\tgraph [rankdir=LR];\n\tstart [shape=plaintext];\n\tstart -> ");
    const char *start_node;
    config_lookup_string(cfg, "automaton.start", &start_node);
    // strcat(dest, start_node);
    // strcat(dest, "\n");

    char test_fmt[1024];
    snprintf(test_fmt, 1024, fmt_str, start_node);

    for(i = 0; i < node_count; ++i) {
        config_setting_t *cur_node = config_setting_get_elem(nodes, i);
        if(cur_node == NULL) {
            fprintf(stderr, "Couldn't find node %s", start);
            return false;
        }

        config_setting_t *trans = config_setting_lookup(cur_node, "transitions");
        if(trans == NULL) return false;

        int num_paths = config_setting_length(trans);
        int j;
        char loop_fmt_str[256] = "\t%s%s%s -> %s [label=\"%s\"];\n";
        for(j = 0; j < num_paths; ++j) {
            config_setting_t *cur_path = config_setting_get_elem(trans, j);
            const char *next_start;
            config_setting_lookup_string(cur_path, "to", &next_start);

            int accepted_state;
            config_setting_lookup_bool(cur_node, "accepted", &accepted_state);
            char cur_node_txt[32] = {0}, cur_node_shape[32] = {0};
            strcpy(cur_node_txt, config_setting_name(cur_node));
            if(accepted_state) {
                strcpy(cur_node_shape, " [shape=doublecircle];\n\t");
            }

            config_setting_t *accepted = config_setting_lookup(cur_path, "accepts");
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
            char loop_fmt[256];
            snprintf(loop_fmt, 256, loop_fmt_str, accepted_state ? cur_node_txt : "", cur_node_shape, cur_node_txt, next_start, label);
            strcat(test_fmt, loop_fmt);
            free(label);
        }
    }

    strcat(test_fmt, "}\n");

    strcpy(dest, test_fmt);

    return 0;
}

void help_message(char *name) {
    printf("%s %s %s\n", "Usage: ", name, "[FILE] [--run|--graph]");
}

int main(int argc, char **argv) {
    if(argc != 3 || (strcmp(argv[2], "--run") != 0 && strcmp(argv[2], "--graph") != 0)) {
        help_message(argv[0]);
        return -1;
    }

    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, argv[1])) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    const char *start_node;
    if(!config_lookup_string(&cfg, "automaton.start", &start_node)) return(EXIT_FAILURE);

    if(strcmp(argv[2], "--run") == 0) {
        char input[80];
        scanf("%79[^\n]%*c", input);

        bool accepted = isValid(&cfg, start_node, input);
        printf("%s\n", accepted ? "accepted" : "not accepted");
    } else if(strcmp(argv[2], "--graph") == 0) {
        char *dest = (char *)calloc(1024, sizeof(char));
        to_dot(&cfg, start_node, dest);
        printf("%s", dest);
        free(dest);
    }

    config_destroy(&cfg);
    return 0;
}
