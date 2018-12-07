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

int isArg (char * str){
  if (*(str) == '-'){
    if (strlen(str) == 2){
      if(*(str + 1) == 'c') return 0;       //-c
      else if(*(str + 1) == 's') return 1;  //-s
      else if(*(str + 1) == 'l') return 2;  //-l
      else {
        return -1;
      }
    }
  } return -1;
}

int isNum (char * str){
  int i = 0;
  int argNum = 0;
  for(;(*(str + i) >= '0') &&  (*(str + i) <= '9') && (i < strlen(str)); i++){
    argNum *= 10;
    argNum += (*(str + i) - '0');
  }
  if (i == strlen(str)) return argNum;
  return -1;
}

void space(int strl){
  for (int i = 0; i + strl < spaceCount; i++){
    printf(" ");
  }
}

void print(int rank, int len){
  int tempLen = strlen(*(ppWord + rank));
  if((tempLen == len || len == -1) && len != 0 ){//&& tempLen < 10
    printf("%s", *(ppWord + rank));
    space(tempLen);
    printf("%d\n", *(pStatQuant + rank));
  }
}

int main (int argc, char **argv){
  int caseSens = 1;   //-c je pro case insensitive
  int wordLen = -1;  //-l je pro omezeni delky slova
  int sortStyle = 0;  //-s je pro razeni; 0 (default - podle poradi zapisu); 1 (podle cetnosti), 2 (podle abecedy)
  int maxQuant = 0;
  int minQuant = 100000;
  int argTemp;

  for(int i = 1; i < argc; i++){
    int tempNum;
    argTemp = isArg(*(argv + i));
    if (argTemp == 0){
      caseSens = 0;
    }
    else if (argTemp == 1){
      if (i + 1 < argc){
        i++;
        tempNum = isNum(*(argv + i));
        if (tempNum == 1 || tempNum == 2) sortStyle = tempNum;
        else fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
      }
      else fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
    }
    else if (argTemp == 2){
      if (i + 1 < argc){
        i++;
        tempNum = isNum(*(argv + i));
        if (tempNum >= 0) wordLen = tempNum;
        else fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
      }
      else fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
    }
  }
  int wordCount = scan(caseSens);

  for (int i = 0; i < wordCount; i++) {   //Hledani maxima a minima
    if(*(pStatQuant + i) > maxQuant) maxQuant = *(pStatQuant + i);
    if(*(pStatQuant + i) < minQuant) minQuant = *(pStatQuant + i);
  }

  if (wordLen != 0) printf("Seznam slov:\n");
  if (sortStyle == 0){

    for (int i = 0; i < wordCount; i++){
      print(i, wordLen);
    }
  }

  else if (sortStyle == 1){   //vypis podle cetnosti
    for (int i = minQuant; i <= maxQuant; i++){
      for (int r = 0; r < wordCount; r++){
        if (*(pStatQuant + r) == i){
          print(r, wordLen);
        }
      }
    }
  }
  else if (sortStyle == 2){   //abecedni vypis
    char buffer[100];
    int temp;
    for (int i = 1; i < wordCount; i++) {
      for (int j = 1; j < wordCount; j++) {
        if (strcmp(*(ppWord + j - 1), *(ppWord + j)) > 0) {
          strcpy(buffer, *(ppWord + j - 1));
          temp = *(pStatQuant + j - 1);

          free(*(ppWord + j - 1));
          *(ppWord + j - 1) = malloc((strlen(*(ppWord + j)) + 1) * sizeof(char));

          strcpy(*(ppWord + j - 1),*(ppWord + j));
          *(pStatQuant + j - 1) = *(pStatQuant + j);

          free(*(ppWord + j));
          *(ppWord + j) = malloc((strlen(buffer) + 1) * sizeof(char));
          strcpy(*(ppWord + j), buffer);
          *(pStatQuant + j) = temp;
        }
      }
    }
    for (int i = 0; i < wordCount; i++){
      print(i, wordLen);
    }
  }

  printf ("Pocet slov:");
  space(strlen("Pocet slov:"));
  printf ("%d\n", wordCount);
  printf ("Nejcastejsi:");
  space(strlen("Nejcastejsi:") + 1);

  for (int i = 0; i < wordCount; i++){
    if (*(pStatQuant + i) == maxQuant) printf (" %s", *(ppWord + i));
  }

  printf ("\nNejmene caste:");
  space(strlen("Nejmene caste:") + 1);
  for (int i = 0; i < wordCount; i++){
    if (*(pStatQuant + i) == minQuant) printf (" %s", *(ppWord + i));
  }
    printf ("\n");
  fr(wordCount);
  return 0;
}
