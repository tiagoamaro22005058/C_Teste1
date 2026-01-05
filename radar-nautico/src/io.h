#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "types.h"

int io_open_output(const char *path, FILE **out);
int io_write_frame(FILE *out, const Frame *frame, const RadarConfig *cfg);
void io_close_output(FILE *out);

#endif
