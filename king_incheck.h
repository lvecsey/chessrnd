#ifndef KING_INCHECK_H
#define KING_INCHECK_H

#include "basegame.h"

enum { KIC_ERROR=-101, KIC_NEG=0, KIC_POS=1 };

int king_incheck(basegame_t *game, uint64_t totalpop, uint64_t opp_pieces, long int ptype);

#endif
