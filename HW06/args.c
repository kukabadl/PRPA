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
  if (strlen(str) == 2){

  }
  else if (strlen(str) > 2){

  }
  return 100;
}

int main (int argc, char **argv){
  int[argc];  //pole urcuje, zda se jedna o argument nebo cislo
  for (int i = 0; i < argc; i++){

  }
}
