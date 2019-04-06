#include <stdio.h>
#include <math.h>
#define eps 1.e-10
double z(double x){
    if(x>0) return 1;
    else if(x<0) return -1;
    else return 0;
}
double f(double x){
    return exp(x)-exp(M_PI);
}
double roots(double a, double b, double (*f)(double)){
    double c,fa,fb,fc,zfa,zfb,zfc;
    int n=0;
    fa=f(a); fb=f(b); zfa=z(fa); zfb=z(fb);
    if(zfa*zfb>0){
		printf("Metod ne primenim");
		return -1;
	}
    else if(zfa*zfb<0){
        do{
            n++;
            printf("[%d]\n", n);
            if(fabs(fa)<eps) {
                return a;
            }
            if(fabs(fb)<eps) {
                return b;
            }
            zfa=z(fa); zfb=z(fb);
            c = a -(b - a) * fa / (fb - fa);
            fc=f(c); zfc=z(fc);
            printf("%lf\n", c);
            if(zfc*zfa<0){
                b=c; fb=fc;
            }
            else if(zfc*zfb<0){
                a=c; fa=fc;
            }
            else return c;
        }while(fabs(b-a) > eps && fabs(b-a)>eps*fabs(a));
	}
	return c;
}
int main(void){
    double a,b;
    scanf("%le%le", &a,&b);
    if(roots(a,b,f)!=-1)
    printf("%lf\t", roots(a,b,f));
    return 0;
}

