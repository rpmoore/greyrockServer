#ifndef NET__SOCK__H__
#define NET__SOCK__H__

typedef int net_socket;

class netSock {
  public:
  static net_socket getTcpServerSocket(const char* port, int backLog);
  static net_socket getTcpClientSocket(const char* address, const char* port);
};
#endif
