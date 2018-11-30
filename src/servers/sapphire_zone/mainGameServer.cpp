#include <iostream>

#include "ServerMgr.h"
#include <Framework.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include "Script/ScriptMgr.h"
#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include "Linkshell/LinkshellMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/HousingMgr.h"
#include "DebugCommand/DebugCommandHandler.h"
#include "Manager/PlayerMgr.h"
#include "Manager/ShopMgr.h"

#include <Config/ConfigMgr.h>

Sapphire::Framework g_fw;

using namespace Sapphire;
using namespace Sapphire::World;

bool setupFramework()
{
  auto pServer = std::make_shared< ServerMgr >( "config.ini" );
  auto pLogger = std::make_shared< Logger >();
  auto pExdData = std::make_shared< Data::ExdDataGenerated >();
  auto pScript = std::make_shared< Scripting::ScriptMgr >();
  auto pDb = std::make_shared< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pLsMgr = std::make_shared< LinkshellMgr >();
  auto pHousingMgr = std::make_shared< Manager::HousingMgr >();
  auto pTeriMgr = std::make_shared< Manager::TerritoryMgr >();
  auto pDebugCom = std::make_shared< DebugCommandHandler >();
  auto pConfig = std::make_shared< ConfigMgr >();
  auto pPlayerMgr = std::make_shared< Manager::PlayerMgr >();
  auto pShopMgr = std::make_shared< Manager::ShopMgr >();

  pLogger->setLogPath( "log/SapphireZone" );
  pLogger->init();

  g_fw.set< ServerMgr >( pServer );
  g_fw.set< Logger >( pLogger );
  g_fw.set< Data::ExdDataGenerated >( pExdData );
  g_fw.set< Scripting::ScriptMgr >( pScript );
  g_fw.set< Db::DbWorkerPool< Db::ZoneDbConnection > >( pDb );
  g_fw.set< LinkshellMgr >( pLsMgr );
  g_fw.set< Manager::HousingMgr >( pHousingMgr );
  g_fw.set< Manager::TerritoryMgr >( pTeriMgr );
  g_fw.set< DebugCommandHandler >( pDebugCom );
  g_fw.set< ConfigMgr >( pConfig );
  g_fw.set< Manager::PlayerMgr >( pPlayerMgr );
  g_fw.set< Manager::ShopMgr >( pShopMgr );

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
