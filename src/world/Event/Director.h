#ifndef SAPPHIRE_DIRECTOR_H
#define SAPPHIRE_DIRECTOR_H

#include <Common.h>

#include "ForwardsZone.h"

namespace Sapphire::Event
{

  /*!
  \class Director
  \brief Base class for all Directors implements sequence and variables

  */

  class Director
  {

  public:
    enum DirectorType
    {
      BattleLeve = 0x8001,
      GatheringLeve = 0x8002,
      InstanceContent = 0x8003, // used for dungeons/raids
      PublicContent = 0x8004,
      QuestBattle = 0x8006,
      CompanyLeve = 0x8007,
      GoldSaucer = 0x800A,
      DpsChallange = 0x800D,
      Fate = 0x801A
    };

    enum DirectorState
    {
      Created,
      DutyReset,
      DutyInProgress,
      DutyFinished
    };

    Director( DirectorType type, uint16_t contentId );

    uint32_t getDirectorId() const;

    uint16_t getContentId() const;

    DirectorType getType() const;

    uint8_t getSequence() const;

    uint8_t getBranch() const;

    void sendDirectorInit( Entity::Player& player ) const;

    void sendDirectorClear( Entity::Player& player ) const;

    void sendDirectorVars( Entity::Player& player ) const;

    void setDirectorUI8AL( uint8_t value );

    void setDirectorUI8AH( uint8_t value );

    void setDirectorUI8BL( uint8_t value );

    void setDirectorUI8BH( uint8_t value );

    void setDirectorUI8CL( uint8_t value );

    void setDirectorUI8CH( uint8_t value );

    void setDirectorUI8DL( uint8_t value );

    void setDirectorUI8DH( uint8_t value );

    void setDirectorUI8EL( uint8_t value );

    void setDirectorUI8EH( uint8_t value );

    void setDirectorUI8FL( uint8_t value );

    void setDirectorUI8FH( uint8_t value );

    void setDirectorUI8GL( uint8_t value );

    void setDirectorUI8GH( uint8_t value );

    void setDirectorUI8HL( uint8_t value );

    void setDirectorUI8HH( uint8_t value );

    void setDirectorUI8IL( uint8_t value );

    void setDirectorUI8IH( uint8_t value );

    void setDirectorUI8JL( uint8_t value );

    void setDirectorUI8JH( uint8_t value );

    void setDirectorSequence( uint8_t value );

    void setDirectorBranch( uint8_t value );

  private:
    /*! Id of the content of the director */
    uint16_t m_contentId;

    /*! DirectorType | ContentId */
    uint32_t m_directorId;

    /*! currect sequence */
    uint8_t m_sequence;

    /*! current branch */
    uint8_t m_branch;

    union
    {
      struct UI8LH
      {
        uint8_t UI8AL : 4;
        uint8_t UI8AH : 4;
        uint8_t UI8BL : 4;
        uint8_t UI8BH : 4;
        uint8_t UI8CL : 4;
        uint8_t UI8CH : 4;
        uint8_t UI8DL : 4;
        uint8_t UI8DH : 4;
        uint8_t UI8EL : 4;
        uint8_t UI8EH : 4;
        uint8_t UI8FL : 4;
        uint8_t UI8FH : 4;
        uint8_t UI8GL : 4;
        uint8_t UI8GH : 4;
        uint8_t UI8HL : 4;
        uint8_t UI8HH : 4;
        uint8_t UI8IL : 4;
        uint8_t UI8IH : 4;
        uint8_t UI8JL : 4;
        uint8_t UI8JH : 4;
      } ui8lh;

      struct UI8
      {
        uint8_t UI8A;
        uint8_t UI8B;
        uint8_t UI8C;
        uint8_t UI8D;
        uint8_t UI8E;
        uint8_t UI8F;
        uint8_t UI8G;
        uint8_t UI8H;
        uint8_t UI8I;
        uint8_t UI8J;
      } ui8;

      struct FLAGS
      {
        uint8_t flags80;
        uint8_t flags72;
        uint8_t flags64;
        uint8_t flags56;
        uint8_t flags48;
        uint8_t flags40;
        uint8_t flags32;
        uint8_t flags24;
        uint8_t flags16;
        uint8_t flags8;
      } flags;

      /*! raw storage for flags/vars */
      uint8_t arrData[10];
    } m_unionData;

    /*! type of the director */
    DirectorType m_type;

    uint32_t m_elapsedTime;


  };

}

#endif //SAPPHIRE_DIRECTOR_H
