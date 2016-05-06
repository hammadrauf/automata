#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig.h>
#include "automata.h"

void help_message(char *name) {
    printf("%s %s %s\n", "Usage: ", name, "[FILE] [--run|--graph]");
}

int main(int argc, char **argv) {
    if(argc != 3 || (strcmp(argv[2], "--run") != 0 && strcmp(argv[2], "--graph") != 0)) {
        help_message(argv[0]);
        return 0;
    }

    config_t cfg;
    config_init(&cfg);

    FILE *fp = fopen(argv[1], "r");

    if(!config_read(&cfg, fp)) {
        fprintf(stderr, "%d - %s\n", config_error_line(&cfg),
                                     config_error_text(&cfg));
        config_destroy(&cfg);
        fclose(fp);
        return(EXIT_FAILURE);
    }

    fseek(fp, 0L, SEEK_END);
    unsigned long sz = ftell(fp);

    fclose(fp);

    const char *start_node;
    if(!config_lookup_string(&cfg, "automaton.start", &start_node)) return(EXIT_FAILURE);

    if(strcmp(argv[2], "--run") == 0) {
        char input[80];
        scanf("%79[^\n]%*c", input);

        bool accepted = automata_is_accepted(&cfg, start_node, input);
        printf("%s\n", accepted ? "accepted" : "not accepted");
    } else if(strcmp(argv[2], "--graph") == 0) {
        // char dest[sz] = {0};
        char *dest = (char *)calloc(sz, sizeof(char));
        automata_to_dot(&cfg, start_node, dest, sz);
        printf("%s", dest);
        free(dest);
    }

    config_destroy(&cfg);
    return 0;
}
