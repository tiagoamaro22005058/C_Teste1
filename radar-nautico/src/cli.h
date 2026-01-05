#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include "types.h"

int cli_run(Frame *current, BaseDados **history, const RadarConfig *cfg, FILE *out);

#endif
