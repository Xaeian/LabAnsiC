#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "list.h"

//----------------------------------------------------------------------------- <--- Tests

int Tests(void)
{
  LIST_t nbr32 = { .type = LIST_TYPE_32 };
  LIST_Init(&nbr32);
  const uint32_t nbr32_set[] = {12, 428, 64};
  LIST_Set(&nbr32, (void *)nbr32_set, sizeof(nbr32_set) / sizeof(uint32_t));
  LIST_Push(&nbr32, 191);
  LIST_Push(&nbr32, 47);
  LIST_Print(&nbr32);

  LIST_t nbr8 = { .type = LIST_TYPE_8 };
  LIST_Init(&nbr8);
  const uint8_t nbr8_set[] = {12, 172, 64};
  LIST_Set(&nbr8, (void *)nbr8_set, sizeof(nbr8_set) / sizeof(uint8_t));
  LIST_Push(&nbr8, 291);
  LIST_Push(&nbr8, 47);
  LIST_Print(&nbr8);

  LIST_t string = { .type = LIST_TYPE_8 };
  LIST_Init(&string);
  LIST_SetString(&string, "Hell");
  LIST_PushChars(&string, 'o', 'w', 0);
  LIST_PushChar(&string, ' ');
  LIST_ConnString(&string, "World");
  LIST_PrintString(&string);
}

//----------------------------------------------------------------------------- <--- Prime Numbers

int PrimeNumbers(uint64_t start, uint64_t end)
{
  LIST_t nbr64 = { .type = LIST_TYPE_64 };
  LIST_Init(&nbr64);
  uint64_t value;
  size_t print = 0;

  bool prime;
  for(int nbr = 2; nbr <= end; nbr++)
  {
    prime = true;
    for(int i = 0; i < nbr64.size; i++)
    {
      value = LIST_Get(&nbr64, i);
      if(value > sqrt(nbr)) break;
      if(nbr % value == 0) {
        prime = false;
        break;
      }
    }
    if(prime) {
      if(!print && nbr >= start) print = nbr64.size;
      LIST_Push(&nbr64, nbr);
    }
  }

  for(int i = print; i < nbr64.size; i++)
  {
    printf("%lld ", LIST_Get(&nbr64, i));
  }
}

//----------------------------------------------------------------------------- <--- Main

#define START 10001000

int main(void)
{
  //Tests();
  PrimeNumbers(START, START + 100);
}