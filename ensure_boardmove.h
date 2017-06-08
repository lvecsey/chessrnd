#ifndef ENSURE_BOARDMOVE_H
#define ENSURE_BOARDMOVE_H

#include <stdint.h>

#include "ml.h"

int ensure_boardmove(struct ml *base, uint64_t totalpop, uint64_t opp_pieces);

#endif
