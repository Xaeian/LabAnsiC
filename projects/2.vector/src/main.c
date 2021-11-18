#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Funkcja wypełnia przekazaną tablice 'array' wartościami od 'min' do 'max' co '1'.
 * @param array zadeklarowana tablica.
 * @param min wartość, od której zaczyna wypełniać się tablica.
 * @param min wartość,  na której kończy wypełniać się tablica.
 * @param limit długość zadeklarowanej tablicy.
 * @retval liczba elementów, którymi została wypełniona tablica.
 * Zwraca '0' jeżeli limit < abs(max - min).
 */
uint16_t FillArray32MinMax(int32_t array[], int32_t min, int32_t max, uint16_t limit)
{
  uint16_t i = 0;
  while(min != max) {
    if(max > min) array[i++] = min++;
    else array[i++] = min--;
    if(!--limit) return 0;
  };
  array[i++] = min;
  return i;
}

/**
 * Funkcja tworzy tablicę 'array' i wypełnia ją wartościami od 'min' do 'max' co '1'. 
 * @param array wskaźnik na niezadeklarowaną tablicę
 * @param min wartość, od której zaczyna wypełniać się tablica.
 * @param min wartość, na której kończy wypełniać się tablica.
 * @retval długość zwróconej tablicy.
 */
uint16_t GetArray32MinMax(int32_t *array[], int32_t min, int32_t max)
{
  uint16_t length;
  if(max > min) length = (uint16_t)(max - min + 1);
  else length = (uint16_t)(min - max + 1);

  *array = (int32_t *)malloc(length * sizeof(int32_t));
  return FillArray32MinMax(*array, min, max, length);
}

/**
 * Wektor typu uint32_t
 * @param buffer wskaźnik na zawartość wektora
 * @param length długość wektora
 */
typedef struct vectorType {
  int32_t *buffer;
  uint16_t length;
} vector_t;

/**
 * Funkcja tworzy wektor 'vector_t' i wypełnia go wartościami od 'min' do 'max' co '1'.
 * @param min wartość, od której zaczyna wypełniać się tablica.
 * @param min wartość, na której kończy wypełniać się tablica.
 * @retval wektor 'vector_t'.
 */
vector_t vectorInit(int32_t min, int32_t max)
{
  vector_t vector;
  vector.length = GetArray32MinMax(&vector.buffer, min, max);
  return vector;
}

/**
 * Funkcja sprawdza, czy wektor jest zainicjowany.
 * @param vector wskaźnika na wektor 'vector_t'.
 * @retval true: wektor zainicjowany, false: wektor niezainicjowany.
 */
bool vectorIsSet(vector_t *vector)
{
  if(vector->length) return true;
  else false;
}

// #define ARRAY_LENGTH 16

int main(void)
{
  /*
  int32_t array[ARRAY_LENGTH];
  uint16_t length = FillArray32MinMax(array, -5, 10, ARRAY_LENGTH);
  
  int32_t *array;
  uint16_t length = GetArray32MinMax(&array, -5, 10);

  if(length) {
    for(int i = 0; i < length; i++) printf("%d ", array[i]);
  }
  else printf("error");
  */

  vector_t vector = vectorInit(5, 20);
  
  if(vectorIsSet(&vector)) {
    for(int i = 0; i < vector.length; i++) printf("%d ", vector.buffer[i]);
  }
  else printf("error");
  return 0;
}