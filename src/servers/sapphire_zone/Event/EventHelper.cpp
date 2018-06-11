#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <boost/range/algorithm/remove_if.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "Framework.h"
#include "EventHelper.h"
#include "EventHandler.h"


extern Core::Framework g_fw;


using namespace Core::Common;

std::string Core::Event::getEventName( uint32_t eventId )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   uint16_t eventType = eventId >> 16;

   auto unknown = std::string{ "unknown" };

   switch( eventType )
   {
   case Event::EventHandler::EventHandlerType::Quest:
   {
      auto questInfo = pExdData->get< Core::Data::Quest >( eventId );
      if( !questInfo )
         return unknown + "Quest";

      std::string name = questInfo->id;
      std::size_t pos = name.find_first_of( "_" );

      return name.substr( 0, pos );
   }
   case Event::EventHandler::EventHandlerType::CustomTalk:
   {
      auto customTalkInfo = pExdData->get< Core::Data::CustomTalk >( eventId );
      if( !customTalkInfo )
         return unknown + "CustomTalk";

      std::string name = customTalkInfo->name;
      std::size_t pos = name.find_first_of( "_" );

      return customTalkInfo->name.substr( 0, pos );
   }
   case Event::EventHandler::EventHandlerType::Opening:
   {
      auto openingInfo = pExdData->get< Core::Data::Opening >( eventId );
      if( openingInfo )
         return openingInfo->name;
      return unknown + "Opening";
   }
   case Event::EventHandler::EventHandlerType::Aetheryte:
   {
      auto aetherInfo = pExdData->get< Core::Data::Aetheryte >( eventId & 0xFFFF );
      if( aetherInfo->isAetheryte )
         return "Aetheryte";
      return "Aethernet";
   }
   case Event::EventHandler::EventHandlerType::ICDirector:
   {
      auto contentInfo = pExdData->get< Core::Data::InstanceContent >( eventId & 0xFFFF );
      std::string name = contentInfo->name;

      name.erase( boost::remove_if( name, boost::is_any_of( "â˜…_ '()[]-\x1a\x1\x2\x1f\x1\x3.:" ) ), name.end() );
      name[0] = toupper( name[0] );
      return name;
   }

   case Event::EventHandler::EventHandlerType::Warp:
   {
      return "ChocoboTaxi";
   }
   default:
   {
      return unknown;
   }
   }
}

uint32_t Core::Event::mapEventActorToRealActor( uint32_t eventActorId )
{
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
   auto levelInfo = pExdData->get< Core::Data::Level >( eventActorId );
   if( levelInfo )
      return levelInfo->objectKey;

   return 0;
}
