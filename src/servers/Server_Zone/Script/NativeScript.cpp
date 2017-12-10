#include "NativeScript.h"

namespace Core {
    namespace Scripting {

        NativeScript::NativeScript( )
        { }

        StatusEffectScript* NativeScript::getStatusEffectScript( uint32_t statusId )
        {
           return m_statusEffectScripts.at( statusId );
        }

        ActionScript* NativeScript::getAbilityScript( uint32_t abilityId )
        {
           return m_actionScripts.at( abilityId );
        }

        QuestScript* NativeScript::getQuestScript( uint32_t questId )
        {
           return m_questScripts.at( questId );
        }

        BattleNpcScript* NativeScript::getBattleNpcScript( uint32_t npcId )
        {
           return m_battleNpcScripts.at( npcId );
        }

        ZoneScript* NativeScript::getZoneScript( uint32_t zoneId )
        {
           return m_zoneScripts.at( zoneId );
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

        void NativeScript::loadScript( std::string path )
        {
//           auto handle = m_loader.loadModule( path );
//           if( handle )
//           {
//              // todo: this is shit
//              if( auto script = m_loader.getScriptObject< StatusEffectScript >( handle ) )
//              {
//                 m_statusEffectScripts.insert( std::make_pair( script->getEffectId(), script ) );
//              }
//              else if( auto script = m_loader.getScriptObject< ActionScript >( handle ) )
//              {
//                 m_actionScripts.insert( std::make_pair( script->getActionId(), script ) );
//              }
//              else if( auto script = m_loader.getScriptObject< QuestScript >( handle ) )
//              {
//                 m_questScripts.insert( std::make_pair( script->getQuestId(), script ) );
//              }
//              else if( auto script = m_loader.getScriptObject< BattleNpcScript >( handle ) )
//              {
//                  m_battleNpcScripts.insert( std::make_pair( script->getNpcId(), script ) );
//              }
//              else if( auto script = m_loader.getScriptObject< ZoneScript >( handle ) )
//              {
//                  m_zoneScripts.insert( std::make_pair( script->getZoneId(), script ) );
//              }
//              else
//              {
//                 // unload anything which doesn't have a suitable export
//                 m_loader.unloadScript( handle );
//              }
//           }
        }


        boost::shared_ptr< NativeScript > create_script_engine( )
        {
           return boost::make_shared< NativeScript >( );
        }
    }
}
