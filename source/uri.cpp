/*
 * uri.cpp
 *
 *  Created on: 09.07.2017
 *      Author: mike
 */

#include "parser.hpp"

namespace uri {

uri::uri()
:
	pimpl(std::make_shared<impl>())
{
}

uri::uri(std::string const& string)
:
	uri()
{
	auto begin = std::cbegin(string);
	auto end = std::cend(string);
	auto result = x3::parse(begin, end, parser::uri, *pimpl);
	if (!result || begin != end)
		throw std::invalid_argument("Invalid uri: " + string);
}

uri::uri(std::string const& scheme, std::string const& userinfo,
		std::string const& host, std::uint16_t port,
		std::string const& path, std::string const& query,
		std::string const& fragment)
:
	uri()
{
	pimpl->scheme = scheme;
	pimpl->hier_part.authority.userinfo = userinfo;
	pimpl->hier_part.authority.host = host;
	pimpl->hier_part.authority.port = port;
	pimpl->hier_part.path = path;
	pimpl->query = query;
	pimpl->fragment = fragment;
}

uri::~uri() noexcept = default;

std::string uri::scheme() const
{
	return pimpl->scheme;
}

std::string uri::userinfo() const
{
	return pimpl->hier_part.authority.userinfo;
}

std::string uri::host() const
{
	return pimpl->hier_part.authority.host;
}

std::uint16_t uri::port() const
{
	return pimpl->hier_part.authority.port;
}

std::string uri::path() const
{
	return pimpl->hier_part.path;
}

std::string uri::query() const
{
	return pimpl->query;
}

std::string uri::fragment() const
{
	return pimpl->fragment;
}

std::string uri::string() const
{
	std::string string = scheme();
	string += "://";
	if (!userinfo().empty())
	{
		string += userinfo();
		string += '@';
	}
	if (!host().empty())
	{
		string += host();
	}
	if (port() != 0)
	{
		string += ':';
		string += std::to_string(port());
	}
	if (!path().empty())
	{
		string += path();
	}
	if (!query().empty())
	{
		string += '?';
		string += query();
	}
	if (!fragment().empty())
	{
		string += '#';
		string += fragment();
	}
	return string;
}

}
