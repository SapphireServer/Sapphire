#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Territory/PublicContent.h"
#include <Util/UtilMath.h>
#include "Network/CommonActorControl.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketDef/Zone/ServerZoneDef.h"

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

    auto mainBookHandler = [ & ]( Entity::Player& player, Entity::EventObjectPtr eobj, TerritoryPtr terri, uint32_t eventId, uint64_t actorId )
    {
      if( instance.getSequence() == 1 )
      {
        auto v1 = instance.getCustomVar( 1 );
        if( v1 == 0 )
        {
          player.sendUrgent( "The host of this ceremony is not determined yet, become the host as the first one to join the instance with quest 67114 at seq 12." );
          return;
        }
        if( v1 != player.getId() )
        {
          player.sendUrgent( "You are not the host of this ceremony." );
          return;
        }
        auto v2 = instance.getCustomVar( 2 );
        if( v2 > 0 )
        {
          auto p1 = instance.getPlayer( v1 );
          auto p2 = instance.getPlayer( v2 );
          if( p1 && p2 )
          {
            //skip seq 2, 3 for now
            instance.setDirectorSequence( 4 );
            p1->eventFinish( eventId, 1 );
            FFXIVCeremonySetActorAppearance packetData = {};
            packetData.u1 = 1;
            packetData.u2 = 1;
            if( !( p1->getEquipDisplayFlags() & Sapphire::Common::EquipDisplayFlags::HideWeapon ) )
            {
              packetData.actors[0].mainWeaponModel = p1->getModelMainWeapon();
              packetData.actors[0].secWeaponModel = p1->getModelSubWeapon();
            }
            packetData.actors[0].charId = p1->getId();
            packetData.actors[0].guardianDeity = p1->getGuardianDeity();
            packetData.actors[0].models[ Common::GearModelSlot::ModelHead ] = p1->getModelForSlot( Common::GearModelSlot::ModelHead );
            packetData.actors[0].models[ Common::GearModelSlot::ModelBody ] = p1->getModelForSlot( Common::GearModelSlot::ModelBody );
            packetData.actors[0].models[ Common::GearModelSlot::ModelHands ] = p1->getModelForSlot( Common::GearModelSlot::ModelHands );
            packetData.actors[0].models[ Common::GearModelSlot::ModelLegs ] = p1->getModelForSlot( Common::GearModelSlot::ModelLegs );
            packetData.actors[0].models[ Common::GearModelSlot::ModelFeet ] = p1->getModelForSlot( Common::GearModelSlot::ModelFeet );
            packetData.actors[0].models[ Common::GearModelSlot::ModelNeck ] = p1->getModelForSlot( Common::GearModelSlot::ModelNeck );
            packetData.actors[0].models[ Common::GearModelSlot::ModelEar ] = p1->getModelForSlot( Common::GearModelSlot::ModelEar );
            packetData.actors[0].models[ Common::GearModelSlot::ModelRing1 ] = p1->getModelForSlot( Common::GearModelSlot::ModelRing1 );
            packetData.actors[0].models[ Common::GearModelSlot::ModelRing2 ] = p1->getModelForSlot( Common::GearModelSlot::ModelRing2 );
            packetData.actors[0].models[ Common::GearModelSlot::ModelWrist ] = p1->getModelForSlot( Common::GearModelSlot::ModelWrist );
            memcpy( packetData.actors[0].look, p1->getLookArray(), sizeof( packetData.actors[0].look ) );
            if( !( p2->getEquipDisplayFlags() & Sapphire::Common::EquipDisplayFlags::HideWeapon ) )
            {
              packetData.actors[1].mainWeaponModel = p2->getModelMainWeapon();
              packetData.actors[1].secWeaponModel = p2->getModelSubWeapon();
            }
            packetData.actors[1].charId = p2->getId();
            packetData.actors[1].guardianDeity = p2->getGuardianDeity();
            packetData.actors[1].models[ Common::GearModelSlot::ModelHead ] = p2->getModelForSlot( Common::GearModelSlot::ModelHead );
            packetData.actors[1].models[ Common::GearModelSlot::ModelBody ] = p2->getModelForSlot( Common::GearModelSlot::ModelBody );
            packetData.actors[1].models[ Common::GearModelSlot::ModelHands ] = p2->getModelForSlot( Common::GearModelSlot::ModelHands );
            packetData.actors[1].models[ Common::GearModelSlot::ModelLegs ] = p2->getModelForSlot( Common::GearModelSlot::ModelLegs );
            packetData.actors[1].models[ Common::GearModelSlot::ModelFeet ] = p2->getModelForSlot( Common::GearModelSlot::ModelFeet );
            packetData.actors[1].models[ Common::GearModelSlot::ModelNeck ] = p2->getModelForSlot( Common::GearModelSlot::ModelNeck );
            packetData.actors[1].models[ Common::GearModelSlot::ModelEar ] = p2->getModelForSlot( Common::GearModelSlot::ModelEar );
            packetData.actors[1].models[ Common::GearModelSlot::ModelRing1 ] = p2->getModelForSlot( Common::GearModelSlot::ModelRing1 );
            packetData.actors[1].models[ Common::GearModelSlot::ModelRing2 ] = p2->getModelForSlot( Common::GearModelSlot::ModelRing2 );
            packetData.actors[1].models[ Common::GearModelSlot::ModelWrist ] = p2->getModelForSlot( Common::GearModelSlot::ModelWrist );
            memcpy( packetData.actors[1].look, p2->getLookArray(), sizeof( packetData.actors[1].look ) );

            instance.foreachPlayer( [ &instance, &packetData ]( auto p )
              {
                auto packet = makeZonePacket< FFXIVCeremonySetActorAppearance >( p->getId() );
                memcpy( &packet->data(), &packetData, sizeof( packetData ) );
                p->queuePacket( packet );
                p->eventStart( p->getId(), instance.getDirectorId(), Event::EventHandler::EnterTerritory, 1, p->getZoneId() );
                p->directorPlayScene( instance.getDirectorId(), 3, 9219, 0, 1, 50000 );
              });
          }
          else
          {
            player.sendUrgent( "Two main characters must be in the instance to begin the ceremony." );
          }
        }
        else
        {
          player.sendUrgent( "Need another character with quest 67114 at seq 12 to begin the ceremony." );
        }
      }
      else if( instance.getSequence() == 4 )
      {
        player.sendUrgent( "WIP..." );
      }
    };

    auto subBookHandler = [ & ]( Entity::Player& player, Entity::EventObjectPtr eobj, TerritoryPtr terri, uint32_t eventId, uint64_t actorId )
    {
      auto v2 = instance.getCustomVar( 2 );
      if( v2 == player.getId() )
      {
        player.sendUrgent( "Wait for your partner to start the ceremony." );
      }
    };

    instance.registerEObj( "unknown_0", 2005027, 0, 0, { 0.0f, 251.103f, -60.39313f }, 1.0f, Common::Util::floatFromUInt16Rot( 28453 ) )->setOnTalkHandler( subBookHandler );
    instance.registerEObj( "unknown_1", 2004902, 0, 1, { -0.1025963f, 2.902821f, -125.97f }, 1.0f, Common::Util::floatFromUInt16Rot( 32767 ) );
    instance.registerEObj( "unknown_2", 2004786, 0, 0, { 0.0f, 501.103f, -60.39313f }, 1.0f, Common::Util::floatFromUInt16Rot( 28453 ) )->setOnTalkHandler( mainBookHandler );
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
      if( player.hasQuest( 67114 ) && player.getQuestSeq( 67114 ) == 12 )
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
    else if( instance.getCustomVar( 2 ) == 0 || instance.getCustomVar( 2 ) == player.getId() )
    {
      if( player.hasQuest( 67114 ) && player.getQuestSeq( 67114 ) == 12 )
      {
        instance.setCustomVar( 2, player.getId() );
        auto p1 = instance.getPlayer( instance.getCustomVar( 1 ) );
        if( p1 )
        {
          auto p = makeZonePacket< FFXIVDirectorUnk4 >( getId() );
          p->data().param[0] = instance.getDirectorId();
          p->data().param[1] = 4365;
          p->data().param[2] = 0;
          p->data().param[3] = 0;
          p1->queuePacket( p );
        }
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
    };
    if( instance.getCustomVar( 1 ) == player.getId() )
    {
      player.setPosAndSendActorMove( 0, 500, -50, -3.14f );
    }
    else if( instance.getCustomVar( 2 ) == player.getId() )
    {
      player.setPosAndSendActorMove( 0, 250, -50, -3.14f );
    }
    else
    {
      player.setPosAndSendActorMove( 0, 750, -50, -3.14f );
    }
    //player.queuePacket( makeActorControlSelf( getId(), DirectorUpdate, instance.getDirectorId(), 0x80000003, 1200 ) ); // timer
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