
#include <stdio.h>

#include <stdint.h>

int show_bitmask(uint64_t mask) {

  long int file, rank;

  long int bitno = 63;

  long int val;
  
  for (rank = 7; rank >= 0; rank--) {
    for (file = 0; file < 8; file++) {

      val = (mask&(1UL<<bitno)) ? 1 : 0;
      
      putchar('0' + val);
      bitno--;
      
    }
    putchar('\n');
  }

  return 0;
  
}
