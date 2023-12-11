#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

typedef enum {
  STATE_Key,
  STATE_Value,
  STATE_End
} STATE_t;

struct {
  char host[100];
  float reap_interval;
  float send_interval;
  int data_limit;
  char inst[20];
} config;

int main(void)
{
  char *str;
  size_t len = file_load("config.ini", &str);
  STATE_t state = STATE_Key;
  char key[100], value[100];
  uint8_t i = 0;

  while(*str)
  {
    if(state == STATE_Key) {
      if(*str == '=') {
        state = STATE_Value;
        key[i] = '\0';
        i = 0;
      }
      else if(*str == ' ');
      else if(*str == '\n' || *str == '\r') {
        i = 0;
      }
      else key[i++] = *str;
    }
    else if(state == STATE_Value) {
      if(*str == '\n' || *str == '\r') {
        state = STATE_End;
        value[i] = '\0';
        i = 0;
      }
      else if(*str == ' ');
      else value[i++] = *str;
    }
    if(state == STATE_End) {
      if(strcmp(key, "send_interval") == 0) {
        config.send_interval = atof(value);
      }
      printf("%s: %s\n", key, value);
      state = STATE_Key;
    }
    str++;
  }
}
  

