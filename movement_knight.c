
#include <stdio.h>

#include <stdint.h>

#define gtinrange(x) ( (x) >= 0UL && (x) < 64UL )

long int setnext(long int x, long int *is_gtr) {
  if (is_gtr != NULL) *is_gtr = gtinrange(x);
  if (x < 0) x = 0;
  x %= 64;
  return x;
}

uint64_t movement_knight(uint64_t knight, uint64_t totalpop, uint64_t opp_pieces) {

  uint64_t ret = 0;

  long int file, rank;

  long int bitno;

  long int bitnext;

  long int is_gts[8];

  uint64_t mask;
  
  long int bitnexts[8];

  long int j;

  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {

      bitno = rank*8+(7-file);

      for (j = 0; j < 8; j++) is_gts[j] = 0;

      mask = (1ULL << bitno);
      
      if (knight & mask) {

	bitnexts[0] = setnext(bitno - 17, is_gts+0);

	if (file > 0) {
	  bitnexts[1] = setnext(bitno - 15, is_gts+1);
	}

	if (file > 0) {
	  bitnexts[2] = setnext(bitno + 17, is_gts+2);
	}
	
	bitnexts[3] = setnext(bitno + 15, is_gts+3);

	if (file < 6) {
	  bitnexts[4] = setnext(bitno - 10, is_gts+4);
	}

	if (file < 6) {
	  bitnexts[5] = setnext(bitno - 6, is_gts+5);
	}
	
	if (file < 6) {
	  bitnexts[6] = setnext(bitno + 10, is_gts+6);
	}

	if (file < 6) {
	  bitnexts[7] = setnext(bitno + 6, is_gts+7);
	}
	  
	// occupied squares

	for (j = 0; j < 8; j++) {

	  if (!is_gts[j]) continue;
	  
	  if (opp_pieces & (1ULL << bitnexts[j])) {
	    ret |= 1ULL << bitnexts[j];
	  }

	}

	// empty squares

	for (j = 0; j < 8; j++) {

	  if (!is_gts[j]) continue;
	  
	  if (! (totalpop & (1ULL << bitnexts[j]))) {
	    ret |= 1ULL << bitnexts[j];
	  }

	}

	return ret;
	
      }
    }
  }
  
  return ret;
  
}


