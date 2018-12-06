#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** ppWord;   //ukazatel na ukazatele na jednotliva slova
int * pStat;
char buffer [100];
int c = 0;  //-c je pro case sensitive
int l = 100;//-l je pro omezeni delky slova
int s = 2;  //-s je pro razeni - 1 podle cetnosti, 2 je pro abecedni
int diff = 0;

#define spaceCount 21

int isNum (char * str){
  int i = 0;
  int argNum = 0;
  for(;*(str + i) >= '0' &&  *(str + i) <= '9' && i < strlen(str); i++){
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

int isArg (char * str){
  if (*(str) == '-'){
    if (strlen(str) == 2){
      if(*(str + 1) == 'c'){
        return 0;
      }
      else if(*(str + 1) == 's'){
        return 1;
      }
      else if(*(str + 1) == 'l'){
        return 2;
      }
      else {
        fprintf(stderr, "Warning: Chybna hodnota parametru -s!");
        return -1;
      }
    }
  }

  return 100;
}

void whichArgs(int argc, char **argv){
  int argument;
  for (int i = 1; i < argc; i++){
    argument = isArg(*(argv + i));
    if (argument >= 0){
      if (argument == 0) {        //parametr -c
        c = 1;
      }
      else if (argument == -1 || i + 1 >= argc){   //chybny parametr
        //printf ("je to v haji\n");
      }
      else {
        if (argument == 1){    //parametr -s
          if (0 < isNum(*(argv + i + 1))){
            s = isNum(*(argv + i + 1));
            i++;
          }
        }
        else if (argument == 2){    //parametr -l
          if (0 <= isNum(*(argv + i + 1))){
            l = isNum(*(argv + i + 1));
            i++;
          }
        //else fprintf (stderr, "je to v haji\n");
        }
      }
    }
  }
}

int isChar(char in){    //pokud je dany char interpunkce vrati nulu, jinak jednicku
  if(in < 48 || in > 122 || (in > 90 && in < 97) || (in > 57 && in < 65)) return 0;
  else return 1;
}

void interpunkce (char * str, int strl){
  int remove = 0;
  for(; isChar(*(str + remove)) == 0 && remove < strl; remove++);
  for (int r = remove; r <= strl; r++){
    *(str + r - remove) = *(str + r);
  }
  *(str + strl - remove) = '\0';
  for(int i = strl - remove; isChar(*(str + i)) == 0 && i >= 0; i--) *(str + i) = '\0';
}

int scan (){
  int wordCount = 0;
  ppWord = (char **) malloc(101 * sizeof(char *));
  for(;1 == scanf("%s", buffer); wordCount++){
    interpunkce(buffer, (int) strlen(buffer));
    int strLeTemp = (int) strlen(buffer);
    if(c){
      for(int i = 0; i < strLeTemp; i++){
        if (buffer[i] >= 'A' && buffer[i] <= 'Z') buffer[i] += 32;
      }
    }
    if (((wordCount + 1) % 100) == 0) ppWord = (char **) realloc (ppWord, (wordCount + 101) * sizeof(char *));
    *(ppWord + wordCount) = (char *) malloc((strLeTemp + 1) * sizeof(char));
    strcpy(*(ppWord + wordCount), buffer);
  }
  return wordCount;
}

void sort (int wordCount){
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
}

int statCount (int wordCount){
  int r = 0;
  for (; r < wordCount; r++){
    *(pStat + diff * 2) = r;
    while(r + 1 < wordCount){
      if (strcmp(*(ppWord + r), *(ppWord + r + 1)) == 0) *(pStat + diff*2 + 1) += 1;
      else break;
      r++;
    }
    diff++;
  }
  return diff;
}

int main (int argc, char **argv){
  whichArgs(argc, argv);
  int wordCount = scan();
  sort(wordCount);
  int leastItems = 1000000;
  int mostItems = 0;

  pStat = calloc(wordCount * 2, sizeof(int));
  printf("Seznam slov:\n");
  int diff = statCount(wordCount);
  if (s == 2){      //Vypis podle abecedy -s 2
    int temp0;
    int temp1;
    for (int i = 1; i < diff; i++) {
      for (int j = 1; j < diff; j++) {
        if (*(pStat + (j - 1)*2 + 1) > *(pStat + j*2 +1)) {
          temp0 = *(pStat + (j - 1) * 2);
          temp1 = *(pStat + (j - 1) * 2 + 1);
          *(pStat + (j - 1) * 2) = *(pStat + j * 2);
          *(pStat + (j - 1) * 2 + 1) = *(pStat + j * 2 + 1);
          *(pStat + j*2) = temp0;
          *(pStat + j*2 + 1) = temp1;
        }
      }
    }
    for (int i = 0; i < diff; i++){
      if (strlen(*(ppWord + *(pStat + i * 2))) <= l) {
        printf ("%s", *(ppWord + *(pStat + i * 2)));
        space(strlen(*(ppWord + *(pStat + i * 2))));
        printf("%d\n", *(pStat + i * 2 + 1) + 1);
        if (*(pStat + i * 2 + 1) < leastItems) leastItems = *(pStat + i * 2 + 1);
        if (*(pStat + i * 2 + 1) > mostItems) mostItems = *(pStat + i * 2 + 1);
      }
    }
  }
  else if (s == 1){     //Vypis podle cetnosti -s 1
    for(int i = 0; i < diff; i++){
      if (strlen(*(ppWord + i)) <= l){
        printf ("%s", *(ppWord + *(pStat + i * 2)));
        space(strlen(*(ppWord + *(pStat + i * 2))));
        printf("%d\n", *(pStat + i * 2 + 1) + 1);
        if (*(pStat + i * 2 + 1) < leastItems) leastItems = *(pStat + i * 2 + 1);
        if (*(pStat + i * 2 + 1) > mostItems) mostItems = *(pStat + i * 2 + 1);
        i += *(pStat + i * 2 + 2);
      }
    }
  }
  printf ("Nejcastejsi:");
  space(strlen("Nejcastejsi:") + 1);
  for (int i = 0; i < diff; i++){
    if (*(pStat + i * 2 + 1) == mostItems) printf (" %s", *(ppWord + *(pStat + i * 2)));
  }
  printf ("\nNejmene caste:");
  space(strlen("Nejmene caste:") + 1);
  for (int i = 0; i < diff; i++){
    if (*(pStat + i * 2 + 1) == leastItems) printf (" %s", *(ppWord + *(pStat + i * 2)));
  }
  printf ("\nPocet slov: %d\n", wordCount);

  for (int i = 0; i < wordCount; i++){
    free(*(ppWord + i));
  }
  free(pStat);
  free(ppWord);
  return 0;
}
