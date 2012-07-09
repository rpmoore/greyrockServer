#include <stdlib.h>
#include <string.h>
#include "httpEngine.h"


bool gr_http_createURI(gr_uri *uri_struct, char *uri, size_t length){
  int index = 0,startIndex,endIndex;
  //clear out the uri struct
  memset(uri_struct,0,sizeof(gr_uri));
  //start reading the characters from the input stream.
  //find the first non whitespace charachter.
  while(index < length && isspace(uri[index])){++index;}
  startIndex = index; // need this to copy the full url at the end.
  


}

void gr_http_start(gr_request *new_request, net_socket socket){
  //clear out the request struct
  memset(new_request,0,sizeof(gr_request));
  
}


void gr_http_error(gr_request *request, int http_error)
{


}
