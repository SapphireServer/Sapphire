#include "Session.h"

using namespace Sapphire::Api;

Session::Session()
{

}

Session::~Session()
{

}

uint32_t Session::getIp() const
{
  return m_ip;
}

void Session::setSessionId( uint8_t* sessionId )
{
  memcpy( m_sessionId, sessionId, 56 );
}

void Session::setIp( uint32_t ip )
{
  m_ip = ip;
}

uint32_t Session::getAccountId() const
{
  return m_accountId;
}

void Session::setAccountId( uint32_t id )
{
  m_accountId = id;
}
