#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


void Hilbert(double *, int);
void iks(double *, int);
void Result(double *, double *, double *, int);
void Gauss(double *, double *, double *, int);

void Hilbert(double *A, int n){
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[i + j * n] = 1.0/(double)(1+i+j);
        }
    }
}

void iks(double *x1, int n){
    int i;
    for(i = 0; i < n; i++){
		x1[i] = 1;
	}
}

void Result(double *a, double *x1, double *y1, int n){
	int i, j;
	double sum = 0;
    for(j = 0; j < n; j++) {
		for(i = 0; i < n; i++) {
			sum += a[i + j * n] * x1[i];
		}
		y1[j] = sum;
		sum = 0;
	}
}

void Gauss(double *a, double *y, double *x, int n){
  double maximum, temp, temp1, temp2;
  int k, index1, index2, i, j;
  for(k = 0; k < n; k++){
    maximum = fabs(a[k + k * n]);
    index1 = k;
    index2 = k;
    for(i = k; i < n; i++){
		for(j = k; j < n; j++){
			if (fabs(a[i + j * n]) > maximum){
				maximum = fabs(a[i + j * n]);
				index1 = i;
				index2 = j;
			}
		}
    }
    for(i = 0; i < n; i++){
		temp = a[i + k * n];
		a[i + k * n] = a[i + index2 * n];
		a[i + index2 * n] = temp;
	}
    for(j = 0; j < n; j++){
		temp = a[k + j * n];
		a[k + j * n] = a[index1 + j * n];
		a[index1 + j * n] = temp;
	}


    temp = y[k];
    y[k] = y[index2];
    y[index2] = temp;

	temp = x[k];
	x[k] = x[index2];
	x[index2] = temp;

	temp1 = a[k + k * n];
	for(i = k; i < n; i++){
        a[i + k * n] = a[i + k * n]/temp1;
	}
	y[k] = y[k]/temp1;
	if(k < n-1) {
        for(j = (k + 1); j < n; j++) {
                temp2 = a[k + j * n];
            for(i = k; i < n; i++) {
                a[i + j * n] = a[i + j * n] - (temp2 * a[i + k * n]);
            }
            y[j] = y[j] - (temp2 * y[k]);
        }
	}

  }
    for(k = n-1; k >= 0; k--) {
		x[k] = y[k];
		for(j = 0; j < k; j++) {
			y[j] = y[j] - a[k + j * n] * x[k];
		}
	}
}

int main(int argc, char const *argv[]){
    int n, i, l;
    double *a = NULL, *y1 = NULL,*y2 = NULL, *x1 = NULL, *x = NULL, *y = NULL;
    double razn, maxrazn = 0, sumrazn = 0, dlinna = 0, nevaz, maxnevazka = 0, sumnevaz = 0, dlinna2 = 0, t;
    n = 0;
    l = strlen(argv[1]);
    for(i = l - 1; i >=0; i--) {
        n += ((int)argv[1][i] - 48) * (int)pow(10, l - 1 - i);
    }

    a = (double *)malloc(n * n * sizeof(double));

    x1 = (double *)malloc(n * sizeof(double));
    y1 = (double *)malloc(n * sizeof(double));
    y2 = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));

    iks(x1,n);
    Hilbert(a,n);
    Result(a,x1,y1,n);

    for(i = 0; i < n; i++) {
        y2[i] = y1[i];
    }

    t = clock();
    Gauss(a,y1,x,n);
    t = clock() - t;
    t /= CLOCKS_PER_SEC;

    Hilbert(a,n);
    Result(a,x,y,n);

    for(i = 0;i < n;i++) {
        razn = fabs(x[i]-x1[i]);
        dlinna += razn*razn;
        sumrazn += razn;
        if(razn > maxrazn){
            maxrazn = razn;
        }
    }
    dlinna = sqrt(dlinna);

    for(i = 0;i < n;i++) {
        nevaz = fabs(y[i]-y2[i]);
        dlinna2 += nevaz*nevaz;
        sumnevaz += nevaz;
        if(nevaz > maxnevazka){
            maxnevazka = nevaz;
        }
    }
    dlinna2 = sqrt(dlinna2);
    printf("Maxrazn: %le\nSumrazn: %le\nDlinna: %le\n", maxrazn, sumrazn, dlinna);
    printf("\n");
    printf("Maxnevazka: %le\nSumnevaz: %le\nDlinnaNevaz: %le\n", maxnevazka, sumnevaz, dlinna2);
    printf("Operating time: %lg\n", t);

    free(x1);
    free(y1);
    free(y2);
    free(x);
    free(y);
    return 0;
}

