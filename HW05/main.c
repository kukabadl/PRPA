#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Deklarace globalnich promennych - jde do nich zapsat kdekoliv v programu
a kdekoliv v programu z nich cist - jejich hodnoty se pri volani jine funkce nevymazi.
Prestoze jsem tuhle moznost pravdepodobne nevyuzil, je dobre ji mit.
*/
int numOfRows;
int numCount = 0;
int * pMatrix;
int max0Size;
int max1Size;
int maxInInterval = 0;

/*funkce, ktera slouzi pro porovnavani cisel do qsort. do qsort se na tuto funkci da pointer*/
int cmp (const void * cislo0, const void * cislo1) {
   return (*(int *) cislo0 - *(int *) cislo1);
}

/*
int size je funkce, ktera si vezme int a pak pocita, kolik ma zadane cislo cifer - kvuli vypisu
aby to netrvalo dlouho, tak misto odecitani jedne radeji delim 10, na vysledek to nema vliv
*/
int size (int size){
	int log = 0;
	if (size < 0){
		log = 1;
  }
	while (size != 0){
		size /= 10;
		log++;
	}
	return log;
}

/* int sortIt() je fce, ktera dela vsechno a vraci bud error, kdyz je vstup spatny
a nebo 0, kdyz vse probehne dobre*/
int sortIt () {
	float interval;                                                        //pomocna promenna pro ukladani velikosti jednoho intervalu
	if (1 != scanf("%d", &numOfRows) || numOfRows < 1) return 100;         //zadani poctu radku histogramu, vratit error, pokud jsou zadani a nebo zadany pocet neplatne
	int inInterval [numOfRows];                                            //vytvori pole intu, ktere bude pozdeji pouzito pro ukladani poctu prvku jednotlivzch intervalu
	pMatrix = (int*) malloc(1002 * sizeof(int));                           //alokuje v pameti misto pro 1002 cisel
	for (;scanf("%d", (pMatrix + numCount)) == 1; numCount++){             //dokud uzivatel zadava platna cisla, tak se ukladaji do pameti
		if ((numCount % 1000) == 0){                                         //pokud by se blizilo vycerpani jiz alokovane pameti, tak se alokuje dalsich 1000 prvku
			pMatrix = realloc(pMatrix, (numCount + 1 + 1000) * sizeof(int));
		}
	}

  qsort (pMatrix, numCount, sizeof(int), cmp);                           //Volani fce qsort, ktera seradi vsechna zadana cisla
	printf("Median %.2f\n",(numCount % 2) ? (*(pMatrix + numCount / 2)) : (*(pMatrix + numCount / 2 - 1) + *(pMatrix + numCount / 2)) / (float) 2);

  /*
    Zkraceny zapis podminky pro vypis medianu - ekvivalentni k :

    if (numCount % 2){                                         //Pokud je zbytek po deleni poctu prvku 2ma nenulovy - je jich lichy pocet, pak:
      printf("Median %.2f\n", (*(pMatrix + numCount / 2)));    //Vypise prostredni prvek.
    }

    else {                                                     //Jinak spocita aritmeticky prumer 2 strednich hodnot - jili pocet sudy
      printf("Median %.2f\n", (*(pMatrix + numCount / 2 - 1) + *(pMatrix + numCount / 2)) / (float) 2));
    }
  */

	printf("Number count: %d\n", numCount);                      //Vypis poctu zadanych cisel.

  numCount --;                                                 //Snizi promennou o jedna, aby se dala pouzit pro indexovani pole - zacinaji se indexovat uz od 0

  printf("Min: %d\n", *(pMatrix));                             //Protoze je pole serazene - vytiskne prvni prvek jako minimum
	printf("Max: %d\n", *(pMatrix + numCount));                  //Protoze je pole serazene - vytiskne posledni prvek jako maximum
	printf("Histogram:\n");                                      //nadpis

  /*Spocita velikost intervalu - od nejvetsi hodnoty v poli odecte nejmensi
  a vydeli pozadovanym poctem radku histogramu. Funkce fabs(); vraci absoluutni
  hodnotu. Kladna hodnota se bude pro budouci vypocty hodit vice. Velikosti
  intervalu se ulozi do promenne interval.*/
  interval = (float)(fabs((*(pMatrix + numCount) - *(pMatrix))/(float)numOfRows));

  int iter = 0;          //pomocna promenna - udavaporadi prave kontrolovaneho prvku matice v nasl. for loopu
	for (int r = 0; r < numOfRows; r++){     //loop se provede pro kazdy radek histogramu
		inInterval[r] = 0;                     //pole nesouci pocet prvku patricich do r-teho intervalu histogramu
    /*for prochazi pole a kontroluje, jestli prislusny prvek patri do intervalu.
    Pokud zjisti, ze dalsi prvek uz neexistuje, skonci.*/
    for (; *(pMatrix + iter) <= ((*(pMatrix)) + (1 + r) * interval); iter ++){
			inInterval[r]++;
			if (iter + 1 > numCount){
				iter++;
				break;
			}
      /*Tento if se stara o to, aby se do promenne maxInInterval ulozil pocet prvku nejvetsiho intervalu.
      To je potreba vedet pro skalovani histogramu. */
			if (inInterval[r] > maxInInterval) maxInInterval = inInterval[r];
		}
	}

  for (int r = 0; r < numOfRows; r++){      //slouzi pro tisk vystupu - provede se pro kazdy radek histogramu
    //udela prislusny pocet mezer, tak, aby mel vypis konstantni delku ta je nastavena na 3
    for (int space = 0; space < 3 - size((*(pMatrix)) + r * interval); space++){
			printf(" ");
		}
		printf ("%.1f -", (*(pMatrix)) + r * interval);     //Vypise spodni hranici r-teho intervalu
    //udela prislusny pocet mezer, tak, aby mel vypis konstantni delku ta je nastavena na 3
		for (int space = 0; space < 3 - size((*(pMatrix)) + (r + 1) * interval); space++){
			printf(" ");
		}
		printf (" %.1f|",(*(pMatrix)) + (r + 1)*interval);  //Vypise horni hranici r-teho intervalu
    /* Pomocna promenna temp - slouzi pro vysledek skalovani radku. je vypocitana
    jeste pred for loopem, aby se pri kazde iteraci nemuel vyraz prepocitavat znovu.
    pocet_prvku_r-teho_Intervalu * maximalni_pocet= / pocet_prvku_nejvetsiho_intervalu
    */
    int temp = (int)(inInterval[r]*25/(float)maxInInterval);

    //for vypise prislusny pocet "="
    for(int i = 0; i < temp; i++){
      printf("=");
    }
    printf("\n");
	}

  free (pMatrix);     //uvolneni alokovane pameti
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
