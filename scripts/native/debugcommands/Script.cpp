#include <ScriptObject.h>

#include <Script/NativeScriptManager.h>
#include <boost/format.hpp>

class Script : public DebugCommandScript
{
public:
   Script() : DebugCommandScript( "script", "Script management commands", 0 )
   { }

   virtual void run( Entity::Player& player, const std::string& args, const std::string& subCommand, const std::string& params )
   {
      if( subCommand == "unload" )
      {
         if ( subCommand == params )
            player.sendDebug( "Command failed: requires name of script" );
         else
         if( m_objects->m_scriptMgr->getNativeScriptHandler().unloadScript( params ) )
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
            m_objects->m_scriptMgr->getNativeScriptHandler().findScripts( scripts, params );

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
            if ( m_objects->m_scriptMgr->getNativeScriptHandler().loadScript( params ) )
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
            m_objects->m_scriptMgr->getNativeScriptHandler().queueScriptReload( params );
            player.sendDebug( "Queued script reload for script: " + params );
         }
      }
      else if( subCommand == "build" || subCommand == "b" )
      {
         if( subCommand == params )
            player.sendDebug( "Command failed: requires name of cmake target" );
         else
         {

         }
      }
      else
      {
         player.sendDebug( "Unknown script subcommand: " + subCommand );
      }
   }
};