#ifndef POS_H
#define POS_H

#include <stdint.h>

typedef struct {

  long int ptype;
  uint64_t *ploc;
  
} pos_t;

pos_t setpos(long int ptype, uint64_t *ploc);

#endif
