#include "server_http.hpp"
#include "client_http.hpp"

#include <nlohmann/json.hpp>

#include <Logging/Logger.h>
#include <Config/ConfigMgr.h>

#include <Network/Connection.h>
#include <Network/Hive.h>
#include <Network/Acceptor.h>

#include <Exd/ExdData.h>
#include <Crypt/base64.h>

#include <Database/DbLoader.h>
#include <Database/ZoneDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Database/PreparedStatement.h>
#include <Util/Util.h>

//Added for the default_resource example
#include <fstream>
#include <string>

#include <vector>
#include <algorithm>

#include "SapphireApi.h"

#include <Util/CrashHandler.h>


// fucking filesystem
#if _MSC_VER >= 1925
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif


Sapphire::Common::Util::CrashHandler crashHandler;

Sapphire::Db::DbWorkerPool< Sapphire::Db::ZoneDbConnection > g_charaDb;
Sapphire::Data::ExdData g_exdData;
Sapphire::Api::SapphireApi g_sapphireAPI;


using namespace std;
using namespace Sapphire;

using HttpServer = SimpleWeb::Server< SimpleWeb::HTTP >;
using HttpClient = SimpleWeb::Client< SimpleWeb::HTTP >;

//Added for the default_resource example
void default_resource_send( const HttpServer& server, const shared_ptr< HttpServer::Response >& response,
                            const shared_ptr< ifstream >& ifs );


HttpServer server;
std::string configPath( "api.ini" );
Sapphire::Common::Config::ApiConfig   m_config;

void reloadConfig()
{
  auto pConfig = std::make_shared< Sapphire::Common::ConfigMgr >();

  Logger::info( "Loading config " + configPath );

  bool failedLoad = false;

  // load global cfg first
  if( !pConfig->loadGlobalConfig( m_config.global ) )
  {
    Logger::fatal( "Error loading config global.ini" );
    failedLoad = true;
  }

  if( !pConfig->loadConfig( configPath ) )
  {
    Logger::fatal( "Error loading config {0}", configPath );
    failedLoad = true;
  }

  if( failedLoad )
  {
    Logger::fatal( "If this is the first time starting the server, we've copied the default configs for your editing pleasure." );
    throw "Error loading config";
  }

  // setup api config
  m_config.network.listenPort = pConfig->getValue< uint16_t >( "Network", "ListenPort", 80 );
  m_config.network.listenIP = pConfig->getValue< std::string >( "Network", "ListenIp", "0.0.0.0" );
}

void print_request_info( shared_ptr< HttpServer::Request > request )
{
  Logger::info( "Request from {0} ({1})", request->remote_endpoint_address, request->path  );
}

bool loadSettings( int32_t argc, char* argv[] )
{
  reloadConfig();

  std::vector< std::string > args( argv + 1, argv + argc );
  for( size_t i = 0; i + 1 < args.size(); i += 2 )
  {
    std::string arg( "" );
    std::string val( "" );

    try
    {
      arg = Common::Util::toLowerCopy( std::string( args[ i ] ) );
      val = std::string( args[ i + 1 ] );

      // trim '-' from start of arg
      arg = arg.erase( 0, arg.find_first_not_of( '-' ) );


    }
    catch( ... )
    {
      Logger::error( "Error parsing argument: {0} value: {1}\n", arg, val );
      Logger::error( "Usage: <arg> <val> \n" );
    }
  }

  Logger::info( "Setting up generated EXD data" );
  auto dataPath = m_config.global.general.dataPath;
  if( !g_exdData.init( dataPath ) )
  {
    Logger::fatal( "Error setting up generated EXD data. Make sure that DataPath is set correctly in global.ini" );
    Logger::fatal( "DataPath: {0}", dataPath );
    return false;
  }

  Sapphire::Db::DbLoader loader;

  loader.addDb( g_charaDb, m_config.global.database );
  if( !loader.initDbs() )
    return false;

  server.config.port = m_config.network.listenPort;
  server.config.address = m_config.network.listenIP;

  Logger::info( "Database: Connected to {0}:{1}", m_config.global.database.host, m_config.global.database.port );

  return true;
}

using ContentType = enum
{
  NONE,
  TEXT_PLAIN,
  JSON,
  XML,
};

std::string buildHttpResponse( uint16_t rCode, const std::string& content = "", ContentType type = NONE )
{
  std::string result{ "" };
  std::string httpHead{ "HTTP/1.1 " };
  std::string contentHeader{ "Content-Length: " };
  std::string contentTypeHeader{ "Content-Type: " };

  switch( type )
  {
    case NONE:
      contentTypeHeader = "";
      break;
    case TEXT_PLAIN:
      contentTypeHeader += "text/plain\r\n";
      break;
    case JSON:
      contentTypeHeader += "application/json\r\n";
      break;
    case XML:
      contentTypeHeader += "text/xml\r\n";
      break;

  }

  switch( rCode )
  {
    case 200:
      result += httpHead + "200 OK\r\n";
      if( content.size() > 0 )
      {
        result += contentTypeHeader;
        result += contentHeader + std::to_string( content.size() ) + "\r\n";
      }
      break;
    case 400:
    case 401:
    case 402:
    case 403:
      result += httpHead + std::to_string( rCode ) + "\r\n";
      if( content.size() > 0 )
      {
        result += contentTypeHeader;
        result += contentHeader + std::to_string( content.size() ) + "\r\n";
      }
      break;
    case 500:
      result += httpHead + "500 Internal Server Error\r\n";
      break;
    default:
      result += httpHead + std::to_string( rCode ) + "\r\n";


  }
  result += "\r\n";
  if( content.size() > 0 )
    result += content;

  return result;
}

void getZoneName( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  string number = request->path_match[ 1 ];
  auto info = g_exdData.getRow< Excel::TerritoryType >( atoi( number.c_str() ) );
  std::string responseStr = "Not found!";
  if( info )
  {
    responseStr = info->getString( info->data().Name ) + ", " + info->getString( info->data().LVB );
  }
  *response << buildHttpResponse( 200, responseStr );
}

void createAccount( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string pass = json["pass"];
    std::string user = json["username"];
    // reloadConfig();

    std::string sId;
    if( g_sapphireAPI.createAccount( user, pass, sId ) )
    {
      nlohmann::json response_json = {
              {"sId", sId},
              {"lobbyHost", m_config.global.network.lobbyHost},
              {"frontierHost", m_config.global.network.restHost},
              {"lobbyPort", m_config.global.network.lobbyPort}
      };

      std::string json_string = response_json.dump();
      *response << buildHttpResponse( 200, json_string, JSON );
    }
    else
      *response << buildHttpResponse( 400 );
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void login( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string pass = json["pass"];
    std::string user = json["username"];

    std::string sId;

    // reloadConfig();
    if( g_sapphireAPI.login( user, pass, sId ) )
    {
      nlohmann::json response_json = {
              {"sId", sId},
              {"lobbyHost", m_config.global.network.lobbyHost},
              {"frontierHost", m_config.global.network.restHost},
              {"lobbyPort", m_config.global.network.lobbyPort}
      };

      std::string json_string = response_json.dump();

      *response << buildHttpResponse( 200, json_string, JSON );
    }
    else
      *response << buildHttpResponse( 400 );

  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void deleteCharacter( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string sId = json["sId"];
    std::string secret = json["secret"];
    std::string name = json["name"];

    // reloadConfig();

    int32_t accountId = g_sapphireAPI.checkSession( sId );

    if( m_config.global.general.serverSecret != secret )
    {
      std::string json_string = "{\"result\":\"invalid_secret\"}";
      *response << buildHttpResponse( 403, json_string, JSON );
    }
    else
    {
      g_sapphireAPI.deleteCharacter( name, accountId );
      std::string json_string = "{\"result\":\"success\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }

}

void createCharacter( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string sId = json["sId"];
    std::string secret = json["secret"];
    std::string name = json["name"];
    std::string infoJson = json["infoJson"];

    std::string finalJson = Common::Util::base64Decode( infoJson );

    // reloadConfig();

    int32_t result = g_sapphireAPI.checkSession( sId );

    if( result != -1 )
    {
      if( m_config.global.general.serverSecret != secret )
      {
        std::string json_string = "{\"result\":\"invalid_secret\"}";
        *response << buildHttpResponse( 403, json_string, JSON );
      }
      else
      {
        int32_t charId = g_sapphireAPI.createCharacter( result, name, finalJson,
                                                        m_config.global.general.defaultGMRank );

        std::string json_string = "{\"result\":\"" + std::to_string( charId ) + "\"}";
        *response << buildHttpResponse( 200, json_string, JSON );
      }
    }
    else
    {
      std::string json_string = "{\"result\":\"invalid\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }

}

void insertSession( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );

  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string sId = json["sId"];
    uint32_t accountId = json["accountId"].get< uint32_t >();
    std::string secret = json["secret"];

    // reloadConfig();
    if( m_config.global.general.serverSecret != secret )
    {
      std::string json_string = "{\"result\":\"invalid_secret\"}";
      *response << buildHttpResponse( 403, json_string, JSON );
    }
    else
    {
      g_sapphireAPI.insertSession( accountId, sId );
      std::string json_string = "{\"result\":\"success\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void checkNameTaken( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );

  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string name = json["name"];
    std::string secret = json["secret"];

    // reloadConfig();

    if( m_config.global.general.serverSecret != secret )
    {
      std::string json_string = "{\"result\":\"invalid_secret\"}";
      *response << buildHttpResponse( 403, json_string, JSON );
    }
    else
    {
      std::string json_string;
      if( !g_sapphireAPI.checkNameTaken( name ) )
        json_string = "{\"result\":\"false\"}";
      else
        json_string = "{\"result\":\"true\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void checkSession( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string sId = json["sId"];
    std::string secret = json["secret"];
    int32_t result = g_sapphireAPI.checkSession( sId );

    // reloadConfig();

    if( result != -1 )
    {
      if( m_config.global.general.serverSecret != secret )
      {
        std::string json_string = "{\"result\":\"invalid_secret\"}";
        *response << buildHttpResponse( 403, json_string, JSON );
      }
      else
      {
        std::string json_string = nlohmann::json( {
          { "result", result }
        } ).dump(1)
        ;
        *response << buildHttpResponse( 200, json_string, JSON );
      }
    }
    else
    {
      std::string json_string = "{\"result\":\"invalid\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }

}

void getNextCharId( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string secret = json["secret"];

    // reloadConfig();

    if( m_config.global.general.serverSecret != secret )
    {
      std::string json_string = "{\"result\":\"invalid_secret\"}";
      *response << buildHttpResponse( 403, json_string, JSON );
    }
    else
    {
      std::string json_string = "{\"result\":\"" + std::to_string( g_sapphireAPI.getNextEntityId() ) + "\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }

}

void getNextContentId( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );

  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string secret = json["secret"];

    // reloadConfig();

    if( m_config.global.general.serverSecret != secret )
    {
      std::string json_string = "{\"result\":\"invalid_secret\"}";
      *response << buildHttpResponse( 403, json_string, JSON );
    }
    else
    {
      std::string json_string = "{\"result\":\"" + std::to_string( g_sapphireAPI.getNextCharaId() ) + "\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }

}

void getCharacterList( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto json = nlohmann::json::parse( request->content );

    std::string sId = json["sId"];
    std::string secret = json["secret"];

    // reloadConfig();

    int32_t result = g_sapphireAPI.checkSession( sId );

    if( result != -1 )
    {
      if( m_config.global.general.serverSecret != secret )
      {
        std::string json_string = "{\"result\":\"invalid_secret\"}";
        *response << buildHttpResponse( 403, json_string, JSON );
      }
      else
      {
        auto charList = g_sapphireAPI.getCharList( result );

        auto json = nlohmann::json();

        for( auto entry : charList )
        {
          json["charArray"].push_back( {
            { "name", std::string( entry.getName() ) },
            { "entityId", std::to_string( entry.getId() ) },
            { "contentId", std::to_string( entry.getCharacterId() ) },
            { "infoJson", std::string( entry.getInfoJson() ) }
          } );
        }
        
        json["result"] = "success";
        
        *response << buildHttpResponse( 200, json.dump(1), JSON );
      }
    }
    else
    {
      std::string json_string = "{\"result\":\"invalid\"}";
      *response << buildHttpResponse( 200, json_string, JSON );
    }
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void get_init( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto web_root_path = fs::canonical( "web" );
    auto path = fs::canonical( web_root_path / "news.xml" );
    //Check if path is within web_root_path
    if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
        !std::equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
      throw invalid_argument( "path must be within root path" );
    if( !( fs::exists( path ) && fs::is_regular_file( path ) ) )
      throw invalid_argument( "file does not exist" );

    auto ifs = make_shared< ifstream >();
    ifs->open( path.string(), ifstream::in | ios::binary | ios::ate );

    if( *ifs )
    {
      auto length = ifs->tellg();
      ifs->seekg( 0, ios::beg );

      *response << "HTTP/1.1 200 OK\r\n" << "Content-Length: " << length << "\r\n\r\n";
      default_resource_send( server, response, ifs );
    }
    else
      throw invalid_argument( "could not read file" );
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void get_headline_all( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto web_root_path = fs::canonical( "web" );
    auto path = fs::canonical( web_root_path / "headlines.xml" );
    //Check if path is within web_root_path
    if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
        !std::equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
      throw invalid_argument( "path must be within root path" );
    if( !( fs::exists( path ) && fs::is_regular_file( path ) ) )
      throw invalid_argument( "file does not exist" );

    auto ifs = make_shared< ifstream >();
    ifs->open( path.string(), ifstream::in | ios::binary | ios::ate );

    if( *ifs )
    {
      auto length = ifs->tellg();
      ifs->seekg( 0, ios::beg );
      *response << "HTTP/1.1 200 OK\r\n" << "Content-Length: " << length << "\r\n\r\n";
      default_resource_send( server, response, ifs );
    }
    else
      throw invalid_argument( "could not read file" );
  }
  catch( exception& e )
  {
    *response << buildHttpResponse( 500 );
    Logger::error( e.what() );
  }
}

void defaultGet( shared_ptr< HttpServer::Response > response, shared_ptr< HttpServer::Request > request )
{
  print_request_info( request );
  try
  {
    auto web_root_path = fs::canonical( "web" );
    auto path = fs::canonical( "web" + request->path );
    //Check if path is within web_root_path
    if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
        !std::equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
      throw invalid_argument( "path must be within root path" );
    if( fs::is_directory( path ) )
      path /= "index.html";
    if( !( fs::exists( path ) && fs::is_regular_file( path ) ) )
      throw invalid_argument( "file does not exist" );

    auto ifs = make_shared< ifstream >();
    ifs->open( path.string(), ifstream::in | ios::binary | ios::ate );

    if( *ifs )
    {
      auto length = ifs->tellg();
      ifs->seekg( 0, ios::beg );

      *response << "HTTP/1.1 200 OK\r\n" << "Content-Length: " << length << "\r\n\r\n";
      default_resource_send( server, response, ifs );
    }
    else
      throw invalid_argument( "could not read file" );
  }
  catch( const exception& )
  {
    string content = "Path not found: " + request->path;
    *response << buildHttpResponse( 404, content );
  }
}

int main( int argc, char* argv[] )
{
  Logger::init( "log/api" );

  Logger::info( "===========================================================" );
  Logger::info( "Sapphire API Server " );
  Logger::info( "Version: 0.0.1" );
  Logger::info( "Compiled: " __DATE__ " " __TIME__ );
  Logger::info( "===========================================================" );

  if( !loadSettings( argc, argv ) )
    throw std::exception();

  Logger::setLogLevel( m_config.global.general.logLevel );

  server.resource[ "^/ZoneName/([0-9]+)$" ][ "GET" ] = &getZoneName;
  server.resource[ "^/sapphire-api/lobby/createAccount" ][ "POST" ] = &createAccount;
  server.resource[ "^/sapphire-api/lobby/login" ][ "POST" ] = &login;
  server.resource[ "^/sapphire-api/lobby/deleteCharacter" ][ "POST" ] = &deleteCharacter;
  server.resource[ "^/sapphire-api/lobby/createCharacter" ][ "POST" ] = &createCharacter;
  server.resource[ "^/sapphire-api/lobby/insertSession" ][ "POST" ] = &insertSession;
  server.resource[ "^/sapphire-api/lobby/checkNameTaken" ][ "POST" ] = &checkNameTaken;
  server.resource[ "^/sapphire-api/lobby/checkSession" ][ "POST" ] = &checkSession;
  server.resource[ "^/sapphire-api/lobby/getNextEntityId" ][ "POST" ] = &getNextCharId;
  server.resource[ "^/sapphire-api/lobby/getNextCharaId" ][ "POST" ] = &getNextContentId;
  server.resource[ "^/sapphire-api/lobby/getCharacterList" ][ "POST" ] = &getCharacterList;
  server.resource[ "^(/frontier-api/ffxivsupport/view/get_init)(.*)" ][ "GET" ] = &get_init;
  server.resource[ "^(/frontier-api/ffxivsupport/information/get_headline_all)(.*)" ][ "GET" ] = &get_headline_all;

  server.default_resource[ "GET" ] = &defaultGet;

  thread server_thread( [ & ]()
                        {
                          //Start server
                          server.start();
                        } );

  Logger::info( "API server running on {0}:{1}", m_config.network.listenIP, m_config.network.listenPort );

  //Wait for server to start so that the client can connect
  this_thread::sleep_for( chrono::seconds( 1 ) );

  server_thread.join();
  return 0;
}

void default_resource_send( const HttpServer& server, const shared_ptr< HttpServer::Response >& response,
                            const shared_ptr< ifstream >& ifs )
{
  //read and send 128 KB at a time
  static vector< char > buffer( 131072 ); // Safe when server is running on one thread
  streamsize read_length;
  if( ( read_length = ifs->read( &buffer[ 0 ], buffer.size() ).gcount() ) > 0 )
  {
    response->write( &buffer[ 0 ], read_length );
    if( read_length == static_cast< streamsize >( buffer.size() ) )
    {
      server.send( response, [ &server, response, ifs ]( const std::error_code& ec )
      {
        if( !ec )
          default_resource_send( server, response, ifs );
        else
          cerr << "Connection interrupted" << endl;
      } );
    }
  }
}
