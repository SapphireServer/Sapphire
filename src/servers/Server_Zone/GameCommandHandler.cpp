#include <boost/lexical_cast.hpp>

#include <Server_Common/Common.h>
#include <Server_Common/Database.h>
#include <Server_Common/GamePacketNew.h>
#include <Server_Common/CommonNetwork.h>
#include <Server_Common/UtilMath.h>
#include <Server_Common/PacketContainer.h>
#include <Server_Common/Logger.h>
#include <Server_Common/ExdData.h>

#include "GameCommand.h"
#include "GameCommandHandler.h"

#include "ServerNoticePacket.h"
#include "ActorControlPacket142.h"
#include "ActorControlPacket143.h"
#include "InitUIPacket.h"
#include "GameConnection.h"
#include "ScriptManager.h"

#include "Player.h"
#include "BattleNpc.h"

#include "Zone.h"

#include "ServerZone.h"

#include "StatusEffect.h"
#include "Session.h"
#include <boost/make_shared.hpp>

extern Core::Db::Database g_database;
extern Core::Scripting::ScriptManager g_scriptMgr;
extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;

// instanciate and initialize commands
Core::GameCommandHandler::GameCommandHandler()
{

   // Push all commands onto the register map
   registerCommand( "set", &GameCommandHandler::set, "Loads and injects a premade Packet.", Common::UserLevel::all );
   registerCommand( "get", &GameCommandHandler::get, "Loads and injects a premade Packet.", Common::UserLevel::all );
   registerCommand( "add", &GameCommandHandler::add, "Loads and injects a premade Packet.", Common::UserLevel::all );
   //registerCommand( "debug", &GameCommandHandler::debug, "Loads and injects a premade Packet.", Common::UserLevel::all );
   registerCommand( "inject", &GameCommandHandler::injectPacket, "Loads and injects a premade Packet.", Common::UserLevel::all );
   registerCommand( "script_reload", &GameCommandHandler::scriptReload, "Loads and injects a premade Packet.", Common::UserLevel::all );
   registerCommand( "nudge", &GameCommandHandler::nudge, "Nudges you forward/up/down", Common::UserLevel::all );

}

// clear all loaded commands
Core::GameCommandHandler::~GameCommandHandler()
{
   for( auto it = m_commandMap.begin(); it != m_commandMap.end(); ++it )
      ( *it ).second.reset();
}

// add a command set to the register map
void Core::GameCommandHandler::registerCommand( const std::string& n, Core::GameCommand::pFunc functionPtr,
                                                const std::string& hText, Core::Common::UserLevel uLevel )
{
   m_commandMap[std::string( n )] = boost::make_shared<GameCommand>( n, functionPtr, hText, uLevel );
}

// try to retrieve the command in question, execute if found
void Core::GameCommandHandler::execCommand( char * data, Core::Entity::PlayerPtr pPlayer )
{

   // define callback pointer
   void ( GameCommandHandler::*pf )( char *, Entity::PlayerPtr, boost::shared_ptr< GameCommand > );

   std::string commandString;

   // check if the command has parameters
   std::string tmpCommand = std::string( data );
   std::size_t pos = tmpCommand.find_first_of( " " );

   if( pos != std::string::npos )
      // command has parameters, grab the first part
      commandString = tmpCommand.substr( 0, pos );
   else
      // no parameters, just get the command
      commandString = tmpCommand;

   // try to retrieve the command 
   auto it = m_commandMap.find( commandString );

   if( it == m_commandMap.end() )
      // no command found, do something... or not
      pPlayer->sendUrgent( "Command not found." );
   // TODO Notify the client of the failed command
   else
   {
      // command found, call the callback function and pass parameters if present.
      pf = ( *it ).second->m_pFunc;
      ( this->*pf )( data, pPlayer, ( *it ).second );
      return;
   }


}



///////////////////////////////////////////////////////////////////////////////////////
// Definition of the commands
///////////////////////////////////////////////////////////////////////////////////////

void Core::GameCommandHandler::scriptReload( char * data, Core::Entity::PlayerPtr pPlayer,
                                             boost::shared_ptr<Core::GameCommand> command )
{
   g_scriptMgr.reload();
}

void Core::GameCommandHandler::set( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr<Core::GameCommand> command )
{
   std::string subCommand = "";
   std::string params = "";

   // check if the command has parameters
   std::string tmpCommand = std::string( data + command->getName().length() + 1 );

   std::size_t pos = tmpCommand.find_first_of( " " );

   if( pos != std::string::npos )
      // command has parameters, grab the first part
      subCommand = tmpCommand.substr( 0, pos );
   else
      // no subcommand given
      subCommand = tmpCommand;

   if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
      params = std::string( data + command->getName().length() + 1 + pos + 1 );

   g_log.debug( "[" + std::to_string( pPlayer->getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( ( ( subCommand == "pos" ) || ( subCommand == "posr" ) ) && ( params != "" ) )
   {
      int32_t posX;
      int32_t posY;
      int32_t posZ;

      sscanf( params.c_str(), "%d %d %d", &posX, &posY, &posZ );

      if( ( posX == 0xcccccccc ) || ( posY == 0xcccccccc ) || ( posZ == 0xcccccccc ) )
      {
         pPlayer->sendUrgent( "Syntaxerror." );
         return;
      }

      if( subCommand == "pos" )
         pPlayer->setPosition( static_cast< float >( posX ),
                               static_cast< float >( posY ),
                               static_cast< float >( posZ ) );
      else
         pPlayer->setPosition( pPlayer->getPos().x + static_cast< float >( posX ),
                               pPlayer->getPos().y + static_cast< float >( posY ),
                               pPlayer->getPos().z + static_cast< float >( posZ ) );

      Network::Packets::GamePacketNew< Network::Packets::Server::FFXIVIpcActorSetPos >
         setActorPosPacket( pPlayer->getId() );
      setActorPosPacket.data().x = pPlayer->getPos().x;
      setActorPosPacket.data().y = pPlayer->getPos().y;
      setActorPosPacket.data().z = pPlayer->getPos().z;
      pPlayer->queuePacket( setActorPosPacket );

   }
   else if( ( subCommand == "zone" ) && ( params != "" ) )
   {
      int32_t zoneId;
      sscanf( params.c_str(), "%i", &zoneId );

      if( zoneId < 1 )
         pPlayer->sendUrgent( "Zone id out of range." );
      else
      {
         pPlayer->setPosition( pPlayer->getPos() );
         pPlayer->performZoning( zoneId, pPlayer->getPos(), 0);
      }

   }
   else if( ( subCommand == "hp" ) && ( params != "" ) )
   {
      int32_t hp;
      sscanf( params.c_str(), "%i", &hp );

      pPlayer->setHp( hp );

      auto control = Network::Packets::Server::ActorControlPacket142( pPlayer->getId(), Common::ActorControlType::HpSetStat, 1, pPlayer->getHp() );

      pPlayer->sendToInRangeSet( control, true );

   }

   else if( ( subCommand == "tele" ) && ( params != "" ) )
   {
      int32_t aetheryteId;
      sscanf( params.c_str(), "%i", &aetheryteId );

      pPlayer->teleport( aetheryteId );
   }

   else if( ( subCommand == "unlockaetheryte" ) && ( params != "" ) )
   {
	   for( uint8_t i = 0; i < 255; i++ )
		   pPlayer->registerAetheryte( i );
   }

   else if( ( subCommand == "discovery" ) && ( params != "" ) )
   {
      int32_t map_id;
      int32_t discover_id;
      sscanf( params.c_str(), "%i %i", &map_id, &discover_id );

      Network::Packets::GamePacketNew< Network::Packets::Server::FFXIVIpcDiscovery > discoveryPacket( pPlayer->getId() );
      discoveryPacket.data().map_id = map_id;
      discoveryPacket.data().map_part_id = discover_id;
      pPlayer->queuePacket( discoveryPacket );
   }

   else if( ( subCommand == "discovery_pos" ) && ( params != "" ) )
   {
      int32_t map_id;
      int32_t discover_id;
      int32_t pos_id;
      sscanf( params.c_str(), "%i %i %i", &pos_id, &map_id, &discover_id );

      std::string query2 = "UPDATE IGNORE `discoveryinfo` SET `discover_id` = '" + std::to_string( discover_id ) +
         "' WHERE `discoveryinfo`.`id` = " + std::to_string( pos_id ) + ";";

      std::string query1 = "INSERT IGNORE INTO `discoveryinfo` (`id`, `map_id`, `discover_id`) VALUES ('" + std::to_string( pos_id ) +
         "', '" + std::to_string( map_id ) +
         "', '" + std::to_string( discover_id ) + "')";

      g_database.execute( query1.c_str() );
      g_database.execute( query2.c_str() );

   }

   else if( subCommand == "discovery_reset" )
   {
      pPlayer->resetDiscovery();
      pPlayer->queuePacket( Network::Packets::Server::InitUIPacket( pPlayer ) );
   }
   else if( subCommand == "classjob" )
   {
       int32_t id;

       sscanf( params.c_str(), "%d", &id );

       if( pPlayer->getLevelForClass( static_cast<Core::Common::ClassJob> ( id ) ) == 0 )
       {
           pPlayer->setLevelForClass( 1, static_cast<Core::Common::ClassJob> ( id ) );
           pPlayer->setClassJob( static_cast<Core::Common::ClassJob> ( id ) );
       }
       else
           pPlayer->setClassJob( static_cast<Core::Common::ClassJob> ( id ) );
   }
   else if( subCommand == "no" )
   {
      int32_t id;

      sscanf( params.c_str(), "%d", &id );

     

      uint8_t typeshift = 0x6;
      uint8_t mask = 1 << typeshift;
      id &= mask;
      bool final = ( id & mask ) == mask;
      pPlayer->sendDebug( std::to_string(final) );
   }
   else if( subCommand == "aaah" )
   {
      int32_t id;

      sscanf( params.c_str(), "%d", &id );
      pPlayer->sendDebug( std::to_string( pPlayer->actionHasCastTime( id ) ) );
   }

}

void Core::GameCommandHandler::add( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr<Core::GameCommand> command )
{
   std::string subCommand;
   std::string params = "";

   // check if the command has parameters
   std::string tmpCommand = std::string( data + command->getName().length() + 1 );

   std::size_t pos = tmpCommand.find_first_of( " " );

   if( pos != std::string::npos )
      // command has parameters, grab the first part
      subCommand = tmpCommand.substr( 0, pos );
   else
   {
      // no subcommand given
      subCommand = tmpCommand;
      return;
   }

   if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
      params = std::string( data + command->getName().length() + 1 + pos + 1 );

   g_log.debug( "[" + std::to_string( pPlayer->getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( ( subCommand == "item" ) && ( params != "" ) )
   {
      int32_t catalogId;
      int32_t amount;

      sscanf( params.c_str(), "%d %d", &catalogId, &amount );

      if( amount < 1 || amount > 99 )
      {
         amount = 1;
      }

      if( ( catalogId == 0xcccccccc ) )
      {
         pPlayer->sendUrgent( "Syntaxerror." );
         return;
      }

      if( !pPlayer->addItem( -1, catalogId, amount ) )
         pPlayer->sendUrgent( "Item " + std::to_string( catalogId ) + " not found..." );

   }
   else if( subCommand == "exp" )
   {
      int32_t amount;

      sscanf( params.c_str(), "%d", &amount );

      pPlayer->gainExp( amount );
   }
   else if( subCommand == "status" )
   {
      int32_t id;
      int32_t duration;
      uint16_t param;

      sscanf( params.c_str(), "%d %d %hd", &id, &duration, &param );

      StatusEffect::StatusEffectPtr effect( new StatusEffect::StatusEffect( id, pPlayer, pPlayer, duration, 3000 ) );
      effect->setParam( param );

      pPlayer->addStatusEffect( effect );
   }
   else if( subCommand == "spawn" )
   {
      int32_t model, name;

      sscanf( params.c_str(), "%d %d", &model, &name );

      Entity::BattleNpcPtr pBNpc( new Entity::BattleNpc( model, name, pPlayer->getPos() ) );

      auto pZone = pPlayer->getCurrentZone();
      pBNpc->setCurrentZone( pZone );
      pZone->pushActor( pBNpc );

   }
   else if( subCommand == "op" )
   {
      // temporary research packet
      int32_t opcode;
      sscanf( params.c_str(), "%x", &opcode );
      Network::Packets::GamePacketPtr pPe( new Network::Packets::GamePacket( opcode, 0x30, pPlayer->getId(), pPlayer->getId() ) );
      pPlayer->queuePacket( pPe );
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

      pPlayer->sendNotice( "Injecting ACTOR_CONTROL " + std::to_string( opcode ) );
      
      Network::Packets::GamePacketNew< Network::Packets::Server::FFXIVIpcActorControl143 > actorControl( playerId, pPlayer->getId() );
      actorControl.data().category = opcode;
      actorControl.data().param1 = param1;
      actorControl.data().param2 = param2;
      actorControl.data().param3 = param3;
      actorControl.data().param4 = param4;
      actorControl.data().param5 = param5;
      actorControl.data().param6 = param6;
      pPlayer->queuePacket( actorControl );


      /*sscanf(params.c_str(), "%x %x %x %x %x %x %x", &opcode, &param1, &param2, &param3, &param4, &param5, &param6, &playerId);

      Network::Packets::Server::ServerNoticePacket noticePacket(pPlayer, "Injecting ACTOR_CONTROL " + std::to_string(opcode));

      pPlayer->queuePacket(noticePacket);

      Network::Packets::Server::ActorControlPacket143 controlPacket(pPlayer, opcode,
      param1, param2, param3, param4, param5, param6, playerId);
      pPlayer->queuePacket(controlPacket);*/

   }


}

void Core::GameCommandHandler::get( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr<Core::GameCommand> command )
{
   std::string subCommand;
   std::string params = "";

   // check if the command has parameters
   std::string tmpCommand = std::string( data + command->getName().length() + 1 );

   std::size_t pos = tmpCommand.find_first_of( " " );

   if( pos != std::string::npos )
      // command has parameters, grab the first part
      subCommand = tmpCommand.substr( 0, pos );
   else
      // no subcommand given
      subCommand = tmpCommand;

   if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
      params = std::string( data + command->getName().length() + 1 + pos + 1 );

   g_log.debug( "[" + std::to_string( pPlayer->getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( ( subCommand == "pos" ) )
   {

      int16_t map_id = g_exdData.m_zoneInfoMap[pPlayer->getCurrentZone()->getId()].map_id;

      pPlayer->sendNotice( "Pos:\n" +
                           std::to_string( pPlayer->getPos().x ) + "\n" +
                           std::to_string( pPlayer->getPos().y ) + "\n" +
                           std::to_string( pPlayer->getPos().z ) + "\n" +
                           std::to_string( pPlayer->getRotation() ) + "\nMapId: " +
                           std::to_string( map_id ) + "\nZoneID: " +
                           std::to_string( pPlayer->getCurrentZone()->getId() ) + "\n" );
   }

}

void Core::GameCommandHandler::injectPacket( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr< Core::GameCommand > command )
{
   auto pSession = g_serverZone.getSession( pPlayer->getId() );
   if( pSession )
      pSession->getZoneConnection()->injectPacket( data + 7, pPlayer );
}

void Core::GameCommandHandler::nudge( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command )
{
   std::string subCommand;

   // check if the command has parameters
   std::string tmpCommand = std::string( data + command->getName().length() + 1 );

   std::size_t spos = tmpCommand.find_first_of( " " );

   auto& pos = pPlayer->getPos();

   int32_t offset = 0;
   char direction[20];
   memset( direction, 0, 20 );

   sscanf( tmpCommand.c_str(), "%d %s", &offset, direction );


   if( direction[0] == 'u' || direction[0] == '+' )
   {
      pos.y += offset;
      pPlayer->sendNotice( "nudge: Placing up " + std::to_string( offset ) + " yalms" );
   }
   else if( direction[0] == 'd' || direction[0] == '-' )
   {
      pos.y -= offset;
      pPlayer->sendNotice( "nudge: Placing down " + std::to_string( offset ) + " yalms" );

   }
   else
   {
      float angle = pPlayer->getRotation() + ( PI / 2 );
      pos.x -= offset * cos( angle );
      pos.z += offset * sin( angle );
      pPlayer->sendNotice( "nudge: Placing forward " + std::to_string( offset ) + " yalms" );
   }
   if( offset != 0 )
   {
      Network::Packets::GamePacketNew< Network::Packets::Server::FFXIVIpcActorSetPos >
         setActorPosPacket( pPlayer->getId() );
      setActorPosPacket.data().x = pPlayer->getPos().x;
      setActorPosPacket.data().y = pPlayer->getPos().y;
      setActorPosPacket.data().z = pPlayer->getPos().z;
      setActorPosPacket.data().r16 = Math::Util::floatToUInt16Rot( pPlayer->getRotation() );
      pPlayer->queuePacket( setActorPosPacket );
   }
}
