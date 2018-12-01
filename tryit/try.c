#include <stdio.h>
int prd;

void lama (){
	for (int r = 0; r < 2; r++){
	prd = 100;
}

}

int main (){
int a = 1;
int b = 2;
int in;
lama();
printf ("prd = %d\n", prd);
if (0 > scanf("%d", &in) || in < 0) {
printf ("error\n");
}
else printf ("not error\n");
return 0;
}
