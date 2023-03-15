#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Exd/ExdData.h>
#include <Service.h>

#include "Manager/QuestMgr.h"
#include "Manager/MapMgr.h"

#include "Player.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::World;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void Player::finishQuest( uint16_t questId, uint32_t optionalChoice )
{
  removeQuest( questId );

  auto& questMgr = Common::Service< Manager::QuestMgr >::ref();

  updateQuestsCompleted( questId );

  //@todo should probably be changed to a bool function in case reward can not be obtained as quests will not complete in that case
  questMgr.onCompleteQuest( *this, questId, optionalChoice );
}

void Player::unfinishQuest( uint16_t questId )
{
  removeQuestsCompleted( questId );
  auto& questMgr = Common::Service< Manager::QuestMgr >::ref();
  questMgr.sendQuestsInfo( *this );
}

void Player::removeQuest( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );

  if( idx == -1 )
  {
    Logger::error( "QuestId#{0} not found in active quest list!", questId );
    return;
  }

  auto& questMgr = Common::Service< Manager::QuestMgr >::ref();
  auto& mapMgr = Common::Service< Manager::MapMgr >::ref();

  m_quests[ idx ] = World::Quest();
  removeQuestTracking( idx );
  deleteDbQuest( questId );

  mapMgr.updateQuests( *this );
  questMgr.onRemoveQuest( *this, idx );

}

void Player::removeQuestTracking( int8_t idx )
{
  for( int32_t ii = 0; ii < 5; ii++ )
  {
    if( m_questTracking[ ii ] == idx )
      m_questTracking[ ii ] = -1;
  }
}

bool Player::hasQuest( uint32_t questId )
{
  return ( getQuestIndex( static_cast< uint16_t >( questId ) ) > -1 );
}

int8_t Player::getQuestIndex( uint16_t questId )
{
  for( size_t pos = 0; pos < 30; ++pos )
  {
    if( m_quests[ pos ].getId() == questId )
      return static_cast< int8_t >( pos );
  }
  return -1;
}

void Player::updateQuest( const World::Quest& quest )
{
  auto& questMgr = Common::Service< World::Manager::QuestMgr >::ref();
  auto& mapMgr = Common::Service< World::Manager::MapMgr >::ref();

  if( hasQuest( quest.getId() ) )
  {
    uint8_t index = getQuestIndex( quest.getId() );
    m_quests[ index ] = quest;
    mapMgr.updateQuests( *this );
    questMgr.onUpdateQuest( *this, index );
  }
  else if( quest.getSeq() != 0 )
    addQuest( quest );
}

bool Player::addQuest( const World::Quest& quest )
{
  int8_t idx = getFreeQuestSlot();

  if( idx == -1 )
  {
    Logger::error( "No free slot for additional quests" );
    return false;
  }

  auto& questMgr = Common::Service< Manager::QuestMgr >::ref();
  auto& mapMgr = Common::Service< Manager::MapMgr >::ref();

  m_quests[ idx ] = quest;

  insertDbQuest( quest, idx );
  addQuestTracking( idx );

  mapMgr.updateQuests( *this );
  questMgr.onUpdateQuest( *this, idx );

  return true;
}

std::optional< World::Quest > Player::getQuest( uint32_t questId )
{
  if( !hasQuest( questId ) )
    return std::nullopt;

  auto idx = getQuestIndex( questId );

  auto quest = getQuestByIndex( idx );
  return { quest };
}

int8_t Player::getFreeQuestSlot()
{
  int8_t result = -1;
  for( int8_t idx = 0; idx < 30; idx++ )
    if( m_quests[ idx ].getId() == 0 )
    {
      result = idx;
      break;
    }

  return result;
}

void Player::addQuestTracking( uint8_t idx )
{
  for( int32_t ii = 0; ii < 5; ii++ )
  {
    if( m_questTracking[ ii ] == -1 )
    {
      m_questTracking[ ii ] = idx;
      break;
    }
  }
}

void Player::updateQuestsCompleted( uint32_t questId )
{
  uint8_t index = questId / 8;
  uint8_t bitIndex = ( questId ) % 8;

  uint8_t value = 0x80 >> bitIndex;

  m_questCompleteFlags[ index ] |= value;
}

bool Player::isQuestCompleted( uint32_t questId )
{
  uint8_t index = questId / 8;
  uint8_t bitIndex = ( questId ) % 8;

  uint8_t value = 0x80 >> bitIndex;

  return m_questCompleteFlags[ index ] & value;
} 

void Player::removeQuestsCompleted( uint32_t questId )
{
  uint8_t index = questId / 8;
  uint8_t bitIndex = ( questId ) % 8;

  uint8_t value = 0x80 >> bitIndex;

  m_questCompleteFlags[ index ] ^= value;

  Common::Service< Manager::MapMgr >::ref().updateQuests( *this );
}

World::Quest& Player::getQuestByIndex( uint16_t index )
{
  return m_quests[ index ];
}

std::array< World::Quest, 30 >& Player::getQuestArrayRef()
{
  return m_quests;
}

int16_t Player::getQuestTracking( uint8_t index ) const
{
  if( index < 0 || index >= 5 )
    return -1;
  return m_questTracking[ index ];
}

Player::QuestComplete& Player::getQuestCompleteFlags()
{
  return m_questCompleteFlags;
}







