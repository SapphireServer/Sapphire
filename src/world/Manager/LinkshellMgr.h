#pragma once

#include <memory>
#include <map>
#include <vector>
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{

  enum Hierarchy : __int32
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

    // create new linkshell entry and insert into db
    LinkshellPtr createLinkshell( const std::string& name, Entity::Player& player );

    void finishLinkshellCreation( const std::string& name, uint32_t result, Entity::Player& player );

    // get all linkshells associated with player
    const std::vector< LinkshellPtr > getPlayerLinkshells( Entity::Player& player ) const;

    LinkshellPtr getLinkshellById( uint64_t lsId );
  };

}
