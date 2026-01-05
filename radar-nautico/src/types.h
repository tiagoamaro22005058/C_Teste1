#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

typedef struct EntidadeIED {
    char id[16];
    int tipo;
    int x;
    int y;
    int ang;
    int vel;
    int atributo1;
    int atributo2;
    struct EntidadeIED *next;
} EntidadeIED;

typedef struct Frame {
    int numero;
    EntidadeIED *entidades;
} Frame;

typedef struct BaseDados {
    Frame frame;
    struct BaseDados *next;
} BaseDados;

typedef struct RadarConfig {
    int largura;
    int altura;
    int total_frames;
} RadarConfig;

typedef struct SimConfig {
    int total_frames;
} SimConfig;

#endif
