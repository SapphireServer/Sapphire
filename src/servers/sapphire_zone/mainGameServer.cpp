#include <iostream>

#include "ServerMgr.h"
#include <Framework.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include "Script/ScriptMgr.h"
#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include "Linkshell/LinkshellMgr.h"
#include "Zone/TerritoryMgr.h"
#include "Zone/HousingMgr.h"
#include "DebugCommand/DebugCommandHandler.h"

#include <Config/ConfigMgr.h>

Core::Framework g_fw;

using namespace Core;

bool setupFramework()
{
  auto pServer = std::make_shared< ServerMgr >( "config.ini" );
  auto pLogger = std::make_shared< Logger >();
  auto pExdData = std::make_shared< Data::ExdDataGenerated >();
  auto pScript = std::make_shared< Scripting::ScriptMgr >();
  auto pDb = std::make_shared< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pLsMgr = std::make_shared< LinkshellMgr >();
  auto pHousingMgr = std::make_shared< HousingMgr >();
  auto pTeriMgr = std::make_shared< TerritoryMgr >();
  auto pDebugCom = std::make_shared< DebugCommandHandler >();
  auto pConfig = std::make_shared< ConfigMgr >();

  pLogger->setLogPath( "log/SapphireZone" );
  pLogger->init();

  g_fw.set< ServerMgr >( pServer );
  g_fw.set< Logger >( pLogger );
  g_fw.set< Data::ExdDataGenerated >( pExdData );
  g_fw.set< Scripting::ScriptMgr >( pScript );
  g_fw.set< Db::DbWorkerPool< Db::ZoneDbConnection > >( pDb );
  g_fw.set< LinkshellMgr >( pLsMgr );
  g_fw.set< HousingMgr >( pHousingMgr );
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

  g_fw.get< ServerMgr >()->run( argc, argv );
  return 0;
}
