#ifndef _PLAYERMINIMAL_H
#define _PLAYERMINIMAL_H

#include <map>
#include <stdint.h>
#include <string.h>
namespace Core {


   class PlayerMinimal
   {
   public:
      PlayerMinimal( void );
      ~PlayerMinimal( void );

      // write player to the database
      void write();

      // load player from db, by id
      void load( uint32_t charId );

      void saveAsNew();

      std::string getLookString();

      std::string getInfoJson();

      std::string getModelString();

      std::string getClassString();

      // return the id of the actor
      uint32_t getId()
      {
         return m_iD;
      }

      void setId( uint32_t id )
      {
         m_iD = id;
      }

      void setContentId( uint64_t id )
      {
         m_contentId = id;
      }

      uint64_t getContentId()
      {
         return m_contentId;
      }


      uint32_t getAccountId()
      {
         return m_accountId;
      }

      void setAccountId( uint32_t accountId )
      {
         m_accountId = accountId;
      }

      // return the actors name
      char * getName()
      {
         return m_name;
      }

      void setLook( uint8_t index, uint32_t value )
      {
         m_lookMap[index] = value;
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

      uint8_t getClass()
      {
         return m_class;
      }

      uint8_t getGuardianDeity()
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

      uint8_t getBirthDay()
      {
         return m_birthDay;
      }

      uint8_t getBirthMonth()
      {
         return m_birthMonth;
      }

      uint8_t getVoice()
      {
         return m_birthMonth;
      }

      void setVoice( uint8_t voice )
      {
         m_voice = voice;
      }

      uint32_t getZoneId()
      {
         return m_zoneId;
      }

      uint32_t getTribe()
      {
         return m_tribe;
      }

      void setTribe( uint8_t tribe )
      {
         m_tribe = tribe;
      }

      uint32_t						m_modelEquip[10];

   private:
      uint32_t						m_accountId;
      uint32_t						m_iD;
      uint64_t						m_contentId;

      uint8_t							m_guardianDeity;
      uint8_t							m_birthMonth;
      uint8_t							m_birthDay;
      uint8_t							m_class;

      uint8_t							m_voice;

      uint8_t                    m_tribe;

      uint16_t                        m_zoneId;

      std::map<uint8_t, uint32_t>		m_lookMap;
      std::map<uint8_t, uint16_t>		m_classMap;
      uint8_t							m_look[26];

      char							m_name[34];


   };

}
#endif
