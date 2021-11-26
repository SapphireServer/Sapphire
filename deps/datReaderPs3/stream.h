#ifndef XIV_UTILS_STREAM_H
#define XIV_UTILS_STREAM_H

#include <memory>
#include <iostream>
#include <vector>

namespace xivps3::utils::stream
{
  template< typename CharT, typename TraitsT = std::char_traits< CharT > >
  class vectorwrapbuf :
    public std::basic_streambuf< CharT, TraitsT >
  {
  public:
    vectorwrapbuf( std::vector< CharT >& vec )
    {
      this->setg( vec.data(), vec.data(), vec.data() + vec.size() );
    }
  };
}
#endif // XIV_UTILS_STREAM_H
