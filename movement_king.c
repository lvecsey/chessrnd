
#include <stdio.h>

#include <stdint.h>

#include "show_bitmask.h"

uint64_t movement_king(uint64_t king, uint64_t totalpop, uint64_t opp_pieces) {

  uint64_t ret = 0;

  long int file, rank;

  long int bitno;

  uint64_t mask, original_mask;
  
  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {

      bitno = rank*8+(7-file);

      original_mask = (1ULL << bitno);
      
      if (king & original_mask) {

	mask = original_mask;
	mask <<= 1;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = original_mask;
	mask >>= 1;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = original_mask;
	mask <<= 8;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}	

	mask = original_mask;
	mask >>= 8;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = original_mask;
	mask <<= 9;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}	

	mask = original_mask;
	mask <<= 7;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = original_mask;
	mask >>= 9;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = original_mask;
	mask >>= 7;

	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	return ret;
	
      }
    }
  }
  
  return king;
  
}


