#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);
double F(double);
double Simpson(double, double, double, double, double *, double *, int *);

double f(double x){
	return sqrt(exp(3 * x) + exp(2 * x));
}

double F(double x){
	return (2 * pow((exp(x) + 1),1.5))/3;
}

double Simpson(double h, double b, double x, double eps, double *sumerr, double *sumerrabs, int *nstep){
	double err, errabs, I1, I2, h_new, chi;
	double fx, fx2, fx4, fx1, fx3;
	double sum = 0;
	(*sumerr) = 0;
	(*sumerrabs) = 0;
	(*nstep) = 0;
	fx = f(x);
	while(x < b - eps){
		fx1 = f(x + h), fx2 = f(x + 0.5 * h), fx3 = f(x + 0.75 * h), fx4 = f(x + 0.25 * h);
		I1 = (h/6)*(fx + 4*fx2 + fx1);
		I2 = (h/12)*(fx + 4*fx4 + 2*fx2 + 4*fx3 + fx1);
		err = (I2 - I1)/15;
		errabs = fabs(err);
		chi = errabs / eps;

		if(chi > 1e5) chi = 1e5;
		else if(chi < 1e-5) chi = 1e-5;
		chi = pow(chi,0.2);
		h_new = 0.95 * h / chi;

		if(errabs < eps) {
			fx = fx1;
			x += h;
			sum += I2;
			(*sumerr) += err;
			(*sumerrabs) += fabs(err);
			(*nstep)++;
		}

		h = h_new;
		if(x + h > b){
			h = b - x;
		}
	}
	return sum;
}

int main(void){
	double a, b, eps1, eps2, eps3, x, h, pogr1, pogr2, pogr3;
	double sumerr1, sumerrabs1, sumerr2, sumerrabs2, sumerr3, sumerrabs3;
	int nstep1, nstep2, nstep3;
	double S1, S2, S3;
	scanf("%le%le", &a, &b);

	h = b-a;

	eps1 = 1e-7;
	eps2 = 1e-9;
	eps3 = 1e-11;

	x=a;

	S1 = Simpson(h,b,x,eps1,&sumerr1,&sumerrabs1,&nstep1);
	S2 = Simpson(h,b,x,eps2,&sumerr2,&sumerrabs2,&nstep2);
	S3 = Simpson(h,b,x,eps3,&sumerr3,&sumerrabs3,&nstep3);

	pogr1 = S1 - (F(b) - F(a));
	pogr2 = S2 - (F(b) - F(a));
	pogr3 = S3 - (F(b) - F(a));

	printf("\nEPS = %le\n\n", eps1);
	printf("Pogreshnost = %le\nSumerr = %le\nSumerrabs = %le\nSteps = %d\n\n", pogr1, sumerr1, sumerrabs1, nstep1);

	printf("EPS = %le\n\n", eps2);
	printf("Pogreshnost = %le\nSumerr = %le\nSumerrabs = %le\nSteps = %d\n\n", pogr2, sumerr2, sumerrabs2, nstep2);

	printf("EPS = %le\n\n", eps3);
	printf("Pogreshnost = %le\nSumerr = %le\nSumerrabs = %le\nSteps = %d\n\n", pogr3, sumerr3, sumerrabs3, nstep3);

	printf("\nChislo = %lg\n", (S1-S2)/(S2-S3));
	printf("Chislo dlya ERR = %lg\t%lg\n", (pogr1/pogr2), (pogr2/pogr3));
	return 0;
}
