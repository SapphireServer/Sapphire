#ifndef SAPPHIRE_MYSQL_NATIVE_H
#define SAPPHIRE_MYSQL_NATIVE_H

#include <mysql.h>
#include <type_traits>
#include <utility>

namespace Mysql
{
   using BindBool = std::remove_pointer_t< decltype( std::declval< MYSQL_BIND >().is_null ) >;
}

#endif // SAPPHIRE_MYSQL_NATIVE_H
