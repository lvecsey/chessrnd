
#include <stdio.h>

#include <stdint.h>

#define gtinrange(x) ( (x) >= 0UL && (x) < 64UL )

uint64_t movement_king(uint64_t king, uint64_t totalpop, uint64_t opp_pieces) {

  uint64_t ret = 0;

  long int file, rank;

  long int bitno;

  long int bitnext;

  long int is_gts[8];

  uint64_t mask;
  
  long int bitnexts[8];

  long int j;

  long int xi, yi;
  
  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {

      bitno = rank*8+(7-file);

      for (j = 0; j < 8; j++) is_gts[j] = 0;

      mask = (1ULL << bitno);
      
      if (king & mask) {

	mask = (1ULL << bitno);

	mask <<= 1;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = (1ULL << bitno);

	mask >>= 1;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = (1ULL << bitno);

	mask <<= 8;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}	

	mask = (1ULL << bitno);

	mask >>= 8;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = (1ULL << bitno);

	mask <<= 9;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}	

	mask = (1ULL << bitno);

	mask <<= 7;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = (1ULL << bitno);

	mask >>= 9;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}

	mask = (1ULL << bitno);

	mask >>= 7;
	if (! (totalpop & mask)) {
	  ret |= mask;
	}
	
	return ret;
	
      }
    }
  }
  
  return ret;
  
}


