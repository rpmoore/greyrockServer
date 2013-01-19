#include <stdio.h>
#include <stdlib.h> //exit
#include <string.h> //memset
#include <stdbool.h> //true false
#include <sys/socket.h> //socket
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h> //close
#include <errno.h> //perror, gai_strerror
#include <arpa/inet.h>

#include "net_sock.h"
#include "version.h"

//private functions
void
grs_copy_element_to_struct(void **struct_entry,const void *data, uint32_t element_size);

net_socket
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

net_socket
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
  freeaddrinfo(servinfo);
  return sockfd;
}

bool
gr_netSock_createURI(gr_uri *uri_struct, const char *uri, const size_t length){
  uint32_t index = 0,start_index,end_index,hostname_size,file_size;
  
  //clear out the uri struct
  memset((void *)uri_struct,0,sizeof(gr_uri));
  
  //start reading the characters from the input stream.
  //find the first non whitespace charachter.
  while(index < length && isspace(uri[index])){++index;}
  start_index = index; // need this to copy the full url at the end.

  //gethostname
  while(index < length && uri[index] != ':' && uri[index] != '/' && !isspace(uri[index])){++index;};
  end_index = index;
  hostname_size = end_index - start_index;
  //only add the hostname if there is one.  This allows for absolute paths.
  if(hostname_size != 0){
    grs_copy_element_to_struct((void **)&uri_struct->hostname,(const void *)uri+start_index,hostname_size); 
  }
  if(index == length)
  {
    return true;
  }
  
  start_index = end_index;
  while(index < length && uri[index] != '?'){++index;};
  end_index = index;
  
  file_size = end_index - start_index;
  grs_copy_element_to_struct((void **)&uri_struct->file,(const void *)uri+start_index,file_size); 

  return true;
}

void
grs_copy_element_to_struct(void **struct_entry,const void *data, uint32_t element_size)
{
  *struct_entry = (char *) calloc(element_size,sizeof(char));
  strncpy(*struct_entry, data, element_size);
}

