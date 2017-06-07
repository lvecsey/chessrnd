
#include "basegame.h"

#include "ml.h"

int debug_out(basegame_t *game, struct ml *pn) {
  
  show_ml(pn);
  show_positions(game->positions);

  return 0;
  
}
