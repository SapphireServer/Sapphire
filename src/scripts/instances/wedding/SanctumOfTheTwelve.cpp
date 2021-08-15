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

  /*
    Custom var usage:
    0: current time
    1: main actor 1 id
    2: main actor 2 id
    3: internal sequence start time
    4: internal sequence
    5: remaining unfinished player count
    101: questBL
    102: questBH
    103: questCL
    104: questCH
    105: questDL
    106: questDH
  */

  void onInit( PublicContent& instance ) override
  {
    auto exitHandler = [ & ]( Entity::Player& player, Entity::EventObjectPtr eobj, TerritoryPtr terri, uint32_t eventId, uint64_t actorId )
    {
      player.eventFinish( eventId, 1 );
      player.exitInstance();
    };

    auto mainBookHandler = [ & ]( Entity::Player& player, Entity::EventObjectPtr eobj, TerritoryPtr terri, uint32_t eventId, uint64_t actorId )
    {
      auto v1 = instance.getCustomVar( 1 );
      auto v2 = instance.getCustomVar( 2 );
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
      if( instance.getSequence() == 1 )
      {
        if( v2 > 0 )
        {
          auto p1 = instance.getPlayer( v1 );
          auto p2 = instance.getPlayer( v2 );
          if( p1 && p2 )
          {
            auto seq1Callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
            {
              if( result.param1 != 512 || result.param2 != 0 )
                return;
              instance.setCustomVar( 3, 0 );
              instance.setCustomVar( 4, 0 );
              //skip 2 for now
              instance.setSequence( 3 );
              instance.foreachPlayer( [ &instance ]( auto p )
                {
                  p->queuePacket( makeActorControlSelf( p->getId(), DirectorUpdate, instance.getDirectorId(), 0x80000001, 1 ) );
                });
            };
            // event item workaround
            player.eventFinish( eventId, 1 );
            player.eventStart( player.getId(), instance.getDirectorId(), Event::EventHandler::Item, 0, 2001464 );
            player.playScene( instance.getDirectorId(), 32, 134225921, 0, 1, 1077, seq1Callback );
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
        if( instance.getCustomVar( 4 ) == 5 )
        {
          auto p1 = instance.getPlayer( v1 );
          auto p2 = instance.getPlayer( v2 );
          if( p1 && p2 )
          {
            auto seq4Callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
            {
              if( result.param1 != 512 || result.param2 != 0 )
                return;
              instance.setCustomVar( 3, 0 );
              instance.setCustomVar( 4, 0 );
              instance.setSequence( 5 );
              instance.foreachPlayer( [ &instance ]( auto p )
                {
                  p->queuePacket( makeActorControlSelf( p->getId(), DirectorUpdate, instance.getDirectorId(), 0x80000001, 1 ) );
                });
            };
            // event item workaround
            player.eventFinish( eventId, 1 );
            player.eventStart( player.getId(), instance.getDirectorId(), Event::EventHandler::Item, 0, 2001464 );
            player.playScene( instance.getDirectorId(), 32, 134225921, 0, 1, 1086, seq4Callback );
          }
          else
          {
            player.sendUrgent( "Two main characters must be in the instance to continue the ceremony." );
          }
        }
        else
          player.sendUrgent( "Waiting for the cutscene and popup messages to finish..." );
      }
      else if( instance.getSequence() == 6 )
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
    switch( instance.getSequence() )
    {
      case 3:
      {
        if( instance.getCustomVar( 3 ) == 0 )
          instance.setCustomVar( 3, tickCount );
        auto dt = std::difftime( tickCount, instance.getCustomVar( 3 ) ) / 1000.f;
        auto v4 = instance.getCustomVar( 4 );
        switch( v4 )
        {
          case 0:
          case 1:
          case 2:
          {
            if( dt >= 1 + v4 * 7 )
            {
              instance.setCustomVar( 4, v4 + 1 );
              FFXIVIpcDirectorPopUp packetData = {};
              packetData.directorId = instance.getDirectorId();
              packetData.flags = 3;
              packetData.bNPCName = 1010505;
              packetData.textId = v4 == 0 ? 1088 : ( v4 == 1 ? 1006 : 1007 );
              packetData.popupTimeMs = 6000;
              packetData.param[ 0 ] = 1024;
              packetData.param[ 1 ] = instance.getCustomVar( 1 );
              packetData.param[ 2 ] = instance.getCustomVar( 2 );
              instance.foreachPlayer( [ &instance, &packetData ]( auto p )
                {
                  auto packet = makeZonePacket< FFXIVIpcDirectorPopUp >( p->getId() );
                  memcpy( &packet->data(), &packetData, sizeof( packetData ) );
                  p->queuePacket( packet );
                });
            }
            break;
          }
          case 3:
          {
            if( dt < 23 )
              return;
            auto p1 = instance.getPlayer( instance.getCustomVar( 1 ) );
            auto p2 = instance.getPlayer( instance.getCustomVar( 2 ) );
            if( !p1 || !p2 )
            {
              instance.setSequence( 1 );
              instance.foreachPlayer( [ &instance ]( auto p )
                {
                  p->sendUrgent( "Failed to start the scene, missing main actors." );
                });
              return;
            }
            FFXIVCeremonySetActorAppearance packetData = {};
            auto qBL = instance.getCustomVar( 101 );
            packetData.questBL = qBL;
            packetData.u1 = 1;
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

            instance.foreachPlayer( [ &instance, &packetData, qBL ]( auto p )
              {
                auto packet = makeZonePacket< FFXIVCeremonySetActorAppearance >( p->getId() );
                memcpy( &packet->data(), &packetData, sizeof( packetData ) );
                p->queuePacket( packet );
                p->eventStart( p->getId(), instance.getDirectorId(), Event::EventHandler::GameProgress, 1, 1 );
                std::vector< uint32_t > paramList;
                paramList.push_back( qBL < 2 ? 664 : 665 );

                auto seq3Callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
                {
                  //keep everyone in their room for now
                  /*
                  if( player.getId() == instance.getCustomVar( 1 ) )
                  {
                    player.setPosAndNotifyClient( 1.454, 3.12581, -132.7992, -3.14 );
                  }
                  else if( player.getId() == instance.getCustomVar( 2 ) )
                  {
                    player.setPosAndNotifyClient( -1.454, 3.12581, -132.7992, -3.14 );
                  }
                  else
                  {
                    player.setPosAndNotifyClient( 0, 2.64, -119, -3.14 );
                  }
                  */
                  auto v5 = instance.getCustomVar( 5 );
                  v5--;
                  instance.setCustomVar( 5, v5 );
                  if( v5 == 0 )
                  {
                    instance.setCustomVar( 3, 0 );
                    instance.setCustomVar( 4, 1 );
                  }
                };

                p->playScene16( instance.getDirectorId(), 3, 9219, 0, paramList, seq3Callback );
              });
            instance.setCustomVar( 3, 0 );
            instance.setCustomVar( 4, 0 );
            instance.setCustomVar( 5, instance.getPopCount() );
            instance.setSequence( 4 );
            break;
          }
        }
        break;
      }
      case 4:
      {
        if( instance.getCustomVar( 3 ) == 0 )
          instance.setCustomVar( 3, tickCount );
        auto dt = std::difftime( tickCount, instance.getCustomVar( 3 ) ) / 1000.f;
        auto v4 = instance.getCustomVar( 4 );
        switch( v4 )
        {
          case 1:
          case 2:
          case 3:
          {
            if( dt >= 6 + ( v4 - 1 ) * 7 )
            {
              instance.setCustomVar( 4, v4 + 1 );
              FFXIVIpcDirectorPopUp packetData = {};
              packetData.directorId = instance.getDirectorId();
              packetData.flags = 3;
              packetData.bNPCName = 1010505;
              packetData.textId = v4 == 1 ? 1008: ( v4 == 2 ? 1091 : 1097 );
              packetData.popupTimeMs = 6000;
              packetData.param[ 0 ] = 1024;
              packetData.param[ 1 ] = instance.getCustomVar( 1 );
              packetData.param[ 2 ] = instance.getCustomVar( 2 );
              instance.foreachPlayer( [ &instance, &packetData ]( auto p )
                {
                  auto packet = makeZonePacket< FFXIVIpcDirectorPopUp >( p->getId() );
                  memcpy( &packet->data(), &packetData, sizeof( packetData ) );
                  p->queuePacket( packet );
                });
            }
            break;
          }
          case 4:
          {
            if( dt >= 28 )
            {
              instance.setCustomVar( 4, 5 );
              instance.foreachPlayer( [ &instance ]( auto p )
                {
                  auto packet = makeZonePacket< FFXIVDirectorUnk4 >( p->getId() );
                  packet->data().param[0] = instance.getDirectorId();
                  packet->data().param[1] = 4353;
                  packet->data().param[2] = 1;
                  packet->data().param[3] = 0;
                  p->queuePacket( packet );
                });
            }
          }
        }
        break;
      }
      case 5:
      {
        if( instance.getCustomVar( 3 ) == 0 )
          instance.setCustomVar( 3, tickCount );
        auto dt = std::difftime( tickCount, instance.getCustomVar( 3 ) ) / 1000.f;
        auto v4 = instance.getCustomVar( 4 );
        switch( v4 )
        {
          case 0:
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
          case 9:
          case 10:
          {
            if( dt >= 1 + v4 * 7 )
            {
              instance.setCustomVar( 4, v4 + 1 );
              FFXIVIpcDirectorPopUp packetData = {};
              packetData.directorId = instance.getDirectorId();
              packetData.flags = 3;
              packetData.bNPCName = 1010505;
              packetData.textId = v4 == 0 ? 1010 :
                ( v4 == 1 ? 1011 :
                ( v4 == 2 ? 1015 :
                ( v4 == 3 ? 1103 :
                ( v4 == 4 ? 1019 :
                ( v4 == 5 ? 1107 :
                ( v4 == 6 ? 1020 :
                ( v4 == 7 ? 1021 :
                ( v4 == 8 ? 1125 :
                ( v4 == 9 ? 1126 : 1127 ) ) ) ) ) ) ) ) );
              packetData.popupTimeMs = 6000;
              packetData.param[ 0 ] = 1024;
              packetData.param[ 1 ] = instance.getCustomVar( 1 );
              packetData.param[ 2 ] = instance.getCustomVar( 2 );
              instance.foreachPlayer( [ &instance, &packetData ]( auto p )
                {
                  auto packet = makeZonePacket< FFXIVIpcDirectorPopUp >( p->getId() );
                  memcpy( &packet->data(), &packetData, sizeof( packetData ) );
                  p->queuePacket( packet );
                });
            }
            break;
          }
          case 11:
          {
            if( dt >= 78 )
            {
              auto qBH = instance.getCustomVar( 102 );
              instance.foreachPlayer( [ &instance, qBH ]( auto p )
                {
                  p->eventStart( p->getId(), instance.getDirectorId(), Event::EventHandler::GameProgress, 1, 1 );
                  std::vector< uint32_t > paramList;
                  paramList.push_back( 665 + qBH );

                  auto seq5Callback = [ & ]( Entity::Player& player, const Event::SceneResult& result )
                  {
                    auto v5 = instance.getCustomVar( 5 );
                    v5--;
                    instance.setCustomVar( 5, v5 );
                    if( v5 == 0 )
                    {
                      instance.setCustomVar( 3, 0 );
                      instance.setCustomVar( 4, 1 );
                    }
                  };

                  p->playScene16( instance.getDirectorId(), 3, 9219, 0, paramList, seq5Callback );
                });
              instance.setCustomVar( 3, 0 );
              instance.setCustomVar( 4, 0 );
              instance.setCustomVar( 5, instance.getPopCount() );
              instance.setSequence( 6 );
            }
            break;
          }
        }
        break;
      }
    }
    instance.setCustomVar( 0, tickCount );
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
        instance.setCustomVar( 101, player.getQuestUI8BL( 67114 ) );
        instance.setCustomVar( 102, player.getQuestUI8BH( 67114 ) );
        instance.setCustomVar( 103, player.getQuestUI8CL( 67114 ) );
        instance.setCustomVar( 104, player.getQuestUI8CH( 67114 ) );
        instance.setCustomVar( 105, player.getQuestUI8DL( 67114 ) );
        instance.setCustomVar( 106, player.getQuestUI8DH( 67114 ) );
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
    if( instance.getCustomVar( 1 ) == player.getId() && instance.getSequence() == 1 )
    {
      player.setPosAndNotifyClient( 0, 500, -50, -3.14f );
    }
    else if( instance.getCustomVar( 2 ) == player.getId() && instance.getSequence() == 1 )
    {
      player.setPosAndNotifyClient( 0, 250, -50, -3.14f );
    }
    else
    {
      player.setPosAndNotifyClient( 0, 750, -50, -3.14f );
    }
    //player.queuePacket( makeActorControlSelf( getId(), DirectorUpdate, instance.getDirectorId(), 0x80000003, 1200 ) ); // timer, we dont need it for now
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