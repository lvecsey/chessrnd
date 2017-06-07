#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "movement_rook.h"

#include "collected_side.h"

#include "total_population.h"

#include "update_game.h"

#include "ml.h"

#include "show_bitmask.h"

uint64_t bmatch_rook = 0b1000000000000000100000000000000000000000000000000000000000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t rook;

  uint64_t rookmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int counter;

  int retval;

  uint64_t combined_rookmove;

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

  base->next = NULL;
    
  game.bl.pawns = bitmask_change(game.bl.pawns, "a7a5");
  
  game.bl.rooks = bitmask_change(game.bl.rooks, "a8a7");
  
  combined_rookmove = 0;

  game.bl2.num_rooks = 8 + 2;
  game.bl2.rooks = calloc(game.bl2.num_rooks, sizeof(uint64_t));
  if (game.bl2.rooks == NULL) {
    perror("calloc");
    return -1;
  }

  for (j = 0; j < game.wh2.num_rooks; j++) {
    game.bl2.rooks[j] = 0;
  }
  
  game.bl2.rooks[0] = game.bl.rooks & (1ULL << (55 - 0));
  game.bl2.rooks[1] = game.bl.rooks & (1ULL << (63 - 7));  

  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  
  
  for (j = 0; j < game.bl2.num_rooks; j++) {

    rook = game.bl2.rooks[j];

    if (!rook) continue;
    
    rookmove = movement_rook(rook, totalpop, cs_white);

    show_bitmask(rookmove);
    
    combined_rookmove |= rookmove;
    
    retval = add_mlspecific(base, game.bl2.rooks+j, rookmove, BROOK);
      
  }

  show_bitmask(combined_rookmove);
  
  if (combined_rookmove != bmatch_rook) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
