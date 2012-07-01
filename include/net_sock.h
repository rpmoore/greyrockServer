#ifndef NET__SOCK__H__
#define NET__SOCK__H__

typedef int net_sock;
net_sock getTcpServerSocket(const char* port, int backLog);
net_sock getTcpClientSocket(const char* address, const char* port);

#endif
