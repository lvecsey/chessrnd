
#include <stdio.h>

#include <stdint.h>

uint64_t movement_queen(uint64_t queen, uint64_t totalpop, uint64_t opp_pieces) {

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

      mask = (1ULL << bitno);
      
      if (queen & mask) {

	xi = file + 1;
	
	for ( mask <<= 7; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask <<= 7) {

	  if (xi < 8) xi++; else break;
	  
	  ret |= mask;
	  
	  if (opp_pieces & mask) break;

	}

	mask = (1ULL << bitno);

	xi = file - 1;
	
	for ( mask <<= 9; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask <<= 9) {

	  ret |= mask;

	  if (xi > 0) xi--; else break;
	  
	  if (opp_pieces & mask) break;

	}

	mask = (1ULL << bitno);

	xi = file - 1;
	
	for ( mask >>= 7; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask >>= 7) {

	  if (xi > 0) xi--; else break;
	  
	  ret |= mask;
	  
	  if (opp_pieces & mask) break;

	}

	mask = (1ULL << bitno);

	xi = file + 1;
	
	for ( mask >>= 9; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask >>= 9) {

	  if (xi < 8) xi++; else break;
	  
	  ret |= mask;
	  
	  if (opp_pieces & mask) break;

	}

	for (xi = file; xi < 8; xi++) {
	  bitno = rank*8+(7-file);
	  if (! (totalpop & mask) || (opp_pieces & mask)) {
	    ret |= mask;
	  }
	  if (opp_pieces & mask) break;
	}

	for (xi = file; xi >= 0; xi--) {
	  bitno = rank*8+(7-file);
	  if (! (totalpop & mask) || (opp_pieces & mask)) {
	    ret |= mask;
	  }
	  if (opp_pieces & mask) break;
	}

	xi = file;

	for (yi = rank; yi < 8; yi++) {
	  bitno = rank*8+(7-file);
	  if (! (totalpop & mask) || (opp_pieces & mask)) {
	    ret |= mask;
	  }
	  if (opp_pieces & mask) break;
	}

	for (yi = rank; yi >= 0; yi--) {
	  bitno = rank*8+(7-file);
	  if (! (totalpop & mask) || (opp_pieces & mask)) {
	    ret |= mask;
	  }
	  if (opp_pieces & mask) break;
	}
	
	return ret;
	
      }
    }
  }
  
  return ret;
  
}


