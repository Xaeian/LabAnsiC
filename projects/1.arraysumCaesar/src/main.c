#include <stdio.h>
#include <stdint.h>

#define ENTER "\n"

int ArraySum(int *ary, uint16_t length)
{
  int sum = 0;
  while(length) {
    sum += *ary;
    length--;
    ary++;
  }
  return sum;
}

#define RANGE 'Z' - 'A'
void CaesarCode_Print(char *str, int8_t offset)
{
  offset %= RANGE;
  while(*str) {
    char sign = *str;
    if(sign >= 'A' && sign <= 'Z') {
      sign += offset;
      if(sign > 'Z') { sign -= RANGE; }
      else if(sign < 'A') { sign += RANGE; }
    }
    printf("%c", sign);
    str++;
  }
}

#define LEN 6


int main(void)
{
  char *main_str = "#HeLLo-7WoRLd";
  CaesarCode_Print(main_str, 3);

  printf(ENTER);

  int main_ary[LEN] = { 1, 2, 3, 4, 5, 6};
  int sum = ArraySum(main_ary, LEN);
  printf("Suma: %i", sum);
}
