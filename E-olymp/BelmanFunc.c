#include <stdio.h>
#include <stdlib.h>

int maxima(int *, int , int );

int main(void){
	int *a, *b, n, shag, i;
	scanf("%d", &n);
	n = n + 2;
	a = (int *)malloc(n*sizeof(int));
	b = (int *)malloc(n*sizeof(int));
	a[0] = 0; a[n-1] = 0;
	for(i = 1; i < n-1; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &shag);
	for(i = 0; i < n; i++) b[i] = 0;
	for(i = 1; i < n; i++){
		b[i] = maxima(b, shag, i) + a[i];
	}
	printf("%d", b[n-1]);
	return 0;
}

int maxima(int *b, int shag, int k){
	int i;
	int max = b[k-1];
	for(i = 1; i < shag && i < k; i++){
		if(max < b[k-i-1]) max = b[k-i-1];
	}
	return max;
}
