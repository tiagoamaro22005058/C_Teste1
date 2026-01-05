#ifndef SIM_H
#define SIM_H

#include "types.h"

int sim_advance_frame(const Frame *current, const RadarConfig *cfg, Frame *next);
void sim_apply_movements(EntidadeIED *list, const RadarConfig *cfg);
void sim_remove_out_of_bounds(EntidadeIED **list, const RadarConfig *cfg);

#endif
