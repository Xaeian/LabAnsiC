#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

uint32_t hash(char *str) {
  uint32_t hash = 5381;
  uint32_t c;
  while((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}

void print(char *str) {
  printf("%s: %u\n", str, hash(str));
}

int main(void)
{
  print("temp");
  print("temperature");
  print("vibes");
  print("vibrations");
  print("val");
  print("values");
  print("baud");
  print("baudrate");

}

  // HASH_Temp = 1,
  // HASH_Temperature = 2,
  // HASH_Vibes = 3,
  // HASH_Vibrations = 3,
  // HASH_Val = 4,
  // HASH_Values = 5,
  // HASH_Baud = 2090105025,
  // HASH_Baudrate = 1


// int main(void)
// {
//   char str[] = "-+Exa++X1=plE-+";
//   char *p = str;
//   bool separator_flag = false, start_flag = false;
//   char separator_char = '-';
//   while(*p) {
//     if((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {  
//       if(separator_flag && start_flag) printf("%c", separator_char);
//       printf("%c", LowerChar[*p]);
//       separator_flag = false;
//       start_flag = true;
//     } else {
//       separator_flag = true;
//     }
//     p++;
//   }
//   return 0;
// }



