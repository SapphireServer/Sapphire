#ifndef SAPPHIRE_LINKSHELLMGR_H
#define SAPPHIRE_LINKSHELLMGR_H

#include <memory>
#include <map>
#include "ForwardsZone.h"
#include "BaseManager.h"

namespace Sapphire::World::Manager
{

  class LinkshellMgr : public Manager::BaseManager
  {
  private:
    std::map< uint64_t, LinkshellPtr > m_linkshellIdMap;
    std::map< std::string, LinkshellPtr > m_linkshellNameMap;

    LinkshellPtr getLinkshellByName( const std::string& name );

    LinkshellPtr getLinkshellById( uint64_t lsId );

  public:
    LinkshellMgr( FrameworkPtr pFw );

    bool loadLinkshells();
  };

}
#endif //SAPPHIRE_LINKSHELLMGR_H
