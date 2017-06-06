#ifndef TOTAL_POPULATION_H
#define TOTAL_POPULATION_H

#include "collected_side.h"

#define total_population(pl1, pl2) ( collected_side(pl1) | collected_side(pl2) )

#endif
