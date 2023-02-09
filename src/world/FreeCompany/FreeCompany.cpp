#include "FreeCompany.h"

#include <utility>

Sapphire::FreeCompany::FreeCompany( uint64_t id, std::string name, std::string tag, uint64_t masterId, uint64_t chatChannelId ) :
  m_id( id ),
  m_name( std::move( name ) ),
  m_tag( std::move( tag ) ),
  m_chatChannelId( chatChannelId ),
  m_masterCharacterId( masterId )
{

}

uint64_t Sapphire::FreeCompany::getId() const
{
  return m_id;
}

const std::string& Sapphire::FreeCompany::getName() const
{
  return m_name;
}

void Sapphire::FreeCompany::setName( std::string name )
{
  m_name = std::move( name );
}

const std::string& Sapphire::FreeCompany::getTag() const
{
  return m_tag;
}

void Sapphire::FreeCompany::setTag( std::string tag )
{
  m_tag = std::move( tag );
}

uint64_t Sapphire::FreeCompany::getMasterId() const
{
  return m_masterCharacterId;
}

void Sapphire::FreeCompany::setMasterId( uint64_t masterId )
{
  m_masterCharacterId = masterId;
}

uint64_t Sapphire::FreeCompany::getCredit() const
{
  return m_credit;
}

void Sapphire::FreeCompany::setCredit( uint64_t credit )
{
  m_credit = credit;
}

uint64_t Sapphire::FreeCompany::getCreditAccumulated() const
{
  return m_creditAccumulated;
}

void Sapphire::FreeCompany::setCreditAccumulated( uint64_t credit )
{
  m_creditAccumulated = credit;
}

uint8_t Sapphire::FreeCompany::getRank() const
{
  return m_rank;
}

void Sapphire::FreeCompany::setRank( uint8_t rank )
{
  m_rank = rank;
}

uint64_t Sapphire::FreeCompany::getPoints() const
{
  return m_points;
}

void Sapphire::FreeCompany::setPoints( uint64_t points )
{
  m_points = points;
}

uint64_t Sapphire::FreeCompany::getCrest() const
{
  return m_crest;
}

void Sapphire::FreeCompany::setCrest( uint64_t crest )
{
  m_crest = crest;
}

uint32_t Sapphire::FreeCompany::getCreateDate() const
{
  return m_createDate;
}

void Sapphire::FreeCompany::setCreateDate( uint32_t createDate )
{
  m_createDate = createDate;
}

uint8_t Sapphire::FreeCompany::getGrandCompany() const
{
  return m_gc;
}

void Sapphire::FreeCompany::setGrandCompany( uint8_t gcIndex )
{
  if( gcIndex > 2 )
    return;
  m_gc = gcIndex;
}

uint64_t Sapphire::FreeCompany::getGcReputation( uint8_t gcIndex ) const
{
  if( gcIndex > 2 )
    return 0;
  return m_gcReputation[ gcIndex ];
}

void Sapphire::FreeCompany::setGcReputation( uint8_t gcIndex, uint64_t reputation )
{
  if( gcIndex > 2 )
    return;
  m_gcReputation[ gcIndex ] = reputation;
}

Sapphire::Common::FreeCompanyStatus Sapphire::FreeCompany::getFcStatus() const
{
  return m_status;
}

void Sapphire::FreeCompany::setFcStatus( Sapphire::Common::FreeCompanyStatus status )
{
  m_status = status;
}

const std::string& Sapphire::FreeCompany::getFcBoard() const
{
  return m_fcBoard;
}

void Sapphire::FreeCompany::setFcBoard( const std::string& board )
{
  m_fcBoard = board;
}

const std::string& Sapphire::FreeCompany::getFcMotto() const
{
  return m_fcMotto;
}

void Sapphire::FreeCompany::setFcMotto( const std::string& motto )
{
  m_fcMotto = motto;
}

uint32_t Sapphire::FreeCompany::getFcVersion() const
{
  return m_fcVersion;
}

void Sapphire::FreeCompany::setFcVersion( uint32_t version )
{
  m_fcVersion = version;
}

const std::array< uint64_t, 3 >& Sapphire::FreeCompany::getActiveActionIdArr() const
{
  return m_activeActionId;
}

const std::array< uint64_t, 3 >& Sapphire::FreeCompany::getActiveActionTimeLeftArr() const
{
  return m_activeActionTimeLeft;
}

const std::array< uint64_t, 15 >& Sapphire::FreeCompany::getActionStockArr() const
{
  return m_actionStock;
}

uint64_t Sapphire::FreeCompany::getChatChannel() const
{
  return m_chatChannelId;
}

const std::set< uint64_t >& Sapphire::FreeCompany::getMemberIdList() const
{
  return m_memberIds;
}

std::set< uint64_t >& Sapphire::FreeCompany::getMemberIdList()
{
  return m_memberIds;
}

void Sapphire::FreeCompany::addInvite( uint64_t memberId )
{

}

void Sapphire::FreeCompany::addMember( uint64_t memberId, uint8_t hierarchyId, uint32_t lastLogout )
{
  FcMember member{ memberId, hierarchyId, lastLogout };
  m_memberDetails[ memberId ] = member;
  m_memberIds.insert( memberId );
}

void Sapphire::FreeCompany::setChatChannel( uint64_t chatChannelId )
{
  m_chatChannelId = chatChannelId;
}



