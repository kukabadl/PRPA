#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool asteriskLast;
bool plotEn;
int sirka, patro, plotVys;

int sizeLimit(int input){
	if(input >= 3 && input <= 69) {
		return 1;
	}
	else return 0;
}

int error (int err){			//je to error
	switch (err) {
		case 103:
			fprintf (stderr, "Error: Neplatna velikost plotu!\n");
			break;
		case 102:
			fprintf(stderr, "Error: Sirka neni liche cislo!\n");
			break;
		case 101:
			fprintf(stderr, "Error: Vstup mimo interval!\n");
			break;
		case 100:
			fprintf(stderr, "Error: Chybny vstup!\n");
			break;
	}
	return err;
}

void mezer (unsigned char mez, unsigned char fill){
	bool asterisk = asteriskLast;
	for (unsigned char i = 0; i < mez; i++){
		if (fill == 1){
			if (asterisk) printf("*");
			else printf("o");
			asterisk = !asterisk;
		}
		else if (fill == 0) printf(" ");
		else if (fill == 2) printf("X");
	}
	printf("X");
	if (fill == 1) {
		asteriskLast = asterisk;
	}
}

void strecha (){
	char offset = sirka/2;
	char rep = 0;
	while (offset > rep){
			mezer (offset - rep, 0);
			if (rep > 0){
				mezer (rep*2-1, 0);
			}
			rep++;
			printf("\n");
	}
}

void plot () {
	bool blank = plotVys % 2;
		if (patro == plotVys || patro == 1){
			for (int plotCpy = plotVys; plotCpy > 0; plotCpy --){
				if (!blank) printf ("-");
				else printf ("|");
				blank = !blank;
			}
		}
		else if (patro < plotVys) {
			for (int plotCpy = plotVys; plotCpy > 0; plotCpy --){
				if (!blank) printf (" ");
				else printf ("|");
				blank = !blank;
			}
		}
}

void steny (){
	mezer (sirka - 1, 2);
	plot ();
	printf("\n");
	patro --;
	for (; patro -1 > 0; patro--){
		printf("X");
		if (plotEn){
			mezer (sirka - 2, 1);
			plot ();
		}
		else mezer (sirka - 2, 0);
		printf("\n");
	}
	mezer (sirka - 1, 2);
	plot ();
	printf("\n");
}

int main() {
  if (2 == scanf ("%d %d", &sirka, &patro)) {
    if (sizeLimit(sirka) && sizeLimit(patro)) {
			if (sirka % 2) {
				if (sirka == patro){
					if(1 == scanf ("%d", &plotVys)){
						if ((plotVys <= patro) && plotVys) plotEn = 1;
						else return error (103);
					}
					else return error (100);
				}
				strecha ();
				steny ();
			}
			else return error (102);
    }
    else return error (101);
  }
	else return error (100);
  return 0;
}
