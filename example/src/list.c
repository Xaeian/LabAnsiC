#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "list.h"

//---------------------------------------------------------------------------------------------------------------------

void *LIST_Init(LIST_t *list)
{
  list->size = 0;
  list->limit = list->booking * (LIST_BOOKING_MARGIN + 1);
  list->buffer = malloc(list->type * list->limit);
  return list->buffer;
}

//---------------------------------------------------------------------------------------------------------------------

void *LIST_Set(LIST_t *list, void *data, size_t size)
{
  int new = (size + list->booking) / list->booking;
  int old = list->limit / list->booking;

  if (new > old || new - LIST_BOOKING_MARGIN < old)
  {
    list->limit = (size_t)((size + list->size + list->booking) / list->booking) * list->booking;
    void *new_buffer = malloc(list->type * list->limit);
    if (!new_buffer) return NULL;
    list->buffer = new_buffer;
  }
  memcpy(list->buffer, data, list->type * size);
  list->size = size;
  return list->buffer;
}

void *LIST_Conn(LIST_t *list, void *data, size_t size)
{
  if (size + list->size > list->limit)
  {
    list->limit = (size_t)((size + list->size + list->booking) / list->booking) * list->booking;
    void *new_buffer = malloc(list->type * list->limit);
    if (!new_buffer) return NULL;
    memcpy(new_buffer, list->buffer, list->type * list->size);
    free(list->buffer);
    list->buffer = new_buffer;
  }
  memcpy((void *)(list->buffer + list->type * list->size), data, list->type * size);
  list->size += size;

  return list->buffer;
}

void *LIST_PushList(LIST_t *list, int count, ...)
{
  va_list args; 
  va_start(args, count);
  uint64_t data;
  void *buffer;
  for (int i = 0; i < count; i++) {
    data = va_arg(args, uint64_t);
    buffer = LIST_Conn(list, (void *)&data, 1);
  }
  va_end(args);
  return buffer;
}

void *LIST_PushPointerList(LIST_t *list, void *data, ...)
{
  if(list->size) list->size--;
  va_list args; va_start(args, data);
  void *buffer;
  while(data) {
    buffer = LIST_Conn(list, data, 1);
    data = va_arg(args, void *);
  }
  va_end(args);
  return buffer;
}

//---------------------------------------------------------------------------------------------------------------------

static void LIST_Print_int8(LIST_t *list)
{
  int8_t *array = (int8_t *)list->buffer;
  char string[4];
  for(int i = 0; i < list->size; i++) {
    itoa(*array, string, 10);
    puts(string);
    putchar(' ');
    array++;
  }
}

static void LIST_Print_int16(LIST_t *list)
{
  int16_t *array = (int16_t *)list->buffer;
  char string[6];
  for(int i = 0; i < list->size; i++) {
    itoa(*array, string, 10);
    puts(string);
    putchar(' ');
    array++;
  }
}

static void LIST_Print_int32(LIST_t *list)
{
  int32_t *array = (int32_t *)list->buffer;
  char string[11];
  for(int i = 0; i < list->size; i++) {
    itoa(*array, string, 10);
    puts(string);
    putchar(' ');
    array++;
  }
}

static void LIST_Print_uint8(LIST_t *list)
{
  uint8_t *array = (uint8_t *)list->buffer;
  char string[4];
  for(int i = 0; i < list->size; i++) {
    utoa(*array, string, 10);
    puts(string);
    putchar(' ');
    array++;
  }
}

static void LIST_Print_uint16(LIST_t *list)
{
  uint16_t *array = (uint16_t *)list->buffer;
  char string[6];
  for(int i = 0; i < list->size; i++) {
    utoa(*array, string, 10);
    puts(string);
    putchar(' ');
    array++;
  }
}

static void LIST_Print_uint32(LIST_t *list)
{
  uint32_t *array = (uint32_t *)list->buffer;
  char string[11];
  for(int i = 0; i < list->size; i++) {
    utoa(*array, string, 10);
    puts(string);
    putchar(' ');
    array++;
  }
}

void LIST_Print(LIST_t *list)
{
  switch(list->type) {
    case LIST_TYPE_8:  //poo
    case LIST_TYPE_16: //ooo
    case LIST_TYPE_32: //;
    case LIST_TYPE_64: //8
  }
}

//--------------------------------------------------------------------------------------------------------------------- <--- String

void *LIST_SetString(LIST_t *list, const char *string)
{
  return LIST_Set(list, (void *)string, strlen(string) + 1);
}

void *LIST_ConnString(LIST_t *list, char *string)
{
  if(list->size) list->size--;
  return LIST_Conn(list, (void *)string, strlen(string) + 1);
}

void *LIST_PushChars(LIST_t *list, int data, ...)
{
  if(list->size) list->size--;
  va_list args; va_start(args, data);
  while (data) {
    LIST_Conn(list, (void *)&data, 1);
    data = va_arg(args, int);
  }
  va_end(args);
  return LIST_Conn(list, (void *)&data, 1);
}

//---------------------------------------------------------------------------------------------------------------------