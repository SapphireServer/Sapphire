#ifndef _ACTION_H_
#define _ACTION_H_

#include <src/servers/Server_Common/Common.h>
#include "src/servers/Server_Zone/Forwards.h"

namespace Core { namespace Action {

   enum struct ActionAspect : uint32_t
   {
      None       = 0,   // Doesn't imply unaspected
      Fire       = 1,
      Ice        = 2,
      Wind       = 3,
      Stone      = 4,
      Lightning  = 5,
      Water      = 6,
      Unaspected = 7    // Doesn't imply magical unaspected damage - could be unaspected physical
   };

   enum struct ActionType : int16_t
   {
      Physical   = -1,
      Unknown_0  = 0, // Very likely actions that only deals with status effects and nothing else
      Unknown_1  = 1, // Related to actions that deal with player movement (knockbacks, gapclosers etc)
      Unknown_2  = 2, // Possibly attacks that bypass calculation (deal raw damage)
      Unknown_3  = 3, // Possibly AoEs without marker
      Unknown_4  = 4,
      Magical    = 5,
      Unknown_6  = 6, // Possibly breath, eye & song attacks
      Unknown_7  = 7,
      LimitBreak = 8,
   };

   class Action 
   {

   public:
      Action();
      virtual ~Action();

      uint32_t getId() const;

      Common::ActionType getActionType() const;

      Entity::ActorPtr getTargetActor() const;

      bool isInterrupted() const;

      void setInterrupted();

      uint64_t getStartTime() const;

      void setStartTime( uint64_t startTime );

      uint32_t getCastTime() const;

      void setCastTime( uint32_t castTime );

      Entity::ActorPtr getActionSource() const;

      virtual void onStart() {};
      virtual void onFinish() {};
      virtual void onInterrupt() {};

      // update action, if returns true, action is done and has to be removed from the actor
      virtual bool update();

   protected:
      uint32_t	m_id;
      Common::ActionType m_actionType;

      uint64_t	m_startTime;
      uint32_t	m_castTime;

      Entity::ActorPtr m_pSource;
      Entity::ActorPtr m_pTarget;

      bool m_bInterrupt;

   };

}
}

#endif