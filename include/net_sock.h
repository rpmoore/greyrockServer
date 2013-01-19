#ifndef NET__SOCK__H__
#define NET__SOCK__H__

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int net_socket;

typedef struct __http__uri {
  char *uri_str;
  int port;
  char *hostname;
  char *protocol;
  char *user;
  char *file;
} gr_uri;

net_socket getTcpServerSocket(const char* port, int backLog);
net_socket getTcpClientSocket(const char* address, const char* port);

/**
  @brief Parse the string in uri into the structure uri_struct.
  This will read from the char string until it finds the first non whitespace
  character sequence.  It will then parse that sequence until it hits the end
  of the buffer or the next whitespace character.  This parses a RFC 3986
  uri.
  @param uri_struct The new gr_uri to fill out.
  @param uri The uri string to parse.
  @param uriLength The length of the uri character buffer.
  @return true is returned if the uri is valid, othewise false is returned.
*/
bool gr_netSock_createURI(gr_uri *uri_struct, const char *uri, const size_t length);

#ifdef __cplusplus
}
#endif
#endif
