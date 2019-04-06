#include <stdio.h>
#include <math.h>
#define eps 1.e-9
double znak(double x){
	if(x>0) return 1;
	else if(x<0) return -1;
	else return 0;
}
double koren(double a, double b, double (*f)(double)){
	double fa,fb,zfa,zfb;
	fa=f(a); fb=f(b);
	zfa=znak(fa); zfb=znak(fb);
	if(zfa==0){ 
		printf("%le", a);
		return 0;
	}
	else if(zfb==0){
		printf("%le", a);
		return 0;
	}
	else if(zfa==zfb){
		printf("Metod ne primenim");
		return 0;
	}
	double x,fx,zfx;
	while((fabs(b-a)>eps) && (fabs(b-a)>eps*fabs(a))){
		x= a -(b - a) * fa / (fb - fa);
		fx=f(x);
		zfx=znak(fx);
		printf("%lf\n", x);
		if(zfa==zfx){
			a=x; fa=fx;
		}
		else if(zfb==zfx){
			b=x; fb=fx;
		}
		else{
			break;
		}
	}
	return x;
}
int main(void){
	double a,b;
	scanf("%le%le", &a,&b);
	printf("%le", koren(a,b,sin));
	return 0;
}
