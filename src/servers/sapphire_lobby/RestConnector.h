#ifndef _RESTCONNECTOR_H_
#define _RESTCONNECTOR_H_

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "client_http.hpp"
#include "Forwards.h"

typedef SimpleWeb::Client< SimpleWeb::HTTP > HttpClient;
typedef std::shared_ptr< SimpleWeb::ClientBase< SimpleWeb::HTTP >::Response > HttpResponse;

namespace Core {
class Session;

namespace Network {
class LobbySession;

class RestConnector
{
public:
  RestConnector();

  ~RestConnector();

  HttpResponse requestApi( std::string endpoint, std::string data );

  LobbySessionPtr getSession( char* sId );

  int32_t createCharacter( char* sId, std::string name, std::string infoJson );

  std::vector< std::tuple< std::string, uint32_t, uint64_t, std::string>> getCharList( char* sId );

  bool deleteCharacter( char* sId, std::string name );

  bool checkNameTaken( std::string name );

  uint32_t getNextCharId();

  uint64_t getNextContentId();

  std::string serverSecret;
  std::string restHost;

};
}
}

#endif
