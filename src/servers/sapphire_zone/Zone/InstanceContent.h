#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Zone.h"
#include "Forwards.h"

namespace Core
{

class InstanceContent : public Zone
{
public:
   enum InstanceContentState
   {
      Created,
      DutyStarted,
      DutyFinished
   };

   InstanceContent( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName );
   virtual ~InstanceContent();

private:
   Event::DirectorPtr m_pDirector;

};

}
#endif //SAPPHIRE_INSTANCECONTENT_H
