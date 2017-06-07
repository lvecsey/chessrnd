#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "movement_queen.h"

#include "collected_side.h"

#include "total_population.h"

#include "update_game.h"

#include "ml.h"

#include "show_bitmask.h"

#include "gameset.h"

uint64_t wmatch_queen = 0b0000000000000000000000000000000110000010010001000010100000000000;

int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t queen;

  uint64_t queenmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int counter;

  int retval;

  uint64_t combined_queenmove;

  struct ml *base;

  long int j;

  base = malloc(sizeof(struct ml));
  if (base==NULL) {
    perror("malloc");
    return -1;
  }

  retval = gameset(&game);
  if (retval == -1) {
    fprintf(stderr, "Trouble with call to gameset.\n");
    return -1;
  }
  
  game.wh2.pawns[2] = bitmask_change(game.wh2.pawns[2], "c2c4");
  game.wh2.pawns[4] = bitmask_change(game.wh2.pawns[3], "e2e4");  

  apply_game2(&game);
  
  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  combined_queenmove = 0;

  game.wh2.num_queens = 8 + 2;
  game.wh2.queens = calloc(game.wh2.num_queens, sizeof(uint64_t));
  if (game.wh2.queens == NULL) {
    perror("calloc");
    return -1;
  }

  for (j = 0; j < game.wh2.num_queens; j++) {
    game.wh2.queens[j] = 0;
  }
  
  game.wh2.queens[0] = game.wh.queens;

  for (j = 0; j < game.wh2.num_queens; j++) {

    queen = game.wh2.queens[j];

    if (!queen) continue;

    show_bitmask(queen);
    
    queenmove = movement_queen(queen, totalpop, cs_black);

    combined_queenmove |= queenmove;
    
    show_bitmask(queenmove);
    
    retval = add_mlspecific(base, game.wh2.queens+j, queenmove, WQUEEN);
      
  }

  if (combined_queenmove != wmatch_queen) {
    printf("FAILURE");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
