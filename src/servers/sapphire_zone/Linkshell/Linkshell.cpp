#include "Linkshell.h"


Sapphire::Linkshell::Linkshell( uint64_t id,
                            const std::string& name,
                            uint64_t masterId,
                            const std::set< uint64_t >& members,
                            const std::set< uint64_t >& leaders,
                            const std::set< uint64_t >& invites ) :
  m_linkshellId( id ),
  m_name( name ),
  m_masterCharacterId( masterId ),
  m_memberIds( members ),
  m_leaderIds( leaders ),
  m_inviteIds( invites )
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

void Sapphire::Linkshell::addMember( uint64_t memberId )
{
  m_memberIds.insert( memberId );
}

void Sapphire::Linkshell::removeMember( uint64_t memberId )
{
  m_memberIds.erase( memberId );
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



