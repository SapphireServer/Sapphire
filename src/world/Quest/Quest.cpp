#include "Quest.h"

Sapphire::World::Quest::Quest()
{
  m_data.a.questId = 0;
}

Sapphire::World::Quest::Quest( uint16_t questId, uint8_t seq, uint8_t flags )
{
  m_data.a.questId = questId;
  m_data.a.sequence = seq;
  m_data.a.flags = flags;
}

uint16_t Sapphire::World::Quest::getId() const
{
  return m_data.b.questId;
}

bool Sapphire::World::Quest::getBitFlag8( uint8_t index )
{
  return m_data.a.BitFlag8 & ( 1 << index );
}

bool Sapphire::World::Quest::getBitFlag16( uint8_t index )
{
  return m_data.a.BitFlag16 & ( 1 << index );
}

bool Sapphire::World::Quest::getBitFlag24( uint8_t index )
{
  return m_data.a.BitFlag24 & ( 1 << index );
}

bool Sapphire::World::Quest::getBitFlag32( uint8_t index )
{
  return m_data.a.BitFlag32 & ( 1 << index );
}

bool Sapphire::World::Quest::getBitFlag40( uint8_t index )
{
  return m_data.a.BitFlag40 & ( 1 << index );
}

bool Sapphire::World::Quest::getBitFlag48( uint8_t index )
{
  return m_data.a.BitFlag48 & ( 1 << index );
}

uint8_t Sapphire::World::Quest::getUI8A() const
{
  uint8_t value = 0;
  value = m_data.c.UI8A;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8B() const
{
  uint8_t value = 0;
  value = m_data.c.UI8B;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8C() const
{
  uint8_t value = 0;
  value = m_data.c.UI8C;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8D() const
{
  uint8_t value = 0;
  value = m_data.c.UI8D;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8E() const
{
  uint8_t value = 0;
  value = m_data.c.UI8E;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8F() const
{
  uint8_t value = 0;
  value = m_data.c.UI8F;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8AH()
{
  uint8_t value = 0;
  value = m_data.b.UI8AH;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8BH()
{
  uint8_t value = 0;
  value = m_data.b.UI8BH;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8CH()
{
  uint8_t value = 0;
  value = m_data.b.UI8CH;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8DH()
{
  uint8_t value = 0;
  value = m_data.b.UI8DH;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8EH()
{
  uint8_t value = 0;
  value = m_data.b.UI8EH;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8FH()
{
  uint8_t value = 0;
  value = m_data.b.UI8FH;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8AL()
{
  uint8_t value = 0;
  value = m_data.b.UI8AL;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8BL()
{
  uint8_t value = 0;
  value = m_data.b.UI8BL;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8CL()
{
  uint8_t value = 0;
  value = m_data.b.UI8CL;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8DL()
{
  uint8_t value = 0;
  value = m_data.b.UI8DL;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8EL()
{
  uint8_t value = 0;
  value = m_data.b.UI8EL;
  return value;
}

uint8_t Sapphire::World::Quest::getUI8FL()
{
  uint8_t value = 0;
  value = m_data.b.UI8FL;
  return value;
}

uint16_t Sapphire::World::Quest::getUI16A()
{
  uint16_t value = 0;
  return value;
}

uint16_t Sapphire::World::Quest::getUI16B()
{
  uint16_t value = 0;
  return value;
}

uint16_t Sapphire::World::Quest::getUI16C()
{
  uint16_t value = 0;
  return value;
}

uint32_t Sapphire::World::Quest::getUI32A()
{
  uint32_t value = 0;
  return value;
}

void Sapphire::World::Quest::setUI8A( uint8_t val )
{
  m_data.c.UI8A = val;
}

void Sapphire::World::Quest::setUI8B( uint8_t val )
{
  m_data.c.UI8B = val;
}

void Sapphire::World::Quest::setUI8C( uint8_t val )
{
  m_data.c.UI8C = val;
}

void Sapphire::World::Quest::setUI8D( uint8_t val )
{
  m_data.c.UI8D = val;
}

void Sapphire::World::Quest::setUI8E( uint8_t val )
{
  m_data.c.UI8E = val;
}

void Sapphire::World::Quest::setUI8F( uint8_t val )
{
  m_data.c.UI8F = val;
}

void Sapphire::World::Quest::setUI8AH( uint8_t val )
{
  m_data.b.UI8AH = val;
}

void Sapphire::World::Quest::setUI8BH( uint8_t val )
{
  m_data.b.UI8BH = val;
}

void Sapphire::World::Quest::setUI8CH( uint8_t val )
{
  m_data.b.UI8CH = val;
}

void Sapphire::World::Quest::setUI8DH( uint8_t val )
{
  m_data.b.UI8DH = val;
}

void Sapphire::World::Quest::setUI8EH( uint8_t val )
{
  m_data.b.UI8EH = val;
}

void Sapphire::World::Quest::setUI8FH( uint8_t val )
{
  m_data.b.UI8FH = val;
}

void Sapphire::World::Quest::setUI8AL( uint8_t val )
{
  m_data.b.UI8AL = val;
}

void Sapphire::World::Quest::setUI8BL( uint8_t val )
{
  m_data.b.UI8BL = val;
}

void Sapphire::World::Quest::setUI8CL( uint8_t val )
{
  m_data.b.UI8CL = val;
}

void Sapphire::World::Quest::setUI8DL( uint8_t val )
{
  m_data.b.UI8DL = val;
}

void Sapphire::World::Quest::setUI8EL( uint8_t val )
{
  m_data.b.UI8EL = val;
}

void Sapphire::World::Quest::setUI8FL( uint8_t val )
{
  m_data.b.UI8FL = val;
}

void Sapphire::World::Quest::setUI16A( uint16_t val )
{
}

void Sapphire::World::Quest::setUI16B( uint16_t val )
{
}

void Sapphire::World::Quest::setUI16C( uint16_t val )
{
}

void Sapphire::World::Quest::setUI32A( uint32_t val )
{
}

void Sapphire::World::Quest::setBitFlag8( uint8_t index, bool val )
{
  uint8_t realIdx = 8 - index;

  if( val )
    m_data.a.BitFlag8 |= ( 1 << realIdx );
  else
    m_data.a.BitFlag8 &= ~( 1 << realIdx );
}

void Sapphire::World::Quest::setBitFlag16( uint8_t index, bool val )
{
  uint8_t realIdx = 8 - index;

  if( val )
    m_data.a.BitFlag16 |= ( 1 << realIdx );
  else
    m_data.a.BitFlag16 &= ~( 1 << realIdx );
}

void Sapphire::World::Quest::setBitFlag24( uint8_t index, bool val )
{
  uint8_t realIdx = 8 - index;

  if( val )
    m_data.a.BitFlag24 |= ( 1 << realIdx );
  else
    m_data.a.BitFlag24 &= ~( 1 << realIdx );
}

void Sapphire::World::Quest::setBitFlag32( uint8_t index, bool val )
{
  uint8_t realIdx = 8 - index;

  if( val )
    m_data.a.BitFlag32 |= ( 1 << realIdx );
  else
    m_data.a.BitFlag32 &= ~( 1 << realIdx );
}

void Sapphire::World::Quest::setBitFlag40( uint8_t index, bool val )
{
  uint8_t realIdx = 8 - index;

  if( val )
    m_data.a.BitFlag40 |= ( 1 << realIdx );
  else
    m_data.a.BitFlag40 &= ~( 1 << realIdx );
}

void Sapphire::World::Quest::setBitFlag48( uint8_t index, bool val )
{
  uint8_t realIdx = 8 - index;

  if( val )
    m_data.a.BitFlag48 |= ( 1 << realIdx );
  else
    m_data.a.BitFlag48 &= ~( 1 << realIdx );
}


uint8_t Sapphire::World::Quest::getSeq() const
{
  return m_data.c.sequence;
}

uint8_t Sapphire::World::Quest::getFlags() const
{
  return m_data.c.flags;
}

void Sapphire::World::Quest::setSeq( uint8_t seq )
{
  m_data.a.sequence = seq;
}

void Sapphire::World::Quest::setFlags( uint8_t flags )
{
  m_data.a.flags = flags;
}

void Sapphire::World::Quest::setId( uint16_t id )
{
  m_data.a.questId = id;
}

Sapphire::Common::QuestData Sapphire::World::Quest::getQuestData() const
{
  return m_data;
}

bool Sapphire::World::Quest::operator==( const Sapphire::World::Quest &rhs ) const
{
  return ( m_data.a.questId == rhs.m_data.a.questId ) &&
         ( m_data.a.sequence == rhs.m_data.a.questId ) &&
         ( m_data.a.flags == rhs.m_data.a.flags ) &&
         ( m_data.a.BitFlag8 == rhs.m_data.a.BitFlag8 ) &&
         ( m_data.a.BitFlag16 == rhs.m_data.a.BitFlag16 ) &&
         ( m_data.a.BitFlag24 == rhs.m_data.a.BitFlag24 ) &&
         ( m_data.a.BitFlag32 == rhs.m_data.a.BitFlag32 ) &&
         ( m_data.a.BitFlag40 == rhs.m_data.a.BitFlag40 ) &&
         ( m_data.a.BitFlag48 == rhs.m_data.a.BitFlag48 );
}

bool Sapphire::World::Quest::operator!=( const Sapphire::World::Quest &rhs ) const
{
  return ( m_data.a.questId != rhs.m_data.a.questId ) ||
         ( m_data.a.sequence != rhs.m_data.a.questId ) ||
         ( m_data.a.flags != rhs.m_data.a.flags ) ||
         ( m_data.a.BitFlag8 != rhs.m_data.a.BitFlag8 ) ||
         ( m_data.a.BitFlag16 != rhs.m_data.a.BitFlag16 ) ||
         ( m_data.a.BitFlag24 != rhs.m_data.a.BitFlag24 ) ||
         ( m_data.a.BitFlag32 != rhs.m_data.a.BitFlag32 ) ||
         ( m_data.a.BitFlag40 != rhs.m_data.a.BitFlag40 ) ||
         ( m_data.a.BitFlag48 != rhs.m_data.a.BitFlag48 );
}
