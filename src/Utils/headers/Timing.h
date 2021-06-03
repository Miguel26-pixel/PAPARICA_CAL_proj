#ifndef CAL_PROJ_TIMING_H
#define CAL_PROJ_TIMING_H

#include <unistd.h>

/**
 * Stores the current time into 'start' variable.
 */
void initTime();

/**
 * Calculates the difference between the current time and the 'start' time.
 * @return Number of microseconds passed.
 */
long calculatePerformance();

#endif //CAL_PROJ_TIMING_H
