#pragma once

#include <cstdint>
#include <string>
#include <ForwardsZone.h>
#include <array>
#include <set>
#include <unordered_map>

namespace Sapphire::World::Manager
{

  enum UpdateStatus : int32_t
  {
    NONE_8 = 0x0,
    JOINED = 0x1,
    CHANGELEADER = 0x2,
    DISBAND = 0x3,
    KICK_MEMBER = 0x4,
    KICK_SELF = 0x5,
    LEAVE_MEMBER = 0x6,
    LEAVE_SELF = 0x7,
    MOVEZONE = 0x8,
    MOVETERRITORY = 0x9,
    OFFLINE_MEMBER = 0xA,
    RECOVERY_MEMBER = 0xB,
    LEAVELEADER_LEAVED_MEMBER = 0xC,
    LEAVELEADER_LEAVED_SELF = 0xD,
    ADDMEMBER_BUDDY = 0xE,
    REMOVEMEMBER_BUDDY = 0xF,
    SENDREADYCHECK = 0x10,
    REPLYREADYCHECK = 0x11,
  };

  struct Party
  {
    std::vector< uint32_t > MemberId;
    uint64_t PartyID;
    uint64_t ChatChannel;
    uint32_t LeaderId;
    uint8_t PartyCount;
  };

  using PartyPtr = std::shared_ptr< Party >;

  class PartyMgr
  {
  public:
    PartyMgr() = default;

    /// Perform required actions for events
    void onJoin( Entity::Player& joiner, Entity::Player& inviter );
    void onLeave( Entity::Player& leavingPlayer );
    void onMoveZone( Entity::Player& movingPlayer );
    void onDisband( Entity::Player& disbandingPlayer );
    void onKick( const std::string& kickPlayerName, Entity::Player& leader );
    void onChangeLeader( const std::string& newLeaderName, Entity::Player& oldLeader );

    void onMemberDisconnect( Entity::Player& disconnectingPlayer );
    void onMemberRejoin( Entity::Player& joiningPlayer );

    void onJoinBuddy( Entity::Player& buddyOwner, Party& party );
    void onLeaveBuddy( Entity::Player& buddyOwner, Party& party );
    void onStartReadyCheck( Entity::Player& startingPlayer, Party& party );
    void onReplyReadyCheck( Entity::Player& replyingPlayer, Party& party );

    ///////////////////////////
    PartyPtr getParty( uint64_t partyId );

  private:
    // arbitrary start range for party ids
    uint64_t m_maxPartyId = 0x0000044000000000;

    uint64_t createParty();
    void removeParty( uint64_t partyId );
    uint64_t getNextPartyId();
    std::unordered_map< uint64_t, PartyPtr > m_partyIdMap;

    static void sendPartyUpdate( Party& party );
    static void removeMember( Party& party, const Entity::PlayerPtr& pMember );
    static std::vector< Entity::PlayerPtr > getPartyMembers( Party& party );
    static Entity::PlayerPtr getPartyLeader( Party& party );

    static int8_t getPartyLeaderIndex( const Party& party );

  };

}
