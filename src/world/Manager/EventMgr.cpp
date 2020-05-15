#include <Common.h>
#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include <Service.h>

#include "EventMgr.h"
#include "Event/EventHandler.h"

using namespace Sapphire::Common;

std::string Sapphire::World::Manager::EventMgr::getEventName( uint32_t eventId )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto eventType = static_cast< Event::EventHandler::EventHandlerType >( eventId >> 16 );

  auto unknown = std::string{ "unknown" };

  switch( eventType )
  {
    case Event::EventHandler::EventHandlerType::Quest:
    {
      auto questInfo = exdData.get< Sapphire::Data::Quest >( eventId );
      if( !questInfo )
        return unknown + "Quest";

      std::string name = questInfo->id;
      std::size_t pos = name.find_first_of( "_" );

      return name.substr( 0, pos );
    }
    case Event::EventHandler::EventHandlerType::CustomTalk:
    {
      auto customTalkInfo = exdData.get< Sapphire::Data::CustomTalk >( eventId );
      if( !customTalkInfo )
        return unknown + "CustomTalk";

      std::string name = customTalkInfo->name;
      std::size_t pos = name.find_first_of( "_" );

      return customTalkInfo->name.substr( 0, pos );
    }
    case Event::EventHandler::EventHandlerType::Opening:
    {
      auto openingInfo = exdData.get< Sapphire::Data::Opening >( eventId );
      if( openingInfo )
        return openingInfo->name;
      return unknown + "Opening";
    }
    case Event::EventHandler::EventHandlerType::Aetheryte:
    {
      auto aetherInfo = exdData.get< Sapphire::Data::Aetheryte >( eventId & 0xFFFF );
      if( aetherInfo->isAetheryte )
        return "Aetheryte";
      return "Aethernet";
    }
    case Event::EventHandler::EventHandlerType::ICDirector:
    {
      // auto contentInfo = pExdData->get< Sapphire::Data::InstanceContent >( eventId & 0xFFFF );
      return "InstanceContentDirector#" + std::to_string( eventId & 0xFFFF );
    }
    case Event::EventHandler::EventHandlerType::QuestBattleDirector:
    {

      auto qbInfo = exdData.get< Sapphire::Data::QuestBattle >( eventId & 0xFFFF );
      if( !qbInfo )
        return "unknown";
      auto questInfo = exdData.get< Sapphire::Data::Quest >( qbInfo->quest );
      if( !questInfo )
        return "unknown";

      std::string name = questInfo->name;
      std::string remove( ",â˜…_ '()[]-\x1a\x1\x2\x1f\x1\x3.:" );
      Util::eraseAllIn( name, remove );
      name[ 0 ] = toupper( name[ 0 ] );
      return name;
    }


    case Event::EventHandler::EventHandlerType::Warp:
    {
      auto warpInfo = exdData.get< Sapphire::Data::Warp >( eventId );
      if( warpInfo )
        return "WarpTaxi";
      return unknown + "ChocoboWarp"; //who know
    }

    case Event::EventHandler::EventHandlerType::Shop:
    {
      auto shopInfo = exdData.get< Sapphire::Data::GilShop >( eventId );

      return "GilShop" + std::to_string( eventId );
      /*if( shopInfo )
      {
        if( shopInfo->name.empty() || shopInfo->name == " " )
          return "GilShop" + std::to_string( eventId );
        return shopInfo->name;
      }*/
      //return unknown + "GilShop";
    }
    default:
    {
      return unknown;
    }
  }
}

uint32_t Sapphire::World::Manager::EventMgr::mapEventActorToRealActor( uint32_t eventActorId )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto levelInfo = exdData.get< Sapphire::Data::Level >( eventActorId );
  if( levelInfo )
    return levelInfo->object;

  return 0;
}
