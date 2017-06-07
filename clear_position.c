
#include <assert.h>

#include <stdio.h>

#include <stdint.h>

#include "pos.h"

#include "ml.h"

int clear_position(pos_t *positions, char *algebraic_coord) {

  long int rank, file;

  long int bitno;

  uint64_t mask;
  
  pos_t *pdest;

  file = algebraic_coord[0] - 'a';
  rank = algebraic_coord[1] - '1';  

  pdest = positions + (rank*8+file);

  printf("Position %.2s\n", algebraic_coord);
  printf("%s: pdest->ptype = %ld\n", __FUNCTION__, pdest->ptype);
  
  pdest->ptype = EPIECE;

  if (pdest->ploc != NULL) {
    bitno = rank * 8 + (7 - file);
    mask = 1ULL << bitno;
    pdest->ploc[0] &= ~mask;
  }
    
  return 0;
  
}
