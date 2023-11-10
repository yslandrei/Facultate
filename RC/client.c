#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h> 
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int c;
  struct sockaddr_in server;
  
  uint16_t lenPosList, posList[100], lenString;
  uint8_t ch, string[100];

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(53325);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.30.0.4");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("character = ");
  scanf("%c", &ch);
  printf("string = ");    printf("%hu \n", posList[i]);
  scanf("%s", string);

  lenString = htons(strlen(string));
  
  send(c, &ch, sizeof(ch), 0);
  send(c, &lenString, sizeof(lenString), 0);
  send(c, string, sizeof(string) * strlen(string), 0);
  
  recv(c, &lenPosList, sizeof(lenPosList), MSG_WAITALL);
  lenPosList = ntohs(lenPosList);
  printf("Lungime: %hu\n", lenPosList);
  recv(c, posList, sizeof(uint16_t) * lenPosList, MSG_WAITALL);

  printf("Aparitile sunt: ");
  for (int i = 0; i < lenPosList; i ++) { 
    printf("%hu \n", posList[i]);
    posList[i] = ntohs(posList[i]);
    printf("%hu \n", posList[i]);
  }

  close(c);
}
