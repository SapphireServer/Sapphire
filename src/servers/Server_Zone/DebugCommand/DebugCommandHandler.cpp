#include <boost/lexical_cast.hpp>

#include <Server_Common/Common.h>
#include <Server_Common/Version.h>
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Network/CommonNetwork.h>
#include <Server_Common/Util/UtilMath.h>
#include <Server_Common/Network/PacketContainer.h>
#include <Server_Common/Logging/Logger.h>
#include <Server_Common/Exd/ExdData.h>
#include <Server_Common/Database/DatabaseDef.h>

#include "DebugCommand.h"
#include "DebugCommandHandler.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/GameConnection.h"
#include "Script/ScriptManager.h"

#include "Actor/Player.h"
#include "Actor/BattleNpc.h"

#include "Zone/Zone.h"

#include "ServerZone.h"

#include "StatusEffect/StatusEffect.h"
#include "Session.h"
#include <boost/make_shared.hpp>


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
void Core::DebugCommandHandler::registerCommand( const std::string& n, DebugCommand::pFunc functionPtr,
                                                 const std::string& hText, uint8_t uLevel )
{
   m_commandMap[std::string( n )] = boost::make_shared< DebugCommand >( n, functionPtr, hText, uLevel );
}

// try to retrieve the command in question, execute if found
void Core::DebugCommandHandler::execCommand( char * data, Entity::Player& player )
{

   // define callback pointer
   void ( DebugCommandHandler::*pf )( char *, Entity::Player&, boost::shared_ptr< DebugCommand > );

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
      player.sendUrgent( "Command not found." );
   else
   {
      if( player.getGmRank() < it->second->getRequiredGmLevel() )
      {
         player.sendUrgent( "You are not allowed to use this command." );
         return;
      }

      // command found, call the callback function and pass parameters if present.
      pf = ( *it ).second->m_pFunc;
      ( this->*pf )( data, player, ( *it ).second );
      return;
   }


}


///////////////////////////////////////////////////////////////////////////////////////
// Definition of the commands
///////////////////////////////////////////////////////////////////////////////////////

void Core::DebugCommandHandler::scriptReload( char * data, Entity::Player& player,
                                              boost::shared_ptr< DebugCommand > command )
{
   g_scriptMgr.reload();
   player.sendDebug( "Scripts reloaded." );
}

void Core::DebugCommandHandler::help( char* data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   player.sendDebug( "Registered debug commands:" );
   for ( auto cmd : m_commandMap )
   {
      if ( player.getGmRank( ) >= cmd.second->m_gmLevel )
      {
         player.sendDebug( " - " + cmd.first + " - " + cmd.second->getHelpText( ) );
      }
   }
}

void Core::DebugCommandHandler::set( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
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

   g_log.debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( ( ( subCommand == "pos" ) || ( subCommand == "posr" ) ) && ( params != "" ) )
   {
      int32_t posX;
      int32_t posY;
      int32_t posZ;

      sscanf( params.c_str(), "%d %d %d", &posX, &posY, &posZ );

      if( ( posX == 0xcccccccc ) || ( posY == 0xcccccccc ) || ( posZ == 0xcccccccc ) )
      {
         player.sendUrgent( "Syntaxerror." );
         return;
      }

      if( subCommand == "pos" )
         player.setPosition( static_cast< float >( posX ),
                             static_cast< float >( posY ),
                             static_cast< float >( posZ ) );
      else
         player.setPosition( player.getPos().x + static_cast< float >( posX ),
                             player.getPos().y + static_cast< float >( posY ),
                             player.getPos().z + static_cast< float >( posZ ) );

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorSetPos >
         setActorPosPacket( player.getId() );
      setActorPosPacket.data().x = player.getPos().x;
      setActorPosPacket.data().y = player.getPos().y;
      setActorPosPacket.data().z = player.getPos().z;
      player.queuePacket( setActorPosPacket );

   }
   else if( ( subCommand == "tele" ) && ( params != "" ) )
   {
      int32_t aetheryteId;
      sscanf( params.c_str(), "%i", &aetheryteId );

      player.teleport( aetheryteId );
   }
   else if( ( subCommand == "discovery" ) && ( params != "" ) )
   {
      int32_t map_id;
      int32_t discover_id;
      sscanf( params.c_str(), "%i %i", &map_id, &discover_id );

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcDiscovery > discoveryPacket( player.getId() );
      discoveryPacket.data().map_id = map_id;
      discoveryPacket.data().map_part_id = discover_id;
      player.queuePacket( discoveryPacket );
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
      player.resetDiscovery();
      player.queuePacket( Network::Packets::Server::InitUIPacket( player ) );
   }
   else if( subCommand == "classjob" )
   {
       int32_t id;

       sscanf( params.c_str(), "%d", &id );

       if( player.getLevelForClass( static_cast< Common::ClassJob > ( id ) ) == 0 )
       {
           player.setLevelForClass( 1, static_cast< Common::ClassJob > ( id ) );
           player.setClassJob( static_cast< Common::ClassJob > ( id ) );
       }
       else
           player.setClassJob( static_cast< Common::ClassJob > ( id ) );
   }
   else if ( subCommand == "cfpenalty" )
   {
      int32_t minutes;
      sscanf( params.c_str(), "%d", &minutes );

      player.setCFPenaltyMinutes( minutes );
   }
   else if ( subCommand == "eorzeatime" )
   {
      uint64_t timestamp;
      sscanf( params.c_str(), "%" SCNu64, &timestamp );

      player.setEorzeaTimeOffset( timestamp );
      player.sendNotice( "Eorzea time offset: " + std::to_string( timestamp ) );
   }
   else if ( subCommand == "model" )
   {
      uint32_t slot;
      uint32_t val;
      sscanf( params.c_str(), "%d %d", &slot, &val );

      player.setModelForSlot( static_cast< Inventory::EquipSlot >( slot ), val );
      player.sendModel();
      player.sendDebug( "Model updated" );
   }
   else if ( subCommand == "mount" )
   {
      int32_t id;
      sscanf( params.c_str(), "%d", &id );

      player.dismount();
      player.mount( id );
   }
   else
   {
      player.sendUrgent( subCommand + " is not a valid SET command." );
   }

}

void Core::DebugCommandHandler::add( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
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

   g_log.debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


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

void Core::DebugCommandHandler::get( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
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

   g_log.debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( ( subCommand == "pos" ) )
   {

      int16_t map_id = g_exdData.m_zoneInfoMap[player.getCurrentZone()->getId()].map_id;

      player.sendNotice( "Pos:\n" +
                         std::to_string( player.getPos().x ) + "\n" +
                         std::to_string( player.getPos().y ) + "\n" +
                         std::to_string( player.getPos().z ) + "\n" +
                         std::to_string( player.getRotation() ) + "\nMapId: " +
                         std::to_string( map_id ) + "\nZoneID: " +
                         std::to_string( player.getCurrentZone()->getId() ) + "\n" );
   }
   else
   {
      player.sendUrgent( subCommand + " is not a valid GET command." );
   }

}

void Core::DebugCommandHandler::injectPacket( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pSession = g_serverZone.getSession( player.getId() );
   if( pSession )
      pSession->getZoneConnection()->injectPacket( data + 7, player );
}

void Core::DebugCommandHandler::injectChatPacket( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pSession = g_serverZone.getSession( player.getId() );
   if( pSession )
      pSession->getChatConnection()->injectPacket( data + 8, player );
}

void Core::DebugCommandHandler::nudge( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   std::string subCommand;

   // check if the command has parameters
   std::string tmpCommand = std::string( data + command->getName().length() + 1 );

   std::size_t spos = tmpCommand.find_first_of( " " );

   auto& pos = player.getPos();

   int32_t offset = 0;
   char direction[20];
   memset( direction, 0, 20 );

   sscanf( tmpCommand.c_str(), "%d %s", &offset, direction );

   if( direction[0] == 'u' || direction[0] == '+' )
   {
      pos.y += offset;
      player.sendNotice( "nudge: Placing up " + std::to_string( offset ) + " yalms" );
   }
   else if( direction[0] == 'd' || direction[0] == '-' )
   {
      pos.y -= offset;
      player.sendNotice( "nudge: Placing down " + std::to_string( offset ) + " yalms" );

   }
   else
   {
      float angle = player.getRotation() + ( PI / 2 );
      pos.x -= offset * cos( angle );
      pos.z += offset * sin( angle );
      player.sendNotice( "nudge: Placing forward " + std::to_string( offset ) + " yalms" );
   }
   if( offset != 0 )
   {
      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcActorSetPos >
         setActorPosPacket( player.getId() );
      setActorPosPacket.data().x = player.getPos().x;
      setActorPosPacket.data().y = player.getPos().y;
      setActorPosPacket.data().z = player.getPos().z;
      setActorPosPacket.data().r16 = Math::Util::floatToUInt16Rot( player.getRotation() );
      player.queuePacket( setActorPosPacket );
   }
}

void Core::DebugCommandHandler::serverInfo( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   player.sendDebug( "SapphireServer " + Version::VERSION + "\nRev: " + Version::GIT_HASH );
   player.sendDebug( "Compiled: " __DATE__ " " __TIME__ );
   player.sendDebug( "Sessions: " + std::to_string( g_serverZone.getSessionCount() ) );
}

void Core::DebugCommandHandler::unlockCharacter( char* data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   player.unlock( );
}
