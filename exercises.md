### Zadanie 1

Napisać program, który przeanalizuje wprowadzony na stałe łańcuch znaków oraz wyświetli z niego jedynie litery i cyfry, a wszystkie duże litery zamieni na małe. Wszystkie pozostałe znaki lub grupy znaków zamieni separator `-` w taki sposób, aby separatory z sobą nie sąsiadowały. Separatory na początku i końcu łańcucha mają zostać pominięte.

```bash
^^Hel1o*_W0rld$ # input string
he11o-world # console output
```

Pomocny może okazać się przykład z wyświetlaniem kolejnych znaków łańcucha:

```cpp
char str[] = "example";
// deklaracja referencji (statycznego wskaźnika)
// zarezerwowanie 8 baytów pamięci
// wypełnienie pamięcie wartością "example\0"
char *p = str; // deklaracja wskaźnika p i ustawienie go na str
while(*p) { // wykonuje dopuki wskaźnik wskazuje na inną wartość niż 0
  printf("%c", *p); // wyświetlenie wartosci na którą wskazuje wskaźnik
  p++; // inkrementacja położenia wskaźnika
}
```

**Featchers**

- Zamienić program w funkcję, która przyjmuje tablice oraz znak separacji

```cpp
void replaceFnc(char *str, char sep);
void replaceFnc(char str[], char sep)
```

- Sprawić, aby funkcja nie wyświetlała wyniku, a jedynie zwracała łańcuch znaków, który będzie wyświetalny w funkcji głównej. Łańcuch wejściowy nie ma ulec modyfikacji.

```cpp
return char *replaceFnc(char *str, char sep);
```

- Dodać, w obsłudze funkcji, zamianę dużych liter na małe lub odwrotnie, w zależności od przekazanego parametru.
- Dodać zamianę znaków Polskich na ich odpowiedniki bez _ogonków_
- Dadać zamianę cyfr na ich nazwy w języku angielskim

### Zadanie 2

Doimplementować do pseudoklasy `vector` pseudometody:
- `vectorPrint` - wyświetlanie zawartości wektora
- `vectorMerge` - łączenie dwóch wektorów
- `vestorSum` - sumowanie wektorów
- `vestorDifference` - odejmowanie wektorów
- `vestorMultiplication` - mnożenie wektorów
- `vestorPop` - usówanie ostatniej wartości z wektora
- `vestorPush` - dodawanie do wektora wartości

Każda funkcja musi być ładnie opisana (prz ypmocy ) oraz musi w funkcji `main` znajdować się jej przykładowe wywołanie.