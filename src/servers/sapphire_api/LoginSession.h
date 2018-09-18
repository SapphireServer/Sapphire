#pragma once

#ifndef _CLoginSession_H_
#define _CLoginSession_H_

#include <stdint.h>
#include <string>
#include <string.h>

namespace Core {

class LoginSession
{

private:
  uint32_t m_IP;
  uint32_t m_accountID;

  uint8_t m_sessionId[56];

public:

  std::string newCharName;

  LoginSession( void );

  ~LoginSession( void );

  uint32_t getIP()
  {
    return m_IP;
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

  /*INLINE CLobbySocket* getSocket() {
  return m_pGS;
  }

  INLINE void setSocket(CLobbySocket * pS) {
  m_pGS = pS;
  }*/

};

}

#endif
