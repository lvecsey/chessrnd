
#include <stdint.h>

#include "pos.h"

pos_t setpos(long int ptype, uint64_t *ploc) {

  return (pos_t) { .ptype = ptype, .ploc = ploc };

}
