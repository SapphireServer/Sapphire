#pragma once

#include <memory>
#include <map>
#include <vector>
#include "ForwardsZone.h"
#include "FreeCompany/FreeCompany.h"

namespace Sapphire::World::Manager
{



  class FreeCompanyMgr
  {
  private:
    std::unordered_map< uint64_t, FreeCompanyPtr > m_fcIdMap;
    std::unordered_map< std::string, FreeCompanyPtr > m_fcNameMap;

    /*! map used for easy lookup of char id to fc id */
    std::unordered_map< uint64_t, uint64_t > m_charaIdToFcIdMap;

    uint64_t m_maxFcId{ 0 };
    uint32_t m_onlinePlayers{ 0 };

  public:

    FreeCompanyMgr() = default;

    // initialize all fcs from db to memory
    bool loadFreeCompanies();
    void writeFreeCompany( uint64_t fcId );

    // create new fc entry and insert into db
    FreeCompanyPtr createFreeCompany( const std::string& name, const std::string& tag, Entity::Player& player );

    bool renameFreeCompany( uint64_t fcId, const std::string& name, const std::string& tag, Entity::Player& player );

    void addMember( uint64_t fcId, uint64_t memberId );

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

    void dbInsertMember( uint64_t fcId, uint64_t characterId, uint8_t hierarchyId );
    void dbInsertFc( const FreeCompany& fc );
    void dbUpdateFc( const FreeCompany& fc );
    std::vector< FreeCompanyPtr > dbSelectFcsAll();
    std::vector< FreeCompany::FcMember > dbSelectMembersByFc( uint64_t fcId );

    // get fc associated with player
    FreeCompanyPtr getPlayerFreeCompany( uint64_t characterId );
    FreeCompanyPtr getFreeCompanyById( uint64_t fcId );
    FreeCompanyPtr getFreeCompanyByName( const std::string& name );

   // void leaveLinkshell( uint64_t lsId, uint64_t characterId );
   // void joinLinkshell( uint64_t lsId, uint64_t characterId );

    void onFcLogin( uint64_t characterId );
    void onFcLogout( uint64_t characterId );
    void onSignPetition( Entity::Player& source, Entity::Player& target );

  };

}
