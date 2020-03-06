#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

double f(double u) return u * u;
double f_u(double u) return 2 * u;
double EXP_f(double u) return exp(u*u);
double EXP_f_u (double u) return 2* u * u * exp(u);


void ODE(double h, double M, double u_0, double complex a_11, double *u){
	double w_1, t_M, t_m;
	int i;
	u[0] = u_0;
	for(i = 0; i < M; i++) {
		t_M = (h / M) * (i + 1);
		t_m = (h / M) * i;
		w_1 = f(u[i]) / (1 - a_11 * (t_M - t_m) * f_u(u[i]));
		u[i+1] = u[i] + (t_M - t_m) * creal(w_1);
	}
	return;
}

void ODESolve(double h, double M_0, double u_0, double complex a_11, double *u, double r, int s){
	double w_1, t_M, t_m, M;
	int i;
	M = M_0 * pow(r,(s - 1));
	u[0] = u_0;
	for(i = 0; i < M; i++) {
		t_M = (h / M) * (i + 1);
		t_m = (h / M) * i;
		w_1 = f(u[i]) / (1 - a_11 * (t_M - t_m) * f_u(u[i]));
		u[i+1] = u[i] + (t_M - t_m) * creal(w_1);
	}
	return;
}
