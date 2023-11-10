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
  
  uint16_t lenPosList, posList[105];
  uint8_t ch;
  uint16_t lenString;
  uint8_t string[105];

  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(53325);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.30.0.4");
  
  printf("character = ");
  scanf("%c", &ch);
  printf("string = ");
  scanf("%s", string);

  lenString = htons(strlen(string));
  
  //send(c, &ch, sizeof(ch), 0);
  //send(c, &lenString, sizeof(lenString), 0);
  //send(c, string, sizeof(string) * strlen(string), 0);

  sendto(c, &ch, sizeof(ch) + sizeof(lenString) + sizeof(string) * strlen(string), 0, (struct sockaddr *) &server, sizeof(server));
  //sendto(c, &lenString, sizeof(lenString), 0, (struct sockaddr *) &server, sizeof(server));
  //sendto(c, string, sizeof(string) * strlen(string), 0, (struct sockaddr *) &server, sizeof(server));

  int l = sizeof(server);

  recvfrom(c, &lenPosList, sizeof(lenPosList) + 2 * 100, MSG_WAITALL, (struct sockaddr *) &server, &l);
  lenPosList = ntohs(lenPosList);
  printf("Lungime: %hu\n", lenPosList);
  //recvfrom(c, posList, sizeof(uint16_t) * lenPosList, MSG_WAITALL, (struct sockaddr *) &server, &l);
  
  printf("Aparitile sunt: ");
  for (int i = 0; i < lenPosList; i ++) { 
    posList[i] = ntohs(posList[i]);
    printf("%hu \n", posList[i]);
  }

  close(c);
}
