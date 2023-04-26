#pragma once

#include <memory>
#include <iostream>
#include <vector>

namespace xiv::utils::stream
{
  template< typename CharT, typename TraitsT = std::char_traits< CharT > >
  class vectorwrapbuf : public std::basic_streambuf< CharT, TraitsT >
  {
  public:
    vectorwrapbuf( std::vector< CharT >& vec ) : std::basic_streambuf< CharT, TraitsT >()
    {
      this->setg( vec.data(), vec.data(), vec.data() + vec.size() );
    }
  };
}// namespace xiv::utils::stream
