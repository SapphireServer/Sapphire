#ifndef SAPPHIRE_RESULTBIND_H
#define SAPPHIRE_RESULTBIND_H

#include <boost/scoped_array.hpp>

#include "mysql_util.h"
#include "mysql.h"
#include "PreparedStatement.h"

namespace Core
{
namespace Db
{

   class ResultBind
   {
      uint32_t m_numFields;
      boost::scoped_array< char > m_isNull;
      boost::scoped_array< char > m_err;
      boost::scoped_array< unsigned long > m_len;
      MYSQL_STMT* m_pStmt;

   public:
      boost::scoped_array< MYSQL_BIND > m_pBind;

      ResultBind( MYSQL_STMT* pStmt );

      ~ResultBind();

      void bindResult();

   };

}
}

#endif //SAPPHIRE_RESULTBIND_H
