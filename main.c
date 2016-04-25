#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libconfig.h>

bool willAccept(config_setting_t *transition, const char *input) {
    config_setting_t *accepts = config_setting_lookup(transition, "accepts");
    int length = config_setting_length(accepts);
    int i;
    for(i = 0; i < length; ++i) {
        const char *cur = config_setting_get_string_elem(accepts, i);
        if(strcmp(cur, "~") == 0 || strcmp(cur, &input[0]) == 0) {
            return true;
        }
    }

    return false;
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
    if(end_node) return true;

    config_setting_t *trans = config_setting_lookup(cur_node, "transitions");
    if(trans == NULL) return false;

    int num_paths = config_setting_length(trans);
    int i;
    for(i = 0; i < num_paths; ++i) {
        config_setting_t *cur_path = config_setting_get_elem(trans, i);
        // printf("%d\n", willAccept(cur_path, input));
        if(willAccept(cur_path, input)) {
            const char *next_input = input + 1;
            const char *next_start;
            config_setting_lookup_string(cur_path, "to", &next_start);
            bool next = isValid(cfg, next_start, next_input);
            if(next) return true;
        }
    }

    return false;
}

int main(int argc, char **argv) {
    config_t cfg;
    config_init(&cfg);

    if(!config_read_file(&cfg, "../sample_automaton.cfg")) {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return(EXIT_FAILURE);
    }

    // const char input[] = {"q"};
    char *input = (char*)malloc(80*sizeof(char));
    scanf("%80s", input);

    const char *start_node;
    if(!config_lookup_string(&cfg, "automaton.start", &start_node)) return(EXIT_FAILURE);

    bool accepted = isValid(&cfg, start_node, input);
    printf("%s\n", accepted ? "accepted" : "not accepted");


    return 0;
}
