#include "main.h"
#include "standard.h"
#include "special.h"

int main(void)
{
	short choice = 0;
	
	while(choice < 1 || choice > 7) {
		printf("Welche Rechnung möchtest du ausführen?\n");
		printf("1 - Addieren\n");
		printf("2 - Subtrahieren\n");
		printf("3 - Multiplizieren\n");
		printf("4 - Dividieren\n");
		printf("5 - Modolu\n");
		printf("6 - Exponential\n");
		printf("7 - Fakultät1\n");
		scanf("%hd", &choice);
	}		
		
	if(choice > 0 && choice < 7)
		eingabe2(choice);
	else
		eingabe1();
	
	return 0;
}

void eingabe2(short choice) {
	int a, b;
	int ergebnis;
	float ergebnisF;
	printf("Gib bitte die beiden Zahlen ein!\n");
	printf("a  'Rechnungsart' b\n");
	scanf("%d" "%d", &a, &b);
	
	switch(choice) {
		case 1:	ergebnis = addition(a, b);			break;
		case 2: ergebnis = subtraktion(a, b);		break;
		case 3: ergebnis = multiplikation(a, b);	break;
		case 4: ergebnisF = dividierung(a, b);		break;
		case 5:	ergebnis = modolu(a, b);			break;
		case 6: ergebnis = exponential(a, b);		break;
	}	
	if(choice == 4)
		printf("\nDas Ergebnis ist %f.\n", ergebnisF);
	else
		printf("\nDas Ergebnis ist %d.\n", ergebnis);
}

void eingabe1() {
	int a;
	int ergebnis;
	printf("Gib bitte die Zahl ein!\n");
	scanf("%d", &a);
	
	ergebnis = fakultaet(a);
	
	printf("\nDas Ergebnis ist %d.\n", ergebnis);
}
