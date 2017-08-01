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

uri::uri(std::string const& str)
:
	uri()
{
	auto begin = std::cbegin(str);
	auto end = std::cend(str);
	auto result = x3::parse(begin, end, parser::uri, *pimpl);
	if (!result || begin != end)
		throw std::invalid_argument("Invalid uri: " + str);
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

}
