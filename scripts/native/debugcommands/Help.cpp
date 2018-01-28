#include <ScriptObject.h>

#include <Script/NativeScriptManager.h>

class Help : public DebugCommandScript
{
public:
   Help() : DebugCommandScript( "help", "Displays server build information", 0 )
   { }

   virtual void run( Entity::Player& player, const std::string& data, const std::string& subCommand, const std::string& params )
   {
      player.sendDebug( "Available debug commands:" );

      for( std::pair< uint32_t, ScriptObject* > s : m_objects->m_scriptMgr->getNativeScriptHandler().getScriptsOfType< DebugCommandScript >() )
      {
         auto script = dynamic_cast< DebugCommandScript* >( s.second );

         if( player.getGmRank() >= script->getGmLevel() )
            player.sendDebug( " - " + script->getCmd() + " - " + script->getHelpText() );
      }
   }
};