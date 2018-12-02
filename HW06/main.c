#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ** ppWord;   //ukazatel na ukazatele na jednotliva slova
int * pWord;
char buffer [100];
int wordCount = 0;
/*funkce, ktera slouzi pro porovnavani cisel do qsort. do qsort se na tuto funkci da pointer*/
int cmp (const void * cislo0, const void * cislo1) {
   return (*(int *) cislo0 - *(int *) cislo1);
}


/* int sortIt() je fce, ktera dela vsechno a vraci bud error, kdyz je vstup spatny
a nebo 0, kdyz vse probehne dobre*/
int sortIt () {
  //pSlovo = (* int) malloc(101 * sizeof(*int));
  while(1 == scanf("%s", buffer)){
    printf ("%s\n", buffer);
  }
  //qsort (pMatrix, numCount, sizeof(int), cmp);                           //Volani fce qsort, ktera seradi vsechna zadana cisla

  //free ();     //uvolneni alokovane pameti
	return 0;
}

int main (){
  /*Zavola funkci sortIt, ktera dela skoro vse, pokud je jeji navratova hodnota 100,
  pak vytiskne error a tuto navratovou hodnotu take vrati. Pokud sortIt skoncila uspesne,
  pak vrati nulu.*/
	if (sortIt() == 100){
		fprintf(stderr, "Histogram size error\n");
		return 100;
	}
	else return 0;
}
