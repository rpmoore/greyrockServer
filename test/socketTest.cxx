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
BOOST_AUTO_TEST_CASE( send_from_client_sockets_test)
{
  net_socket serverSocket = netSock::getTcpServerSocket("9999", 10);
  net_socket clientSocket = netSock::getTcpClientSocket("localhost", "9999");

  net_socket newSocket;
  BOOST_CHECK_GT(newSocket = accept(serverSocket,NULL,0),0);

  const char * outBuf = "BEAD-Test";
  char * inBuf = (char *)calloc(strlen(outBuf)+1,sizeof(char));
  BOOST_CHECK_EQUAL(write(clientSocket,outBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(read(newSocket,inBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(strcmp(outBuf,inBuf),0);
  
  free(inBuf);
  close(serverSocket);
  close(clientSocket);
}

/**
Test that we can send data from the server socket first.
*/
BOOST_AUTO_TEST_CASE( send_from_server_sockets_test)
{
  net_socket serverSocket = netSock::getTcpServerSocket("9999", 10);
  net_socket clientSocket = netSock::getTcpClientSocket("localhost", "9999");

  net_socket newSocket;
  BOOST_CHECK_GT(newSocket = accept(serverSocket,NULL,0),0);

  const char * outBuf = "BEAD-Test";
  char * inBuf = (char *)calloc(strlen(outBuf)+1,sizeof(char));
  BOOST_CHECK_EQUAL(write(newSocket,outBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(read(clientSocket,inBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(strcmp(outBuf,inBuf),0);
  
  free(inBuf);
  close(serverSocket);
  close(clientSocket);
}

/**
Test that we can echo the data back. 
*/
BOOST_AUTO_TEST_CASE( echo_test)
{
  net_socket serverSocket = netSock::getTcpServerSocket("9999", 10);
  net_socket clientSocket = netSock::getTcpClientSocket("localhost", "9999");

  net_socket newSocket;
  BOOST_CHECK_GT(newSocket = accept(serverSocket,NULL,0),0);

  const char * outBuf = "BEAD-Test";
  char * inBuf = (char *)calloc(strlen(outBuf)+1,sizeof(char));
  char * secondBuf = (char *)calloc(strlen(outBuf)+1,sizeof(char));
  BOOST_CHECK_EQUAL(write(clientSocket,outBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(read(newSocket,inBuf,strlen(outBuf)),strlen(outBuf));
  BOOST_CHECK_EQUAL(write(newSocket,inBuf,strlen(inBuf)),strlen(inBuf));
  BOOST_CHECK_EQUAL(read(clientSocket,secondBuf,strlen(inBuf)),strlen(inBuf));
  
  BOOST_CHECK_EQUAL(strcmp(inBuf,secondBuf),0);
  
  free(inBuf);
  close(serverSocket);
  close(clientSocket);
}
