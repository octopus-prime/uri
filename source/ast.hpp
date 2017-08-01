/*
 * ast.hpp
 *
 *  Created on: 01.08.2017
 *      Author: mike
 */

#pragma once

#include <uri/uri.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace uri {
namespace ast {

struct authority
{
	std::string userinfo;
	std::string host;
	std::uint16_t port = 0;
};

struct hier_part
{
	ast::authority authority;
	std::string path;
};

}

struct uri::impl
{
	std::string scheme;
	ast::hier_part hier_part;
	std::string query;
	std::string fragment;
};

namespace ast {

using uri = uri::impl;

}
}

BOOST_FUSION_ADAPT_STRUCT(uri::ast::authority, userinfo, host, port);
BOOST_FUSION_ADAPT_STRUCT(uri::ast::hier_part, authority, path);
BOOST_FUSION_ADAPT_STRUCT(uri::ast::uri, scheme, hier_part, query, fragment);
