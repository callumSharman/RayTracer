#include "interval.h"

/* initialise interval instance. Takes min and max */
interval_t interval_init(double min, double max){
    interval_t inter;
    inter.min = min;
    inter.max = max;
    return inter;
}

/* does the interval contain x */
int interval_contains(interval_t inter, double x){
    return((x >= inter.min) && (x <= inter.max));
}

/* does the interval contain x BUT x cannot be the min or max */
int interval_surrounds(interval_t inter, double x){
    return((inter.min < x) && (x < inter.max));
}

/* clamps a double to be within the interval */
double interval_clamp(interval_t inter, double x){
    if(x < inter.min) return inter.min;
    if(x > inter.max) return inter.max;
}

