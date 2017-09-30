#ifndef SAPPHIRE_DBLOADER_H
#define SAPPHIRE_DBLOADER_H

#include <stdint.h>
#include <functional>
#include <queue>
#include <stack>
#include <string>
#include "DbConnection.h"

namespace Core
{
   namespace Db
   {

   template< class T >
   class DbWorkerPool;

   class DbLoader
   {
   public:
      DbLoader();

      template< class T >
      DbLoader& addDb( DbWorkerPool< T >& pool, const ConnectionInfo& info );

      bool initDbs();

      enum DbTypeFlags
      {
         DATABASE_NONE        = 0,
         DATABASE_CHARACTER   = 1,
         DATABASE_MASK_ALL    = DATABASE_CHARACTER
      };

   private:
      bool openDatabases();
      bool prepareStatements();

      using Predicate = std::function< bool() >;
      using Closer = std::function< void() >;

      bool process( std::queue< Predicate >& queue );

      std::queue< Predicate > m_open;
      std::queue< Predicate > m_prepare;
      std::stack< Closer > m_close;
   };
}
}

#endif //SAPPHIRE_DBLOADER_H
