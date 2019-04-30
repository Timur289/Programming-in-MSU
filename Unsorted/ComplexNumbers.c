#include <stdio.h>
#include <complex.h>
  int main(void)
    {
        double complex z = 1.0 + 2.0*I;
        printf("%ld%+%ldi\n", creal(z), cimag(z));
    }
