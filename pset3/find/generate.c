/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // check if any argument is provided, if not notify that this program needs atleast one number
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // convert the first argument into integer number & store it in variable n
    int n = atoi(argv[1]);


    // check if second (seed) argument is provided,
    //if yes then make it as a seed number using srand, 
    //which will will be used in rand for creating same result when required
    //if not provided, then give srand a default seed as current time value converted to unsigned int which will be different everytime
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // generate & print number , n many times using rand & make sure it's less than the maximum range - LIMIT
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }

    // done
    return 0;
}
