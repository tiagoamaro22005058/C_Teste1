#include <stdio.h>

#include "cli.h"
#include "history.h"
#include "io.h"
#include "sim.h"
#include "util.h"

int cli_run(Frame *current, BaseDados **history, const RadarConfig *cfg, FILE *out) {
    int option = -1;

    if (current == NULL || history == NULL || cfg == NULL || out == NULL) {
        return 1;
    }

    while (scanf("%d", &option) == 1) {
        if (option == 0) {
            return 0;
        }
        if (option == 1) {
            Frame next = {0};
            if (sim_advance_frame(current, cfg, &next) != 0) {
                return 1;
            }
            entidade_free_list(current->entidades);
            current->entidades = next.entidades;
            current->numero = next.numero;
            *history = history_append(*history, current);
            io_write_frame(out, current, cfg);
        }
    }

    return 0;
}
