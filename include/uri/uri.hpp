/*
 * uri.hpp
 *
 *  Created on: 31.07.2017
 *      Author: mike
 */

#pragma once

#include <string>
#include <memory>

namespace uri {

class uri {
public:
	struct impl;

	uri();
	uri(std::string str);
	~uri();
	std::string scheme() const;
	std::string userinfo() const;
	std::string host() const;
	std::uint16_t port() const;
	std::string path() const;
	std::string query() const;
	std::string fragment() const;
	std::string str() const;

private:
	std::shared_ptr<impl> pimpl;
};

}
