
#include <stdio.h>

#include "pos.h"

int clear_position(pos_t *positions, char *algebraic_dest) {

  long int dest_rank, dest_file;

  pos_t *pdest;
  
  dest_file = algebraic_dest[0] - 'a';
  dest_rank = algebraic_dest[1] - '1';  

  pdest = positions + (dest_rank*8+dest_file);
  if (pdest->ptype && pdest->ploc != NULL) {
    pdest->ptype = 0;
    pdest->ploc[0] = 0;
  }
    
  return 0;
  
}
