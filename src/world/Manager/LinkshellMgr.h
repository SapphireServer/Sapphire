#pragma once

#include <memory>
#include <map>
#include <vector>
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{

  enum Hierarchy : uint32_t
  {
    NONE_1 = 0x0,
    MASTER = 0x1,
    LEADER = 0x2,
    MEMBER = 0x3,
    INVITE = 0x4,
    MAX_0 = 0x7,
  };

  class LinkshellMgr
  {
  private:
    std::map< uint64_t, LinkshellPtr > m_linkshellIdMap;
    std::map< std::string, LinkshellPtr > m_linkshellNameMap;

    LinkshellPtr getLinkshellByName( const std::string& name );

  public:
    LinkshellMgr() = default;

    // initialize all linkshells from db to memory
    bool loadLinkshells();
    void writeLinkshell( uint64_t lsId );

    // create new linkshell entry and insert into db
    LinkshellPtr createLinkshell( const std::string& name, Entity::Player& player );

    void finishLinkshellCreation( const std::string& name, uint32_t result, Entity::Player& player );

    void invitePlayer( Entity::Player& sourcePlayer, Entity::Player& invitedPlayer, uint64_t linkshellId );
    void kickPlayer( Entity::Player& sourcePlayer, Entity::Player& kickedPlayer, uint64_t linkshellId );

    void addLeader( Entity::Player& sourcePlayer, Entity::Player& newLeaderPlayer, uint64_t linkshellId );
    void removeLeader( Entity::Player& sourcePlayer, Entity::Player& leaderPlayer, uint64_t linkshellId );
    void declineLeader( Entity::Player& sourcePlayer, uint64_t linkshellId );
    void changeMaster( Entity::Player& sourcePlayer, Entity::Player& nextMasterPlayer, uint64_t linkshellId );

    void sendLinkshellList( Entity::Player& player );

    // get all linkshells associated with player
    const std::vector< LinkshellPtr > getPlayerLinkshells( Entity::Player& player ) const;

    LinkshellPtr getLinkshellById( uint64_t lsId );

    void leaveLinkshell( uint64_t lsId, uint64_t characterId );
    void joinLinkshell( uint64_t lsId, uint64_t characterId );


  };

}
