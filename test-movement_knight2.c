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

uint64_t bmatch_knight = 0b0000000000000000101001010000000000000000000000000000000000000000;

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

  long int j;
  
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

  retval = init_pieceloc2(&game.wh2);
  retval = init_pieceloc2(&game.bl2);  

  game.wh2.king = game.wh.king;

  game.wh2.rooks[0] = game.wh.rooks & (1UL << 7);
  game.wh2.rooks[1] = game.wh.rooks & (1UL << 0);  

  game.wh2.knights[0] = game.wh.knights & (1UL << 6);
  game.wh2.knights[1] = game.wh.knights & (1UL << 1);  

  game.wh2.bishops[0] = game.wh.bishops & (1UL << 5);
  game.wh2.bishops[1] = game.wh.bishops & (1UL << 2);  

  game.wh2.queens[0] = game.wh.queens;

  for (file = 0; file < 8; file++) {
    game.wh2.pawns[0] = game.wh.pawns & (1UL << (15 - file));
  }
  
  game.bl2.king = game.bl.king;  

  game.bl2.rooks[0] = game.bl.rooks & (1UL << 63);
  game.bl2.rooks[1] = game.bl.rooks & (1UL << 56);

  game.bl2.knights[0] = game.bl.knights & (1UL << 62);
  game.bl2.knights[1] = game.bl.knights & (1UL << 57);    

  game.bl2.bishops[0] = game.bl.bishops & (1UL << 5);
  game.bl2.bishops[1] = game.bl.bishops & (1UL << 2);  

  game.bl2.queens[0] = game.bl.queens;

  for (file = 0; file < 8; file++) {
    game.bl2.pawns[0] = game.bl.pawns & (1UL << (55 - file));
  }
  
  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  combined_knightmove = 0;
  
  for (j = 0; j < game.bl2.num_knights; j++) {

    knight = game.bl2.knights[j];

    if (!knight) continue;
    
    knightmove = movement_knight(knight, totalpop, cs_white);

    combined_knightmove |= knightmove;
    
    show_bitmask(knightmove);
    
    retval = add_mlspecific(base, game.bl2.knights+j, knightmove, BKNIGHT);
      
  }

  if (combined_knightmove != bmatch_knight) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for black.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
