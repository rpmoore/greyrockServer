#include <stdlib.h>
#include <string.h>
#include "httpEngine.h"

void gr_http_start(gr_request *new_request, net_socket socket){
  //clear out the request struct
  memset(new_request,0,sizeof(gr_request));
  
}

void gr_http_error(gr_request *request, int http_error)
{


}
