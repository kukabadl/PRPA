#include <stdio.h>
#include <stdlib.h>

int ** ppLoc;
int * pRow;
int * pColumn;
int * pSign;
int * pTemp;
int * pTempMult0;
int * pTempMult1;
int multActive;
int rowTemp;
int columnTemp;
int err = 0;

void initTempAdd(int current){
  rowTemp = *(pRow + current);
  columnTemp = *(pColumn + current);
  free (pTemp);
  pTemp = (int *)calloc(rowTemp * columnTemp, sizeof(int));
  for (int r = 0; r < (rowTemp * columnTemp); r++){
    *(pTemp + r) = *(*(ppLoc + current) + r);
  }
}

void initTempMultiply(int nRows, int nColumns, int which){
  if (which){
    free (pTempMult1);
    pTempMult1 = (int *)calloc(nRows * nColumns, sizeof(int));
  }
  else if (which == 0){
    free (pTempMult0);
    pTempMult0 = (int *)calloc(nRows * nColumns, sizeof(int));
  }
}

void print(int current){    //pokud je current == -1, pak se vytiskne Temp matice, jinak prislusna matice
  if (current == -1){
    printf ("%d %d\n", rowTemp, columnTemp);
    for (int r = 0; r < (rowTemp * columnTemp); r++){
      printf("%d", *(pTemp + r));
      if (((r + 1) % columnTemp) == 0){
        printf ("\n");
      }
      else printf (" ");
    }
  }
  else {
    printf ("%d %d\n", *(pRow + current), *(pColumn + current));
    for (int r = 0; r < (*(pRow + current) * (*(pColumn + current))); r++){
      printf("%d", *(*(ppLoc + current) + r));
      if (((r + 1) % (*(pColumn + current))) == 0){
        printf ("\n");
      }
      else printf (" ");
    }
  }
}

int add(int orderMat, int sgn){    //funkce pricteni matice k Temp
  if (orderMat != 0){
    int *pMat = *(ppLoc + orderMat);
    if (rowTemp == *(pRow + abs(orderMat)) && columnTemp  == *(pColumn + abs(orderMat))){
      if (orderMat < 0){
        orderMat *= -1;
        for (int r = 0; r < (rowTemp * columnTemp); r++){
          *(pTemp + r) = (*(pTemp + r) + sgn*(*(pMat + r)));
        }
      }
    }
    else {
      return 100;
    }
  }
  else {
    if (multActive) int *pMat = *pTempMult1;
    else int *pMat = *pTempMult0;
    if (rowTemp == *(pRow + abs(orderMat)) && columnTemp  == *(pColumn + abs(orderMat))){
      if (orderMat < 0){
        orderMat *= -1;
        for (int r = 0; r < (rowTemp * columnTemp); r++){
          *(pTemp + r) = (*(pTemp + r) + sgn*(*(pMat + r)));
        }
      }
    }
    else {
      return 100;
    }
  }
  return 0;
}

int subtract(int orderMat){
  int *pMat = *(ppLoc + orderMat);
  //int *pMat1 = *(ppLoc + orderMat1);
  if (rowTemp == *(pRow + orderMat) && columnTemp  == *(pColumn + orderMat)){
    for (int r = 0; r < (rowTemp * columnTemp); r++){
      *(pTemp + r) = (*(pTemp + r) - (*(pMat + r)));
    }
  }
  else {
    return 100;
  }
  return 0;
}
/*
int multiply(){
  return 0;
}
*/

int sign (int count){
  char in;
  int out = scanf(" %c", &in);
  if (out == EOF) return -1;
  else if (1 != out) return 100;
  else if (in == '+'){
     *(pSign + count) = 1;
     return 0;
   }
  else if (in == '-'){
     *(pSign + count) = -1;
     return 0;
   }
  else if (in == '*'){
    *(pSign + count) = 2;
    return 0;
  }
  return 100;
}

int save (int count){
  if (2 != scanf("%d %d", (pRow + count), (pColumn + count))){
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
  }
  int sizeMat = *(pRow + count) * (*(pColumn + count));
  *(ppLoc + count) = (int*)calloc(sizeMat, sizeof(int));
  for (int i = 0; i < sizeMat; i++){
    if (1 != scanf ("%d", (*(ppLoc + count) + i))){
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
	   }
  }
  return sign(count);
}

unsigned char run (){
  int count = 0;
  int current = 0;
  int saved;

  ppLoc = (int **)calloc(1, sizeof(int *));
  pRow = (int *)calloc(1, sizeof(int));
  pColumn = (int *)calloc(1, sizeof(int));
  pSign = (int *)calloc(1, sizeof(int));

  while (1) {
    ppLoc = (int **)realloc(ppLoc, sizeof(int *) * (count + 1));
    pRow = (int *)realloc(pRow, sizeof(int) * (count + 1));
    pColumn = (int *)realloc(pColumn, sizeof(int) * (count + 1));
    pSign = (int *)realloc(pSign, sizeof(int) * (count + 1));
    saved = save(count);

    if (saved == 100){
      return 100;
    }
    else if (saved == -1){
      break;
    }
    count ++;
  }

  initTempAdd(0);
  while (current < count){
    if (*(pSign + current) == 1){       //sign == "+"
      if ((current + 1) < count){
        if (*(pSign + current + 1) != 2){
          add(current + 1);
        }
        else;
      }
      else add(current + 1);
    }
    else if (*(pSign + current) == -1){       //sign == "-"
      if ((current + 1) < count){
        if (*(pSign + current + 1) != 2){
          subtract(current + 1);
        }
        else;
      }
      else subtract(current + 1);
    }
    else if (*(pSign + current) == 2){
      multiply(current);
    }

  /*
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
    current ++;
  }

  print(-1);

  for (int b = 0; b <= count; b++){
    free (*(ppLoc + b));
  }

  free (ppLoc);
  free (pRow);
  free (pColumn);
  free (pSign);
  free (pTemp);
  return 0;
}

int main (){
    err  = run();

    return err;
}
