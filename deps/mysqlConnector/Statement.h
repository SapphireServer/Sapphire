#ifndef SAPPHIRE_STATEMENT_H
#define SAPPHIRE_STATEMENT_H

#include <stdint.h>
#include <string>
#include <memory>

namespace Mysql
{
   class Connection;
   class ResultSet;

   class Statement : public std::enable_shared_from_this< Statement >
   {
   protected:
      std::shared_ptr< Connection > m_pConnection;

      void doQuery( const std::string& q );

      uint64_t m_lastUpdateCount;

      unsigned int m_warningsCount;

   public:
      Statement( std::shared_ptr< Connection > conn );

      virtual ~Statement() {};

      virtual std::shared_ptr< Connection > getConnection();

      virtual bool execute( const std::string& sql );

      virtual std::shared_ptr< ResultSet > executeQuery( const std::string& sql );

      virtual std::shared_ptr< ResultSet > getResultSet();

      virtual uint64_t getUpdateCount();

      virtual uint32_t getWarningCount();

      virtual uint32_t errNo();

   private:
      /* Prevent use of these */
      Statement( const Statement& );
      void operator=( Statement& );
   };

}
#endif //SAPPHIRE_STATEMENT_H
