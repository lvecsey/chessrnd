
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>

#include "basegame.h"

#include "gamestate.h"

#include "total_population.h"
#include "collected_side.h"

#include "ml.h"

#include "update_game.h"

#include "fill_stringbuf.h"

#include "king_incheck.h"

#include "set_position.h"
#include "clear_position.h"

int remove_checks(basegame_t *game, long int ptype, struct ml *base) {

  struct ml *pn = base->next;

  struct ml *entry;

  long int dest_rank, dest_file;
  
  basegame_t updated;

  gamestate_t gamestate;

  char strbuf[4];

  int retval;

  int black_side = (ptype == BKING);

  double percent;

  long int counter = 0;

  long int incheck_count = 0;
  
  while (pn!=NULL) {

    updated.wh = game->wh;
    updated.bl = game->bl;

    memcpy(updated.positions, game->positions, sizeof(updated.positions));

    retval = fill_stringbuf(pn, strbuf, &dest_rank, &dest_file);
    if (retval == -1) {
      printf("Problem with fill_stringbuf.\n");
      return -1;
    }
    
    //    update_game(&updated, pn, strbuf);

    set_position(updated.positions, strbuf+2, pn->ptype, pn->pieceStart); 
       
    gamestate.totalpop = total_population(&updated.wh, &updated.bl);
    gamestate.opp_pieces = collected_side(black_side ? &updated.bl : &updated.wh);

    {
      long int bitno = (dest_rank * 8 + (7 - dest_file));
      uint64_t mask = 1ULL << bitno;

      uint64_t cs_side = black_side ? collected_side(&updated.bl) : collected_side(&updated.wh);
      
      if ( cs_side & mask) {
	clear_position(updated.positions, strbuf+2);
      }
	
    }

    if (king_incheck(&updated, gamestate.totalpop, gamestate.opp_pieces, ptype)) {
      printf("Move would put king into check. Removing it.\n");
      entry = pn;
      entry->ploc = 0;
      pn = entry->next;
      remove_entry(base, entry);

      incheck_count++;
      
    }
    else {
      pn = pn->next;
    }

    counter++;
    
  }

  percent = ((double) incheck_count) / counter;
  printf("Percent of legal moves considered, that are in check: %.02f\n", percent);
  
  return 0;

}
