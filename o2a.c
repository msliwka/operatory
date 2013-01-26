/**
 * 2. Napisz program, który prosi o podanie liczby dni, 
 * a następnie zamienia je na tygodnie i dni. 
 * Dla przykładu, program powinien zamienić 16 dni na:
 * 
 * 16 dni to 2 tygodnie i 2 dni.
 *
 * W programie wykorzystaj pętlę while, aby użytkownik użytkownik mógł 
 * wielokrotnie wpisywać liczbę dni. Koniec programu powinien nastąpić 
 * po wprowadzeniu liczby 0 lub liczby ujemnej.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

typedef struct fmt {
	char ident;
	long long denominator;
	char* singular;
	char* plural1;
	char* plural2;
} fmt;

const fmt fmts[] = {
	{'l', ((long long)1000)*365*24*60*60, "millenium", "millenia", "milleniow"}, 
	{'w', ((long long)100)*365*24*60*60, "wiek", "wieki", "wiekow"}, // amen
	{'r', 365*24*60*60, "rok", "lata", "lat"},
	{'m', 31*24*60*60, "miesiac", "miesiace", "miesiecy"},
	{'t', 7*24*60*60, "tydzien", "tygodnie", "tygodni"},
	{'d', 24*60*60, "dzien", "dni", "dni"},
	{'g', 60*60, "godzina", "godziny", "godzin"},
	{'i', 60, "minuta", "minuty", "minut"},
	{'s', 1, "sekunda", "sekundy", "sekund"},
};

const char* plural(const int n, const fmt* const f)
{
	// dla jezyka polskiego posiadamy 3 formy liczby mnogiej
	return (n==1 ? f->singular : n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? f->plural1 : f->plural2);
}

void help()
{
	int i;
	printf("Wejscie podawac przez <liczba><litera>\n");
	printf("dozwolone formaty to:\n");
	for (i = 0; i < ARRAY_SIZE(fmts); ++i) 
		printf("   %c - %s\n", toupper(fmts[i].ident), fmts[i].singular);
	printf("\n   przyklad: 16D\n");
}

int main(void)
{

	char buffer[1000];
	int i, j, h = 0;
	long long n = 0, seconds = 0, temp;

	while(1) {
		// cleanup
		n = 0;
		seconds = 0;

		if(!h) {
			help();
			h=1;
		}
		// scan it
		printf("podaj wartosc: ");
		fgets(buffer, sizeof(buffer), stdin);

		// check exit; 2, bo nam zbiera rowniez enter
		if (strlen(buffer) < 2) {
			printf("Koniec!\n");
			break;
		}

		// parse it
		for(i = 0; i < strlen(buffer); ++i) {
			if(isdigit(buffer[i])) {
				n = 10*n + (buffer[i] - '0');
			}
			else if(isalpha(buffer[i])) {
				// nie dostalismy liczby, ignorujemy
				if(!n) continue;
				
				// jakby ktos wpisal z duzej
				buffer[i] = tolower(buffer[i]);
				
				// sprawdzamy format
				for(j = 0; j < ARRAY_SIZE(fmts); ++j) {
					if (fmts[j].ident == buffer[i]) {
						seconds += n*fmts[j].denominator;
						n = 0;
						break;
					}
				}

				// nie znalezlismy formatu
				if(j == ARRAY_SIZE(fmts)) {
					printf("Podano nieznany format: %c\n", buffer[i]);
					h = 0; // pomylil sie, uruchamiamy helpa ponownie
					continue;
				}
			}
		}

		printf("Wybrano: %lld s\n", seconds);

		// wypisujemy 
		printf("Po konwersji: ");
		for(i = 0; i < ARRAY_SIZE(fmts); ++i) {
			// jako zmienna calkowita zadziala calosc nam jako floor(wartosc)
			temp = seconds/fmts[i].denominator;
			// gdy trafi sie nam 0 to pomijamy
			if (temp == 0) continue;
			printf("%lld %s ", temp, plural(temp, &fmts[i]));
			seconds -= temp*fmts[i].denominator;
		}
		printf("\n");
		printf("\n");
	}

	return 0;
}