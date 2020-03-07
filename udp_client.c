#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void main(int argc, char **argv) {
  if (argc != 3) {
    printf("Usage: %s <ipaddress> <port>\n", argv[0]);
    exit(0);
  }
  int port = atoi(argv[2]);
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&server_addr, '\0', sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  strcpy(buffer, "Hello Server\n");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
  printf("[+]Data Send: %s", buffer);
}
