#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

int parse_input_file(const char *path, RadarConfig *cfg, EntidadeIED **entidades) {
    FILE *in = NULL;
    EntidadeIED *head = NULL;
    EntidadeIED *tail = NULL;

    if (entidades == NULL) {
        return 1;
    }

    if (cfg != NULL) {
        (void)cfg;
    }

    in = fopen(path, "r");
    if (in == NULL) {
        return 1;
    }

    while (!feof(in)) {
        char id[16];
        int x = 0;
        int y = 0;
        int ang = 0;
        int vel = 0;
        int tipo = 0;
        int parsed = 0;
        EntidadeIED *node = NULL;

        parsed = fscanf(in, "%15s %d %d %d %d %d", id, &x, &y, &ang, &vel, &tipo);
        if (parsed == EOF) {
            break;
        }
        if (parsed != 6) {
            fscanf(in, "%*[\n]");
            continue;
        }

        node = malloc(sizeof(*node));
        if (node == NULL) {
            fclose(in);
            while (head != NULL) {
                EntidadeIED *next = head->next;
                free(head);
                head = next;
            }
            return 1;
        }
        memset(node, 0, sizeof(*node));
        strncpy(node->id, id, sizeof(node->id) - 1);
        node->x = x;
        node->y = y;
        node->ang = ang;
        node->vel = vel;
        node->tipo = tipo;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    fclose(in);
    *entidades = head;
    return 0;
}
