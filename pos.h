#ifndef POS_H
#define POS_H

#include <stdint.h>

typedef struct {

  long int moveno_history;
  
  long int ptype;
  uint64_t *ploc;
  
} pos_t;

pos_t setpos(long int ptype, uint64_t *ploc, long int moveno);

int show_positions_indepth(pos_t *positions);

int show_positions(pos_t *positions);

#endif
