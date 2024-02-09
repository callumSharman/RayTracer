#ifndef _INTERVAL_H_
#define _INTERVAL_H_

typedef struct interval interval_t;

struct interval {
    double min;
    double max;
};

/* initialise interval instance. Takes min and max */
interval_t interval_init(double min, double max);

/* does the interval contain x */
int interval_contains(interval_t inter, double x);

/* does the interval contain x BUT x cannot be the min or max */
int interval_surrounds(interval_t inter, double x);

#endif