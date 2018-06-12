#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <boost/format.hpp>
#include <cinttypes>

#include <Common.h>
#include <Version.h>
#include <Network/GamePacketNew.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>

#include "DebugCommand.h"
#include "DebugCommandHandler.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/InitUIPacket.h"
#include "Network/PacketWrappers/PlayerSpawnPacket.h"
#include "Network/GameConnection.h"
#include "Script/ScriptMgr.h"
#include "Script/NativeScriptMgr.h"

#include "Actor/EventObject.h"

#include "Zone/Zone.h"
#include "Zone/InstanceContent.h"
#include "Zone/TerritoryMgr.h"
#include "Event/EventDefs.h"

#include "ServerZone.h"

#include "Session.h"
#include "Framework.h"

extern Core::Framework g_fw;

// instanciate and initialize commands
Core::DebugCommandHandler::DebugCommandHandler()
{
   // Push all commands onto the register map ( command name - function - description - required GM level )
   registerCommand( "set", &DebugCommandHandler::set, "Executes SET commands.", 1 );
   registerCommand( "get", &DebugCommandHandler::get, "Executes GET commands.", 1 );
   registerCommand( "add", &DebugCommandHandler::add, "Executes ADD commands.", 1 );
   registerCommand( "inject", &DebugCommandHandler::injectPacket, "Loads and injects a premade packet.", 1 );
   registerCommand( "injectc", &DebugCommandHandler::injectChatPacket, "Loads and injects a premade chat packet.", 1 );
   registerCommand( "replay", &DebugCommandHandler::replay, "Replays a saved capture folder.", 1 );
   registerCommand( "nudge", &DebugCommandHandler::nudge, "Nudges you forward/up/down.", 1 );
   registerCommand( "info", &DebugCommandHandler::serverInfo, "Show server info.", 0 );
   registerCommand( "help", &DebugCommandHandler::help, "Shows registered commands.", 0 );
   registerCommand( "script", &DebugCommandHandler::script, "Server script utilities.", 1 );
   registerCommand( "instance", &DebugCommandHandler::instance, "Instance utilities", 1 );
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
   auto pLog = g_fw.get< Logger >();
   auto pTerriMgr = g_fw.get< TerritoryMgr >();
   auto pDb = g_fw.get< Db::DbWorkerPool< Db::CharaDbConnection > >();
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

   pLog->debug( "[" + std::to_string( player.getId() ) + "] " +
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
         player.setPos( static_cast< float >( posX ),
                        static_cast< float >( posY ),
                        static_cast< float >( posZ ) );
      else
         player.setPos( player.getPos().x + static_cast< float >( posX ),
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

      pDb->execute( query1 );
      pDb->execute( query2 );

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
   else if ( subCommand == "msqguide" )
   {
      int32_t id;
      sscanf( params.c_str(), "%d", &id );

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcMSQTrackerProgress > msqPacket(
              player.getId());
      msqPacket.data().id = id;
      player.queuePacket( msqPacket );

      player.sendDebug( "MSQ Guide updated " );
   }
   else if ( subCommand == "msqdone")
   {
      int32_t id;
      sscanf( params.c_str(), "%d", &id );

      Network::Packets::ZoneChannelPacket< Network::Packets::Server::FFXIVIpcMSQTrackerComplete > msqPacket ( player.getId() );
      msqPacket.data().id = id;
      player.queuePacket( msqPacket );

      player.sendDebug( "MSQ Guide updated " );
   }
   else if( subCommand == "weatheroverride" || subCommand == "wo" )
   {
      uint32_t weatherId;

      sscanf( params.c_str(), "%d", &weatherId );

      player.getCurrentZone()->setWeatherOverride( static_cast< Common::Weather >( weatherId ) );
   }
   else if( subCommand == "festival" )
   {
      uint16_t festivalId;
      sscanf( params.c_str(), "%hu", &festivalId );

      pTerriMgr->setCurrentFestival( festivalId );
   }
   else if( subCommand == "festivaldisable" )
   {
      pTerriMgr->disableCurrentFestival();
   }
   else
   {
      player.sendUrgent( subCommand + " is not a valid SET command." );
   }

}

void Core::DebugCommandHandler::add( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pLog = g_fw.get< Logger >();
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

   pLog->debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( subCommand == "status" )
   {
      int32_t id;
      int32_t duration;
      uint16_t param;

      sscanf( params.c_str(), "%d %d %hu", &id, &duration, &param );

      auto effect = StatusEffect::make_StatusEffect( id, player.getAsPlayer(), player.getAsPlayer(), duration, 3000 );
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
   else if( subCommand == "op" )
   {
      // temporary research packet
      int32_t opcode;
      sscanf( params.c_str(), "%x", &opcode );
      auto pPe = Network::Packets::make_GamePacket( opcode, 0x30, player.getId(), player.getId() );
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
   auto pLog = g_fw.get< Logger >();
   auto pExdData = g_fw.get< Data::ExdDataGenerated >();
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

   pLog->debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( ( subCommand == "pos" ) )
   {

      int16_t map_id = pExdData->get< Core::Data::TerritoryType >( player.getCurrentZone()->getTerritoryId() )->map;

      player.sendNotice( "Pos:\n" +
                         std::to_string( player.getPos().x ) + "\n" +
                         std::to_string( player.getPos().y ) + "\n" +
                         std::to_string( player.getPos().z ) + "\n" +
                         std::to_string( player.getRot() ) + "\nMapId: " +
                         std::to_string( map_id ) + "\nZoneID: " +
                         std::to_string(player.getCurrentZone()->getTerritoryId() ) + "\n" );
   }
   else
   {
      player.sendUrgent( subCommand + " is not a valid GET command." );
   }

}

void Core::DebugCommandHandler::injectPacket( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pServerZone = g_fw.get< ServerZone >();
   auto pSession = pServerZone->getSession( player.getId() );
   if( pSession )
      pSession->getZoneConnection()->injectPacket( data + 7, player );
}

void Core::DebugCommandHandler::injectChatPacket( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pServerZone = g_fw.get< ServerZone >();
   auto pSession = pServerZone->getSession( player.getId() );
   if( pSession )
      pSession->getChatConnection()->injectPacket( data + 8, player );
}

void Core::DebugCommandHandler::replay( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pLog = g_fw.get< Logger >();
   auto pServerZone = g_fw.get< ServerZone >();
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

   pLog->debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );


   if( subCommand == "start" )
   {
      auto pSession = pServerZone->getSession( player.getId() );
      if( pSession )
         pSession->startReplay( params );
   }
   else if( subCommand == "stop" )
   {
      auto pSession = pServerZone->getSession( player.getId() );
      if( pSession )
         pSession->stopReplay();
   }
   else if( subCommand == "info" )
   {
      auto pSession = pServerZone->getSession( player.getId() );
      if( pSession )
         pSession->sendReplayInfo();
   }
   else
   {
      player.sendUrgent( subCommand + " is not a valid replay command." );
   }


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
      float angle = player.getRot() + ( PI / 2 );
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
      setActorPosPacket.data().r16 = Math::Util::floatToUInt16Rot( player.getRot() );
      player.queuePacket( setActorPosPacket );
   }
}

void Core::DebugCommandHandler::serverInfo( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command )
{
   auto pServerZone = g_fw.get< ServerZone >();
   player.sendDebug( "SapphireZone " + Version::VERSION + "\nRev: " + Version::GIT_HASH );
   player.sendDebug( "Compiled: " __DATE__ " " __TIME__ );
   player.sendDebug( "Sessions: " + std::to_string( pServerZone->getSessionCount() ) );
}

void Core::DebugCommandHandler::script( char* data, Entity::Player &player, boost::shared_ptr< DebugCommand > command )
{
   auto pLog = g_fw.get< Logger >();
   auto pScriptMgr = g_fw.get< Scripting::ScriptMgr >();
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

   // todo: fix params so it's empty if there's no params
   if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
      params = std::string( data + command->getName().length() + 1 + pos + 1 );

   pLog->debug( "[" + std::to_string( player.getId() ) + "] " +
                "subCommand " + subCommand + " params: " + params );

   if( subCommand == "unload" )
   {
      if ( subCommand == params )
         player.sendDebug( "Command failed: requires name of script" );
      else
         if( pScriptMgr->getNativeScriptHandler().unloadScript( params ) )
            player.sendDebug( "Unloaded script successfully." );
         else
            player.sendDebug( "Failed to unload script: " + params );
   }
   else if( subCommand == "find" || subCommand == "f" )
   {
      if( subCommand == params )
         player.sendDebug( "Because reasons of filling chat with nonsense, please enter a search term" );
      else
      {
         std::set< Core::Scripting::ScriptInfo* > scripts;
         pScriptMgr->getNativeScriptHandler().findScripts( scripts, params );

         if( !scripts.empty() )
         {
            player.sendDebug( "Found " + std::to_string( scripts.size() ) + " scripts" );

            for( auto it = scripts.begin(); it != scripts.end(); ++it )
            {
               auto script = *it;
               player.sendDebug( " - '" + script->library_name + "' loaded at @ 0x" +
                                 boost::str( boost::format( "%|X|" ) % script->handle ) +
                                 ", num scripts: " + std::to_string( script->scripts.size() ) );
            }
         }
         else
            player.sendDebug( "No scripts found with search term: " + params );
      }
   }
   else if( subCommand == "load" || subCommand == "l" )
   {
      if( subCommand == params )
         player.sendDebug( "Command failed: requires relative path to script" );
      else
      {
         if ( pScriptMgr->getNativeScriptHandler().loadScript( params ) )
            player.sendDebug( "Loaded '" + params + "' successfully" );
         else
            player.sendDebug( "Failed to load '" + params + "'" );
      }

   }
   else if( subCommand == "queuereload" || subCommand == "qrl" )
   {
      if( subCommand == params )
         player.sendDebug( "Command failed: requires name of script to reload" );
      else
      {
         pScriptMgr->getNativeScriptHandler().queueScriptReload( params );
         player.sendDebug( "Queued script reload for script: " + params );
      }
   }
   else
   {
      player.sendDebug( "Unknown script subcommand: " + subCommand );
   }
}

void Core::DebugCommandHandler::instance( char* data, Entity::Player &player, boost::shared_ptr< DebugCommand > command )
{
   auto pTeriMgr = g_fw.get< TerritoryMgr >();
   std::string cmd( data ), params, subCommand;
   auto cmdPos = cmd.find_first_of( ' ' );

   if( cmdPos != std::string::npos )
   {
      params = cmd.substr( cmdPos + 1 );

      auto p = params.find_first_of( ' ' );

      if( p != std::string::npos )
      {
         subCommand = params.substr( 0, p );
         params = params.substr( subCommand.length() + 1 );
      }
      else
         subCommand = params;
   }

   if( subCommand == "create" || subCommand == "cr" )
   {
      uint32_t instanceContentId;
      sscanf( params.c_str(), "%d", &instanceContentId );

      auto instance = pTeriMgr->createInstanceContent( instanceContentId );
      if( instance )
         player.sendDebug( "Created instance with id: " + std::to_string( instance->getGuId() ) + " -> " + instance->getName() );
      else
         player.sendDebug( "Failed to create instance with id: " + std::to_string( instanceContentId ) );
   }
   else if( subCommand == "bind" )
   {
      uint32_t instanceId;
      sscanf( params.c_str(), "%d", &instanceId );

      auto instance = pTeriMgr->getInstanceZonePtr( instanceId );
      if( instance )
      {
         auto pInstanceContent = instance->getAsInstanceContent();
         pInstanceContent->bindPlayer( player.getId() );
         player.sendDebug(
                 "Now bound to instance with id: " + std::to_string( pInstanceContent->getGuId() ) +
                 " -> " + pInstanceContent->getName() );
      }
      else
         player.sendDebug( "Unknown instance with id: " + std::to_string( instanceId ) );
   }
   else if( subCommand == "unbind" )
   {
      uint32_t instanceId;
      sscanf( params.c_str(), "%d", &instanceId );

      auto instance = pTeriMgr->getInstanceZonePtr( instanceId );
      if( !instance )
      {
         player.sendDebug( "Unknown instance with id: " + std::to_string( instanceId ) );
         return;
      }

      auto pInstanceContent = instance->getAsInstanceContent();
      if( pInstanceContent->isPlayerBound( player.getId() ) )
      {
         pInstanceContent->unbindPlayer( player.getId() );
         player.sendDebug(
                 "Now unbound from instance with id: " + std::to_string( pInstanceContent->getGuId() ) +
                 " -> " + pInstanceContent->getName() );
      }
      else
         player.sendDebug( "Player not bound to instance with id: " + std::to_string( instanceId ) );

   }
   else if( subCommand == "createzone" || subCommand == "crz" )
   {
      uint32_t zoneId;
      sscanf( params.c_str(), "%d", &zoneId );

      auto instance = pTeriMgr->createTerritoryInstance( zoneId );
      if( instance )
         player.sendDebug( "Created instance with id: " + std::to_string( instance->getGuId() ) + " -> " + instance->getName() );
      else
         player.sendDebug( "Failed to create instance with id: " + std::to_string( zoneId ) );
   }
   else if( subCommand == "remove" || subCommand == "rm" )
   {
      uint32_t terriId;
      sscanf( params.c_str(), "%d", &terriId );

      if( pTeriMgr->removeTerritoryInstance( terriId ) )
         player.sendDebug( "Removed instance with id: " + std::to_string( terriId ) );
      else
         player.sendDebug( "Failed to remove instance with id: " + std::to_string( terriId ) );
   }
   else if( subCommand == "return" || subCommand == "ret" )
   {
      player.exitInstance();
   }
   else if( subCommand == "set" )
   {
      uint32_t index;
      uint32_t value;
      sscanf( params.c_str(), "%d %d", &index, &value );


      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if( !instance )
         return;

      instance->setVar( static_cast< uint8_t >( index ), static_cast< uint8_t >( value ) );
   }
   else if( subCommand == "objstate" )
   {
      char objName[128];
      uint8_t state;

      sscanf( params.c_str(), "%s %hhu", objName, &state );

      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if( !instance )
         return;

      auto obj = instance->getEObjByName( objName );
      if( !obj )
         return;

      obj->setState( state );
   }
   else if ( subCommand == "objflag" )
   {
      char objName[256];
      uint32_t state1;
      uint32_t state2;

      sscanf( params.c_str(), "%s %i %i", objName, &state1, &state2 );

      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if( !instance )
         return;

      auto obj = instance->getEObjByName( objName );
      if( !obj ) {
         player.sendDebug( "No eobj found." );
         return;
      }

      obj->setAnimationFlag( state1, state2 );
   }
   else if( subCommand == "seq" )
   {
      uint8_t seq;

      sscanf( params.c_str(), "%hhu", &seq );

      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if( !instance )
         return;

      instance->setSequence( seq );
   }
   else if( subCommand == "branch" )
   {
      uint8_t branch;

      sscanf( params.c_str(), "%hhu", &branch );

      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if( !instance )
         return;

      instance->setBranch( branch );
   }
   else if ( subCommand == "qte_start" )
   {
      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if ( !instance )
         return;

      player.sendDebug( "qte start" );
      instance->startQte();
   }
   else if ( subCommand == "event_start" )
   {
      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if ( !instance )
         return;

      player.sendDebug( "evt start" );
      instance->startEventCutscene();
   }
   else if ( subCommand == "event_end" )
   {
      auto instance = boost::dynamic_pointer_cast< InstanceContent >( player.getCurrentZone() );
      if ( !instance )
         return;

      player.sendDebug( "evt end" );
      instance->endEventCutscene();
   }
   else if( subCommand == "bgm" )
   {
      uint16_t bgmId;
      sscanf( params.c_str(), "%hd", &bgmId );

      if( auto instance = player.getCurrentInstance() )
         instance->setCurrentBGM( bgmId );
   }
   else
   {
      player.sendDebug( "Unknown sub command." );
   }
}
