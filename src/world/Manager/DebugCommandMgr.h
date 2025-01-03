#pragma once

#include <map>
#include <Common.h>

#include "DebugCommand/DebugCommand.h"
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{

  // handler for in game commands
  class DebugCommandMgr
  {
  private:
    // container mapping command string to command object
    std::map< std::string, std::shared_ptr< DebugCommand > > m_commandMap;

  public:
    DebugCommandMgr();

    ~DebugCommandMgr();

    // register command to command map
    void registerCommand( const std::string& n, DebugCommand::pFunc, const std::string& hText, uint8_t uLevel );

    // execute command if registered
    void execCommand( char* data, Entity::Player& player );

    // help command
    void help( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    // command handler callbacks
    void set( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void get( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void add( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );
    //void debug( char * data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void injectPacket( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void injectChatPacket( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void replay( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void nudge( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void serverInfo( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void unlockCharacter( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void instance( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );
    void questBattle( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void housing( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void linkshell( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void script( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void contentFinder( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void cbt( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void easyWarp( char* data, Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void hotReload( char* data, Sapphire::Entity::Player& player, std::shared_ptr< DebugCommand > command );

    void facing( char* data, Sapphire::Entity::Player& player, std::shared_ptr< DebugCommand > command );

  };

}