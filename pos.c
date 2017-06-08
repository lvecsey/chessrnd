
#include <stdio.h>

#include <stdint.h>

#include "pos.h"

#include "ml.h"

pos_t setpos(long int ptype, uint64_t *ploc, long int moveno) {

  return (pos_t) { .moveno_history = moveno, .ptype = ptype, .ploc = ploc };

}


int show_positions_indepth(pos_t *positions) {

  long int rank, file;

  char c;

  pos_t *pdest;
  
  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {
      pdest = positions + rank*8+file;
      printf("%ld ", pdest->ptype);
    }
    putchar('\n');
  }

  return 0;
  
}

int show_positions(pos_t *positions) {

  long int rank, file;

  char c;

  pos_t *pdest;
  
  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {
      pdest = positions + rank*8+file;
      c = (pdest->ptype == EPIECE) ? '0' : '1';
      putchar(c);
    }
    putchar('\n');
  }

  return 0;
  
}
