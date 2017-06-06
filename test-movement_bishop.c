#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "movement_bishop.h"

#include "collected_side.h"

#include "total_population.h"

#include "ml.h"

#include "show_bitmask.h"

uint64_t wmatch_bishop = 0b0000000000000000000000000000000000000000000000000000010000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t bishop;

  uint64_t bishopmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int counter;

  int retval;

  uint64_t combined_bishopmove;

  struct ml *base;

  long int j;

  base = malloc(sizeof(struct ml));
  if (base==NULL) {
    perror("malloc");
    return -1;
  }
  
  game.wh.pawns = piecemask_wpawn;
  game.wh.rooks = piecemask_wrook;
  game.wh.knights = piecemask_wbishop;
  game.wh.bishops = piecemask_wbishop;
  game.wh.king = piecemask_wking;
  game.wh.queens = piecemask_wqueen;

  game.bl.pawns = piecemask_bpawn;
  game.bl.rooks = piecemask_brook;
  game.bl.knights = piecemask_bbishop;
  game.bl.bishops = piecemask_bbishop;
  game.bl.king = piecemask_bking;
  game.bl.queens = piecemask_bqueen;

  game.wh.pawns = bitmask_change(game.wh.pawns, "f2f3");
  
  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  combined_bishopmove = 0;

  game.wh2.num_bishops = 8 + 2;
  game.wh2.bishops = calloc(game.wh2.num_bishops, sizeof(uint64_t));
  if (game.wh2.bishops == NULL) {
    perror("calloc");
    return -1;
  }

  for (j = 0; j < game.wh2.num_bishops; j++) {
    game.wh2.bishops[j] = 0;
  }
  
  game.wh2.bishops[0] = game.wh.bishops & (1ULL << (7 - 2));
  game.wh2.bishops[1] = game.wh.bishops & (1ULL << (7 - 5));

  for (j = 0; j < game.wh2.num_bishops; j++) {

    bishop = game.wh2.bishops[j];

    if (!bishop) continue;
    
    bishopmove = movement_bishop(bishop, totalpop, cs_black);

    combined_bishopmove |= bishopmove;
    
    show_bitmask(bishopmove);
    
    retval = add_mlspecific(base, game.wh2.bishops+j, bishopmove, WBISHOP);
      
  }

  if (combined_bishopmove != wmatch_bishop) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
