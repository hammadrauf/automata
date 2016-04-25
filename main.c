#include <stdio.h>
#include <stddef.h>
#include <libconfig.h>

typedef struct {
    int accepts;
    struct state *dest;
} transition_t;

typedef struct state {
    int n;
    int num_transitions;
    transition_t *trans;
} state_t;

state_t *parseBin(int binl, char *bin) {
    state_t *head = NULL;
    int start = 0;
    int end = 0;

    while(end < binl) {
        for(int i = start; i < binl; ++i) {
            if(bin[i] == '0' && i + 1 < binl && bin[i + 1] == '0') {
                end = i;
                break;
            }
        }
    }

    return head;
}

int main(int argc, char **argv) {
    return 0;
}
