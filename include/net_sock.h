#ifndef NET__SOCK__H__
#define NET__SOCK__H__

typedef int net_sock;
net_sock getTcpServerSocket(int port, int backLog);
net_sock getTcpClientSocket(int port);

#endif
