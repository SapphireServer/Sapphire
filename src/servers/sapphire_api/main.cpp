#include "server_http.hpp"
#include "client_http.hpp"

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <Logging/Logger.h>
#include <Config/XMLConfig.h>

#include <Network/Connection.h>
#include <Network/Hive.h>
#include <Network/Acceptor.h>

#include <Exd/ExdDataGenerated.h>
#include <Crypt/base64.h>

#include <Database/DbLoader.h>
#include <Database/CharaDbConnection.h>
#include <Database/DbWorkerPool.h>
#include <Database/PreparedStatement.h>

//Added for the default_resource example
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <vector>
#include <algorithm>

#include <Framework.h>

#include "Forwards.h"
#include "SapphireAPI.h"


Core::Framework g_fw;
Core::Logger g_log;
Core::Db::DbWorkerPool< Core::Db::CharaDbConnection > g_charaDb;
Core::Data::ExdDataGenerated g_exdDataGen;
Core::Network::SapphireAPI g_sapphireAPI;

using namespace std;
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server< SimpleWeb::HTTP >;
using HttpClient = SimpleWeb::Client< SimpleWeb::HTTP >;

//Added for the default_resource example
void default_resource_send( const HttpServer &server, const shared_ptr< HttpServer::Response > &response,
                            const shared_ptr< ifstream > &ifs );


auto m_pConfig = boost::make_shared< Core::XMLConfig >();
HttpServer server;
std::string configPath( "config/settings_rest.xml" );

void reloadConfig()
{
   m_pConfig = boost::make_shared< Core::XMLConfig >();

   if( !m_pConfig->loadConfig( configPath ) )
      throw "Error loading config ";
}

void print_request_info( shared_ptr< HttpServer::Request > request ) 
{
   g_log.info( "Request from " + request->remote_endpoint_address + " (" + request->path + ")" );
}

bool loadSettings( int32_t argc, char* argv[] )
{
   g_log.info( "Loading config " + configPath );

   if( !m_pConfig->loadConfig( configPath ) )
   {
      g_log.fatal( "Error loading config " + configPath );
      return false;
   }

   std::vector<std::string> args( argv + 1, argv + argc );
   for( size_t i = 0; i + 1 < args.size(); i += 2 )
   {
      std::string arg( "" );
      std::string val( "" );

      try
      {
         arg = boost::to_lower_copy( std::string( args[i] ) );
         val = std::string( args[i + 1] );

         // trim '-' from start of arg
         arg = arg.erase( 0, arg.find_first_not_of( '-' ) );

         if( arg == "ip" )
         {
            // todo: ip addr in config
            m_pConfig->setValue< std::string >( "Settings.General.ListenIP", val );
         }
         else if( arg == "p" || arg == "port" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.ListenPort", val );
         }
         else if( arg == "exdpath" || arg == "datapath" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.DataPath", val );
         }
         else if( arg == "h" || arg == "dbhost" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Host", val );
         }
         else if( arg == "dbport" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Port", val );
         }
         else if( arg == "u" || arg == "user" || arg == "dbuser" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Username", val );
         }
         else if( arg == "pass" || arg == "dbpass" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Pass", val );
         }
         else if( arg == "d" || arg == "db" || arg == "database" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.Mysql.Database", val );
         }
         else if ( arg == "lobbyip" || arg == "lobbyhost" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.LobbyHost", val );
         }
         else if ( arg == "lobbyport" )
         {
            m_pConfig->setValue< std::string >( "Settings.General.LobbyPort", val );
         }
      }
      catch( ... )
      {
         g_log.error( "Error parsing argument: " + arg + " " + "value: " + val + "\n" );
         g_log.error( "Usage: <arg> <val> \n" );
      }
   }

   g_log.info( "Setting up generated EXD data" );
   if( !g_exdDataGen.init( m_pConfig->getValue< std::string >( "Settings.General.DataPath", "" ) ) )
   {
      g_log.fatal( "Error setting up generated EXD data " );
      return false;
   }

   Core::Db::DbLoader loader;

   Core::Db::ConnectionInfo info;
   info.password = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Pass", "" );
   info.host = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Host", "127.0.0.1" );
   info.database = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Database", "sapphire" );
   info.port = m_pConfig->getValue< uint16_t >( "Settings.General.Mysql.Port", 3306 );
   info.user = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Username", "root" );
   info.syncThreads = m_pConfig->getValue< uint8_t >( "Settings.General.Mysql.SyncThreads", 2 );
   info.asyncThreads = m_pConfig->getValue< uint8_t >( "Settings.General.Mysql.AsyncThreads", 2 );

   loader.addDb( g_charaDb, info );
   if( !loader.initDbs() )
      return false;

   server.config.port = static_cast< uint16_t >( std::stoul( m_pConfig->getValue< std::string >( "Settings.General.HttpPort", "80" ) ) );

   g_log.info( "Database: Connected to " + info.host + ":" + std::to_string( info.port ) );

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
   std::string result{""};
   std::string httpHead{"HTTP/1.1 "};
   std::string contentHeader{"Content-Length: "};
   std::string contentTypeHeader{"Content-Type: "};

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

void getZoneName( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   string number = request->path_match[1];
   auto info = g_exdDataGen.get< Core::Data::TerritoryType >( atoi( number.c_str() ) );
   std::string responseStr = "Not found!";
   if( info )
      responseStr = info->name + ", " + info->bg;
   *response << buildHttpResponse( 200, responseStr );
}

void createAccount( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {

      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );

      std::string pass = pt.get<string>( "pass" );
      std::string user = pt.get<string>( "username" );
      // reloadConfig();

      std::string sId;
      if( g_sapphireAPI.createAccount( user, pass, sId ) )
      {
         std::string json_string = "{\"sId\":\"" + sId + 
                                    "\", \"lobbyHost\":\"" + m_pConfig->getValue< std::string >( "Settings.General.LobbyHost" ) + 
                                    "\", \"frontierHost\":\"" + m_pConfig->getValue< std::string >( "Settings.General.FrontierHost" ) + "\"}";
         *response << buildHttpResponse( 200, json_string, JSON );
      }
      else
         *response << buildHttpResponse( 400 );
   }
   catch( exception& e )
   {
      *response << buildHttpResponse( 500 );
      g_log.error( e.what() );
   }
}

void login( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );

      std::string pass = pt.get<string>( "pass" );
      std::string user = pt.get<string>( "username" );

      std::string sId;

      // reloadConfig();
      if( g_sapphireAPI.login( user, pass, sId ) )
      {
         std::string json_string = "{\"sId\":\"" + sId + 
                                    "\", \"lobbyHost\":\"" + m_pConfig->getValue< std::string >("Settings.General.LobbyHost") + 
                                    "\", \"frontierHost\":\"" + m_pConfig->getValue< std::string >( "Settings.General.FrontierHost" ) + "\"}";
         *response << buildHttpResponse( 200, json_string, JSON );
      }
      else
         *response << buildHttpResponse( 400 );

   }
   catch( exception& e )
   { 
      *response << buildHttpResponse( 500 );
      g_log.error( e.what() );
   }

}

void deleteCharacter( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string sId = pt.get<string>( "sId" );
      std::string secret = pt.get<string>( "secret" );
      std::string name = pt.get<string>( "name" );
          
      // reloadConfig();

      int32_t accountId = g_sapphireAPI.checkSession( sId );

      if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret )
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
      g_log.error( e.what() );
   }

}

void createCharacter( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string sId = pt.get<string>( "sId" );
      std::string secret = pt.get<string>( "secret" );
      std::string name = pt.get<string>( "name" );
      std::string infoJson = pt.get<string>( "infoJson" );

      std::string finalJson = Core::Util::base64_decode( infoJson );

      // reloadConfig();

      int32_t result = g_sapphireAPI.checkSession( sId );

      if( result != -1 )
      {
         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
         {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << buildHttpResponse( 403, json_string, JSON );
         }
         else
         {
            int32_t charId = g_sapphireAPI.createCharacter( result, name, finalJson, m_pConfig->getValue< uint8_t >( "Settings.Parameters.DefaultGMRank", 255 ) );

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
      g_log.error( e.what() );
   }

}

void insertSession( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );

   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string sId = pt.get<string>( "sId" );
      uint32_t accountId = pt.get<uint32_t>( "accountId" );
      std::string secret = pt.get<string>( "secret" );
         // reloadConfig();
      if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
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
      g_log.error( e.what() );
   }
}

void checkNameTaken( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );

   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );

      std::string name = pt.get<string>( "name" );
      std::string secret = pt.get<string>( "secret" );

      // reloadConfig();

      if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
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
      g_log.error( e.what() );
   }
}

void checkSession( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string sId = pt.get<string>( "sId" );
      std::string secret = pt.get<string>( "secret" );
      int32_t result = g_sapphireAPI.checkSession( sId );

      // reloadConfig();

      if( result != -1 )
      {
         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
         {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << buildHttpResponse( 403, json_string, JSON );
         }
         else
         {
            std::string json_string = "{\"result\":\"" + std::to_string( result ) + "\"}";
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
      g_log.error( e.what() );
   }

}

void getNextCharId( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string secret = pt.get<string>( "secret" );

      // reloadConfig();

      if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
      {
         std::string json_string = "{\"result\":\"invalid_secret\"}";
         *response << buildHttpResponse( 403, json_string, JSON );
      }
      else
      {
         std::string json_string = "{\"result\":\"" + std::to_string( g_sapphireAPI.getNextCharId() ) + "\"}";
         *response << buildHttpResponse( 200, json_string, JSON );
      }
   }
   catch( exception& e )
   {
      *response << buildHttpResponse( 500 );
      g_log.error( e.what() );
   }

}

void getNextContentId( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );

   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string secret = pt.get<string>( "secret" );

      // reloadConfig();

      if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
      {
         std::string json_string = "{\"result\":\"invalid_secret\"}";
         *response << buildHttpResponse( 403, json_string, JSON );
      }
      else
      {
         std::string json_string = "{\"result\":\"" + std::to_string( g_sapphireAPI.getNextContentId() ) + "\"}";
         *response << buildHttpResponse( 200, json_string, JSON );
      }
   }
   catch( exception& e )
   {
      *response << buildHttpResponse( 500 );
      g_log.error( e.what() );
   }

}

void getCharacterList( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      using namespace boost::property_tree;
      ptree pt;
      read_json( request->content, pt );
      std::string sId = pt.get<string>( "sId" );
      std::string secret = pt.get<string>( "secret" );

      // reloadConfig();

      int32_t result = g_sapphireAPI.checkSession( sId );

      if( result != -1 )
      {
         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) 
         {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << buildHttpResponse( 403, json_string, JSON );
         }
         else
         {
            auto charList = g_sapphireAPI.getCharList( result );
            using boost::property_tree::ptree;
            ptree pt;
            ptree char_tree;

            for( auto entry : charList )
            {
               ptree tree_entry;
               tree_entry.put( "name", std::string( entry.getName() ) );
               tree_entry.put( "charId", std::to_string( entry.getId() ) );
               tree_entry.put( "contentId", std::to_string( entry.getContentId() ) );
               tree_entry.put( "infoJson", std::string( entry.getInfoJson() ) );
               char_tree.push_back( std::make_pair( "", tree_entry ) );
            }

            pt.add_child( "charArray", char_tree );
            pt.put( "result", "success" );
            std::ostringstream oss;
            write_json( oss, pt );
            std::string responseStr = oss.str();
            *response << buildHttpResponse( 200, responseStr, JSON );
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
      g_log.error( e.what() );
   }
}

void get_init( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      auto web_root_path = boost::filesystem::canonical( "web" );
      auto path = boost::filesystem::canonical( web_root_path / "news.xml" );
      //Check if path is within web_root_path
      if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
          !std::equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
         throw invalid_argument( "path must be within root path" );
      if( !( boost::filesystem::exists( path ) && boost::filesystem::is_regular_file( path ) ) )
         throw invalid_argument( "file does not exist" );

      auto ifs = make_shared<ifstream>();
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
      g_log.error( e.what() );
   }
}

void get_headline_all( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      auto web_root_path = boost::filesystem::canonical( "web" );
      auto path = boost::filesystem::canonical( web_root_path / "headlines.xml" );
      //Check if path is within web_root_path
      if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
          !std::equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
         throw invalid_argument( "path must be within root path" );
      if( !( boost::filesystem::exists( path ) && boost::filesystem::is_regular_file( path ) ) )
         throw invalid_argument( "file does not exist" );

      auto ifs = make_shared<ifstream>();
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
      g_log.error( e.what() );
   }
}

void defaultGet( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) 
{
   print_request_info( request );
   try
   {
      auto web_root_path = boost::filesystem::canonical( "web" );
      auto path = boost::filesystem::canonical( web_root_path / request->path );
      //Check if path is within web_root_path
      if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
          !std::equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
         throw invalid_argument( "path must be within root path" );
      if( boost::filesystem::is_directory( path ) )
         path /= "index.html";
      if( !( boost::filesystem::exists( path ) && boost::filesystem::is_regular_file( path ) ) )
         throw invalid_argument( "file does not exist" );

      auto ifs = make_shared<ifstream>();
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
   catch( const exception & )
   {
      string content = "Path not found: " + request->path;
      *response << buildHttpResponse( 400, content );
   }
}

int main( int argc, char* argv[] )
{
   auto pLog = boost::shared_ptr< Core::Logger >( new Core::Logger() );
   g_fw.set< Core::Logger >( pLog );
   g_log.setLogPath( "log/SapphireAPI" );
   g_log.init();

   g_log.info( "===========================================================" );
   g_log.info( "Sapphire API Server " );
   g_log.info( "Version: 0.0.1" );
   g_log.info( "Compiled: " __DATE__ " " __TIME__ );
   g_log.info( "===========================================================" );

   if( !loadSettings( argc, argv ) )
      throw std::exception();

   server.config.port = stoi( m_pConfig->getValue< std::string >( "Settings.General.HttpPort", "80" ) );
   g_log.info( "Starting API server at port " + m_pConfig->getValue< std::string >( "Settings.General.HttpPort", "80" ) + "..." );

   server.resource["^/ZoneName/([0-9]+)$"]["GET"] = &getZoneName; 
   server.resource["^/sapphire-api/lobby/createAccount"]["POST"] = &createAccount;
   server.resource["^/sapphire-api/lobby/login"]["POST"] = &login;
   server.resource["^/sapphire-api/lobby/deleteCharacter"]["POST"] = &deleteCharacter;
   server.resource["^/sapphire-api/lobby/createCharacter"]["POST"] = &createCharacter; 
   server.resource["^/sapphire-api/lobby/insertSession"]["POST"] = &insertSession;
   server.resource["^/sapphire-api/lobby/checkNameTaken"]["POST"] = &checkNameTaken;
   server.resource["^/sapphire-api/lobby/checkSession"]["POST"] = &checkSession;
   server.resource["^/sapphire-api/lobby/getNextCharId"]["POST"] = &getNextCharId;
   server.resource["^/sapphire-api/lobby/getNextContentId"]["POST"] = &getNextContentId;
   server.resource["^/sapphire-api/lobby/getCharacterList"]["POST"] = &getCharacterList;
   server.resource["^(/frontier-api/ffxivsupport/view/get_init)(.*)"]["GET"] = &get_init;
   server.resource["^(/frontier-api/ffxivsupport/information/get_headline_all)(.*)"]["GET"] = &get_headline_all;
   
   server.default_resource["GET"] = &defaultGet;
   
   thread server_thread( [&]() 
   {
      //Start server
      server.start();
   } );

   //Wait for server to start so that the client can connect
   this_thread::sleep_for( chrono::seconds( 1 ) );
   
   server_thread.join();
   return 0;
}

void default_resource_send( const HttpServer &server, const shared_ptr<HttpServer::Response> &response,
                            const shared_ptr<ifstream> &ifs )
{
   //read and send 128 KB at a time
   static vector<char> buffer( 131072 ); // Safe when server is running on one thread
   streamsize read_length;
   if( ( read_length = ifs->read( &buffer[0], buffer.size() ).gcount() ) > 0 )
   {
      response->write( &buffer[0], read_length );
      if( read_length == static_cast< streamsize >( buffer.size() ) )
      {
         server.send( response, [&server, response, ifs]( const boost::system::error_code &ec ) {
            if( !ec )
               default_resource_send( server, response, ifs );
            else
               cerr << "Connection interrupted" << endl;
         } );
      }
   }
}
