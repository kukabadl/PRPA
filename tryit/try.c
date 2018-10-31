#include <stdio.h>

int main (){
  printf("\rlabadum\n");
  printf("\rsss\n");
  fsetpos(1, 2);
  addstr("Hello world");
}
