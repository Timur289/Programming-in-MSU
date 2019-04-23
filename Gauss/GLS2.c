#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void Hilbert(double **, int);
void HilbertPlusE(double **, int);
void iks(double *, int);
void Result(double **, double *, double *, int);
void Gauss(double **, double *, double *, int);
void Vandermond(double **, double *, int);

void Vandermond(double **A, double *xv, int n){
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(j == 0){
                A[i][j] = 1;
            }
            else{
                A[i][j] = pow(xv[i],j);
            }
        }
    }
}

void HilbertBezNull(double **A, int n){
    int i, j, k, c;
    c = 1;
    for(i = 0; i < n; i++) {
        if(i >= n - 500) {
            for(k = 0; k < c; k++){
                A[i][k] = 0;
            }
            for(j = k; j < n; j++) {
                A[i][j] =  1.0/(double)(1+i+j);
            }
            c++;
        }
        else {
            for(j = 0; j < n; j++) {
                A[i][j] =  1.0/(double)(1+i+j);

            }
        }
    }
}

void HilbertBezNullPlusE(double **A, int n){
    int i, j, k, c;
    c = 1;
    for(i = 0; i < n; i++) {
        if(i >= n - 500) {
            for(k = 0; k < c; k++){
                A[i][k] = 0;
            }
            for(j = k; j < n; j++) {
                A[i][j] =  1.0/(double)(1+i+j);
                if(i == j) A[i][j] += 1;
            }
            c++;
        }
        else {
            for(j = 0; j < n; j++) {
                A[i][j] =  1.0/(double)(1+i+j);
                if(i == j) A[i][j] += 1;
            }
        }
    }
}


void Hilbert(double **A, int n){
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[j][i] = 1.0/(double)(1+i+j);
        }
    }
}

void HilbertPlusE(double **A, int n){
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            A[j][i] = 1.0/(double)(1+i+j);
            if(i == j) {
                A[j][i] += 1;
            }
        }
    }
    return;
}

void iks(double *x1, int n){
    int i;
    for(i = 0;i < n;i++){
		x1[i] = 1;
	}
	return;
}

void Result(double **a, double *x1, double *y1, int n){
	int i,j;
	double sum = 0;
    for(i = 0;i < n;i++){
		for(j = 0;j < n;j++){
			sum += a[j][i]*x1[j];
		}
		y1[j] = sum;
		sum=0;
	}
	return;
}

void Gauss(double **a, double *y, double *x, int n){
  double maximum, temp, temp1, temp2, *w;
  int k, index1, index2, i, j;
  for(k = 0; k < n; k++){
    maximum = fabs(a[k][k]);
    index1 = k;
    index2 = k;
    for(i = k; i < n; i++){
		for(j = k; j < n; j++){
			if (fabs(a[j][i]) > maximum){
				maximum = fabs(a[j][i]);
				index1 = j;
				index2 = i;
			}
		}
    }

    for(i = 0; i < n; i++){
		temp = a[j][k];
		a[j][k] = a[j][index1];
		a[j][index1] = temp;
	}

	w = a[k];
	a[k] = a[index2];
	a[index2] = w;

    temp = y[k];
    y[k] = y[index2];
    y[index2] = temp;

	temp = x[k];
	x[k] = x[index1];
	x[index1] = temp;

	temp1 = a[k][k];
	for(i = k; i < n; i++){
        a[k][i] = a[k][i]/temp1;
	}
	y[k] = y[k]/temp1;
	if(k < n-1) {
        for(j = (k + 1); j < n; j++) {
                temp2 = a[j][k];
            for(i = k; i < n; i++) {
                a[j][i] = a[j][i] - (temp2 * a[k][i]);
            }
            y[j] = y[j] - (temp2 * y[k]);
        }
	}

  }
    for(k = n-1; k >= 0; k--) {
		x[k] = y[k];
		for(j = 0; j < k; j++) {
			y[j] = y[j] - a[j][k] * x[k];
		}
	}
	return;
}

//(int n, char **s)
int main(void){
    int n, i, j;
    scanf("%d", &n);
    double **a = NULL, *y1 = NULL,*y2 = NULL, *x1 = NULL, *x = NULL, *y = NULL, *xv = NULL;
    double razn, maxrazn = 0, sumrazn = 0, dlinna = 0, nevaz, maxnevazka = 0, sumnevaz = 0, dlinna2 = 0, t;

//    char r = '9';
//    int r2 = (int)r - 48;

    a = (double **)malloc(n * sizeof(double *));
    for(i = 0; i < n; i++) {
        a[i] = (double *)malloc(n * sizeof(double));
    }

    x1 = (double *)malloc(n * sizeof(double));
    y1 = (double *)malloc(n * sizeof(double));
    y2 = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    y = (double *)malloc(n * sizeof(double));
    xv = (double *)malloc(n * sizeof(double));

    for(i = 0; i < n; i++) {
        xv[i] = (double) i / (n - 1);
    }


    /*for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%le\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/


    iks(x1,n);
    Hilbert(a,n);
    Result(a,x1,y1,n);

    for(j = 0; j < n; j++) {
        y2[j] = y1[j];
    }

    t = clock();
    Gauss(a,y1,x,n);
    t = clock() - t;
    t /= CLOCKS_PER_SEC;

    Hilbert(a,n);
    Result(a,x,y,n);

    for(i = 0; i < n; i++) {
        razn = fabs(x[i]-x1[i]);
        dlinna += razn*razn;
        sumrazn += razn;
        if(razn > maxrazn){
            maxrazn = razn;
        }
    }
    dlinna = sqrt(dlinna);

    for(i = 0; i < n; i++) {
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
    free(xv);
    return 0;
}

