#include <stdio.h>
#include <stdlib.h>

int maxima(int , int);

int main(void) {
	int n, i, tmin, lft, rht, f, min, w, sum, a;
	scanf("%d", &n);
	int s[n], d[n];
	for(i = 0; i < n; i++) scanf("%d", &s[i]);
	for(i = 0; i < n; i++) scanf("%d", &d[i]);
	lft = 0; rht = n - 1;
	while(lft < rht) {
		tmin = s[lft];
		f = 0;
		min = lft;
		for(i = lft; i <= rht; i++) {
			if(s[i] < tmin) {
				tmin = s[i];
				min = i;
				f = 0;
			}
			if(d[i] < tmin) {
				tmin = d[i];
				min = i;
				f = 1;
			}
		}
		if(!f) {
			w = s[lft];
			s[lft] = s[min];
			s[min] = w;
			w = d[lft];
			d[lft] = d[min];
			d[min] = w;
			lft++;
		}
		else {
			w = s[rht];
			s[rht] = s[min];
			s[min] = w;
			w = d[rht];
			d[rht] = d[min];
			d[min] = w;
			rht--;
		}
	}
	for(a = sum = i = 0; i < n; i++) {
		a += s[i];
		sum = maxima(a,sum) + d[i];
	}
	printf("%d\n", sum);
	return 0;
}

int maxima(int a, int sum) {
	return a > sum ? a : sum;
}
