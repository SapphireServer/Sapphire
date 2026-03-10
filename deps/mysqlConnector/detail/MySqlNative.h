#pragma once

#include <mysql.h>
#include <type_traits>
#include <utility>

namespace Mysql
{
  using BindBool = std::remove_pointer_t< decltype( std::declval< MYSQL_BIND >().is_null ) >;
}
