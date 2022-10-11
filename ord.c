#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void swap(double *, double *);
int particion(double *, int, int);
void ordenamiento(int , int, double *);


int main(){
	// Arreglo con los elementos a ordenar
	double arreglo[6] = {3.2, 3.6, 9.0, 2.0, 3.1, 0.3};
	ordenamiento(0, 5, arreglo);
	printf("fin ordenamiento");

	for (int i=0; i< 6; i++){
		printf("%d: %f\n", i, arreglo[i]);
	}
}

/* Ordenamiento */
void swap(double *a, double *b){
	double x = *a;
	*a = *b;
	*b = x;
}

int particion(double *pob, int low, int high){
	double pivote = pob[high];
	int i = low-1;
	for (int j= low; j <= high-1; j++){
	//printf("afinidad: %f\n", pob[j].obj);
		if(pob[j] < pivote){
			i++;
			swap(&pob[i], &pob[j]);
		}
	}
	swap(&pob[i+1], &pob[high]);
	return i+1;
}

void ordenamiento(int low, int high, double *pob){
	/* ordenar la población de antigenos con base en la afinidad*/
	/* Quicksort */
	if (low < high){
		int pi = particion(pob, low, high);
		printf("%d\n", pi);
		
		ordenamiento(low, pi-1, pob );
		ordenamiento(pi+1, high, pob);
	}
		
}
