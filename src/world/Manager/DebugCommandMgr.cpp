#include <cinttypes>

#include <Common.h>
#include <Version.h>
#include <Network/GamePacket.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Network/PacketContainer.h>
#include <Logging/Logger.h>
#include <Exd/ExdData.h>
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

#include "Action/ActionLutData.h"

#include "Territory/Territory.h"
#include "Territory/HousingZone.h"
#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"

#include "Manager/TerritoryMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/AchievementMgr.h"
#include "Manager/WarpMgr.h"
#include "Manager/LinkshellMgr.h"
#include "Manager/RNGMgr.h"

#include "Event/EventDefs.h"
#include "ContentFinder/ContentFinder.h"

#include "Linkshell/Linkshell.h"

#include "WorldServer.h"

#include "Session.h"


using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

// instanciate and initialize commands
DebugCommandMgr::DebugCommandMgr()
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
  registerCommand( "linkshell", &DebugCommandMgr::linkshell, "Linkshell creation", 1 );
  registerCommand( "cf", &DebugCommandMgr::contentFinder, "Content-Finder", 1 );
  registerCommand( "ew", &DebugCommandMgr::easyWarp, "Easy warping", 1 );
  registerCommand( "reload", &DebugCommandMgr::hotReload, "Reloads a resource", 1 );
}

// clear all loaded commands
DebugCommandMgr::~DebugCommandMgr()
{
  for( auto & it : m_commandMap )
    it.second.reset();
}

// add a command set to the register map
void DebugCommandMgr::registerCommand( const std::string& n, DebugCommand::pFunc functionPtr, const std::string& hText, uint8_t uLevel )
{
  m_commandMap[ std::string( n ) ] = std::make_shared< DebugCommand >( n, functionPtr, hText, uLevel );
}

// try to retrieve the command in question, execute if found
void DebugCommandMgr::execCommand( char* data, Entity::Player& player )
{

  // define callback pointer
  void ( DebugCommandMgr::*pf )( char*, Entity::Player&, std::shared_ptr< DebugCommand > );

  std::string commandString;

  // check if the command has parameters
  std::string tmpCommand = std::string( data );
  std::size_t pos = tmpCommand.find_first_of( ' ' );

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
    PlayerMgr::sendUrgent( player, "Command not found." );
  else
  {
    if( player.getGmRank() < it->second->getRequiredGmLevel() )
    {
      PlayerMgr::sendUrgent( player, "You are not allowed to use this command." );
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

void DebugCommandMgr::help( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  PlayerMgr::sendDebug( player, "Registered debug commands:" );
  for( const auto& cmd : m_commandMap )
  {
    if( player.getGmRank() >= cmd.second->m_gmLevel )
    {
      PlayerMgr::sendDebug( player, " - {0} - {1}", cmd.first, cmd.second->getHelpText() );
    }
  }
}

void DebugCommandMgr::set( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Sapphire::Common::Service< Sapphire::World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto pCurrentZone = terriMgr.getTerritoryByGuId( player.getTerritoryId() );

  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  std::string subCommand;
  std::string params;

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

  if( pos != std::string::npos )
    // command has parameters, grab the first part
    subCommand = tmpCommand.substr( 0, pos );
  else
    // no subcommand given
    subCommand = tmpCommand;

  if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
    params = std::string( data + command->getName().length() + 1 + pos + 1 );

  Logger::debug( "[{0}] subCommand: {1} params: {1}", player.getId(), subCommand, params );

  if( ( ( subCommand == "pos" ) || ( subCommand == "posr" ) ) && ( !params.empty() ) )
  {
    int32_t posX;
    int32_t posY;
    int32_t posZ;

    sscanf( params.c_str(), "%d %d %d", &posX, &posY, &posZ );

    if( ( posX == 0xcccccccc ) || ( posY == 0xcccccccc ) || ( posZ == 0xcccccccc ) )
    {
      PlayerMgr::sendUrgent( player, "Syntaxerror." );
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

    auto setActorPosPacket = makeZonePacket< FFXIVIpcWarp >( player.getId() );
    setActorPosPacket->data().x = player.getPos().x;
    setActorPosPacket->data().y = player.getPos().y;
    setActorPosPacket->data().z = player.getPos().z;
    pSession->getZoneConnection()->queueOutPacket( setActorPosPacket );

  }
  else if( ( subCommand == "tele" ) && ( !params.empty() ) )
  {
    int32_t aetheryteId;
    sscanf( params.c_str(), "%i", &aetheryteId );

    player.teleport( static_cast< uint16_t >( aetheryteId ) );
  }
  else if( ( subCommand == "discovery" ) && ( !params.empty() ) )
  {
    int32_t map_id;
    int32_t discover_id;
    sscanf( params.c_str(), "%i %i", &map_id, &discover_id );

    auto discoveryPacket = makeZonePacket< FFXIVIpcDiscoveryReply >( player.getId() );
    discoveryPacket->data().mapId = static_cast< uint32_t >( map_id );
    discoveryPacket->data().mapPartId = static_cast< uint32_t >( discover_id );
    pSession->getZoneConnection()->queueOutPacket( discoveryPacket );
  }
  else if( subCommand == "discovery_reset" )
  {
    player.resetDiscovery();
    pSession->getZoneConnection()->queueOutPacket( std::make_shared< PlayerSetupPacket >( player ) );
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
    PlayerMgr::sendServerNotice( player, "Eorzea time offset: {0}", timestamp );
  }
  else if( subCommand == "setMount" )
  {
    int32_t id;
    sscanf( params.c_str(), "%d", &id );

    player.setMount( 0 );
    player.setMount( static_cast< uint32_t >( id ));
  }
  else if( subCommand == "weatheroverride" || subCommand == "wo" )
  {
    uint32_t weatherId;

    sscanf( params.c_str(), "%d", &weatherId );

    pCurrentZone->setWeatherOverride( static_cast< Common::Weather >( weatherId ) );
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
      PlayerMgr::sendDebug( player, "Player doesn't have the quest with ID#: {0}", questId );
      return;
    }
    if( questBit == 0 || questId == 0 )
    {
      PlayerMgr::sendDebug( player, "Params are not correct" );
      return;
    }

    auto questIdx = player.getQuestIndex( questId );
    auto& quest = player.getQuestByIndex( questIdx );

    switch( BitFlag )
    {
      case 8:
      {
        quest.setBitFlag8( questBit, true );
        break;
      }
      case 16:
      {
        quest.setBitFlag16( questBit, true );
        break;
      }
      case 24:
      {
        quest.setBitFlag24( questBit, true );
        break;
      }
      case 32:
      {
        quest.setBitFlag32( questBit, true );
        break;
      }
      case 40:
      {
        quest.setBitFlag40( questBit, true );
        break;
      }
      case 48:
      {
        quest.setBitFlag48( questBit, true );
        break;
      }
    }
    player.updateQuest( quest );
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
  else if( subCommand == "recastreset" )
  {
    player.resetRecastGroups();
    PlayerMgr::sendDebug( player, "All recast groups cleared." );
  }
  else if( subCommand == "freecompany" )
  {
    auto fcPacket = makeZonePacket< FFXIVIpcFreeCompany >( player.getId() );
    fcPacket->data().Crest = 0x0001000100010001;
    strcpy( fcPacket->data().Tag, "Wang" );
    pSession->getZoneConnection()->queueOutPacket( fcPacket );

    auto fcResultPacket = makeZonePacket< FFXIVIpcGetFcStatusResult >( player.getId() );
    fcResultPacket->data().FreeCompanyID = 1;
    fcResultPacket->data().AuthorityList = 1;
    fcResultPacket->data().HierarchyType = 1;
    fcResultPacket->data().GrandCompanyID = 1;
    fcResultPacket->data().FcRank = 8;
    fcResultPacket->data().CrestID = 0x0001000100010001;
    pSession->getZoneConnection()->queueOutPacket( fcResultPacket );
  }
  else
  {
    PlayerMgr::sendUrgent( player, "{0} is not a valid SET command.", subCommand );
  }

}

void DebugCommandMgr::add( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto pCurrentZone = terriMgr.getTerritoryByGuId( player.getTerritoryId() );

  std::string subCommand;
  std::string params;

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

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

    auto effect = StatusEffect::make_StatusEffect( id, player.getAsPlayer(), player.getAsPlayer(), duration, 3000 );
    effect->setParam( param );

    player.addStatusEffect( effect );
  }
  else if( subCommand == "title" )
  {
    uint32_t titleId;
    sscanf( params.c_str(), "%u", &titleId );

    player.addTitle( static_cast< uint16_t >( titleId ) );
    PlayerMgr::sendServerNotice( player, "Added title (id#{0})", titleId );
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

    uint32_t opcode;
    uint32_t param1;
    uint32_t param2;
    uint32_t param3;
    uint32_t param4;
    uint32_t param5;
    uint32_t param6;
    uint32_t playerId;

    sscanf( params.c_str(), "%x %x %x %x %x %x %x %x", &opcode, &playerId, &param1,
            &param2, &param3, &param4, &param5, &param6 );

    PlayerMgr::sendServerNotice( player, "Injecting ACTOR_CONTROL {0}", opcode );

    auto actorControl = makeZonePacket< FFXIVIpcActorControl >( playerId, playerId );
    actorControl->data().category = static_cast< uint16_t >( opcode );
    actorControl->data().param1 = param1;
    actorControl->data().param2 = param2;
    actorControl->data().param3 = param3;
    actorControl->data().param4 = param4;
    pSession->getZoneConnection()->queueOutPacket( actorControl );


    /*sscanf(params.c_str(), "%x %x %x %x %x %x %x", &opcode, &param1, &param2, &param3, &param4, &param5, &param6, &playerId);

    Network::Packets::Server::ServerNoticePacket noticePacket( player, "Injecting ACTOR_CONTROL " + std::to_string( opcode ) );

    player.queuePacket( noticePacket );

    Network::Packets::Server::ActorControlSelfPacket controlPacket( player, opcode,
    param1, param2, param3, param4, param5, param6, playerId );
    player.queuePacket( controlPacket );*/

  }
  else if( subCommand == "actrls" )
  {

    // temporary research packet

    uint32_t opcode;
    uint32_t param1;
    uint32_t param2;
    uint32_t param3;
    uint32_t param4;
    uint32_t param5;
    uint32_t param6;
    uint32_t playerId;

    sscanf( params.c_str(), "%x %x %x %x %x %x %x %x", &opcode, &playerId, &param1,
            &param2, &param3, &param4, &param5, &param6 );

    PlayerMgr::sendServerNotice( player, "Injecting ACTOR_CONTROL {0}", opcode );

    auto actorControl = makeZonePacket< FFXIVIpcActorControlSelf >( playerId, playerId );
    actorControl->data().category = static_cast< uint16_t >( opcode );
    actorControl->data().param1 = param1;
    actorControl->data().param2 = param2;
    actorControl->data().param3 = param3;
    actorControl->data().param4 = param4;
    actorControl->data().param5 = param5;
    actorControl->data().param6 = param6;
    pSession->getZoneConnection()->queueOutPacket( actorControl );


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
    player.setRewardFlag( static_cast< Common::UnlockEntry >( id ) );
  }
  else if( subCommand == "effect" )
  {
    uint16_t param1;
    sscanf( params.c_str(), "%hu", &param1 );

    auto effectPacket = std::make_shared< EffectPacket >( player.getId(), param1 );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( player.getRot() ) );
    effectPacket->setTargetActor( static_cast< uint32_t >( player.getTargetId() ) );

    Common::CalcResultParam entry{};
    entry.Value = static_cast< int16_t >( param1 );
    entry.Type = Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
    entry.Arg0 = static_cast< uint8_t >( Common::ActionHitSeverityType::NormalDamage );

    effectPacket->addTargetEffect( entry, static_cast< uint64_t >( player.getId() ) );

    auto sequence = pCurrentZone->getNextEffectSequence();
    effectPacket->setSequence( sequence );

//    effectPacket->setAnimationId( param1 );
//    effectPacket->setEffectFlags( 0 );

    pSession->getZoneConnection()->queueOutPacket( effectPacket );
  }
  else if( subCommand == "achvGeneral" )
  {
    uint32_t achvSubtype;
    uint32_t progress;

    sscanf( params.c_str(), "%u %u", &achvSubtype, &progress );

    auto& achvMgr = Common::Service< Manager::AchievementMgr >::ref();

    achvMgr.progressAchievementByType< Common::Achievement::Type::General >( player, achvSubtype, progress );
  }
  else
  {
    PlayerMgr::sendUrgent( player, "{0} is not a valid ADD command.", subCommand );
  }

}

void DebugCommandMgr::get( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  std::string subCommand;
  std::string params;

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

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

    int16_t map_id = exdData.getRow< Excel::TerritoryType >( player.getTerritoryTypeId() )->data().Map;

    PlayerMgr::sendServerNotice( player, "Pos:\n {0}\n {1}\n {2}\n {3}\n MapId: {4}\n ZoneId:{5}",
                             player.getPos().x, player.getPos().y, player.getPos().z,
                             player.getRot(), map_id, player.getTerritoryTypeId() );
  }
  else
  {
    PlayerMgr::sendUrgent( player, "{0} is not a valid GET command.", subCommand );
  }

}

void DebugCommandMgr::injectPacket( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto pSession = server.getSession( player.getId() );
  if( pSession )
    pSession->getZoneConnection()->injectPacket( data + 7, player );
}

void DebugCommandMgr::injectChatPacket( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto pSession = server.getSession( player.getId() );
  if( pSession )
    pSession->getChatConnection()->injectPacket( data + 8, player );
}

void DebugCommandMgr::replay( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  std::string subCommand;
  std::string params;

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

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
    auto pSession = server.getSession( player.getId() );
    if( pSession )
      pSession->startReplay( params );
  }
  else if( subCommand == "stop" )
  {
    auto pSession = server.getSession( player.getId() );
    if( pSession )
      pSession->stopReplay();
  }
  else if( subCommand == "info" )
  {
    auto pSession = server.getSession( player.getId() );
    if( pSession )
      pSession->sendReplayInfo();
  }
  else
  {
    PlayerMgr::sendUrgent( player, "{0} is not a valid replay command.", subCommand );
  }


}

void DebugCommandMgr::nudge( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Sapphire::Common::Service< Sapphire::World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );

  std::string subCommand;

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t spos = tmpCommand.find_first_of( ' ' );

  auto& pos = player.getPos();

  int32_t offset = 0;
  char direction[20];
  memset( direction, 0, 20 );

  sscanf( tmpCommand.c_str(), "%d %s", &offset, direction );

  if( direction[ 0 ] == 'u' || direction[ 0 ] == '+' )
  {
    pos.y += offset;
    PlayerMgr::sendServerNotice( player, "nudge: Placing up {0} yalms", offset );
  }
  else if( direction[ 0 ] == 'd' || direction[ 0 ] == '-' )
  {
    pos.y -= offset;
    PlayerMgr::sendServerNotice( player, "nudge: Placing down {0} yalms", offset );

  }
  else
  {
    float angle = player.getRot() + ( PI / 2 );
    pos.x -= offset * cos( angle );
    pos.z += offset * sin( angle );
    PlayerMgr::sendServerNotice( player, "nudge: Placing forward {0} yalms", offset );
  }
  if( offset != 0 )
  {
    auto setActorPosPacket = makeZonePacket< FFXIVIpcWarp >( player.getId() );
    setActorPosPacket->data().x = player.getPos().x;
    setActorPosPacket->data().y = player.getPos().y;
    setActorPosPacket->data().z = player.getPos().z;
    setActorPosPacket->data().Dir = Common::Util::floatToUInt16Rot( player.getRot() );
    pSession->getZoneConnection()->queueOutPacket( setActorPosPacket );
  }
}

void DebugCommandMgr::serverInfo( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  PlayerMgr::sendDebug( player, "SapphireZone {0} \nRev: {1}", Version::VERSION, Version::GIT_HASH );
  PlayerMgr::sendDebug( player, "Compiled: " __DATE__ " " __TIME__ );
  PlayerMgr::sendDebug( player, "Sessions: {0}", server.getSessionCount() );
}

void DebugCommandMgr::script( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  std::string subCommand;
  std::string params;

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

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
      PlayerMgr::sendDebug( player, "Command failed: requires name of script" );
    else if( scriptMgr.getNativeScriptHandler().unloadScript( params ) )
      PlayerMgr::sendDebug( player, "Unloaded script successfully." );
    else
      PlayerMgr::sendDebug( player, "Failed to unload script: {0}", params );
  }
  else if( subCommand == "find" || subCommand == "f" )
  {
    if( subCommand == params )
      PlayerMgr::sendDebug( player, "Because reasons of filling chat with nonsense, please enter a search term" );
    else
    {
      std::set< Sapphire::Scripting::ScriptInfo* > scripts;
      scriptMgr.getNativeScriptHandler().findScripts( scripts, params );

      if( !scripts.empty() )
      {
        PlayerMgr::sendDebug( player, "Found {0} scripts", scripts.size() );

        for( auto script : scripts )
        {
          PlayerMgr::sendDebug( player, " - '{0}', num scripts: {1}", script->library_name, script->scripts.size() );
        }
      }
      else
        PlayerMgr::sendDebug( player, "No scripts found with search term: {0}", params );
    }
  }
  else if( subCommand == "load" || subCommand == "l" )
  {
    if( subCommand == params )
      PlayerMgr::sendDebug( player, "Command failed: requires relative path to script" );
    else
    {
      if( scriptMgr.getNativeScriptHandler().loadScript( params ) )
        PlayerMgr::sendDebug( player, "Loaded '{0}' successfully", params );
      else
        PlayerMgr::sendDebug( player, "Failed to load '{0}'", params );
    }

  }
  else if( subCommand == "queuereload" || subCommand == "qrl" )
  {
    if( subCommand == params )
      PlayerMgr::sendDebug( player, "Command failed: requires name of script to reload" );
    else
    {
      scriptMgr.getNativeScriptHandler().queueScriptReload( params );
      PlayerMgr::sendDebug( player, "Queued script reload for script: {0}", params );
    }
  }
  else
  {
    PlayerMgr::sendDebug( player, "Unknown script subcommand: {0}", subCommand );
  }
}

void DebugCommandMgr::instance( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto pCurrentZone = terriMgr.getTerritoryByGuId( player.getTerritoryId() );

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
      PlayerMgr::sendDebug( player, "Created instance with id#{0} -> {1}", instance->getGuId(), instance->getName() );
    else
      PlayerMgr::sendDebug( player, "Failed to create instance with id#{0}", contentFinderConditionId );
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
        PlayerMgr::sendDebug( player, "Instance id#{} is not an InstanceContent territory.", instanceId );
        return;
      }

      pInstanceContent->bindPlayer( player.getId() );
      PlayerMgr::sendDebug( player,
        "Now bound to instance with id: " + std::to_string( pInstanceContent->getGuId() ) +
        " -> " + pInstanceContent->getName() );
    }
    else
      PlayerMgr::sendDebug( player, "Unknown instance with id#{0}", instanceId );
  }
  else if( subCommand == "unbind" )
  {
    uint32_t instanceId;
    sscanf( params.c_str(), "%d", &instanceId );

    auto instance = terriMgr.getTerritoryByGuId( instanceId );
    if( !instance )
    {
      PlayerMgr::sendDebug( player, "Unknown instance with id#{0} ", instanceId );
      return;
    }

    auto pInstanceContent = instance->getAsInstanceContent();
    if( pInstanceContent->isPlayerBound( player.getId() ) )
    {
      pInstanceContent->unbindPlayer( player.getId() );
      PlayerMgr::sendDebug( player, "Now unbound from instance with id#{0} -> {1}", pInstanceContent->getGuId(), pInstanceContent->getName() );
    }
    else
      PlayerMgr::sendDebug( player, "Player not bound to instance with id#{0}", instanceId );

  }
  else if( subCommand == "createzone" || subCommand == "crz" )
  {
    uint32_t zoneId;
    sscanf( params.c_str(), "%d", &zoneId );

    auto instance = terriMgr.createTerritoryInstance( zoneId );
    if( instance )
      PlayerMgr::sendDebug( player,
        "Created instance with id: " + std::to_string( instance->getGuId() ) + " -> " + instance->getName() );
    else
      PlayerMgr::sendDebug( player, "Failed to create instance with id#{0}", zoneId );
  }
  else if( subCommand == "remove" || subCommand == "rm" )
  {
    uint32_t terriId;
    sscanf( params.c_str(), "%d", &terriId );

    if( terriMgr.removeTerritoryInstance( terriId ) )
      PlayerMgr::sendDebug( player, "Removed instance with id#{0}", terriId );
    else
      PlayerMgr::sendDebug( player, "Failed to remove instance with id#{0}", terriId );
  }
  else if( subCommand == "return" || subCommand == "ret" )
  {
    player.exitInstance();
  }
  else if( subCommand == "stringendomode" || subCommand == "sm" )
  {
      uint32_t mode;
      sscanf( params.c_str(), "%d", &mode );
      if( mode < 5 )
      {
          auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
          if( !instance )
              return;

          instance->sendStringendoMode( mode );
      }
  }
  else if( subCommand == "todo" )
  {
      auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
      if( !instance )
          return;

      instance->sendInvalidateTodoList();

      PlayerMgr::sendDebug( player, "sendInvalidateTodoList executed!" );
  }
  else if( subCommand == "time" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    uint32_t time;
    sscanf( params.c_str(), "%d", &time );

    instance->setExpireValue( time );

    PlayerMgr::sendDebug( player, "Content timer updated!" );
  }
  else if( subCommand == "fail" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    uint8_t reason;
    sscanf( params.c_str(), "%hhu", &reason );

    instance->terminate( reason );
  }
  else if( subCommand == "set" )
  {
    uint32_t index;
    uint32_t value;
    sscanf( params.c_str(), "%d %d", &index, &value );


    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    instance->setVar( static_cast< uint8_t >( index ), static_cast< uint8_t >( value ) );
  }
  else if( subCommand == "objstate" )
  {
    char objName[128];
    uint8_t state;

    sscanf( params.c_str(), "%s %hhu", objName, &state );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
      return;

    obj->setPermissionInvisibility( state );
  }
  else if( subCommand == "objflag" )
  {
    char objName[256];
    uint32_t state1;
    uint32_t state2;

    sscanf( params.c_str(), "%s %i %i", objName, &state1, &state2 );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
    {
      PlayerMgr::sendDebug( player, "No eobj found." );
      return;
    }

    obj->setAnimationFlag( state1, state2 );
  }
  else if( subCommand == "seq" )
  {
    uint8_t seq;

    sscanf( params.c_str(), "%hhu", &seq );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    instance->setSequence( seq );
  }
  else if( subCommand == "flags" )
  {
    uint8_t flags;

    sscanf( params.c_str(), "%hhu", &flags );

    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    instance->setFlags( flags );
  }
  else if( subCommand == "qte_start" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    PlayerMgr::sendDebug( player, "qte start" );
    instance->startQte();
  }
  else if( subCommand == "event_start" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    PlayerMgr::sendDebug( player, "evt start" );
    instance->startEventCutscene();
  }
  else if( subCommand == "event_end" )
  {
    auto instance = std::dynamic_pointer_cast< InstanceContent >( pCurrentZone );
    if( !instance )
      return;

    PlayerMgr::sendDebug( player, "evt end" );
    instance->endEventCutscene();
  }
  else if( subCommand == "bgm" )
  {
    uint16_t bgmId;
    sscanf( params.c_str(), "%hd", &bgmId );

    if( auto instance = pCurrentZone->getAsInstanceContent() )
      instance->setCurrentBGM( bgmId );
  }
  else
  {
    PlayerMgr::sendDebug( player, "Unknown sub command." );
  }
}

void DebugCommandMgr::questBattle( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto pCurrentZone = terriMgr.getTerritoryByGuId( player.getTerritoryId() );
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
      PlayerMgr::sendDebug( player, "Created instance with id#{0} -> {1}", instance->getGuId(), instance->getName() );
    else
      PlayerMgr::sendDebug( player, "Failed to create instance with id#{0}", contentFinderConditionId );
  }
  else if( subCommand == "complete" )
  {

    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    instance->success();

  }
  else if( subCommand == "fail" )
  {

    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
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
      PlayerMgr::sendDebug( player,
        "Created instance with id: " + std::to_string( instance->getGuId() ) + " -> " + instance->getName() );
    else
      PlayerMgr::sendDebug( player, "Failed to create instance with id#{0}", zoneId );
  }
  else if( subCommand == "remove" || subCommand == "rm" )
  {
    uint32_t terriId;
    sscanf( params.c_str(), "%d", &terriId );

    if( terriMgr.removeTerritoryInstance( terriId ) )
      PlayerMgr::sendDebug( player, "Removed instance with id#{0}", terriId );
    else
      PlayerMgr::sendDebug( player, "Failed to remove instance with id#{0}", terriId );
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


    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    instance->setVar( static_cast< uint8_t >( index ), static_cast< uint8_t >( value ) );
  }
  else if( subCommand == "objstate" )
  {
    char objName[128];
    uint8_t state;

    sscanf( params.c_str(), "%s %hhu", objName, &state );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
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

    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    auto obj = instance->getEObjByName( objName );
    if( !obj )
    {
      PlayerMgr::sendDebug( player, "No eobj found." );
      return;
    }

    obj->setAnimationFlag( state1, state2 );
  }
  else if( subCommand == "seq" )
  {
    uint8_t seq;

    sscanf( params.c_str(), "%hhu", &seq );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    instance->setSequence( seq );
  }
  else if( subCommand == "flags" )
  {
    uint8_t flags;

    sscanf( params.c_str(), "%hhu", &flags );

    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    instance->setFlags( flags );
  }
  else if( subCommand == "qte_start" )
  {
    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    PlayerMgr::sendDebug( player, "qte start" );
    instance->startQte();
  }
  else if( subCommand == "event_start" )
  {
    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    PlayerMgr::sendDebug( player, "evt start" );
    instance->startEventCutscene();
  }
  else if( subCommand == "event_end" )
  {
    auto instance = std::dynamic_pointer_cast< QuestBattle >( pCurrentZone );
    if( !instance )
      return;

    PlayerMgr::sendDebug( player, "evt end" );
    instance->endEventCutscene();
  }
  else if( subCommand == "bgm" )
  {
    uint16_t bgmId;
    sscanf( params.c_str(), "%hd", &bgmId );

    if( auto instance = pCurrentZone->getAsInstanceContent() )
      instance->setCurrentBGM( bgmId );
  }
  else
  {
    PlayerMgr::sendDebug( player, "Unknown sub command." );
  }
}

void DebugCommandMgr::housing( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
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
//      auto pZone = teriMgr.getTerritoryFromGuid( player.getTerritoryId() );
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
//          PlayerMgr::sendDebug( player, "You aren't in a housing Territory." );
//      }
//    }
//    else
//      PlayerMgr::sendDebug( player, "PermissionSet out of range." );
//  }
  else
  {
    PlayerMgr::sendDebug( player, "Unknown sub command." );
  }
}

void DebugCommandMgr::linkshell( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command )
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

  if( subCommand != "" )
  {
    auto lsName = subCommand;

    auto& lsMgr = Common::Service< Manager::LinkshellMgr >::ref();

    auto lsPtr = lsMgr.createLinkshell( lsName, player );

    PlayerMgr::sendDebug( player, "Created LS name " + lsPtr->getName() + " ID: " + std::to_string( lsPtr->getId() ) );
  }
}

void DebugCommandMgr::contentFinder( char *data, Sapphire::Entity::Player &player, std::shared_ptr< DebugCommand > command )
{
  auto& cf = Common::Service< ContentFinder >::ref();

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

  if( subCommand == "pop" )
  {
    uint32_t registerId;
    sscanf( params.c_str(), "%d", &registerId );

    auto content = cf.findContentByRegisterId( registerId );
    if( !content )
    {
      PlayerMgr::sendDebug( player, "Content for registerId#{0} not found!", registerId );
      return;
    }
    content->setState( QueuedContentState::MatchingComplete );
  }

}

void DebugCommandMgr::easyWarp( char* data, Sapphire::Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  std::string subCommand;
  std::string params = "";

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

  if( pos != std::string::npos )
    // command has parameters, grab the first part
    subCommand = tmpCommand.substr( 0, pos );
  else
    // no subcommand given
    subCommand = tmpCommand;

  if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
    params = std::string( data + command->getName().length() + 1 + pos + 1 );

  Logger::debug( "[{0}] subCommand: {1} params: {2}", player.getId(), subCommand, params );

  auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto& warpMgr = Common::Service< WarpMgr >::ref();

  if( ( subCommand == "waking_sands" ) )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 140 )->getGuId(), { -483.257f, 17.0748f, -386.731f }, 1.61298f );
  else if( subCommand == "rising_stones" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 156 )->getGuId(), { 22.2674f, 21.2527f, -634.261f }, -0.369245f );
  else if( subCommand == "little_solace" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 152 )->getGuId(), { 24.557f, -3.78776f, 212.615f }, 2.59117f );
  else if( subCommand == "adders_nest" || subCommand == "gridania_gc" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 132 )->getGuId(), { -64.7448f, -0.503434f, 2.21786f }, -2.64096f );
  else if( subCommand == "hall_of_flames" || subCommand == "uldah_gc" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 130 )->getGuId(), { -129.24f, 4.1f, -93.5221f }, -2.30172f );
  else if( subCommand == "maelsrom_command" || subCommand == "limsa_gc" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 128 )->getGuId(), { 76.3952f, 40.0955f, 71.6461f }, 1.62673f );
  else if( subCommand == "carline_canopy" || subCommand == "gridania_adventurer" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 132 )->getGuId(), { 43.729f, -7.96559f, 103.965f }, -1.59436f );
  else if( subCommand == "observatorium" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 155 )->getGuId(), { 224.965f, 221.958f, 301.33f }, -0.0316129f );
  else if( subCommand == "rising_stones" )
    warpMgr.requestMoveTerritory( player, Common::WarpType::WARP_TYPE_GM, terriMgr.getZoneByTerritoryTypeId( 156 )->getGuId(), { 22.7204f, 21.2639f, -635.704f }, -0.360031f );
  else
    PlayerMgr::sendUrgent( player, "{0} is not a valid easyWarp location.", subCommand );
}

void DebugCommandMgr::hotReload( char* data, Sapphire::Entity::Player& player, std::shared_ptr< DebugCommand > command )
{
  std::string subCommand;
  std::string params = "";

  // check if the command has parameters
  std::string tmpCommand = std::string( data + command->getName().length() + 1 );

  std::size_t pos = tmpCommand.find_first_of( ' ' );

  if( pos != std::string::npos )
    // command has parameters, grab the first part
    subCommand = tmpCommand.substr( 0, pos );
  else
    // no subcommand given
    subCommand = tmpCommand;

  if( command->getName().length() + 1 + pos + 1 < strlen( data ) )
    params = std::string( data + command->getName().length() + 1 + pos + 1 );

  Logger::debug( "[{0}] subCommand: {1} params: {2}", player.getId(), subCommand, params );

  if( subCommand == "actions" )
  {
    if( Action::ActionLutData::reloadActions() )
    {
      PlayerMgr::sendDebug( player, "Successfully reloaded actions." );
    }
    else
    {
      PlayerMgr::sendDebug( player, "There was an error reloading actions." );
    }
  }
  else
  {
    PlayerMgr::sendDebug( player, "Unknown sub command." );
  }
}