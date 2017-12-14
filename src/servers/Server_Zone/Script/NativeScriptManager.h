#ifndef NATIVE_SCRIPT_H
#define NATIVE_SCRIPT_H

#include <unordered_map>
#include <set>
#include <queue>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include <Server_Common/Crypt/md5.h>

#include "ScriptLoader.h"

namespace Core {
namespace Scripting {

   class NativeScriptManager
   {
   protected:
      std::unordered_map< uint32_t, StatusEffectScript* > m_statusEffectScripts;
      std::unordered_map< uint32_t, ActionScript* > m_actionScripts;
      std::unordered_map< uint32_t, EventScript* > m_eventScripts;
      std::unordered_map< uint32_t, BattleNpcScript* > m_battleNpcScripts;
      std::unordered_map< uint32_t, ZoneScript* > m_zoneScripts;

      ScriptLoader m_loader;

      std::queue< std::string > m_scriptLoadQueue;

      bool unloadScript( ScriptInfo* info );

   public:
      NativeScriptManager( );

      StatusEffectScript* getStatusEffectScript( uint32_t statusId );
      ActionScript* getActionScript( uint32_t actionId );
      EventScript* getEventScript( uint32_t questId );
      BattleNpcScript* getBattleNpcScript( uint32_t npcId );
      ZoneScript* getZoneScript( uint32_t zoneId );

      bool loadScript( const std::string& path );
      bool unloadScript( const std::string& name );
      void queueScriptReload( const std::string& name );
      void findScripts( std::set< Core::Scripting::ScriptInfo* >& scripts, const std::string& search );

      void processLoadQueue();

      const std::string getModuleExtension();
      bool isModuleLoaded( const std::string& name );

      template< typename key, typename val >
      bool removeValueFromMap( ScriptObject* ptr, std::unordered_map< key, val >& map )
      {
         for( typename std::unordered_map< key, val >::iterator it = map.begin(); it != map.end(); ++it )
         {
            if( ptr == static_cast< ScriptObject* >( it->second ) )
            {
               map.erase( it );
               return true;
            }
         }

         return false;
      }
   };



   boost::shared_ptr< NativeScriptManager > createNativeScriptMgr();
} }


#endif