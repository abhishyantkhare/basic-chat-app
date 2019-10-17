#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int HTTP_PORT = 80;

int main(int argc, char *argv[])
{
  int sockfd, newsockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    perror("Error opening server socket");
    exit(-1);
  }
  char buffer[256] = {0};
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(HTTP_PORT);
  if (bind(sockfd, (const sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("Error binding socket");
    exit(-1);
  }

  if (listen(sockfd, 3) < 0)
  {
    perror("Error listening server socket");
    exit(-1);
  }

  newsockfd = accept(sockfd, (sockaddr *)&address, (socklen_t *)&address);
  if (newsockfd < 0)
  {
    perror("Error accepting connection");
    exit(-1);
  }

  int read_result = read(newsockfd, buffer, 256);
  if (read_result < 0)
  {
    perror("Error reading from socket");
    exit(-1);
  }

  printf("%s", buffer);

  // Error check socket

  return 0;
}