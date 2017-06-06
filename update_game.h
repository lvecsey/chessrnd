#ifndef UPDATE_GAME_H
#define UPDATE_GAME_H

#include <stdint.h>

#include "basegame.h"

#include "ml.h"

int update_game(basegame_t *game, struct ml *pn, char *strbuf);

uuuuint64_t bitmask_change(uint64_t start, char *Strbuf);

#endif
