#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int rozm [2][2];      //0 -> pocet radku (vyska), 1 -> pocet sloupcu (sirka)
char sign;
int * pMat0;
int * pMat1;

unsigned char input (){
  unsigned char iter = 0;
  int in;

  if (2 != scanf("%d %d", &rozm[iter][0], &rozm[iter][1])){
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }

  int matrix0 [rozm[iter][0]][rozm[iter][1]];
  pMat0 = *matrix0;
  for (int i = 0; i < sizeof (matrix0)/4; i++){
    if (1 != scanf ("%d", &in)){
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
	   }
     *(pMat0+i) = in;

  }

  if (1 != scanf(" %c", &sign)){
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }

  iter ++;

  if (2 != scanf("%d %d", &rozm[iter][0], &rozm[iter][1])){
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }

  int matrix1 [rozm[iter][0]][rozm[iter][1]];
  pMat1 = *matrix1;

  for (int i = 0; i < sizeof (matrix1)/4; i++){
    if (1 != scanf ("%d", &in)) {
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
    }
    *(pMat1+i) = in;
  }

  if (sign == '+'){
    if (rozm[0][0] == rozm[1][0] && rozm[0][1] == rozm[1][1]){
      printf ("%d %d\n", rozm[0][0], rozm[0][1]);
      for (int r = 0; r < rozm[0][0]*rozm[0][1]; r++){
        printf("%d", (*(pMat0 + r) + *(pMat1 + r)));
        if ((r + 1) % (rozm[0][1]) == 0){
          printf ("\n");
        }
        else printf (" ");
      }
    }
    else {
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
    }
  }

  else if (sign == '-'){
    if (rozm[0][0] == rozm[1][0] && rozm[0][1] == rozm[1][1]){
      printf ("%d %d\n", rozm[0][0], rozm[0][1]);
      for (int r = 0; r < rozm[0][0]*rozm[0][1]; r++){
        printf("%d", (*(pMat0 + r) - *(pMat1 + r)));
        if ((r + 1) % (rozm[0][1]) == 0){
          printf ("\n");
        }
        else printf (" ");
      }
    }
    else {
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
    }
  }
  else if (sign == '*'){
    if (rozm[0][1] == rozm[1][0]){ // && rozm [0][0] == rozm [1][1]
      printf ("%d %d\n", rozm[0][0], rozm[1][1]);   //rozm[1][1] >> pocet sloupcu
      for (int i = 0; i < rozm [0][0]; i++){
        for (int q = 0; q < rozm [1][1]; q++){
          int mezivypocet = 0;
          for (int r = 0; r < rozm[1][0]; r++){
            mezivypocet += *(pMat0 + r + i*rozm[0][1])*(*(pMat1 + q + r*rozm[1][1]));
          }
          printf("%d", mezivypocet);
          if (q == rozm [1][1] - 1){
            printf ("\n");
          }
          else printf (" ");
        }
      }
    }
    else {
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
    }
  }
  else {
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }
  return 0;
}

int main (){
  return input();
}
