#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <stdbool.h>
#include <libconfig.h>

#if LIBCONFIG_VER_MAJOR >= 1 && LIBCONFIG_VER_MINOR < 5
config_setting_t * config_setting_lookup (const config_setting_t * setting, const char * path) {
    return config_setting_lookup_from(setting, path);
}
#endif

bool automata_is_accepted(config_t *cfg, const char *start, const char *input);
int automata_to_dot(config_t *cfg, const char *start, char *dest, int dest_size);

#endif /* AUTOMATA_H */
