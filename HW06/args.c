#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int isArg (char * str){
  if (*(str) == '-'){
    if (strlen(str) == 2){
      if(*(str + 1) == 'c'){

      }
      else if(*(str + 1) == 's'){

      }
      else if(*(str + 1) == 'l'){

      }
      else {
        fprintf(stderr, "Warning: Chybna hodnota parametru -s!");
        return -1;
      }
    }
  }

  return 100;
}

int main (int argc, char **argv){
  int arg[3] = {0, 0, 0};  //pole urcuje, zda se jedna o argument nebo cislo
            //-c  -s  -l
  for (int i = 1; i < argc; i++){

  }
}
