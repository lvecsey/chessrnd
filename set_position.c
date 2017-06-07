
#include <stdio.h>

#include <stdint.h>

#include "pos.h"

int set_position(pos_t *positions, char *algebraic_dest, long int ptype, uint64_t *pieceStart) {

  long int dest_rank, dest_file;

  pos_t *pdest;

  long int bitno;

  uint64_t mask;
  
  dest_file = algebraic_dest[0] - 'a';
  dest_rank = algebraic_dest[1] - '1';  

  pdest = positions + (dest_rank*8+dest_file);

  bitno = dest_rank * 8 + (7 - dest_file);

  mask = (1ULL << bitno);
  
  printf("%s: Updating position %.02s to ptype=%ld\n", __FUNCTION__, algebraic_dest, ptype);
  
  pdest->ploc = pieceStart;
  pdest->ptype = ptype;
  pdest->ploc[0] = mask;
    
  return 0;
  
}
