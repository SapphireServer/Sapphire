#include "../Group.h"
#include "GroupMgr.h"

Core::Entity::Group::GroupPtr Core::Entity::Group::GroupMgr::findGroupByInviteIdForPlayer( uint64_t playerId ) const
{
   auto it = m_invites.find( playerId );
   if( it != m_invites.end() )
   {
      return findGroupById( it->second );
   }
   return nullptr;
}

Core::Entity::Group::GroupPtr Core::Entity::Group::GroupMgr::findGroupById( uint64_t groupId ) const
{
   auto it = m_groups.find( groupId );
   if( it != m_groups.end() )
   {
      return it->second;
   }
   return nullptr;
}