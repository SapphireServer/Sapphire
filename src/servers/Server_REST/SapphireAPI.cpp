#include "SapphireAPI.h"
#include <src/servers/Server_Common/Crypt/base64.h>
#include "Session.h"
#include "PlayerMinimal.h"
#include <src/servers/Server_Common/Database/Database.h>
#include <time.h>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <sodium.h>

extern Core::Db::Database g_database;

Core::Network::SapphireAPI::SapphireAPI()
{
   
}

Core::Network::SapphireAPI::~SapphireAPI()
{
   
}

bool Core::Network::SapphireAPI::login( const std::string& username, const std::string& pass, std::string& sId )
{
   // FIXME: username is vuln to SQLi
   std::string query = "SELECT account_id, account_pass FROM accounts WHERE account_name = '" + username + "';";
   
   // check if a user with that name / password exists
   auto pQR = g_database.query( query );
   // found?
   if( !pQR )
      return false;

   // id is assumed to be verified with SQL
   // check password here
   auto accountPass = pQR->fetch()[1].getString();
   if ( crypto_pwhash_argon2i_str_verify( accountPass, pass.c_str(), pass.length() ) != 0 )
   {
      return false;
   }

   // user found, proceed
   int32_t accountId = pQR->fetch()[0].getUInt32();

   // session id string generation
   srand( ( uint32_t )time( NULL ) + 42 );
   uint8_t sid[58];

   for( int32_t i = 0; i < 56; i += 4 )
   {
      short number = 0x1111 + rand() % 0xFFFF;
      sprintf( ( char* )sid + i, "%04hx", number );
   }

   // create session for the new sessionid and store to sessionlist
   auto pSession = boost::make_shared< Session >();
   pSession->setAccountId( accountId );
   pSession->setSessionId( sid );

   //auto ip2 = boost::asio::ip::address::from_string( request->remote_endpoint_address );

   //pSession->setIP( ip2.to_v4().to_ulong() );

   std::stringstream ss;

   for( size_t i = 0; i < 56; i++ )
   {
      ss << std::hex << sid[i];
   }
   m_sessionMap[ ss.str() ] = pSession;
   sId = ss.str();
      
   return true;

}


bool Core::Network::SapphireAPI::insertSession( const uint32_t& accountId, std::string& sId )
{
   // create session for the new sessionid and store to sessionlist
   auto pSession = boost::make_shared< Session >();
   pSession->setAccountId( accountId );
   pSession->setSessionId( (uint8_t *)sId.c_str() );

   m_sessionMap[sId] = pSession;

   return true;

}

bool Core::Network::SapphireAPI::createAccount( const std::string& username, const std::string& pass, std::string& sId )
{
   // get account from login name
   auto pQR = g_database.query( "SELECT account_id FROM accounts WHERE account_name = '" + username + "';" );

   // if account was found
   if( pQR )
      return false;

   // we are clear and can create a new account
   // get the next free account id
   pQR = g_database.query( "SELECT MAX(account_id) FROM accounts;" );
   int32_t accountId = pQR->fetch()[0].getUInt32() + 1;

   // Hash password
   char hash[crypto_pwhash_STRBYTES];
   if ( crypto_pwhash_argon2i_str( hash, pass.c_str(), pass.length(), crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE ) != 0 )
   {
      // Failed to allocate a memory
      return false;
   }

   // store the account to the db
   g_database.execute( "INSERT INTO accounts (account_Id, account_name, account_pass, account_created) VALUE(%i, '%s', '%s', %i);",
                        accountId,
                        username.c_str(),
                        hash,
                        time( NULL ) );

   
   if( !login( username, pass, sId ) )
      return false;

   return true;
 
}

int Core::Network::SapphireAPI::createCharacter( const int& accountId, const std::string& name, const std::string& infoJson )
{
   Core::PlayerMinimal newPlayer;

   newPlayer.setAccountId( accountId );
   newPlayer.setId( getNextCharId() );
   newPlayer.setContentId( getNextContentId() );
   newPlayer.setName( name.c_str() );

   boost::property_tree::ptree pt;

   std::stringstream ss;
   ss << infoJson;

   boost::property_tree::read_json( ss, pt );

   const char *ptr = infoJson.c_str() + 50;

   std::string lookPart( ptr );
   int32_t pos = lookPart.find_first_of( "]" );
   if( pos != std::string::npos )
   {
      lookPart = lookPart.substr( 0, pos + 1 );
   }

   std::vector<int32_t> tmpVector;
   std::vector<int32_t> tmpVector2;

   BOOST_FOREACH( boost::property_tree::ptree::value_type &v, pt.get_child( "content" ) )
   {
      boost::property_tree::ptree subtree1 = v.second;
      BOOST_FOREACH( boost::property_tree::ptree::value_type &vs, subtree1 )
      {
         boost::property_tree::ptree subtree2 = vs.second;
         //std::cout << vs.second.data();
         tmpVector.push_back( std::stoi( vs.second.data() ) );
      }
      if( !v.second.data().empty() )
         tmpVector2.push_back( std::stoi( v.second.data() ) );
   }
   std::vector<int32_t>::iterator it = tmpVector.begin();
   for( int32_t i = 0; it != tmpVector.end(); ++it, i++ )
   {
      newPlayer.setLook( i, *it );
   }

   std::string rest = infoJson.substr( pos + 53 );

   newPlayer.setVoice( tmpVector2.at( 0 ) );
   newPlayer.setGuardianDeity( tmpVector2.at( 1 ) );
   newPlayer.setBirthDay( tmpVector2.at( 3 ), tmpVector2.at( 2 ) );
   newPlayer.setClass( tmpVector2.at( 4 ) );
   newPlayer.setTribe( tmpVector2.at( 5 ) );

   newPlayer.saveAsNew();

   return newPlayer.getAccountId();
}

void Core::Network::SapphireAPI::deleteCharacter( std::string name, uint32_t accountId )
{
   PlayerMinimal deletePlayer;
   auto charList = getCharList( accountId );
   for( uint32_t i = 0; i < charList.size(); i++ )
   {
      PlayerMinimal tmpPlayer = charList.at( i );

      if( tmpPlayer.getName() == name )
      {
         deletePlayer = tmpPlayer;
         break;
      }
   }

   int32_t id = deletePlayer.getId();

   g_database.execute( "DELETE FROM charabase WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM characlass WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charadetail WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charaglobalitem WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charainfoblacklist WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charainfofriendlist WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charainfolinkshell WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charainfosearch WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charaitemcrystal WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charaiteminventory WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charaitemgearset WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
   g_database.execute( "DELETE FROM charaquest WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
}

std::vector<Core::PlayerMinimal> Core::Network::SapphireAPI::getCharList( uint32_t accountId )
{

   std::vector<Core::PlayerMinimal> charList;

   boost::shared_ptr<Core::Db::QueryResult> pQR = g_database.query( "SELECT CharacterId, ContentId FROM charabase WHERE AccountId = " + std::to_string( accountId ) + ";" );

   if( !pQR )
   {
      // no chars found for the account
      return charList;
   }

   do
   {
      Core::PlayerMinimal player;

      Core::Db::Field *field = pQR->fetch();

      uint32_t charId = field[0].getInt32();

      player.load( charId );

      charList.push_back( player );

   } while( pQR->nextRow() );

   return charList;
}

bool Core::Network::SapphireAPI::checkNameTaken( std::string name )
{
   std::string query = "SELECT * FROM charabase WHERE Name = '" + g_database.escapeString( name ) + "';";

   auto pQR = g_database.query( query );

   if( !pQR )
      return false;
   else
      return true;
}

uint32_t Core::Network::SapphireAPI::getNextCharId()
{
   int32_t charId = 0;

   boost::shared_ptr<Core::Db::QueryResult> pQR = g_database.query( "SELECT MAX(CharacterId) FROM charabase" );

   if( !pQR )
   {
      return 0x00200001;
   }

   charId = pQR->fetch()[0].getUInt32() + 1;
   if( charId < 0x00200001 )
   {
      return 0x00200001;
   }

   return charId;
}

uint64_t Core::Network::SapphireAPI::getNextContentId()
{
   uint64_t contentId = 0;

   boost::shared_ptr<Core::Db::QueryResult> pQR = g_database.query( "SELECT MAX(ContentId) FROM charabase" );

   if( !pQR )
   {
      return 0x0040000001000001;
   }

   contentId = pQR->fetch()[0].getUInt64() + 1;
   if( contentId < 0x0040000001000001 )
   {
      return 0x0040000001000001;
   }


   return contentId;
}

int Core::Network::SapphireAPI::checkSession( const std::string& sId )
{
   auto it = m_sessionMap.find( sId );

   if( it == m_sessionMap.end() )
      return -1;

   return it->second->getAccountId();
}


bool Core::Network::SapphireAPI::removeSession( const std::string& sId )
{
   auto it = m_sessionMap.find( sId );

   if( it != m_sessionMap.end() )
      m_sessionMap.erase( sId );

   return true;
}