
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "pos.h"

#include "basegame.h"

#include "gameset.h"

#include "ml.h"

#include "update_game.h"

int main(int argc, char *argv[]) {

  basegame_t game;

  int retval;

  long int rank, file;

  long int n;

  long int moveno = -1;
  
  retval = gameset(&game);

  apply_game2(&game);

  for (n = 0; n < 64; n++) {
    game.positions[n].ptype = EPIECE;
  }
  
  rank = 6;
  for (file = 1; file < 7; file++) {
    game.positions[rank*8+file] = setpos(BPAWN, game.bl2.pawns+file, moveno);
  }

  file = 1;
  game.positions[1*8+file] = setpos(BROOK, game.bl2.rooks+file, moveno);
  game.positions[2*8+file] = setpos(BBISHOP, game.bl2.bishops+file, moveno);
  game.positions[3*8+file] = setpos(BKNIGHT, game.bl2.knights+file, moveno);
  game.positions[4*8+file] = setpos(BKNIGHT, game.bl2.knights+file, moveno);
  game.positions[5*8+file] = setpos(BBISHOP, game.bl2.bishops+file, moveno);
  game.positions[6*8+file] = setpos(BROOK, game.bl2.rooks+file, moveno);  

  file = 6;
  game.positions[1*8+file] = setpos(WROOK, game.wh2.rooks+file, moveno);
  game.positions[2*8+file] = setpos(WBISHOP, game.wh2.bishops+file, moveno);
  game.positions[3*8+file] = setpos(WKNIGHT, game.wh2.knights+file, moveno);
  game.positions[4*8+file] = setpos(WKNIGHT, game.wh2.knights+file, moveno);
  game.positions[5*8+file] = setpos(WBISHOP, game.wh2.bishops+file, moveno);
  game.positions[6*8+file] = setpos(WROOK, game.wh2.rooks+file, moveno);  
  
  rank = 1;
  for (file = 1; file < 7; file++) {
    game.positions[rank*8+file] = setpos(BPAWN, game.wh2.pawns+file, moveno);
  }

  show_positions(game.positions);
  
  return 0;

}
