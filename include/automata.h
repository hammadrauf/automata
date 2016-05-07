#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <math.h>
#include <stdbool.h>
#include <libconfig.h>

bool automata_is_accepted(config_t *cfg, const char *start, const char *input);
int automata_to_dot(config_t *cfg, const char *start, char *dest, int dest_size);

#endif /* AUTOMATA_H */
