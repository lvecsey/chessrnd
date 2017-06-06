#ifndef ML_H
#define ML_H

#include <stdint.h>

#include "basegame.h"

enum { WPAWN, BPAWN, WROOK, BROOK, WKNIGHT, BKNIGHT, WBISHOP, BBISHOP, WKING, BKING, WQUEEN, BQUEEN };

struct ml {

  uint64_t *pieceStart;
  
  long int ptype;
  uint64_t ploc;

  struct ml *next;

};

int add_ml(struct ml *base, basegame_t *bg);

int add_mlspecific(struct ml *base, uint64_t *pieceStart, uint64_t pieceloc, long int ptype);

int delete_last(struct ml *base);

int delete_list(struct ml *base);

long int count_nodes(struct ml *base);

int piece_descr(long int ptype);

int remove_entry(struct ml *base, struct ml *entry);

#endif
