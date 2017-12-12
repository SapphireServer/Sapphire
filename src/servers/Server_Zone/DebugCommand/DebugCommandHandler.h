#ifndef _GAMECOMMANDHANDLER_H_
#define _GAMECOMMANDHANDLER_H_

#include <map>

#include "DebugCommand.h"
#include <Server_Common/Common.h>
#include "Forwards.h"

namespace Core {


// handler for in game commands
class DebugCommandHandler
{
private:
   // container mapping command string to command object
   std::map< std::string, boost::shared_ptr< DebugCommand > > m_commandMap;

public:
   DebugCommandHandler();
   ~DebugCommandHandler();

   // register command to command map
   void registerCommand( const std::string& n, DebugCommand::pFunc, const std::string& hText, uint8_t uLevel );

   // execute command if registered
   void execCommand( char * data, Entity::Player& player );

   // help command
   void help( char* data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );

   // command handler callbacks
   void set( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );
   void get( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );
   void add( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );
   //void debug( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );

   void injectPacket( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );
   void injectChatPacket( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );
   void nudge( char* data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );
   void serverInfo( char * data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );

   void unlockCharacter( char* data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );

   void script( char* data, Entity::Player& player, boost::shared_ptr< DebugCommand > command );

};

}
#endif
