#ifndef _FILE_H_
#define _FILE_H_

//---------------------------------------------------------------------------------------------------------------------

bool file_save(const char *name, char **bytes);
int file_load(const char *name, char **bytes);
bool data_save(const char *name, uint8_t **bytes, size_t size);
int data_load(const char *name, uint8_t **bytes);
void putbytes(uint8_t *bytes, size_t size);

//---------------------------------------------------------------------------------------------------------------------

#endif