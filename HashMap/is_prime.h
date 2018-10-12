#ifndef IS_PRIME_H
#define IS_PRIME_H

namespace PrimeProject {

// Internal method to test if a positive number is prime.
bool IsPrime(size_t n) {
  if( n == 2 || n == 3 )
    return true;

  if( n == 1 || n % 2 == 0 )
    return false;

  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;

  return true;
}

// Internal method to return a prime number at least as large as n.
int NextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;
  while (!IsPrime(n)) n += 2;
  return n;
}

}  // namespace PrimeProject

#endif
