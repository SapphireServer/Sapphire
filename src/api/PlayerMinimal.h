#ifndef _PLAYERMINIMAL_H
#define _PLAYERMINIMAL_H

#include <map>
#include <stdint.h>
#include <string.h>

namespace Sapphire::Api
{

  class PlayerMinimal
  {
  public:
    PlayerMinimal();

    ~PlayerMinimal() = default;

    // write player to the database
    void write();

    // load player from db, by id
    void load( uint32_t charId );

    void saveAsNew();

    std::string getInfoJson();

    uint8_t getClassLevel();

    // return the id of the actor
    uint32_t getId() const
    {
      return m_id;
    }

    void setId( uint32_t id )
    {
      m_id = id;
    }

    void setContentId( uint64_t id )
    {
      m_contentId = id;
    }

    uint64_t getContentId() const
    {
      return m_contentId;
    }


    uint32_t getAccountId() const
    {
      return m_accountId;
    }

    void setAccountId( uint32_t accountId )
    {
      m_accountId = accountId;
    }

    // return the actors name
    char* getName()
    {
      return m_name;
    }

    void setLook( uint8_t index, uint32_t value )
    {
      m_lookMap[ index ] = value;
    }


    // return the actors name
    void setName( const char* name )
    {
      strcpy( m_name, name );
    }

    void setClass( uint8_t classId )
    {
      m_class = classId;
    }

    uint8_t getClass() const
    {
      return m_class;
    }

    uint8_t getGuardianDeity() const
    {
      return m_guardianDeity;
    }

    void setGuardianDeity( uint8_t guardianId )
    {
      m_guardianDeity = guardianId;
    }

    void setBirthDay( uint8_t day, uint8_t month )
    {
      m_birthDay = day;
      m_birthMonth = month;
    }

    uint8_t getBirthDay() const
    {
      return m_birthDay;
    }

    uint8_t getBirthMonth() const
    {
      return m_birthMonth;
    }

    uint8_t getVoice() const
    {
      return m_birthMonth;
    }

    void setVoice( uint8_t voice )
    {
      m_voice = voice;
    }

    uint32_t getZoneId() const
    {
      return m_territoryTypeId;
    }

    uint32_t getTribe() const
    {
      return m_tribe;
    }

    void setTribe( uint8_t tribe )
    {
      m_tribe = tribe;
    }

    uint8_t getGmRank() const
    {
      return m_gmRank;
    }

    void setGmRank( uint8_t rank )
    {
      m_gmRank = rank;
    }

    bool getGmInvis() const
    {
      return m_gmInvis;
    }

    void setGmInvis( bool invis )
    {
      m_gmInvis = invis;
    }

    void createInvDbContainer( uint16_t slot ) const;

    uint32_t m_modelEquip[10];

    uint64_t getNextUId64() const;

  private:
    uint32_t m_accountId;
    uint32_t m_id;
    uint64_t m_contentId;

    uint8_t m_guardianDeity;
    uint8_t m_birthMonth;
    uint8_t m_birthDay;
    uint8_t m_class;
    uint8_t m_classLevel;

    uint8_t m_voice;

    uint8_t m_tribe;

    uint16_t m_territoryTypeId;

    uint64_t m_modelMainWeapon;
    uint64_t m_modelSubWeapon;
    uint8_t m_equipDisplayFlags;

    std::map< uint8_t, uint8_t > m_lookMap;
    std::map< uint8_t, uint16_t > m_classMap;
    uint8_t m_look[26];

    uint8_t m_gmRank;
    bool m_gmInvis;

    char m_name[34];

    void insertDbGlobalItem( uint32_t itemId, uint64_t uniqueId ) const;
  };

}
#endif
