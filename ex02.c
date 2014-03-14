#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char**argv)
{

  // workflow should be...
  // 1. generate socket
  // 2. bind
  // 3. listen(passive) from client request(connect function)
  // 4. accept

  int listenfd,connfd,n;
  //fd stands for file descriptor. starting from 3...
  struct sockaddr_in servaddr,cliaddr;
  socklen_t clilen;
  char mesg[4096];
  char output[] = "HTTP/1.0 200 OK\r\nDate: Wed, 12 Mar 2014 00:14:10 GMT\r\n\r\n<html><h1>Hello!</h1></html>\r\n";

  listenfd=socket(AF_INET,SOCK_STREAM,0);
  // generate passive socket (= server socket)
  // listenfd is a indicator for socket(3)

  memset(&servaddr,0,sizeof(servaddr)); //init servaddr
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(32000);
  // htons stands for "host to network short"
  // why? network byte order is Big-Endian

  bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

  listen(listenfd,1024);

  for(int i = 0 ; i < 100 ;i++) {
    clilen=sizeof(cliaddr);
    connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
    printf("connected (%d)\n", connfd);

    if (connfd > 0) {
      n = recv(connfd,mesg,4096,0);
      mesg[n] = 0;
      printf("=====\n%s=====\n", mesg);
      send(connfd,output,strlen(output),0); // what is this for...?
      close(connfd);
    }
  }
}
