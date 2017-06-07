
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

  int retval;
  
  printf("pn->ptype=%ld pn->ploc=%lu\n", pn->ptype, pn->ploc);

  retval = fill_rankfile(*pn->pieceStart, &start_rank, &start_file);
  if (retval==-1) {
    fprintf(stderr, "%s: Trouble getting rankfile for pn=%p, pn->pieceStart\n", __FUNCTION__, pn);
    return -1;
  }

  retval = fill_rankfile(pn->ploc, &dest_rank, &dest_file);	
  if (retval==-1) {
    fprintf(stderr, "%s: Trouble getting rankfile for pn=%p, pn->ploc\n", __FUNCTION__, pn);
    return -1;
  }

  printf("start_rank=%ld start_file=%ld\n", start_rank, start_file);
  
  if (start_rank < 0) {
    start_rank = -start_rank;
  }

  if (start_file < 0) {
    start_file = -start_file;
  }

  start_rank %= 8;
  start_file %= 8;
  
  printf("PIECE MOVE "); piece_descr(pn->ptype); putchar('\n');
  printf("Moving from %c%c to %c%c\n", 'a' + (int) start_file, '1' + (int) start_rank, 'a' + (int) dest_file, '1' + (int) dest_rank);

  return 0;
  
}
