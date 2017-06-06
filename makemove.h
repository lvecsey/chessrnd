#ifndef MAKEMOVE_H
#define MAKEMOVE_H

#include "ml.h"

int makemove_desc(struct ml *base);

struct ml *fetch_move(struct ml *base, long int selectno);

#endif
