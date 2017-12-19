#include <random>

#include <boost/make_shared.hpp>
#include <src/servers/Server_Common/Logging/Logger.h>

#include "../Group.h"
#include "../FriendList.h"
#include "FriendListMgr.h"

extern Core::Logger g_log;

using namespace Core::Entity;

Core::Entity::Social::FriendListMgr::FriendListMgr()
{

}  

bool Social::FriendListMgr::init()
{
   return true;
}

uint64_t Social::FriendListMgr::fetchPlayerFriendsList( uint32_t playerId )
{
   uint64_t newGroupId = generateGroupId();

   auto pFriendList = boost::make_shared< FriendList >( newGroupId, playerId );

   m_groups.emplace( newGroupId, pFriendList );

   g_log.debug( std::to_string( m_groups.size() ) );

   return newGroupId;
}