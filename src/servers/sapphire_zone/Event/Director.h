#ifndef SAPPHIRE_DIRECTOR_H
#define SAPPHIRE_DIRECTOR_H

#include <common/Common.h>

#include "Forwards.h"

namespace Core {
namespace Event {

/*!
\class Director
\brief Base class for all Directors implements sequence and variables

*/

class Director
{

public:
   enum DirectorType
   {
      InstanceContent = 0x8003, // used for dungeons/raids
      CompanyLeve = 0x8007,
      QuestBattle = 0x8006,
      GatheringLeve = 0x8002,
      BattleLeve = 0x8001,
      GoldSaucer = 0x800A,
      Fate = 0x801A,
      DpsChallange = 0x800D
   };

private:
   /*! Id of the content of the director */
   uint16_t m_id;

   /*! DirectorType | ContentId */
   uint32_t m_directorId;

   /*! currect sequence */
   uint8_t m_sequence;

   /*! current branch */
   uint8_t m_branch;

   /*! raw storage for flags/vars */
   uint8_t m_unionData[10];

   /*! type of the director */
   DirectorType m_type;

   uint32_t getDirectorId() const;
   uint16_t getContentId() const;
   DirectorType getType() const;
   uint8_t getSequence() const;
   uint8_t getBranch() const;

};


}
}



#endif //SAPPHIRE_DIRECTOR_H
