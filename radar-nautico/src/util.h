#ifndef UTIL_H
#define UTIL_H

#include "types.h"

EntidadeIED *entidade_clone_list(const EntidadeIED *src);
void entidade_free_list(EntidadeIED *list);
int util_is_out_of_bounds(int x, int y, const RadarConfig *cfg);
void util_angle_to_delta(int ang, int vel, int *dx, int *dy);

#endif
