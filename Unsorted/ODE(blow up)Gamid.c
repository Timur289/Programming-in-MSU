#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double f(double);
double f_u(double);
void ODE(double, double, double, double complex, double *);


int main(void) {
	FILE *f;
	int i;
	double T, t_0, h, M, *u, u_0, shag, re, im;

	printf("Vvedite t_0\n");
	scanf("%lf", &t_0);
	printf("Vvedite T\n");
	scanf("%lf",&T);
	printf("Vvedite re\n");
	scanf("%lf",&re);
	printf("Vvedite im\n");
	scanf("%lf",&im);
	printf("Vvedite u_0\n");
	scanf("%lf",&u_0);
	double complex a_11 = re + im * I;
	M = 200;
	//

	u = (double *)malloc(M * sizeof(double));
	h = T - t_0;

	ODE(h,M,u_0,a_11,u);

	for(i = 0; i < M; i++) {
		printf("u[%d] = %lf\n\n", i, u[i]);
	}

	f = fopen("SecondODE0.5.txt", "w");
	if(!f) {
		printf("Cannot create the file\n");
		return -1;
	}
	else {
		for(i = 0; i < M; i++) {
			shag = (h/M) * i;
			fprintf(f, "%0.2lf %0.2lf\n", shag, u[i]);
		}
	}
	return 0;
}

double f(double u) {
//	return u * u;
//	return 1 + u * u;
//	return exp(u);
	return exp(u*u);
}

double f_u(double u) {
//	return 2 * u;
//	return 2 * u;
//	return u * exp(u);
	return 2 * u  * exp(u*u);
}


void ODE(double h, double M, double u_0, double complex a_11, double *u){
	double w_1,t_M, t_m;
	int i;
	u[0] = u_0;
	for(i = 0; i < M; i++) {
		t_M = (h/M) * (i + 1);
		t_m = (h/M) * i;
		w_1 = f(u[i])/(1 - a_11 * (t_M - t_m) * f_u(u[i]));
		u[i+1] = u[i] + (t_M - t_m) * creal(w_1);
	}
	return;
}
