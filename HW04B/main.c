#include <stdio.h>
#include <stdlib.h>

int ** ppLoc;
int * pRow;
int * pColumn;
int * pSign;
int * pTemp;
int * pTempMult0;
int * pTempMult1;
int * pMultActive;
int multActive;
int rowTemp;
int columnTemp;
int err = 0;
int multRows;
int multColumns;

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

void print(int *pMat, int nRows, int nColumns){
  printf ("%d %d\n", nRows, nColumns);
  for (int r = 0; r < (nRows * nColumns); r++){
    printf("%d", *(pMat + r));
    if (((r + 1) % nColumns) == 0){
      printf ("\n");
    }
    else printf (" ");
  }
}

//pointer na 1. matici, pointer na 2. matici, sign, rows0, columns0, rows1, columns1
int add(int * pMat0, int * pMat1, int sgn, int nRows0, int nColumns0, int nRows1, int nColumns1){
  int *pTempMult;
  //int *pMat = *(ppLoc + orderMat);
  if(sgn != 2){
    //if (rowTemp == *(pRow + orderMat) && columnTemp  == *(pColumn + orderMat)){
    if (nRows0 == nRows1 && nColumns0  == nColumns1){
      for (int r = 0; r < (nRows0 * nColumns0); r++){
        *(pMat0 + r) += sgn*(*(pMat1 + r));
      }
    }
    else return 100;
  }
  else {
    if (nColumns0 == nColumns1){                  // && rozm [0][0] == rozm [1][1]
      if (multActive) pTempMult = pTempMult1;     //multActive znaci do ktere matice se bude ukladat
      else pTempMult = pTempMult0;
      initTempMultiply(nRows0, nColumns1, multActive);
      for (int i = 0; i < nRows0; i++){
        for (int q = 0; q < nColumns1; q++){
          int mezivypocet = 0;
          for (int r = 0; r < nRows1; r++){
            mezivypocet += *(pMat0 + r + i * nColumns0)*(*(pMat1 + q + r * nColumns1));
          }
          *(pTempMult + q) = mezivypocet;
        }
      }
    }
    else {
      fprintf(stderr, "Error: Chybny vstup!\n");
      return 100;
    }
  }
  return 0;
}

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

//add: pointer na 1, pointer na 2, sign, rows0, columns0, rows1, columns1
  initTempAdd(0);
  int comeBack = 0;
  while (current < count){
    if (*(pSign + current) != 2){
      if ((current + 1) < count) {
        if (*(pSign + current + 1) == 2){
          comeBack = current;
          current++;
          continue;
        }
      }
    }
    else {
      add(pMultActive, *(ppLoc + current), 2, multRows, multColumns, *(pRow + current), *(pColumn + current));
      if ((current + 1) < count) {
        if (*(pSign + current + 1) != 2){
          if (multActive){
            pMultActive = pTempMult1;
            multActive = 0;
          }
          else{
            pMultActive = pTempMult0;
            multActive = 1;
          }
          add(pTemp, *(ppLoc + current + 1), 1, rowTemp, columnTemp, *(pRow + current), *(pColumn + current));
        }
      }
      else{
        //add();
      }
    }
    /*
      if ((current + 1) < count){
        if (*(pSign + current + 1) != 2){
          add(pTemp, *(ppLoc + current + 1), *(pSign + current), rowTemp, columnTemp,*(pRow + current), *(pColumn + current));
        }
        else;
      }
      else {
        if (*(pSign + current) != 2){
          add(pTemp, *(ppLoc + current + 1), *(pSign + current), rowTemp, columnTemp,*(pRow + current), *(pColumn + current));
        }
      }
*/
    current ++;
  }
  print(pTemp, rowTemp, columnTemp);
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
