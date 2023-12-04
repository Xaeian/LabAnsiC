#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "list.h"

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
  LIST_SetString(&string, "Hel");
  LIST_PushChars(&string, 'l', 'o', 0);
  LIST_PushChar(&string, ' ');
  LIST_ConnString(&string, "World");
  LIST_PrintString(&string);
}

int main() {
  Tests();
}