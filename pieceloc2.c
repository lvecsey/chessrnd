
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdint.h>

#include "pieceloc2.h"

#include "show_bitmask.h"

int show_pieceloc2(pieceloc2_t *pl2) {

  long int rank, file;

  long int j;
  
  printf("Pawns:\n");
  for (file = 0; file < 8; file++) {
    show_bitmask(pl2->pawns[file]);
  }

  printf("King:\n");
  show_bitmask(pl2->king);

  printf("Queens:\n");
  for (j = 0; j < pl2->num_queens; j++) {
    if (pl2->queens[j]) {
      show_bitmask(pl2->queens[j]);
    }
  }

  printf("Rooks:\n");
  for (j = 0; j < pl2->num_rooks; j++) {
    if (pl2->rooks[j]) {
      show_bitmask(pl2->rooks[j]);
    }
  }

  printf("Knights:\n");
  for (j = 0; j < pl2->num_knights; j++) {
    if (pl2->knights[j]) {
      show_bitmask(pl2->knights[j]);
    }
  }

  printf("Bishops:\n");
  for (j = 0; j < pl2->num_bishops; j++) {
    if (pl2->bishops[j]) {
      show_bitmask(pl2->bishops[j]);
    }
  }
  
  
  return 0;
  
}

int init_pieceloc2(pieceloc2_t *pl2) {

  pl2->pawns = calloc(8, sizeof(uint64_t));
  if (pl2->pawns==NULL) {
    perror("calloc");
    return -1;
  }
  
  pl2->num_rooks = 8 + 2;
  pl2->rooks = calloc(pl2->num_rooks, sizeof(uint64_t));
  if (pl2->rooks==NULL) {
    perror("calloc");
    return -1;
  }
  
  pl2->num_knights = 8 + 2;
  pl2->knights = calloc(pl2->num_knights, sizeof(uint64_t));
  if (pl2->knights==NULL) {
    perror("calloc");
    return -1;
  }
  
  pl2->num_bishops = 8 + 2;
  pl2->bishops = calloc(pl2->num_bishops, sizeof(uint64_t));
  if (pl2->bishops==NULL) {
    perror("calloc");
    return -1;
  }
  
  pl2->num_queens = 8 + 2;
  pl2->queens = calloc(pl2->num_queens, sizeof(uint64_t));
  if (pl2->queens==NULL) {
    perror("calloc");
    return -1;
  }
  
  return 0;

}
