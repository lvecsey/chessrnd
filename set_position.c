
#include <stdio.h>

#include "pos.h"

int set_position(pos_t *positions, char *algebraic_dest, long int ptype) {

  long int dest_rank, dest_file;

  pos_t *pdest;

  long int bitno;
  
  dest_file = algebraic_dest[0] - 'a';
  dest_rank = algebraic_dest[1] - '1';  

  pdest = positions + (dest_rank*8+dest_file);

  bitno = dest_rank * 8 + dest_file;
  
  if (pdest->ploc != NULL) {
    pdest->ptype = ptype;
    pdest->ploc[0] = 1ULL << bitno;
  }
    
  return 0;
  
}
