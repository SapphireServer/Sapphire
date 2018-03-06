#include <boost/make_shared.hpp>

#include "Framework.h"

Core::ServerZone g_serverZone( "config/settings_zone.xml" );

bool Core::Framework::initSocialGroups()
{
   g_friendListMgr = Core::Social::SocialMgr< Core::Social::FriendList >();
   return true;
}

Core::Logger& Core::Framework::getLogger()
{
   return g_log;
}

Core::DebugCommandHandler& Core::Framework::getDebugCommandHandler()
{
   return g_debugCmdHandler;
}

Core::Scripting::ScriptMgr& Core::Framework::getScriptMgr()
{
   return g_scriptMgr;
}

Core::Data::ExdDataGenerated& Core::Framework::getExdDataGen()
{
   return g_exdDataGen;
}

Core::TerritoryMgr& Core::Framework::getTerritoryMgr()
{
   return g_territoryMgr;
}

Core::LinkshellMgr& Core::Framework::getLinkshellMgr()
{
   return g_linkshellMgr;
}

Core::Db::DbWorkerPool< Core::Db::CharaDbConnection >& Core::Framework::getCharaDb()
{
   return g_charaDb;
}

Core::ServerZone& Core::Framework::getServerZone()
{
   return g_serverZone;
}

Core::Social::SocialMgr< Core::Social::FriendList > Core::Framework::getFriendsListMgr()
{
   return g_friendListMgr;
}