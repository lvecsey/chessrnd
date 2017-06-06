
#include <stdio.h>

#include <stdint.h>

#define gtinrange(x) ( (x) >= 0UL && (x) < 64UL )

uint64_t movement_bishop(uint64_t bishop, uint64_t totalpop, uint64_t opp_pieces) {

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
      
      if (bishop & mask) {

	for ( mask <<= 7; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask <<= 7) {

	  ret |= mask;

	  if (opp_pieces & mask) break;

	}

	mask = (1ULL << bitno);

	for ( mask <<= 9; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask <<= 9) {

	  ret |= mask;

	  if (opp_pieces & mask) break;

	}

	mask = (1ULL << bitno);

	for ( mask >>= 7; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask >>= 7) {

	  ret |= mask;

	  if (opp_pieces & mask) break;

	}

	mask = (1ULL << bitno);

	for ( mask >>= 9; mask && (!(totalpop&mask) || (opp_pieces & mask)); mask >>= 9) {

	  ret |= mask;

	  if (opp_pieces & mask) break;

	}
	
	return ret;
	
      }
    }
  }
  
  return ret;
  
}


