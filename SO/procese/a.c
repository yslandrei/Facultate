#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  mkfifo("./a2b", 0666);
  int a2b = open("./a2b", O_WRONLY);
  int b2a = open("./b2a", O_RDONLY);

  int st = 0, dr = 10000;
  while(st <= dr) {
    int mij = (st + dr) / 2;
    printf("[a]: Am ghicit %d\n", mij);
    write(a2b, &mij, sizeof(int));
    char res;
    read(b2a, &res, sizeof(char));
    if(res == '>')
      dr = mij - 1;
    else if(res == '<')
      st = mij + 1;
    else
      break;
  }
  
  close(a2b);
  close(b2a);
  unlink("./a2b");
}
