/*
 * parser.hpp
 *
 *  Created on: 01.08.2017
 *      Author: mike
 */

#pragma once

//#define BOOST_SPIRIT_X3_DEBUG

#include "ast.hpp"
#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace uri {
namespace parser {

x3::rule<struct uri_, ast::uri> const uri("uri");
x3::rule<struct scheme, std::string> const scheme("scheme");
x3::rule<struct hier_part, ast::hier_part> const hier_part("hier_part");
x3::rule<struct authority, ast::authority> const authority("authority");
x3::rule<struct userinfo, std::string> const userinfo("userinfo");
x3::rule<struct host, std::string> const host("host");
x3::rule<struct port, std::uint16_t> const port("port");
x3::rule<struct path, std::string> const path("path");
x3::rule<struct segment, std::string> const segment("segment");
x3::rule<struct reg_name, std::string> const reg_name("reg_name");
x3::rule<struct query, std::string> const query("query");
x3::rule<struct fragment, std::string> const fragment("fragment");
x3::rule<struct pchar, char> const pchar("pchar");
x3::rule<struct unreserved, char> const unreserved("unreserved");
x3::rule<struct pct_encoded, char> const pct_encoded("pct_encoded");
x3::rule<struct sub_delims, char> const sub_delims("sub_delims");

auto const uri_def = scheme >> x3::lit(':') >> hier_part >> -query >> -fragment;
auto const scheme_def = x3::lexeme[x3::alpha >> *(x3::alnum | x3::char_("+-."))];
auto const hier_part_def = x3::lit("//") >> authority >> path; //todo
auto const authority_def = -userinfo >> host >> -port;
auto const userinfo_def = x3::lexeme[*(unreserved | pct_encoded | sub_delims | x3::char_(':'))] >> x3::lit('@');
auto const host_def = reg_name; //todo
auto const port_def = x3::lit(':') >> x3::ushort_;
auto const path_def = *(x3::char_('/') >> segment); //todo
auto const segment_def = x3::lexeme[*pchar];
auto const reg_name_def = x3::lexeme[*(unreserved | pct_encoded | sub_delims)];
auto const query_def = x3::lit('?') >> x3::lexeme[*(pchar | x3::char_("/?"))];
auto const fragment_def = x3::lit('#') >> x3::lexeme[*(pchar | x3::char_("/?"))];
auto const pchar_def = unreserved | pct_encoded | sub_delims | x3::char_(":@");
auto const unreserved_def = x3::alnum | x3::char_("-._~");
auto const pct_encoded_def = x3::lit('%') >> x3::uint_parser<char, 16, 2, 2>();
auto const sub_delims_def = x3::char_("!$&'()*+,;=");

BOOST_SPIRIT_DEFINE(uri, scheme, hier_part, authority, userinfo, host, port, path, segment, reg_name, query, fragment, pchar, unreserved, pct_encoded, sub_delims);

}
}

//Appendix A.  Collected ABNF for URI
//
//   URI           = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
//
//   hier-part     = "//" authority path-abempty
//                 / path-absolute
//                 / path-rootless
//                 / path-empty
//
//   URI-reference = URI / relative-ref
//
//   absolute-URI  = scheme ":" hier-part [ "?" query ]
//
//   relative-ref  = relative-part [ "?" query ] [ "#" fragment ]
//
//   relative-part = "//" authority path-abempty
//                 / path-absolute
//                 / path-noscheme
//                 / path-empty
//
//   scheme        = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
//
//   authority     = [ userinfo "@" ] host [ ":" port ]
//   userinfo      = *( unreserved / pct-encoded / sub-delims / ":" )
//   host          = IP-literal / IPv4address / reg-name
//   port          = *DIGIT
//
//   IP-literal    = "[" ( IPv6address / IPvFuture  ) "]"
//
//   IPvFuture     = "v" 1*HEXDIG "." 1*( unreserved / sub-delims / ":" )
//
//   IPv6address   =                            6( h16 ":" ) ls32
//                 /                       "::" 5( h16 ":" ) ls32
//                 / [               h16 ] "::" 4( h16 ":" ) ls32
//                 / [ *1( h16 ":" ) h16 ] "::" 3( h16 ":" ) ls32
//                 / [ *2( h16 ":" ) h16 ] "::" 2( h16 ":" ) ls32
//                 / [ *3( h16 ":" ) h16 ] "::"    h16 ":"   ls32
//                 / [ *4( h16 ":" ) h16 ] "::"              ls32
//                 / [ *5( h16 ":" ) h16 ] "::"              h16
//                 / [ *6( h16 ":" ) h16 ] "::"
//
//   h16           = 1*4HEXDIG
//   ls32          = ( h16 ":" h16 ) / IPv4address
//   IPv4address   = dec-octet "." dec-octet "." dec-octet "." dec-octet
//
//
//
//
//
//
//
//Berners-Lee, et al.         Standards Track                    [Page 49]
//
//
//RFC 3986                   URI Generic Syntax               January 2005
//
//
//   dec-octet     = DIGIT                 ; 0-9
//                 / %x31-39 DIGIT         ; 10-99
//                 / "1" 2DIGIT            ; 100-199
//                 / "2" %x30-34 DIGIT     ; 200-249
//                 / "25" %x30-35          ; 250-255
//
//   reg-name      = *( unreserved / pct-encoded / sub-delims )
//
//   path          = path-abempty    ; begins with "/" or is empty
//                 / path-absolute   ; begins with "/" but not "//"
//                 / path-noscheme   ; begins with a non-colon segment
//                 / path-rootless   ; begins with a segment
//                 / path-empty      ; zero characters
//
//   path-abempty  = *( "/" segment )
//   path-absolute = "/" [ segment-nz *( "/" segment ) ]
//   path-noscheme = segment-nz-nc *( "/" segment )
//   path-rootless = segment-nz *( "/" segment )
//   path-empty    = 0<pchar>
//
//   segment       = *pchar
//   segment-nz    = 1*pchar
//   segment-nz-nc = 1*( unreserved / pct-encoded / sub-delims / "@" )
//                 ; non-zero-length segment without any colon ":"
//
//   pchar         = unreserved / pct-encoded / sub-delims / ":" / "@"
//
//   query         = *( pchar / "/" / "?" )
//
//   fragment      = *( pchar / "/" / "?" )
//
//   pct-encoded   = "%" HEXDIG HEXDIG
//
//   unreserved    = ALPHA / DIGIT / "-" / "." / "_" / "~"
//   reserved      = gen-delims / sub-delims
//   gen-delims    = ":" / "/" / "?" / "#" / "[" / "]" / "@"
//   sub-delims    = "!" / "$" / "&" / "'" / "(" / ")"
//                 / "*" / "+" / "," / ";" / "="
