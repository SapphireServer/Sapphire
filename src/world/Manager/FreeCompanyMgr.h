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
    enum ResultType : int32_t
    {
      Create = 0x1,
      Leave = 0x2,
      Kick = 0x3,
      Disband = 0x4,
      SetHierarchyName = 0x5,
      SetAuthorityList = 0x6,
      MoveHierarchy = 0x7,
      AddHierarchy = 0x8,
      RemoveHierarchy = 0x9,
      SortHierarchy = 0xA,
      CreateComplete = 0xB,
      ForceDisband = 0xC,
      SetCompanyBoard = 0xD,
      ChangeMaster = 0xE,
      FcLogin = 0xF,
      FcLogout = 0x10,
      RenameCreate = 0x11,
      Rename = 0x12,
      RenameTag = 0x13,
      FcRankUp = 0x14,
      FcReputationUp = 0x15,
      MoveGrandCompany = 0x16,
      MoveGcComplete = 0x17,
      SetCompanyMotto = 0x18,
      SetCrestId = 0x19,
      ChestLock = 0x1A,
      BuyFcAction = 0x1B,
      RemoveFcAction = 0x1C,
      ExecuteFcAction = 0x1D,
      CancelFcAction = 0x1E,
      ClearFcParams = 0x1F,
      TimeoutFcAction = 0x20,
      MoveZone = 0x21,
      Reload = 0x22,
      LandGet = 0x23,
      LandRemove = 0x24,
      LandAutoRemove = 0x25,
      HouseBuild = 0x26,
      HouseRemove = 0x27,
      SetFcMemo = 0x28,
      HouseLock = 0x29,
      HouseUnlock = 0x2A,
      AddJoinRequest = 0x2B,
      RemoveJoinRequest = 0x2C,
      SetInfoFcData = 0x2D,
      DisbandJoinRequest = 0x2E,
      MasterDemote = 0x2F,
      PRoomGet = 0x30,
      PRoomRemove = 0x31,
      PRoomAutoRemove = 0x32,
      FcCreateAccept = 0x65,
      Join = 0x66,
    };

    enum UpdateStatus : uint8_t
    {
      Execute = 0xA,
      Target = 0xB,
      Member = 0xC,
    };

    FreeCompanyMgr() = default;

    // initialize all fcs from db to memory
    bool loadFreeCompanies();
    void writeFreeCompany( uint64_t fcId );

    // create new fc entry and insert into db
    FreeCompanyPtr createFreeCompany( const std::string& name, const std::string& tag, Entity::Player& player );

    bool renameFreeCompany( uint64_t fcId, const std::string& name, const std::string& tag, Entity::Player& player );

    void sendFreeCompanyResult( Entity::Player& player, uint64_t fcId, ResultType resultType, uint64_t target, uint32_t result, UpdateStatus updateStatus );

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


  };

}
