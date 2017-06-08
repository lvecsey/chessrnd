
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "pos.h"

#include "basegame.h"

#include "ml.h"

int gameset(basegame_t *game) {

  long int file;

  long int n;

  int retval;

  long int moveno = -1;
  
  game->wh.pawns = piecemask_wpawn;
  game->wh.rooks = piecemask_wrook;
  game->wh.bishops = piecemask_wbishop;
  game->wh.knights = piecemask_wknight;
  game->wh.king = piecemask_wking;
  game->wh.queens = piecemask_wqueen;

  game->bl.pawns = piecemask_bpawn;
  game->bl.rooks = piecemask_brook;
  game->bl.bishops = piecemask_bbishop;
  game->bl.knights = piecemask_bknight;
  game->bl.king = piecemask_bking;
  game->bl.queens = piecemask_bqueen;

  retval = init_pieceloc2(&game->wh2);
  if (retval==-1) {
    fprintf(stderr, "%s: Memory allocation failure.\n", __FUNCTION__);
    return -1;
  }

  retval = init_pieceloc2(&game->bl2);  
  if (retval==-1) {
    fprintf(stderr, "%s: Memory allocation failure.\n", __FUNCTION__);
    return -1;
  }

  game->wh2.king = game->wh.king;

  game->wh2.rooks[0] = game->wh.rooks & (1UL << 7);
  game->wh2.rooks[1] = game->wh.rooks & (1UL << 0);  

  game->wh2.knights[0] = game->wh.knights & (1UL << 6);
  game->wh2.knights[1] = game->wh.knights & (1UL << 1);  

  game->wh2.bishops[0] = game->wh.bishops & (1UL << 5);
  game->wh2.bishops[1] = game->wh.bishops & (1UL << 2);  

  game->wh2.queens[0] = game->wh.queens;

  for (file = 0; file < 8; file++) {
    game->wh2.pawns[file] = game->wh.pawns & (1UL << (15 - file));
  }
  
  game->bl2.king = game->bl.king;  

  game->bl2.rooks[0] = game->bl.rooks & (1UL << 63);
  game->bl2.rooks[1] = game->bl.rooks & (1UL << 56);

  game->bl2.knights[0] = game->bl.knights & (1UL << 62);
  game->bl2.knights[1] = game->bl.knights & (1UL << 57);    

  game->bl2.bishops[0] = game->bl.bishops & (1UL << 61);
  game->bl2.bishops[1] = game->bl.bishops & (1UL << 58);  

  game->bl2.queens[0] = game->bl.queens;

  for (file = 0; file < 8; file++) {
    game->bl2.pawns[file] = game->bl.pawns & (1UL << (55 - file));
  }

  for (n = 0; n < 64; n++) {
    game->positions[n] = (pos_t) { .moveno_history = moveno, .ptype = EPIECE, .ploc = NULL };
  }
  
  {
    long int rank;

    rank = 7;
    game->positions[rank*8+0] = setpos(BROOK, game->bl2.rooks+0, moveno);
    game->positions[rank*8+1] = setpos(BKNIGHT, game->bl2.knights+0, moveno);
    game->positions[rank*8+2] = setpos(BBISHOP, game->bl2.bishops+0, moveno);
    game->positions[rank*8+3] = setpos(BQUEEN, game->bl2.queens+0, moveno);
    game->positions[rank*8+4] = setpos(BKING, &game->bl2.king, moveno);
    game->positions[rank*8+5] = setpos(BBISHOP, game->bl2.bishops+1, moveno);
    game->positions[rank*8+6] = setpos(BKNIGHT, game->bl2.knights+1, moveno);
    game->positions[rank*8+7] = setpos(BROOK, game->bl2.rooks+1, moveno);

    rank = 6;
    for (file = 0; file < 8; file++) {
      game->positions[rank*8+file] = setpos(BPAWN, game->bl2.pawns+file, moveno);
    }

    rank = 0;
    game->positions[rank*8+0] = setpos(WROOK, game->wh2.rooks+0, moveno);
    game->positions[rank*8+1] = setpos(WKNIGHT, game->wh2.knights+0, moveno);
    game->positions[rank*8+2] = setpos(WBISHOP, game->wh2.bishops+0, moveno);
    game->positions[rank*8+3] = setpos(WQUEEN, game->wh2.queens+0, moveno);
    game->positions[rank*8+4] = setpos(WKING, &game->wh2.king, moveno);
    game->positions[rank*8+5] = setpos(WBISHOP, game->wh2.bishops+1, moveno);
    game->positions[rank*8+6] = setpos(WKNIGHT, game->wh2.knights+1, moveno);
    game->positions[rank*8+7] = setpos(WROOK, game->wh2.rooks+1, moveno);

    rank = 1;
    for (file = 0; file < 8; file++) {
      game->positions[rank*8+file] = setpos(WPAWN, game->wh2.pawns+file, moveno);
    }    
    
  }
  
  return 0;
  
}
  
