/*

Sistema inmune artificial basado en el principio clonal
para problemas de optimización mono-objetivo.
26-sept-22
Con representación real
*/
#define tampob 100 /* tamaño de población */
#define numrmp 30  /* numero de individuos que se reemplazan cada generación */ 
#define nclon 8 	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sia.h"
#include "funciones.c"

int main(int argc, char * argv[])
{
	//fun = &t3;
	//fun = &f5;
	fun = &gold_price;

	Rseed = 0.0;
	lim[0] =  -2.0;
	lim[1] = 2.0;
	int i;
	tol = 0.000000001;
	tampobclon = 0;
	for (i = 1; i <= tampob; i++){
	/* utilizando la expresión de CLONALG 
		de Castro, L.N.; Von Zuben, F.J. (2002). Learning and optimization
		using the clonal selection principle. , 6(3), 239–251. 
		doi:10.1109/tevc.2002.1011539  
	*/
		tampobclon += (int)round((tampob)/i);
	}
	//tampobclon = tampob*nclon;

	anticuerpo *temp;
	
	memory_allocation();

	randomize();
	
	inicializar_pob();
	ordenamiento(0, tampob-1, (pob));
	
	//Gmax = 280;
	printf("random: %f\n", rndreal(lim[0], lim[1]));
	Gmax = 1000;
	for (gen = 0; gen < Gmax; gen++){
		
		generacion();
		
		printf("-----------------POB ACT----------------------\n");
		imprimir_pob(nuevapob, tampob);
		printf("-----------------POB ACT FIN----------------------\n\n");
		encontrar_mejor();
		
		printf("Mejor: %f	afinidad: %f	generacion: %d\n", mejor.obj, mejor.afinidad, mejor.gen);
		
		temp = nuevapob;
		nuevapob  = pob;
		pob = temp ;
	}
	
	free_all();
}

/* Funciones */

/* ----------------------------- MEMORIA ------------------------------- */

void memory_allocation(){

	unsigned numbytes;               
	unsigned numb;
	unsigned numclon;
	
	//char *malloc();
	int i;
	/* Reserva de memoria para poblaciones de anticuerpos actual y nueva */

	numbytes = tampob * sizeof(anticuerpo);
	numb = longitud * sizeof(double);
	
	if ((pob = (anticuerpo *) malloc(numbytes)) == NULL)
		nomemory("actual población");

	if ((nuevapob = (anticuerpo *) malloc(numbytes)) == NULL)
		nomemory("nueva población");
		
	/* Reserva memoria para los clones */
	
	numclon = tampobclon * sizeof(anticuerpo);
	
	if ( (clones = (anticuerpo *)malloc(numclon) )== NULL)
		nomemory("población de clones"); 
	
	/* Reserva de memoria para las cadenas de anticuerpos y variables de decisión */
/*
	for ( i = 0; i < tampob; i++ ) {

		if ((pob[i].cadena = (unsigned *) malloc(numb)) == NULL)
			nomemory("anticuerpos actual población");

		if ((nuevapob[i].cadena = (unsigned *) malloc(numb)) == NULL)
			nomemory("anticuerpos nueva población");
	
		if ((pob[i].x = (double *)malloc(numvar)) == NULL)
			nomemory("variables actual población");
		
		if ((nuevapob[i].x = (double *)malloc(numvar)) == NULL)
			nomemory("variables nueva población");
			
	}
*/	
	/* Mejor anticuerpo */
/*	
	if ( (mejor.cadena = (unsigned *)malloc(numb) ) == NULL)
		nomemory("anticuerpos mejor ab");
*/	
	/* Población de clones */
/*	
	for ( i = 0; i< clon; i++) {
		if ((clones[i].cadena = (unsigned *)malloc(numb)) == NULL)
			nomemory("anticuerpos población de clones");
		
		if ((clones[i].x = (double *)malloc(numvar)) == NULL)
			nomemory("variables actual población");
	} 

*/	printf("memoria lista\n");
}

void free_all(){
	int i;
	int clon = 0;
	
	/*
	for ( i = 0 ; i < tampob ; i++){
		free(pob[i].cadena);
		free(nuevapob[i].cadena);
		free(pob[i].x);
		free(nuevapob[i].x);
	}*/
	
	free(pob);
	free(nuevapob);
	
	/*
	for (i =  0; i<clon; i++){
		free(clones[i].cadena);
		free(clones[i].x);
	}
	*/
	free(clones);
}

void nomemory(char *string){
	printf("ERROR! malloc: falta memoria haciendo %s\n", string);
	exit(1);
}

/* ----------------------------- AIS ------------------------------- */
void inicializar_pob(){
	/* Inicializar la población */
	int i, j, k;
	//double lim[2] = {-1.28, 1.28};

	for( j = 0; j < tampob; j++){
		
		for( i = 0 ; i < longitud ; i++){

			pob[j].cadena[i]=rndreal(lim[0], lim[1]);
		}
		
		objetivo(&(pob[j]));
		pob[j].padre = 0;
		//printf("obj: %f\n", pob[j].obj);
		pob[j].mutaciones = 0;         /* Initialize mutation indicator */
	}

	afinidad(pob, tampob);
	
	printf("inicializar pob listo\n");
}


void objetivo(anticuerpo *ab){
	double f;
	f = (*fun)(ab->cadena);
	ab->obj = f;
}
void afinidad(anticuerpo *p, int size){
	/* Calcular afinidad de un anticuerpo en la población */
	/* normalizar la afinidad */
	int i,j;
	double mayor, menor;
	int indice;
	mayor = p[0].obj;
	menor = p[0].obj;
	indice = 0;

	for (i=0; i< size; i++){
		if (menor > p[i].obj) {
			menor = p[i].obj; 
			indice = i;
		}
	}	
	
	//printf("menor: %d\tobj: %f\n", indice, p[indice].obj);
	/* Calculando distancia euclideana con el mejor individuos */
	for(i=0; i<size; i++){
		p[i].afinidad = 0.0;
		for (j = 0; j< longitud; j++){
			p[i].afinidad +=pow(p[indice].cadena[j] - p[i].cadena[j],2);
		}
		p[i].afinidad = sqrt(p[i].afinidad);
		//printf("%d afinidad: %f\n", i, p[i].afinidad);
	}	
	
	mayor = p[indice].afinidad;
	menor = p[0].afinidad;
	for (i=1; i< size; i++){
		if (menor > p[i].afinidad) menor = p[i].afinidad;
		if (mayor < p[i].afinidad) mayor = p[i].afinidad;	 
	}
	printf("mayor: %f, menor: %f\n", mayor, menor);
	
	//printf("mayor: %f, menor: %f --------\n", mayor, menor);
	//printf("x1: %f, x2: %f\n", p[indice].x[0], p[indice].x[1]);
	for(i = 0; i< size; i++){
		p[i].afinidad = (mayor - p[i].afinidad)/(mayor-menor);
		//printf("aff: %f\n", pob[i].afinidad);
	}
	
}

/* Ejecutar los procesos relacionados a cada generación */
void generacion(){
	int i,j, clon = 0;
	printf("gen\n");
	for (i=0; i<tampob; i++){
		pob[i].numclon = (unsigned)round(tampob/(i+1));
	}

	clonar();
	hipermutar();
	afinidad(clones, tampobclon);

	seleccion_neg(tampobclon);
	ordenamiento(0, tampobclon-1, (clones));

	printf("-----------------CLONES----------------------\n");
	
	imprimir_pob(clones, tampobclon);
	
	printf("-----------------CLONES FIN----------------------\n\n");
	
	

	seleccionar();
	
	
	reemplazar(numrmp);
	afinidad(nuevapob, tampob);
	
	ordenamiento(0, tampob-1, (nuevapob));
	/* número de clones para cada individuo*/
	
	
	

}

void imprimir_pob(anticuerpo *pobla, int tam){
	int i, j ;
	
	for (i = 0; i < tam; i++){
	printf("%d\t", i);
		for (j = 0; j< numvar; j++)
			printf("x%d: %f\t", j+1, pobla[i].cadena[j]);
		printf(" feval: %f\tafinidad: %f\tpadre: %d\n", pobla[i].obj, pobla[i].afinidad, pobla[i].padre);
	}
}
/* Ordenamiento */
void swap(anticuerpo *a, anticuerpo *b){
	anticuerpo x = *a;
	*a = *b;
	*b = x;
}

int particion(anticuerpo *p, int low, int high){
	anticuerpo pivote = p[high];
	int i = low-1;
	for (int j= low; j <= high-1; j++){
	//printf("afinidad: %f\n", pob[j].obj);
		if(p[j].afinidad > pivote.afinidad){
			i++;
			swap(&p[i], &p[j]);
		}
	}
	swap(&p[i+1], &p[high]);
	return i+1;
}

void ordenamiento(int low, int high, anticuerpo *p){
	/* ordenar la población de antigenos con base en la afinidad*/
	/* Quicksort */
	if (low < high){
		int pi = particion(p, low, high);
		
		ordenamiento(low, pi-1, p );
		ordenamiento(pi+1, high, p);
	}
		
}


void clonar(){
	/* producir n elementos clonados de cada anticuerpo seleccionado */ 
	/* utilizando la expresión de CLONALG para determinar el número de clones */

        int clon,c;
        int i,j,k;
        k=0;
        clon = 0;

        for (j = 0; j < tampob; j++){
			for (i = 0; i < pob[j].numclon; i++){
				clones[k] = pob[j];
				if (pob[j].numclon>1){
					
					clones[k].numclon = i+1;
				}else{
					clones[k].numclon = 0;
				}
				clones[k].padre = j;
				k++;
			}
		}
}
double min(double a, double b){
	if(a > b){
		return b;
	}else{
		return a;
	}
}

void hipermutar(){
	/* mutar a anticuerpos en proporción a su afinidad */
	/* la hipérmutación sólo se aplica en la población de elementos clonados */
	double pm = 0.0;
	double sl, sr,nm,u;
	int i,j, k;
	int clon = 0;
	//nm = 20.0;
	//nm = 100.0 + gen;
	double sigma, s1, s2;
	//double lim[2] = {-1.28, 1.28};
	k= 0;
	nm = 40.0;
	for (i=0; i<tampobclon; i++){
		clones[i].mutaciones = 0;
		/*expresión de pm de CLONALG*/
		pm = exp(-10.0*clones[i].afinidad);
		if (clones[i].numclon !=0){
			pm = exp(-10*(1.0/clones[i].numclon));
		}else{
			pm = exp(-10*(1.0/(i+1.0)));
		}
		
		for (j=0; j<longitud; j++){
			/* Mutación aritmetica o parameter based mutation Deb 1995 */
			if(flip(pm)){
				/* Mutación polinomial (parameter based mutation) */
				//u = rndreal(0.0, 1.0);
				
				sigma = min(clones[i].cadena[j] - lim[0], lim[1] - clones[i].cadena[j]) / (lim[1] - lim[0]);
				//s1 = (clones[i].cadena[j] - lim[0])/ (lim[1]-lim[0]);
				//s2 = (lim[1]- clones[i].cadena[j])/ (lim[1]-lim[0]);
				u = rndreal(0,1);
				
				sl = -1.0 + pow((2.0*u + (1.0-2.0*u)*pow(1.0-sigma, nm+1.0)), (1.0/(1.0+nm))) ;
				sr = 1.0 - pow(2.0*(1.0-u) + 2.0*(u-0.5)*pow((1.0-sigma), nm+1.0), (1.0/(1.0+nm)));
				
				if (u > 0.5){
					clones[i].cadena[j] += sr*(lim[1] -lim[0]);
					//printf("sr: %f\n", sr);
				}else{
					clones[i].cadena[j] += sl*(lim[1]- lim[0]);
					//printf("sl: %f\n", sl);
				}

				if (clones[i].cadena[j] > lim[1] ){
					clones[i].cadena[j] = lim[1];
				}else if(clones[i].cadena[j] < lim[0]){
					clones[i].cadena[j] = lim[0];
				}
				
				clones[i].mutaciones++;
			}
			
		}
		
		if (clones[i].mutaciones > 0){
			// Actualizar información del individuo
			//printf("decodificado\n");
			//printf("%d mutt: %d\n", i, clones[i].mutaciones);
			//printf("mutadx %d\n", i);
			objetivo(&(clones[i]));
		}
		//printf("mut?: %d\tval fin: %f\t numclones: %d\n",clones[i].mutaciones, clones[i].obj, clones[i].numclon);
	}
	
}
void seleccionar(){
	/* seleccionar n elmentos de la población actual y los clones */
	/* 
	   se asume que ambas poblaciones (la población principal y la de clones)
	   están ordenadas
	
	   Selecciona los mejores anticuerpos (menor val obj) y los coloca en la 
	   siguiente población asegurnado de esta forma que el tamaño de la población
	   de generación generación permanezca constante 
	*/
	int i,j,k, l, n;
	
	// Tamaño de la población actual: tampob;
	// El ciclo será controlado por el tamaño de la población de la gen siguiente
	// es decir, el tamaño de la población actual
	j = k = i = n = 0;
	double mejor;
	int indice;
	printf("nueva seleccion\n");
	while (j < tampob ){
		if ( pob[i].obj > clones[k].obj){
			nuevapob[j] = clones[k];
			k++;
		}else if (pob[i].obj < clones[k].obj){
			nuevapob[j] = pob[i];
			i++;
		} else{
			if (flip(0.5) ){
				nuevapob[j] = clones[k];
				k++;
			}else{
				nuevapob[j] = pob[i];
				i++;
			}
		}
		//if (flip(0.2)){
			//mejor = clones[j*nclon].obj;
			/*
			if (j==0){
				mejor = clones[0].obj;
				//indice = j*nclon;
				indice = 0;
			}else{
				n += pob[j-1].numclon;
				mejor = clones[n].obj;
				indice = n;
			}
			for (l = 0; l<pob[j].numclon; l++){
				if (mejor > clones[i].obj){
					mejor = clones[i].obj;
					indice = i;
				}
				i++;
			}
				if ( pob[j].obj > clones[indice].obj){
					nuevapob[j] = clones[indice];
				}else{
					nuevapob[j] = pob[j];
				}
			*/
		j++;
	}
	/*
	j = k = i = 0;
	
	while (j < tampob ){
		//if (flip(0.2)){
		if ( pob[i].obj > clones[k].obj){
			nuevapob[j] = clones[k];
			k++;
		}else if (pob[i].obj < clones[k].obj){
			nuevapob[j] = pob[i];
			i++;
		} else{
			if (flip(0.5) ){
				nuevapob[j] = clones[k];
				k++;
			}else{
				nuevapob[j] = pob[i];
				i++;
			}
		}
		*/
	
		/*}else{
			if (flip(0.5) ){
				nuevapob[j] = clones[k];
				k++;
			}else{
				nuevapob[j] = pob[i];
				i++;
			
		}
		}*/
	
}
void reemplazar(int n){
	/* Reemplaza un número fijo de individuos de la población nueva 
	   con las peores afinidades con nuevos individuos generados 
	   aleatoriamente
	*/
	int i,j,k;
	//double lim[2] = {-1.28, 1.28};
	for (i = tampob-1; i>= tampob-n; i--){
		
		for (j = 0; j < longitud; j++){
			nuevapob[i].cadena[j] = rndreal(lim[0], lim[1]);
		}
		objetivo(&(nuevapob[i]));
		
		nuevapob[i].numclon = 0;         /* Initialize mutation place */
		nuevapob[i].mutaciones = 0;         /* Initialize mutation indicator */
		
	}

}

void seleccion_neg(int size){
	/* 
	Asignar afinidad de 0 a los clones que sean identicos a sus padres 
	después de efecutuada la mutación   
	*/
	int i, j;
	double sum;
	
	for (i=0; i<size; i++){
		sum = 0.0;
		
		for (j=0; j<longitud; j++){
			sum += pow((clones[i].cadena[j]-pob[clones[i].padre].cadena[j]), 2.0);
		}
		sum = sqrt(sum);

		if (sum < tol ){
			clones[i].afinidad = 0.0;
		}
	}
}

void encontrar_mejor(){
	/* localizar el anticuerpo con la mejor afinidad y asignarlo a mejorAb */
	
	int i,j;
	double mej = INFINITY;
	for (i=0; i < tampob; i++){
		if ( pob[i].obj < mej ) {
			 mej = pob[i].obj;
			 j = i;
		}
	}
	/* copiando el mejor a su lugar */
	for (i=0; i< longitud; i++)
	{
	mejor.cadena[i] = pob[j].cadena[i];
	}
	mejor.obj =  pob[j].obj;
	mejor.afinidad = pob[j].afinidad;
	mejor.gen = gen;
}