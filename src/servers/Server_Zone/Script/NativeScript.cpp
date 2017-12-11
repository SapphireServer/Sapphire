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

        ActionScript* NativeScript::getAbilityScript( uint32_t abilityId )
        {
           auto script = m_actionScripts.find( abilityId );
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

        void NativeScript::removeStatusEffectScript( uint32_t statusId )
        {
           m_statusEffectScripts.erase( statusId );
        }

        void NativeScript::removeAbilityScript( uint32_t abilityId )
        {
           m_actionScripts.erase( abilityId );
        }

        void NativeScript::removeQuestScript( uint32_t questId )
        {
           m_questScripts.erase( questId );
        }

        void NativeScript::removeBattleNpcScript( uint32_t npcId )
        {
           m_battleNpcScripts.erase( npcId );
        }

        bool NativeScript::loadScript( std::string path )
        {
           auto info = m_loader.loadModule( path );
           if( info )
           {
              // todo: this is shit
              if( auto script = m_loader.getScriptObject< StatusEffectScript >( info->handle, "StatusEffectScript" ) )
              {
                 info->script = script;
                 m_statusEffectScripts[ script->getId() ] = script;
              }
              else if( auto script = m_loader.getScriptObject< ActionScript >( info->handle, "ActionScript" ) )
              {
                 info->script = script;
                 m_actionScripts[ script->getId() ] = script;
              }
              else if( auto script = m_loader.getScriptObject< QuestScript >( info->handle, "QuestScript" ) )
              {
                 info->script = script;
                 m_questScripts[ script->getId() ] = script;
              }
              else if( auto script = m_loader.getScriptObject< BattleNpcScript >( info->handle, "BattleNpcScript" ) )
              {
                 info->script = script;
                 m_battleNpcScripts[ script->getId() ] = script;
              }
              else if( auto script = m_loader.getScriptObject< ZoneScript >( info->handle, "ZoneScript" ) )
              {
                 info->script = script;
                 m_zoneScripts[ script->getId() ] = script;
              }
              else
              {
                 // unload anything which doesn't have a suitable export
                 m_loader.unloadScript( info->handle );

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

        bool NativeScript::unloadScript( std::string name )
        {
           return m_loader.unloadScript( name );
        }


        boost::shared_ptr< NativeScript > create_script_engine( )
        {
           return boost::make_shared< NativeScript >();
        }
    }
}
