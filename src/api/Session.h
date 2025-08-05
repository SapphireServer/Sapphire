#pragma once

#include <stdint.h>
#include <string>
#include <string.h>

namespace Sapphire::Api
{

  class Session
  {

  private:
    uint32_t m_ip;
    uint32_t m_accountId;
    std::string m_sessionId;

  public:
    std::string newCharName;

    Session();

    ~Session();

    uint32_t getIp() const;

    void setSessionId( const char* sessionId );

    void setIp( uint32_t ip );

    uint32_t getAccountId() const;

    void setAccountId( uint32_t id );

  };

}