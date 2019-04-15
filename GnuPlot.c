#include <stdio.h>
#include <math.h>
int main(void)
{
int i,j;
double x[]={0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,2.5,M_PI},
y[]={0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,2.5,M_PI};
FILE *fout=NULL;
fout=fopen("data2.txt","w");
for(i=0;i<11;i++) {
for(j=0;j<11;j++)
fprintf(fout,"%lg %lg %lg\n",x[i],y[j],cos(x[i])*cos(y[j]) );
fprintf(fout," \n");
}
return 0;
}
