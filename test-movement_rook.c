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

uint64_t wmatch_rook = 0b0000000000000000000000000000000000000000011111101000000110000001;

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

  game.wh.pawns = bitmask_change(game.wh.pawns, "a2a4");
  game.wh.pawns = bitmask_change(game.wh.pawns, "h2h4");

  game.wh.rooks = bitmask_change(game.wh.rooks, "a1a3");
  game.wh.rooks = bitmask_change(game.wh.rooks, "h1h3");    

  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  combined_rookmove = 0;

  game.wh2.num_rooks = 8 + 2;
  game.wh2.rooks = calloc(game.wh2.num_rooks, sizeof(uint64_t));
  if (game.wh2.rooks == NULL) {
    perror("calloc");
    return -1;
  }

  for (j = 0; j < game.wh2.num_rooks; j++) {
    game.wh2.rooks[j] = 0;
  }
  
  game.wh2.rooks[0] = game.wh.rooks & (1ULL << (23 - 0));
  game.wh2.rooks[1] = game.wh.rooks & (1ULL << (23 - 7));  

  for (j = 0; j < game.wh2.num_rooks; j++) {

    rook = game.wh2.rooks[j];

    if (!rook) continue;
    
    rookmove = movement_rook(rook, totalpop, cs_black);

    combined_rookmove |= rookmove;
    
    retval = add_mlspecific(base, game.wh2.rooks+j, rookmove, WROOK);
      
  }

  if (combined_rookmove != wmatch_rook) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
