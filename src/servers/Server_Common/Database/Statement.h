#ifndef SAPPHIRE_STATEMENT_H
#define SAPPHIRE_STATEMENT_H

#include <stdint.h>
#include <string>
#include "StatementBase.h"

namespace Core
{
namespace Db
{
   class Connection;
   class ResultSet;

   class Statement : public StatementBase
   {
   protected:
      Connection * m_pConnection;

      void doQuery( const std::string& q );

      uint64_t m_lastUpdateCount;

      unsigned int m_warningsCount;

   public:
      Statement( Connection* conn );

      virtual ~Statement() {};

      Connection * getConnection() override;

      bool execute( const std::string& sql ) override;

      ResultSet * executeQuery( const std::string& sql ) override;

      ResultSet * getResultSet() override;

      uint64_t getUpdateCount() override;

      uint32_t getWarningCount() override;

      uint32_t errNo() override;

   private:
      /* Prevent use of these */
      Statement( const Statement& );
      void operator=( Statement& );
   };

}
}



#endif //SAPPHIRE_STATEMENT_H
