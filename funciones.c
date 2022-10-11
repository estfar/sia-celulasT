/* Funciones de prueba para mono-objetivo */
//#include <math.h>
//#include <stdio.h>
#define PI 3.14159265358979323846
#include "rand.c"

double f5(double *x){
	//limites = -65.536 65.536
double a[2][25];
	double a0[5] = {-32.0, -16.0, 0.0,16.0, 32.0};
	double fun, sum = 0.0;
	fun = 0.0;
	double K = 500.0;
	int i,j = 0;
	/*-------------------- Matriz a -----------------------*/
	for (i = 0; i< 25; i++)
	{
		a[0][i] = a0[j];
		j++;
		if ( j == 5 )
		{
			j = 0;	
		}
		
		if ( i >= 0 && i < 5 )
		{
			a[1][i] = -32.0;
		}
		else if ( i >= 5 && i < 10 )
		{
			a[1][i] = -16.0;
		}
		else if ( i>=10 && i < 15 )
		{
			a[1][i] = 0.0;
		}
		else if ( i>=15 && i<20 ){
			a[1][i] = 16.0;
		}
		else
		{
			a[1][i] = 32.0;
		}
	}
	/* función sum_{j=1}^{25} */
	for (j = 0; j< 25; j++){
		for( i=0; i<2; i++ ) {
		sum += pow( x[i] - a[i][j], 6.0);
			
		}
	 fun += ( (1.0)/( (j +1.0) + sum) ) ;
	}
	fun = (1.0)/( 0.002 + (fun));
	//printf("fun--: %f\n", fun);
	return fun;
}

/* Generalized Rosembrock's function */
double f2(double *x){
	// intervalo de las variables -5.12 5.12
	int i,j;
	double sum;
	sum = 0.0;
	for(i = 0; i<2-1; i++){
		sum = (100.*pow(x[i+1] - pow(x[i],2),2) + pow((x[i]-1),2));
	}
	return sum;
}

double f3(double *x){
	// intervalo de la variables: -5.12 5.12	
	int i,j;
	double sum;
	sum = 0.0;
	for (i=0; i<2; i++){
		sum += floor(x[i]);
	}
	return 12.0+sum;
}

double t3(double *x){
	// intervalo de las variables : -20 20
	int i,j;
	double sum = 0.0;
	sum = pow(10*(x[1]-x[0]*x[0]),2) + pow((1-x[0]),2) + 90*pow((x[3]-x[2]*x[2]),2) + pow((1-x[2]),2) + 10*pow((x[1]+x[3]-2),2) + 0.1*pow((x[1]-x[3]),2);
	return sum;
}

double clong1(double *x){

	return pow(sin(5*PI), 6); 
}

double f4(double *x){
	int i;
	int n = 2;
	double sum = 0.0;
	for(i = 0; i< n; i++){
		sum += (i+1)*pow(x[i],4) + rndreal(0,1);
	}
	return sum ;
}

double f8(double *x){
	//[-500 500]
	int i;
	double sum = 0.0;
	for (i=0; i<4; i++){
		sum += (-1)*x[i]*sin(sqrt(abs(x[i])));
	}
	return sum;
}

double f6(double *x){
	// -100 100
	// min (0,0) = 0
	double sum =0.0;
	sum = 0.5 + ( pow(sin(sqrt(pow(x[0],2) + pow(x[1],2))),2)- 0.5 )/ ( pow(1.0+0.001*(pow(x[0],2)+pow(x[1],2)), 2) );
	return sum;
}

double f7(double *x){
	return pow((x[0]*x[0]+x[1]*x[1]), 0.25) * (pow(sin(50*pow(x[0]*x[0]+x[1]*x[1], 0.1)),2) + 1.0) ;
}

double gold_price(double *x){
	// -2 2
	// min(0,-1) =  3
	return (1.0 + pow((x[0]+x[1]+1),2)*(19-14*x[0] + 3*x[0]*x[0] - 14*x[1] + 6*x[0]*x[1] + 3*x[1]*x[1]))*(30+pow(2*x[0] - 3*x[1],2)*(18-32*x[0] + 12*x[0]*x[0] + 48*x[1]-36*x[1]*x[0] + 27*x[1]*x[1]));
}

double RCOS(double *x){
	return 1.0*pow(x[1] - (5.1/(4*PI*PI))*x[1]*x[1] + 5*x[0]/PI - 36.0, 2) + 10.0*((1-1/(8*PI))*cos(x[0])) + 10.0;
}