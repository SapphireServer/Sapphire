#include "../Group.h"
#include "SocialMgr.h"


template< class T >
Core::Social::SocialMgr::GroupMgr()
{

}

Core::Social::SocialMgr::~GroupMgr()
{

}

T Core::Social::SocialMgr::findGroupByInviteIdForPlayer( uint64_t playerId ) const
{
   auto it = m_invites.find( playerId );
   if( it != m_invites.end() )
   {
      return findGroupById( it->second );
   }
   return nullptr;
}

T Core::Social::SocialMgr::findGroupById( uint64_t groupId ) const
{
   auto it = m_groups.find( groupId );
   if( it != m_groups.end() )
   {
      return it->second;
   }
   return nullptr;
}

uint64_t Core::Social::SocialMgr::GroupMgr::generateGroupId()
{
   m_lastGroupId++;
   return m_lastGroupId;
}

bool Core::Social::SocialMgr::hasInvite( uint64_t playerId ) const
{
   auto it = m_invites.find( playerId );
   if ( it != m_invites.end() )
   {
      return true;
   }
   return false;
}