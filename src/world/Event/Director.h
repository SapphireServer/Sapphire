#ifndef SAPPHIRE_DIRECTOR_H
#define SAPPHIRE_DIRECTOR_H

#include <common/Common.h>

#include "Forwards.h"

namespace Core {
namespace Event {

/*!
\class Director
\brief Base class for all Directors implements sequence and variables

\author Mordred
*/

class Director
{
private:
   /*! Id of the director */
   uint32_t m_id;

   /*! currect sequence */
   uint8_t m_sequence;

   /*! current branch */
   uint8_t m_branch;

   /*! raw storage for flags/vars */
   uint8_t m_unionData[10];

public:
   uint8_t getId() const;
   uint8_t getSequence() const;

};


}
}



#endif //SAPPHIRE_DIRECTOR_H
