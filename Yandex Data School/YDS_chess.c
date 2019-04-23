#include <stdio.h>
#include <stdlib.h>

void bishop(int n, int _x, int _y, int **B) {
  int i, x, y;

  x = _x;
  y = _y;
  while((x+1 < n) && (y+1 < n)) B[++x][++y] = 1;

  x = _x;
  y = _y;
  while((x-1 >= 0) && (y+1 < n)) B[--x][++y] = 1;

  x = _x;
  y = _y;
  while((x+1 < n) && (y-1 >= 0)) B[++x][--y] = 1;

  x = _x;
  y = _y;
  while((x-1 >= 0) && (y-1 >= 0)) B[--x][--y] = 1;
}

int main(void) {

  int n, m, i, j, ans, **B = NULL, *x = NULL, *y = NULL;

  scanf("%d%d", &n, &m);

  x = (int*)malloc(m * sizeof(int));
  y = (int*)malloc(m * sizeof(int));
  B = (int**)calloc(n, sizeof(int*));
  for(i = 0; i < n; i++) B[i] = (int*)calloc(n, sizeof(int));

  for(i = 0; i < m; i++) {
    scanf("%d%d", &x[i], &y[i]);
    x[i]-=1;
    y[i]-=1;
    B[x[i]][y[i]] = 1;
    bishop(n, x[i], y[i], B);
  }

  ans = 0;

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      if(B[i][j]) ans++;

  ans = n*n - ans;

  printf("%d\n", ans);

  return 0;
}
