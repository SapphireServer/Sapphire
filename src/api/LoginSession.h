#pragma once

#ifndef _CLoginSession_H_
#define _CLoginSession_H_

#include <stdint.h>
#include <string>
#include <string.h>

namespace Sapphire
{

  class LoginSession
  {

  private:
    uint32_t m_ip;
    uint32_t m_accountId;
    uint8_t m_sessionId[56];

  public:
    std::string newCharName;

    LoginSession( void );

    ~LoginSession( void );

    uint32_t getIp()
    {
      return m_ip;
    }

    void setSessionId( uint8_t* sessionId )
    {
      memcpy( m_sessionId, sessionId, 56 );
    }

    void setIp( uint32_t ip )
    {
      m_ip = ip;
    }

    uint32_t getAccountId()
    {
      return m_accountId;
    }

    void setAccountId( uint32_t id )
    {
      m_accountId = id;
    }

  };

}

#endif
