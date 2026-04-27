#ifndef TIMECHECK_H
#define TIMECHECK_H
#include "sortAlgos.h"
#include "generatingNumbers.h"
#include <chrono>



double compareAsc(iterator first, iterator last, func);

double compareDesc(iterator first, iterator last, func);

double compareRand(iterator first, iterator last, func);

double compareConst(iterator first, iterator last, func);


#endif