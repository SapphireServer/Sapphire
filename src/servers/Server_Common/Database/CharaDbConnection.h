#ifndef SAPPHIRE_CHARACONNECTION_H
#define SAPPHIRE_CHARACONNECTION_H

#include "DbConnection.h"

namespace Core
{
namespace Db
{
class DbConnectionInfo;

enum CharaDbStatements : uint32_t
{
   CHAR_SEL_LOAD,
   CHAR_SEL_LOAD_CLASSINFO,
   CHAR_SEL_LOAD_SEARCHINFO,
   CHAR_SEL_LOAD_QUESTINFO,
   CHAR_INS_TEST,

   MAX_STATEMENTS
};

class  CharaDbConnection : public DbConnection
{
public:
   typedef CharaDbStatements Statements;

   CharaDbConnection( ConnectionInfo& connInfo );
   CharaDbConnection( Core::LockedWaitQueue< Operation* >* q, ConnectionInfo &connInfo );

   ~CharaDbConnection();

   void doPrepareStatements() override;

};

}
}

#endif //SAPPHIRE_CHARACONNECTION_H
