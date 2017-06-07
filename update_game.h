#ifndef UPDATE_GAME_H
#define UPDATE_GAME_H

#include <stdint.h>

#include "basegame.h"

#include "ml.h"

int update_game(basegame_t *game, struct ml *pn, char *strbuf);

uint64_t bitmask_change(uint64_t start, char *strbuf);

uint64_t bitmask_singlechange(uint64_t start, char *strbuf);

#endif
