#ifndef DELAYTIME_H
#define DELAYTIME_H

#include <conio.h>
#include <time.h>

// fn nay se delay time trong "s" giay
void delayTimeIn(int s)
{
    for (int i = 0; i < s; i++)
    {
        delay(1);
    }
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

#endif