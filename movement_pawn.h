#ifndef MOVEMENT_PAWN_H
#define MOVEMENT_PAWN_H

#include <stdint.h>

uint64_t movement_wpawn(uint64_t wpawn, uint64_t totalpop, uint64_t blackpieces);

uint64_t movement_bpawn(uint64_t wpawn, uint64_t totalpop, uint64_t blackpieces);

#endif
