#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "ODE.h"

int main(void){
  	FILE *f, *f1;
  	int i, s, r, S, j;
  	double T, t_0, h, M, *u, u_0, shag, re, im;
    double **p_eff, **u_basic, sum1 = 0, sum2 = 0;

  	printf("Vvedite t_0\n");   scanf("%lf", &t_0);
  	printf("Vvedite T\n");     scanf("%lf",&T);
  	printf("Vvedite re\n");    scanf("%lf",&re);
  	printf("Vvedite im\n");    scanf("%lf",&im);
  	printf("Vvedite u_0\n");   scanf("%lf",&u_0);

    double complex a_11 = re + im * I;
  	M = 200;
    h = T - t_0;

    u = (double *)malloc(M * sizeof(double));

    ODE(h,M,u_0,a_11,u);

    f = fopen("SecondODE0.5.txt", "w");
    if(!f) {
      printf("Cannot create the file\n");
      return -1;
    }
    else {
      for(i = 0; i < M; i++) {
        shag = (h / M) * i;
        fprintf(f, "%0.2lf %0.2lf\n", shag, u[i]);
      }
    }

    t_0 = 0; T = 5; re = 0.5; im = 0.5; u_0 = 0; S = 15; r = 2;

    u_basic = (double **)malloc(S * sizeof(double *));
    for(i = 0; i < S; i++) u_basic[i] = (double *)malloc(M * sizeof(double));

    p_eff = (double **)malloc(S * sizeof(double*));
    for(i = 0; i < S; i++) p_eff[i] = (double *)malloc(M * sizeof(double));

    for(s = 1; s <= S; s++)  ODESolve(h,M,u_0,a_11,u_basic,r,s);

    for(i = 2; i < S; i++){
      for(j = 1; j < M; j++) {
        sum1 = fabs(u_basic[i-1][j] - u_basic[i-2][j]);
        sum2 = fabs(u_basic[i][j] - u_basic[i-1][j]);
        p_eff[i][j] = log(sum1/sum2)/log(2);
        sum1 = 0; sum2 = 0;
      }
    }

    f1 = fopen("GamidEXP(S15).txt", "w");
    if(!f1) {
      printf("Cannot create the file\n");
      return -1;
    }
    else {
      for(i = 1; i < M; i++) {
        shag = (h / M) * i;
        fprintf(f1, "%0.2lf %0.2lf\n", shag, p_eff[14][i]);
      }
    }

    free(p_eff);
    free(u_basic);
    free(u);
    fclose(f);
    fclose(f1);
    return 0;
}
