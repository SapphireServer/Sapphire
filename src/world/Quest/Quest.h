#pragma once

#include <memory>
#include "Common.h"

namespace Sapphire::World
{

  class Quest : public std::enable_shared_from_this< Quest >
  {
  public:
    Quest();
    Quest( uint16_t questId, uint8_t seq, uint8_t flags );
    uint16_t getId() const;
    uint8_t getSeq() const;
    uint8_t getFlags() const;

    void setId( uint16_t id );
    void setSeq( uint8_t seq );
    void setFlags( uint8_t flags );

    uint8_t getUI8A() const;
    uint8_t getUI8B() const;
    uint8_t getUI8C() const;
    uint8_t getUI8D() const;
    uint8_t getUI8E() const;
    uint8_t getUI8F() const;
    uint8_t getUI8AH();
    uint8_t getUI8BH();
    uint8_t getUI8CH();
    uint8_t getUI8DH();
    uint8_t getUI8EH();
    uint8_t getUI8FH();
    uint8_t getUI8AL();
    uint8_t getUI8BL();
    uint8_t getUI8CL();
    uint8_t getUI8DL();
    uint8_t getUI8EL();
    uint8_t getUI8FL();
    uint16_t getUI16A();
    uint16_t getUI16B();
    uint16_t getUI16C();
    uint32_t getUI32A();
    bool getBitFlag8( uint8_t index );
    bool getBitFlag16( uint8_t index );
    bool getBitFlag24( uint8_t index );
    bool getBitFlag32( uint8_t index );
    bool getBitFlag40( uint8_t index );
    bool getBitFlag48( uint8_t index );
    void setUI8A( uint8_t val );
    void setUI8B( uint8_t val );
    void setUI8C( uint8_t val );
    void setUI8D( uint8_t val );
    void setUI8E( uint8_t val );
    void setUI8F( uint8_t val );
    void setUI8AH( uint8_t val );
    void setUI8BH( uint8_t val );
    void setUI8CH( uint8_t val );
    void setUI8DH( uint8_t val );
    void setUI8EH( uint8_t val );
    void setUI8FH( uint8_t val );
    void setUI8AL( uint8_t val );
    void setUI8BL( uint8_t val );
    void setUI8CL( uint8_t val );
    void setUI8DL( uint8_t val );
    void setUI8EL( uint8_t val );
    void setUI8FL( uint8_t val );
    void setUI16A( uint16_t val );
    void setUI16B( uint16_t val );
    void setUI16C( uint16_t val );
    void setUI32A( uint32_t val );
    void setBitFlag8( uint8_t index, bool val );
    void setBitFlag16( uint8_t index, bool val );
    void setBitFlag24( uint8_t index, bool val );
    void setBitFlag32( uint8_t index, bool val );
    void setBitFlag40( uint8_t index, bool val );
    void setBitFlag48( uint8_t index, bool val );

    Common::QuestData getQuestData() const;

    bool operator==( const Quest& rhs ) const;
    bool operator!=( const Quest& rhs ) const;

  private:
    Common::QuestData m_data;
  };

}

