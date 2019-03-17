#include "SapphireAPI.h"
#include <Crypt/base64.h>
#include "Session.h"
#include "PlayerMinimal.h"
#include <time.h>

#include <sstream>

#include <nlohmann/json.hpp>

#include <Database/DatabaseDef.h>

bool Sapphire::Network::SapphireAPI::login( const std::string& username, const std::string& pass, std::string& sId )
{
  std::string query =
    "SELECT account_id FROM accounts WHERE account_name = '" + username + "' AND account_pass = '" + pass + "';";

  // check if a user with that name / password exists
  auto pQR = g_charaDb.query( query );
  // found?
  if( !pQR->next() )
    return false;

  // user found, proceed
  uint32_t accountId = pQR->getUInt( 1 );

  // session id string generation
  srand( ( uint32_t ) time( NULL ) + 42 );
  uint8_t sid[58];

  for( int32_t i = 0; i < 56; i += 4 )
  {
    short number = 0x1111 + rand() % 0xFFFF;
    sprintf( ( char* ) sid + i, "%04hx", number );
  }

  // create session for the new sessionid and store to sessionlist
  auto pSession = std::make_shared< Session >();
  pSession->setAccountId( accountId );
  pSession->setSessionId( sid );

  std::stringstream ss;

  for( size_t i = 0; i < 56; i++ )
  {
    ss << std::hex << sid[ i ];
  }
  m_sessionMap[ ss.str() ] = pSession;
  sId = ss.str();

  return true;

}


bool Sapphire::Network::SapphireAPI::insertSession( const uint32_t accountId, std::string& sId )
{
  // create session for the new sessionid and store to sessionlist
  auto pSession = std::make_shared< Session >();
  pSession->setAccountId( accountId );
  pSession->setSessionId( ( uint8_t* ) sId.c_str() );

  m_sessionMap[ sId ] = pSession;

  return true;

}

bool Sapphire::Network::SapphireAPI::createAccount( const std::string& username, const std::string& pass, std::string& sId )
{
  // get account from login name
  auto pQR = g_charaDb.query( "SELECT account_id FROM accounts WHERE account_name = '" + username + "';" );
  // found?
  if( pQR->next() )
    return false;

  // we are clear and can create a new account
  // get the next free account id
  pQR = g_charaDb.query( "SELECT MAX(account_id) FROM accounts;" );
  if( !pQR->next() )
    return false;
  uint32_t accountId = pQR->getUInt( 1 ) + 1;

  // store the account to the db
  g_charaDb.directExecute( "INSERT INTO accounts (account_Id, account_name, account_pass, account_created) VALUE( " +
                           std::to_string( accountId ) + ", '" +
                           username + "', '" +
                           pass + "', " +
                           std::to_string( time( nullptr ) ) + ");" );


  if( !login( username, pass, sId ) )
    return false;

  return true;

}

int Sapphire::Network::SapphireAPI::createCharacter( const uint32_t accountId, const std::string& name,
                                                     const std::string& infoJson,
                                                     const uint32_t gmRank )
{
  Sapphire::PlayerMinimal newPlayer;

  newPlayer.setAccountId( accountId );
  newPlayer.setId( getNextCharId() );
  newPlayer.setContentId( getNextContentId() );
  newPlayer.setName( name.c_str() );

  auto json = nlohmann::json::parse( infoJson );

  const char* ptr = infoJson.c_str() + 50;

  std::string lookPart( ptr );
  int32_t pos = lookPart.find_first_of( "]" );
  if( pos != std::string::npos )
  {
    lookPart = lookPart.substr( 0, pos + 1 );
  }

  std::vector< int32_t > tmpVector;
  std::vector< int32_t > tmpVector2;

  for( auto& v : json["content"] )
  {
    if( v.is_array() )
    {
      for( auto& vs : v )
      {
        tmpVector.push_back( std::stoi( std::string( vs ) ) );
      }
    }

    if( !v.empty() && !v.is_array() )
      tmpVector2.push_back( std::stoi( std::string( v ) ) );
  }

  // leaving this in for now for reference
  // BOOST_FOREACH( boost::property_tree::ptree::value_type& v, pt.get_child( "content" ) )
  //       {
  //         boost::property_tree::ptree subtree1 = v.second;
  //         BOOST_FOREACH( boost::property_tree::ptree::value_type& vs, subtree1 )
  //               {
  //                 boost::property_tree::ptree subtree2 = vs.second;
  //                 //std::cout << vs.second.data();
  //                 tmpVector.push_back( std::stoi( vs.second.data() ) );
  //               }
  //         if( !v.second.data().empty() )
  //           tmpVector2.push_back( std::stoi( v.second.data() ) );
  //       }
  
  std::vector< int32_t >::iterator it = tmpVector.begin();
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
  newPlayer.setGmRank( gmRank );

  newPlayer.saveAsNew();

  return newPlayer.getAccountId();
}

void Sapphire::Network::SapphireAPI::deleteCharacter( std::string name, const uint32_t accountId )
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

  g_charaDb.execute( "DELETE FROM charainfo WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM characlass WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charaglobalitem WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charainfoblacklist WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charainfofriendlist WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charainfolinkshell WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charainfosearch WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charaitemcrystal WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charaiteminventory WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charaitemgearset WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
  g_charaDb.execute( "DELETE FROM charaquest WHERE CharacterId LIKE '" + std::to_string( id ) + "';" );
}

std::vector< Sapphire::PlayerMinimal > Sapphire::Network::SapphireAPI::getCharList( uint32_t accountId )
{

  std::vector< Sapphire::PlayerMinimal > charList;

  auto pQR = g_charaDb.query(
    "SELECT CharacterId, ContentId FROM charainfo WHERE AccountId = " + std::to_string( accountId ) + ";" );

  while( pQR->next() )
  {
    Sapphire::PlayerMinimal player;

    uint32_t charId = pQR->getUInt( 1 );

    player.load( charId );

    charList.push_back( player );
  }
  return charList;
}

bool Sapphire::Network::SapphireAPI::checkNameTaken( std::string name )
{

  g_charaDb.escapeString( name );
  std::string query = "SELECT * FROM charainfo WHERE Name = '" + name + "';";

  auto pQR = g_charaDb.query( query );

  if( !pQR->next() )
    return false;
  else
    return true;
}

uint32_t Sapphire::Network::SapphireAPI::getNextCharId()
{
  uint32_t charId = 0;

  auto pQR = g_charaDb.query( "SELECT MAX(CharacterId) FROM charainfo" );

  if( !pQR->next() )
    return 0x00200001;

  charId = pQR->getUInt( 1 ) + 1;
  if( charId < 0x00200001 )
    return 0x00200001;

  return charId;
}

uint64_t Sapphire::Network::SapphireAPI::getNextContentId()
{
  uint64_t contentId = 0;

  auto pQR = g_charaDb.query( "SELECT MAX(ContentId) FROM charainfo" );

  if( !pQR->next() )
    return 0x0040000001000001;

  contentId = pQR->getUInt64( 1 ) + 1;
  if( contentId < 0x0040000001000001 )
    return 0x0040000001000001;

  return contentId;
}

int Sapphire::Network::SapphireAPI::checkSession( const std::string& sId )
{
  auto it = m_sessionMap.find( sId );

  if( it == m_sessionMap.end() )
    return -1;

  return it->second->getAccountId();
}


bool Sapphire::Network::SapphireAPI::removeSession( const std::string& sId )
{
  auto it = m_sessionMap.find( sId );

  if( it != m_sessionMap.end() )
    m_sessionMap.erase( sId );

  return true;
}
