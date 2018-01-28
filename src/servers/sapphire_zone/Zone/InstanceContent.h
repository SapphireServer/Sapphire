#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Zone.h"
#include "Forwards.h"

namespace Core
{

class InstanceContent : public Zone
{
public:
   InstanceContent( uint32_t instanceContentId, uint32_t guid );
   virtual ~InstanceContent();

private:
   DirectorPtr m_pDirector;

};

}
#endif //SAPPHIRE_INSTANCECONTENT_H
