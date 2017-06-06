
#include <stdint.h>

int single_algebraic(uint64_t piecemask, char *output_str) {

  long int rank=0, file=0;

  long int bitno;
  
  uint64_t locmask = 1UL << 63;

  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {
      if (piecemask&locmask) {
	output_str[0] = 'a' + file;
	output_str[1] = '1' + rank;
	return 0;
      }
      locmask >>= 1;
    }
  }
    
  return 0;
  
}
