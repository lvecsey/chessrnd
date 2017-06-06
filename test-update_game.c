
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "basegame.h"

#include "ml.h"

#include "update_game.h"

#include "collected_side.h"
#include "total_population.h"

#include "movement_knight.h"

#include "makemove.h"

#include "show_bitmask.h"

#include "fill_rankfile.h"

uint64_t expected_wknightmask1 = 0b0000000000000000000000000000000000000000100000000000000000000010;

uint64_t expected_wknightmask2 = 0b0000000000000000000000000000000000000000001000000000000000000010;

uint64_t expected_wknightmask3 = 0b0000000000000000000000000000000000000000000001000000000001000000;

uint64_t expected_wknightmask4 = 0b0000000000000000000000000000000000000000000000010000000001000000;

int main(int argc, char *argv[]) {

  struct ml *base = malloc(sizeof(struct ml));

  struct ml *pn;
  
  basegame_t game;
  
  uint64_t totalpop;
  uint64_t cs_white;
  uint64_t cs_black;

  long int file, rank;

  long int counter;

  char strbuf[4];
  
  int retval;

  int rnd_fd = open("/dev/urandom", O_RDONLY);
  uint64_t rnds;

  long int start_file, start_rank;
  long int dest_file, dest_rank;

  long int selectno;

  long int j;

  ssize_t bytes_read;
  
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

  retval = init_pieceloc2(&game.wh2);
  retval = init_pieceloc2(&game.bl2);  

  game.wh2.king = game.wh.king;

  game.wh2.rooks[0] = game.wh.rooks & (1UL << 7);
  game.wh2.rooks[1] = game.wh.rooks & (1UL << 0);  

  game.wh2.knights[0] = game.wh.knights & (1UL << 6);
  game.wh2.knights[1] = game.wh.knights & (1UL << 1);  

  game.wh2.bishops[0] = game.wh.bishops & (1UL << 5);
  game.wh2.bishops[1] = game.wh.bishops & (1UL << 2);  

  game.wh2.queens[0] = game.wh.queens;

  for (file = 0; file < 8; file++) {
    game.wh2.pawns[file] = game.wh.pawns & (1UL << (15 - file));
  }
  
  game.bl2.king = game.bl.king;  

  game.bl2.rooks[0] = game.bl.rooks & (1UL << 63);
  game.bl2.rooks[1] = game.bl.rooks & (1UL << 56);

  game.bl2.knights[0] = game.bl.knights & (1UL << 62);
  game.bl2.knights[1] = game.bl.knights & (1UL << 57);    

  game.bl2.bishops[0] = game.bl.bishops & (1UL << 5);
  game.bl2.bishops[1] = game.bl.bishops & (1UL << 2);  

  game.bl2.queens[0] = game.bl.queens;

  for (file = 0; file < 8; file++) {
    game.bl2.pawns[file] = game.bl.pawns & (1UL << (55 - file));
  }
  
  base->next = NULL;
    
  totalpop = total_population(&game.wh, &game.bl);

  cs_white = collected_side(&game.wh);
  cs_black = collected_side(&game.bl);  

  {
    uint64_t knightmove;

    uint64_t knight;

    long int file, rank;
    
    for (j = 0; j < game.wh2.num_knights; j++) {

      knight = game.wh2.knights[j];

      if (!knight) continue;

      fill_rankfile(knight, &start_rank, &start_file);

      printf("Moving knight on square %c%c\n", 'a' + start_file, '1' + start_rank);
      
      knightmove = movement_knight(knight, totalpop, cs_black);

      retval = add_mlspecific(base, game.wh2.knights+j, knightmove, WKNIGHT);
      
    }

  }

  counter = count_nodes(base);
      
  printf("%s: Counted %ld moves, for white.\n", __FUNCTION__, counter);

  bytes_read = read(rnd_fd, &rnds, sizeof(uint64_t));

  {
    selectno = ((double) counter) * rnds / 18446744073709551615.0; 
    printf("Selected moveno %ld\n", selectno);
  }
  
  pn = fetch_move(base, selectno);
  fill_rankfile(*pn->pieceStart, &start_rank, &start_file);
  fill_rankfile(pn->ploc, &dest_rank, &dest_file);	

  makemove_desc(pn);
  
  strbuf[0] = 'a' + start_file;
  strbuf[1] = '1' + start_rank;
  strbuf[2] = 'a' + dest_file;
  strbuf[3] = '1' + dest_rank;
  
  retval = update_game(&game, pn, strbuf);

  show_bitmask(game.wh2.knights[0]);
  show_bitmask(game.wh2.knights[1]);  
  
  if (game.wh.knights == expected_wknightmask1 || game.wh.knights == expected_wknightmask2) {

    printf("SUCCESS");
    return 0;

  }

    if (game.wh.knights == expected_wknightmask3 || game.wh.knights == expected_wknightmask4) {

    printf("SUCCESS");
    return 0;

  }
  
  printf("FAILURE");
  
  return 0;

}
