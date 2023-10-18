#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int a2b[2], b2c[2], c2p[2];  
  pipe(a2b);
  if(fork() == 0) {
    close(a2b[0]);
    for(int i = 1; i < argc; i ++) {
      int x = 0;
      for(int j = 0; j < strlen(argv[i]); j ++)
        x = x * 10 + (int)(argv[i][j] - '0');
      int isPrime = 1;
      if(x < 2)
        isPrime = 0;
      else {
        for(int d = 2; d * d <= x; d++)
          if(x % d == 0) {
            isPrime = 0;
            break;
          }
      }
      if(isPrime == 1)
        write(a2b[1], &x, sizeof(int));
    }
    int final = 0; // trimit 0 ca b sa stie finalul
    write(a2b[1], &final, sizeof(int));
    close(a2b[1]);
    exit(EXIT_SUCCESS);
  }
  close(a2b[1]);
  
  pipe(b2c);
  if(fork() == 0) {
    close(b2c[0]);
    int maxx = -1;
    while(1) {
      int x;
      read(a2b[0], &x, sizeof(int));
      //printf("[b]: Read %d", x);
      if(x == 0)
        break;
      if(x > maxx)
        maxx = x;
    }
    close(a2b[0]);
    write(b2c[1], &maxx, sizeof(int));
    close(b2c[1]);
    exit(EXIT_SUCCESS);
  }
  close(a2b[0]);
  close(b2c[1]);

  pipe(c2p);
  if(fork() == 0) {
    close(c2p[0]);
    int x;
    read(b2c[0], &x, sizeof(int));
    close(b2c[0]);
    int sum = 0;
    while(x > 0) {
      sum = sum + x % 10;
      x /= 10;
    }
    write(c2p[1], &sum, sizeof(int));
    close(c2p[1]);
    exit(EXIT_SUCCESS);
  }
  close(b2c[0]);
  close(c2p[1]);
  
  int x;
  read(c2p[0], &x, sizeof(int));
  close(c2p[0]);
  printf("Suma cifrelor celui mare numar prim este: %d\n", x);
  return 0;
}
