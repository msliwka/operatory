/**
 * 3. Napisz program, który prosi użytkownika o podanie dwóch liczb całkowitych, 
 * a następnie sumuje wszystkie liczby całkowite pomiędzy podanymi liczbami 
 * (włącznie) i wypisuje wynik. Dla przykładu po podaniu liczb 2 i 6 program 
 * powinien wypisywać:
 *
 * Suma kolejnych liczb całkowitych od 2 do 6 wynosi 20.
 */
#include <stdio.h>

void swap (int* a, int* b)
{
  int c; c=*a; *a=*b; *b=c;
}

int main(void)

{
	int a, b, suma = 0;

	printf ("podaj liczbe a\n");
	scanf ("%d", &a);

	printf ("podaj liczbe b\n");
	scanf ("%d",&b);

	if(a>b) {
		swap(&a, &b);
	}

	/*while (a <= b) { suma = suma + a;++a; }	
	while (a <= b) { suma = suma + a++; }	
	while (a <= b) { suma += a++; }	
	for (;a <= b; a++) suma = suma + a;
	for (;a <= b; a++) suma += a;
	for (;a <= b; ++a) suma = suma + a;
	for (;a <= b; ++a) suma += a;
	for (;a <= b; suma += a++) ;
	do { suma = suma + a; a++; } while (a <= b);
	do { suma = suma + a++; } while (a <= b);
	*/
	do { suma += a++; } while (a <= b);


	printf ("wynik otrzymanej sumy liczb %d\n", suma);
	
	return 0;
}