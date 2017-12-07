#include "../Group.h"
#include "GroupMgr.h"

using namespace Core::Entity;

Social::GroupMgr::GroupMgr()
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

Social::GroupPtr Core::Entity::Social::GroupMgr::findGroupById( uint64_t groupId ) const
{
   auto it = m_groups.find( groupId );
   if( it != m_groups.end() )
   {
      return it->second;
   }
   return nullptr;
}