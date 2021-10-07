## Dlaczego C

Na języki programowania warto patrzeć jak na narzędzia. A narzędzia jak to narzędzia, często są dość uniwersalne, jednak zawsze mają określone zadanie, z którym radzą sobie dobrze. A jak jakieś narzędzie radzi sobie z czymś najlepiej ciężko, żeby znikło z skrzynki narzedziowej.

Dla języka **C** taką niszą są systemy wbudowane (embeded system)...

## Konfiguracja środowiska

Kompilowanie i debugowanie programów w języku **C** oraz innych języków kompilowanych trzeba mieć kompilator. Dla naszych zastosowań idealny będzie [**MinGW**](http://sqrt.pl/mingw.zip).

_Aby uniknąć dokonywania zmian w konfiguracji najlepiej rozpakować do lokalizacji `C:\WinGW\`_

Jest on narzędziem dzięki któremu projekt napisany w języku **C** zamienimy na plik wsadowy do mikrokontrolera `.bin`/`.hex` lub
aplikację `.exe`.

![Compiler](/image/compiler.png)

Następnym krokiem będzie dodanie ścieżki do zmiennych systemowych, tak aby skróty `gcc`, `gbd` uruchamiały odpowiedznie programy.

    {gcc-path}\mingw64\bin
    C:\WinGW\mingw64\bin

![Path](/image/path.png)

Teraz można dokonać stworzyć plik `main.c`

```cpp
#include <stdio.h> // Dołączenie biblioteki
int main (void) // Funkcja główna
{
  printf("Hello, World!"); // Wyświetlenie przywitania
  return 0;
}
```

oraz dokonać pierwszej kompilacji

    gcc {input-filse} -o {output-app}
    gcc src/main.c -o main.exe

Jednak, aby pracować wygodniej oraz debugować potrzebujemy jakiegoś IDE. Świetnie sprawdzi się [Visual Studio Code](https://code.visualstudio.com/Download), dla którego skonfigurowany projekt umieszczony jest w folderze `template` na tym repozytorium.

# Podstawy

## Typy zmiennych

**Typy całkowite**

| Type                                                     |  Bits | Bytes |  Znak   |    Format     |
| :------------------------------------------------------- | ----: | ----: | :-----: | :-----------: |
| `char`                                                   |     8 |     1 | `+`/`-` |     `%c`      |
| `signed char`                                            |     8 |     1 |   `-`   |     `%c`      |
| `unsigned char`                                          |     8 |     1 |   `+`   |     `%c`      |
| `short`, `short int`, `signed short`, `signed short int` |    16 |     2 |   `-`   |     `%d`      |
| `unsigned short`, `unsigned short int`                   |    16 |     2 |   `+`   |     `%u`      |
| `long`, `long int`, `signed long`, `signed long int`     |    32 |     4 |   `-`   |     `%ld`     |
| `unsigned long`, `unsigned long int`                     |    32 |     4 |   `+`   |     `%lu`     |
| `int`,                                                   | 16/32 |   2/4 |   `-`   |  `%d`/`%ld`   |
| `long long`, `long long int`                             |    64 |     8 |   `-`   | `%ld`/`%I64d` |
| `unsigned long long`, `unsigned long long int`           |    64 |     8 |   `+`   | `%lu`/`%I64u` |

`+`_liczba bez znaku_ `-`_liczba ze znakiem_

W zależności od kompilatora `char` oraz `int` mogą być potraktowane niejednoznacznie. Niektóre typy zmiennych mogą być określane na różne sposoby, co też jest trochę irytujące. Dodatkowo stosując `char` nie wskazujemy czy ma być on interpretowany jako 8-bitowa liczba, czy np. znak **ASCII**. Zatem dobrą praktyką jest stosować bibliotekę

```cpp
#include <stdint.h>
```

Wówczas jest porządeczek.

| Type       | Bits | Bytes |    Format     |
| :--------- | ---: | ----: | :-----------: |
| `char`     |    8 |     1 |     `%c`      |
| `int8_t`   |    8 |     1 |     `%d`      |
| `uint8_t`  |    8 |     1 |     `%u`      |
| `int16_t`  |   16 |     2 |     `%d`      |
| `uint16_t` |   16 |     2 |     `%u`      |
| `int32_t`  |   32 |     4 |     `%ld`     |
| `uint32_t` |   32 |     4 |     `%lu`     |
| `int64_t`  |   64 |     8 | `%ld`/`%I64d` |
| `int64_t`  |   64 |     8 | `%lu`/`%I64u` |

Typ `char` stosujemy jako znak lub częściej jako substytut `string`'a w przypadku tablicy lub wskaźnika, gdyż tym typem nie dysponujemy w języku `c`. Możemy dalej trzymać ten schemat dodając własne typy z subfix'em `_t`.

Brakuje również zmiennej `bool`/`boolena`, ponieważ najmniejszą ilością danych (w przypadku procesorów 8-bitowych) jaka może trafić do **ALU** jest 1 bajt, czyli zmienna typu `char`, więc tworzenie typu `bool` byłoby bezcelowe, jednak ze względu na czytelność kodu warto dołączyć bibliotekę

```cpp
#include <stdbool.h>
```

i użytać `true`/`false` zamiast `0`/`1`. Jednak jest to jedynie rzutowanie na zmienną `char`.

**Typy zmiennoprzecinkowe**

| Type          | Value bits |    Bytes | Format |
| :------------ | ---------: | -------: | :----: |
| `float`       |         23 |        4 |  `%f`  |
| `double`      |         52 |        8 | `%lf`  |
| `long double` |          - | 10/12/16 | `%LF`  |

Słabsze procesory są pozbawione hardware'owego modułu operacji dziesiętnych, więc podczas operacji na tych zmiennych są one emulowane, co jest strasznie powolne. Zatem często stosuje się zmienne całkowite z przesuniętym przecinkiem.

**Type `void`**

Ogólnie nie znaczy nic lub oznacza brak typu. Stosujemy w trzech sytuacjach:

- jako argument funkcji, która nie pobiera argumentów - `int myfnc(void)`
- oznaczenie, że funkcja nie zwraca nic - `void myfnc(int)`
- wskaźnik na nieznany typ - `void*`

## Struktura programu

Standardowa aplikacja działająca na systemie operacyjnym

```cpp
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
// powiązania
// definicje
// zmienne globalne
int main(int argc, char *argv[]) // pobranie argumentów podczas wywołania
{
  // zmienne lokalne
  // program
  return 0;
}
```

`int argc` - ilość argumentów
`int argc` - tablica `string`-ów

Standardowa aplikacja systemów wbudowanych

```cpp
#include <stdint.h>
#include <stdbool.h>
#include "microcontroller.h"
// powiązania
// definicje
// zmienne globalne
int main(void)
{
  // zmienne lokalne
  // inicjalizacja
  while(1) {
    // runetime
  }
  return 0;
}
```

## Operatory arytmetyczne

| Nazwa              | Operator | Przykłady  | Z przypisaniem |
| ------------------ | :------: | ---------- | -------------- |
| Dodawanie          |   `+`    | x = x + y  | x += y         |
| Odejmopwanie       |   `-`    | x = x - y  | x -= y         |
| Mnożenie           |   `*`    | x = x \* y | x \*= y        |
| Dzielenie          |   `/`    | x = x / y  | x /= y         |
| Reszta z dzielenia |   `%`    | x = x % y  | x /= y         |
| Inkrementacja      |   `++`   | x++        | x += 1         |
| Dekrementacja      |   `--`   | x--        | x -= 1         |

Operatory bitowe

| Nazwa                            | Operator | Przykłady  | Z przypisaniem |
| -------------------------------- | :------: | ---------- | -------------- |
| Koniunkcja **AND**               |   `&`    | x = x & y  | x &= y         |
| Alternatywa **OR**               |   `\|`   | x = x \| y | x \|= y        |
| Alternatywa wykluczająca **XOR** |   `^`    | x = x ^ y  | x ^= y         |
| Negacja **NOT**                  |   `~`    | x = ~x     |                |
| Przesunięcie w lewo              |   `<<`   | x = x << y | x <<= y        |
| Przesunięcie w prawo             |   `>>`   | x = x >> y | x >>= y        |

```cpp
  int16_t a = 12;
  int16_t b = 4;
  a = a + b; //
```

## Switch...Case

W przykładzie w zależności od zmiennej `day` ma wyświetlić się nazwa dnia tygodnia, na który wskazuje.

```cpp
int day = 4;
switch(day)
{
  case 1: printf("Dziś jest poniedziałek"); break;
  case 2: printf("Dziś jest wtorek"); break;
  case 3: printf("Dziś jest środa"); break;
  case 4: printf("Dziś jest czwartek"); break;
  case 5: printf("Dziś jest piątek"); break;
  case 6: printf("Dziś jest sobota"); break;
  case 0: case 7: printf("Dziś jest niedziela"); break;
}
```

Widzimy, że po każdym bloku kodu dla każdej opcji znajduje się instrukcji `break`. Instrukcja to wymusza wyjście z instrukcji `switch`, a także pętki takich jak `while`, czy `for`. Instrukcję `break` możemy pominąć, wówczas program przeskoczy do kolejnego `case`-a

```c#
uint8_t day = 4;
switch (day)
{
  case 1: printf("Do weekendy jeszcze trzeba przeżyć poniedziałek");
  case 2: printf("Do weekendy jeszcze trzeba przeżyć wtorek");
  case 3: printf("Do weekendy jeszcze trzeba przeżyć środę");
  case 4: printf("Do weekendy jeszcze trzeba przeżyć czwartek");
  case 5: printf("Do weekendy jeszcze trzeba przeżyć piątek");
    break;
  default:
    printf("Weekend trwa w najlepsze!");
    break;
}
```

## Enum/Define

Typy wyliczeniowe `enum` i definicje `define`

```c#
enum weekDay {
  WEEKDAY_Monday = 1,
  WEEKDAY_Tuesday = 2,
  WEEKDAY_Wednesday = 3,
  WEEKDAY_Thursday = 4,
  WEEKDAY_Friday = 5,
  WEEKDAY_Saturday = 6,
  WEEKDAY_Sunday = 7
};

enum weekDay day = WEEKDAY_Thursday;
```

```c#
enum weekDay {
  WEEKDAY_Monday = 1,
  WEEKDAY_Tuesday = 2,
  WEEKDAY_Wednesday = 3,
  WEEKDAY_Thursday = 4,
  WEEKDAY_Friday = 5,
  WEEKDAY_Saturday = 6,
  WEEKDAY_Sunday = 7
} day = WEEKDAY_Thursday;
```

```c#
typedef enum {
  WEEKDAY_Monday = 1,
  WEEKDAY_Tuesday = 2,
  WEEKDAY_Wednesday = 3,
  WEEKDAY_Thursday = 4,
  WEEKDAY_Friday = 5,
  WEEKDAY_Saturday = 6,
  WEEKDAY_Sunday = 7
} weekDay_t;

weekDay_t day = WEEKDAY_Thursday;
```

Typy wyliczeniowe stożone za pomocą słowa `enum` mają wielkość `int`. Gdy chcemy zaoszczędzić pamięć, możemy zmienić `_t` na `_e` oraz przypisywać jego wartości do zmiennych zajmujących mniej pamięci w celu optymalizacji.

```c#
typedef enum
{
  WEEKDAY_Monday = 1,
  WEEKDAY_Tuesday = 2,
  WEEKDAY_Wednesday = 3,
  WEEKDAY_Thursday = 4,
  WEEKDAY_Friday = 5,
  WEEKDAY_Saturday = 6,
  WEEKDAY_Sunday = 7
} weekDay_e;

uint8_t day = WEEKDAY_Thursday;
```

Możemy też po prostu użyć `#define`. Przyjmuje się, że definicje składają się z dużych liter.

```c#
#define WEEKDAY_MONDAY = 1,
#define WEEKDAY_TUESDAY  = 2,
#define WEEKDAY_WEDNESDAY = 3,
#define WEEKDAY_THURSDAY = 4,
#define WEEKDAY_FRIDAY = 5,
#define WEEKDAY_SATURDAY = 6,
#define WEEKDAY_SUNDAY = 7

uint8_t day = WEEKDAY_THURSDAY;
```

## If...Else

Operatory logiczne

| Nazwa          | Operator | Przykłady |
| -------------- | :------: | --------- |
| Równy          |   `==`   | x == y    |
| Różny          |   `!=`   | x != y    |
| Większy        |   `>`    | x > y     |
| Mniejszy       |   `<`    | x < y     |
| Większy-Równy  |   `>=`   | x >= y    |
| Mniejszy-Równy |   `<=`   | x <= y    |

Operatory logiczne dla prawdy zwracają `1` natomiast dla fałszu `0`.
Podczas implementacji `0` jest traktowane jako fałsz, a każda inna wartość jako prawda.

```cpp
int32_t a = 12, b = 16;

if(a == b) {
  printf("Result: %d = %d", a, b);
}
else if (a > b) {
  printf("Result: %d > %d", a, b);
}
else {
  printf("Result: %d < %d", a, b);
}
```

```cpp
int32_t a = 12, b = 16;

if(a == b) printf("Result: %d = %d", a, b);
else if (a > b) printf("Result: %d > %d", a, b);
else printf("Result: %d < %d", a, b);
```

Łączenie wyrażeń logicznych

| Nazwa                       | Operator | Przykłady              | Rezultat       |
| --------------------------- | :------: | ---------------------- | -------------- |
| Suma logiczna **AND**       |   `&&`   | `x > 2 && x <= 5`      | x ∈ ( 2 ; 5 〉 |
| Alternatywa logiczna **OR** |  `\|\|`  | `x <= 2 \|\| x > 5`    | x ∈ ( 2 ; 5 〉 |
| Negacja logiczna **NOT**    |   `!`    | `!(x > 2 \|\| x <= 5)` | x ∈ ( 2 ; 5 〉 |

```cpp
int32_t age = 12;

if(age < 14 || age > 40) printf("Good Morning");
else if (age < 28) printf("Hello");
else printf("Hi");
```

## Loops

**while**

```cpp
uint8_t n = 1;
while(n <= 10) {
	printf("%d ", n);
	n++;
}
```

## Arrays & Strings
<!---
#include <stdio.h>

```cpp


uint8_t n[ 10 ];

for ( i = 0; i < 10; i++ ) {
      n[ i ] = i + 100; /* set element at location i to i + 100 */
}

   /* output each array element's value */
   for (j = 0; j < 10; j++ ) {
      printf("Element[%d] = %d\n", j, n[j] );
   }
```

<!---
|     | x0  | x1  | x2  | x3  | x4  | x5  | x6  | x7  | x8  | x9  | xA  | xB  | xC  | xD  | xE  | xF  |
| --- | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| x0  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x1  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x2  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x3  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x4  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x5  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x6  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x7  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x8  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| x9  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| xA  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| xB  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| xC  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| xD  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| xE  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| xF  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
-->

```cpp
char str1[100] = "Guantanamera\0";
char str2[] = "Guantanamera";
char str3[13] = { 'G','u','a','n','t','a','n','a','m','e','r','a', '\0' };
char str4[] = { 'G','u','a','n','t','a','n','a','m','e','r','a', 0 };
char str5[] = { 71,117,97,110,116,97,110,97,109,101,114,97, 0 };
char str6[] = { 0x47,0x75,0x61,0x6E,0x74,0x61,0x6E,0x61,0x6D,0x65,0x72,0x61, 0 };
```

Powiązanie pomiędzy liczbą a znakiem znajdziemy w tablicy **ASCII**.
String jest **wskaźnikiem**/**referencją**, który wskazuje na rejestr zawierający pierwszy znak łańcucha. Łańcuch ciągnie się do rejestru, w którym znajduje się wartość `0`.

| str  |   G    |   u    |   a    |   n    |   t    |   a    |   n    |   a    |   m    |   e    |   r    |   a    |   \0   |
| :--: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
| addr | 0xFF01 | 0xFF02 | 0xFF03 | 0xFF04 | 0xFF05 | 0xFF06 | 0xFF07 | 0xFF08 | 0xFF09 | 0xFF10 | 0xFF11 | 0xFF12 | 0xFF12 |

`str1` = 0xFF01 ⟶ `"Guantanamera"`
`str[0]` = `'G'` = `0x47` = `71`
`str[7]` = `'n'` = `0x6E` = `110`
`&str[7]` = 0xFF01 ⟶ `"namera"`


<!---

```cpp



for(int i;

```

//scanf("%d %d", &number1, &number2);

```cpp
void read()
{
   char str[20];
   gets(str);
   printf("%s", str);
   return;
}
```

```cpp
#define MAX_LIMIT 20
void read()
{
   char str[MAX_LIMIT];
   fgets(str, MAX_LIMIT, stdin);
   printf("%s", str);

   getchar();
   return;
}
```

// protobuff
// struktura danych littel-endin

// napisz funkcje

Operatory logiczne

Operatory binarne

// nagłówki .h -> para .c .h
// multifile program

```cpp
#include <stdio.h>
int main()
{
   char str[20];
   gets(str);
   printf("%s", str);
   return 0;
}
```

## Struktury

## Wskaźniki

## Rzutowanie

// słabe typowanie

// komentarze

// chamskie konwersjie
// size_of

//%c %d

```cpp
int i, j, k; //
char c, ch; //
float f, price; //
double d; //
void
```

```cpp
int i, j, k; //
char c, ch; //
float f, price; //
double d; //
void
```

### Biblioteka

```cpp
#include <stdbool.h>
#include <stdint.h>
```

`Variable`

Zmienne C

extern int d = 3, f = 5; // declaration of d and f.
int d = 3, f = 5; // definition and initializing d and f.
byte z = 22; // definition and initializes z.
char x = 'x'; // the variable x has the value 'x'.

Zmienne języka C

int i, j, k;
char c, ch;
float f, salary;
double d;
void

```cpp
#include <stdio.h>
int main (void)
{
  puts ("Hello World!");
  return 0;
}
```


-->