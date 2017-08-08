#include "server_http.hpp"
#include "client_http.hpp"

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <Server_Common/Logger.h>
#include <Server_Common/XMLConfig.h>
#include <Server_Common/Database.h>

#include <Server_Common/Connection.h>
#include <Server_Common/Hive.h>
#include <Server_Common/Acceptor.h>

#include <Server_Common/ExdData.h>
#include <Server_Common/base64.h>

//Added for the default_resource example
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <vector>
#include <algorithm>

#include "Forwards.h"
#include "SapphireAPI.h"


Core::Logger g_log;
Core::Db::Database g_database;
Core::Data::ExdData g_exdData;
Core::Network::SapphireAPI g_sapphireAPI;

using namespace std;
using namespace boost::property_tree;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

//Added for the default_resource example
void default_resource_send( const HttpServer &server, const shared_ptr<HttpServer::Response> &response,
                            const shared_ptr<ifstream> &ifs );

void print_request_info( shared_ptr<HttpServer::Request> request ) {
   g_log.info( "Request from " + request->remote_endpoint_address + " (" + request->path + ")" );
}

int main()
{
   g_log.setLogPath( "SapphireAPI" );
   g_log.init();

   g_log.info( "===========================================================" );
   g_log.info( "Sapphire API Server " );
   g_log.info( "Version: 0.0.1" );
   g_log.info( "Compiled: " __DATE__ " " __TIME__ );
   g_log.info( "===========================================================" );

   auto m_pConfig = new Core::XMLConfig();

   g_log.info( "Loading config settings_rest.xml" );

   if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
   {
      g_log.fatal( "Error loading config settings_rest.xml" );
      return 1;
   }

   if( !g_exdData.init( m_pConfig->getValue< std::string >( "Settings.General.DataPath" ) ) )
   {
      g_log.fatal( "Error setting up EXD data " );
      return 1;
   }

   Core::Db::DatabaseParams params;
   params.bufferSize = 16384;
   params.connectionCount = 3;
   params.databaseName = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Database", "sapphire" );
   params.hostname = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Host", "127.0.0.1" );
   params.password = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Pass", "" );
   params.port = m_pConfig->getValue< uint16_t >( "Settings.General.Mysql.Port", 3306 );
   params.username = m_pConfig->getValue< std::string >( "Settings.General.Mysql.Username", "root" );

   if( !g_database.initialize( params ) )
   {
      std::this_thread::sleep_for( std::chrono::milliseconds( 5000 ) );
      return -1;
   }

   g_log.info( "Database: Connected to " + params.hostname + ":" + std::to_string( params.port ) );
   g_exdData.loadZoneInfo();

   HttpServer server;
   server.config.port = stoi( m_pConfig->getValue< std::string >( "Settings.General.HttpPort", "80" ) );
   g_log.info( "Starting REST server at port " + m_pConfig->getValue< std::string >( "Settings.General.HttpPort", "80" ) + "..." );

   server.resource["^/ZoneName/([0-9]+)$"]["GET"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      string number = request->path_match[1];
      auto it = g_exdData.m_zoneInfoMap.find( atoi( number.c_str() ) );
      std::string responseStr = "Not found!";
      if( it != g_exdData.m_zoneInfoMap.end() )
      {
         responseStr = it->second.zone_name + ", " + it->second.zone_str;
      }
      *response << "HTTP/1.1 200 OK\r\nContent-Length: " << responseStr.length() << "\r\n\r\n" << responseStr;
   };


   /* Create account */
   server.resource["^/sapphire-api/lobby/createAccount"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      std::string responseStr = "HTTP/1.1 400\r\n\r\n";
      try
      {

         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string pass = pt.get<string>( "pass" );
         std::string user = pt.get<string>( "username" );

         std::string sId;
         if( g_sapphireAPI.createAccount( user, pass, sId ) )
         {
            auto m_pConfig = new Core::XMLConfig();

            g_log.info( "Loading config settings_rest.xml" );

            if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
            {
               g_log.fatal( "Error loading config settings_rest.xml" );
               return 1;
            }

            std::string json_string = "{\"sId\":\"" + sId + "\", \"lobbyHost\":\"" + m_pConfig->getValue< std::string >( "Settings.General.LobbyHost" ) + "\", \"frontierHost\":\"" + m_pConfig->getValue< std::string >( "Settings.General.FrontierHost" ) + "\"}";
            *response << "HTTP/1.1 200 OK\r\n "
                      << "Content-Type: application/json\r\n"
                      << "Content-Length: " << json_string.length() << "\r\n\r\n"
                      << json_string;
         }
         else
            *response << "HTTP/1.1 400\r\n\r\n";
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }
      *response << "HTTP/1.1 200 OK\r\nContent-Length: " << responseStr.length() << "\r\nContent-Type: text/xml\r\n\r\n" << responseStr;
   };


   server.resource["^/sapphire-api/lobby/login"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string pass = pt.get<string>( "pass" );
         std::string user = pt.get<string>( "username" );

         std::string sId;

         if( g_sapphireAPI.login( user, pass, sId ) )
         {
            auto m_pConfig = new Core::XMLConfig();

            if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
            {
               g_log.fatal( "Error loading config settings_rest.xml" );
               return 1;
            }

            std::string json_string = "{\"sId\":\"" + sId + "\", \"lobbyHost\":\"" + m_pConfig->getValue< std::string >("Settings.General.LobbyHost") + "\", \"frontierHost\":\"" + m_pConfig->getValue< std::string >( "Settings.General.FrontierHost" ) + "\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
         else
            *response << "HTTP/1.1 400\r\n\r\n";

      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/deleteCharacter"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string sId = pt.get<string>( "sId" );
         std::string secret = pt.get<string>( "secret" );
         std::string name = pt.get<string>( "name" );

         int accountId = g_sapphireAPI.checkSession( sId );
         
         auto m_pConfig = new Core::XMLConfig();

         if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
         {
            g_log.fatal( "Error loading config settings_rest.xml" );
            return 1;
         }

         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
         else
         {
            g_sapphireAPI.deleteCharacter( name, accountId );
            std::string json_string = "{\"result\":\"success\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/createCharacter"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
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

         int result = g_sapphireAPI.checkSession( sId );

         if( result != -1 )
         {
            auto m_pConfig = new Core::XMLConfig();

            if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
            {
               g_log.fatal( "Error loading config settings_rest.xml" );
               return 1;
            }

            if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
               std::string json_string = "{\"result\":\"invalid_secret\"}";
               *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
            }
            else
            {
               int charId = g_sapphireAPI.createCharacter( result, name, finalJson );

               std::string json_string = "{\"result\":\"" + std::to_string( charId ) + "\"}";
               *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
            }
         }
         else
         {
            std::string json_string = "{\"result\":\"invalid\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/checkNameTaken"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string name = pt.get<string>( "name" );
         std::string secret = pt.get<string>( "secret" );

         auto m_pConfig = new Core::XMLConfig();

         if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
         {
            g_log.fatal( "Error loading config settings_rest.xml" );
            return 1;
         }

         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
         else
         {
            std::string json_string;
            if( !g_sapphireAPI.checkNameTaken( name ) )
               json_string = "{\"result\":\"false\"}";
            else
               json_string = "{\"result\":\"true\"}";

            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/checkSession"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string sId = pt.get<string>( "sId" );
         std::string secret = pt.get<string>( "secret" );

         int result = g_sapphireAPI.checkSession( sId );

         if( result != -1 )
         {
            auto m_pConfig = new Core::XMLConfig();

            if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
            {
               g_log.fatal( "Error loading config settings_rest.xml" );
               return 1;
            }

            if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
               std::string json_string = "{\"result\":\"invalid_secret\"}";
               *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
            }
            else
            {
               std::string json_string = "{\"result\":\"" + std::to_string( result ) + "\"}";
               *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
            }
         }
         else
         {
            std::string json_string = "{\"result\":\"invalid\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/getNextCharId"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string secret = pt.get<string>( "secret" );

         auto m_pConfig = new Core::XMLConfig();

         if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
         {
            g_log.fatal( "Error loading config settings_rest.xml" );
            return 1;
         }

         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
         else
         {
            std::string json_string = "{\"result\":\"" + std::to_string( g_sapphireAPI.getNextCharId() ) + "\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/getNextContentId"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string secret = pt.get<string>( "secret" );

         auto m_pConfig = new Core::XMLConfig();

         if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
         {
            g_log.fatal( "Error loading config settings_rest.xml" );
            return 1;
         }

         if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
            std::string json_string = "{\"result\":\"invalid_secret\"}";
            *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
         else
         {
            std::string json_string = "{\"result\":\"" + std::to_string( g_sapphireAPI.getNextContentId() ) + "\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^/sapphire-api/lobby/getCharacterList"]["POST"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         using namespace boost::property_tree;
         ptree pt;
         read_json( request->content, pt );

         std::string sId = pt.get<string>( "sId" );
         std::string secret = pt.get<string>( "secret" );

         int result = g_sapphireAPI.checkSession( sId );

         if( result != -1 )
         {
            auto m_pConfig = new Core::XMLConfig();

            if( !m_pConfig->loadConfig( "config/settings_rest.xml" ) )
            {
               g_log.fatal( "Error loading config settings_rest.xml" );
               return 1;
            }

            if( m_pConfig->getValue< std::string >( "Settings.General.ServerSecret" ) != secret ) {
               std::string json_string = "{\"result\":\"invalid_secret\"}";
               *response << "HTTP/1.1 403\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
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
               *response << "HTTP/1.1 200\r\nContent-Length: " << responseStr.length() << "\r\n\r\n" << responseStr;
            }
         }
         else
         {
            std::string json_string = "{\"result\":\"invalid\"}";
            *response << "HTTP/1.1 200\r\nContent-Length: " << json_string.length() << "\r\n\r\n" << json_string;
         }
      }
      catch( exception& e )
      {
         *response << "HTTP/1.1 500\r\n\r\n";
         g_log.error( e.what() );
      }

   };

   server.resource["^(/frontier-api/ffxivsupport/view/get_init)(.*)"]["GET"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
	   print_request_info( request );

	   try
	   {
		   auto web_root_path = boost::filesystem::canonical( "web" );
		   auto path = boost::filesystem::canonical( web_root_path / "news.xml" );
		   //Check if path is within web_root_path
		   if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
			   !equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
			   throw invalid_argument( "path must be within root path" );
		   if( !( boost::filesystem::exists( path ) && boost::filesystem::is_regular_file( path ) ) )
			   throw invalid_argument( "file does not exist" );

		   std::string cache_control, etag;

		   // Uncomment the following line to enable Cache-Control
		   // cache_control="Cache-Control: max-age=86400\r\n";

		   auto ifs = make_shared<ifstream>();
		   ifs->open( path.string(), ifstream::in | ios::binary | ios::ate );

		   if( *ifs )
		   {
			   auto length = ifs->tellg();
			   ifs->seekg( 0, ios::beg );

			   *response << "HTTP/1.1 200 OK\r\n" << cache_control << etag << "Content-Length: " << length << "\r\n\r\n";
			   default_resource_send( server, response, ifs );
		   }
		   else
			   throw invalid_argument( "could not read file" );
	   }
	   catch( exception& e )
	   {
		   *response << "HTTP/1.1 500\r\n\r\n";
		   g_log.error( e.what() );
	   }

   };

   server.resource["^(/frontier-api/ffxivsupport/information/get_headline_all)(.*)"]["GET"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
	   print_request_info( request );

	   try
	   {
		   auto web_root_path = boost::filesystem::canonical( "web" );
		   auto path = boost::filesystem::canonical( web_root_path / "headlines.xml" );
		   //Check if path is within web_root_path
		   if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
			   !equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
			   throw invalid_argument( "path must be within root path" );
		   if( !( boost::filesystem::exists( path ) && boost::filesystem::is_regular_file( path ) ) )
			   throw invalid_argument( "file does not exist" );

		   std::string cache_control, etag;

		   // Uncomment the following line to enable Cache-Control
		   // cache_control="Cache-Control: max-age=86400\r\n";

		   auto ifs = make_shared<ifstream>();
		   ifs->open( path.string(), ifstream::in | ios::binary | ios::ate );

		   if( *ifs )
		   {
			   auto length = ifs->tellg();
			   ifs->seekg( 0, ios::beg );

			   *response << "HTTP/1.1 200 OK\r\n" << cache_control << etag << "Content-Length: " << length << "\r\n\r\n";
			   default_resource_send( server, response, ifs );
		   }
		   else
			   throw invalid_argument( "could not read file" );
	   }
	   catch( exception& e )
	   {
		   *response << "HTTP/1.1 500\r\n\r\n";
		   g_log.error( e.what() );
	   }

   };

   //Default GET-example. If no other matches, this anonymous function will be called. 
   //Will respond with content in the web/-directory, and its subdirectories.
   //Default file: index.html
   //Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
   server.default_resource["GET"] = [&server]( shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request ) {
      print_request_info( request );

      try
      {
         auto web_root_path = boost::filesystem::canonical( "web" );
         auto path = boost::filesystem::canonical( web_root_path / request->path );
         //Check if path is within web_root_path
         if( distance( web_root_path.begin(), web_root_path.end() ) > distance( path.begin(), path.end() ) ||
             !equal( web_root_path.begin(), web_root_path.end(), path.begin() ) )
            throw invalid_argument( "path must be within root path" );
         if( boost::filesystem::is_directory( path ) )
            path /= "index.html";
         if( !( boost::filesystem::exists( path ) && boost::filesystem::is_regular_file( path ) ) )
            throw invalid_argument( "file does not exist" );

         std::string cache_control, etag;

         // Uncomment the following line to enable Cache-Control
         // cache_control="Cache-Control: max-age=86400\r\n";

         auto ifs = make_shared<ifstream>();
         ifs->open( path.string(), ifstream::in | ios::binary | ios::ate );

         if( *ifs )
         {
            auto length = ifs->tellg();
            ifs->seekg( 0, ios::beg );

            *response << "HTTP/1.1 200 OK\r\n" << cache_control << etag << "Content-Length: " << length << "\r\n\r\n";
            default_resource_send( server, response, ifs );
         }
         else
            throw invalid_argument( "could not read file" );
      }
      catch( const exception &e )
      {
         string content = "Path not found: " + request->path;
         *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
      }
   };

   thread server_thread( [&server]() {
      //Start server
      server.start();
   } );

   //Wait for server to start so that the client can connect
   this_thread::sleep_for( chrono::seconds( 1 ) );
   
   server_thread.join();
   g_log.info( "Started REST server at port " + std::to_string( server.config.port ) );

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
