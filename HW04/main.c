#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int32_t rozm[2];      //0 -> pocet radku (vyska), 1 -> pocet sloupcu (sirka)


unsigned char scan(){
  if (2 != scanf("%d %d", &rozm[0], &rozm[1])){
    return error();
  }
  while (1 == scanf()){

  }
  return 0;
}

unsigned char error (void){
  fprintf(stderr, "Error: Chybny vstup!\n");
  return 101;
}


unsigned char main (){
  return scan();
}
