#ifndef _GAMECOMMANDHANDLER_H_
#define _GAMECOMMANDHANDLER_H_

#include <map>

#include "GameCommand.h"
#include <Server_Common/Common.h>
#include "Forwards.h"

namespace Core {


// handler for in game commands
class GameCommandHandler
{
private:
   // container mapping command string to command object
   std::map<std::string, boost::shared_ptr<GameCommand> > m_commandMap;

public:
   GameCommandHandler();
   ~GameCommandHandler();

   // register command to command map
   void registerCommand( const std::string& n, GameCommand::pFunc, const std::string& hText, Common::UserLevel uLevel );

   // execute command if registered
   void execCommand( char * data, Entity::PlayerPtr pPlayer );

   // command handler callbacks
   void set( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );
   void get( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );
   void add( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );
   //void debug( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );
   void scriptReload( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );

   void setQuestHandler( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );

   void injectPacket( char * data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );
   void nudge( char* data, Entity::PlayerPtr pPlayer, boost::shared_ptr<GameCommand> command );

};

}
#endif
