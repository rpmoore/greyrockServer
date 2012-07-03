#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "net_sock.h"


/**
 @brief Test that we can create sockets and accept a connection
*/
BOOST_AUTO_TEST_CASE( create_sockets_test)
{
  net_socket serverSocket = netSock::getTcpServerSocket("9999", 10);
  net_socket clientSocket = netSock::getTcpClientSocket("localhost", "9999");

  BOOST_CHECK_GT(accept(serverSocket,NULL,0),0);

  close(serverSocket);
  close(clientSocket);
}

/**
Test that we can send data on the client socket first.
*/
BOOST_AUTO_TEST_CASE( send_sockets_test)
{
  net_socket serverSocket = netSock::getTcpServerSocket("9999", 10);
  net_socket clientSocket = netSock::getTcpClientSocket("localhost", "9999");

  net_socket newSocket;
  BOOST_CHECK_GT(newSocket = accept(serverSocket,NULL,0),0);

  char * outBuf = "BEAD-Test";
  char * inBuf = (char *)calloc(strlen(outBuf)+1,sizeof(char));
  BOOST_CHECK_EQUAL(write(clientSocket,outBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(read(newSocket,inBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(strcmp(outBuf,inBuf),0);
  
  free(inBuf);
  close(serverSocket);
  close(clientSocket);
}
