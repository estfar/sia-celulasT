#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funciones.c"

int main(){
	
	double (*fun)(double *);
	fun = &f5;

	if (8 < INFINITY){
		printf("El número es menor que infinito :0\n");
	}
	else{
		printf("no lo es ja!\n");
	}
	double res;
	double x[] = {-49.0, 49.0};
	res = (*fun)(x);
	printf("rsultado: %f\n", res);

	printf("valor del exponenete: %f\n", exp(-10));

	double v = 0.0;
	double y[4] = {1.04,1.09,0.95,0.90};
	v = t3(y);
	printf("val: %f\n", v);
}
