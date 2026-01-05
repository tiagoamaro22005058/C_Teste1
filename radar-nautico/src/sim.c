#include <stdlib.h>

#include "collision.h"
#include "sim.h"
#include "util.h"

int sim_advance_frame(const Frame *current, const RadarConfig *cfg, Frame *next) {
    if (current == NULL || cfg == NULL || next == NULL) {
        return 1;
    }

    next->numero = current->numero + 1;
    next->entidades = entidade_clone_list(current->entidades);
    if (current->entidades != NULL && next->entidades == NULL) {
        return 1;
    }

    sim_apply_movements(next->entidades, cfg);
    sim_remove_out_of_bounds(&next->entidades, cfg);
    collision_resolve(&next->entidades);

    return 0;
}

void sim_apply_movements(EntidadeIED *list, const RadarConfig *cfg) {
    EntidadeIED *iter = list;

    if (cfg == NULL) {
        return;
    }

    while (iter != NULL) {
        int dx = 0;
        int dy = 0;
        util_angle_to_delta(iter->ang, iter->vel, &dx, &dy);
        iter->x += dx;
        iter->y += dy;
        iter = iter->next;
    }
}

void sim_remove_out_of_bounds(EntidadeIED **list, const RadarConfig *cfg) {
    EntidadeIED *current = NULL;
    EntidadeIED *prev = NULL;

    if (list == NULL || cfg == NULL) {
        return;
    }

    current = *list;
    while (current != NULL) {
        if (util_is_out_of_bounds(current->x, current->y, cfg)) {
            EntidadeIED *to_remove = current;
            if (prev == NULL) {
                *list = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_remove);
            continue;
        }
        prev = current;
        current = current->next;
    }
}
