#pragma once

#include <Network/GamePacket.h>
#include "Forwards.h"
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Common.h>

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  class FreeCompanyResultPacket : public ZoneChannelPacket< FFXIVIpcFreeCompanyResult >
  {
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

    FreeCompanyResultPacket( Entity::Player& player, uint64_t fcId, uint64_t arg,
                             ResultType type, uint32_t result, UpdateStatus updateStatus, const std::string& fcName, const std::string& targetName ) :

      ZoneChannelPacket< FFXIVIpcFreeCompanyResult >( player.getId(), player.getId() )
    {
      initialize( player, fcId, arg, type, result, updateStatus, fcName, targetName );
    };

  private:
    void initialize( Entity::Player& player, uint64_t fcId, uint64_t arg,
                     ResultType type, uint32_t result, UpdateStatus updateStatus, const std::string& fcName, const std::string& targetName )
    {
      m_data.FreeCompanyID = fcId;
      m_data.Identity = 0xFF;
      m_data.Type = static_cast< uint32_t >( type );
      m_data.Result = result;
      m_data.UpdateStatus = updateStatus;
      m_data.Arg = arg;
      strcpy( m_data.FreeCompanyName, fcName.c_str() );
      strcpy( m_data.TargetName, targetName.c_str() );
    };
  };
  template< typename... Args >
  std::shared_ptr< FreeCompanyResultPacket > makeFcResult( Args... args )
  {
    return std::make_shared< FreeCompanyResultPacket >( args... );
  }
}
