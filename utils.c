#include <stdio.h>
#include "utils.h"


/* Prints a progress bar to the console. Put within a loop, 
   give the current progress and the total (how much progress 
   should be when finished) */
void printProgress(int progress, int total) {
    const int barWidth = 50;
    int filledWidth = barWidth * progress / total;

    printf("[");
    
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            printf("#");
        } else {
            printf(" ");
        }
    }

    printf("] %d%%\r", progress * 100 / total);
    fflush(stdout);  // Flush the output to ensure immediate update
}