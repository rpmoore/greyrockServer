#ifndef __HTTP__ENGINE__HEADER__
#define __HTTP__ENGINE__HEADER__

#include <stdint.h>
#include "net_sock.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __http__version {
  uint8_t major;
  uint8_t minor;

} gr_request_version;

typedef enum __http__method { 
  POST,GET,PUT,DELETE,HEAD,OPTIONS,TRACE,CONNECT
} gr_method;

typedef struct __http__request {
  gr_request_version version;
  gr_method method;
  gr_url url;
  net_socket soc;
  
} gr_request;


/**
  @brief Start the http connection.
  @param new_request A newly allocated gr_request.
  @param net_socket The socket descriptor that the request came in on.
*/
void gr_http_start(gr_request *new_request, net_socket socket);

/**
  @brief Sends an error back to the client with the specified error.
  @param request The initial request from the client.
  @param http_error The http error code to return to the client.
*/
void gr_http_error(gr_request *request, int http_error);
#ifdef __cplusplus
}
#endif
#endif //__HTTP__ENGINE__HEADER__
