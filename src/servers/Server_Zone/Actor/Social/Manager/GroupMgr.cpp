#include "../Group.h"
#include "GroupMgr.h"

using namespace Core::Entity;

Social::GroupMgr::GroupMgr()
{

}

Social::GroupMgr::~GroupMgr()
{

}

Social::GroupPtr Social::GroupMgr::findGroupByInviteIdForPlayer( uint64_t playerId ) const
{
   auto it = m_invites.find( playerId );
   if( it != m_invites.end() )
   {
      return findGroupById( it->second );
   }
   return nullptr;
}

Social::GroupPtr Social::GroupMgr::findGroupById( uint64_t groupId ) const
{
   auto it = m_groups.find( groupId );
   if( it != m_groups.end() )
   {
      return it->second;
   }
   return nullptr;
}

uint64_t Social::GroupMgr::generateGroupId()
{
   m_lastGroupId++;
   return m_lastGroupId;
}

bool Social::GroupMgr::hasInvite( uint64_t playerId ) const
{
   auto it = m_invites.find( playerId );
   if ( it != m_invites.end() )
   {
      return true;
   }
   return false;
}