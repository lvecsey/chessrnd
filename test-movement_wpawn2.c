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

uint64_t wmatch_pawn = 0b0000000010000000100000000000000000000000000000000000000000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t wpawn;

  uint64_t pawnmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int file, rank;

  long int counter;

  int retval;

  long int j;
  
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

  game.wh.knights = bitmask_change(game.wh.knights, "g1h3");

  game.wh2.pawns = calloc(8, sizeof(uint64_t));
  if (game.wh2.pawns == NULL) {
    perror("calloc");
    return -1;
  }

  game.wh2.pawns[0] = game.wh.pawns & (1ULL << (15 - 0));
  game.wh2.pawns[1] = game.wh.pawns & (1ULL << (15 - 1));
  game.wh2.pawns[2] = game.wh.pawns & (1ULL << (15 - 2));
  game.wh2.pawns[3] = game.wh.pawns & (1ULL << (15 - 3));

  game.wh2.pawns[4] = game.wh.pawns & (1ULL << (15 - 4));
  game.wh2.pawns[5] = game.wh.pawns & (1ULL << (15 - 5));
  game.wh2.pawns[6] = game.wh.pawns & (1ULL << (15 - 6));
  game.wh2.pawns[7] = game.wh.pawns & (1ULL << (15 - 7));    
  
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  for (j = 0; j < 8; j++) {

    wpawn = game.wh2.pawns[j];

    if (!wpawn) continue;
    
    pawnmove = movement_wpawn(wpawn, totalpop, cs_black);

    show_bitmask(pawnmove);
    
    retval = add_mlspecific(base, game.wh2.pawns+j, pawnmove, WPAWN);
      
  }

  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  if (counter == 16) {
    printf("SUCCESS");
    return 0;
  }

  printf("FAILURE");
  
  return -1;

}
