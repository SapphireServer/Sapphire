#ifndef NATIVE_SCRIPT_H
#define NATIVE_SCRIPT_H

#include <unordered_map>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include <Server_Common/Crypt/md5.h>

#include "ScriptLoader.h"

namespace Core {
    namespace Scripting {

        class NativeScript
        {
        protected:
            std::unordered_map< uint32_t, StatusEffectScript* > m_statusEffectScripts;
            std::unordered_map< uint32_t, ActionScript* > m_actionScripts;
            std::unordered_map< uint32_t, QuestScript* > m_questScripts;
            std::unordered_map< uint32_t, BattleNpcScript* > m_battleNpcScripts;
            std::unordered_map< uint32_t, ZoneScript* > m_zoneScripts;

            ScriptLoader m_loader;

        public:
            NativeScript( );

            StatusEffectScript* getStatusEffectScript( uint32_t statusId );
            ActionScript* getAbilityScript( uint32_t abilityId );
            QuestScript* getQuestScript( uint32_t questId );
            BattleNpcScript* getBattleNpcScript( uint32_t npcId );
            ZoneScript* getZoneScript( uint32_t zoneId );

            void removeStatusEffectScript( uint32_t statusId );
            void removeAbilityScript( uint32_t abilityId );
            void removeQuestScript( uint32_t questId );
            void removeBattleNpcScript( uint32_t npcId );


            bool loadScript( std::string );
            bool unloadScript( std::string );
            void clearAllScripts();

            const std::string getModuleExtension();

        };



        boost::shared_ptr< NativeScript > create_script_engine( );
    } }


#endif