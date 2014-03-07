#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int ac, char* av[]) {
  int socket_handle;
  struct sockaddr_in socket_details; 
  // arpa/inet.h
  // 시스템 마다 다르고, 프로토콜마다 다르다.
  // 크기가 변할 수 있기 때문에 진짜 크기를 알아야한다.

  char* input_buffer;
  char httpget[] = "GET / HTTP/1.1\r\n\r\n";

  input_buffer = malloc (20000);

  socket_handle = socket (AF_INET, SOCK_STREAM, 0);
  socket_details.sin_family = AF_INET;
  socket_details.sin_addr.s_addr = inet_addr ("54.199.134.112");
  socket_details.sin_port = htons(80);

  connect (socket_handle,(struct sockaddr*)&socket_details, sizeof ( struct sockaddr));
  send (socket_handle , httpget, strlen(httpget), 0 );
  recv (socket_handle , input_buffer , 20000, 0 );
  printf ("%s\n", input_buffer );

  return 0 ;
}
