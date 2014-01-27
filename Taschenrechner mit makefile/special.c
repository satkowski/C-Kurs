#include "special.h"

int modolu(int a, int b) {
	return a % b;
}

int exponential(int a, int b) {
	int ergebnis = 1;
	int c;
	for(c = 0; c < b; c++)
		ergebnis *= a;
	return ergebnis;	
}

int fakultaet(int a) {
	if(a == 1)
		return 1;
	return a * fakultaet(a - 1);
}
