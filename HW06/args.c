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
int main (int argc, char **argv){
  int argument;
  int c = 0;  //-c je pro case sensitive
  int l = -1;  //-l je pro omezeni delky slova
  int s = -1;  //-s je pro razeni - 1 je pro abecedni, 2 podle cetnosti

  for (int i = 1; i < argc; i++){
    argument = isArg(*(argv + i));
    if (argument >= 0){
      if (argument == 0) {        //parametr -c
        c = 1;
      }
      else if (argument == -1 || i + 1 >= argc){   //chybny parametr
      }
      else {
        if (argument == 1){    //parametr -s
          if (0 < isNum(*(argv + i + 1)) && isNum(*(argv + i + 1)) < 3){
            s = isNum(*(argv + i + 1));
            i++;
          }
          else fprintf (stderr, "Warning: Chybna hodnota parametru -s!\n");
        }
        else if (argument == 2){    //parametr -l
          if (0 <= isNum(*(argv + i + 1))){
            l = isNum(*(argv + i + 1));
            i++;
          }
        else fprintf (stderr, "Warning: Chybna hodnota parametru -l!\n");
        }
      }
    }
  }
  printf ("c = %d\n", c);
  printf ("l = %d\n", l);
  printf ("s = %d\n", s);
}
