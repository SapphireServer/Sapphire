#include "MySqlBase.h"
#include "Connection.h"
#include "Statement.h"
#include "PreparedStatement.h"
#include "ResultSet.h"
#include "PreparedResultSet.h"
#include <memory>

namespace Mysql
{
   using PreparedResultSetScopedPtr = std::unique_ptr< Mysql::PreparedResultSet >;
}
