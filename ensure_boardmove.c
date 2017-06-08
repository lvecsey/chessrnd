
#include <stdio.h>
#include <stdlib.h>

#include "ml.h"

int ensure_boardmove(struct ml *base, uint64_t totalpop, uint64_t opp_pieces) {

  struct ml *pn = base->next;

  uint64_t ps;
  
  while (pn != NULL) {

    ps = pn->pieceStart[0];

    if (!ps) {
      fprintf(stderr, "%s: Sorry, there is no pieceStart location represented by this move.\n", __FUNCTION__);
      return -1;
    }
    
    if (! (ps & totalpop)) {
      show_ml(pn);
      fprintf(stderr, "%s: Suggested move is not in current board population.\n", __FUNCTION__);
      exit(EXIT_FAILURE);
    }

    if (ps & opp_pieces) {
      show_ml(pn);
      fprintf(stderr, "%s: Suggested most is actually an opponent piece.\n", __FUNCTION__);
      exit(EXIT_FAILURE);
    }

    pn = pn->next;
    
  }

  return 0;

}
  
