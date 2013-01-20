#ifndef NET__SOCK__H__
#define NET__SOCK__H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int net_socket;

typedef struct __http__url {
  char *url_str;
  char *hostname;
  char *protocol;
  char *user;
  char *file;
  uint16_t port;
} gr_url;

net_socket gr_tcp_server_socket(const char* port, int backLog);
net_socket gr_tcp_client_socket(const char* address, const char* port);

/**
  @brief Parse the string in url into the structure url_struct.
  This will read from the char string until it finds the first non whitespace
  character sequence.  It will then parse that sequence until it hits the end
  of the buffer or the next whitespace character.  This parses a subset of 
  RFC 3986, specifically RFC 1738.
  @param url_struct The new gr_url to fill out.
  @param url The url string to parse.
  @param urlLength The length of the url character buffer.
  @return true is returned if the url is valid, othewise false is returned.
*/
bool gr_netsock_create_url(gr_url *url_struct, const char *url, const size_t length);

#ifdef __cplusplus
}
#endif
#endif
