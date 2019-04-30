#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int maxima(int ,int);

int main(void){
  int **a, n, m, i, j, way_sum;
  char *way;
  scanf("%d%d", &m, &n);
  way_sum = m + n - 2;
  way = (char *)malloc((way_sum) * sizeof(char));
  a = (int **)malloc(m * sizeof(int*));
  for(i = 0; i < m; i++) a[i] = (int *)malloc(n * sizeof(int));
  for(i = m-1; i >= 0; i--) {
    for(j = 0; j < n; j++)	scanf("%d", &a[i][j]);
  }
  
  for(i = 1; i < m; i++) a[i][0] += a[i-1][0];
  for(i = 1; i < n; i++) a[0][i] += a[0][i-1];

  for(i = 1; i < m; i++) {
    for(j = 1; j < n; j++) a[i][j] += maxima(a[i-1][j],a[i][j-1]);
  }

  i = m - 1; j = n - 1;
  while(way_sum > 0) {
    if(j != 0 && i != 0){
      if(a[i-1][j] < a[i][j-1]) {way[way_sum-1] = 'R';  j--;}
      else  {way[way_sum-1] = 'F'; i--;}
    }
    else {
      if(j == 0)  way[way_sum-1] = 'F';
      else if(i == 0) way[way_sum-1] = 'R';
    }
    way_sum--;
  }
  for(i = 0; i < m+n-2; i++) printf("%c",way[i]);
  return 0;
}

int maxima(int a, int b) {
  return a < b ? b : a;
}
