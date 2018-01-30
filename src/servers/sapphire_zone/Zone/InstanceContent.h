#ifndef SAPPHIRE_INSTANCECONTENT_H
#define SAPPHIRE_INSTANCECONTENT_H

#include "Zone.h"
#include "Forwards.h"
#include <common/Exd/ExdDataGenerated.h>

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

   InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                    uint32_t guId,
                    const std::string& internalName,
                    const std::string& contentName,
                    uint32_t instanceContentId );
   virtual ~InstanceContent();

   boost::shared_ptr< Core::Data::InstanceContent > getInstanceContentInfo() const;

   uint32_t getInstanceContentId() const;

private:
   Event::DirectorPtr m_pDirector;
   boost::shared_ptr< Core::Data::InstanceContent > m_instanceContentInfo;
   uint32_t m_instanceContentId;
   InstanceContentState m_state;

};

}
#endif //SAPPHIRE_INSTANCECONTENT_H
