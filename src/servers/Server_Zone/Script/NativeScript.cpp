#include "NativeScript.h"

namespace Core {
    namespace Scripting {

        NativeScript::NativeScript( )
        { }

        StatusEffectScript* NativeScript::getStatusEffectScript( uint32_t statusId )
        {
           return m_statusEffectScripts.at( statusId );
        }

        AbilityScript* NativeScript::getAbilityScript( uint32_t abilityId )
        {
           return m_abilityScripts.at( abilityId );
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
           m_abilityScripts.erase( abilityId );
        }

        void NativeScript::removeQuestScript( uint32_t questId )
        {
           m_questScripts.erase( questId );
        }

        void NativeScript::removeBattleNpcScript( uint32_t npcId )
        {
           m_battleNpcScripts.erase( npcId );
        }





        boost::shared_ptr< NativeScript > create_script_engine( )
        {
           return boost::make_shared< NativeScript >( );
        }
    }
}
