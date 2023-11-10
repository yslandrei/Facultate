#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h> 
 
int main() {
  int c;
  struct sockaddr_in server;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(8889);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.30.5.25");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  uint16_t id = 3325;
  uint16_t strLen;
  char str[1000];
  id = htons(id);
  send(c, &id, sizeof(id), 0);
  recv(c, &strLen, sizeof(char) * (sizeof(strLen) + 10), 0);
  strLen = ntohs(strLen);
  recv(c, str, strLen, 0);

  for (int i = 0; i < strLen + 30; i ++) {
    printf("%c", str[i]);
  }

  // char ch;
  // uint32_t count = -1;
  // do {
  //   count ++;
  //   recv(c, &ch, sizeof(ch), 0);
  // } while (ch != NULL);
  // send(c, &count, sizeof(count), 0);
  // // printf("\nCount: %d", count);

  // uint16_t a, b, sum;
  // recv(c, &a, sizeof(a), 0);
  // recv(c, &b, sizeof(b), 0);
  // printf("a = %d\nb= %d\n", a, b);
  // sum = a + b;
  // send(c, &sum, sizeof(sum), 0);

  // uint16_t port;
  // recv(c, &port, sizeof(port), 0);
  // port = ntohs(port);
  // printf("Port: %d\n", port);
  // int c_udp;
  // struct sockaddr_in server_udp;
  
  // c_udp = socket(AF_INET, SOCK_DGRAM, 0);
  // if (c_udp < 0) {
  //   printf("Eroare la crearea socketului client\n");
  //   return 1;
  // }
  // memset(&server_udp, 0, sizeof(server_udp));
  // server_udp.sin_port = htons(port);
  // server_udp.sin_family = AF_INET;
  // server_udp.sin_addr.s_addr = inet_addr("172.30.5.25");

  // uint16_t portCopy = port;
  // uint16_t oglindit = 0;
  // while (portCopy) {
  //   oglindit = oglindit * 10 + portCopy % 10;
  //   portCopy /= 10;
  // }
  // printf("Oglindit: %d", oglindit);
  // oglindit = htons(oglindit);
  // sendto(c_udp, &oglindit, sizeof(oglindit), 0, (struct sockaddr *) &server_udp, sizeof(server_udp));
  // close(c_udp);

  close(c);
}