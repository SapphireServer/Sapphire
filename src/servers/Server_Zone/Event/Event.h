#ifndef _EVENT_H
#define _EVENT_H

#include "../Forwards.h"

namespace Core {
   namespace Event {

      class Event 
      {
      public:
         Event( uint64_t actorId, uint32_t eventId, uint8_t eventType, uint8_t eventParam2, uint32_t eventParam3 );

         ~Event() {}

         uint64_t getActorId() const;

         uint32_t getId() const;

         uint32_t getParam1() const;

         uint16_t getParam2() const;

         uint8_t getEventType() const;

         uint32_t getEventParam2() const;

         uint32_t getEventParam3() const;

         bool hasPlayedScene() const;

         void setPlayedScene( bool playedScene );

         Scripting::EventReturnCallback getEventReturnCallback() const;

         void setEventReturnCallback( Scripting::EventReturnCallback callback );

         enum EventType : uint8_t
         {
            Talk = 1,
            Emote = 2,
            DistanceBelow = 3,
            DistanceOver = 4,
            BattleReward = 5,
            Craft = 6,
            Nest = 7,
            Item = 8,
            Drop = 9,
            WithinRange = 10,
            OutsideRange = 11,
            GameStart = 12,
            GameProgress = 13,
            EnterTerritory = 15,
            GameComeBack = 17,
            ActionResult = 18,
            MateriaCraft = 19,
            Fishing = 20,
            UI = 21,
            Housing = 22,
            Say = 23,
            TableGame = 24,
         };

      protected:
         uint64_t m_actorId;
         uint32_t m_eventId;
         uint32_t m_param1;
         uint16_t m_param2;
         uint8_t m_eventType;
         uint8_t m_eventParam2;
         uint32_t m_eventParam3;
         bool m_playedScene;
         Scripting::EventReturnCallback m_callback;
      };

   }
}
#endif
