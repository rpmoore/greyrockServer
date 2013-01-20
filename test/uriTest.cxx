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
BOOST_AUTO_TEST_CASE( parse_host_name )
{
  gr_url url;
  const char * test_url = "www.test.com";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,test_url),0);
}

/**
 @brief Tests to make sure that the hostname and schema can be retrieved.
*/
BOOST_AUTO_TEST_CASE( parse_schema )
{
  gr_url url;
  const char * test_url = "http://www.test.com";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,test_url),0);
}

/**
 @brief Tests to make sure that the hostname can be retrieved.
*/
BOOST_AUTO_TEST_CASE( parse_port )
{
  gr_url url;
  const char * test_url = "www.test.com:1234";
  const char * expected_url = "www.test.com";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,expected_url), 0);
  BOOST_CHECK_EQUAL(url.port,1234);
}

/**
 @brief Tests to make sure that the hostname can be retrieved.
*/
BOOST_AUTO_TEST_CASE( parse_user )
{
  gr_url url;
  const char * test_url = "ryan@www.test.com";
  const char * expected_url = "www.test.com";
  const char * user = "ryan";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,expected_url), 0);
  BOOST_CHECK(url.user != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.user,user), 0);
}

/**
 @brief Tests to make sure that the hostname can be retrieved ignoring characters after whitespace.
*/
BOOST_AUTO_TEST_CASE( parse_ignoring_ending_space )
{
  gr_url url;
  const char * test_url = "www.test.com ignored";
  const char * expected_url= "www.test.com";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,expected_url),0);
}

/**
 @brief Tests to make sure that the hostname can be retrieved ignoring starting whitespace.
*/
BOOST_AUTO_TEST_CASE( parse_ignoring_starting_space )
{
  gr_url url;
  const char * test_url = "  www.test.com";
  const char * expected_url = "www.test.com";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,expected_url),0);
}

/**
 @brief A basic test to make sure that the absolute path can be parsed.
*/
BOOST_AUTO_TEST_CASE( parse_url_path )
{
  gr_url url;
  const char * test_url = "www.test.com/index.html";
  const char * expected_url = "www.test.com";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,expected_url),0);
  BOOST_CHECK_EQUAL(url.port,0);
  BOOST_CHECK(url.protocol == NULL);
  BOOST_CHECK(url.user == NULL);
  BOOST_CHECK(url.file != NULL);
  BOOST_CHECK_EQUAL(url.file,"/index.html");
}

/**
 @brief A basic test to make sure that the absolute path can be parsed.
*/
BOOST_AUTO_TEST_CASE( parse_absolute_url )
{
  gr_url url;
  const char * test_url = "/index.html";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname == NULL);
  BOOST_CHECK_EQUAL(url.port,0);
  BOOST_CHECK(url.protocol == NULL);
  BOOST_CHECK(url.user == NULL);
  BOOST_CHECK(url.file != NULL);
  BOOST_CHECK_EQUAL(url.file,"/index.html");

}

/**
 @brief A basic test to make sure that each field can get parsed correctly.
*/
BOOST_AUTO_TEST_CASE( parse_url_full )
{
  gr_url url;
  const char * test_url = "http://ryan@www.test.com:88/index.html";
  BOOST_CHECK(gr_netsock_create_url(&url,test_url,strlen(test_url)));
  BOOST_CHECK(url.hostname != NULL);
  BOOST_CHECK_EQUAL(strcmp(url.hostname,"www.test.com"),0);
  BOOST_CHECK_EQUAL(url.port,88);
  BOOST_CHECK(url.protocol != NULL);
  BOOST_CHECK_EQUAL(url.protocol,"http");
  BOOST_CHECK(url.user != NULL);
  BOOST_CHECK_EQUAL(url.user,"ryan");
  BOOST_CHECK(url.file != NULL);
  BOOST_CHECK_EQUAL(url.file,"/index.html");
}

