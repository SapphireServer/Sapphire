#ifndef _SESSION_H_
#define _SESSION_H_

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
    uint8_t m_sessionId[56];

  public:
    std::string newCharName;

    Session();

    ~Session();

    uint32_t getIp() const;

    void setSessionId( uint8_t* sessionId );

    void setIp( uint32_t ip );

    uint32_t getAccountId() const;

    void setAccountId( uint32_t id );

  };

}

#endif