#pragma once

#include <memory>
#include <map>
#include <vector>
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{



  class FreeCompanyMgr
  {
  private:
    std::map< uint64_t, FreeCompanyPtr > m_fcIdMap;
    std::map< std::string, FreeCompanyPtr > m_fcNameMap;

    FreeCompanyPtr getFcByName( const std::string& name );

  public:


    FreeCompanyMgr() = default;

    // initialize all fcs from db to memory
    bool loadFreeCompanies();
    void writeFreeCompany( uint64_t fcId );

    // create new fc entry and insert into db
    FreeCompanyPtr createFreeCompany( const std::string& name, const std::string& tag, Entity::Player& player );

    bool renameFreeCompany( uint64_t fcId, const std::string& name, const std::string& tag, Entity::Player& player );

    //void sendFreeCompanyResult( Entity::Player& player, uint64_t fcId, ResultType resultType, uint64_t target,
    //                            uint32_t result, UpdateStatus updateStatus, std::string targetName );

    void sendFcInviteList( Entity::Player& player );
    void sendFcStatus( Entity::Player& player );

   /* void invitePlayer( Entity::Player& sourcePlayer, Entity::Player& invitedPlayer, uint64_t linkshellId );
    void kickPlayer( Entity::Player& sourcePlayer, Entity::Player& kickedPlayer, uint64_t linkshellId );

    void addLeader( Entity::Player& sourcePlayer, Entity::Player& newLeaderPlayer, uint64_t linkshellId );
    void removeLeader( Entity::Player& sourcePlayer, Entity::Player& leaderPlayer, uint64_t linkshellId );
    void declineLeader( Entity::Player& sourcePlayer, uint64_t linkshellId );
    void changeMaster( Entity::Player& sourcePlayer, Entity::Player& nextMasterPlayer, uint64_t linkshellId ); */

    void sendFreeCompanyStatus( Entity::Player& player );

    // get fc associated with player
    FreeCompanyPtr getPlayerFreeCompany( Entity::Player& player ) const;

    FreeCompanyPtr getFreeCompanyById( uint64_t fcId );

   // void leaveLinkshell( uint64_t lsId, uint64_t characterId );
   // void joinLinkshell( uint64_t lsId, uint64_t characterId );

    void onFcLogin( uint64_t characterId );

  };

}
