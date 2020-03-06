#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double f(double);
double f_u(double);
void ODE(double, double, double, double complex, double *);
void ODESolve(double, double, double, double complex, double **, int, int);


int main(void) {
	FILE *f;
	int i, s, r, S,j;
	double T, t_0, h, M, **u_basic, u_0, shag, re, im;
	double **p_eff, sum1 = 0, sum2 = 0;
	t_0 = 0; T = 5; re = 0.5; im = 0.5; u_0 = 0; S = 15; r = 2;
	/*printf("Vvedite t_0\n");
	scanf("%lf", &t_0);
	printf("Vvedite T\n");
	scanf("%lf",&T);
	printf("Vvedite re\n");
	scanf("%lf",&re);
	printf("Vvedite im\n");
	scanf("%lf",&im);
	printf("Vvedite u_0\n");
	scanf("%lf",&u_0);
	printf("Vvedite S\n");
	scanf("%d",&S);
	printf("Vvedite r\n");
	scanf("%d",&r);*/
	double complex a_11 = re + im * I;
	M = 200;
	
	u_basic = (double **)malloc(S * sizeof(double *));
	for(i = 0; i < S; i++) u_basic[i] = (double *)malloc(M * sizeof(double));
	p_eff = (double **)malloc(S * sizeof(double*));
	for(i = 0; i < S; i++) p_eff[i] = (double *)malloc(M * sizeof(double));
	h = T - t_0;
	
//	tmp = CMPLX (1., 2.);
//	printf ("%lu\n", sizeof (tmp));
//	printf ("(%f, %f)\n", creal (a_11), cimag (a_11));
//	return 0;
//	printf ("%.15e\n", exp (1));

	//ODE(h,M,u_0,a_11,u);
	for(s = 1; s <= S; s++)  ODESolve(h,M,u_0,a_11,u_basic,r,s);
	/*for(j = 0; j < S; j++) {
		for(i = 0; i < M; i++) {
			printf("u_basic[%d][%d] = %lf\t", j, i, u_basic[j][i]);
		}
		printf("\n\n");
	}*/
	for(i = 2; i < S; i++){ 
		for(j = 1; j < M; j++) {
			sum1 = fabs(u_basic[i-1][j] - u_basic[i-2][j]);
			sum2 = fabs(u_basic[i][j] - u_basic[i-1][j]);
			p_eff[i][j] = log(sum1/sum2)/log(2);
			printf("p_eff[%d][%d] = %0.4lf  ", i, j, p_eff[i][j]);
			printf("[sum1] = %lf \t [sum2] = %lf\n\n", sum1, sum2);
			sum1 = 0; sum2 = 0;
		}
		printf("\n");
	}
/*	f = fopen("Gamid.txt", "w");
	if(!f) {
		printf("Cannot create the file\n");
		return -1;
	}
	else {
		for(i = 0; i < M; i++) {
			shag = (h/M) * i;
			fprintf(f, "%0.2lf %0.2lf\n", shag, u_basic[i]);
		}
	}*/
	f = fopen("GamidEXP(S15).txt", "w");
	if(!f) {
		printf("Cannot create the file\n");
		return -1;
	}
	else {
		for(i = 1; i < M; i++) {
			shag = (h/M) * i;
			fprintf(f, "%0.2lf %0.2lf\n", shag, p_eff[14][i]);
			//fprintf(f, "%0.2lf %0.2lf\n", shag, u[i]);
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
	//return 2 * u;
//	return 2 * u;
//	return u * exp(u);
	return 2 * u * exp(u*u);
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

void ODESolve(double h, double M_0, double u_0, double complex a_11, double **u_basic, int r, int s){
	double w_1,t_M, t_m, M;
	double *u;
	int i, j;
	
	
	M = M_0 * pow(r,(s-1));
	u = (double *)malloc(M * sizeof(double));
	

	u[0] = u_0;
	for(i = 0; i < M; i++) {
		t_M = (h/M) * (i + 1);
		t_m = (h/M) * i;
		w_1 = f(u[i])/(1 - a_11 * (t_M - t_m) * f_u(u[i]));
		u[i+1] = u[i] + (t_M - t_m) * creal(w_1);
	}
	
	for(i = 0; i < M_0; i++) {
		j = pow(r,(s-1));
		u_basic[s-1][i] = u[(i) * j];
	}
	
	return;

}
