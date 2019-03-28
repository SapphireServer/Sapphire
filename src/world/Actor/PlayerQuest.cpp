#include <Common.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/PacketContainer.h>

#include "Network/GameConnection.h"
#include "Network/PacketWrappers/QuestMessagePacket.h"

#include "Session.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

void Sapphire::Entity::Player::finishQuest( uint16_t questId )
{

  int8_t idx = getQuestIndex( questId );

  removeQuest( questId );
  updateQuestsCompleted( questId );

  sendQuestTracker();

}

void Sapphire::Entity::Player::unfinishQuest( uint16_t questId )
{
  removeQuestsCompleted( questId );
  sendQuestInfo();
}

void Sapphire::Entity::Player::removeQuest( uint16_t questId )
{

  int8_t idx = getQuestIndex( questId );

  if( ( idx != -1 ) && ( m_activeQuests[ idx ] != nullptr ) )
  {

    auto questUpdatePacket = makeZonePacket< FFXIVIpcQuestUpdate >( getId() );
    questUpdatePacket->data().slot = static_cast< uint8_t >( idx );
    questUpdatePacket->data().questInfo.c.questId = 0;
    questUpdatePacket->data().questInfo.c.sequence = 0xFF;
    queuePacket( questUpdatePacket );

    auto questFinishPacket = makeZonePacket< FFXIVIpcQuestFinish >( getId() );
    questFinishPacket->data().questId = questId;
    questFinishPacket->data().flag1 = 1;
    questFinishPacket->data().flag2 = 1;
    queuePacket( questFinishPacket );

    for( int32_t ii = 0; ii < 5; ii++ )
    {
      if( m_questTracking[ ii ] == idx )
        m_questTracking[ ii ] = -1;
    }

    std::shared_ptr< QuestActive > pQuest = m_activeQuests[ idx ];
    m_activeQuests[ idx ].reset();

    m_questIdToQuestIdx.erase( questId );
    m_questIdxToQuestId.erase( idx );

    deleteQuest( questId );
  }

  sendQuestTracker();

}

bool Sapphire::Entity::Player::hasQuest( uint32_t questId )
{
  return ( getQuestIndex( static_cast< uint16_t >( questId ) ) > -1 );
}

int8_t Sapphire::Entity::Player::getQuestIndex( uint16_t questId )
{
  auto it = m_questIdToQuestIdx.find( questId );
  if( it != m_questIdToQuestIdx.end() )
    return it->second;

  return -1;
}

bool Sapphire::Entity::Player::getQuestBitFlag8( uint16_t questId, uint8_t index )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->a.BitFlag8 & ( 1 << index );
  }

  return false;
}

bool Sapphire::Entity::Player::getQuestBitFlag16( uint16_t questId, uint8_t index )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->a.BitFlag16 & ( 1 << index );
  }

  return false;
}

bool Sapphire::Entity::Player::getQuestBitFlag24( uint16_t questId, uint8_t index )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->a.BitFlag24 & ( 1 << index );
  }

  return false;
}

bool Sapphire::Entity::Player::getQuestBitFlag32( uint16_t questId, uint8_t index )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->a.BitFlag32 & ( 1 << index );
  }

  return false;
}

bool Sapphire::Entity::Player::getQuestBitFlag40( uint16_t questId, uint8_t index )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->a.BitFlag40 & ( 1 << index );
  }

  return false;
}

bool Sapphire::Entity::Player::getQuestBitFlag48( uint16_t questId, uint8_t index )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->a.BitFlag48 & ( 1 << index );
  }

  return false;
}

uint8_t Sapphire::Entity::Player::getQuestUI8A( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->c.UI8A;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8B( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->c.UI8B;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8C( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->c.UI8C;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8D( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->c.UI8D;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8E( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->c.UI8E;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8F( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->c.UI8F;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8AH( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8AH;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8BH( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8BH;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8CH( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8CH;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8DH( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8DH;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8EH( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8EH;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8FH( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8FH;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8AL( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8AL;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8BL( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8BL;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8CL( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8CL;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8DL( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8DL;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8EL( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8EL;
  }

  return value;
}

uint8_t Sapphire::Entity::Player::getQuestUI8FL( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint8_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    value = pNewQuest->b.UI8FL;
  }

  return value;
}

uint16_t Sapphire::Entity::Player::getQuestUI16A( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint16_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    //   value = pNewQuest->d.UI16A;
  }

  return value;
}

uint16_t Sapphire::Entity::Player::getQuestUI16B( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint16_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    //   value = pNewQuest->d.UI16B;
  }

  return value;
}

uint16_t Sapphire::Entity::Player::getQuestUI16C( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint16_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    //  value = pNewQuest->d.UI16C;
  }

  return value;
}

uint32_t Sapphire::Entity::Player::getQuestUI32A( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );
  uint32_t value = 0;
  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    // value = pNewQuest->e.UI32A;
  }

  return value;
}

void Sapphire::Entity::Player::setQuestUI8A( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->c.UI8A = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8B( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->c.UI8B = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8C( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->c.UI8C = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8D( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->c.UI8D = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8E( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->c.UI8E = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8F( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->c.UI8F = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8AH( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8AH = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8BH( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8BH = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8CH( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8CH = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8DH( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8DH = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8EH( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8EH = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8FH( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8FH = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8AL( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8AL = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8BL( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8BL = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8CL( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8CL = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8DL( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8DL = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8EL( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8EL = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI8FL( uint16_t questId, uint8_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    pNewQuest->b.UI8FL = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI16A( uint16_t questId, uint16_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    //   pNewQuest->d.UI16A = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI16B( uint16_t questId, uint16_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    //  pNewQuest->d.UI16B = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI16C( uint16_t questId, uint16_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

//      pNewQuest->d.UI16C = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestUI32A( uint16_t questId, uint32_t val )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    // pNewQuest->e.UI32A = val;

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestBitFlag8( uint16_t questId, uint8_t index, bool val )
{
  int8_t idx = getQuestIndex( questId );

  uint8_t realIdx = 8 - index;

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    if( val )
      pNewQuest->a.BitFlag8 |= ( 1 << realIdx );
    else
      pNewQuest->a.BitFlag8 &= ~( 1 << realIdx );

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestBitFlag16( uint16_t questId, uint8_t index, bool val )
{
  int8_t idx = getQuestIndex( questId );

  uint8_t realIdx = 8 - index;

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    if( val )
      pNewQuest->a.BitFlag16 |= ( 1 << realIdx );
    else
      pNewQuest->a.BitFlag16 &= ~( 1 << realIdx );

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestBitFlag24( uint16_t questId, uint8_t index, bool val )
{
  int8_t idx = getQuestIndex( questId );

  uint8_t realIdx = 8 - index;

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    if( val )
      pNewQuest->a.BitFlag24 |= ( 1 << realIdx );
    else
      pNewQuest->a.BitFlag24 &= ~( 1 << realIdx );

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestBitFlag32( uint16_t questId, uint8_t index, bool val )
{
  int8_t idx = getQuestIndex( questId );

  uint8_t realIdx = 8 - index;

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    if( val )
      pNewQuest->a.BitFlag32 |= ( 1 << realIdx );
    else
      pNewQuest->a.BitFlag32 &= ~( 1 << realIdx );

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestBitFlag40( uint16_t questId, uint8_t index, bool val )
{
  int8_t idx = getQuestIndex( questId );

  uint8_t realIdx = 8 - index;

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    if( val )
      pNewQuest->a.BitFlag40 |= ( 1 << realIdx );
    else
      pNewQuest->a.BitFlag40 &= ~( 1 << realIdx );

    updateQuest( questId, pNewQuest->c.sequence );
  }
}

void Sapphire::Entity::Player::setQuestBitFlag48( uint16_t questId, uint8_t index, bool val )
{
  int8_t idx = getQuestIndex( questId );

  uint8_t realIdx = 8 - index;

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];

    if( val )
      pNewQuest->a.BitFlag48 |= ( 1 << realIdx );
    else
      pNewQuest->a.BitFlag48 &= ~( 1 << realIdx );

    updateQuest( questId, pNewQuest->c.sequence );
  }
}


uint8_t Sapphire::Entity::Player::getQuestSeq( uint16_t questId )
{
  int8_t idx = getQuestIndex( questId );

  if( idx != -1 )
  {
    std::shared_ptr< QuestActive > pNewQuest = m_activeQuests[ idx ];
    return pNewQuest->c.sequence;
  }
  return 0;
}

void Sapphire::Entity::Player::updateQuest( uint16_t questId, uint8_t sequence )
{
  if( hasQuest( questId ) )
  {
    uint8_t index = getQuestIndex( questId );
    auto pNewQuest = m_activeQuests[ index ];

    auto questUpdatePacket = makeZonePacket< FFXIVIpcQuestUpdate >( getId() );
    pNewQuest->c.sequence = sequence;
    questUpdatePacket->data().slot = index;
    questUpdatePacket->data().questInfo = *pNewQuest;
    queuePacket( questUpdatePacket );

  }
  else
  {

    uint8_t idx = 0;
    bool hasFreeSlot = false;
    for( ; idx < 30; idx++ )
      if( !m_activeQuests[ idx ] )
      {
        hasFreeSlot = true;
        break;
      }

    if( !hasFreeSlot )
      return;

    std::shared_ptr< QuestActive > pNewQuest( new QuestActive() );
    pNewQuest->c.questId = questId;
    pNewQuest->c.sequence = sequence;
    pNewQuest->c.padding = 0;
    m_activeQuests[ idx ] = pNewQuest;
    m_questIdToQuestIdx[ questId ] = idx;
    m_questIdxToQuestId[ idx ] = questId;

    auto questUpdatePacket = makeZonePacket< FFXIVIpcQuestUpdate >( getId() );
    questUpdatePacket->data().slot = idx;
    questUpdatePacket->data().questInfo = *pNewQuest;
    queuePacket( questUpdatePacket );

    for( int32_t ii = 0; ii < 5; ii++ )
    {
      if( m_questTracking[ ii ] == -1 )
      {
        m_questTracking[ ii ] = idx;
        break;
      }
    }

    insertQuest( questId, idx, sequence );
    sendQuestTracker();

  }
}

void Sapphire::Entity::Player::sendQuestTracker()
{
  auto trackerPacket = makeZonePacket< FFXIVIpcQuestTracker >( getId() );

  for( int32_t ii = 0; ii < 5; ii++ )
  {
    if( m_questTracking[ ii ] >= 0 )
    {
      trackerPacket->data().entry[ ii ].active = 1;
      trackerPacket->data().entry[ ii ].questIndex = static_cast< uint8_t >( m_questTracking[ ii ] );
    }
  }
  queuePacket( trackerPacket );
}

void Sapphire::Entity::Player::setQuestTracker( uint16_t index, int16_t flag )
{
  if( flag == 0 )
  {
    //remove
    for( uint8_t ii = 0; ii < 5; ii++ )
    {
      if( m_questTracking[ ii ] == index )
      {
        m_questTracking[ ii ] = -1;
        break;
      }
    }
  }
  else
  {
    //add
    for( uint8_t ii = 0; ii < 5; ii++ )
    {
      if( m_questTracking[ ii ] == -1 )
      {
        m_questTracking[ ii ] = index;
        break;
      }
    }
  }

}


void Sapphire::Entity::Player::sendQuestInfo()
{
  auto activeQuestListPacket = makeZonePacket< FFXIVIpcQuestActiveList >( getId() );

  for( int32_t i = 0; i < 30; i++ )
  {
    uint8_t offset = i * 12;
    if( m_activeQuests[ i ] != nullptr )
    {

      auto& quest = activeQuestListPacket->data().activeQuests[ i ];
      quest = *m_activeQuests[ i ];

    }
  }

  queuePacket( activeQuestListPacket );

  auto completeQuestListPacket = makeZonePacket< FFXIVIpcQuestCompleteList >( getId() );
  memcpy( completeQuestListPacket->data().questCompleteMask, m_questCompleteFlags, sizeof( m_questCompleteFlags ) );
  queuePacket( completeQuestListPacket );

  sendQuestTracker();
}

void
Sapphire::Entity::Player::sendQuestMessage( uint32_t questId, int8_t msgId, uint8_t type, uint32_t var1, uint32_t var2 )
{
  queuePacket( std::make_shared< QuestMessagePacket >( getAsPlayer(), questId, msgId, type, var1, var2 ) );
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

bool Sapphire::Entity::Player::giveQuestRewards( uint32_t questId, uint32_t optionalChoice )
{
  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  uint32_t playerLevel = getLevel();
  auto questInfo = pExdData->get< Sapphire::Data::Quest >( questId );


  if( !questInfo )
    return false;

  auto paramGrowth = pExdData->get< Sapphire::Data::ParamGrow >( questInfo->classJobLevel0 );

  // TODO: use the correct formula, this one is wrong
  uint32_t exp =
    ( questInfo->expFactor * paramGrowth->questExpModifier * ( 45 + 5 * questInfo->classJobLevel0 ) ) / 100;

  exp = questInfo->expFactor;

  auto rewardItemCount = questInfo->itemReward0.size();
  uint16_t optionalItemCount = static_cast< uint16_t >( questInfo->itemReward1.size() );

  uint32_t gilReward = questInfo->gilReward;

  // TODO: check if there is room in inventory, else return false;
  if( exp > 0 )
    gainExp( exp );

  if( rewardItemCount > 0 )
  {
    for( uint32_t i = 0; i < questInfo->itemReward0.size(); i++ )
    {
      addItem( questInfo->itemReward0.at( i ), questInfo->itemCountReward0.at( i ) );
    }
  }

  if( optionalItemCount > 0 )
  {
    auto itemId = questInfo->itemReward1.at( optionalChoice );
    addItem( itemId, questInfo->itemCountReward1.at( optionalChoice ) );
  }

  if( gilReward > 0 )
    addCurrency( CurrencyType::Gil, gilReward );

  return true;
}

std::shared_ptr< QuestActive > Sapphire::Entity::Player::getQuestActive( uint16_t index )
{
  return m_activeQuests[ index ];
}

