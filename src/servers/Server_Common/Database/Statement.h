#ifndef SAPPHIRE_STATEMENT_H
#define SAPPHIRE_STATEMENT_H

#include <stdint.h>
#include <string>

namespace Core
{
namespace Db
{
   class Connection;
   class ResultSet;

   class Statement
   {
   protected:
      Connection * m_pConnection;

      void doQuery( const std::string& q );

      uint64_t m_lastUpdateCount;

      unsigned int m_warningsCount;

   public:
      Statement( Connection* conn );

      virtual ~Statement() {};

      virtual Connection * getConnection();

      virtual bool execute( const std::string& sql );

      virtual ResultSet * executeQuery( const std::string& sql );

      virtual ResultSet * getResultSet();

      virtual uint64_t getUpdateCount();

      virtual uint32_t getWarningCount();

      virtual uint32_t errNo();

   private:
      /* Prevent use of these */
      Statement( const Statement& );
      void operator=( Statement& );
   };

}
}



#endif //SAPPHIRE_STATEMENT_H
