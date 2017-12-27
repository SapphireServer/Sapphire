#include "NativeScriptManager.h"

namespace Core {
   namespace Scripting {

   NativeScriptManager::NativeScriptManager( )
   { }

   StatusEffectScript* NativeScriptManager::getStatusEffectScript( uint32_t statusId )
   {
      auto script = m_statusEffectScripts.find( statusId );
      if( script == m_statusEffectScripts.end() )
         return nullptr;

      return script->second;
   }

   ActionScript* NativeScriptManager::getActionScript( uint32_t actionId )
   {
      auto script = m_actionScripts.find( actionId );
      if( script == m_actionScripts.end() )
         return nullptr;

      return script->second;
   }

   EventScript* NativeScriptManager::getEventScript( uint32_t questId )
   {
      auto script = m_eventScripts.find( questId );
      if( script == m_eventScripts.end() )
         return nullptr;

      return script->second;
   }

   BattleNpcScript* NativeScriptManager::getBattleNpcScript( uint32_t npcId )
   {
      auto script = m_battleNpcScripts.find( npcId );
      if( script == m_battleNpcScripts.end() )
         return nullptr;

      return script->second;
   }

   ZoneScript* NativeScriptManager::getZoneScript( uint32_t zoneId )
   {
      auto script = m_zoneScripts.find( zoneId );
      if( script == m_zoneScripts.end() )
         return nullptr;

      return script->second;
   }

   bool NativeScriptManager::loadScript( const std::string& path )
   {
      auto module = m_loader.loadModule( path );
      if( !module )
         return false;

      auto scripts = m_loader.getScripts( module->handle );
      if( !scripts )
      {
         m_loader.unloadScript( module );
         return false;
      }

      //
      bool success = false;

      for( int i = 0; ; i++ )
      {
         if( scripts[i] == nullptr )
            break;

         auto script = scripts[i];
         module->scripts.push_back( script );

         switch( script->getType() )
         {
            case ScriptType::StatusEffect:
               m_statusEffectScripts[ script->getId() ] = dynamic_cast< StatusEffectScript* >( script );
               break;
            case ScriptType::Action:
               m_actionScripts[ script->getId() ] = dynamic_cast< ActionScript* >( script );
               break;
            case ScriptType::Quest:
               m_eventScripts[ script->getId() ] = dynamic_cast< EventScript* >( script );
               break;
            case ScriptType::BattleNpc:
               m_battleNpcScripts[ script->getId() ] = dynamic_cast< BattleNpcScript* >( script );
               break;
            case ScriptType::Zone:
               m_zoneScripts[ script->getId() ] = dynamic_cast< ZoneScript* >( script );
               break;
         }

         success = true;
      }

      if( !success )
      {
         m_loader.unloadScript( module->handle );
         return false;
      }

      return true;
   }

   const std::string NativeScriptManager::getModuleExtension()
   {
      return m_loader.getModuleExtension();
   }

   bool NativeScriptManager::unloadScript( const std::string& name )
   {
      auto info = m_loader.getScriptInfo( name );
      if( !info )
         return false;

      return unloadScript( info );
   }

   bool NativeScriptManager::unloadScript( ScriptInfo* info )
   {
      for( auto& script : info->scripts )
      {
         switch( script->getType() )
         {
            case ScriptType::StatusEffect:
               removeValueFromMap< uint32_t, StatusEffectScript* >( script, m_statusEffectScripts );
               break;
            case ScriptType::Action:
               removeValueFromMap< uint32_t, ActionScript* >( script, m_actionScripts );
               break;
            case ScriptType::Quest:
               removeValueFromMap< uint32_t, EventScript* >( script, m_eventScripts );
               break;
            case ScriptType::BattleNpc:
               removeValueFromMap< uint32_t, BattleNpcScript* >( script, m_battleNpcScripts );
               break;
            case ScriptType::Zone:
               removeValueFromMap< uint32_t, ZoneScript* >( script, m_zoneScripts );
               break;

            default:
               continue;
         }
      }

      return m_loader.unloadScript( info );
   }

   void NativeScriptManager::queueScriptReload( const std::string &name )
   {
      auto info = m_loader.getScriptInfo( name );
      if( !info )
         return;

      // backup actual lib path
      std::string libPath( info->library_path );

      if( !unloadScript( info ) )
         return;

      m_scriptLoadQueue.push( libPath );
   }

   void NativeScriptManager::processLoadQueue()
   {
      std::vector< std::string > deferredLoads;

      while( !m_scriptLoadQueue.empty() )
      {
         auto item = m_scriptLoadQueue.front();

         // if it fails, we defer the loading to the next tick
         if( !loadScript( item ) )
            deferredLoads.push_back( item );

         m_scriptLoadQueue.pop();
      }

      if( !deferredLoads.empty() )
      {
         for( auto& item : deferredLoads )
            m_scriptLoadQueue.push( item );
      }
   }

   void NativeScriptManager::findScripts( std::set< Core::Scripting::ScriptInfo* >& scripts, const std::string& search )
   {
      return m_loader.findScripts( scripts, search );
   }

   bool NativeScriptManager::isModuleLoaded( const std::string &name )
   {
      return m_loader.isModuleLoaded( name );
   }



   boost::shared_ptr< NativeScriptManager > createNativeScriptMgr()
   {
      return boost::make_shared< NativeScriptManager >();
   }
}
}
