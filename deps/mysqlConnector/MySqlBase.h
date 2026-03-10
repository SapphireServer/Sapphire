#pragma once

#include <memory>
#include <string>
#include <cstdint>
#include "MySqlTypes.h"

namespace Mysql
{

  class Connection;

  class MySqlBase : public std::enable_shared_from_this< MySqlBase >
  {
  public:
    MySqlBase();

    ~MySqlBase();

    std::shared_ptr< Connection > connect( const std::string& hostName, const std::string& userName,
                                           const std::string& password, uint16_t port );
    std::shared_ptr< Connection > connect( const std::string& hostName, const std::string& userName,
                                           const std::string& password, const OptionMap& map, uint16_t port );

    std::string getVersionInfo();

  private:
    MySqlBase( const MySqlBase& );
    void operator=( MySqlBase& );
  };

}// namespace Mysql
