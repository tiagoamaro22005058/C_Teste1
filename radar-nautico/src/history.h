#ifndef HISTORY_H
#define HISTORY_H

#include "types.h"

BaseDados *history_append(BaseDados *head, const Frame *frame_copy);
Frame *history_get_frame(BaseDados *head, int index);
void history_free_from(BaseDados *node);
void history_free_all(BaseDados *head);

#endif
