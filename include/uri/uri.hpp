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
	uri(std::string const& string);
	uri(std::string const& scheme, std::string const& userinfo,
		std::string const& host, std::uint16_t port,
		std::string const& path, std::string const& query,
		std::string const& fragment);
	~uri() noexcept;
	std::string scheme() const;
	std::string userinfo() const;
	std::string host() const;
	std::uint16_t port() const;
	std::string path() const;
	std::string query() const;
	std::string fragment() const;
	std::string string() const;

private:
	std::shared_ptr<impl> pimpl;
};

}
