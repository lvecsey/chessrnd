
#include <stdint.h>

#include "fill_rankfile.h"

uint64_t movement_wpawn(uint64_t wpawn, uint64_t totalpop, uint64_t blackpieces) {

  uint64_t ret = 0;

  long int start_rank, start_file;

  fill_rankfile(wpawn, &start_rank, &start_file);
  
  if ( (wpawn<<8) || (wpawn<<16) ) {

    if (! (totalpop & (wpawn<<8))) {
      ret |= wpawn<<8;
    }

    if (!(totalpop & (wpawn<<16)) && !(totalpop & (wpawn<<8))) {
      if (wpawn & 0b1111111100000000) {
	ret |= wpawn<<16;
      }
    }

    if (start_file < 7) {
      if (blackpieces & (wpawn<<7)) {
	ret |= wpawn<<7;
      }
    }

    if (start_file > 0) {
      if (blackpieces & (wpawn<<9)) {
	ret |= wpawn<<9;
      }
    }
    
  }
    
  return ret;
  
}

uint64_t movement_bpawn(uint64_t bpawn, uint64_t totalpop, uint64_t whitepieces) {

  uint64_t ret = 0;

  long int start_rank, start_file;

  fill_rankfile(bpawn, &start_rank, &start_file);
  
  if ( (bpawn>>8) || (bpawn>>16) ) {

    if (! (totalpop & (bpawn>>8))) {
      ret |= bpawn>>8;
    }

    if (!(totalpop & (bpawn>>16)) && !(totalpop & (bpawn>>8))) {
      if (bpawn & 0b0000000011111111000000000000000000000000000000000000000000000000) {
	ret |= bpawn>>16;
      }
    }

    if (start_file > 0) {
      if (whitepieces & (bpawn>>7)) {
	ret |= bpawn>>7;
      }
    }

    if (start_file < 7) {
      if (whitepieces & (bpawn>>9)) {
	ret |= bpawn>>9;
      }
    }
    
  }
  
  return ret;
  
}
