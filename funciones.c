/* Funciones de prueba para mono-objetivo */
//#include <math.h>
//#include <stdio.h>
#define PI 3.14159265358979323846
#include "rand.c"

double A[4][10] = {{4.0, 1.0, 8.0, 6.0, 3.0, 2.0, 5.0, 8.0, 6.0, 7.0},
				  {4.0, 1.0, 8.0, 6.0, 7.0, 9.0, 5.0, 1.0, 2.0, 3.6},
				  {4.0, 1.0, 8.0, 6.0, 3.0, 2.0, 3.0, 8.0, 6.0, 7.0},
				  {4.0, 1.0, 8.0, 6.0, 7.0, 9.0, 3.0, 1.0, 2.0, 3.6}};
double C[10] = {0.1, 0.2, 0.2, 0.4, 0.6, 0.6, 0.3, 0.7, 0.5, 0.5};
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
		//sum += (i+1)*pow(x[i],4) + rndreal(0,1);
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
	// x1: [-5,10]
	// x2: [0,15]
	// tres minimos
	// (-pi,12.25) = (pi,2.275) =(9.42478,2.475) 0.397887
	double a, b, c, d, e, f;
	a = 1.0;
	b = 5.1/(4.0*PI*PI);
	c = 5.0/(PI);
	d = 6.0;
	e = 10.0;
	f = 1.0/(8.0*PI);
	return a*pow(x[1] - b*x[0]*x[0] + c*x[0] - d, 2) + e*((1.0-f)*cos(x[0])) + e;
}

double SQRN5(double *x){
	// xi: [0, 10]
	// s3 = (4,4,4,4) = -10.15320 j = 5
	// s4 = (4,4,4,4) = -10.402820 j= 7
	// s5 = (4,4,4,4) = -10.53628 j=10
		double r, res = 0.0;
	int j, i;
	for (j=0; j<7; j++){
		r = 0.0;
		for (i = 0; i< 4; i++){
			r += pow((x[i] - A[i][j]), 2.0) + C[j];
		}
		res += (1.0/r);
	}
	
	return -res;
}

double sixhump(double *x){
	// x1: [-3, 3]
	// x2: [-2, 2]
	// (-0.0898, 0.7126) = -1.0316
	// (0.0898, -0.7126) = -1.0316
	return (4.0 - 2.1*x[0]*x[0] + pow(x[0],4)/3)*x[0]*x[0] + x[0]*x[1] + (-4.0 + 4.0*x[1]*x[1])*x[1]*x[1];
}

double shubert(double *x){
	// xi [-10.0, 10.0]
	// 760 local minima, 18 of which are global minima
	// whit -186.73
	double r1, r2;
	r1 = r2 = 0.0;
	int i, j;
	for (i = 0; i<5; i++){
		r1 += (i+1.0)*cos((i+2.0)*x[0] + (i+1.0));
		r2 += (i+1.0)*cos((i+2.0)*x[2] + (i+1.0));
	}
	return r1*r2;
}

double stuckman(double *x){
	// xi [0, 10.0]
	// The global maximum is located at
	/*
				(r11, r21) si m1 > m2
	(x1, x2) =  (r12, r22) de lo contrario
	*/
}

double easom(double *x){
	// xi [-100, 100]
	//minimim (PI,PI) = -1
	return -cos(x[0])*cos(x[1])*exp(-pow(x[0]-PI,2.0)-pow(x[1]-PI,2.0));
}

double b1(double *x){
	//xi [-50, 50]
	// (0,0) = 0
	return x[0]*x[0] + 2*x[1]*x[1] - 0.3*cos(3.0*PI*x[0]) - 0.4*cos(4.0*PI*x[1]) + 0.7;
}

double b2(double *x){
	//xi [-50, 50]
	// (0,0) = 0
	return x[0]*x[0] + 2*x[1]*x[1] - 0.3*(cos(3.0*PI*x[0])*cos(4.0*PI*x[1])) + 0.3;
}

double b3(double *x){
	//xi [-50, 50]
	// (0,0) = 0
	return x[0]*x[0] + 2*x[1]*x[1] - 0.3*cos(3.0*PI*x[0]) - cos(4.0*PI*x[1]) + 0.3;
}

double colville(double *x){
	return 100.0*pow(x[1]-x[0]*x[0],2.0) + pow(1-x[0],2.0) + 90.0*pow(x[3]-x[2]*x[2],2.0) + pow(1.0 - x[2],2.0) + 10.1*(pow(x[1]-1.0,2.0) + pow(x[3]-1.0,2.0)) + 19.8*(x[1]-1.0)*(x[3]-1.0);
}