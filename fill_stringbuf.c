
#include <stdio.h>

#include "fill_rankfile.h"

#include "ml.h"

#include "pos.h"

int fill_stringbuf(struct ml *pn, char *strbuf) {

  long int start_rank, start_file;

  long int dest_rank, dest_file;

  int retval;
  
  retval = fill_rankfile(*pn->pieceStart, &start_rank, &start_file);
  if (retval==-1) {
    show_ml(pn);
    fprintf(stderr, "%s: [WHITE] Trouble getting rankfile for pn=%p, pn->pieceStart\n", __FUNCTION__, pn);
    return -1;
  }

  retval = fill_rankfile(pn->ploc, &dest_rank, &dest_file);	
  if (retval==-1) {
    fprintf(stderr, "%s: [WHITE] Trouble getting rankfile for pn=%p, pn->ploc\n", __FUNCTION__, pn);
    return -1;
  }

  strbuf[0] = 'a' + start_file;
  strbuf[1] = '1' + start_rank;
  strbuf[2] = 'a' + dest_file;
  strbuf[3] = '1' + dest_rank;

  return 0;

}
