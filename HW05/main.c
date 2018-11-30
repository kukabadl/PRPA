#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int numOfColumns;
int numCount = 0;
int * pMatrix;
int max0Size;
int max1Size;
int maxInInterval = 0;

double log(double x);

int cmp (const void * cislo0, const void * cislo1) {
   return (*(int *) cislo0 - *(int *) cislo1);
}

int size (int size){
	//printf ("size = %d ", size);
	int log = 0;
	if (size < 0){
		log = 1;
	}

	while (size != 0){
		size /= 10;
		log++;
	}
	//printf ("log = %d\n", log + 2);
	return log + 2;
}

int sortIt () {
	float interval;
	if (1 != scanf("%d", &numOfColumns)) return 100;
	int inInterval [numOfColumns];
	pMatrix = (int*) malloc(101 * sizeof(int));
	for (;scanf("%d", (pMatrix + numCount)) != EOF; numCount++){
		if ((numCount % 100) == 0){
			pMatrix = realloc(pMatrix, (numCount + 100) * sizeof(int));
		}
	}
	qsort (pMatrix, numCount, sizeof(int), cmp);

	printf("Median: %.2f\n",(numCount%2)? (*(pMatrix + numCount/2)):(*(pMatrix + numCount/2 - 1) + *(pMatrix + numCount/2))/(float)2);
	printf("Number count: %d\n", numCount);
	numCount --;
	printf("Min: %d\n", *(pMatrix));
	printf("Max: %d\n", *(pMatrix + numCount));
	printf("Histogram:\n");
	interval = (float)(fabs((*(pMatrix + numCount) - *(pMatrix))/(float)numOfColumns));

	for (int s = 0; s < numOfColumns; s++){					//najde jaky interval bude mit pri vypsani nejvetsi delku
		if(size((int)((*(pMatrix)) + s * interval)) > max0Size){
			max0Size = size((int)((*(pMatrix)) + s * interval));
		}
		if(size((int)((*(pMatrix)) + s * interval)) > max1Size){
			max1Size = size((int)((*(pMatrix)) + (s + 1) * interval));
		}
	}
	int iter = 0;

	for (int r = 0; r <= numOfColumns; r++){
		inInterval[r] = 0;
		for (; *(pMatrix + iter) < ((*(pMatrix)) + (1 + r) * interval); iter ++){
			inInterval[r]++;
			if (iter + 1 > numCount){
				iter++;
				break;
			}
			if (inInterval[r] > maxInInterval) maxInInterval = inInterval[r];
		}
	}

	for (int r = 0; r < numOfColumns; r++){
		for (int space = 0; space < max0Size - size ((*(pMatrix)) + r * interval); space++){
			printf(" ");
		}
		printf (" %.1f -", (*(pMatrix)) + r * interval);
		for (int space = 0; space < max0Size - size ((*(pMatrix)) + (r + 1) * interval); space++){
			printf(" ");
		}
		printf ("  %.1f|\n",(*(pMatrix)) + (r + 1)*interval);
	}
	free (pMatrix);
	return 0;
}

int main (){
	if (sortIt() == 100){
		printf("Histogram size error\n");
		return 100;
	}
	else return 0;
}
