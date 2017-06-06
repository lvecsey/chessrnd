#ifndef PIECELOC_H
#define PIECELOC_H

#include <stdint.h>

typedef struct {
  uint64_t pawns;
  uint64_t rooks;
  uint64_t bishops;
  uint64_t knights;
  uint64_t king;
  uint64_t queens;
} pieceloc_t;

#endif
