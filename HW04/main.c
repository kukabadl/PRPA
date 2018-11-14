#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int rozm [2][2];      //0 -> pocet radku (vyska), 1 -> pocet sloupcu (sirka)
char sign;
int * pMat0;
int * pMat1;

void add (int *mat0, int *mat1, int radku, int sloupcu){
  printf ("%d %d\n", radku, sloupcu);
  printf ("mat0[0] = %d\n", *mat0);
  //printf ();
  for (int r = 0; r < radku*sloupcu; r++){
    if (r % sloupcu == 0){
      printf ("\n");
    }
    printf(" %d", (*(mat0 + r) + *(mat1 + r)));

  }
  printf ("\n");
}

void fillMatrix (int *mat, int pocPrvku){
  int in;
  for (int i = 0; i < pocPrvku; i++){
    scanf ("%d", &in);
    *(mat+i) = in;
  }
  for (int i = 0; i < pocPrvku; i++){
    printf ("matx[%d] = %d\n", i, *(mat+i));
  }
}

unsigned char input (){
  unsigned char iter = 0;
  while (iter < 2){
    if (2 != scanf("%d %d", &rozm[iter][0], &rozm[iter][1])){
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 101;
    }
    if (iter == 0){
      int matrix0 [rozm[iter][0]][rozm[iter][1]];
      pMat0 = *matrix0;
      fillMatrix(pMat0, sizeof (matrix0)/4);
    }
    else {
      int matrix1 [rozm[iter][0]][rozm[iter][1]];
      pMat1 = *matrix1;
      fillMatrix(pMat1, sizeof (matrix1)/4);
    }
    if (iter == 0){
      if (1 != scanf(" %c", &sign)){
        fprintf(stderr, "Error: Chybny vstup!\n");
        return 101;
      }
    }
    iter ++;
  }
  if (sign == '+' && rozm[0][0] == rozm[1][0] && rozm[0][1] == rozm[1][1]){
    add(pMat0, pMat1, rozm[0][0], rozm[0][1]);
  }
  else if (sign == '-' && rozm[0][0] == rozm[1][0] && rozm[0][1] == rozm[1][1]){
    printf ("%c", sign);
  }
  else if (sign == '*'){
    printf ("%c", sign);
  }
  else {
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 101;
  }
  return 0;
}

int main (){
  return input();
}
