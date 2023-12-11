#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------------------------------------------------

#ifndef LIST_BOOKING_MARGIN
#define LIST_BOOKING_MARGIN 1
#endif
#define LIST_BOOKING_DEFAULT 32

//---------------------------------------------------------------------------------------------------------------------

typedef enum {
  LIST_TYPE_8 = 1,
  LIST_TYPE_16 = 2,
  LIST_TYPE_32 = 4,
  LIST_TYPE_64 = 8
} LIST_Type_e;

typedef struct {
  LIST_Type_e type; // setting
  uint16_t booking; // setting
  size_t limit;
  size_t size;
  void *buffer;
} LIST_t;

//---------------------------------------------------------------------------------------------------------------------

void *LIST_Init(LIST_t *list);

void *LIST_Set(LIST_t *list, void *data, size_t size);
void *LIST_Conn(LIST_t *list, void *data, size_t size);
void *LIST_PushList(LIST_t *list, int count, ...);
void *LIST_PushPointerList(LIST_t *list, void *data, ...);
void *LIST_Push(LIST_t *list, uint64_t data);
uint64_t LIST_Get(LIST_t *list, size_t index);
void LIST_Print(LIST_t *list);

void *LIST_SetString(LIST_t *list, const char *string);
void *LIST_ConnString(LIST_t *list, char *string);
void *LIST_PushChars(LIST_t *list, char data, ...);
void *LIST_PushChar(LIST_t *list, char data);
void LIST_PrintString(LIST_t *list);

//---------------------------------------------------------------------------------------------------------------------