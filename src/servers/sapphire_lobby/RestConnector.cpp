#include "RestConnector.h"
#include "LobbySession.h"
#include "ServerLobby.h"
#include <Logging/Logger.h>
#include <Crypt/base64.h>
#include <time.h>
#include <iomanip>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

extern Core::Logger g_log;

typedef std::vector<std::tuple<std::string, uint32_t, uint64_t, std::string>> CharList;

Core::Network::RestConnector::RestConnector()
{

}

Core::Network::RestConnector::~RestConnector()
{

}

HttpResponse Core::Network::RestConnector::requestApi( std::string endpoint, std::string data )
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
      g_log.error( endpoint + " failed, REST is not reachable: " + std::string( e.what() ) );
      return nullptr;
   }
   return r;
}

Core::LobbySessionPtr Core::Network::RestConnector::getSession( char* sId )
{
   std::string json_string = "{\"sId\": \"" + std::string( sId ) + "\",\"secret\": \"" + serverSecret + "\"}";

   HttpResponse r = requestApi( "checkSession", json_string );
   
   if( r == nullptr )
      return nullptr;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
         return nullptr;
      }

      if( content.find( "invalid" ) == std::string::npos )
      {
         LobbySessionPtr pSession( new Core::LobbySession() );
         pSession->setAccountID( atoi( pt.get<std::string>( "result" ).c_str() ) );
         pSession->setSessionId( (uint8_t *)sId );
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

bool Core::Network::RestConnector::checkNameTaken( std::string name )
{
   std::string json_string = "{\"name\": \"" + name + "\",\"secret\": \"" + serverSecret + "\"}";

   HttpResponse r = requestApi( "checkNameTaken", json_string );

   if( r == nullptr )
      return true;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
         return true;
      }

      if( pt.get<std::string>( "result" ) != "invalid" && pt.get<std::string>( "result" ) == "false" )
         return false;
      return true;
   }
   else
   {
      return true;
   }
}

uint32_t Core::Network::RestConnector::getNextCharId()
{
   std::string json_string = "{\"secret\": \"" + serverSecret + "\"}";

   HttpResponse r = requestApi( "getNextCharId", json_string );

   if( r == nullptr )
      return -1;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
         return -1;
      }

      if( content.find( "invalid" ) == std::string::npos )
      {
         return pt.get<uint32_t>( "result" );
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

uint64_t Core::Network::RestConnector::getNextContentId()
{
   std::string json_string = "{\"secret\": \"" + serverSecret + "\"}";

   HttpResponse r = requestApi( "getNextContentId", json_string );

   if( r == nullptr )
      return -1;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
         return -1;
      }

      if( content.find( "invalid" ) == std::string::npos )
      {
         return pt.get<uint64_t>( "result" );
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

CharList Core::Network::RestConnector::getCharList( char * sId )
{
   std::string json_string = "{\"sId\": \"" + std::string( sId, 56 ) + "\",\"secret\": \"" + serverSecret + "\"}";

   HttpResponse r = requestApi( "getCharacterList", json_string );

   CharList list;
   if( r == nullptr )
      return list;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   g_log.debug( content );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
         return list;
      }

      if( pt.get<std::string>( "result" ).find( "invalid" ) == std::string::npos )
      {

         g_log.debug( pt.get_value<std::string>( "result" ) );

         for( auto& child : pt.get_child( "charArray" ) ){
            g_log.debug( child.second.get<std::string>( "contentId" ) );
            list.push_back( std::make_tuple( child.second.get<std::string>( "name" ), atoi( child.second.get<std::string>( "charId" ).c_str() ), child.second.get<uint64_t>( "contentId" ), child.second.get<std::string>( "infoJson" ) ) );
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

bool Core::Network::RestConnector::deleteCharacter( char* sId, std::string name )
{
   std::string json_string = "{\"sId\": \"" + std::string( sId, 56 ) + "\",\"secret\": \"" + serverSecret + "\",\"name\": \"" + name + "\"}";

   HttpResponse r = requestApi( "deleteCharacter", json_string );

   if( r == nullptr )
      return false;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
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

int Core::Network::RestConnector::createCharacter( char * sId,  std::string name, std::string infoJson )
{
   std::string json_string = "{\"sId\": \"" + std::string( sId, 56 ) + "\",\"secret\": \"" + serverSecret + "\",\"name\": \"" + name + "\",\"infoJson\": \"" + Core::Util::base64_encode( (uint8_t *)infoJson.c_str(), infoJson.length() ) + "\"}";

   HttpResponse r = requestApi( "createCharacter", json_string );

   if( r == nullptr )
      return -1;

   std::string content = std::string( std::istreambuf_iterator<char>( r->content ), {} );
   g_log.debug( content );
   if( r->status_code.find( "200" ) != std::string::npos )
   {
      using namespace boost::property_tree;
      ptree pt;

      try {
         std::stringstream ss;
         ss << content;

         read_json( ss, pt );
      }
      catch( std::exception& e )
      {
         g_log.debug( "Could not parse REST response: " + std::string( e.what() ) );
         return -1;
      }

      if( content.find( "invalid" ) == std::string::npos )
         return atoi( pt.get<std::string>( "result" ).c_str() );
      return -1;
   }
   else
   {
      return -1;
   }
}
