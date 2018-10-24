#ifndef SAPPHIRE_RESULTBIND_H
#define SAPPHIRE_RESULTBIND_H

#include <memory>
#include "mysql_util.h"
#include "mysql.h"
#include "PreparedStatement.h"

namespace Mysql
{
   class ResultBind
   {
      uint32_t m_numFields;
      std::unique_ptr< char[] > m_isNull;
      std::unique_ptr< char[] > m_err;
      std::unique_ptr< unsigned long[] > m_len;
      MYSQL_STMT* m_pStmt;

   public:
      std::unique_ptr< MYSQL_BIND[] > m_pBind;

      MYSQL_STMT* getStmt() { return m_pStmt; }

      ResultBind( MYSQL_STMT* pStmt );

      ~ResultBind();

      void bindResult();

   };
}

#endif //SAPPHIRE_RESULTBIND_H
