#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IP_ADDR "127.0.0.1"

void main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <port>\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);
  int udp_socket;
  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = inet_addr(IP_ADDR);

  bind(udp_socket, (struct sockaddr*)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);

  while (1) {
    recvfrom(udp_socket, buffer, 1024, 0, (struct sockaddr*)&si_other, &addr_size);
    printf("[+]Data Received: %s", buffer);
  }
}
