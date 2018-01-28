#include <ScriptObject.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/GamePacketNew.h>
#include <Actor/BattleNpc.h>
#include <Zone/Zone.h>

class Add : public DebugCommandScript
{
public:
   Add() : DebugCommandScript( "add", "Executes ADD command", 1 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string &subCommand, const std::string &params )
   {
      if( subCommand == "status" )
      {
         int32_t id;
         int32_t duration;
         uint16_t param;

         sscanf( params.c_str(), "%d %d %hu", &id, &duration, &param );

         StatusEffect::StatusEffectPtr effect( new StatusEffect::StatusEffect( id, player.getAsPlayer(), player.getAsPlayer(), duration, 3000 ) );
         effect->setParam( param );

         player.addStatusEffect( effect );
      }
      else if( subCommand == "title" )
      {
         uint32_t titleId;
         sscanf( params.c_str(), "%u", &titleId );

         player.addTitle( titleId );
         player.sendNotice( "Added title (ID: " + std::to_string( titleId ) + ")" );
      }
      else if( subCommand == "spawn" )
      {
         int32_t model, name;

         sscanf( params.c_str(), "%d %d", &model, &name );

         Entity::BattleNpcPtr pBNpc( new Entity::BattleNpc( model, name, player.getPos() ) );

         auto pZone = player.getCurrentZone();
         pBNpc->setCurrentZone( pZone );
         pZone->pushActor( pBNpc );

      }
      else if( subCommand == "op" )
      {
         // temporary research packet
         int32_t opcode;
         sscanf( params.c_str(), "%x", &opcode );
         Network::Packets::GamePacketPtr pPe( new Network::Packets::GamePacket( opcode, 0x30, player.getId(), player.getId() ) );
         player.queuePacket( pPe );
      }
      else if( subCommand == "actrl" )
      {

         // temporary research packet

         int32_t opcode;
         int32_t param1;
         int32_t param2;
         int32_t param3;
         int32_t param4;
         int32_t param5;
         int32_t param6;
         int32_t playerId;

         sscanf( params.c_str(), "%x %x %x %x %x %x %x %x", &opcode, &param1, &param2, &param3, &param4, &param5, &param6, &playerId );

         player.sendNotice( "Injecting ACTOR_CONTROL " + std::to_string( opcode ) );

         Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorControl143 > actorControl( playerId, player.getId() );
         actorControl.data().category = opcode;
         actorControl.data().param1 = param1;
         actorControl.data().param2 = param2;
         actorControl.data().param3 = param3;
         actorControl.data().param4 = param4;
         actorControl.data().param5 = param5;
         actorControl.data().param6 = param6;
         player.queuePacket( actorControl );


         /*sscanf(params.c_str(), "%x %x %x %x %x %x %x", &opcode, &param1, &param2, &param3, &param4, &param5, &param6, &playerId);

         Network::Packets::Server::ServerNoticePacket noticePacket( player, "Injecting ACTOR_CONTROL " + std::to_string( opcode ) );

         player.queuePacket( noticePacket );

         Network::Packets::Server::ActorControlPacket143 controlPacket( player, opcode,
         param1, param2, param3, param4, param5, param6, playerId );
         player.queuePacket( controlPacket );*/

      }
      else
      {
         player.sendUrgent( subCommand + " is not a valid ADD command." );
      }
   }
};