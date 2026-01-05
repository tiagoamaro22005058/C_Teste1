#include <stdlib.h>

#include "collision.h"

int entidade_has_collision(const EntidadeIED *list, const EntidadeIED *target) {
    int count = 0;
    const EntidadeIED *iter = list;

    while (iter != NULL) {
        if (iter->x == target->x && iter->y == target->y) {
            count++;
            if (count > 1) {
                return 1;
            }
        }
        iter = iter->next;
    }

    return 0;
}

void collision_resolve(EntidadeIED **list) {
    EntidadeIED *current = NULL;
    EntidadeIED *prev = NULL;

    if (list == NULL) {
        return;
    }

    current = *list;
    while (current != NULL) {
        if (entidade_has_collision(*list, current)) {
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
