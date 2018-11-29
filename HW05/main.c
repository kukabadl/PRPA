#include <stdio.h>
#include <stdlib.h>

int numOfColumns;
int numCount = 0;
int * pMatrix;

int input () {
	if (1 != scanf("%d", &numOfColumns)) return 100;
	pMatrix = (int*) malloc(101 * sizeof(int));
	for (;scanf("%d", (pMatrix + numCount)) != EOF; numCount++){
		if ((numCount % 100) == 0){
			pMatrix = realloc(pMatrix, (numCount + 100) * sizeof(int));
		}
		printf ("%d\n", numCount);
	}
	numCount --;
	free (pMatrix);
	return 0;
}

int main (){
	if (input() == 100){
		printf("Histogram size error\n");
		return 100;
	}
	else return 0;
}
