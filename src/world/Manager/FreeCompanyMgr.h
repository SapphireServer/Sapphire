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

    void sendFcInviteList( Entity::Player& player );
    void sendFcStatus( Entity::Player& player );

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

    void onFcLogin( uint64_t characterId );
    void onFcLogout( uint64_t characterId );
    void onSignPetition( Entity::Player& source, Entity::Player& target );

  };

}
