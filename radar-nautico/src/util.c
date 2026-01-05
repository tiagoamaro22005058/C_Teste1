#include <stdlib.h>
#include <string.h>

#include "util.h"

EntidadeIED *entidade_clone_list(const EntidadeIED *src) {
    EntidadeIED *head = NULL;
    EntidadeIED *tail = NULL;

    while (src != NULL) {
        EntidadeIED *node = malloc(sizeof(*node));
        if (node == NULL) {
            entidade_free_list(head);
            return NULL;
        }
        memcpy(node, src, sizeof(*node));
        node->next = NULL;
        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        src = src->next;
    }

    return head;
}

void entidade_free_list(EntidadeIED *list) {
    while (list != NULL) {
        EntidadeIED *next = list->next;
        free(list);
        list = next;
    }
}

int util_is_out_of_bounds(int x, int y, const RadarConfig *cfg) {
    if (cfg == NULL) {
        return 1;
    }
    if (x < 0 || x >= cfg->largura) {
        return 1;
    }
    if (y < 0 || y >= cfg->altura) {
        return 1;
    }
    return 0;
}

void util_angle_to_delta(int ang, int vel, int *dx, int *dy) {
    int step_x = 0;
    int step_y = 0;

    switch (ang) {
        case 0:
            step_x = vel;
            step_y = 0;
            break;
        case 45:
            step_x = vel;
            step_y = -vel;
            break;
        case 90:
            step_x = 0;
            step_y = -vel;
            break;
        case 135:
            step_x = -vel;
            step_y = -vel;
            break;
        case 180:
            step_x = -vel;
            step_y = 0;
            break;
        case 225:
            step_x = -vel;
            step_y = vel;
            break;
        case 270:
            step_x = 0;
            step_y = vel;
            break;
        case 315:
            step_x = vel;
            step_y = vel;
            break;
        default:
            step_x = 0;
            step_y = 0;
            break;
    }

    if (dx != NULL) {
        *dx = step_x;
    }
    if (dy != NULL) {
        *dy = step_y;
    }
}
