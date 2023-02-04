#pragma once

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
      TreasureHunt = 0x8009,
      GoldSaucer = 0x800A,
      CompanyCraftDirector = 0x800B,
      DpsChallange = 0x800D,
      Fate = 0x801A
    };

    enum DirectorSetupFlags : uint8_t
    {
      ClearTodo = 0x01,
      Unknown02 = 0x02,
      Unknown04 = 0x04,
      Unknown08 = 0x08,
      Unknown10 = 0x10,
      Unknown20 = 0x20, //Do some chat msg
      Unknown40 = 0x40,
      Unknown80 = 0x80,
    };

    enum DirectorSceneId : uint8_t
    {
      Opening = 0x01,
      Enter = 0x02,
      Reset = 0x03,
      Cutscene = 0x04,
      Failed = 0x05,
      Complete = 0x06
    };

    enum DirectorState
    {
      Created,
      DutyReset,
      DutyInProgress,
      DutyFinished,
      DutyFailed
    };

    Director( DirectorType type, uint16_t contentId );

    uint32_t getDirectorId() const;

    uint16_t getContextId() const;

    DirectorType getType() const;

    uint8_t getSequence() const;

    uint8_t getFlags() const;

    void sendDirectorInit( Entity::Player& player ) const;

    void sendEventLogMessage( Sapphire::Entity::Player& player, Sapphire::InstanceContent& instance, uint32_t msgId, const std::initializer_list< uint32_t > args = {} ) const;

    void sendDirectorClear( Entity::Player& player ) const;

    void sendDirectorVars( Entity::Player& player ) const;

    void setDirectorSequence( uint8_t value );

    void setDirectorFlags( uint8_t value );

    /*!
     * @brief Sets a value of a director var
     * @param index of var to set
     * @param value to set
     */
    void setDirectorVar( uint8_t index, uint8_t value );

    /*!
     * @brief Sets a value of a director var
     * @param index of var to set
     * @param value to set left shifted. Just first 4 bits. Discards last bits
     * @param value to set right shifted. Just first 4 bits. Discards last bits
     */
    void setDirectorVar( uint8_t index, uint8_t valueLeft, uint8_t valueRight );

    /*!
     * @brief Sets a value of a custom var
     * @param index of var to set 
     * @param value to set
     */
    void setCustomVar( uint32_t index, uint64_t value );

    /*!
     * @brief Gets a value of a director var
     * @param index of var to get
     * @return 8 bits of selected index
     */
    uint8_t getDirectorVar( uint8_t index );

    /*!
     * @brief Gets a value of a director var in 4 bits
     * @param index of var to get
     * @param shiftLeft if true, last 4 bits otherwise first 4 bits
     * @return 4 bits of selected index
     */
    uint8_t getDirectorVar( uint8_t index, bool shiftLeft );

    /*!
     * @brief Gets a value of a custom var
     * @param index of var to get
     * @return custom var
     */
    uint64_t getCustomVar( uint32_t index );
  private:
    /*! Id of the content of the director */
    uint16_t m_contextId;

    /*! DirectorType | ContentId */
    uint32_t m_directorId;

    /*! currect sequence */
    uint8_t m_sequence;

    /*! current flags */
    uint8_t m_flags;

    uint8_t m_vars[ 10 ];

    /*! type of the director */
    DirectorType m_type;

    /*! custom vars */
    std::unordered_map< uint32_t, uint64_t > m_customVarMap;
  };

}