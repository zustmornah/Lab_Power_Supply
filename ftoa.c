/*
 * ftoa.c
 *
 *  Created on: Jun 12, 2017
 *      Author: Adom_Kwabena
 */

#include <math.h>
#include "ftoa.h"
// Function to convert float to string
// Based on the work of https://gist.github.com/psych0der/6319244
void float_to_string(float f, char* string)
{
    int a;
    int b;
    int c;
    int k;
    int l = 0;
    int m;
    int i = 0;

    // Handle negative float
    if (f < 0)
    {
        string[i++] = '-';
        f *= -1;
    }

    a = f;
    f -= a;
    k = PRECISION;

    // Number of digits in whole number
    while (k > -1)
    {
        l = pow(10, k);
        m = a / l;
        if (m > 0)
        {
            break;
        }
        k--;
    }

    // Extract individual digits before decimal point
    for (l = k + 1; l > 0; l--)
    {
        b = pow(10, l - 1);
        c = a / b;
        string[i++] = c + '0';
        a %= b;
    }

    string[i++] = '.';

    for (l = 0; l < PRECISION; l++)
    {
        f *= 10.0;
        b = f;
        string[i++] = b + '0';
        f -= b;
    }

    string[i] = '\0';
}

