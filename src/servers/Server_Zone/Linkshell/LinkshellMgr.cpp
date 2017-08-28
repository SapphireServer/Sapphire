#include "LinkshellMgr.h"
#include <Server_Common/Database/Database.h>
#include <Server_Common/Logging/Logger.h>
#include <boost/make_shared.hpp>

#include "Linkshell.h"

extern Core::Logger g_log;
extern Core::Db::Database g_database;

Core::LinkshellMgr::LinkshellMgr()
{

}

bool Core::LinkshellMgr::loadLinkshells()
{

   auto res = g_database.query( "SELECT LinkshellId, MasterCharacterId, CharacterIdList, "
                                        "LinkshellName, LeaderIdList, InviteIdList "
                                        "FROM infolinkshell "
                                "ORDER BY LinkshellId ASC;" );
   if( !res )
      return false;

   Db::Field *field = res->fetch();


   do
   {
      uint32_t linkshellId = field[0].getUInt32();
      uint32_t masterId = field[1].getUInt32();

      std::string name = field[3].getString();

      std::vector< uint64_t > characterIdList( field[2].getLength() / 8 );
      field[2].getBinary( reinterpret_cast< char* >( &characterIdList[0] ), field[2].getLength() );
      std::set< uint64_t > members( characterIdList.begin(), characterIdList.end() );

      //std::vector< uint64_t > leaderIdList( field[4].getLength() / 8 );
      //field[4].getBinary( reinterpret_cast< char* >( &leaderIdList[0] ), field[4].getLength() );
      //std::set< uint64_t > leaders( leaderIdList.begin(), leaderIdList.end() );

      std::set< uint64_t > leaders;

      //std::vector< uint64_t > inviteIdList( field[5].getLength() / 8 );
      //field[5].getBinary( reinterpret_cast< char* >( &leaderIdList[0] ), field[5].getLength() );
      //std::set< uint64_t > invites( inviteIdList.begin(), inviteIdList.end() );
      std::set< uint64_t > invites;

      auto lsPtr = boost::make_shared< Linkshell >( linkshellId, name, masterId, members, leaders, invites );
      m_linkshellIdMap[linkshellId] = lsPtr;
      m_linkshellNameMap[name] = lsPtr;

   } while( res->nextRow() );

   return true;

}
