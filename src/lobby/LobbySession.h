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
    char m_sessionId[ 64 ];
    uint8_t m_charaIndex;

  public:
    std::string newCharName;

    LobbySession() = default;
    ~LobbySession() = default;

    uint32_t getIP()
    {
      return m_IP;
    }

    char* getSessionId()
    {
      return m_sessionId;
    }

    void setSessionId( char* sessionId )
    {
      memcpy( m_sessionId, sessionId, sizeof( m_sessionId ) );
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
    void setCharaIndex( uint8_t index )
    {
      m_charaIndex = index;
    }

    uint8_t getCharaIndex()
    {
      return m_charaIndex;
    }

  };

}

#endif
