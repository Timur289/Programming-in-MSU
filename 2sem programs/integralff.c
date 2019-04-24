#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double t)
{
    return (cos(t)+1)/sqrt(t);
}

void integral(double *eps, double *alpha)
{
    double s=0, ds=0, sumerr=0, sumerrabs=0, nsteps=0, err, errabs,  xi, h_new, h=0.5, x;
	x=0;
	while(s<(*alpha-*eps))
	{
		if (!x) x+=h;
        ds=((f(x)+2*f(x+(h/2))+f(x+h))*h)/4.0;
        err=((f(x)-2*f(x+(h/2))+f(x+h))*h)/12.0;
        errabs=fabs(err);
        xi=errabs/(*eps);
        if(xi>1.e3) xi=1.e3;
        if(xi<1.e-3) xi=1.e-3;
        xi=pow(xi, 1.0/3.0); 
        h_new=0.95*h/xi;
        if(errabs<(*eps)){
            if((s+ds)<(*alpha+*eps)){
                s+=ds;
                x+=h;
                sumerr+=err;
                sumerrabs+=errabs;
                nsteps++;
            }
            else{
                h_new=h*(*alpha-s)/ds;
            }
        }
		h=h_new;
    }
    printf("\nresults:\n> x = %.14lf\n", x);
    printf("> s = %lf\n", s);
    printf("> nsteps = %lf\n", nsteps);
    printf("> sumerr = %le\n", sumerr);
    printf("> sumerrabs = %le\n", sumerrabs);
}

int main(void)
{
	double eps, alpha;
	printf("Enter your epsilon:\n> eps = ");
	scanf("%lf", &eps);
	printf("Enter your alpha:\n> alpha = ");
	scanf("%lf", &alpha);
	integral(&eps, &alpha);
	return 0;
}
