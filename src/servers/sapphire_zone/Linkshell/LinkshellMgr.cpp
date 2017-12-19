#include "LinkshellMgr.h"
#include <boost/make_shared.hpp>
#include <common/Logging/Logger.h>
#include <common/Database/DatabaseDef.h>

#include "Linkshell.h"

extern Core::Logger g_log;

Core::LinkshellMgr::LinkshellMgr()
{

}

bool Core::LinkshellMgr::loadLinkshells()
{

   auto res = g_charaDb.query( "SELECT LinkshellId, MasterCharacterId, CharacterIdList, "
                                      "LinkshellName, LeaderIdList, InviteIdList "
                                      "FROM infolinkshell "
                               "ORDER BY LinkshellId ASC;" );


   while( res->next() )
   {
      uint64_t linkshellId = res->getUInt64( 1 );
      uint32_t masterId = res->getUInt( 2 );
      std::string name = res->getString( 4 );

      auto func = []( std::set< uint64_t >& outList, std::vector< char >& inData )
      {
         if( inData.size() )
         {
            std::vector< uint64_t > list( inData.size() / 8 );
            outList.insert( list.begin(), list.end() );
         }
      };

      std::set< uint64_t > members;
      std::vector< char > membersBin;
      membersBin = res->getBlobVector( 3 );
      func( members, membersBin );

      std::set< uint64_t > leaders;
      std::vector< char > leadersBin;
      leadersBin = res->getBlobVector( 5 );
      func( members, leadersBin );

      std::set< uint64_t > invites;
      std::vector< char > invitesBin;
      invitesBin = res->getBlobVector( 6 );
      func( members, invitesBin );

      auto lsPtr = boost::make_shared< Linkshell >( linkshellId, name, masterId, members, leaders, invites );
      m_linkshellIdMap[linkshellId] = lsPtr;
      m_linkshellNameMap[name] = lsPtr;

   }

   return true;

}

Core::LinkshellPtr Core::LinkshellMgr::getLinkshellByName( const std::string& name )
{
   auto it = m_linkshellNameMap.find( name );
   if( it == m_linkshellNameMap.end() )
      return nullptr;
   else
      return it->second;
}

Core::LinkshellPtr Core::LinkshellMgr::getLinkshellById( uint64_t lsId )
{
   auto it = m_linkshellIdMap.find( lsId );
   if( it == m_linkshellIdMap.end() )
      return nullptr;
   else
      return it->second;
}
