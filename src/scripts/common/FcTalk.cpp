#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdData.h>

using namespace Sapphire;

class FcTalk : public Sapphire::ScriptAPI::EventScript
{
public:
  FcTalk() :
    Sapphire::ScriptAPI::EventScript( 0x001F0000 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto& exdData = Common::Service< Data::ExdData >::ref();
    auto switchTalk = exdData.getRow< Excel::SwitchTalk >( eventId );
    uint32_t talkEvent = 0;

    if( !switchTalk )
      return;

    for( auto entry = 15; entry >= 0; entry-- )
    {
      auto caseCondition = switchTalk->data().TalkCase[ entry ].CaseCondition;

      if( ( caseCondition >> 16 ) == Event::EventHandler::EventHandlerType::Quest && player.isQuestCompleted( caseCondition ) )
      {
        talkEvent = switchTalk->data().TalkCase[ entry ].Talk;
        break;
      }
      else
      {
        talkEvent = switchTalk->data().TalkCase[ 0 ].Talk;
      }
    }

    if( talkEvent == 0 )
      return;

    eventMgr().eventStart( player, actorId, talkEvent, Event::EventHandler::EventType::Nest, 0, 5 );
    eventMgr().playScene( player, talkEvent, 0, HIDE_HOTBAR | NO_DEFAULT_CAMERA, { 0 }, nullptr );
  }
};

EXPOSE_SCRIPT( FcTalk );