#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[2];
    if (scanf ("%d %d", &a[0], &a[1]))
      {
        if (abs(a[0]) <= 10000 && abs(a[1]) <= 10000){
            printf("Desitkova soustava: %d %d\n", a[0], a[1]);
            printf("Sestnactkova soustava: %x %x\n", a[0], a[1]);
            printf("Soucet: %d + %d = %d\n", a[0], a[1], a[0] + a[1]);
            printf("Rozdil: %d - %d = %d\n", a[0], a[1], a[0] - a[1]);
            printf("Soucin: %d * %d = %d\n", a[0], a[1],(a[0] * a[1]));

            if (a[0] != 0 && a[1] != 0){
                printf("Podil: %d / %d = %d\n", a[0], a[1], (a[0] / a[1]));
            }
            else printf("Nedefinovany vysledek!\n");

            printf("Prumer: %.1f\n", (a[0] + a[1])/(float)2);
        }
        else printf("Vstup je mimo interval!\n");
      }
    return 0;
  }
