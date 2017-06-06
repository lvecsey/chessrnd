
#include <stdint.h>

int fill_rankfile(uint64_t ploc, long int *out_rank, long int *out_file) {

  long int rank, file;

  long int bitno;

  uint64_t mask;
  
  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {

      bitno = rank * 8 + (7 - file);

      mask = 1ULL << bitno;
      
      if (ploc & mask) {

	*out_rank = rank;
	*out_file = file;

	return 0;
	
      }
      
    }
  }
  
  return 0;
  
}
