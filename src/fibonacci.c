#include <math.h>

#include "fibonacci.h"

/*
 *  Calculates the nth term of the Fibonacci sequence using a closed form.
 *
 *  @param      n      position of the term in the sequence.
 *  @return            term on the nth position.
 */
int getNthTermFromFibonacci(int n)
{
    return floor((pow((1.0 + sqrt(5.0)) / 2.0, n) - pow((1.0 - sqrt(5.0)) / 2.0, n)) / sqrt(5.0));
}


int triangular(int n)
{
    return (n * (n + 1)) / 2;
}

/*
 *  Calculates the nth term of the real Fibonacci sequence using a closed form.
 *
 *  @param      n      term on the ntg position.
 */
int realFibonacciSequence(int n)
{
    int k = 0;

    while (n > triangular(k))
    {
        k++;
    }

    return getNthTermFromFibonacci(n - triangular(k - 1));
}
