#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void Matrica(double **A, int n){
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[i][j] = 1.0/(double)(1+i+j);
            if(i == j){
				A[i][j] += 1;
			}
        }
        if(i == j){
			A[i][j] += 1;
		}
    }
    return;
}
double * nevazka(double **A,double *x2, int n){
    int i, j;
    double *y2 = NULL;
    y2 = (double *)malloc(n*sizeof(double));
    double sum = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[i][j] = 1.0/(double)(1+i+j);
        }
    }
    for(i = 0;i < n;i++){
		for(j = 0;j < n;j++){
			sum += A[i][j]*x2[j];
		}
		y2[i] = sum;
		sum=0;
	}
    return y2;
}

double * iks(int n){
    int i;
    double *x1;
    x1 = (double *)malloc(n*sizeof(double));
    for(i = 0;i < n;i++){
		x1[i] = 1;
	}
	return x1;
}
double * r1(double **a, double *x1, int n){
	int i,j;
	double *y1,sum = 0;
	y1 = (double *)malloc(n*sizeof(double));
	for(i = 0;i < n;i++){
		for(j = 0;j < n;j++){
			sum += a[i][j]*x1[j];
		}
		y1[i] = sum;
		sum=0;
		printf("y1[%d] = %le\n", i, y1[i]);
	}
	printf("\n");
	return y1;
}
double * gauss(double **a, double *y, int n){
  double *x, max;
  int k, index,i,j;
  x = (double *)malloc(n * sizeof(double));
  k = 0;
  while (k < n)
  {
    max = fabs(a[k][k]);
    index = k;
    for(i=k+1;i<n;i++){
		if (fabs(a[i][k]) > max){
			max = fabs(a[i][k]);
			index = i;
		}
    }
    for(j = 0;j < n;j++){
		double temp = a[k][j];
		a[k][j] = a[index][j];
		a[index][j] = temp;
	}
    double temp = y[k];
    y[k] = y[index];
    y[index] = temp;
    for(i=k;i < n;i++){
		double temp = a[i][k];
			for(j = 0;j < n;j++){
				a[i][j] = a[i][j] / temp;
			}
			y[i] = y[i] / temp;
		if (i != k){
			for(j = 0;j < n;j++){
				a[i][j] = a[i][j] - a[k][j];
			}
			y[i] = y[i] - y[k];
		}
    }
    k++;
  }
    printf("\n");
	for(k = n-1;k >= 0;k--){
		x[k] = y[k];
		for(i=0;i < k;i++){
			y[i] = y[i] - a[i][k] * x[k];
		}
	}
	return x;
}
int main(void){
    int n, i;
    double **a = NULL, *y1 = NULL, razn, maxrazn = 0, sumrazn = 0, dlinna = 0,nevaz, maxnevazka = 0,sumnevaz = 0,dlinna2 = 0;
    double *x = NULL, *x1 = NULL, *y = NULL;
    scanf("%d", &n);
    a = (double **)malloc(n * sizeof(double *));
    for(i = 0; i < n; i++){
        a[i] = (double *)malloc(n * sizeof(double));
    }
    Matrica(a,n);
    x1 = iks(n);
    for(i = 0;i < n;i++){
		printf("x1[%d] = %le\n", i, x1[i]);
	}
	printf("\n");
    y1 = r1(a,x1,n);
    x = gauss(a,y1,n);
    for (i = 0; i < n; i++){
        printf("x[%d] = %le\n", i, x[i]); 
    }
    printf("\n");
	y = nevazka(a,x,n);
    for (i = 0; i < n; i++){
        printf("y[%d] = %le\n", i, y[i]);
    }
    printf("\n");
    for(i = 0;i < n;i++) {
        razn = fabs(x[i]-x1[i]);
        dlinna += razn*razn;
        sumrazn += razn;
        if(razn > maxrazn){
            maxrazn = razn;
        }
    }
    for(i = 0;i < n;i++) {
        nevaz = fabs(y[i]-y1[i]);
        dlinna2 += nevaz*nevaz; 
        sumnevaz += nevaz;
        if(nevaz > maxnevazka){
            maxnevazka = nevaz;
        }
    }
    printf("Maxrazn: %le\nSumrazn: %le\nDlinna: %le\n", maxrazn, sumrazn, sqrt(dlinna));
    printf("\n");
    printf("Maxnevazka: %le\nSumnevaz: %le\nDlinnaNevaz: %le\n", maxnevazka, sumnevaz, sqrt(dlinna2));
    return 0;
}
