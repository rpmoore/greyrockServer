#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "net_sock.h"

/**
 @brief Tests to make sure that the hostname can be retrieved.
*/
BOOST_AUTO_TEST_CASE( parseHostName )
{
  gr_uri uri;
  const char * testUri = "www.test.com";
  BOOST_CHECK(gr_netSock_createURI(&uri,testUri,strlen(testUri)));
  BOOST_CHECK(uri.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(uri.hostname,testUri),0);
}

/**
 @brief Tests to make sure that the hostname and schema can be retrieved.
*/
BOOST_AUTO_TEST_CASE( parseSchema )
{
  gr_uri uri;
  const char * testUri = "http://www.test.com";
  BOOST_CHECK(gr_netSock_createURI(&uri,testUri,strlen(testUri)));
  BOOST_CHECK(uri.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(uri.hostname,testUri),0);
}

/**
 @brief Tests to make sure that the hostname can be retrieved ignoring characters after whitespace.
*/
BOOST_AUTO_TEST_CASE( parseIgnoringEndingSpace )
{
  gr_uri uri;
  const char * testUri = "www.test.com ignored";
  const char * expectedUri= "www.test.com";
  BOOST_CHECK(gr_netSock_createURI(&uri,testUri,strlen(testUri)));
  BOOST_CHECK(uri.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(uri.hostname,expectedUri),0);
}

/**
 @brief Tests to make sure that the hostname can be retrieved ignoring starting whitespace.
*/
BOOST_AUTO_TEST_CASE( parseIgnoringStartingSpace )
{
  gr_uri uri;
  const char * testUri = "  www.test.com";
  const char * expectedUri = "www.test.com";
  BOOST_CHECK(gr_netSock_createURI(&uri,testUri,strlen(testUri)));
  BOOST_CHECK(uri.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(uri.hostname,expectedUri),0);
}

/**
 @brief A basic test to make sure that the absolute path can be parsed.
*/
BOOST_AUTO_TEST_CASE( parseUrlPath )
{
  gr_uri uri;
  const char * testURI = "www.test.com/index.html";
  const char * expectedURI = "www.test.com";
  BOOST_CHECK(gr_netSock_createURI(&uri,testURI,strlen(testURI)));
  BOOST_CHECK(uri.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(uri.hostname,expectedURI),0);
  BOOST_CHECK_EQUAL(uri.port,0);
  BOOST_CHECK(uri.protocol == NULL);
  BOOST_CHECK(uri.user == NULL);
  BOOST_CHECK(uri.file != NULL);
  BOOST_CHECK_EQUAL(uri.file,"/index.html");
}

/**
 @brief A basic test to make sure that the absolute path can be parsed.
*/
BOOST_AUTO_TEST_CASE( parseAbsoluteURI )
{
  gr_uri uri;
  const char * testURI = "/index.html";
  BOOST_CHECK(gr_netSock_createURI(&uri,testURI,strlen(testURI)));
  BOOST_CHECK(uri.hostname == NULL);
  BOOST_CHECK_EQUAL(uri.port,0);
  BOOST_CHECK(uri.protocol == NULL);
  BOOST_CHECK(uri.user == NULL);
  BOOST_CHECK(uri.file != NULL);
  BOOST_CHECK_EQUAL(uri.file,"/index.html");

}


/**
 @brief A basic test to make sure that each field can get parsed correctly.
*/
BOOST_AUTO_TEST_CASE( parseUriFull )
{
  gr_uri uri;
  const char * testURI = "http://ryan@www.test.com:88/index.html";
  BOOST_CHECK(gr_netSock_createURI(&uri,testURI,strlen(testURI)));
  BOOST_CHECK(uri.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(uri.hostname,"www.test.com"),0);
  BOOST_CHECK_EQUAL(uri.port,88);
  BOOST_CHECK(uri.protocol != NULL);
  BOOST_CHECK_EQUAL(uri.protocol,"http");
  BOOST_CHECK(uri.user != NULL);
  BOOST_CHECK_EQUAL(uri.user,"ryan");
  BOOST_CHECK(uri.file != NULL);
  BOOST_CHECK_EQUAL(uri.file,"/index.html");
}

