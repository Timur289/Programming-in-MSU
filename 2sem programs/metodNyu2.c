#include <stdio.h>
#include <math.h>
#define eps 1.e-12
int n=0;
double f(double x){
    return sin(x);
}
double df(double x){
    return cos(x);
}
double root(double x){
    double y;
    do{
       n++;
       printf("[%d]\n", n);
       y = x;
       x = - f(x) / df(x) + x;
    }while(fabs(x-y)>eps && fabs(x-y)>eps*fabs(y));
    return x;
}
int main(void){
    double x;
    scanf("%le", &x);
    double r = root(x);
    printf("%lf\tf(x) = %le\n", r, f(r));
    return 0;
}


