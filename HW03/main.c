#include <stdio.h>
#include <stdlib.h>

void mezer (unsigned char mez){
	for (unsigned char i = 0; i < mez; i++){
		printf(" ");
	}
	printf("X");
}

void strecha (int sirka){
	char offset = sirka/2;
	char rep = 0;
	while (offset > rep){
			mezer (offset - rep);
			if (rep > 0){
				mezer (rep*2-1);
			}
			rep++;
			printf("\n");
	}
}

void cara (int sirka){
	for (unsigned char i = 0; i < sirka; i++){
		printf("X");
	}
		printf ("\n");
}

void steny (int sirka, int vyska){
	vyska -= 2;
	for (unsigned char i = 0; i < vyska; i++){
		printf ("X");
		mezer (sirka-2);
		printf ("\n");
	}
}

void DoIt(int sirka, int vyska){
	strecha (sirka);
	cara (sirka);
	steny (sirka, vyska);
	cara (sirka);
}

int sizeLimit(int input){
	if(input >= 3 && input <= 69) {
		return 1;
	}
	else return 0;
}

int main()
{
    int sirka, vyska;
    if (scanf ("%d %d", &sirka, &vyska)) {
        if (sizeLimit(sirka) && sizeLimit(vyska)) {
					if (sirka %2) {
						DoIt(sirka, vyska);
					}
					else {
						fprintf(stderr, "Error: Sirka neni liche cislo!\n");
						return 102;
					}
        }
        else {
					fprintf(stderr, "Error: Vstup mimo interval!\n");
					return 101;
				}
      }
			else {
				fprintf(stderr, "Error: Chybny vstup!\n");
				return 100;
			}
	    return 0;
	  }
