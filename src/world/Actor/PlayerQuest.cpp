#include <Common.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Exd/ExdData.h>
#include <Network/PacketContainer.h>
#include <Service.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/Notice2Packet.h"

#include "Manager/QuestMgr.h"

#include "Session.h"
#include "Player.h"


using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void Sapphire::Entity::Player::finishQuest( uint16_t questId, uint32_t optionalChoice )
{
  removeQuest( questId );

  auto& questMgr = Common::Service< World::Manager::QuestMgr >::ref();

  //@todo should probably be changed to a bool function in case reward can not be obtained as quests will not complete in that case
  questMgr.onCompleteQuest( *this, questId, optionalChoice );

  updateQuestsCompleted( questId );
}

void Sapphire::Entity::Player::unfinishQuest( uint16_t questId )
{
  removeQuestsCompleted( questId );
  auto& questMgr = Common::Service< World::Manager::QuestMgr >::ref();
  questMgr.sendQuestsInfo( *this );
}

void Sapphire::Entity::Player::removeQuest( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );

  if( idx == -1 )
  {
    Logger::error( "QuestId#{0} not found in active quest list!", questId );
    return;
  }

  auto& questMgr = Common::Service< World::Manager::QuestMgr >::ref();

  m_quests[ idx ] = World::Quest();
  removeQuestTracking( idx );
  deleteDbQuest( questId );

  questMgr.onRemoveQuest( *this, idx );

}

void Sapphire::Entity::Player::removeQuestTracking( int8_t idx )
{
  for( int32_t ii = 0; ii < 5; ii++ )
  {
    if( m_questTracking[ ii ] == idx )
      m_questTracking[ ii ] = -1;
  }
}

bool Sapphire::Entity::Player::hasQuest( uint32_t questId )
{
  return ( getQuestIndex( static_cast< uint16_t >( questId ) ) > -1 );
}

int8_t Sapphire::Entity::Player::getQuestIndex( uint16_t questId )
{
  for( size_t pos = 0; pos < 30; ++pos )
  {
    if( m_quests[ pos ].getId() == questId )
      return static_cast< int8_t >( pos );
  }
  return -1;
}

void Sapphire::Entity::Player::updateQuest( const World::Quest& quest )
{
  auto& questMgr = Common::Service< World::Manager::QuestMgr >::ref();

  if( hasQuest( quest.getId() ) )
  {
    uint8_t index = getQuestIndex( quest.getId() );
    m_quests[ index ] = quest;
    questMgr.onUpdateQuest( *this, index );
  }
  else
    addQuest( quest );
}

bool Sapphire::Entity::Player::addQuest( const World::Quest& quest )
{
  int8_t idx = getFreeQuestSlot();

  if( idx == -1 )
  {
    Logger::error( "No free slot for additional quests" );
    return false;
  }

  auto& questMgr = Common::Service< World::Manager::QuestMgr >::ref();

  m_quests[ idx ] = quest;

  insertDbQuest( quest, idx );
  addQuestTracking( idx );

  questMgr.onUpdateQuest( *this, idx );

  return true;
}

int8_t Sapphire::Entity::Player::getFreeQuestSlot()
{
  int8_t idx = 0;
  int result = -1;
  for( int8_t idx = 0; idx < 30; idx++ )
    if( m_quests[ idx ].getId() == 0 )
    {
      result = idx;
      break;
    }

  return result;
}

void Sapphire::Entity::Player::addQuestTracking( uint8_t idx )
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

void
Sapphire::Entity::Player::sendEventNotice( uint32_t questId, int8_t noticeId, uint8_t numOfArgs, uint32_t var1, uint32_t var2 )
{
  queuePacket( std::make_shared< Notice2Packet >( getAsPlayer(), questId, noticeId, numOfArgs, var1, var2 ) );
}

void Sapphire::Entity::Player::updateQuestsCompleted( uint32_t questId )
{
  uint8_t index = questId / 8;
  uint8_t bitIndex = ( questId ) % 8;

  uint8_t value = 0x80 >> bitIndex;

  m_questCompleteFlags[ index ] |= value;
}

void Sapphire::Entity::Player::removeQuestsCompleted( uint32_t questId )
{
  uint8_t index = questId / 8;
  uint8_t bitIndex = ( questId ) % 8;

  uint8_t value = 0x80 >> bitIndex;

  m_questCompleteFlags[ index ] ^= value;

}

Sapphire::World::Quest& Sapphire::Entity::Player::getQuestByIndex( uint16_t index )
{
  return m_quests[ index ];
}

std::array< Sapphire::World::Quest, 30 >& Sapphire::Entity::Player::getQuestArrayRef()
{
  return m_quests;
}

int16_t Sapphire::Entity::Player::getQuestTracking( uint8_t index ) const
{
  if( index < 0 || index >= 5 )
    return -1;
  return m_questTracking[ index ];
}

Sapphire::Entity::Player::QuestComplete& Sapphire::Entity::Player::getQuestCompleteFlags()
{
  return m_questCompleteFlags;
}







