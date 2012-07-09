#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "net_sock.h"


/**
 @brief A basic test to make sure that each field can get parsed correctly.
*/
BOOST_AUTO_TEST_CASE( parseBaseURI)
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
  BOOST_CHECK_EQUAL(uri.file,"index.html");

}
