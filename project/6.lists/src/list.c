#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "list.h"

//---------------------------------------------------------------------------------------------------------------------

void *LIST_Init(LIST_t *list)
{
  list->size = 0;
  if(!list->booking) list->booking = LIST_BOOKING_DEFAULT;
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

void *LIST_Push(LIST_t *list, uint64_t data)
{
  LIST_Conn(list, &data, 1);
}

static uint8_t LIST_Get8(LIST_t *list, size_t index)
{
  uint8_t *array = (uint8_t *)list->buffer;
  return array[index];
}

static uint16_t LIST_Get16(LIST_t *list, size_t index)
{
  uint16_t *array = (uint16_t *)list->buffer;
  return array[index];
}

static uint32_t LIST_Get32(LIST_t *list, size_t index)
{
  uint32_t *array = (uint32_t *)list->buffer;
  return array[index];
}

static uint64_t LIST_Get64(LIST_t *list, size_t index)
{
  uint64_t *array = (uint64_t *)list->buffer;
  return array[index];
}

uint64_t LIST_Get(LIST_t *list, size_t index)
{
  uint64_t value;
  switch(list->type) {
    case LIST_TYPE_8: value = (uint8_t)LIST_Get8(list, index); break;
    case LIST_TYPE_16: value = (uint16_t)LIST_Get16(list, index); break;
    case LIST_TYPE_32: value = (uint32_t)LIST_Get32(list, index); break;
    case LIST_TYPE_64: value = LIST_Get64(list, index); break;
  }
  return value;
}

//---------------------------------------------------------------------------------------------------------------------

static void LIST_Print8(LIST_t *list)
{
  uint8_t *array = (uint8_t *)list->buffer;
  char string[4];
  for(int i = 0; i < list->size; i++) {
    itoa(*array, string, 10);
    printf("%s ", string);
    array++;
  }
  printf("\r\n");
}

static void LIST_Print16(LIST_t *list)
{
  uint16_t *array = (uint16_t *)list->buffer;
  char string[6];
  for(int i = 0; i < list->size; i++) {
    itoa(*array, string, 10);
    printf("%s ", string);
    array++;
  }
  printf("\r\n");
}

static void LIST_Print32(LIST_t *list)
{
  uint32_t *array = (uint32_t *)list->buffer;
  char string[11];
  for(int i = 0; i < list->size; i++) {
    itoa(*array, string, 10);
    printf("%s ", string);
    array++;
  }
  printf("\r\n");
}

static void LIST_Print64(LIST_t *list)
{
  uint64_t *array = (uint64_t *)list->buffer;
  char string[20];
  for(int i = 0; i < list->size; i++) {
    ulltoa(*array, string, 10);
    printf("%s ", string);
    array++;
  }
  printf("\r\n");
}

void LIST_Print(LIST_t *list)
{
  switch(list->type) {
    case LIST_TYPE_8: LIST_Print8(list); break;
    case LIST_TYPE_16: LIST_Print16(list); break;
    case LIST_TYPE_32: LIST_Print32(list); break;
    case LIST_TYPE_64: LIST_Print64(list); break;
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

void *LIST_PushChars(LIST_t *list, char data, ...)
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

void *LIST_PushChar(LIST_t *list, char data)
{
  char push[] = { data, 0 };
  return LIST_PushChars(list, data, 0);
}

void LIST_PrintString(LIST_t *list)
{
  char *p = (char *)list->buffer;
  size_t size = list->size;
  while(size) {
    putchar(*p);
    p++;
    size--;
  }
}

//---------------------------------------------------------------------------------------------------------------------