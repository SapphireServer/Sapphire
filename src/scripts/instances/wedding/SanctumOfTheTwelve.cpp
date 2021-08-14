#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Territory/PublicContent.h"
#include <Util/UtilMath.h>
#include "Network/CommonActorControl.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

using namespace Sapphire;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

class SanctumOfTheTwelve : public Sapphire::ScriptAPI::PublicContentScript
{
public:
  SanctumOfTheTwelve() : Sapphire::ScriptAPI::PublicContentScript( 1 ) { }

  void onInit( PublicContent& instance ) override
  {
    auto exitHandler = [ & ]( Entity::Player& player, Entity::EventObjectPtr eobj, TerritoryPtr terri, uint32_t eventId, uint64_t actorId )
    {
      player.eventFinish( eventId, 1 );
      player.exitInstance();
    };

    instance.registerEObj( "unknown_0", 2005027, 0, 0, { 0.0f, 251.103f, -60.39313f }, 1.0f, Common::Util::floatFromUInt16Rot( 28453 ) );
    instance.registerEObj( "unknown_1", 2004902, 0, 1, { -0.1025963f, 2.902821f, -125.97f }, 1.0f, Common::Util::floatFromUInt16Rot( 32767 ) );
    instance.registerEObj( "unknown_2", 2004786, 0, 0, { 0.0f, 501.103f, -60.39313f }, 1.0f, Common::Util::floatFromUInt16Rot( 28453 ) );
    instance.registerEObj( "unknown_3", 2004783, 0, 0, { 0.0f, 0.5f, 19.0f }, 1.0f, Common::Util::floatFromUInt16Rot( 32767 ) )->setOnTalkHandler( exitHandler );
    instance.registerEObj( "unknown_4", 2004783, 0, 0, { 0.0f, 250.5515f, -48.19313f }, 1.0f, Common::Util::floatFromUInt16Rot( 32767 ) )->setOnTalkHandler( exitHandler );
    instance.registerEObj( "unknown_5", 2004783, 0, 0, { -0.01531982f, 500.5456f, -48.20331 }, 0.9917603f, Common::Util::floatFromUInt16Rot( 32767 ) )->setOnTalkHandler( exitHandler );
    instance.registerEObj( "unknown_6", 2004783, 0, 0, { -0.01531982f, 750.5475f, -55.13086f }, 0.9917603f, Common::Util::floatFromUInt16Rot( 32767 ) )->setOnTalkHandler( exitHandler );
    instance.setCurrentFestival( 237, 0 );
  }

  void onUpdate( PublicContent& instance, uint64_t tickCount ) override
  {

  }

  void onPlayerZoneIn( PublicContent& instance, Entity::Player& player ) override
  {
    if( instance.getCustomVar( 1 ) == 0 || instance.getCustomVar( 1 ) == player.getId() )
    {
      if( player.hasQuest( 67114 ) )
      {
        instance.setCustomVar( 1, player.getId() );
        instance.setDirectorUI8AL( player.getQuestUI8AH( 67114 ) );
        instance.setDirectorUI8BL( player.getQuestUI8AL( 67114 ) );
        instance.setDirectorUI8CL( player.getGuardianDeity() );
        instance.setDirectorUI8DL( player.getGuardianDeity() );
        instance.setDirectorUI8EL( player.getQuestUI8FH( 67114 ) );
        instance.setDirectorUI8FL( player.getQuestUI8FL( 67114 ) );
        instance.setDirectorUI8GL( 1 );
        instance.setDirectorUI8HL( 1 );
        instance.setDirectorUI8IL( 1 );
        instance.setDirectorUI8JL( 1 );
      }
    }
  }

  void onLeaveTerritory( PublicContent& instance, Entity::Player& player ) override
  {
  }

  void onEnterTerritory( PublicContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
  {
    auto callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto p = makeZonePacket< FFXIVDirectorUnk4 >( getId() );
      p->data().param[0] = instance.getDirectorId();
      p->data().param[1] = 4365;
      p->data().param[2] = 0;
      p->data().param[3] = 0;
      player.queuePacket( p );
    };
    player.queuePacket( makeActorControlSelf( getId(), DirectorUpdate, instance.getDirectorId(), 0x80000003, 1200 ) ); // timer
    player.playScene( instance.getDirectorId(), 1, HIDE_HOTBAR, 0, 2, 4, callback );
  }
 
  void onDebug( Entity::Player& player, uint32_t param ) override
  {
    auto instance = player.getCurrentPublicContent();
    if( !instance || instance->getDirectorId() != getId() )
      return;
    player.sendUrgent( "SanctumOfTheTwelve: debug {}", param );

    player.eventStart( player.getId(), instance->getDirectorId(), Event::EventHandler::EnterTerritory, 1, player.getZoneId() );
    player.directorPlayScene( instance->getDirectorId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, 0, 1, param );
  }
 
};

EXPOSE_SCRIPT( SanctumOfTheTwelve );