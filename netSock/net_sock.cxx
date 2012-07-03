#include <stdio.h>
#include <stdlib.h> //exit
#include <string.h> //memset
#include <sys/socket.h> //socket
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h> //close
#include <errno.h> //perror, gai_strerror
#include <arpa/inet.h>

#include "net_sock.h"
#include "version.h"

net_sock
getTcpServerSocket(const char* port, int backLog){
  struct addrinfo hints,*servinfo,*p;
  int rv,sockfd;
  int yes = 1;
  //set up the hints for the socket.
  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if((rv = getaddrinfo(NULL,port,&hints,&servinfo)) != 0){
    fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(rv));
  
    return -1;
  }

  for(p = servinfo;p!= NULL;p = p->ai_next){
    if((sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1){
      perror("server: socket");
      continue;
    }

    if(setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR,&yes,sizeof(int)) == -1){
      perror("server: setsockopt");
      exit(1);
    }

    if(bind(sockfd,p->ai_addr,p->ai_addrlen) == -1) {
      close(sockfd);
      perror("server: bind");
      continue;
    }
    break;
  }
  freeaddrinfo(servinfo);

  if(listen(sockfd,backLog) == -1) {
    perror("server: listen");
    exit(1);
  }
    
  return sockfd;
}

net_sock
getTcpClientSocket(const char* address,const char* port){
  struct addrinfo hints,*servinfo,*p;
  int rv,sockfd;
  memset(&hints, 0,sizeof(struct addrinfo));
  
  if((rv = getaddrinfo(address,port,&hints,&servinfo))!= 0){
    fprintf(stderr,"getaddrInfo: %s\n",gai_strerror(rv));
    return -1;
  }

  for(p = servinfo; p != NULL;p = p->ai_next) {
    if((sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1) {
      perror("client: socket");
      continue;
    }
 
    if(connect(sockfd,p->ai_addr,p->ai_addrlen) == -1) {
      close(sockfd);
      perror("client: connect");
      continue;
    }
    break;
  }

  return sockfd;
}
