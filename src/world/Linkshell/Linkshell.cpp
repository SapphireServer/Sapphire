#include "Linkshell.h"

#include <utility>

Sapphire::Linkshell::Linkshell( uint64_t id, std::string name, uint64_t chatChannelId,
                                uint64_t masterId, std::set< uint64_t >  members, std::set< uint64_t >  leaders,
                                std::set< uint64_t >  invites ) :
  m_linkshellId( id ),
  m_name( std::move( name ) ),
  m_chatChannelId( chatChannelId ),
  m_masterCharacterId( masterId ),
  m_memberIds( std::move( members ) ),
  m_leaderIds( std::move( leaders ) ),
  m_inviteIds( std::move( invites ) )
{

}

uint64_t Sapphire::Linkshell::getId() const
{
  return m_linkshellId;
}

uint64_t Sapphire::Linkshell::getMasterId() const
{
  return m_masterCharacterId;
}

const std::set< uint64_t >& Sapphire::Linkshell::getMemberIdList() const
{
  return m_memberIds;
}

std::set< uint64_t >& Sapphire::Linkshell::getMemberIdList()
{
  return m_memberIds;
}

const std::string& Sapphire::Linkshell::getName() const
{
  return m_name;
}

const std::set< uint64_t >& Sapphire::Linkshell::getLeaderIdList() const
{
  return m_leaderIds;
}

std::set< uint64_t >& Sapphire::Linkshell::getLeaderIdList()
{
  return m_leaderIds;
}

const std::set< uint64_t >& Sapphire::Linkshell::getInviteIdList() const
{
  return m_inviteIds;
}

std::set< uint64_t >& Sapphire::Linkshell::getInviteIdList()
{
  return m_inviteIds;
}

uint64_t Sapphire::Linkshell::getChatChannel() const
{
  return m_chatChannelId;
}

void Sapphire::Linkshell::addMember( uint64_t memberId )
{
  m_memberIds.insert( memberId );
}

void Sapphire::Linkshell::removeMember( uint64_t memberId )
{
  m_memberIds.erase( memberId );
  m_leaderIds.erase( memberId );
  m_inviteIds.erase( memberId );
}

void Sapphire::Linkshell::addLeader( uint64_t memberId )
{
  m_leaderIds.insert( memberId );
}

void Sapphire::Linkshell::removeLeader( uint64_t memberId )
{
  m_leaderIds.erase( memberId );
}

void Sapphire::Linkshell::addInvite( uint64_t memberId )
{
  m_inviteIds.insert( memberId );
}

void Sapphire::Linkshell::removeInvite( uint64_t memberId )
{
  m_inviteIds.erase( memberId );
}

void Sapphire::Linkshell::setMasterId( uint64_t masterId )
{
  m_masterCharacterId = masterId;
}

void Sapphire::Linkshell::setName( std::string name )
{
  m_name = std::move( name );
}



