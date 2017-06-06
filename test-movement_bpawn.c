#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "movement_pawn.h"

#include "collected_side.h"

#include "total_population.h"

#include "ml.h"

#include "show_bitmask.h"

uint64_t bmatch_pawn = 0b0000000010000000100000000000000000000000000000000000000000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t bpawn;

  uint64_t pawnmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int file, rank;

  long int counter;

  int retval;

  struct ml *base = malloc(sizeof(struct ml));

  if (base==NULL) {
    perror("malloc");
    return -1;
  }
  
  game.wh.pawns = piecemask_wpawn;
  game.wh.rooks = piecemask_wrook;
  game.wh.bishops = piecemask_wbishop;
  game.wh.knights = piecemask_wknight;
  game.wh.kings = piecemask_wking;
  game.wh.queens = piecemask_wqueen;

  game.bl.pawns = piecemask_bpawn;
  game.bl.rooks = piecemask_brook;
  game.bl.bishops = piecemask_bbishop;
  game.bl.knights = piecemask_bknight;
  game.bl.kings = piecemask_bking;
  game.bl.queens = piecemask_bqueen;

  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  for (file = 0; file < 8; file ++) {

    bpawn = game.bl.pawns & (1UL << (55 - file));

    pawnmove = movement_bpawn(bpawn, totalpop, cs_white);

    show_bitmask(pawnmove);
    
    retval = add_mlspecific(base, bpawn, pawnmove, BPAWN);
      
  }

  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for black.\n", __FUNCTION__, counter);

  if (counter == 16) {
    printf("SUCCESS");
    return 0;
  }

  printf("FAILURE");
  
  return -1;

}
