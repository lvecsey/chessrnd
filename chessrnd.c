
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>

#include "basegame.h"

#include "collected_side.h"

#include "total_population.h"

#include "ml.h"

#include "movement_pawn.h"
#include "movement_knight.h"
#include "movement_king.h"
#include "movement_rook.h"
#include "movement_bishop.h"
#include "movement_queen.h"

#include "show_bitmask.h"

#include "fill_rankfile.h"

#include "makemove.h"

#include "pos.h"

#include "update_game.h"

#include "gameset.h"

#include "clear_position.h"

#include "set_position.h"

#include "king_incheck.h"

#include "remove_checks.h"

#include "fill_stringbuf.h"

int main(int argc, char *argv[]) {

  uint64_t totalpop;

  uint64_t cs_white, cs_black;
  
  basegame_t game;

  struct ml *base = malloc(sizeof(struct ml));

  int retval;

  long int counter;
  
  int rnd_fd;
  uint64_t rnds;
  ssize_t bytes_read;
  
  long int moveno;
  
  long int max_moves = 1000;

  long int selectno;

  uint64_t pieceStart;

  long int dest_file, dest_rank;
  
  char strbuf[4];
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int out_fd = open("output_chessrnd.txt", O_RDWR|O_CREAT, mode);

  long int j;
  
  struct ml *pn;

  ssize_t bytes_written;

  long int file, rank;
  
  rnd_fd = open("/dev/urandom", O_RDONLY);
  if (rnd_fd == -1) {
    perror("open");
    return -1;
  }
  
  retval = ftruncate(out_fd, 0);
  
  if (base==NULL) {
    perror("malloc");
    return -1;
  }

  retval = gameset(&game);  
  if (retval==-1) {
    fprintf(stderr, "%s: Trouble with initializing basic chess board.\n", __FUNCTION__);
    return -1;
  }
  
  for (moveno = 0; moveno < max_moves; moveno++) {

    base->next = NULL;
    
    if (moveno & 1) {
      
      printf("Black move (moveno %ld)\n", moveno);      

      totalpop = total_population(&game.wh, &game.bl);

      cs_white = collected_side(&game.wh);
      cs_black = collected_side(&game.bl);  

      if (totalpop == (game.wh.king | game.bl.king)) {
	fprintf(stderr, "%s: Reached draw, just kings are left.\n", __FUNCTION__);
      }
      
      {
	uint64_t pawnmove;

	uint64_t bpawn;

	long int file, rank;

	for (file = 0; file < 8; file++) {
    
	  bpawn = game.bl2.pawns[file];

	  if (!bpawn) continue;
	  
	  pawnmove = movement_bpawn(bpawn, totalpop, cs_white);

	  retval = add_mlspecific(base, game.bl2.pawns+file, pawnmove, BPAWN);

	}
      
      }

      {
	uint64_t knightmove;

	uint64_t knight;

	long int file, rank;
    
	for (j = 0; j < game.bl2.num_knights; j++) {

	  knight = game.bl2.knights[j];

	  if (!knight) continue;
	
	  knightmove = movement_knight(knight, totalpop, cs_white);

	  retval = add_mlspecific(base, game.bl2.knights+j, knightmove, BKNIGHT);
      
	}

      }

      {

	uint64_t rookmove;
	
	uint64_t rook;

	long int file, rank;

	for (j = 0; j < game.bl2.num_rooks; j++) {

	  rook = game.bl2.rooks[j];

	  if (!rook) continue;
	
	  rookmove = movement_rook(rook, totalpop, cs_white);

	  retval = add_mlspecific(base, game.bl2.rooks+j, rookmove, BROOK);
	  
	}
	
      }

      {

	uint64_t bishopmove;
	
	uint64_t bishop;

	long int file, rank;

	for (j = 0; j < game.bl2.num_bishops; j++) {

	  bishop = game.bl2.bishops[j];

	  if (!bishop) continue;
	
	  bishopmove = movement_bishop(bishop, totalpop, cs_white);

	  retval = add_mlspecific(base, game.bl2.bishops+j, bishopmove, BBISHOP);
	  
	}
	
      }

      {

	uint64_t queenmove;
	
	uint64_t queen;

	long int file, rank;

	for (j = 0; j < game.bl2.num_queens; j++) {

	  queen = game.bl2.queens[j];

	  if (!queen) continue;
	
	  queenmove = movement_queen(queen, totalpop, cs_white);

	  retval = add_mlspecific(base, game.bl2.queens+j, queenmove, BQUEEN);
	  
	}
	
      }
      
      {
	uint64_t kingmove;
	uint64_t king;
	long int file, rank;

	king = game.bl2.king;
	if (king) {
	  kingmove = movement_king(king, totalpop, cs_white);
	  retval = add_mlspecific(base, &game.bl2.king+0, kingmove, BKING);
	}

      }

      retval = ensure_boardmove(base, totalpop, cs_white);
      
      retval = remove_checks(&game, BKING, base, moveno);
      if (retval==-1) {
	printf("Trouble removing potential moves that leave king in check.\n");
	return -1;
      }
      
      counter = count_nodes(base);
      
      printf("%s: Counted %ld moves, for black.\n", __FUNCTION__, counter);

      if (!counter) {
	printf("Leaving, no moves to make.\n");
	return 0;
      }
      
      bytes_read = read(rnd_fd, &rnds, sizeof(uint64_t));
      if (bytes_read != sizeof(uint64_t)) {
	perror("read");
	return -1;
      }
      
      {
	selectno = ((double) counter) * rnds / 18446744073709551615.0; 
	printf("Selected moveno %ld\n", selectno);
      }

      pn = fetch_move(base, selectno);
      
      retval = fill_stringbuf(pn, strbuf, &dest_rank, &dest_file);
      if (retval==-1) {
	fprintf(stderr, "%s: Trouble filling coordinate pair.\n", __FUNCTION__);
	return -1;
      }
      
      {
	pos_t pos = game.positions[dest_rank*8+dest_file];

	if (pn->ptype != BKING && pos.ptype == BKING) {
	  if (pos.moveno_history == moveno) {
	    debug_out(&game, pn);
	    fprintf(stderr, "%s: Black king randomly captured. Move %.4s.\n", __FUNCTION__, strbuf);
	    return 0;
	  }
	}
	
      }

      makemove_desc(pn);
      
      if (strbuf[0] == strbuf[2] && strbuf[1] == strbuf[3]) {
	debug_out(&game, pn);
	fprintf(stderr, "%s: Not moving to a different square.\n", __FUNCTION__);
	return -1;
      }     

      bytes_written = write(out_fd, strbuf, 4);

      assert(pn->pieceStart != NULL);
      
      set_position(game.positions, strbuf+2, pn->ptype, pn->pieceStart, moveno);       
      update_game(&game, pn, strbuf);

      {
	long int bitno = (dest_rank * 8 + (7 - dest_file));
	uint64_t mask = 1ULL << bitno;

	if (cs_white & mask) {
	  clear_position(game.positions, strbuf+2);
	}
	
      }
      
      apply_game2(&game);
      
      assert(game.bl.king);
      
    }

    else {

      printf("White move (moveno %ld)\n", moveno);
      
      totalpop = total_population(&game.wh, &game.bl);

      cs_white = collected_side(&game.wh);
      cs_black = collected_side(&game.bl);  

      if (totalpop == (game.wh.king | game.bl.king)) {
	fprintf(stderr, "%s: Reached draw, just kings are left.\n", __FUNCTION__);
      }
      
      {
	uint64_t pawnmove;

	uint64_t wpawn;

	long int file, rank;

	for (file = 0; file < 8; file++) {
    
	  wpawn = game.wh2.pawns[file];

	  if (!wpawn) continue;

	  pawnmove = movement_wpawn(wpawn, totalpop, cs_black);

	  retval = add_mlspecific(base, game.wh2.pawns+file, pawnmove, WPAWN);

	}
      
      }

      {
	uint64_t knightmove;

	uint64_t knight;

	long int file, rank;
    
	for (j = 0; j < game.bl2.num_knights; j++) {

	  knight = game.wh2.knights[j];

	  if (!knight) continue;

	  knightmove = movement_knight(knight, totalpop, cs_black);

	  retval = add_mlspecific(base, game.wh2.knights+j, knightmove, WKNIGHT);
      
	}

      }

      {

	uint64_t rookmove;
	
	uint64_t rook;

	long int file, rank;

	for (j = 0; j < game.wh2.num_rooks; j++) {

	  rook = game.wh2.rooks[j];

	  if (!rook) continue;
	
	  rookmove = movement_rook(rook, totalpop, cs_black);

	  retval = add_mlspecific(base, game.wh2.rooks+j, rookmove, WROOK);
	  
	}
	
      }

      {

	uint64_t bishopmove;
	
	uint64_t bishop;

	long int file, rank;

	for (j = 0; j < game.wh2.num_bishops; j++) {

	  bishop = game.wh2.bishops[j];

	  if (!bishop) continue;
	
	  bishopmove = movement_bishop(bishop, totalpop, cs_black);

	  retval = add_mlspecific(base, game.wh2.bishops+j, bishopmove, WBISHOP);
	  
	}
	
      }

      {

	uint64_t queenmove;
	
	uint64_t queen;

	long int file, rank;

	for (j = 0; j < game.wh2.num_queens; j++) {

	  queen = game.wh2.queens[j];

	  if (!queen) continue;
	
	  queenmove = movement_queen(queen, totalpop, cs_black);

	  retval = add_mlspecific(base, game.wh2.queens+j, queenmove, WQUEEN);
	  
	}
	
      }
      
      {
	uint64_t kingmove;
	uint64_t king;
	long int file, rank;

	king = game.wh2.king;
	if (king) {
	  kingmove = movement_king(king, totalpop, cs_black);
	  retval = add_mlspecific(base, &game.wh2.king+0, kingmove, WKING);
	}

      }

      retval = ensure_boardmove(base, totalpop, cs_black);
      
      retval = remove_checks(&game, WKING, base, moveno);
      if (retval==-1) {
	printf("Trouble removing potential moves that leave king in check.\n");
	return -1;
      }

      counter = count_nodes(base);
      
      printf("%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

      if (!counter) {
	printf("Leaving, no moves to make.\n");
	return 0;
      }
      
      bytes_read = read(rnd_fd, &rnds, sizeof(uint64_t));
      if (bytes_read != sizeof(uint64_t)) {
	perror("read");
	return -1;
      }
      
      {
	selectno = ((double) counter) * rnds / 18446744073709551615.0; 
	printf("Selected moveno %ld\n", selectno);
      }

      pn = fetch_move(base, selectno);

      retval = fill_stringbuf(pn, strbuf, &dest_rank, &dest_file);
      if (retval==-1) {
	fprintf(stderr, "%s: Trouble filling coordinate pair.\n", __FUNCTION__);
	return -1;
      }
      
      {
	pos_t pos = game.positions[dest_rank*8+dest_file];

	if (pn->ptype != WKING && pos.ptype == WKING) {
	  if (pos.moveno_history == moveno) {
	    debug_out(&game, pn);
	    fprintf(stderr, "%s: White king randomly captured. Move %.4s.\n", __FUNCTION__, strbuf);
	    return 0;
	  }
	}	
      }      

      makemove_desc(pn);
      
      if (strbuf[0] == strbuf[2] && strbuf[1] == strbuf[3]) {
	debug_out(&game, pn);
	fprintf(stderr, "%s: Not moving to a different square.\n", __FUNCTION__);
	return -1;
      }     
      
      bytes_written = write(out_fd, strbuf, 4);

      assert(pn->pieceStart != NULL);
      
      set_position(game.positions, strbuf+2, pn->ptype, pn->pieceStart, moveno);       
      update_game(&game, pn, strbuf);

      {
	long int bitno = (dest_rank * 8 + (7 - dest_file));
	uint64_t mask = 1ULL << bitno;

	if (cs_black & mask) {
	  clear_position(game.positions, strbuf+2);
	}
	
      }
      
      apply_game2(&game);
      
      assert(game.wh.king);
      
    }

    delete_list(base);
    
  }
      
  //  add_ml(base, &game);
  
  return 0;

}
