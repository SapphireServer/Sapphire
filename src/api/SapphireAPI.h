#ifndef _SAPPHIREAPI_H_
#define _SAPPHIREAPI_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "PlayerMinimal.h"

namespace Sapphire
{
  class Session;
}

namespace Sapphire::Network
{

  class SapphireAPI
  {
  public:
    SapphireAPI() = default;
    ~SapphireAPI() = default;

    using SessionMap = std::map< std::string, std::shared_ptr< Session > >;

    bool login( const std::string& username, const std::string& pass, std::string& sId );

    bool createAccount( const std::string& username, const std::string& pass, std::string& sId );

    int32_t createCharacter( uint32_t accountId, const std::string& name,
                             const std::string& infoJson, uint32_t gmRank );

    void deleteCharacter( std::string name, uint32_t accountId );

    bool insertSession( uint32_t accountId, std::string& sId );

    std::vector< Sapphire::PlayerMinimal > getCharList( uint32_t accountId );

    bool checkNameTaken( std::string name );

    uint32_t getNextCharId();

    uint64_t getNextContentId();

    int32_t checkSession( const std::string& sId );

    bool removeSession( const std::string& sId );

    SessionMap m_sessionMap;

  };
}

#endif
