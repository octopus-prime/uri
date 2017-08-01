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

//"http://www.ics.uci.edu:65000/pub/ietf/uri/#Related",
//"https://www.google.com:443",
//"https://www.google.com",
//"https://foo:bar@www.google.com",
//"https://horst.com:123?foo%20xxx#bar",
//"https://he.wikipedia.org/wiki/%D7%9E%D7%9C%D7%97%D7%9E%D7%94_%D7%95%D7%A9%D7%9C%D7%95%D7%9D",
//"http://www.w%33.org",
//"http://r%C3%A4ksm%C3%B6rg%C3%A5s.josefsson.org",
//"http://%E7%B4%8D%E8%B1%86.w3.mag.keio.ac.jp",
//"https:/www.google.com:443",
//"https://www.google.com:",

std::initializer_list<std::string> const strings
{
	"http://www.ics.uci.edu:65000/pub/ietf/uri/#Related",
	"https://foo:bar@www.google.com",
};

std::initializer_list<std::string> const schemes
{
	"http",
	"https",
};

std::initializer_list<std::string> const userinfos
{
	"",
	"foo:bar",
};

std::initializer_list<std::string> const hosts
{
	"www.ics.uci.edu",
	"www.google.com",
};

std::initializer_list<std::uint16_t> const ports
{
	65000,
	0,
};

BOOST_DATA_TEST_CASE(test_success, strings ^ schemes ^ userinfos ^ hosts ^ ports, string, scheme, userinfo, host, port)
{
	uri temp;
	BOOST_REQUIRE_NO_THROW(temp = uri(string));
	BOOST_CHECK_EQUAL(temp.scheme(), scheme);
	BOOST_CHECK_EQUAL(temp.userinfo(), userinfo);
	BOOST_CHECK_EQUAL(temp.host(), host);
	BOOST_CHECK_EQUAL(temp.port(), port);
}

//std::initializer_list<string_t> const invalids
//{
//	"",
//};
//
//BOOST_DATA_TEST_CASE(test_failure, invalids, string)
//{
//	BOOST_CHECK_THROW(parse(string), parser_exception);
//}

BOOST_AUTO_TEST_SUITE_END()

}
