#include <cinttypes>

#include <Common.h>
#include <Version.h>
#include <Network/GamePacket.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>
#include <cmath>
#include <Network/PacketWrappers/EffectPacket.h>
#include <Service.h>

#include "DebugCommand/DebugCommand.h"
#include "DebugCommandMgr.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/PlayerSpawnPacket.h"
#include "Network/GameConnection.h"
#include "Script/ScriptMgr.h"
#include "Script/NativeScriptMgr.h"

#include "Actor/EventObject.h"
#include "Actor/BNpc.h"

#include "Territory/Territory.h"
#include "Territory/HousingZone.h"
#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"
#include "Manager/TerritoryMgr.h"
#include "Event/EventDefs.h"

#include "ServerMgr.h"

#include "Session.h"

using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::World::Manager;

// instanciate and initialize commands
Sapphire::World::Manager::DebugCommandMgr::DebugCommandMgr()
{
  // Push all commands onto the register map ( command name - function - description - required GM level )
  registerCommand( "set", &DebugCommandMgr::set, "Executes SET commands.", 1 );
  registerCommand( "get", &DebugCommandMgr::get, "Executes GET commands.", 1 );
  registerCommand( "add", &DebugCommandMgr::add, "Executes ADD commands.", 1 );
  registerCommand( "inject", &DebugCommandMgr::injectPacket, "Loads and injects a premade packet.", 1 );
  registerCommand( "injectc", &DebugCommandMgr::injectChatPacket, "Loads and injects a premade chat packet.", 1 );
  registerCommand( "replay", &DebugCommandMgr::replay, "Replays a saved capture folder.", 1 );
  registerCommand( "nudge", &DebugCommandMgr::nudge, "Nudges you forward/up/down.", 1 );
  registerCommand( "info", &DebugCommandMgr::serverInfo, "Show server info.", 0 );
  registerCommand( "help", &DebugCommandMgr::help, "Shows registered commands.", 0 );
  registerCommand( "script", &DebugCommandMgr::script, "Server script utilities.", 1 );
  registerCommand( "instance", &DebugCommandMgr::instance, "Instance utilities", 1 );
  registerCommand( "questbattle", &DebugCommandMgr::questBattle, "Quest battle utilities", 1 );
  registerCommand( "qb", &DebugCommandMgr::questBattle, "Quest battle utilities", 1 );
  registerCommand( "housing", &DebugCommandMgr::housing, "Housing utilities", 1 );
}

// clear all loaded commands
Sapphire::World::Manager::DebugCommandMgr::~DebugCommandMgr()
{
  for( auto it = m_commandMap.begin(); it != m_commandMap.end(); ++it )
    ( *it ).second.reset();
}

// add a command set to the register map
void Sapphire::World::Manager::DebugCommandMgr::registerCommand( const std::string& n, DebugCommand::pFunc functionPtr,
                                                                 const std::string& hText, uint8_t uLevel )
{
  m_commandMap[ std::string( n ) ] = std::make_shared< DebugCommand >( n, functionPtr, hText, uLevel );
}

// try to retrieve the command in question, execute if found
void Sapphire::World::Manager::DebugCommandMgr::execCommand( char* data, Entity::Player& player )
{

  // define callback pointer
  void ( DebugCommandMgr::*pf )( char*, Entity::Player&, std::shared_ptr< DebugCommand > );

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

void Sapphire::World::Manager::DebugCommandMgr::help( char* data, Entity::Player& player,
                                                      std::shared_ptr< DebugCommand > command )
{
  player.sendDebug( "Registered debug commands:" );
  for( auto cmd : m_commandMap )
  {
    if( player.getGmRank() >= cmd.second->m_gmLevel )
    {
      player.sendDebug( " - {0} - {1}", cmd.first, cmd.second->getHelpText() );
    }
  }
}

void Sapphire::World::Manager::DebugCommandMgr::set( char* data, Entity::Player& player,
                                                     std::shared_ptr< DebugCommand > command )
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
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

  Logger::debug( "[{0}] subCommand: {1} params: {1}", player.getId(), subCommand, params );

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

    auto setActorPosPacket = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
    setActorPosPacket->data().x = player.getPos().x;
    setActorPosPacket->data().y = player.getPos().y;
    setActorPosPacket->data().z = player.getPos().z;
    player.queuePacket( setActorPosPacket );

  }
  else if( ( subCommand == "tele" ) && ( params != "" ) )
  {
    int32_t aetheryteId;
    sscanf( params.c_str(), "%i", &aetheryteId );

    player.teleport( static_cast< uint16_t >( aetheryteId ) );
  }
  else if( ( subCommand == "discovery" ) && ( params != "" ) )
  {
    int32_t map_id;
    int32_t discover_id;
    sscanf( params.c_str(), "%i %i", &map_id, &discover_id );

    auto discoveryPacket = makeZonePacket< FFXIVIpcDiscovery >( player.getId() );
    discoveryPacket->data().mapId = static_cast< uint32_t >( map_id );
    discoveryPacket->data().mapPartId = static_cast< uint32_t >( discover_id );
    player.queuePacket( discoveryPacket );
  }
  else if( subCommand == "discovery_reset" )
  {
    player.resetDiscovery();
    player.queuePacket( std::make_shared< PlayerSetupPacket >( player ) );
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
  else if( subCommand == "cfpenalty" )
  {
    int32_t minutes;
    sscanf( params.c_str(), "%d", &minutes );

    player.setCFPenaltyMinutes( static_cast< uint32_t >( minutes ) );
  }
  else if( subCommand == "eorzeatime" )
  {
    uint64_t timestamp;
    sscanf( params.c_str(), "%" SCNu64, &timestamp );

    player.setEorzeaTimeOffset( timestamp );
    player.sendNotice( "Eorzea time offset: {0}", timestamp );
  }
  else if( subCommand == "mount" )
  {
    int32_t id;
    sscanf( params.c_str(), "%d", &id );

    player.dismount();
    player.mount( static_cast< uint32_t >( id ) );
  }
  else if( subCommand == "msqguide" )
  {
    int32_t id;
    sscanf( params.c_str(), "%d", &id );

    auto msqPacket = makeZonePacket< FFXIVIpcMSQTrackerProgress >( player.getId() );
    msqPacket->data().id = static_cast< uint32_t >( id );
    player.queuePacket( msqPacket );

    player.sendDebug( "MSQ Guide updated " );
  }
  else if( subCommand == "msqdone" )
  {
    int32_t id;
    sscanf( params.c_str(), "%d", &id );

    auto msqPacket = makeZonePacket< FFXIVIpcMSQTrackerComplete >( player.getId() );
    msqPacket->data().id = static_cast< uint32_t >( id );
    player.queuePacket( msqPacket );

    player.sendDebug( "MSQ Guide updated " );
  }
  else if( subCommand == "weatheroverride" || subCommand == "wo" )
  {
    uint32_t weatherId;

    sscanf( params.c_str(), "%d", &weatherId );

    player.getCurrentTerritory()->setWeatherOverride( static_cast< Common::Weather >( weatherId ) );
  }
  else if( subCommand == "festival" )
  {
    uint16_t festivalId;
    uint16_t additionalId;

    sscanf( params.c_str(), "%hu %hu", &festivalId, &additionalId );

    terriMgr.setCurrentFestival( festivalId, additionalId );
  }
  else if( subCommand == "festivaldisable" )
  {
    terriMgr.disableCurrentFestival();
  }
  else if( subCommand == "BitFlag" )
  {
    uint16_t questId;
    uint8_t questBit;
    int8_t BitFlag;
    sscanf( params.c_str(), "%hhu %hu %hhu", &BitFlag, &questId, &questBit );

    if( !player.hasQuest( questId ) )
    {
      player.sendDebug( "Player doesn't have the quest with ID#: {0}", questId );
      return;
    }
    if( questBit == 0 || questId == 0 )
    {
      player.sendDebug( "Params are not correct" );
      return;
    }

    switch( BitFlag )
    {
      case 8:
      {
        player.setQuestBitFlag8( questId, questBit, true );
        break;
      }
      case 16:
      {
        player.setQuestBitFlag16( questId, questBit, true );
        break;
      }
      case 24:
      {
        player.setQuestBitFlag24( questId, questBit, true );
        break;
      }
      case 32:
      {
        player.setQuestBitFlag32( questId, questBit, true );
        break;
      }
      case 40:
      {
        player.setQuestBitFlag40( questId, questBit, true );
        break;
      }
      case 48:
      {
        player.setQuestBitFlag48( questId, questBit, true );
        break;
      }
    }
  }
  else if( subCommand == "mobaggro" )
  {
    auto inRange = player.getInRangeActors();

    for( auto actor : inRange )
    {
      if( actor->getId() == player.getTargetId() && actor->getAsChara()->isAlive() )
      {
        actor->getAsBNpc()->onActionHostile( player.getAsChara() );
      }
    }
  }
  else if( subCommand == "gauge" )
  {
    uint8_t values[15];
    std::memset( values, 0, sizeof( values ) );
    sscanf( params.c_str(), "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            &values[ 0 ], &values[ 1 ], &values[ 2 ], &values[ 3 ], &values[ 4 ],
            &values[ 5 ], &values[ 6 ], &values[ 7 ], &values[ 8 ], &values[ 9 ],
            &values[ 10 ], &values[ 11 ], &values[ 12 ], &values[ 13 ], &values[ 14 ] );
    player.gaugeSetRaw( values );
  }
  else if( subCommand == "visual" )
  {
    int32_t id;
    sscanf( params.c_str(), "%d", &id );
    auto pPacket = makeZonePacket< FFXIVIpcCharaVisualEffect >( player.getId() );
    pPacket->data().id = id;
    player.queuePacket( pPacket );
  }
  else
  {
    player.sendUrgent( "{0} is not a valid SET command.", subCommand );
  }

}

void Sapphire::World::Manager::DebugCommandMgr::add( char* data, Entity::Player& player,
                                                     std::shared_ptr< DebugCommand > command )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

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

  Logger::debug( "[" + std::to_string( player.getId() ) + "] " +
                 "subCommand " + subCommand + " params: " + params );


  if( subCommand == "status" )
  {
    int32_t id;
    int32_t duration;
    uint16_t param;

    sscanf( params.c_str(), "%d %d %hu", &id, &duration, &param );

    auto effect = StatusEffect::make_StatusEffect( id, player.getAsPlayer(), player.getAsPlayer(),
                                                   duration, 3000 );
    effect->setParam( param );

    player.addStatusEffect( effect );
  }
  else if( subCommand == "title" )
  {
    uint32_t titleId;
    sscanf( params.c_str(), "%u", &titleId );

    player.addTitle( static_cast< uint16_t >( titleId ) );
    player.sendNotice( "Added title (id#{0})", titleId );
  }
  else if( subCommand == "bnpc" )
  {
    auto bNpcTemplate = serverMgr.getBNpcTemplate( params );

    if( !bNpcTemplate )
    {
      player.sendNotice( "Template {0} not found in cache!", params );
      return;
    }
    auto playerZone = player.getCurrentTerritory();
    auto pBNpc = std::make_shared< Entity::BNpc >( playerZone->getNextActorId(),
                                                   bNpcTemplate,
                                                   player.getPos().x,
                                                   player.getPos().y,
                                                   player.getPos().z,
                                                   player.getRot(),
                                                   1, 1000, playerZone );



    //pBNpc->setCurrentZone( playerZone );
    //pBNpc->setPos( player.getPos().x, player.getPos().y, player.getPos().z );

    playerZone->pushActor( pBNpc );


  }
  else if( subCommand == "op" )
  {
    // temporary research packet
    int32_t opcode;
    sscanf( params.c_str(), "%x", &opcode );
    // TODO: fix for new setup
    //auto pPe = Network::Packets::make_GamePacket( opcode, 0x30, player.getId(), player.getId() );
    //player.queuePacket( pPe );
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

    sscanf( params.c_str(), "%x %x %x %x %x %x %x %x", &opcode, &param1, &param2, &param3, &param4, &param5, &param6,
            &playerId );

    player.sendNotice( "Injecting ACTOR_CONTROL {0}", opcode );

    auto actorControl = makeZonePacket< FFXIVIpcActorControlSelf >( playerId, player.getId() );
    actorControl->data().category = static_cast< uint16_t >( opcode );
    actorControl->data().param1 = static_cast< uint16_t >( param1 );
    actorControl->data().param2 = static_cast< uint16_t >( param2 );
    actorControl->data().param3 = static_cast< uint16_t >( param3 );
    actorControl->data().param4 = static_cast< uint16_t >( param4 );
    actorControl->data().param5 = static_cast< uint16_t >( param5 );
    actorControl->data().param6 = static_cast< uint16_t >( param6 );
    player.queuePacket( actorControl );


    /*sscanf(params.c_str(), "%x %x %x %x %x %x %x", &opcode, &param1, &param2, &param3, &param4, &param5, &param6, &playerId);

    Network::Packets::Server::ServerNoticePacket noticePacket( player, "Injecting ACTOR_CONTROL " + std::to_string( opcode ) );

    player.queuePacket( noticePacket );

    Network::Packets::Server::ActorControlSelfPacket controlPacket( player, opcode,
    param1, param2, param3, param4, param5, param6, playerId );
    player.queuePacket( controlPacket );*/

  }
  else if( subCommand == "unlock" )
  {
    uint32_t id;

    sscanf( params.c_str(), "%d", &id );
    player.learnAction( static_cast< uint16_t >( id ) );
  }
  else if ( subCommand == "effect")
  {
    uint16_t param1;
    sscanf( params.c_str(), "%hu", &param1 );

    auto effectPacket = std::make_shared< Server::EffectPacket >( player.getId(), player.getTargetId(), param1 );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( player.getRot() ) );

    Common::EffectEntry entry{};
    entry.value = static_cast< int16_t >( param1 );
    entry.effectType = Common::ActionEffectType::Damage;
    entry.param0 = static_cast< uint8_t >( Common::ActionHitSeverityType::NormalDamage );

    effectPacket->addEffect( entry );

    auto sequence = player.getCurrentTerritory()->getNextEffectSequence();
    effectPacket->setSequence( sequence );

//    effectPacket->setAnimationId( param1 );
//    effectPacket->setEffectFlags( 0 );

    player.queuePacket( effectPacket );
  }
  else
  {
    player.sendUrgent( "{0} is not a valid ADD command.", subCommand );
  }


}

void Sapphire::World::Manager::DebugCommandMgr::get( char* data, Entity::Player& player,
                                                     std::shared_ptr< DebugCommand > command )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
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

  Logger::debug( "[{0}] subCommand: {1} params: {2}", player.getId(), subCommand, params );

  if( ( subCommand == "pos" ) )
  {

    int16_t map_id = exdData.get< Sapphire::Data::TerritoryType >( player.getCurrentTerritory()->getTerritoryTypeId() )->map;

    player.sendNotice( "Pos:\n {0}\n {1}\n {2}\n {3}\n MapId: {4}\n ZoneId:{5}",
                       player.getPos().x, player.getPos().y, player.getPos().z,
                       player.getRot(), map_id, player.getCurrentTerritory()->getTerritoryTypeId() );
  }
  else
  {
    player.sendUrgent( "{0} is not a valid GET command.", subCommand );
  }

}

void
Sapphire::World::Manager::DebugCommandMgr::injectPacket( char* data, Entity::Player& player,
                                                         std::shared_ptr< DebugCommand > command )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

  auto pSession = serverMgr.getSession( player.getId() );
  if( pSession )
    pSession->getZoneConnection()->injectPacket( data + 7, player );
}

void Sapphire::World::Manager::DebugCommandMgr::injectChatPacket( char* data, Entity::Player& player,
                                                                  std::shared_ptr< DebugCommand > command )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

  auto pSession = serverMgr.getSession( player.getId() );
  if( pSession )
    pSession->getChatConnection()->injectPacket( data + 8, player );
}

void Sapphire::World::Manager::DebugCommandMgr::replay( char* data, Entity::Player& player,
                                                        std::shared_ptr< DebugCommand > command )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

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

  Logger::debug( "[" + std::to_string( player.getId() ) + "] " +
                 "subCommand " + subCommand + " params: " + params );


  if( subCommand == "start" )
  {
    auto pSession = serverMgr.getSession( player.getId() );
    if( pSession )
      pSession->startReplay( params );
  }
  else if( subCommand == "stop" )
  {
    auto pSession = serverMgr.getSession( player.getId() );
    if( pSession )
      pSession->stopReplay();
  }
  else if( subCommand == "info" )
  {
    auto pSession = serverMgr.getSession( player.getId() );
    if( pSession )
      pSession->sendReplayInfo();
  }
  else
  {
    player.sendUrgent( "{0} is not a valid replay command.", subCommand );
  }


}

void Sapphire::World::Manager::DebugCommandMgr::nudge( char* data, Entity::Player& player,
                                                       std::shared_ptr< DebugCommand > command )
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

  if( direction[ 0 ] == 'u' || direction[ 0 ] == '+' )
  {
    pos.y += offset;
    player.sendNotice( "nudge: Placing up {0} yalms", offset );
  }
  else if( direction[ 0 ] == 'd' || direction[ 0 ] == '-' )
  {
    pos.y -= offset;
    player.sendNotice( "nudge: Placing down {0} yalms", offset );

  }
  else
  {
    float angle = player.getRot() + ( PI / 2 );
    pos.x -= offset * cos( angle );
    pos.z += offset * sin( angle );
    player.sendNotice( "nudge: Placing forward {0} yalms", offset );
  }
  if( offset != 0 )
  {
    auto setActorPosPacket = makeZonePacket< FFXIVIpcActorSetPos >( player.getId() );
    setActorPosPacket->data().x = player.getPos().x;
    setActorPosPacket->data().y = player.getPos().y;
    setActorPosPacket->data().z = player.getPos().z;
    setActorPosPacket->data().r16 = Common::Util::floatToUInt16Rot( player.getRot() );
    player.queuePacket( setActorPosPacket );
  }
}

void
Sapphire::World::Manager::DebugCommandMgr::serverInfo( char* data, Entity::Player& player,
                                                       std::shared_ptr< DebugCommand > command )
{
  auto& serverMgr = Common::Service< World::ServerMgr >::ref();

  player.sendDebug( "SapphireZone {0} \nRev: {1}", Version::VERSION, Version::GIT_HASH );
  player.sendDebug( "Compiled: " __DATE__ " " __TIME__ );
  player.sendDebug( "Sessions: {0}", serverMgr.getSessionCount() );
}

void Sapphire::World::Manager::DebugCommandMgr::script( char* data, Entity::Player& player,
                                                        std::shared_ptr< DebugCommand > command )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
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

  Logger::debug( "[{0}] subCommand: {1} params: {2}", player.getId(), subCommand, params );

  if( subCommand == "unload" )
  {
    if( subCommand == params )
      player.sendDebug( "Command failed: requires name of script" );
    else if( scriptMgr.getNativeScriptHandler().unloadScript( params ) )
      player.sendDebug( "Unloaded script successfully." );
    else
      player.sendDebug( "Failed to unload script: {0}", params );
  }
  else if( subCommand == "find" || subCommand == "f" )
  {
    if( subCommand == params )
      player.sendDebug( "Because reasons of filling chat with nonsense, please enter a search term" );
    else
    {
      std::set< Sapphire::Scripting::ScriptInfo* > scripts;
      scriptMgr.getNativeScriptHandler().findScripts( scripts, params );

      if( !scripts.empty() )
      {
        player.sendDebug( "Found {0} scripts", scripts.size() );

        for( auto it = scripts.begin(); it != scripts.end(); ++it )
        {
          auto script = *it;
          player.sendDebug( " - '{0}', num scripts: {1}", script->library_name, script->scripts.size() );
        }
      }
      else
        player.sendDebug( "No scripts found with search term: {0}", params );
    }
  }
  else if( subCommand == "load" || subCommand == "l" )
  {
    if( subCommand == params )
      player.sendDebug( "Command failed: requires relative path to script" );
    else
    {
      if( scriptMgr.getNativeScriptHandler().loadScript( params ) )
        player.sendDebug( "Loaded '{0}' successfully", params );
      else
        player.sendDebug( "Failed to load '{0}'", params );
    }

  }
  else if( subCommand == "queuereload" || subCommand == "qrl" )
  {
    if( subCommand == params )
      player.sendDebug( "Command failed: requires name of script to reload" );
    else
    {
      scriptMgr.getNativeScriptHandler().queueScriptReload( params );
      player.sendDebug( "Queued script reload for script: {0}", params );
    }
  }
  else
  {
    player.sendDebug( "Unknown script subcommand: {0}", subCommand );
  }
}

void Sapphire::World::Manager::DebugCommandMgr::instance( char* data, Entity::Player& player,
                                                          std::shared_ptr< DebugCommand > command )
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
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
    uint32_t contentFinderConditionId;
    sscanf( params.c_str(), "%d", &contentFinderConditionId );

    auto instance = terriMgr.createInstanceContent( contentFinderConditionId );
    if( instance )
      player.sendDebug( "Created instance with id#{0} -> {1}", instance->getGuId(), instance->getName() );
    else
      player.sendDebug( "Failed to create instance with id#{0}", contentFinderConditionId );
  }
  else if( subCommand == "bind" )
  {
    uint32_t instanceId;
    sscanf( params.c_str(), "%d", &instanceId );

    auto terri = terriMgr.getTerritoryByGuId( instanceId );
    if( terri )
    {
      auto pInstanceContent = terri->getAsInstanceContent();
      if( !pInstanceContent )
      {
        player.sendDebug( "Instance id#{} is not an InstanceContent territory.", instanceId );
        return;
      }

      pInstanceContent->bindPlayer( player.getId() );
      player.sendDebug(
        "Now bound to instance with id: " + std::to_string( pInstanceContent->getGuId() ) +
        " -> " + pInstanceContent->getName() );
    }
    else
      player.sendDebug( "Unknown instance with id#{0}", instanceId );
  }
  else if( subCommand == "unbind" )
  {
    uint32_t instanceId;
    sscanf( params.c_str(), "%d", &instanceId );

    auto instance = terriMgr.getTerritoryByGuId( instanceId );
    if( !instance )
    {
      player.sendDebug( "Unknown instance with id#{0} ", instanceId );
      return;
    }

    auto pInstanceContent = instance->getAsInstanceContent();
    if( pInstanceContent->isPlayerBound( player.getId() ) )
    {
      pInstanceContent->unbindPlayer( player.getId() );
      player.sendDebug( "Now unbound from instance with id#{0} -> {1}", pInstanceContent->getGuId(), pInstanceContent->getName() );
    }
    else
      player.sendDebug( "Player not bound to instance with id#{0}", instanceId );

  }
  else if( subCommand == "createzone" || subCommand == "crz" )
  {
    uint32_t zoneId;
    sscanf( params.c_str(), "%d", &zoneId );

    auto instance = terriMgr.createTerritoryInstance( zoneId );
    if( instance )
      player.sendDebug(
        "Created instance with id: " + std::to_string( instance->getGuId() ) + " -> " + instance->getName() );
    else
      player.sendDebug( "Failed to create instance with id#{0}", zoneId );
  }
  else if( subCommand == "remove" || subCommand == "rm" )
  {
    uint32_t terriId;
    sscanf( params.c_str(), "%d", &terriId );

    if( terriMgr.removeTerritoryInstance( terriId ) )
      player.sendDebug( "Removed instance with id#{0}", terriId );
    else
      player.sendDebug( "Failed to remove instance with id#{0}", terriId );
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


    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->setVar( static_cast< uint8_t >( index ), static_cast< uint8_t >( value ) );
  }
  else if( subCommand == "objstate" )
  {
    char objName[128];
    uint8_t state;

    sscanf( params.c_str(), "%s %hhu", objName, &state );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
      return;

    obj->setState( state );
  }
  else if( subCommand == "objflag" )
  {
    char objName[256];
    uint32_t state1;
    uint32_t state2;

    sscanf( params.c_str(), "%s %i %i", objName, &state1, &state2 );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
    {
      player.sendDebug( "No eobj found." );
      return;
    }

    obj->setAnimationFlag( state1, state2 );
  }
  else if( subCommand == "seq" )
  {
    uint8_t seq;

    sscanf( params.c_str(), "%hhu", &seq );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->setSequence( seq );
  }
  else if( subCommand == "branch" )
  {
    uint8_t branch;

    sscanf( params.c_str(), "%hhu", &branch );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->setBranch( branch );
  }
  else if( subCommand == "qte_start" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    player.sendDebug( "qte start" );
    instance->startQte();
  }
  else if( subCommand == "event_start" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
      return;

    player.sendDebug( "evt start" );
    instance->startEventCutscene();
  }
  else if( subCommand == "event_end" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( player.getCurrentTerritory() );
    if( !instance )
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

void Sapphire::World::Manager::DebugCommandMgr::questBattle( char* data, Entity::Player& player,
                                                             std::shared_ptr< DebugCommand > command )
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
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
    uint32_t contentFinderConditionId;
    sscanf( params.c_str(), "%d", &contentFinderConditionId );

    auto instance = terriMgr.createQuestBattle( contentFinderConditionId );
    if( instance )
      player.sendDebug( "Created instance with id#{0} -> {1}", instance->getGuId(), instance->getName() );
    else
      player.sendDebug( "Failed to create instance with id#{0}", contentFinderConditionId );
  }
  else if( subCommand == "complete" )
  {

    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->success();

  }
  else if( subCommand == "fail" )
  {

    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->fail();

  }
  else if( subCommand == "createzone" || subCommand == "crz" )
  {
    uint32_t zoneId;
    sscanf( params.c_str(), "%d", &zoneId );

    auto instance = terriMgr.createTerritoryInstance( zoneId );
    if( instance )
      player.sendDebug(
        "Created instance with id: " + std::to_string( instance->getGuId() ) + " -> " + instance->getName() );
    else
      player.sendDebug( "Failed to create instance with id#{0}", zoneId );
  }
  else if( subCommand == "remove" || subCommand == "rm" )
  {
    uint32_t terriId;
    sscanf( params.c_str(), "%d", &terriId );

    if( terriMgr.removeTerritoryInstance( terriId ) )
      player.sendDebug( "Removed instance with id#{0}", terriId );
    else
      player.sendDebug( "Failed to remove instance with id#{0}", terriId );
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


    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->setVar( static_cast< uint8_t >( index ), static_cast< uint8_t >( value ) );
  }
  else if( subCommand == "objstate" )
  {
    char objName[128];
    uint8_t state;

    sscanf( params.c_str(), "%s %hhu", objName, &state );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
      return;

    obj->setState( state );
  }
  else if( subCommand == "objflag" )
  {
    char objName[256];
    uint32_t state1;
    uint32_t state2;

    sscanf( params.c_str(), "%s %i %i", objName, &state1, &state2 );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
    {
      player.sendDebug( "No eobj found." );
      return;
    }

    obj->setAnimationFlag( state1, state2 );
  }
  else if( subCommand == "seq" )
  {
    uint8_t seq;

    sscanf( params.c_str(), "%hhu", &seq );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->setSequence( seq );
  }
  else if( subCommand == "branch" )
  {
    uint8_t branch;

    sscanf( params.c_str(), "%hhu", &branch );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    instance->setBranch( branch );
  }
  else if( subCommand == "qte_start" )
  {
    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    player.sendDebug( "qte start" );
    instance->startQte();
  }
  else if( subCommand == "event_start" )
  {
    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
      return;

    player.sendDebug( "evt start" );
    instance->startEventCutscene();
  }
  else if( subCommand == "event_end" )
  {
    auto instance = std::dynamic_pointer_cast< QuestBattle >( player.getCurrentTerritory() );
    if( !instance )
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

void Sapphire::World::Manager::DebugCommandMgr::housing( char* data, Entity::Player& player,
                                                         std::shared_ptr< DebugCommand > command )
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
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

//  if( subCommand == "permission" || subCommand == "perm" )
//  {
//    uint8_t permissionSet;
//    sscanf( params.c_str(), "%hhu", &permissionSet );
//
//    if ( permissionSet < 5 )
//    {
//      auto pZone = player.getCurrentTerritory();
//      if( terriMgr.isHousingTerritory( pZone->getTerritoryTypeId() ) )
//      {
//        auto pHousing = std::dynamic_pointer_cast< HousingZone >( pZone );
//        if( pHousing )
//        {
//          // todo: wat?
//          Common::LandIdent ident {};
//          ident.wardNum = pHousing->getWardNum();
//          ident.territoryTypeId = pHousing->getTerritoryTypeId();
//
//          player.setLandFlags( permissionSet, 0, pHousing->getLandSetId(), ident );
//          player.sendLandFlags();
//        }
//        else
//          player.sendDebug( "You aren't in a housing Territory." );
//      }
//    }
//    else
//      player.sendDebug( "PermissionSet out of range." );
//  }
  else
  {
    player.sendDebug( "Unknown sub command." );
  }
}
