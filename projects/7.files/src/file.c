#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file.h"

//---------------------------------------------------------------------------------------------------------------------

bool file_save(const char *name, char **bytes)
{
  FILE *fp = fopen(name, "wb");
  if (fp == NULL)
    return false;

  fprintf(fp, "%s", *bytes);
  fclose(fp);
}

int file_load(const char *name, char **bytes)
{
  size_t size = 0;
  FILE *fp = fopen(name, "rb");
  if (fp == NULL)
  {
    *bytes = NULL;
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  *bytes = (char *)malloc(size + 1);
  if (size != fread(*bytes, sizeof(char), size, fp))
  {
    free(*bytes);
    return -2;
  }
  fclose(fp);
  (*bytes)[size] = 0;
  return size;
}

//---------------------------------------------------------------------------------------------------------------------

bool data_save(const char *name, uint8_t **bytes, size_t size)
{
  FILE *fp = fopen(name, "wb");
  if (fp == NULL)
    return false;

  fwrite(*bytes, sizeof(uint8_t), size, fp);
  fclose(fp);
}

int data_load(const char *name, uint8_t **bytes)
{
  size_t size = 0;
  FILE *fp = fopen(name, "rb");
  if (fp == NULL)
  {
    *bytes = NULL;
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  *bytes = (char *)malloc(size);
  if (size != fread(*bytes, sizeof(char), size, fp))
  {
    free(*bytes);
    return -2;
  }
  fclose(fp);
  return size;
}

//---------------------------------------------------------------------------------------------------------------------

void putbytes(uint8_t *bytes, size_t size)
{
  for(size_t i = 0; i < size; i++)
  {
    putchar(*bytes);
    bytes++;
  }
}

//---------------------------------------------------------------------------------------------------------------------