#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 80
#define QUEUELIMIT 5

int
main(int argc, char* argv[])
{
  int server_sock;
  int client_sock;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  unsigned int server_len = sizeof(server_addr);
  unsigned int client_len = sizeof(client_addr);

  if ((server_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("socket() failed");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, server_len);
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  if (bind(server_sock, (struct sockaddr*)&server_addr, server_len) < 0) {
    perror("bind() failed");
    exit(EXIT_FAILURE);
  }

  if (listen(server_sock, QUEUELIMIT) < 0) {
    perror("bind() failed");
    exit(EXIT_FAILURE);
  }

  while (1) {
    if ((client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len)) < 0) {
      perror("accept() failed");
      exit(EXIT_FAILURE);
    }
    printf("connected from %s.\n", inet_ntoa(client_addr.sin_addr));
    write(client_sock, "Hello world", 11);
    close(client_sock);
  }

  close(server_sock);
  return EXIT_SUCCESS;
}
