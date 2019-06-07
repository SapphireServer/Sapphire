#pragma once

#ifndef _CLobbySession_H_
#define _CLobbySession_H_

#include <stdint.h>
#include <string>
#include <string.h>

namespace Sapphire::Lobby
{

  class LobbySession
  {

  private:
    uint32_t m_IP;
    uint32_t m_accountID;
    uint8_t m_sessionId[56];

  public:
    std::string newCharName;

    LobbySession( void );

    ~LobbySession( void );

    uint32_t getIP()
    {
      return m_IP;
    }

    uint8_t* getSessionId()
    {
      return m_sessionId;
    }

    void setSessionId( uint8_t* sessionId )
    {
      memcpy( m_sessionId, sessionId, 56 );
    }

    void setIP( uint32_t iP )
    {
      m_IP = iP;
    }

    uint32_t getAccountID()
    {
      return m_accountID;
    }

    void setAccountID( uint32_t iD )
    {
      m_accountID = iD;
    }

  };

}

#endif
