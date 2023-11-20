#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

//----------------------------------------------------------------------------- <--- Prime Numbers

int PrimeNumbers(uint64_t start, uint64_t end)
{
  uint64_t nbr64[end];
  size_t size = 0;
  size_t print = 0;

  bool prime;
  for(int nbr = 2; nbr <= end; nbr++)
  {
    prime = true;
    for(int i = 0; i < size; i++)
    {
      if(nbr64[i] > sqrt(nbr)) break;
      if(nbr % nbr64[i] == 0) {
        prime = false;
        break;
      }
    }
    if(prime) {
      if(!print && nbr >= start) print = size;
      nbr64[size] = nbr;
      size++;
    }
  }

  printf("%lld ", size);

  for(int i = print; i < size; i++)
  {
    printf("%lld ", nbr64[i]);
  }
}

//----------------------------------------------------------------------------- <--- Main

#define START 100100

int main(void)
{
  PrimeNumbers(START, START + 100);
}