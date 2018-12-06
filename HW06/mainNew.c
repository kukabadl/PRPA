#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define spaceCount 21
char ** ppWord;
int * pStatQuant, * pStatRank;

void fr (int wCount){
  for (int i = 0; i < wCount; i++){
    free(*(ppWord + i));
  }
  free(pStatQuant);
  free(pStatRank);
  free(ppWord);
}

int isChar(char in){    //pokud je dany char interpunkce vrati nulu, jinak jednicku
  if(in < 48 || in > 122 || (in > 90 && in < 97) || (in > 57 && in < 65)) return 0;
  else return 1;
}

int interpunkce (char * str, int strl){
  int remove = 0;
  for(; isChar(*(str + remove)) == 0 && remove < strl; remove++);
  for (int r = remove; r <= strl; r++){
    *(str + r - remove) = *(str + r);
  }
  *(str + strl - remove) = '\0';
  for(int i = strl - remove; isChar(*(str + i)) == 0 && i >= 0; i--) *(str + i) = '\0';
  return strlen(str);
}

int scan (int c){
  bool alreadyPresent = 0;
  int wCount = 0;
  char buffer [100];
  ppWord = (char **) malloc(101 * sizeof(char *));
  pStatQuant = (int *) malloc(101 * sizeof(int));
  pStatRank = (int *) malloc(101 * sizeof(int));

  for(;1 == scanf("%s", buffer); alreadyPresent = 0, wCount++){
    int strLeTemp = interpunkce(buffer, strlen(buffer));
    if(c){
      for(int i = 0; i < strLeTemp; i++){
        if (buffer[i] >= 'A' && buffer[i] <= 'Z') buffer[i] += 32;
      }
    }
    if (((wCount + 1) % 100) == 0){   //prialokovani mista pro dalsi cleny
      ppWord = (char **) realloc (ppWord, (wCount + 101) * sizeof(char *));
      pStatQuant = (int *) realloc (pStatQuant, (wCount + 101) * sizeof(int));
      pStatRank = (int *) realloc (pStatRank, (wCount + 101) * sizeof(int));
    }

    for (int i = 0; i < wCount; i++){
      if (0 == strcmp(buffer, *(ppWord + i))){
        *(pStatQuant + i) += 1;
        alreadyPresent = 1;
        wCount--;
        break;
      }
    }

    if(alreadyPresent == 0){
      *(ppWord + wCount) = (char *) malloc((strLeTemp + 1) * sizeof(char));
      strcpy(*(ppWord + wCount), buffer);
      *(pStatQuant + wCount) = 1;
      *(pStatRank + wCount) = wCount;
    }
  }
  return wCount;
}

void printAll(int wCount){
  for(int i = 0; i < wCount; i++){
    printf("Poradi = %d\n", *(pStatRank + i));
    printf("Mnozstvi = %d\n", *(pStatQuant + i));
    printf("Slovo = %s\n\n", *(ppWord + i));
  }
}

int main (int argc, char **argv){
  int caseSens = 1;  //-c je pro case insensitive
  int l = 100;//-l je pro omezeni delky slova
  int s = 0;  //-s je pro razeni - 1 podle cetnosti, 2 je pro abecedni
  int wordCount = scan(caseSens);

  printAll(wordCount);
  fr(wordCount);
  return 0;
}
