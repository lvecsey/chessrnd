#ifndef PIECELOC2_H
#define PIECELOC2_H

#include <stdint.h>

typedef struct {

  uint64_t king;

  uint64_t *pawns;

  long int num_rooks;
  uint64_t *rooks;

  long int num_knights;
  uint64_t *knights;
  
  long int num_bishops;
  uint64_t *bishops;
  
  long int num_queens;
  uint64_t *queens;
  
} pieceloc2_t;

int init_pieceloc2(pieceloc2_t *pl2);

int show_pieceloc2(pieceloc2_t *pl2);

#endif
