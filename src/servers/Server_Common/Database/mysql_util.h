/*
Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.

The MySQL Connector/C++ is licensed under the terms of the GPLv2
<http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>, like most
MySQL Connectors. There are special exceptions to the terms and
conditions of the GPLv2 as it is applied to this software, see the
FLOSS License Exception
<http://www.mysql.com/about/legal/licensing/foss-exception.html>.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef SAPPHIRE_MYSQL_UTIL_H
#define SAPPHIRE_MYSQL_UTIL_H

#include <iostream>
#include <sstream>
#include <mysql.h>

#ifndef UL64
#ifdef _WIN32
#define UL64(x) x##ui64
#else
#define UL64(x) x##ULL
#endif
#endif

#ifndef L64
#ifdef _WIN32
#define L64(x) x##i64
#else
#define L64(x) x##LL
#endif
#endif

#define NULLCSTR static_cast<char *>(0)

#ifndef _WIN32
#  ifndef HAVE_FUNCTION_STRTOLL
#    define strtoll(__a, __b, __c)  static_cast<long long>(Util::strtold((__a), NULL))
#    define HAVE_FUNCTION_STRTOLL 1
#  endif
#  ifndef HAVE_FUNCTION_STRTOULL
#    define strtoull(__a, __b, __c)  static_cast<unsigned long long>(Util::strtold((__a), NULL))
#    define HAVE_FUNCTION_STRTOULL 1
#  endif
#else
# ifndef strtoll
#  define strtoll(x, e, b) _strtoi64((x), (e), (b))
# endif
# ifndef strtoull
#  define strtoull(x, e, b) _strtoui64((x), (e), (b))
# endif
#endif	//	_WIN32


#define bit_uint1korr(A)	(*(((uint8_t*)(A))))

#define bit_uint2korr(A) ((uint16_t) (((uint16_t) (((unsigned char*) (A))[1])) +\
                                   ((uint16_t) (((unsigned char*) (A))[0]) << 8)))
#define bit_uint3korr(A) ((uint32_t) (((uint32_t) (((unsigned char*) (A))[2])) +\
                                   (((uint32_t) (((unsigned char*) (A))[1])) << 8) +\
                                   (((uint32_t) (((unsigned char*) (A))[0])) << 16)))
#define bit_uint4korr(A) ((uint32_t) (((uint32_t) (((unsigned char*) (A))[3])) +\
                                   (((uint32_t) (((unsigned char*) (A))[2])) << 8) +\
                                   (((uint32_t) (((unsigned char*) (A))[1])) << 16) +\
                                   (((uint32_t) (((unsigned char*) (A))[0])) << 24)))
#define bit_uint5korr(A) ((uint64_t)(((uint32_t) (((unsigned char*) (A))[4])) +\
                                    (((uint32_t) (((unsigned char*) (A))[3])) << 8) +\
                                    (((uint32_t) (((unsigned char*) (A))[2])) << 16) +\
                                   (((uint32_t) (((unsigned char*) (A))[1])) << 24)) +\
                                    (((uint64_t) (((unsigned char*) (A))[0])) << 32))
#define bit_uint6korr(A) ((uint64_t)(((uint32_t) (((unsigned char*) (A))[5])) +\
                                    (((uint32_t) (((unsigned char*) (A))[4])) << 8) +\
                                    (((uint32_t) (((unsigned char*) (A))[3])) << 16) +\
                                    (((uint32_t) (((unsigned char*) (A))[2])) << 24)) +\
                        (((uint64_t) (((uint32_t) (((unsigned char*) (A))[1])) +\
                                    (((uint32_t) (((unsigned char*) (A))[0]) << 8)))) <<\
                                     32))
#define bit_uint7korr(A) ((uint64_t)(((uint32_t) (((unsigned char*) (A))[6])) +\
                                    (((uint32_t) (((unsigned char*) (A))[5])) << 8) +\
                                    (((uint32_t) (((unsigned char*) (A))[4])) << 16) +\
                                   (((uint32_t) (((unsigned char*) (A))[3])) << 24)) +\
                        (((uint64_t) (((uint32_t) (((unsigned char*) (A))[2])) +\
                                    (((uint32_t) (((unsigned char*) (A))[1])) << 8) +\
                                    (((uint32_t) (((unsigned char*) (A))[0])) << 16))) <<\
                                     32))
#define bit_uint8korr(A) ((uint64_t)(((uint32_t) (((unsigned char*) (A))[7])) +\
                                    (((uint32_t) (((unsigned char*) (A))[6])) << 8) +\
                                    (((uint32_t) (((unsigned char*) (A))[5])) << 16) +\
                                    (((uint32_t) (((unsigned char*) (A))[4])) << 24)) +\
                        (((uint64_t) (((uint32_t) (((unsigned char*) (A))[3])) +\
                                    (((uint32_t) (((unsigned char*) (A))[2])) << 8) +\
                                    (((uint32_t) (((unsigned char*) (A))[1])) << 16) +\
                                    (((uint32_t) (((unsigned char*) (A))[0])) << 24))) <<\
                                    32))
namespace Util
{
   long double strtold( const char *nptr, char **endptr );
   long double strtonum( const std::string &str, int radix = 10 );
   int32_t mysql_type_to_datatype( const MYSQL_FIELD * const field );

   typedef struct st_our_charset
   {
      unsigned int	nr;
      const char		*name;
      const char		*collation;
      unsigned int	char_minlen;
      unsigned int	char_maxlen;
      const char		*comment;
      unsigned int 	(*mb_charlen)(unsigned int c);
      unsigned int 	(*mb_valid)(const char *start, const char *end);
   } OUR_CHARSET;

   const OUR_CHARSET * find_charset(unsigned int charsetnr);

}
#endif //SAPPHIRE_MYSQL_UTIL_H
