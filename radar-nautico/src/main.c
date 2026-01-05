#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "history.h"
#include "io.h"
#include "parse.h"
#include "sim.h"
#include "util.h"

int parse_dimensions(const char *arg, int *largura, int *altura) {
    int w = 0;
    int h = 0;

    if (sscanf(arg, "%dx%d", &w, &h) != 2) {
        return 1;
    }
    if (w <= 0 || h <= 0) {
        return 1;
    }
    *largura = w;
    *altura = h;
    return 0;
}

int main(int argc, char **argv) {
    const char *input_path = NULL;
    const char *output_path = NULL;
    RadarConfig cfg = {0};
    Frame current = {0};
    BaseDados *history = NULL;
    FILE *out = NULL;
    int i = 0;

    if (argc != 5) {
        fprintf(stderr, "Uso: %s <input> <WxH> <frames> <output>\n", argv[0]);
        return 1;
    }

    input_path = argv[1];
    if (parse_dimensions(argv[2], &cfg.largura, &cfg.altura) != 0) {
        fprintf(stderr, "Dimensoes invalidas.\n");
        return 1;
    }

    cfg.total_frames = atoi(argv[3]);
    output_path = argv[4];

    if (io_open_output(output_path, &out) != 0) {
        fprintf(stderr, "Erro ao abrir output.\n");
        return 1;
    }

    if (parse_input_file(input_path, &cfg, &current.entidades) != 0) {
        fprintf(stderr, "Erro ao ler input.\n");
        io_close_output(out);
        return 1;
    }

    current.numero = 0;
    history = history_append(history, &current);
    io_write_frame(out, &current, &cfg);

    for (i = 0; i < cfg.total_frames; i++) {
        Frame next = {0};
        if (sim_advance_frame(&current, &cfg, &next) != 0) {
            entidade_free_list(current.entidades);
            history_free_all(history);
            io_close_output(out);
            return 1;
        }
        entidade_free_list(current.entidades);
        current = next;
        history = history_append(history, &current);
        io_write_frame(out, &current, &cfg);
    }

    if (cfg.total_frames == 0) {
        cli_run(&current, &history, &cfg, out);
    }

    entidade_free_list(current.entidades);
    history_free_all(history);
    io_close_output(out);

    return 0;
}
