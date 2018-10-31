#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

int32_t mat1 [2];       //false, sloupcu je mat1[0], radku mat1[1]
int32_t mat2 [2];       //true

void input (bool kteraMat){
  for (int i = 0; i < 2; i++){
    if (kteraMat){
      if (1 == scanf ("%d", &mat2[i])){

      }
    }
    else {

    }
  }
}
int main() {
input (false);

  return 0;
}
