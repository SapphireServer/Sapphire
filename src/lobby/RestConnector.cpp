#include "RestConnector.h"
#include "LobbySession.h"
#include "ServerLobby.h"
#include <Logging/Logger.h>
#include <Crypt/base64.h>
#include <time.h>
#include <iomanip>

#include <nlohmann/json.hpp>

using namespace Sapphire;

typedef std::vector< std::tuple< std::string, uint32_t, uint64_t, std::string > > CharList;

Lobby::RestConnector::RestConnector()
{

}

Lobby::RestConnector::~RestConnector()
{

}

HttpResponse Lobby::RestConnector::requestApi( std::string endpoint, std::string data )
{
  HttpClient client( restHost );

  std::string reqstr = "/sapphire-api/lobby/" + endpoint;

  HttpResponse r;
  try
  {
    r = client.request( "POST", reqstr, data );
  }
  catch( std::exception& e )
  {
    Logger::error( "{0} failed, Api is not reachable: {1}", endpoint, e.what() );
    return nullptr;
  }
  return r;
}

Lobby::LobbySessionPtr Lobby::RestConnector::getSession( char* sId )
{
  std::string json_string = "{\"sId\": \"" + std::string( sId ) + "\",\"secret\": \"" + serverSecret + "\"}";

  HttpResponse r = requestApi( "checkSession", json_string );

  if( r == nullptr )
    return nullptr;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    nlohmann::json json;  

    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return nullptr;
    }

    if( content.find( "invalid" ) == std::string::npos )
    {
      LobbySessionPtr pSession( new Lobby::LobbySession() );
      pSession->setAccountID( json["result"].get< uint32_t >() );
      pSession->setSessionId( ( uint8_t* ) sId );
      return pSession;
    }
    else
    {
      return nullptr;
    }
  }
  else
  {
    return nullptr;
  }
}

bool Lobby::RestConnector::checkNameTaken( std::string name )
{
  std::string json_string = "{\"name\": \"" + name + "\",\"secret\": \"" + serverSecret + "\"}";

  HttpResponse r = requestApi( "checkNameTaken", json_string );

  if( r == nullptr )
    return true;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    auto json = nlohmann::json();

    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return true;
    }

    if( json["result"] != "invalid" && json["result"] == "false" )
      return false;
    return true;
  }
  else
  {
    return true;
  }
}

uint32_t Lobby::RestConnector::getNextCharId()
{
  std::string json_string = "{\"secret\": \"" + serverSecret + "\"}";

  HttpResponse r = requestApi( "getNextCharId", json_string );

  if( r == nullptr )
    return -1;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    auto json = nlohmann::json();

    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return -1;
    }

    if( content.find( "invalid" ) == std::string::npos )
    {
      return std::stoi( std::string( json["result"] ) );
    }
    else
    {
      return -1;
    }
  }
  else
  {
    return -1;
  }
}

uint64_t Lobby::RestConnector::getNextContentId()
{
  std::string json_string = "{\"secret\": \"" + serverSecret + "\"}";

  HttpResponse r = requestApi( "getNextContentId", json_string );

  if( r == nullptr )
    return -1;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    auto json = nlohmann::json();

    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return -1;
    }

    if( content.find( "invalid" ) == std::string::npos )
    {
      return std::stoll( std::string( json["result"] ) );
    }
    else
    {
      return -1;
    }
  }
  else
  {
    return -1;
  }
}

CharList Lobby::RestConnector::getCharList( char* sId )
{
  std::string json_string = "{\"sId\": \"" + std::string( sId, 56 ) + "\",\"secret\": \"" + serverSecret + "\"}";

  HttpResponse r = requestApi( "getCharacterList", json_string );

  CharList list;
  if( r == nullptr )
    return list;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  Logger::debug( content );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    auto json = nlohmann::json();

    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return list;
    }

    if( json["result"].get< std::string >().find( "invalid" ) == std::string::npos )
    {

      Logger::debug( json["result"] );

      for( auto& child : json["charArray"] )
      {
        Logger::info( child["contentId"] );
        //std::string, uint32_t, uint64_t, std::string
        list.push_back( { child["name"],
                          std::stoi( std::string( child["charId"] ) ),
                          std::stoll( std::string( child["contentId"] ) ),
                          child["infoJson"] 
                        } );
      }

      return list;

    }
    else
    {
      return list;
    }
  }
  else
  {
    return list;
  }
}

bool Lobby::RestConnector::deleteCharacter( char* sId, std::string name )
{
  std::string json_string =
    "{\"sId\": \"" + std::string( sId, 56 ) + "\",\"secret\": \"" + serverSecret + "\",\"name\": \"" + name + "\"}";

  HttpResponse r = requestApi( "deleteCharacter", json_string );

  if( r == nullptr )
    return false;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    auto json = nlohmann::json();
    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return false;
    }

    if( content.find( "invalid" ) == std::string::npos )
      return true;
    return false;
  }
  else
  {
    return false;
  }
}

int Lobby::RestConnector::createCharacter( char* sId, std::string name, std::string infoJson )
{
  std::string json_string =
    "{\"sId\": \"" + std::string( sId, 56 ) + "\",\"secret\": \"" + serverSecret + "\",\"name\": \"" + name +
    "\",\"infoJson\": \"" + Common::Util::base64Encode( ( uint8_t* ) infoJson.c_str(), infoJson.length() ) + "\"}";

  HttpResponse r = requestApi( "createCharacter", json_string );

  if( r == nullptr )
    return -1;

  std::string content = std::string( std::istreambuf_iterator< char >( r->content ), {} );
  Logger::debug( content );
  if( r->status_code.find( "200" ) != std::string::npos )
  {
    auto json = nlohmann::json();

    try
    {
      json = json.parse( content );
    }
    catch( std::exception& e )
    {
      Logger::debug( "Could not parse Api response: {0}", e.what() );
      return -1;
    }

    if( content.find( "invalid" ) == std::string::npos )
      return std::stoi( json["result"].get< std::string >() );
    return -1;
  }
  else
  {
    return -1;
  }
}
