
#include <stdio.h>

#include <stdint.h>

long int count_bits(uint64_t bitmask) {

  long int counter = 0;

  uint64_t mask;
  
  mask = 1ULL << 63;

  while(mask) {
    if (bitmask & mask) counter++;
    mask>>=1ULL;
  }

  return counter;

}
  
int fill_rankfile(uint64_t ploc, long int *out_rank, long int *out_file) {

  long int rank, file;

  long int bitno;

  uint64_t mask;

  if (!ploc) {
    fprintf(stderr, "%s: Cannot extract rank file, no bits set.\n", __FUNCTION__);
    return -1;
  }

  if (count_bits(ploc) > 1) {
    fprintf(stderr, "%s: More than one bit is set, cannot find unique location.\n", __FUNCTION__);
    return -1;
  }
  
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
  
  return -1;
  
}
