#include <ScriptObject.h>

#include <Zone/Zone.h>

class Get : public DebugCommandScript
{
public:
   Get() : DebugCommandScript( "get", "Executes GET commands", 1 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      if( ( subCommand == "pos" ) )
      {

         int16_t map_id = m_objects->m_exd->m_zoneInfoMap[player.getCurrentZone()->getTerritoryId()].map_id;

         player.sendNotice( "Pos:\n" +
                            std::to_string( player.getPos().x ) + "\n" +
                            std::to_string( player.getPos().y ) + "\n" +
                            std::to_string( player.getPos().z ) + "\n" +
                            std::to_string( player.getRotation() ) + "\nMapId: " +
                            std::to_string( map_id ) + "\nZoneID: " +
                            std::to_string(player.getCurrentZone()->getTerritoryId() ) + "\n" );
      }
      else
      {
         player.sendUrgent( subCommand + " is not a valid GET command." );
      }
   }
};