
#include <stdio.h>

#include "pos.h"

#include "basegame.h"

#include "ml.h"

#include "fill_rankfile.h"

#include "king_incheck.h"

int king_incheck(basegame_t *game, uint64_t totalpop, uint64_t opp_pieces, long int ptype) {

  long int rank, file;

  long int xi, yi;

  long int bitno;
  
  int retval;

  uint64_t mask, original_mask;

  pos_t pos;

  show_positions_indepth(game->positions);
  
  switch(ptype) {
  case WKING:

    retval = fill_rankfile(game->wh.king, &rank, &file);
    if (retval == -1) {
      fprintf(stderr, "%s: Leaving because cannot set rank file.\n", __FUNCTION__);
      return KIC_ERROR;
    }
    
    bitno = (rank * 8 + (7 - file));

    original_mask = (1ULL << bitno);
    
    mask = original_mask;
    
    for (yi = rank + 1; mask && yi < 8; yi++) {
      mask <<= 8;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == BQUEEN || pos.ptype == BROOK) return KIC_POS;
	}
	break;
      }
    }

    mask = original_mask;
    
    for (yi = rank - 1; mask && yi >= 0; yi--) {
      mask >>= 8;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == BQUEEN || pos.ptype == BROOK) return KIC_POS;
	}
	break;
      }
    }

    mask = original_mask;

    for (xi = file + 1; mask && xi < 8; xi++) {
      mask >>= 1;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == BQUEEN || pos.ptype == BROOK) return KIC_POS;
	}
	break;
      }
    }

    mask = original_mask;

    for (xi = file - 1; mask && xi >= 0; xi--) {
      mask <<= 1;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == BQUEEN || pos.ptype == BROOK) return KIC_POS;
	}
	break;
      }
    }
    
    break;

  case BKING:

    retval = fill_rankfile(game->bl.king, &rank, &file);
    if (retval==-1) {
      fprintf(stderr, "%s: Leaving because cannot set rank file.\n", __FUNCTION__);
      return KIC_ERROR;
    }
    
    bitno = (rank * 8 + (7 - file));

    original_mask = (1ULL << bitno);
    
    mask = original_mask;
    
    for (yi = rank + 1; mask && yi < 8; yi++) {
      mask <<= 8;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == WQUEEN || pos.ptype == WROOK) return KIC_POS;
	}
	break;
      }
    }

    mask = original_mask;
    
    for (yi = rank - 1; mask && yi >= 0; yi--) {
      mask >>= 8;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == WQUEEN || pos.ptype == WROOK) return KIC_POS;
	}
	break;
      }
    }

    mask = original_mask;
    
    for (xi = file + 1; mask && xi < 8; xi++) {
      mask >>= 1;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == WQUEEN || pos.ptype == WROOK) return KIC_POS;
	}
	break;
      }
    }

    mask = original_mask;

    for (xi = file - 1; mask && xi >= 0; xi--) {
      mask <<= 1;
      if (totalpop & mask) {
	if (opp_pieces & mask) {
	  pos = game->positions[yi*8+file];
	  if (pos.ptype == WQUEEN || pos.ptype == WROOK) return KIC_POS;
	}
	break;
      }
    }
    
    break;
  }
  
  return KIC_NEG;

}
