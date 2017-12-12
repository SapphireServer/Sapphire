#include "NativeScript.h"

namespace Core {
   namespace Scripting {

   NativeScript::NativeScript( )
   { }

   StatusEffectScript* NativeScript::getStatusEffectScript( uint32_t statusId )
   {
      auto script = m_statusEffectScripts.find( statusId );
      if( script == m_statusEffectScripts.end() )
         return nullptr;

      return script->second;
   }

   ActionScript* NativeScript::getActionScript( uint32_t actionId )
   {
      auto script = m_actionScripts.find( actionId );
      if( script == m_actionScripts.end() )
         return nullptr;

      return script->second;
   }

   QuestScript* NativeScript::getQuestScript( uint32_t questId )
   {
      auto script = m_questScripts.find( questId );
      if( script == m_questScripts.end() )
         return nullptr;

      return script->second;
   }

   BattleNpcScript* NativeScript::getBattleNpcScript( uint32_t npcId )
   {
      auto script = m_battleNpcScripts.find( npcId );
      if( script == m_battleNpcScripts.end() )
         return nullptr;

      return script->second;
   }

   ZoneScript* NativeScript::getZoneScript( uint32_t zoneId )
   {
      auto script = m_zoneScripts.find( zoneId );
      if( script == m_zoneScripts.end() )
         return nullptr;

      return script->second;
   }

   bool NativeScript::loadScript( const std::string& path )
   {
      auto module = m_loader.loadModule( path );
      if( module )
      {
         auto script = m_loader.getScriptObject( module->handle );
         if( script )
         {
            module->script = script;
            module->script_name = script->getName();
            module->type = script->getType();

            switch( script->getType() )
            {
               case ScriptType::StatusEffect:
                  m_statusEffectScripts[ script->getId() ] = dynamic_cast< StatusEffectScript* >( script );
                  break;
               case ScriptType::Action:
                  m_actionScripts[ script->getId() ] = dynamic_cast< ActionScript* >( script );
                  break;
               case ScriptType::Quest:
                  m_questScripts[ script->getId() ] = dynamic_cast< QuestScript* >( script );
                  break;
               case ScriptType::BattleNpc:
                  m_battleNpcScripts[ script->getId() ] = dynamic_cast< BattleNpcScript* >( script );
                  break;
               case ScriptType::Zone:
                  m_zoneScripts[ script->getId() ] = dynamic_cast< ZoneScript* >( script );
                  break;

               default:
                  m_loader.unloadScript( module );
                  return false;
            }
         }
         else
         {
            m_loader.unloadScript( module );
            return false;
         }

      }
      else
         return false;

      return true;
   }

   const std::string NativeScript::getModuleExtension()
   {
      return m_loader.getModuleExtension();
   }

   bool NativeScript::unloadScript( const std::string& name )
   {
      auto info = m_loader.getScriptInfo( name );
      if( info )
      {
         auto ptr = info->script;

         switch( info->type )
         {
            case ScriptType::StatusEffect:
               removeValueFromMap< uint32_t, StatusEffectScript* >( ptr, m_statusEffectScripts );
               break;
            case ScriptType::Action:
               removeValueFromMap< uint32_t, ActionScript* >( ptr, m_actionScripts );
               break;
            case ScriptType::Quest:
               removeValueFromMap< uint32_t, QuestScript* >( ptr, m_questScripts );
               break;
            case ScriptType::BattleNpc:
               removeValueFromMap< uint32_t, BattleNpcScript* >( ptr, m_battleNpcScripts );
               break;
            case ScriptType::Zone:
               removeValueFromMap< uint32_t, ZoneScript* >( ptr, m_zoneScripts );
               break;

            default:
               return false;
         }

         return m_loader.unloadScript( info );
      }

      return false;
   }

   void NativeScript::findScripts( std::set< Core::Scripting::ScriptInfo* >& scripts, const std::string& search )
   {
      return m_loader.findScripts( scripts, search );
   }



   boost::shared_ptr< NativeScript > create_script_engine( )
   {
      return boost::make_shared< NativeScript >();
   }
}
}
