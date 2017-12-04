#include <boost/lexical_cast.hpp>

#include <src/servers/Server_Common/Common.h>
#include <src/servers/Server_Common/Version.h>
#include <src/servers/Server_Common/Network/GamePacketNew.h>
#include <src/servers/Server_Common/Network/CommonNetwork.h>
#include <src/servers/Server_Common/Util/UtilMath.h>
#include <src/servers/Server_Common/Network/PacketContainer.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <src/servers/Server_Common/Exd/ExdData.h>

#include "DebugCommand.h"
#include "DebugCommandHandler.h"

#include "src/servers/Server_Zone/Network/PacketWrappers/ServerNoticePacket.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket142.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/ActorControlPacket143.h"
#include "src/servers/Server_Zone/Network/PacketWrappers/InitUIPacket.h"
#include "src/servers/Server_Zone/Network/GameConnection.h"
#include "src/servers/Server_Zone/Script/ScriptManager.h"

#include "src/servers/Server_Zone/Actor/Player.h"
#include "src/servers/Server_Zone/Actor/BattleNpc.h"

#include "src/servers/Server_Zone/Zone/Zone.h"

#include "src/servers/Server_Zone/ServerZone.h"

#include "src/servers/Server_Zone/StatusEffect/StatusEffect.h"
#include "src/servers/Server_Zone/Session.h"
#include <boost/make_shared.hpp>

#include <Server_Common/Database/DatabaseDef.h>

#include <cinttypes>

extern Core::Scripting::ScriptManager g_scriptMgr;
extern Core::Data::ExdData g_exdData;
extern Core::Logger g_log;
extern Core::ServerZone g_serverZone;

// instanciate and initialize commands
Core::DebugCommandHandler::DebugCommandHandler()
{
   // Push all commands onto the register map ( command name - function - description - required GM level )
   registerCommand( "set", &DebugCommandHandler::set, "Loads and injects a premade Packet.", 1 );
   registerCommand( "get", &DebugCommandHandler::get, "Loads and injects a premade Packet.", 1 );
   registerCommand( "add", &DebugCommandHandler::add, "Loads and injects a premade Packet.", 1 );
   registerCommand( "inject", &DebugCommandHandler::injectPacket, "Loads and injects a premade packet.", 1 );
   registerCommand( "injectc", &DebugCommandHandler::injectChatPacket, "Loads and injects a premade chat packet.", 1 );
   registerCommand( "script_reload", &DebugCommandHandler::scriptReload, "Reload all server scripts", 1 );
   registerCommand( "nudge", &DebugCommandHandler::nudge, "Nudges you forward/up/down", 1 );
   registerCommand( "info", &DebugCommandHandler::serverInfo, "Send server info", 0 );
   registerCommand( "unlock", &DebugCommandHandler::unlockCharacter, "Unlock character", 1 );
   registerCommand( "help", &DebugCommandHandler::help, "Shows registered commands", 0 );
}

// clear all loaded commands
Core::DebugCommandHandler::~DebugCommandHandler()
{
   for( auto it = m_commandMap.begin(); it != m_commandMap.end(); ++it )
      ( *it ).second.reset();
}

// add a command set to the register map
void Core::DebugCommandHandler::registerCommand( const std::string& n, Core::DebugCommand::pFunc functionPtr,
                                                 const std::string& hText, uint8_t uLevel )
{
   m_commandMap[std::string( n )] = boost::make_shared<DebugCommand>( n, functionPtr, hText, uLevel );
}

// try to retrieve the command in question, execute if found
void Core::DebugCommandHandler::execCommand( char * data, Core::Entity::PlayerPtr pPlayer )
{

   // define callback pointer
   void ( DebugCommandHandler::*pf )( char *, Entity::PlayerPtr, boost::shared_ptr< DebugCommand > );

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
   else
   {
      if( pPlayer->getGmRank() < it->second->getRequiredGmLevel() )
      {
         pPlayer->sendUrgent( "You are not allowed to use this command." );
         return;
      }

      // command found, call the callback function and pass parameters if present.
      pf = ( *it ).second->m_pFunc;
      ( this->*pf )( data, pPlayer, ( *it ).second );
      return;
   }


}


///////////////////////////////////////////////////////////////////////////////////////
// Definition of the commands
///////////////////////////////////////////////////////////////////////////////////////

void Core::DebugCommandHandler::scriptReload( char * data, Core::Entity::PlayerPtr pPlayer,
                                              boost::shared_ptr<Core::DebugCommand> command )
{
   g_scriptMgr.reload();
   pPlayer->sendDebug( "Scripts reloaded." );
}

void Core::DebugCommandHandler::help( char* data, Entity::PlayerPtr pPlayer, boost::shared_ptr< Core::DebugCommand > command )
{
   pPlayer->sendDebug( "Registered debug commands:" );
   for( auto cmd : m_commandMap )
   {
      if( pPlayer->getGmRank() >= cmd.second->m_gmLevel )
      {
         pPlayer->sendDebug( " - " + cmd.first + " - " + cmd.second->getHelpText() );
      }
   }
}

void Core::DebugCommandHandler::set( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr<Core::DebugCommand> command )
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

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorSetPos >
         setActorPosPacket( pPlayer->getId() );
      setActorPosPacket.data().x = pPlayer->getPos().x;
      setActorPosPacket.data().y = pPlayer->getPos().y;
      setActorPosPacket.data().z = pPlayer->getPos().z;
      pPlayer->queuePacket( setActorPosPacket );

   }
   else if( ( subCommand == "tele" ) && ( params != "" ) )
   {
      int32_t aetheryteId;
      sscanf( params.c_str(), "%i", &aetheryteId );

      pPlayer->teleport( aetheryteId );
   }
   else if( ( subCommand == "discovery" ) && ( params != "" ) )
   {
      int32_t map_id;
      int32_t discover_id;
      sscanf( params.c_str(), "%i %i", &map_id, &discover_id );

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcDiscovery > discoveryPacket( pPlayer->getId() );
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

      g_charaDb.execute( query1 );
      g_charaDb.execute( query2 );

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
   else if( subCommand == "cfpenalty" )
   {
      int32_t minutes;
      sscanf( params.c_str(), "%d", &minutes );

      pPlayer->setCFPenaltyMinutes( minutes );
   }
   else if( subCommand == "eorzeatime" )
   {
      uint64_t timestamp;
      sscanf( params.c_str(), "%" SCNu64, &timestamp );

      pPlayer->setEorzeaTimeOffset( timestamp );
      pPlayer->sendNotice( "Eorzea time offset: " + std::to_string( timestamp ) );
   }
   else if( subCommand == "model" )
   {
      uint32_t slot;
      uint32_t val;
      sscanf( params.c_str(), "%d %d", &slot, &val );

      pPlayer->setModelForSlot( static_cast<Inventory::EquipSlot>( slot ), val );
      pPlayer->sendModel();
      pPlayer->sendDebug( "Model updated" );
   }
   else if( subCommand == "mount" )
   {
      int32_t id;
      sscanf( params.c_str(), "%d", &id );

      pPlayer->dismount();
      pPlayer->mount( id );
   }
   else
   {
      pPlayer->sendUrgent( subCommand + " is not a valid SET command." );
   }

}

void Core::DebugCommandHandler::add( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr<Core::DebugCommand> command )
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


   if( subCommand == "status" )
   {
      int32_t id;
      int32_t duration;
      uint16_t param;

      sscanf( params.c_str(), "%d %d %hu", &id, &duration, &param );

      StatusEffect::StatusEffectPtr effect( new StatusEffect::StatusEffect( id, pPlayer, pPlayer, duration, 3000 ) );
      effect->setParam( param );

      pPlayer->addStatusEffect( effect );
   }
   else if( subCommand == "title" )
   {
      uint32_t titleId;
      sscanf( params.c_str(), "%u", &titleId );

      pPlayer->addTitle( titleId );
      pPlayer->sendNotice( "Added title (ID: " + std::to_string( titleId ) + ")" );
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

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorControl143 > actorControl( playerId, pPlayer->getId() );
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
   else if( subCommand == "unlock" )
   {
      int32_t id;
      sscanf( params.c_str(), "%d", &id );

      pPlayer->learnAction( id );
   }
   else if( subCommand == "enablecompanion" )
   {
      pPlayer->learnAction( 17 );
   }
   else
   {
      pPlayer->sendUrgent( subCommand + " is not a valid ADD command." );
   }


}

void Core::DebugCommandHandler::get( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr<Core::DebugCommand> command )
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


   if( subCommand == "pos" )
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
   else
   {
      pPlayer->sendUrgent( subCommand + " is not a valid GET command." );
   }

}

void Core::DebugCommandHandler::injectPacket( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr< Core::DebugCommand > command )
{
   auto pSession = g_serverZone.getSession( pPlayer->getId() );
   if( pSession )
      pSession->getZoneConnection()->injectPacket( data + 7, pPlayer );
}

void Core::DebugCommandHandler::injectChatPacket( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr< Core::DebugCommand > command )
{
   auto pSession = g_serverZone.getSession( pPlayer->getId() );
   if( pSession )
      pSession->getChatConnection()->injectPacket( data + 8, pPlayer );
}

void Core::DebugCommandHandler::nudge( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<DebugCommand> command )
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
      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorSetPos >
         setActorPosPacket( pPlayer->getId() );
      setActorPosPacket.data().x = pPlayer->getPos().x;
      setActorPosPacket.data().y = pPlayer->getPos().y;
      setActorPosPacket.data().z = pPlayer->getPos().z;
      setActorPosPacket.data().r16 = Math::Util::floatToUInt16Rot( pPlayer->getRotation() );
      pPlayer->queuePacket( setActorPosPacket );
   }
}

void Core::DebugCommandHandler::serverInfo( char * data, Core::Entity::PlayerPtr pPlayer, boost::shared_ptr< Core::DebugCommand > command )
{
   pPlayer->sendDebug( "SapphireServer " + Version::VERSION + "\nRev: " + Version::GIT_HASH );
   pPlayer->sendDebug( "Compiled: " __DATE__ " " __TIME__ );
   pPlayer->sendDebug( "Sessions: " + std::to_string( g_serverZone.getSessionCount() ) );
}

void Core::DebugCommandHandler::unlockCharacter( char* data, Entity::PlayerPtr pPlayer, boost::shared_ptr< Core::DebugCommand > command )
{
   pPlayer->unlock();
}
