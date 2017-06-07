
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "basegame.h"

#include "ml.h"

int remove_checks(basegame_t *game, long int ptype, struct ml *base) {

  struct ml *pn = base->next;

  while (pn!=NULL) {

    if (king_incheck(game, ptype)) {
      remove_entry(base, pn);
    }

    pn = pn->next;

  }
  
  return 0;

}
