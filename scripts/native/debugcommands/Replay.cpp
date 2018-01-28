#include <ScriptObject.h>
#include <Session.h>

class Replay : public DebugCommandScript
{
public:
   Replay() : DebugCommandScript( "replay", "Replays a saved capture", 1 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      if( subCommand == "start" )
      {
         auto pSession = m_objects->m_zone->getSession( player.getId() );
         if( pSession )
            pSession->startReplay( params );
      }
      else if( subCommand == "stop" )
      {
         auto pSession = m_objects->m_zone->getSession( player.getId() );
         if( pSession )
            pSession->stopReplay();
      }
      else
      {
         player.sendUrgent( subCommand + " is not a valid replay command." );
      }
   }
};