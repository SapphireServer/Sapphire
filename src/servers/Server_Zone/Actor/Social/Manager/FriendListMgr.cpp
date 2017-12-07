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

Core::Entity::Social::FriendListMgr::~FriendListMgr()
{

}

bool Social::FriendListMgr::init()
{
   return true;
}

Social::FriendListPtr Social::FriendListMgr::getPlayerFriendsList( uint32_t playerId )
{
   std::mt19937_64 engine( std::random_device{}( ) );
   std::uniform_int_distribution<uint64_t> distribution;
   auto ui64 = distribution( engine );

   FriendList nFriendList( ui64, playerId, 200, std::chrono::steady_clock::now() );

   FriendListPtr pFriendList = boost::make_shared< FriendList >( nFriendList );
   pFriendList->getCapacity();
   return pFriendList;
}