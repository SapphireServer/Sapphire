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

         void onPlayerFirstEnterWorld( Entity::PlayerPtr pPlayer );

         static bool registerBnpcTemplate( std::string templateName, uint32_t bnpcBaseId, uint32_t bnpcNameId, uint32_t modelId, std::string aiName );

         bool onTalk( Entity::PlayerPtr pPlayer, uint64_t actorId, uint32_t eventId );
         bool onEnterTerritory( Entity::PlayerPtr pPlayer, uint32_t eventId, uint16_t param1, uint16_t param2 );
         bool onWithinRange( Entity::PlayerPtr pPlayer, uint32_t eventId, uint32_t param1, float x, float y, float z );
         bool onOutsideRange( Entity::PlayerPtr pPlayer, uint32_t eventId, uint32_t param1, float x, float y, float z );
         bool onEmote( Entity::PlayerPtr pPlayer, uint64_t actorId, uint32_t eventId, uint8_t emoteId );
         bool onEventItem( Entity::PlayerPtr pPlayer, uint32_t eventItemId, uint32_t eventId, uint32_t castTime, uint64_t targetId );

         bool onMobKill( Entity::PlayerPtr pPlayer, uint16_t nameId );

         bool onCastFinish( Entity::PlayerPtr pPlayer, Entity::ActorPtr pTarget, uint32_t actionId );

         bool onStatusReceive( Entity::ActorPtr pActor, uint32_t effectId );
         bool onStatusTick( Entity::ActorPtr pActor, uint32_t effectId );
         bool onStatusTimeOut( Entity::ActorPtr pActor, uint32_t effectId );

         bool onZoneInit( ZonePtr pZone );
         
         bool onEventHandlerReturn( Entity::PlayerPtr pPlayer, uint32_t eventId, uint16_t subEvent, uint16_t param1, uint16_t param2, uint16_t param3 );
         bool onEventHandlerTradeReturn( Entity::PlayerPtr pPlayer, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId );
         

         void loadDir( std::string dirname, std::set<std::string>& chaiFiles );

          
      };
   }
}
#endif
