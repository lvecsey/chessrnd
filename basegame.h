#ifndef BASEGAME_H
#define BASEGAME_H

#include <stdint.h>

#include "pieceloc.h"

#include "pieceloc2.h"

#include "pos.h"

typedef struct {

  pieceloc_t wh, bl;

  pieceloc2_t wh2, bl2;

  pos_t positions[64];
  
} basegame_t;

extern uint64_t pawnmask_fwdwhite;
extern uint64_t pawnmask_fwdblack;
extern uint64_t piecemask_wpawn;
extern uint64_t piecemask_bpawn;
extern uint64_t piecemask_wrook;
extern uint64_t piecemask_brook;
extern uint64_t piecemask_wbishop;
extern uint64_t piecemask_bbishop;
extern uint64_t piecemask_wknight;
extern uint64_t piecemask_bknight;
extern uint64_t piecemask_wking;
extern uint64_t piecemask_bking;
extern uint64_t piecemask_wqueen;
extern uint64_t piecemask_bqueen;
#endif
