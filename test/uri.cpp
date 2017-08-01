/*
 * uri.cpp
 *
 *  Created on: 01.08.2017
 *      Author: mike
 */

#include <uri/uri.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

namespace uri {

BOOST_AUTO_TEST_SUITE(test)

//"https://horst.com:123?foo%20xxx#bar",
//"https://he.wikipedia.org/wiki/%D7%9E%D7%9C%D7%97%D7%9E%D7%94_%D7%95%D7%A9%D7%9C%D7%95%D7%9D",
//"http://r%C3%A4ksm%C3%B6rg%C3%A5s.josefsson.org",
//"http://%E7%B4%8D%E8%B1%86.w3.mag.keio.ac.jp",

std::initializer_list<std::string> const strings
{
	"http://www.ics.uci.edu:65535/pub/ietf/uri/?foo=bar#Related",
	"https://foo:bar@www.google.com",
	"http://www.w3.org", //	"http://www.w%33.org",
};

std::initializer_list<std::string> const schemes
{
	"http",
	"https",
	"http",
};

std::initializer_list<std::string> const userinfos
{
	"",
	"foo:bar",
	"",
};

std::initializer_list<std::string> const hosts
{
	"www.ics.uci.edu",
	"www.google.com",
	"www.w3.org",
};

std::initializer_list<std::uint16_t> const ports
{
	65535,
	0,
	0,
};

std::initializer_list<std::string> const paths
{
	"/pub/ietf/uri/",
	"",
	"",
};

std::initializer_list<std::string> const queries
{
	"foo=bar",
	"",
	"",
};

std::initializer_list<std::string> const fragments
{
	"Related",
	"",
	"",
};

BOOST_DATA_TEST_CASE(test_create,
		strings ^ schemes ^ userinfos ^ hosts ^ ports ^ paths ^ queries ^ fragments,
		string,   scheme,   userinfo,   host,   port,   path,   query,    fragment)
{
	uri temp;
	BOOST_REQUIRE_NO_THROW(temp = uri(scheme, userinfo, host, port, path, query, fragment));
	BOOST_CHECK_EQUAL(temp.scheme(), scheme);
	BOOST_CHECK_EQUAL(temp.userinfo(), userinfo);
	BOOST_CHECK_EQUAL(temp.host(), host);
	BOOST_CHECK_EQUAL(temp.port(), port);
	BOOST_CHECK_EQUAL(temp.path(), path);
	BOOST_CHECK_EQUAL(temp.query(), query);
	BOOST_CHECK_EQUAL(temp.fragment(), fragment);
	BOOST_CHECK_EQUAL(temp.string(), string);
}

BOOST_DATA_TEST_CASE(test_parse_success,
		strings ^ schemes ^ userinfos ^ hosts ^ ports ^ paths ^ queries ^ fragments,
		string,   scheme,   userinfo,   host,   port,   path,   query,    fragment)
{
	uri temp;
	BOOST_REQUIRE_NO_THROW(temp = uri(string));
	BOOST_CHECK_EQUAL(temp.scheme(), scheme);
	BOOST_CHECK_EQUAL(temp.userinfo(), userinfo);
	BOOST_CHECK_EQUAL(temp.host(), host);
	BOOST_CHECK_EQUAL(temp.port(), port);
	BOOST_CHECK_EQUAL(temp.path(), path);
	BOOST_CHECK_EQUAL(temp.query(), query);
	BOOST_CHECK_EQUAL(temp.fragment(), fragment);
}

std::initializer_list<std::string> const invalids
{
	"",
	"https:/www.google.com:443",
	"https://www.google.com:",
	"http://www.ics.uci.edu:65536/pub/ietf/uri/?foo=bar#Related",
};

BOOST_DATA_TEST_CASE(test_parse_failure, invalids, string)
{
	uri temp;
	BOOST_CHECK_THROW(temp = uri(string), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

}
