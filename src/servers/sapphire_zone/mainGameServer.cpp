#include <iostream>

#include "ServerZone.h"
#include <boost/algorithm/string.hpp>
#include <Framework.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include "Script/ScriptMgr.h"
#include <Database/CharaDbConnection.h>
#include <Database/DbWorkerPool.h>
#include "Linkshell/LinkshellMgr.h"
#include "Zone/TerritoryMgr.h"
#include "DebugCommand/DebugCommandHandler.h"

#include <Config/ConfigMgr.h>

Core::Framework g_fw;

using namespace Core;

bool setupFramework()
{
   auto pServer = boost::make_shared< ServerZone >( "zone.ini" );
   auto pLogger = boost::make_shared< Logger >();
   auto pExdData = boost::make_shared< Data::ExdDataGenerated >();
   auto pScript = boost::make_shared< Scripting::ScriptMgr >();
   auto pDb = boost::make_shared< Db::DbWorkerPool< Db::CharaDbConnection > >();
   auto pLsMgr = boost::make_shared< LinkshellMgr >();
   auto pTeriMgr = boost::make_shared< TerritoryMgr >();
   auto pDebugCom = boost::make_shared< DebugCommandHandler >();
   auto pConfig = boost::make_shared< ConfigMgr >();

   pLogger->setLogPath( "log/SapphireZone_" );
   pLogger->init();

   g_fw.set< ServerZone >( pServer );
   g_fw.set< Logger >( pLogger );
   g_fw.set< Data::ExdDataGenerated >( pExdData );
   g_fw.set< Scripting::ScriptMgr >( pScript );
   g_fw.set< Db::DbWorkerPool< Db::CharaDbConnection > >( pDb );
   g_fw.set< LinkshellMgr >( pLsMgr );
   g_fw.set< TerritoryMgr >( pTeriMgr );
   g_fw.set< DebugCommandHandler >( pDebugCom );
   g_fw.set< ConfigMgr >( pConfig );

   // actuall catch errors here...
   return true;
}

int main( int32_t argc, char* argv[] )
{
   if( !setupFramework() )
      return 0; // too fucking bad...

   g_fw.get< ServerZone >()->run( argc, argv );
   return 0;
}
