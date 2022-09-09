/*

Sistema inmune artificial basado en el principio clonal
para problemas de optimización mono-objetivo.
09-sept-22

*/

/* Estructura: Anticuerpos (Ab) */
typedef struct anticuerpo{
	unsigned	*cadena;		/* arreglo que contiene la cadena */
	double		obj;			/* valor de la evaluación de las función objetivo */
	double		afinidad;		/* valor de la afinidad del anticuerpo */
	int 		mutaciones;		/* numero de mutaciones */
	int			lugarmut;		/* lugar de la mutación: en caso que se de un solo punto */
	
}anticuerpo;

/* Estructura: mejor */
typedef struct mejorAb{
	unsigned	*cadena;
	double		obj;
	double		afinidad;
}mejorAb;

/* Funciones */

void memory_allocation();
void memory_for_selection();
void free_all();
void free_selection();
void nomemory(char *);

void inicializar_pob();
void calc_afinidad();		/* calcular afinidad de cada anticuerpo en la población */
void seleccionar();			/* seleccionar un número n de anticuerpos en para clonación */
void clonar();				/* producir n elementos clonados de cada anticuerpo seleccionado */ 
							/* aquí es necesario crear una subpoblación de los clones */
void hipermutar();			/* mutar a anticuerpos con menores afinidades */
void actualizar_pob();		/* actualizar la población con n de los clones generados */
void encontrar_mejor();		/* localizar el anticuerpo con la mejor afinidad y asignarlo a mejorAb */

/* Variables */

anticuerpo *pob;			/* generación de anticuerpos actual */
anticuerpo *nuevapob;		/* generación de anticuerpos siguiente */


