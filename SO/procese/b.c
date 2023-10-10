#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  mkfifo("./b2a", 0666);
  int a2b = open("./a2b", O_RDONLY);
  int b2a = open("./b2a", O_WRONLY);
  
  char mic = '<', mare = '>', egal = '=';
  int nr = rand() % 10000;
  while(1) {
    int guess;
    read(a2b, &guess, sizeof(int));
    if(guess > nr) {
      write(b2a, &mare, sizeof(char));
      printf("[b]: >\n");
    }
    else if(guess < nr) {
      write(b2a, &mic, sizeof(char));
      printf("[b]: <\n");
    }
    else if(guess == nr) {
      write(b2a, &egal, sizeof(char));
      printf("[b]: Corect\n");
      break;
    }
  }

  close(a2b);
  close(b2a);
  unlink("./b2a");
  return 0;
}
