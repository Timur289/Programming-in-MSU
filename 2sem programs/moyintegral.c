#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define eps 1e-12
double g(double a, double b) {
	return cos(a)-cos(b);
}

double f(double x){
	return sin(x);
}
double ls(double *X, double *Y, int n){
	int i, c = 0;
	double sum = 0;
	double h, sr;
	for(i=0;i<(n-1);i++){
		h = X[i+1] - X[i];
		sr = (Y[i] + Y[i+1]) * 0.5;
		sum += sr * h;
		c++;
	}
	printf("[%d]\n", c);
	return sum;
}
int main(void){
	int n, i;
	double *X,*Y,a,b,y,shagtr, razn, t;
	scanf("%le%le", &a, &b);
	printf("Kol-vo tochek: ");
	scanf("%d",&n);
	shagtr = (b - a) / (n - 1);
	X=(double*)malloc(n*sizeof(double));
	Y=(double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++){
		X[i]=a + shagtr * i;
		Y[i]=f(X[i]);
	}
	t = clock();
	y = ls(X,Y,n);
	t = clock() - t;
	t /= CLOCKS_PER_SEC;
	razn = fabs(g(a,b) - y);
	printf("%le\t%le\t%le\n", y, g(a,b), razn);
	printf("\n%.30lf\n", t);
	free(X);
	free(Y);
	return 0;
}
