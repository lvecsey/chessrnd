#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "movement_knight.h"

#include "collected_side.h"

#include "total_population.h"

#include "ml.h"

#include "show_bitmask.h"

uint64_t wmatch_knight = 0b0000000000000000000000000000000000000000101001010000000000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t knight;

  uint64_t knightmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int file, rank;

  long int counter;

  int retval;

  uint64_t combined_knightmove;
  
  struct ml *base = malloc(sizeof(struct ml));

  if (base==NULL) {
    perror("malloc");
    return -1;
  }
  
  game.wh.pawns = piecemask_wpawn;
  game.wh.rooks = piecemask_wrook;
  game.wh.bishops = piecemask_wbishop;
  game.wh.knights = piecemask_wknight;
  game.wh.king = piecemask_wking;
  game.wh.queens = piecemask_wqueen;

  game.bl.pawns = piecemask_bpawn;
  game.bl.rooks = piecemask_brook;
  game.bl.bishops = piecemask_bbishop;
  game.bl.knights = piecemask_bknight;
  game.bl.king = piecemask_bking;
  game.bl.queens = piecemask_bqueen;

  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  combined_knightmove = 0;
  
  for (file = 1; file < 8; file += 5) {

    knight = game.wh.knights & (1UL << (7 - file));

    knightmove = movement_knight(knight, totalpop, cs_black);

    combined_knightmove |= knightmove;
    
    show_bitmask(knightmove);
    
    retval = add_mlspecific(base, knight, knightmove, WKNIGHT);
      
  }

  if (combined_knightmove != wmatch_knight) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
