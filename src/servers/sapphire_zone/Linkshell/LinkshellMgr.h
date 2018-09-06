#ifndef CORE_LINKSHELLMGR_H
#define CORE_LINKSHELLMGR_H

#include <boost/shared_ptr.hpp>
#include <map>

namespace Core {
class Linkshell;

using LinkshellPtr = boost::shared_ptr< Linkshell >;

class LinkshellMgr
{
private:
  std::map< uint64_t, LinkshellPtr > m_linkshellIdMap;
  std::map< std::string, LinkshellPtr > m_linkshellNameMap;

  LinkshellPtr getLinkshellByName( const std::string& name );

  LinkshellPtr getLinkshellById( uint64_t lsId );

public:
  LinkshellMgr();

  bool loadLinkshells();
};

}
#endif //CORE_LINKSHELLMGR_H
