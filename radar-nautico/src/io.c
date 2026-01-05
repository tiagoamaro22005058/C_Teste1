#include <stdio.h>

#include "io.h"

int io_open_output(const char *path, FILE **out) {
    if (out == NULL) {
        return 1;
    }

    *out = fopen(path, "w");
    if (*out == NULL) {
        return 1;
    }

    return 0;
}

int io_write_frame(FILE *out, const Frame *frame, const RadarConfig *cfg) {
    const EntidadeIED *iter = NULL;

    if (out == NULL || frame == NULL || cfg == NULL) {
        return 1;
    }

    fprintf(out, "FRAME %d %dx%d\n", frame->numero, cfg->largura, cfg->altura);
    iter = frame->entidades;
    while (iter != NULL) {
        fprintf(out, "%s %d %d %d %d %d\n", iter->id, iter->x, iter->y, iter->ang, iter->vel,
                iter->tipo);
        iter = iter->next;
    }
    fprintf(out, "\n");

    return 0;
}

void io_close_output(FILE *out) {
    if (out != NULL) {
        fclose(out);
    }
}
