#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int HTTP_PORT = 80;

int main(int argc, char *argv[])
{
  int clientfd;
  clientfd = socket(AF_INET, SOCK_STREAM, 0);
  if (clientfd < 0)
  {
    perror("Error opening client socket");
    exit(-1);
  }
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(HTTP_PORT);
  inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

  int connectRes = connect(clientfd, (struct sockaddr *)&address, sizeof(address));
  if (connectRes < 0)
  {
    perror("Error connecting to server");
    exit(-1);
  }
  char buffer[256] = {0};
  while (true)
  {
    fgets(buffer, 256, stdin);
    send(clientfd, buffer, strlen(buffer), 0);
  }
}
