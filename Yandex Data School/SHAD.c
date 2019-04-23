#include <stdio.h>
int main(void) {
  FILE *f;
  int i, j;
  long n, k = 0, x, y, c = 0, p;
  f = fopen("input.txt", "w");
  for(p = 1; p < 10000000000; p++) {
    fprintf(f, "%ld ", p);
  }

  f = fopen("input.txt", "r");
  while(scanf("%ld", &n) == 1)
  for(i = 1; k < n; i++) {
    k = 8 * i + 4 * i * (i-1);
    c++;
  }
  if(c == 0) {
    printf("%ld %ld", c, c);
    return 0;
  }
  k -= n;
  k = c*8 - k;
  i = (k - 1) / (c * 2);
  if(i == 0) {
    y = c - 1;
    for(j = 0; j < k-1; j++) y--;
    x = (-1) * c;
    printf("%ld %ld\n", x, y);
  }
  else if(i == 1){
    k -= c * 2;
    x = (-1) * c + 1;
    y = (-1) * c;
    for(j = 0; j < k - 1; j++) x++;
    printf("%ld %ld\n", x ,y);
  }
  else if(i == 2) {
    y = (-1) * c + 1;
    k -= 4 * c;
    for(j = 0; j < k - 1; j++) y++;
    x = c;
    printf("%ld %ld\n", x, y);
  }
  else if(i == 3){
    x = c - 1;
    k -= 6 * c;
    for(j = 0; j < k - 1; j++) x--;
    y = c;
    printf("%ld %ld\n", x, y);
  }
  return 0;
}
