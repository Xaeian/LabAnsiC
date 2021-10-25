#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

const bool main_replace_array[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1
};
//if(!main_replace_array[*p]) {

int main(void)
{
  char str[] = "-+exa++m1=ple-+";
  char *p = str;
  bool separator_flag = false, start_flag = false;
  char separator_char = '-';

  while(*p) {
    if((*p >= '0' && *p <= '9') || (*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {  
      if(separator_flag && start_flag) printf("%c", separator_char);
      printf("%c", *p);
      separator_flag = false;
      start_flag = true;
    } else {
      separator_flag = true;
    }
    p++;
  }
  return 0;
}