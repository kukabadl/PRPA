#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char ** ppWord;   //ukazatel na ukazatele na jednotliva slova
char buffer [100];
int wordCount = 0;
/*funkce, ktera slouzi pro porovnavani cisel do qsort. do qsort se na tuto funkci da pointer*/
/*
static int cmp_str(const void *lhs, const void *rhs)
{
    return strcmp(lhs, rhs);
}
*/
//size_t strlen(const char *str);
/* int sortIt() je fce, ktera dela vsechno a vraci bud error, kdyz je vstup spatny
a nebo 0, kdyz vse probehne dobre*/
int isChar(char in){    //pokud je dany char interpunkce vrati nulu, jinak jednicku
  if(in < 48 || in > 122 || (in > 90 && in < 97) || (in > 57 && in < 65)) return 0;
  else return 1;
}

void interpunkce (char * str, int strl){
  int remove = 0;
  for(; isChar(*(str + remove)) == 0 && remove < strl; remove++);// printf("%s ", str)
  for (int r = remove; r <= strl; r++){
    *(str + r - remove) = *(str + r);
  }
  *(str + strl - remove) = '\0';
  for(int i = strl - remove; isChar(*(str + i)) == 0 && i >= 0; i--) *(str + i) = '\0';
}

int input () {
ppWord = (char **) malloc(101 * sizeof(char *));
  for(;1 == scanf("%s", buffer); wordCount++){
    printf("%s\n", buffer);
    int strLeTemp = (int) strlen(buffer);
    interpunkce(buffer, strLeTemp);
    printf("%s\n", buffer);
    strLeTemp = (int) strlen(buffer);
    if (((wordCount + 1) % 100) == 0){
      ppWord = (char **) realloc (ppWord, (wordCount + 101) * sizeof(char *));
    }
    *(ppWord + wordCount) = (char *) malloc((strLeTemp + 1) * sizeof(char));
    strcpy(*(ppWord + wordCount), buffer);
  }
  for (int i = 1; i < wordCount; i++) {
    for (int j = 1; j < wordCount; j++) {
     if (strcmp(*(ppWord + j - 1), *(ppWord + j)) > 0) {
      strcpy(buffer, *(ppWord + j - 1));
      free(*(ppWord + j - 1));
      *(ppWord + j - 1) = malloc((strlen(*(ppWord + j)) + 1) * sizeof(char));
      strcpy(*(ppWord + j - 1),*(ppWord + j));
      free(*(ppWord + j));
      *(ppWord + j) = malloc((strlen(buffer) + 1) * sizeof(char));
      strcpy(*(ppWord + j), buffer);
     }
    }
  }
  printf ("Pocet> %d\n", wordCount);
  for(int prd = 0; prd < wordCount; prd++){
    printf("%s ",*(ppWord + prd));
  }

  for (int i = 0; i < wordCount; i++){
    free(*(ppWord + i));
  }
  free(ppWord);
  //free ();     //uvolneni alokovane pameti
  return 0;
}

int main (){
  /*Zavola funkci sortIt, ktera dela skoro vse, pokud je jeji navratova hodnota 100,
  pak vytiskne error a tuto navratovou hodnotu take vrati. Pokud sortIt skoncila uspesne,
  pak vrati nulu.*/
	if (input() == 100){
		fprintf(stderr, "Histogram size error\n");
		return 100;
	}
	else return 0;
}
