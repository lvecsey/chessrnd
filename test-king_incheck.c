#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "basegame.h"

#include "collected_side.h"

#include "total_population.h"

#include "ml.h"

#include "show_bitmask.h"

#include "update_game.h"

#include "king_incheck.h"

#include "gameset.h"

#include "movement_king.h"

#include "remove_checks.h"

uint64_t wmatch_king = 0b0000000000000000000000000110000010000000111000000000000000000000;  
  
int main(int argc, char *argv[]) {

  basegame_t game;
  
  uint64_t king;

  uint64_t kingmove;

  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int counter;

  int retval;

  struct ml *base = malloc(sizeof(struct ml));

  if (base==NULL) {
    perror("malloc");
    return -1;
  }
  
  retval = gameset(&game);
  
  game.bl2.pawns[0] = bitmask_change(game.bl2.pawns[0], "a7a5");

  game.bl2.rooks[0] = bitmask_change(game.bl2.rooks[0], "a8a6");
  game.bl2.rooks[0] = bitmask_change(game.bl2.rooks[0], "a6b6");  
  
  game.wh2.pawns[2] = bitmask_change(game.wh2.pawns[2], "c2c4");
  game.wh2.pawns[3] = bitmask_change(game.wh2.pawns[3], "d2d4");  

  game.wh2.king = bitmask_change(game.wh2.king, "e1d2");
  game.wh2.king = bitmask_change(game.wh2.king, "d2c3");
  game.wh2.king = bitmask_change(game.wh2.king, "c3b4");    

  apply_game2(&game);
  
  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  {
    
    king = game.wh2.king;

    if (!king) return -1;

    show_bitmask(king);

    show_bitmask(totalpop);
    
    kingmove = movement_king(king, totalpop, cs_black);

    show_bitmask(kingmove);
    
    retval = add_mlspecific(base, &game.wh2.king+0, kingmove, WKING);
      
  }

  if (kingmove != wmatch_king) {
    printf("FAILURE");
    return -1;
  }

  retval = remove_checks(&game, WKING, base);
  if (retval==-1) {
    printf("Trouble removing potential moves that leave king in check.\n");
    return -1;
  }
  
  counter = count_nodes(base);
      
  fprintf(stderr, "%s: Counted %ld moves, for black.\n", __FUNCTION__, counter);

  printf("SUCCESS");
  
  return 0;

}
