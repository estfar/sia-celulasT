/*

Sistema inmune artificial basado en el principio clonal
para problemas de optimización mono-objetivo.
26-sept-22
con representación real
*/
#define longitud 2
//76 /* longitud de los anticuerpos */
#define numvar 2   /* numero de variables de decisión */
#include "aleatorio.c"
//#include "funciones.h"	

/* Estructura: Anticuerpos (Ab) */
typedef struct anticuerpo{
	double		cadena[longitud];		/* arreglo que contiene cadena la */
	double		obj;			/* valor de la evaluación de las función objetivo */
	double		afinidad;		/* valor de la afinidad del anticuerpo */
	int			padre;
	int 		mutaciones;		/* numero de mutaciones */
	int		    numclon;		/* número de clones */
	
}anticuerpo;

/* Estructura: mejor */
typedef struct mejorAb{
	double	cadena[longitud];
	double		obj;
	double		afinidad;
	int			gen;
}mejorAb;

/* Funciones */

void memory_allocation();
void memory_for_selection();
void free_all();
void free_selection();
void nomemory(char *);

void inicializar_pob();
void decodificar(anticuerpo *, int);
void afinidad(anticuerpo *, int);	/* calcular objetivo de un anticuerpo en la población */
void generacion();			/* Ejecutar los procesos relacionados a cada generación */
void objetivo(anticuerpo *);		/* calcular afinidad de un anticuerpo en la población */
void ordenamiento(int , int , anticuerpo *);						/* ordenar la población de antigenos */
void clonar();							/* producir n elementos clonados de cada anticuerpo seleccionado */ 
								/* aquí es necesario crear una subpoblación de los clones */
void hipermutar();						/* mutar a anticuerpos con menores afinidades */
void seleccionar( );						/* seleccionar n elmentos de la población actual y los clones */
void reemplazar(int);						/* reemplazar los n ab con las peores afinidades con ab nuevos */
void encontrar_mejor();						/* localizar el anticuerpo con la mejor afinidad y asignarlo a mejorAb */
double min(double a, double b);
void seleccion_neg(int size);						/* elimina los clones identicos a sus padres después de la mutación */

void imprimir_pob(anticuerpo *, int tam);						/* imprimir los individuos de una población:
								   valores de variables, eval de funcion, afinidad, número de clones (?)*/
/* Variables */
int gen;				/* contador de generaciones */
int Gmax;				/* número máximo de generaciones */
anticuerpo *pob;			/* generación de anticuerpos actual */
anticuerpo *nuevapob;			/* generación de anticuerpos siguiente */
anticuerpo *clones;
mejorAb mejor;
double (*fun)(double *);
int tampobclon;
double lim[2];
double tol;
// seria mejor si declaro la varible que va a contener mi función? yo creo que sí ja

