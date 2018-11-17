#include <stdio.h>
#include <stdlib.h>

//int rozm [2][2];      //0 -> pocet radku (vyska), 1 -> pocet sloupcu (sirka)

int ** ppLoc;
int * pRow;
int * pColumn;
int * pSign;

int err = 0;

unsigned char run ();

int main (){
    err  = run();
    free (ppLoc);
    free (pRow);
    free (pColumn);
    free (pSign);
    return err;
}

/*
int add(int * in0, int * in1, int * dim0, int * dim1){
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
  return 0;
}

int subtract(){
  return 0;
}

int multiply(){
  return 0;
}
*/

int sign (){
  char in;
  if (1 != scanf(" %c", &in)){
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }
  if (in == '+') return 1;
  else if (in == '-') return -1;
  else if (in == '*') return 2;
  return 0;
}

int save (int count){
  if (2 != scanf("%d %d", (pRow + count), (pColumn + count))){
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }
  int sizeMat = *(pRow + count) * (*(pColumn + count));
  printf("Matsize = %d\n", sizeMat);

  *(ppLoc + count) = (int*)calloc(sizeMat, sizeof(int *));
  printf("**(ppLoc + count) = %d\n", **(ppLoc + count));

  for (int i = 0; i < sizeMat; i++){
    if (1 != scanf ("%d", (*(ppLoc + count) + i))){
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
	   }
     printf("hodnota prvku matice = %d\n", *(*(ppLoc + count) + i));
  }

  *(pSign + count) = sign();

  printf("sign = %d\n", *(pSign + count));
return 0;
}

unsigned char run (){
  ppLoc = (int **)calloc(1, sizeof(int *));
  pRow = (int *)calloc(1, sizeof(int));
  pColumn = (int *)calloc(1, sizeof(int));
  pSign = (int *)calloc(1, sizeof(int));

  int count = 0;

  while (1) {
    if (100 == save(count)){
      return 100;
    }
    count ++;
    ppLoc = (int **)realloc(ppLoc, sizeof(int *) * (count + 1));
    pRow = (int *)realloc(pRow, sizeof(int) * (count + 1));
    pColumn = (int *)realloc(pColumn, sizeof(int) * (count + 1));
    pSign = (int *)realloc(pSign, sizeof(int) * (count + 1));
  }

  /*
  if (sign == '+'){
    add();
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
    if (rozm[0][1] == rozm[1][0]){                  // && rozm [0][0] == rozm [1][1]
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
  */
  return 0;
}
