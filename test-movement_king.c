#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "movement_king.h"

#include "collected_side.h"

#include "total_population.h"

#include "update_game.h"

#include "ml.h"

#include "show_bitmask.h"

uint64_t wmatch_king = 0b0000000000000000000000000000000000000000000000000001110000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t king;

  uint64_t kingmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int counter;

  int retval;

  uint64_t combined_kingmove;

  struct ml *base;

  long int j;

  base = malloc(sizeof(struct ml));
  if (base==NULL) {
    perror("malloc");
    return -1;
  }
  
  game.wh.pawns = piecemask_wpawn;
  game.wh.rooks = piecemask_wrook;
  game.wh.knights = piecemask_wknight;
  game.wh.bishops = piecemask_wbishop;
  game.wh.king = piecemask_wking;
  game.wh.queens = piecemask_wqueen;

  game.bl.pawns = piecemask_bpawn;
  game.bl.rooks = piecemask_brook;
  game.bl.knights = piecemask_bknight;
  game.bl.bishops = piecemask_bbishop;
  game.bl.king = piecemask_bking;
  game.bl.queens = piecemask_bqueen;

  game.wh.pawns = bitmask_change(game.wh.pawns, "c2c3");
  game.wh.pawns = bitmask_change(game.wh.pawns, "d2d4");
  game.wh.pawns = bitmask_change(game.wh.pawns, "e2e4");
  game.wh.pawns = bitmask_change(game.wh.pawns, "f2f3");  
  
  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  combined_kingmove = 0;

  game.wh2.king = game.wh.king;
  
  {
    king = game.wh2.king;

    if (!king) return -1;
    
    kingmove = movement_king(king, totalpop, cs_black);

    combined_kingmove |= kingmove;
    
    show_bitmask(kingmove);
    
    retval = add_mlspecific(base, &game.wh2.king, kingmove, WKING);
      
  }

  if (combined_kingmove != wmatch_king) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
