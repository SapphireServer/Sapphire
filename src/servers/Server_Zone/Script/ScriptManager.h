#ifndef _SCRIPTMANAGER_H_
#define _SCRIPTMANAGER_H_

#include <boost/shared_ptr.hpp>
#include <mutex>
#include <set>

#include <Server_Common/Common.h>
#include "Forwards.h"


namespace chaiscript
{
   class ChaiScript;
}

namespace Core
{
   namespace Scripting
   {

      class ScriptManager
      {
      private:

         boost::shared_ptr< chaiscript::ChaiScript > m_pChaiHandler;

         std::function< std::string( Entity::Player& ) > m_onFirstEnterWorld;
        // auto fn = m_pChaiHandler->eval< std::function<const std::string( Entity::Player ) > >( "onFirstEnterWorld" );

      public:
         ScriptManager();
         ~ScriptManager();

         int32_t init();
         void reload();

         const boost::shared_ptr< chaiscript::ChaiScript >& getHandler() const;

         void onPlayerFirstEnterWorld( Entity::Player& player );

         static bool registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId, uint32_t bnpcNameId, uint32_t modelId, std::string aiName );

         bool onTalk( Entity::Player& player, uint64_t actorId, uint32_t eventId );
         bool onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 );
         bool onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );
         bool onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );
         bool onEmote( Entity::Player& player, uint64_t actorId, uint32_t eventId, uint8_t emoteId );
         bool onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint32_t castTime, uint64_t targetId );

         bool onMobKill( Entity::Player& player, uint16_t nameId );

         bool onCastFinish( Entity::Player& pPlayer, Entity::ActorPtr pTarget, uint32_t actionId );

         bool onStatusReceive( Entity::ActorPtr pActor, uint32_t effectId );
         bool onStatusTick( Entity::ActorPtr pActor, Core::StatusEffect::StatusEffect& effect );
         bool onStatusTimeOut( Entity::ActorPtr pActor, uint32_t effectId );

         bool onZoneInit( ZonePtr pZone );
         
         bool onEventHandlerReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param1, uint16_t param2, uint16_t param3 );
         bool onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId );
         

         void loadDir( std::string dirname, std::set<std::string>& chaiFiles );

          
      };
   }
}
#endif
