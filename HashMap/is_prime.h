/*
 *  is_prime.h
 *  Created on: October 27, 2018
 *  Author: Tushar Malakar
 */


#ifndef IS_PRIME_H
#define IS_PRIME_H
#include <cstddef>

class prime{

public:
    bool isPrime( size_t n )
   {
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
   }


 //If a number is not Prime, get next Prime


 int nextPrime( size_t n )
 {
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;
    return n;
 }
};
#endif
