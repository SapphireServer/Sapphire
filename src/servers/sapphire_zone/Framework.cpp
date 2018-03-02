#include <boost/make_shared.hpp>

#include "Framework.h"

Core::ServerZone g_serverZone( "config/settings_zone.xml" );

Core::Logger& Core::Framework::getLogger()
{
   g_log.debug( "loogu" );
   return g_log;
}

Core::DebugCommandHandler& Core::Framework::getDebugCommandHandler()
{
   g_log.debug( "debugu" );
   return g_debugCmdHandler;
}

Core::Scripting::ScriptMgr& Core::Framework::getScriptMgr()
{
   g_log.debug( "sukiriputo" );
   return g_scriptMgr;
}

Core::Data::ExdDataGenerated& Core::Framework::getExdDataGen()
{
   g_log.debug( "ekkusudegen" );
   return g_exdDataGen;
}

Core::TerritoryMgr& Core::Framework::getTerritoryMgr()
{
   g_log.debug( "teriitoru" );
   return g_territoryMgr;
}

Core::LinkshellMgr& Core::Framework::getLinkshellMgr()
{
   g_log.debug( "linkusheru" );
   return g_linkshellMgr;
}

Core::Db::DbWorkerPool< Core::Db::CharaDbConnection >& Core::Framework::getCharaDb()
{
   g_log.debug( "chiyaradebee" );
   return g_charaDb;
}

Core::ServerZone& Core::Framework::getServerZone()
{
   g_log.debug( "seruvaa zone" );
   return g_serverZone;
}