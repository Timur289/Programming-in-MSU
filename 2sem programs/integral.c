#include <stdio.h>
#include <math.h>
#include <time.h>
double integral(double, double, double, double, double *, double *, int *);

double g(double a, double b) {
	return cos(a)-cos(b);
}
	
double f(double x) {
	return sin(x);
}
		
int main(void) {
	double x, eps1, eps2, eps3;
	double h, a, b, W1, W2, W3; 
	double pogrewnost1, pogrewnost2, pogrewnost3; 
	double sumd1, sumdabs1, sumd2, sumdabs2, sumd3, sumdabs3;
	int i1, i2, i3;
	
	printf("Vvedite pervoye cislo\n");
	scanf("%lg", &a);
	printf("Vvedite vtoroye cislo\n");
	scanf("%lg", &b);
	h = b-a;
	
	eps1 = 1.e-7;
	eps2 = 1.e-9;
	eps3 = 1.e-11;
	
	x=a;
	
	W1 = integral(h,x,eps1,b, &sumd1, &sumdabs1, &i1);
	W2 = integral(h,x,eps2,b, &sumd2, &sumdabs2, &i2);
	W3 = integral(h,x,eps3,b, &sumd3, &sumdabs3, &i3);
	
	pogrewnost1 = W1 - g(a,b);
	pogrewnost2 = W2 - g(a,b);
	pogrewnost3 = W3 - g(a,b);
	
	printf("epsilon(1-3):");	
	printf("\n1)%lg\n2)%lg\n3)%lg\n", eps1, eps2, eps3);
	printf("integral           \t%lg\t%lg\t%lg\n", W1, W2, W3);
	printf("\npoqrewnost1=%lg\n", pogrewnost1);
	printf("poqrewnost2=%lg\n", pogrewnost2);
	printf("poqrewnost3=%lg\n\n", pogrewnost3);
	printf("summa delt         \t%lg\t%lg\t%lg\n", sumd1, sumd2, sumd3);
	printf("summa delt po modulu\t%lg\t%lg\t%lg\n", sumdabs1, sumdabs2, sumdabs3);
	printf("\nSvewennoye cislo                  \t%lg\n", (W1-W2)/(W2-W3));
	printf("Svewennoye cislo dlya delt         \t%lg    \t%lg\n", sumd1/sumd2, sumd2/sumd3);
	printf("Svewennoye cislo dlya delt po modulu\t%lg    \t%lg\n", sumdabs1/sumdabs2, sumdabs2/sumdabs3);
	
	
	
	return 0;
      }
	
double integral(double h, double x, double eps, double b, double *sumd, double *sumdabs, int *i) {
	double dt, H, I1, I2, h_new;
	double sum = 0;
	(*i)=0;                                                                                                                                                         
	while(x<b-eps) {
		I1=(h/6)*(f(x)+4*f(x+h/2)+f(x+h));
		I2=(h/12)*(f(x)+4*f(x+h/4)+2*f(x+h/2)+4*f(x+(3*h)/4)+f(x+h));
		dt = (I2 - I1)/15;
		H =  pow(fabs(dt)/eps, 0.2);
		
		if(H>10) H=10;
		if(H<0.1) H=0.1;
		h_new = 0.95*h/H;
		
		if(fabs(dt)<eps) { 
			x+=h;
			sum+=I2;
			(*sumd)+=dt;
			(*sumdabs)+=fabs(dt);
			(*i)++;
		}
			
		h=h_new; 
		if(x+h>b) {h=b-x;}
	}
	
	return sum;
}
