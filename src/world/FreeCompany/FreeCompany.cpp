#include "FreeCompany.h"

#include <utility>

using namespace Sapphire;

FreeCompany::FreeCompany( uint64_t id, std::string name, std::string tag, uint64_t masterId, uint64_t chatChannelId ) :
  m_id( id ),
  m_name( std::move( name ) ),
  m_tag( std::move( tag ) ),
  m_chatChannelId( chatChannelId ),
  m_masterCharacterId( masterId )
{

}

uint64_t FreeCompany::getId() const
{
  return m_id;
}

const std::string& FreeCompany::getName() const
{
  return m_name;
}

void FreeCompany::setName( std::string name )
{
  m_name = std::move( name );
}

const std::string& FreeCompany::getTag() const
{
  return m_tag;
}

void FreeCompany::setTag( std::string tag )
{
  m_tag = std::move( tag );
}

uint64_t FreeCompany::getMasterId() const
{
  return m_masterCharacterId;
}

void FreeCompany::setMasterId( uint64_t masterId )
{
  m_masterCharacterId = masterId;
}

uint64_t FreeCompany::getCredit() const
{
  return m_credit;
}

void FreeCompany::setCredit( uint64_t credit )
{
  m_credit = credit;
}

uint64_t FreeCompany::getCreditAccumulated() const
{
  return m_creditAccumulated;
}

void FreeCompany::setCreditAccumulated( uint64_t credit )
{
  m_creditAccumulated = credit;
}

uint8_t FreeCompany::getRank() const
{
  return m_rank;
}

void FreeCompany::setRank( uint8_t rank )
{
  m_rank = rank;
}

uint64_t FreeCompany::getPoints() const
{
  return m_points;
}

void FreeCompany::setPoints( uint64_t points )
{
  m_points = points;
}

uint64_t FreeCompany::getCrest() const
{
  return m_crest;
}

void FreeCompany::setCrest( uint64_t crest )
{
  m_crest = crest;
}

uint32_t FreeCompany::getCreateDate() const
{
  return m_createDate;
}

void FreeCompany::setCreateDate( uint32_t createDate )
{
  m_createDate = createDate;
}

uint8_t FreeCompany::getGrandCompany() const
{
  return m_gc;
}

void FreeCompany::setGrandCompany( uint8_t gcIndex )
{
  if( gcIndex > 2 )
    return;
  m_gc = gcIndex;
}

uint64_t FreeCompany::getGcReputation( uint8_t gcIndex ) const
{
  if( gcIndex > 2 )
    return 0;
  return m_gcReputation[ gcIndex ];
}

void FreeCompany::setGcReputation( uint8_t gcIndex, uint64_t reputation )
{
  if( gcIndex > 2 )
    return;
  m_gcReputation[ gcIndex ] = reputation;
}

Common::FreeCompanyStatus FreeCompany::getFcStatus() const
{
  return m_status;
}

void FreeCompany::setFcStatus( Common::FreeCompanyStatus status )
{
  m_status = status;
}

const std::string& FreeCompany::getFcBoard() const
{
  return m_fcBoard;
}

void FreeCompany::setFcBoard( const std::string& board )
{
  m_fcBoard = board;
}

const std::string& FreeCompany::getFcMotto() const
{
  return m_fcMotto;
}

void FreeCompany::setFcMotto( const std::string& motto )
{
  m_fcMotto = motto;
}

uint32_t FreeCompany::getFcVersion() const
{
  return m_fcVersion;
}

void FreeCompany::setFcVersion( uint32_t version )
{
  m_fcVersion = version;
}

const std::array< uint64_t, 3 >& FreeCompany::getActiveActionIdArr() const
{
  return m_activeActionId;
}

const std::array< uint64_t, 3 >& FreeCompany::getActiveActionTimeLeftArr() const
{
  return m_activeActionTimeLeft;
}

const std::array< uint64_t, 15 >& FreeCompany::getActionStockArr() const
{
  return m_actionStock;
}

uint64_t FreeCompany::getChatChannel() const
{
  return m_chatChannelId;
}

const std::set< uint64_t >& FreeCompany::getMemberIdList() const
{
  return m_memberIds;
}

std::set< uint64_t >& FreeCompany::getMemberIdList()
{
  return m_memberIds;
}

void FreeCompany::addMember( uint64_t memberId, uint8_t hierarchyId, uint32_t lastLogout )
{
  FcMember member{ memberId, hierarchyId, lastLogout };
  m_memberDetails[ memberId ] = member;
  m_memberIds.insert( memberId );
}

void FreeCompany::removeMember( uint64_t memberId )
{
  m_memberDetails.erase( memberId );
  m_memberIds.erase( memberId );
}

void FreeCompany::setChatChannel( uint64_t chatChannelId )
{
  m_chatChannelId = chatChannelId;
}



