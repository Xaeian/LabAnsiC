#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
  #include <Windows.h>
#else
  #include <unistd.h>
#endif

typedef struct {
  const char *name;
  uint16_t head;
  uint16_t tail;
  uint8_t *buffer;
  uint16_t length;
} BUFF_t;

#define DBG_SEND_SIZE 128

const char x_name[] = "x";
uint8_t x_array[64];
BUFF_t x_buff = {.name = x_name, .buffer = x_array, .length = sizeof(x_array)};

const char y_name[] = "y";
uint8_t y_array[DBG_SEND_SIZE];
BUFF_t y_buff = {.name = y_name, .buffer = y_array, .length = DBG_SEND_SIZE};

void BUFF_Push(BUFF_t *buff, uint8_t *buffer, uint16_t length)
{
  while (length--) {
    buff->buffer[buff->head++] = *buffer;
    buffer++;
    if(buff->head >= buff->length) buff->head = 0;
  }
}

bool BUFF_Send(BUFF_t *buff)
{
  if(buff->head != buff->tail) {
    printf("%s:%i ", buff->name, buff->buffer[buff->tail++]);
    if(buff->tail >= buff->length) buff->tail = 0;
    return true;
  } else return false;
}

int main(void)
{
  uint32_t a = 0x01020304;
  uint16_t b = 0x0506;

  uint8_t a_ary[4];
  a_ary[3] = (uint8_t)(a >> 24);
  a_ary[2] = (uint8_t)(a >> 16);
  a_ary[1] = (uint8_t)(a >> 8);
  a_ary[0] = (uint8_t)a;

  BUFF_Push(&x_buff, (uint8_t *)a_ary, 4);
  BUFF_Push(&y_buff, (uint8_t *)&a, 4);
  BUFF_Push(&y_buff, (uint8_t *)&b, 2);

  uint8_t run = 1;
  while (run)
  {
    Sleep(500);
    run = BUFF_Send(&y_buff);
    run += BUFF_Send(&x_buff);
  }
}