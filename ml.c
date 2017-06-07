#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <errno.h>

#include "basegame.h"

#include "ml.h"

int show_ml(struct ml *pn) {

  printf("pn->ptype = %ld\n", pn->ptype);
  printf("pn->ploc = %lu\n", pn->ploc);
  printf("pn->pieceStart = %p\n", pn->pieceStart);
  if (pn->pieceStart != NULL) {
    printf("pn->pieceStart[value] = %lu\n", pn->pieceStart[0]);
  }

  putchar('\n');

  return 0;
  
}

int piece_descr(long int ptype) {

  char *str = NULL;

  switch(ptype) {
  case WPAWN: str="WPAWN"; break;
  case BPAWN: str="BPAWN"; break;
  case WROOK: str="WROOK"; break;
  case BROOK: str="BROOK"; break;
  case WKNIGHT: str="WKNIGHT"; break;
  case BKNIGHT: str="BKNIGHT"; break;
  case WBISHOP: str="WBISHOP"; break;
  case BBISHOP: str="BBISHOP"; break;
  case WQUEEN: str="WQUEEN"; break;
  case BQUEEN: str="BQUEEN"; break;
  case WKING: str="WKING"; break;
  case BKING: str="BKING"; break;
  };    

  printf("%s", str);
  
  return 0;
  
}

int add_ml(struct ml *base, basegame_t *bg) {

  return 0;

}

int add_mlspecific(struct ml *base, uint64_t *pieceStart, uint64_t pieceloc, long int ptype) {

  long int bitno = 63;

  uint64_t mask = 1ULL << bitno;
  
  struct ml *pn;
  
  while (mask) {

    if (pieceloc & mask) {

      pn = malloc(sizeof(struct ml));
      if (pn==NULL) {
	perror("malloc");
	return -1;
      }

      pn->pieceStart = pieceStart;
      if (pn->pieceStart == NULL) {
	pn->pieceStart = malloc(sizeof(uint64_t));
	if (pn->pieceStart==NULL) {
	  perror("malloc");
	  return -1;
	}
	pn->pieceStart[0] = mask; 
      }
      
      pn->ptype = ptype;
      pn->ploc = mask;
      pn->next = base->next;

      base->next = pn;
      
    }

    mask >>= 1UL;

  }

  return 0;
  
}

long int count_nodes(struct ml *base) {

  long int counter = 0;
  
  struct ml *pn = base->next;

  while (pn != NULL) {
    counter++;
    pn = pn->next;
  }

  return counter;
	
}

int delete_last(struct ml *base) {

  struct ml *pn = base;

  while (pn->next != NULL) {

    if (pn->next->next == NULL) break;
    
    pn = pn->next;
    
  }

  if (pn->next != NULL) 
    if (pn->next->next == NULL) {

      free(pn->next);

      pn->next = NULL;
      
    }

  return 0;
  
}

int delete_list(struct ml *base) {

  while (base->next != NULL) {
    delete_last(base);
  }
  
  return 0;

}

int remove_entry(struct ml *base, struct ml *entry) {

  struct ml *pn = base;

  while (pn->next != entry) {

    if (pn->next == NULL) break;

    pn = pn->next;
    
  }

  if (pn->next == entry) {
  
    pn->next = entry->next;
  
    free(pn->next);

  }
    
  return 0;
  
}
