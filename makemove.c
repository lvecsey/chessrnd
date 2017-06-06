
#include <stdio.h>

#include "ml.h"

#include "fill_rankfile.h"

struct ml *fetch_move(struct ml *base, long int selectno) {

  long int counter;

  struct ml *pn = base->next;
  
  counter = 0;
  while (pn != NULL && counter < selectno) {
    counter++;
    pn = pn->next;
  }

  return pn;
  
}

int makemove_desc(struct ml *pn) {

  long int dest_rank, dest_file;

  long int start_rank, start_file;

  printf("pn->ptype = %ld\n", pn->ptype);
  printf("pn->ploc = %lu\n", pn->ploc);

  fill_rankfile(*pn->pieceStart, &start_rank, &start_file);
  fill_rankfile(pn->ploc, &dest_rank, &dest_file);	
  
  printf("PIECE MOVE "); piece_descr(pn->ptype); putchar('\n');
  printf("Moving from %c%c to %c%c\n", 'a' + start_file, '1' + start_rank, 'a' + dest_file, '1' + dest_rank);

  return 0;
  
}
