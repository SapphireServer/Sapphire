#include "EventHelper.h"
#include "Event.h"
#include <Server_Common/Common.h>

#include <Server_Common/ExdData.h>

extern Core::Data::ExdData g_exdData;

using namespace Core::Common;

std::string Core::Event::getEventName( uint32_t eventId )
{
   uint16_t eventType = eventId >> 16;

   switch( eventType )
   {
   case EventType::Quest:
   {
      auto questInfo = g_exdData.getQuestInfo( eventId );
      if( questInfo )
      {
         std::string name = questInfo->name_intern;
         std::size_t pos = name.find_first_of( "_" );

         return questInfo->name_intern.substr( 0, pos );
      }
   }
   break;
   case EventType::CustomTalk:
   {
      auto customTalkInfo = g_exdData.getCustomTalkInfo( eventId );
      if( customTalkInfo )
      {
         std::string name = customTalkInfo->name_intern;
         std::size_t pos = name.find_first_of( "_" );

         return customTalkInfo->name_intern.substr( 0, pos );
      }

   }
   break;
   case EventType::Opening:
   {
      auto openingInfo = g_exdData.getOpeningInfo( eventId );
      if( openingInfo )
         return openingInfo->name;
   }
   break;
   case EventType::Aetheryte:
   {
      auto aetherInfo = g_exdData.getAetheryteInfo( eventId & 0xFFFF );
      if( aetherInfo->isAetheryte )
         return "Aetheryte";
      return "Aethernet";
      
   }
   case EventType::ChocoPort:
   {
      return "ChocoboTaxi";
   }
   default:
   {
      return "";

   }
   }
   return "";
}

uint32_t Core::Event::mapEventActorToRealActor( uint32_t eventActorId )
{
   auto levelInfo = g_exdData.getLevelInfo( eventActorId );
   if( levelInfo )
      return levelInfo->actor_id;

   return 0;
}
