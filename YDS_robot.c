#include <stdio.h>

int main(void) {

  long N, i, j, dir = 0, step = 1, x = 0, y = 0;

  scanf("%ld", &N);

  for(i = 0; i < N;) {
    if(dir == 0) {
      // LEFT
      if((N-i) > step) { x-=step; i+=step; }
      else { x-=(N-i); break; }
    }else if(dir == 1) {
      // DOWN
      if((N-i) > step) { y-=step; i+=step; }
      else { y-=(N-i); break; }
      step++;
    }else if(dir == 2) {
      // RIGHT
      if((N-i) > step) { x+=step; i+=step; }
      else { x+=(N-i); break; }
    }else if(dir == 3) {
      // UP
      if((N-i) > step) { y+=step; i+=step; }
      else { y+=(N-i); break; }
      step++;
    }
    dir = (dir+1)%4;
  }

  printf("%ld %ld\n", x, y);

  return 0;
}
