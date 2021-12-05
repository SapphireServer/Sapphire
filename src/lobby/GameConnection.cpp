#include "GameConnection.h"

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Util/Util.h>
#include <Logging/Logger.h>
#include <Network/GamePacket.h>
#include <Network/PacketDef/Lobby/ServerLobbyDef.h>
#include <Network/PacketDef/Lobby/ClientLobbyDef.h>
#include <Network/GamePacketParser.h>
#include <Crypt/md5.h>
#include <Crypt/blowfish.h>
#include <Config/ConfigMgr.h>

#include <utility>

#include <utility>

#include "ServerLobby.h"
#include "RestConnector.h"
#include "LobbySession.h"

#include "Forwards.h"

using namespace Sapphire;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::LobbyPackets;
using namespace Sapphire::Network::Packets::LobbyPackets::Server;


extern Lobby::ServerLobby g_serverLobby;
extern Lobby::RestConnector g_restConnector;

Lobby::GameConnection::GameConnection( Sapphire::Network::HivePtr pHive,
                                       Sapphire::Network::AcceptorPtr pAcceptor ) :
  Sapphire::Network::Connection( std::move( pHive ) ),
  m_pAcceptor( std::move( pAcceptor ) ),
  m_bEncryptionInitialized( false )
{
}

Lobby::GameConnection::~GameConnection()
{

}


// overwrite the parents onConnect for our game socket needs
void Lobby::GameConnection::onAccept( const std::string& host, uint16_t port )
{
  auto connection = make_GameConnection( m_hive, m_pAcceptor );
  m_pAcceptor->accept( connection );

  Logger::info( "Connect from {0}:{1}", m_socket.remote_endpoint().address().to_string(), m_socket.remote_endpoint().port() );
}


void Lobby::GameConnection::onDisconnect()
{
  Logger::debug( "DISCONNECT" );
}

void Lobby::GameConnection::onRecv( std::vector< uint8_t >& buffer )
{
  m_packets.insert( std::end( m_packets ), std::begin( buffer ), std::end( buffer ) );
  // This is assumed packet always start with valid FFXIVARR_PACKET_HEADER for now.
  FFXIVARR_PACKET_HEADER packetHeader{};
  const auto headerResult = getHeader( m_packets, 0, packetHeader );

  if( headerResult == Incomplete )
    return;

  if( headerResult == Malformed )
  {
    Logger::info( "Dropping connection due to malformed packet header." );
    disconnect();
    return;
  }

  // Dissect packet list
  std::vector< FFXIVARR_PACKET_RAW > packetList;
  const auto packetResult = getPackets( m_packets, sizeof( struct FFXIVARR_PACKET_HEADER ),
                                        packetHeader, packetList );

  if( packetResult == Incomplete )
    return;

  if( packetResult == Malformed )
  {
    Logger::info( "Dropping connection due to malformed packets." );
    disconnect();
    return;
  }

  // Handle it
  handlePackets( packetHeader, packetList );
  m_packets.clear();

}

void Lobby::GameConnection::onError( const asio::error_code& error )
{
  Logger::info( "GameConnection closed: {0}", error.message() );
}

void
Lobby::GameConnection::sendError( uint32_t requestNumber, uint32_t clientTimeValue,
                                  uint32_t errorCode, uint16_t messageId, uint32_t tmpId )
{
  auto errorPacket = makeLobbyPacket< FFXIVIpcNackReply >( tmpId );
  errorPacket->data().requestNumber = requestNumber;
  errorPacket->data().clientTimeValue = clientTimeValue;
  errorPacket->data().errorCode = errorCode;
  errorPacket->data().errorMessageNo = messageId;

  LobbyPacketContainer pRP( m_encKey );
  pRP.addPacket( errorPacket );
  sendPacket( pRP );
}

void Lobby::GameConnection::serviceLogin( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  auto serviceLoginPacket = LobbyChannelPacket< Client::FFXIVIpcServiceLogin >( packet );
  uint32_t requestNumber = serviceLoginPacket.data().requestNumber;
  uint32_t clientTimeValue = serviceLoginPacket.data().clientTimeValue;

  //Logger::info( "requestNumber [{0}]", requestNumber );
  Logger::info( "[accountId#{0}] ReqCharList", m_pSession->getAccountID() );
  LobbyPacketContainer pRP( m_encKey );

  auto serverListPacket = makeLobbyPacket< FFXIVIpcDistWorldInfo >( tmpId );
  serverListPacket->data().requestNumber = requestNumber;
  serverListPacket->data().clientTimeValue = clientTimeValue;
  serverListPacket->data().listIndex = 0;
  serverListPacket->data().endOfList = 1;
  serverListPacket->data().count = 1;
  serverListPacket->data().worldArray[ 0 ].worldId = g_serverLobby.getConfig().global.general.worldID;
  serverListPacket->data().worldArray[ 0 ].worldIndex = 0;
  strcpy( serverListPacket->data().worldArray[ 0 ].displayName, g_serverLobby.getConfig().worldName.c_str() );
  strcpy( serverListPacket->data().worldArray[ 0 ].worldSetName, g_serverLobby.getConfig().worldName.c_str() );
  pRP.addPacket( serverListPacket );

  auto retainerListPacket = makeLobbyPacket< FFXIVIpcDistRetainerInfo >( tmpId );
  retainerListPacket->data().endOfList = 1;
  pRP.addPacket( retainerListPacket );

  sendPacket( pRP );

  auto charList = g_restConnector.getCharList( m_pSession->getSessionId() );

  int32_t charIndex = -1;
  uint8_t usedCharaIndex = 0;

  for( uint8_t i = 0; i < 4; i++ )
  {
    auto charListPacket = makeLobbyPacket< FFXIVIpcServiceLoginReply >( tmpId );
    charListPacket->data().requestNumber = requestNumber;
    charListPacket->data().clientTimeValue = clientTimeValue;
    charListPacket->data().listIndex = i * 2;
    charListPacket->data().count = 2;

    for( auto& j : charListPacket->data().chrArray )
    {
      CharacterInfo details{};
      memset( &details, 0, sizeof( CharacterInfo ) );
      details.chrIndex = ++charIndex;

      if( charList.empty() || charIndex >= charList.size() )
        continue;

      usedCharaIndex = charIndex;

      auto& charEntry = charList[ charIndex ];
      details.characterId = std::get< 2 >( charEntry );
      details.playerId = std::get< 1 >( charEntry );
      details.worldId = g_serverLobby.getConfig().global.general.worldID;

      strcpy( details.graphicData, std::get< 3 >( charEntry ).c_str() );
      strcpy( details.chrName, std::get< 0 >( charEntry ).c_str() );
      strcpy( details.worldSetName, g_serverLobby.getConfig().worldName.c_str() );

      /*Logger::debug( "[{0}] {1} - {2} - {3} - {4} - {5}",
                     charIndex,
                     details.chrIndex,
                     std::get< 0 >( charEntry ),
                     std::get< 1 >( charEntry ),
                     std::get< 2 >( charEntry ),
                     std::get< 3 >( charEntry ) );*/

      j = details;
    }

    if( i == 3 )
    {
      charListPacket->data().maxCreateCharacter = Common::MAX_CREATE_CHARACTER;
      charListPacket->data().maxCharacterList = Common::MAX_CHARACTER_LIST;
      charListPacket->data().entitledExpansion = Common::CURRENT_EXPANSION_ID;
      charListPacket->data().endOfList = 1;
    }

    m_pSession->setCharaIndex( usedCharaIndex );

    LobbyPacketContainer pRP1( m_encKey );
    pRP1.addPacket( charListPacket );
    sendPacket( pRP1 );
  }
}

void Lobby::GameConnection::gameLogin( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  auto serviceLoginPacket = LobbyChannelPacket< Client::FFXIVIpcGameLogin >( packet );
  uint32_t requestNumber = serviceLoginPacket.data().requestNumber;
  uint32_t clientTimeValue = serviceLoginPacket.data().clientTimeValue;

  //Logger::info( "requestNumber [{0}]", requestNumber );

  uint64_t characterId = serviceLoginPacket.data().characterId;
  uint64_t playerId = serviceLoginPacket.data().playerId;
  uint8_t characterIndex = serviceLoginPacket.data().characterIndex;
  uint8_t operation = serviceLoginPacket.data().operation;

  Logger::info( "[accountId#{0}] GameLogin: characterId#{1} playerId#{2}", m_pSession->getAccountID(), characterId, playerId );

  uint64_t ticketId = -1;
  std::string logInCharName;
  auto charList = g_restConnector.getCharList( m_pSession->getSessionId() );

  for( auto& listEntry : charList )
  {
    uint64_t thisContentId = std::get< 2 >( listEntry );

    if( thisContentId == characterId )
    {
      ticketId = std::get< 1 >( listEntry );
      logInCharName = std::get< 0 >( listEntry );
      break;
    }
  }

  if( ticketId == -1 )
    return;

  Logger::info( "[accountId#{0}] Logging in as {1} ticketId ({2})", m_pSession->getAccountID(), logInCharName, ticketId );

  LobbyPacketContainer pRP( m_encKey );

  auto enterWorldPacket = makeLobbyPacket< FFXIVIpcGameLoginReply >( tmpId );
  enterWorldPacket->data().characterId = characterId;
  enterWorldPacket->data().characterIndex = characterIndex;
  enterWorldPacket->data().requestNumber = requestNumber;
  enterWorldPacket->data().clientTimeValue = clientTimeValue;
  strcpy( enterWorldPacket->data().frontendHost, g_serverLobby.getConfig().global.network.zoneHost.c_str() );
  enterWorldPacket->data().frontendPort = g_serverLobby.getConfig().global.network.zonePort;
  enterWorldPacket->data().ticketId = static_cast< uint32_t >( ticketId );
  enterWorldPacket->data().operation = operation;
  enterWorldPacket->data().worldId = g_serverLobby.getConfig().global.general.worldID;
  memcpy( enterWorldPacket->data().ticketData, m_pSession->getSessionId(), sizeof( enterWorldPacket->data().ticketData ) );
  pRP.addPacket( enterWorldPacket );
  sendPacket( pRP );
}

bool Lobby::GameConnection::login( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  auto loginPacket = LobbyChannelPacket< Client::FFXIVIpcLogin >( packet );
  LobbySessionPtr pSession = g_serverLobby.getSession( loginPacket.data().sessionId );

  Logger::info( "Login request from session: {0}", loginPacket.data().sessionId );
  Logger::info( "Client version: {0}", loginPacket.data().version );

  if( g_serverLobby.getConfig().allowNoSessionConnect && !pSession )
  {
    auto session = make_LobbySession();
    session->setAccountID( 0 );
    session->setSessionId( loginPacket.data().sessionId );
    pSession = session;
    Logger::info( "Allowed connection with no session: {0}", loginPacket.data().sessionId );
  }

  if( pSession )
  {
    Logger::info( "Found session linked to accountId: {0}", pSession->getAccountID() );
    m_pSession = pSession;

    auto serviceIdInfoPacket = makeLobbyPacket< FFXIVIpcLoginReply >( tmpId );
    serviceIdInfoPacket->data().activeAccountCount = 1;
    serviceIdInfoPacket->data().regionCode = 3;
    serviceIdInfoPacket->data().optionParam = 0x99;
    serviceIdInfoPacket->data().accountArray[ 0 ].accountIndex = 1;
    serviceIdInfoPacket->data().accountArray[ 0 ].accountId = 0x002E4A2B;
    sprintf( serviceIdInfoPacket->data().accountArray[ 0 ].accountName, "%s", Common::SERVICE_ACCOUNT_DEFAULT_NAME.c_str() );

    LobbyPacketContainer pRP( m_encKey );
    pRP.addPacket( serviceIdInfoPacket );
    sendPacket( pRP );
  }
  else
  {
    Logger::info( "Could not retrieve session: {0}", loginPacket.data().sessionId );
    sendError( 1, 0, 5006, 13001, tmpId );

    return true;
  }
  return false;
}

bool Lobby::GameConnection::charaMake( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  auto charaMakePacket = LobbyChannelPacket< Client::FFXIVIpcCharaMake >( packet );

  uint32_t requestNumber = charaMakePacket.data().requestNumber;
  uint32_t clientTimeValue = charaMakePacket.data().clientTimeValue;
  Client::CharacterOperation characterOperation = charaMakePacket.data().operation;
  //Logger::info( "requestNumber [{0}]", requestNumber );
  Logger::info( "Character Operation [{0}]", characterOperation );

  uint64_t characterId = charaMakePacket.data().characterId;
  uint64_t playerId = charaMakePacket.data().playerId;
  uint8_t characterIndex = charaMakePacket.data().characterIndex;

  Logger::info( "[accountId#{0}] ReqCharCreate", m_pSession->getAccountID() );

  if( characterOperation == Client::CharacterOperation::CHARAOPE_RESERVENAME ) //Character creation name check
  {
    std::string name = std::string( charaMakePacket.data().chracterName );

    Logger::info( "[accountId#{0}] Character Operation CHARAOPE_RESERVENAME: {1}", m_pSession->getAccountID(), name );

    LobbyPacketContainer pRP( m_encKey );

    m_pSession->newCharName = name;

    if( g_restConnector.checkNameTaken( m_pSession->newCharName ) )
    {
      sendError( requestNumber, clientTimeValue, 3074, 13004, tmpId );
      return true;
    }
    uint64_t newContentId = g_restConnector.getNextContentId();

    auto charCreatePacket = makeLobbyPacket< FFXIVIpcCharaMakeReply >( tmpId );
    charCreatePacket->data().chrArray[0].characterId = newContentId;
    charCreatePacket->data().chrArray[0].chrIndex = m_pSession->getCharaIndex() + 1; 
    charCreatePacket->data().chrArray[0].worldId = g_serverLobby.getConfig().global.general.worldID;
    strcpy( charCreatePacket->data().chrArray[0].chrName, m_pSession->newCharName.c_str() );
    strcpy( charCreatePacket->data().chrArray[0].worldSetName, g_serverLobby.getConfig().worldName.c_str() );
    charCreatePacket->data().optionParam = Client::CharacterOperation::CHARAOPE_RESERVENAME;
    charCreatePacket->data().requestNumber = requestNumber;
    charCreatePacket->data().clientTimeValue = clientTimeValue;
    charCreatePacket->data().endOfList = 1;
    charCreatePacket->data().count = 1;
    pRP.addPacket( charCreatePacket );
    sendPacket( pRP );
  }
  else if( characterOperation == Client::CharacterOperation::CHARAOPE_MAKECHARA ) //Character creation finalize
  {
    std::string charDetails( charaMakePacket.data().charaMakeData );
    Logger::info( "[accountId#{0}] Character Operation CHARAOPE_MAKECHARA: {1}", m_pSession->getAccountID(), charDetails );

    if( g_restConnector.createCharacter( m_pSession->getSessionId(), m_pSession->newCharName, charDetails ) !=
        -1 )
    {
      LobbyPacketContainer pRP( m_encKey );

      uint8_t newCharaIndex = m_pSession->getCharaIndex() + 1;

      uint32_t newId = g_restConnector.getNextCharId();
      m_pSession->setCharaIndex( newCharaIndex );

      Logger::info( "[accountId#{0}] index {1} charaterId {2}", m_pSession->getAccountID(), newCharaIndex, characterId );
      Logger::info( "[accountId#{0}] index {1} playerId {2}", m_pSession->getAccountID(), newCharaIndex, newId );

      auto charCreatePacket = makeLobbyPacket< FFXIVIpcCharaMakeReply >( tmpId );
      charCreatePacket->data().chrArray[0].playerId = characterId;
      charCreatePacket->data().chrArray[0].chrIndex = newCharaIndex;
      charCreatePacket->data().chrArray[0].characterId = characterId;
      charCreatePacket->data().chrArray[0].worldId = g_serverLobby.getConfig().global.general.worldID;
      strcpy( charCreatePacket->data().chrArray[0].chrName, m_pSession->newCharName.c_str() );
      strcpy( charCreatePacket->data().chrArray[0].worldSetName, g_serverLobby.getConfig().worldName.c_str() );
      charCreatePacket->data().optionParam = Client::CharacterOperation::CHARAOPE_MAKECHARA;
      charCreatePacket->data().requestNumber = requestNumber;
      charCreatePacket->data().clientTimeValue = clientTimeValue;
      charCreatePacket->data().endOfList = 1;
      charCreatePacket->data().count = 1;
      pRP.addPacket( charCreatePacket );
      sendPacket( pRP );
    }
    else
    {
      sendError( requestNumber, clientTimeValue, 5006, 13001, tmpId );
    }
  }
  else if( characterOperation == Client::CharacterOperation::CHARAOPE_DELETECHARA ) //Character delete
  {
    std::string name = std::string( charaMakePacket.data().chracterName );
    Logger::info( "[accountId#{0}] Character Operation CHARAOPE_DELETECHARA: {1}", m_pSession->getAccountID(), name );


    if( g_restConnector.deleteCharacter( m_pSession->getSessionId(), name ) )
    {

      auto charCreatePacket = makeLobbyPacket< FFXIVIpcCharaMakeReply >( tmpId );
      strcpy( charCreatePacket->data().chrArray[0].chrName, name.c_str() );
      strcpy( charCreatePacket->data().chrArray[0].worldSetName, g_serverLobby.getConfig().worldName.c_str() );
      charCreatePacket->data().optionParam = Client::CharacterOperation::CHARAOPE_DELETECHARA;
      charCreatePacket->data().requestNumber = requestNumber;
      charCreatePacket->data().clientTimeValue = clientTimeValue;
      charCreatePacket->data().endOfList = 1;
      charCreatePacket->data().count = 1;

      LobbyPacketContainer pRP( m_encKey );
      pRP.addPacket( charCreatePacket );
      sendPacket( pRP );
    }
    else
    {
      sendError( requestNumber, clientTimeValue, 5006, 13001, tmpId );
    }
  }
  else
  {
    Logger::error( "[accountId#{0}] Unhandled Character Operation: {1}", m_pSession->getAccountID(), characterOperation );
  }
  return false;
}

void Lobby::GameConnection::debugLogin( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  auto debugLoginPacket = LobbyChannelPacket< Client::FFXIVIpcDebugLogin >( packet );

  uint32_t requestNumber = debugLoginPacket.data().requestNumber;

  //Logger::info( "requestNumber [{0}]", requestNumber );

  Logger::info( "[accountId#{0}] {1} DebugLogin", m_pSession->getAccountID(), debugLoginPacket.data().ticketNumber );

  auto debugLoginReplPacket = makeLobbyPacket< FFXIVIpcDebugLoginRepl >( tmpId );

  debugLoginReplPacket->data().requestNumber = requestNumber;
  //TODO: Why is the client sending the wrong ticket number? Find out why (for now just set to 1 so it grabs the one out of the config)
  debugLoginReplPacket->data().ticketNumber = 1;
  debugLoginReplPacket->data().frontendPort = g_serverLobby.getConfig().global.network.zonePort;
  strcpy( debugLoginReplPacket->data().frontendHost, g_serverLobby.getConfig().global.network.zoneHost.c_str() );
  strcpy( debugLoginReplPacket->data().worldSetName, g_serverLobby.getConfig().worldName.c_str() );

  LobbyPacketContainer pRP( m_encKey );
  pRP.addPacket( debugLoginReplPacket );
  sendPacket( pRP );
}

void Lobby::GameConnection::debugLogin2( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  auto debugLoginPacket = LobbyChannelPacket< Client::FFXIVIpcDebugLogin2 >( packet );

  uint32_t requestNumber = debugLoginPacket.data().requestNumber;

  //Logger::info( "requestNumber [{0}]", requestNumber );

  Logger::info( "[accountId#{0}] {1} DebugLogin2", m_pSession->getAccountID(), debugLoginPacket.data().ticketNumber );

  auto debugLoginReplPacket = makeLobbyPacket< FFXIVIpcDebugLoginRepl >(tmpId);

  debugLoginReplPacket->data().requestNumber = requestNumber;
  //TODO: Why is the client sending the wrong ticket number? Find out why (for now just set to 1 so it grabs the one out of the config)
  debugLoginReplPacket->data().ticketNumber = 1;
  debugLoginReplPacket->data().frontendPort = g_serverLobby.getConfig().global.network.zonePort;
  strcpy( debugLoginReplPacket->data().frontendHost, g_serverLobby.getConfig().global.network.zoneHost.c_str() );
  strcpy( debugLoginReplPacket->data().worldSetName, g_serverLobby.getConfig().worldName.c_str() );

  LobbyPacketContainer pRP( m_encKey );
  pRP.addPacket( debugLoginReplPacket );
  sendPacket( pRP );
}

void Lobby::GameConnection::handleGamePacket( Network::Packets::FFXIVARR_PACKET_RAW& packet )
{
  uint32_t tmpId = packet.segHdr.target_actor;

  uint32_t accountId = 0;
  if( m_pSession )
    accountId = m_pSession->getAccountID();

  Logger::info( "[accountId#{0}] OpCode {1}", accountId, *reinterpret_cast< uint16_t* >( &packet.data[ 2 ] ) );
  
  switch( *reinterpret_cast< uint16_t* >( &packet.data[ 2 ] ) )
  {
    case LoginEx:
    {
      // todo: validate client version based on sha1 or gamever/bootver
      login( packet, tmpId );
    }
    break;

    case ServiceLogin:
    {
      serviceLogin( packet, tmpId );
    }
    break;

    case GameLogin:
    {
      gameLogin( packet, tmpId );
    }
    break;

    case CharaMake:
    {
      charaMake( packet, tmpId );
    }
    break;

    case DebugLogin:
    {
      debugLogin( packet, tmpId );
    }
    break;

    case DebugLogin2:
    {
      debugLogin2( packet, tmpId );
    }
    break;
  }
}

void Lobby::GameConnection::sendPacket( LobbyPacketContainer& pLpc )
{
  uint16_t size = pLpc.getSize();
  uint8_t* dataPtr = pLpc.getRawData( false );
  std::vector< uint8_t > sendBuffer;
  sendBuffer.assign( dataPtr, dataPtr + size );
  send( sendBuffer );
}

void Lobby::GameConnection::sendPackets( Network::Packets::PacketContainer* pPacket )
{
  std::vector< uint8_t > sendBuffer;

  pPacket->fillSendBuffer( sendBuffer );
  send( sendBuffer );
}

void Lobby::GameConnection::sendSinglePacket( FFXIVPacketBasePtr pPacket )
{
  PacketContainer pRP = PacketContainer();
  pRP.addPacket( std::move( pPacket ) );
  sendPackets( &pRP );
}

void Lobby::GameConnection::generateEncryptionKey( uint32_t key, const std::string& keyPhrase )
{
  std::memset( m_baseKey.rawKey, 0, sizeof( m_baseKey ) );
  m_baseKey.magic = 0x12345678;
  m_baseKey.key = key;
  m_baseKey.version = Common::FFXIV_ENC_VERSION;
  std::memcpy( m_baseKey.keyPhrase, keyPhrase.c_str(), keyPhrase.size() );
  Common::Util::md5( m_baseKey.rawKey, m_encKey, sizeof( m_baseKey ) );
}

void Lobby::GameConnection::handlePackets( const Network::Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                                           const std::vector< Network::Packets::FFXIVARR_PACKET_RAW >& packetData )
{
  for( auto inPacket : packetData )
  {

    if( m_bEncryptionInitialized && inPacket.segHdr.type == 3 )
    {
      BlowFish blowfish;
      blowfish.initialize( m_encKey, 0x10 );
      blowfish.Decode( ( uint8_t* ) ( &inPacket.data[ 0 ] ), ( uint8_t* ) ( &inPacket.data[ 0 ] ),
                       ( inPacket.data.size() ) - 0x10 );
    }

    switch( inPacket.segHdr.type )
    {
      case SEGMENTTYPE_ENCRYPTIONINIT: // Encryption init
      {
        std::string key_phrase( reinterpret_cast< char* >( &inPacket.data[ 36 ] ) );
        generateEncryptionKey( *reinterpret_cast< uint32_t* >( &inPacket.data[ 100 ] ), key_phrase );
        m_bEncryptionInitialized = true;

        auto pe1 = std::make_shared< FFXIVRawPacket >( 0x0A, 0x290, 0, 0 );
        *reinterpret_cast< uint32_t* >( &pe1->data()[ 0 ] ) = 0xE0003C2A;

        BlowFish blowfish;
        blowfish.initialize( m_encKey, 0x10 );
        blowfish.Encode( &pe1->data()[ 0 ], &pe1->data()[ 0 ], 0x280 );

        sendSinglePacket( pe1 );
        break;
      }


      case SEGMENTTYPE_IPC: // game packet
      {
        uint32_t accountId = 0;
        if( m_pSession )
          accountId = m_pSession->getAccountID();
        Logger::info( "[accountId#{0}] GamePacket {1}", accountId, inPacket.segHdr.type );
        handleGamePacket( inPacket );
        break;
      }
      case SEGMENTTYPE_KEEPALIVE: // keep alive
      {
        uint32_t id = *reinterpret_cast< uint32_t* >( &inPacket.data[ 0 ] );
        uint32_t timeStamp = *reinterpret_cast< uint32_t* >( &inPacket.data[ 4 ] );

        auto pe4 = std::make_shared< FFXIVRawPacket >( 0x08, 0x18, 0, 0 );
        *( unsigned int* ) ( &pe4->data()[ 0 ] ) = id;
        *( unsigned int* ) ( &pe4->data()[ 4 ] ) = timeStamp;
        sendSinglePacket( pe4 );

        break;
      }
      case 8:
      {
        break;
      }
    }
  }
}
