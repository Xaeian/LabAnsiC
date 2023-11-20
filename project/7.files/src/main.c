#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int load_my_file(const char *name, char **bytes)
{
  FILE *fp = fopen(name, "r+");
  if (fp == NULL) {
    return -1;
  }

  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  *bytes = (char *)malloc(size + 1);
  (*bytes)[size] = 0;

  if (size == fread(*bytes, sizeof(char), size, fp)) {
    free(*bytes);
    return -2;
  }
  fclose(fp);
  return size;
}

int main(void)
{
  char *string;
  int size = load_my_file("./test.txt", &string);
  if(size > 0) {
    putbytes(string, size);
  }
}