### Zadanie 1

Napisać program, który przeanalizuje wprowadzony na stałe łańcuch znaków oraz wyświetli z niego jedynie litery i cyfry. Wszystkie pozostałe znaki lub grupy znaków zamieni separator '-' w taki sposób, aby separatory z sobą nie sąsiadowały. Separatory na początku i końcu łańcucha mają zostać pominięte.
Pomocny może okazać się przykład z wyświetlaniem kolejnych znaków łańcucha:

```cpp
char str[] = "example";
// deklaracja referencji (statycznego wskaźnika)
// zarezerwowanie 8 baytów pamięci
// wypełnienie pamięcie wartością "example\0"
char *p = str; // deklaracja wskaźnika p i ustawienie go na str
while(*p) { // wykonuje dopuki wskaźnik wskazuje na inną wartość niż 0
 printf("%c", *p); // wyświetlenie wartosci na którą wskazuje wskaźnik
 p++; // inkrementacjia położenia wskaźnika
}
```

**Featchers**

- Zamienić program w funkcję, która przyjmuje tablice oraz znak separacji

```cpp
void replaceFnc(char *str, char sep);
void replaceFnc(char str[], char sep)
```

- Sprawić, aby funkcja nie wyświetlała wyniku, a jedynie zwracała łańcuch znaków, który będzie wyświetalny w funkcji głównej

```cpp
return char *replaceFnc(char *str, char sep);
```

<!---
- Dodać zamianę dużych liter na małe w obsłudze funkcji
- Dodać zamianę znaków Polskich na ich odpowiedniki bez _ogonków_
- Dadać zamianę cyfr na ich nazwy w języku angielskim
--->