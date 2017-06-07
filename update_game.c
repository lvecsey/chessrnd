
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "basegame.h"
#include "ml.h"

#include "show_bitmask.h"

uint64_t bitmask_change(uint64_t start, char *strbuf) {

  uint64_t ret;

  long int start_rank, start_file;
  long int dest_rank, dest_file;

  long int bitno;

  long int bitnext;

  start_file = strbuf[0] - 'a';
  start_rank = strbuf[1] - '1';
  dest_file = strbuf[2] - 'a';
  dest_rank = strbuf[3] - '1';
  
  bitno = start_rank * 8 + (7 - start_file);
  bitnext = dest_rank * 8 + (7 - dest_file);  

  ret = start;
  ret &= ~(1ULL << bitno);
  ret |= (1ULL << bitnext);
  
  return ret;
  
}

uint64_t bitmask_singlechange(uint64_t start, char *strbuf) {

  long int dest_rank, dest_file;

  long int bitnext;

  dest_file = strbuf[2] - 'a';
  dest_rank = strbuf[3] - '1';
  
  bitnext = dest_rank * 8 + (7 - dest_file);  

  return (1ULL << bitnext);
  
}

int update_game(basegame_t *game, struct ml *pn, char *strbuf) {

  switch (pn->ptype) {

  case WPAWN: *pn->pieceStart = bitmask_singlechange(game->wh.pawns, strbuf); break;
  case BPAWN: *pn->pieceStart = bitmask_singlechange(game->bl.pawns, strbuf); break;

  case WROOK: *pn->pieceStart = bitmask_singlechange(game->wh.rooks, strbuf); break;
  case BROOK: *pn->pieceStart = bitmask_singlechange(game->bl.rooks, strbuf); break;
    
  case WKNIGHT: *pn->pieceStart = bitmask_singlechange(game->wh.knights, strbuf); break;
  case BKNIGHT: *pn->pieceStart = bitmask_singlechange(game->bl.knights, strbuf); break;

  case WBISHOP: *pn->pieceStart = bitmask_singlechange(game->wh.bishops, strbuf); break;
  case BBISHOP: *pn->pieceStart = bitmask_singlechange(game->bl.bishops, strbuf); break;

  case WQUEEN: *pn->pieceStart = bitmask_singlechange(game->wh.queens, strbuf); break;
  case BQUEEN: *pn->pieceStart = bitmask_singlechange(game->bl.queens, strbuf); break;

  case WKING: *pn->pieceStart = bitmask_singlechange(game->wh.king, strbuf); break;
  case BKING: *pn->pieceStart = bitmask_singlechange(game->bl.king, strbuf); break;
    
  }
  
  return 0;

}

int apply_game2(basegame_t *game) {

  uint64_t sum;

  long int j;
  
  game->wh.king = game->wh2.king;

  sum = 0;
  for (j = 0; j < game->wh2.num_queens; j++) {
    sum |= game->wh2.queens[j];
  }
  game->wh.queens = sum;

  sum = 0;
  for (j = 0; j < game->wh2.num_rooks; j++) {
    sum |= game->wh2.rooks[j];
  }
  game->wh.rooks = sum;

  sum = 0;
  for (j = 0; j < game->wh2.num_knights; j++) {
    sum |= game->wh2.knights[j];
  }
  game->wh.knights = sum;

  sum = 0;
  for (j = 0; j < game->wh2.num_bishops; j++) {
    sum |= game->wh2.bishops[j];
  }
  game->wh.bishops = sum;
  
  sum = 0;
  for (j = 0; j < 8; j++) {
    sum |= game->wh2.pawns[j];
  }
  game->wh.pawns = sum;
  
  game->bl.king = game->bl2.king;  

  sum = 0;
  for (j = 0; j < game->bl2.num_queens; j++) {
    sum |= game->bl2.queens[j];
  }
  game->bl.queens = sum;

  sum = 0;
  for (j = 0; j < game->bl2.num_rooks; j++) {
    sum |= game->bl2.rooks[j];
  }
  game->bl.rooks = sum;

  sum = 0;
  for (j = 0; j < game->bl2.num_knights; j++) {
    sum |= game->bl2.knights[j];
  }
  game->bl.knights = sum;

  sum = 0;
  for (j = 0; j < game->bl2.num_bishops; j++) {
    sum |= game->bl2.bishops[j];
  }
  game->bl.bishops = sum;
  
  sum = 0;
  for (j = 0; j < 8; j++) {
    sum |= game->bl2.pawns[j];
  }
  game->bl.pawns = sum;

  return 0;
  
}
