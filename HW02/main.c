#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int cisel, klad, zapor, sude, liche, suma, max = -10000, min = 10000;

void stat(int input){
  if (cisel) {
    printf (", %d", input);
  }
  else {
    printf ("%d", input);
  }

  cisel++;

  if (input > 0){
    klad++;
  }
  else if (input < 0){
    zapor++;
  }

  if (input % 2 == 0){
    sude++;
  }
  else liche++;

  suma += input;

  if (max < input){
    max = input;
  }

  if (min > input){
    min = input;
  }

}

void present(void){
    printf("\n");
    printf("Pocet cisel: %d\n", cisel);
    printf("Pocet kladnych: %d\n", klad);
    printf("Pocet zapornych: %d\n", zapor);
    printf("Procento kladnych: %.2f\n", (float) 100 * klad / cisel);
    printf("Procento zapornych: %.2f\n", (float) 100 * zapor / cisel);
    printf("Pocet sudych: %d\n", sude);
    printf("Pocet lichych: %d\n", liche);
    printf("Procento sudych: %.2f\n", (float) 100 * sude / cisel);
    printf("Procento lichych: %.2f\n", (float)100 * liche / cisel);
    printf("Prumer: %.2f\n", (float) suma / cisel);
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
    return;
}

int main()
{
  int input;
  while(scanf ("%d ", &input) != EOF) {
    if (abs(input) <= 10000)
    {
      stat(input);
    }
    else {
      printf ("\nError: Vstup je mimo interval!\n");
      return 100;
    }
  }
  present();
    return 0;
}
