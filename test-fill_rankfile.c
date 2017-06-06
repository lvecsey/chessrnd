#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "ml.h"

#include "fill_rankfile.h"

#include "makemove.h"

int main(int argc, char *argv[]) {

  struct ml pn;

  long int start_rank, start_file;
  long int dest_rank, dest_file;

  uint64_t pieceStart = 0b0000000000000000000000000000000000000000000000000000000000000010;
  
  pn.ptype = WKNIGHT;
  pn.pieceStart = &pieceStart;
  pn.ploc = 0b0000000000000000000000000000000000000000000000010000000000000000;
  
  fill_rankfile(*pn.pieceStart, &start_rank, &start_file);
  fill_rankfile(pn.ploc, &dest_rank, &dest_file);	

  makemove_desc(&pn);

  printf("SUCCESS");
  
  return 0;

}
