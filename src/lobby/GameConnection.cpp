#include "GameConnection.h"

#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Util/Util.h>
#include <Logging/Logger.h>
#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Lobby/ServerLobbyDef.h>
#include <Network/GamePacketParser.h>
#include <Crypt/md5.h>
#include <Crypt/blowfish.h>
#include <Config/ConfigMgr.h>

#include "ServerLobby.h"
#include "RestConnector.h"
#include "LobbySession.h"

extern Sapphire::Logger g_log;
extern Sapphire::ServerLobby g_serverLobby;
extern Sapphire::Network::RestConnector g_restConnector;

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::Network::GameConnection::GameConnection( Sapphire::Network::HivePtr pHive,
                                                   Sapphire::Network::AcceptorPtr pAcceptor,
                                                   FrameworkPtr pFw ) :
  Connection( pHive, pFw ),
  m_pAcceptor( pAcceptor ),
  m_bEncryptionInitialized( false )
{
}

Sapphire::Network::GameConnection::~GameConnection()
{

}


// overwrite the parents onConnect for our game socket needs
void Sapphire::Network::GameConnection::OnAccept( const std::string& host, uint16_t port )
{
  auto connection = make_GameConnection( m_hive, m_pAcceptor, m_pFw );
  m_pAcceptor->Accept( connection );

  g_log.info( "Connect from " + m_socket.remote_endpoint().address().to_string() );
}


void Sapphire::Network::GameConnection::OnDisconnect()
{
  g_log.debug( "DISCONNECT" );
}

void Sapphire::Network::GameConnection::OnRecv( std::vector< uint8_t >& buffer )
{
  Packets::FFXIVARR_PACKET_HEADER packetHeader;
  const auto headerResult = Packets::getHeader( buffer, 0, packetHeader );

  if( headerResult == Incomplete )
  {
    g_log.info( "Dropping connection due to incomplete packet header." );
    g_log.info( "FIXME: Packet message bounary is not implemented." );
    Disconnect();
    return;
  }

  if( headerResult == Malformed )
  {
    g_log.info( "Dropping connection due to malformed packet header." );
    Disconnect();
    return;
  }

  // Dissect packet list
  std::vector< Packets::FFXIVARR_PACKET_RAW > packetList;
  const auto packetResult = Packets::getPackets( buffer, sizeof( struct FFXIVARR_PACKET_HEADER ),
                                                 packetHeader, packetList );

  if( packetResult == Incomplete )
  {
    g_log.info( "Dropping connection due to incomplete packets." );
    g_log.info( "FIXME: Packet message bounary is not implemented." );
    Disconnect();
    return;
  }

  if( packetResult == Malformed )
  {
    g_log.info( "Dropping connection due to malformed packets." );
    Disconnect();
    return;
  }

  // Handle it
  handlePackets( packetHeader, packetList );

}

void Sapphire::Network::GameConnection::OnError( const asio::error_code& error )
{
  g_log.info( "GameConnection closed: " + error.message() );
}

void
Sapphire::Network::GameConnection::sendError( uint64_t sequence, uint32_t errorcode, uint16_t messageId, uint32_t tmpId )
{
  auto errorPacket = makeLobbyPacket< FFXIVIpcLobbyError >( tmpId );
  errorPacket->data().seq = sequence;
  errorPacket->data().error_id = errorcode;
  errorPacket->data().message_id = messageId;

  Packets::LobbyPacketContainer pRP( m_encKey );
  pRP.addPacket( errorPacket );
  sendPacket( pRP );
}

void Sapphire::Network::GameConnection::getCharList( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  uint64_t sequence = *reinterpret_cast< uint64_t* >( &packet.data[ 0 ] + 0x10 );
  g_log.info( "Sequence [" + std::to_string( sequence ) + "]" );

  g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] ReqCharList" );
  Packets::LobbyPacketContainer pRP( m_encKey );

  auto serverListPacket = makeLobbyPacket< FFXIVIpcServerList >( tmpId );
  serverListPacket->data().seq = 1;
  serverListPacket->data().offset = 0;
  serverListPacket->data().numServers = 1;
  serverListPacket->data().server[ 0 ].id = g_serverLobby.getConfig().global.general.worldID;
  serverListPacket->data().server[ 0 ].index = 0;
  serverListPacket->data().final = 1;
  strcpy( serverListPacket->data().server[ 0 ].name, g_serverLobby.getConfig().worldName.c_str() );
  pRP.addPacket( serverListPacket );

  auto retainerListPacket = makeLobbyPacket< FFXIVIpcRetainerList >( tmpId );
  retainerListPacket->data().padding[ 8 ] = 1;
  pRP.addPacket( retainerListPacket );

  sendPacket( pRP );

  auto charList = g_restConnector.getCharList( ( char* ) m_pSession->getSessionId() );

  uint32_t charIndex = 0;

  for( uint8_t i = 0; i < 4; i++ )
  {
    auto charListPacket = makeLobbyPacket< FFXIVIpcCharList >( tmpId );
    charListPacket->data().seq = sequence;
    charListPacket->data().numInPacket = 2;
    charListPacket->data().counter = i * 4;

    for( uint8_t j = 0; j < 2; j++ )
    {
      if( charIndex < charList.size() && charList.size() != 0 )
      {
        FFXIVIpcCharList::CharaDetails details;
        memset( &details, 0, sizeof( FFXIVIpcCharList::CharaDetails ) );

        auto& charEntry = charList[ charIndex ];
        details.uniqueId = std::get< 1 >( charEntry );
        details.contentId = std::get< 2 >( charEntry );
        details.serverId = g_serverLobby.getConfig().global.general.worldID;
        details.serverId1 = g_serverLobby.getConfig().global.general.worldID;
        details.index = charIndex;
        strcpy( details.charDetailJson, std::get< 3 >( charEntry ).c_str() );
        strcpy( details.nameChara, std::get< 0 >( charEntry ).c_str() );
        strcpy( details.nameServer, g_serverLobby.getConfig().worldName.c_str() );
        strcpy( details.nameServer1, g_serverLobby.getConfig().worldName.c_str() );

        charListPacket->data().charaDetails[ j ] = details;

        g_log.debug( "[" + std::to_string( charIndex ) + "] " + std::to_string( details.index ) + " - "
                     + std::get< 0 >( charEntry ) + " - " +
                     std::to_string( std::get< 1 >( charEntry ) ) + " - " +
                     std::to_string( std::get< 2 >( charEntry ) ) + " - " +
                     std::get< 3 >( charEntry ) );
      }
      charIndex++;
    }


    // TODO: Eventually move to account info storage
    if( i == 3 )
    {
      charListPacket->data().entitledExpansion = 2;
      charListPacket->data().maxCharOnWorld = 25;
      charListPacket->data().unknown8 = 8;
      charListPacket->data().veteranRank = 12;
      charListPacket->data().counter = ( i * 4 ) + 1;
      charListPacket->data().unknown4 = 128;
    }
    Packets::LobbyPacketContainer pRP( m_encKey );
    pRP.addPacket( charListPacket );
    sendPacket( pRP );

  }
}

void Sapphire::Network::GameConnection::enterWorld( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  uint64_t sequence = *reinterpret_cast< uint64_t* >( &packet.data[ 0 ] + 0x10 );
  g_log.info( "Sequence [" + std::to_string( sequence ) + "]" );

  g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] ReqEnterWorld" );

  uint64_t lookupId = *reinterpret_cast< uint64_t* >( &packet.data[ 0 ] + 0x18 );

  uint32_t logInCharId = -1;
  std::string logInCharName;
  auto charList = g_restConnector.getCharList( ( char* ) m_pSession->getSessionId() );
  for( uint32_t i = 0; i < charList.size(); i++ )
  {
    uint64_t thisContentId = std::get< 2 >( charList[ i ] );

    if( thisContentId == lookupId )
    {
      logInCharId = std::get< 1 >( charList[ i ] );
      logInCharName = std::get< 0 >( charList[ i ] );
      break;
    }
  }

  if( logInCharId == -1 )
    return;

  g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] Logging in as " + logInCharName + "(" +
              std::to_string( logInCharId ) + ")" );

  Packets::LobbyPacketContainer pRP( m_encKey );

  auto enterWorldPacket = makeLobbyPacket< FFXIVIpcEnterWorld >( tmpId );
  enterWorldPacket->data().contentId = lookupId;
  enterWorldPacket->data().seq = sequence;
  strcpy( enterWorldPacket->data().host, g_serverLobby.getConfig().global.network.zoneHost.c_str() );
  enterWorldPacket->data().port = g_serverLobby.getConfig().global.network.zonePort;
  enterWorldPacket->data().charId = logInCharId;
  memcpy( enterWorldPacket->data().sid, m_pSession->getSessionId(), 66 );
  pRP.addPacket( enterWorldPacket );
  sendPacket( pRP );
}

bool Sapphire::Network::GameConnection::sendServiceAccountList( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  LobbySessionPtr pSession = g_serverLobby.getSession( ( char* ) &packet.data[ 0 ] + 0x20 );

  if( g_serverLobby.getConfig().allowNoSessionConnect && pSession == nullptr )
  {
    auto session = make_LobbySession();
    session->setAccountID( 0 );
    session->setSessionId( ( uint8_t* ) &packet.data[ 0 ] + 0x20 );
    pSession = session;
    g_log.info( "Allowed connection with no session: " + std::string( ( char* ) &packet.data[ 0 ] + 0x20 ) );
  }

  if( pSession != nullptr )
  {
    g_log.info( "Found session linked to accountId: " + std::to_string( pSession->getAccountID() ) );
    m_pSession = pSession;

    auto serviceIdInfoPacket = makeLobbyPacket< FFXIVIpcServiceIdInfo >( tmpId );
    sprintf( serviceIdInfoPacket->data().serviceAccount[ 0 ].name, "FINAL FANTASY XIV" );
    serviceIdInfoPacket->data().numServiceAccounts = 1;
    serviceIdInfoPacket->data().u1 = 3;
    serviceIdInfoPacket->data().u2 = 0x99;
    serviceIdInfoPacket->data().serviceAccount[ 0 ].id = 0x002E4A2B;

    Packets::LobbyPacketContainer pRP( m_encKey );
    pRP.addPacket( serviceIdInfoPacket );
    sendPacket( pRP );
  }
  else
  {
    g_log.info( "Could not retrieve session: " + std::string( ( char* ) &packet.data[ 0 ] + 0x20 ) );
    sendError( 1, 5006, 13001, tmpId );

    return true;
  }
  return false;
}

bool Sapphire::Network::GameConnection::createOrModifyChar( FFXIVARR_PACKET_RAW& packet, uint32_t tmpId )
{
  uint64_t sequence = *reinterpret_cast< uint64_t* >( &packet.data[ 0 ] + 0x10 );
  uint8_t type = *reinterpret_cast< uint8_t* >( &packet.data[ 0 ] + 0x29 );
  g_log.info( "Sequence [" + std::to_string( sequence ) + "]" );
  g_log.info( "Type [" + std::to_string( type ) + "]" );

  g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] ReqCharCreate" );

  std::string name;
  uint32_t newId = g_restConnector.getNextCharId();
  uint64_t newContentId = g_restConnector.getNextContentId();

  if( type == 1 ) //Character creation name check
  {
    name = std::string( ( char* ) &packet.data[ 0 ] + 0x2C );

    g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] Type 1: " + name );

    Packets::LobbyPacketContainer pRP( m_encKey );

    m_pSession->newCharName = name;

    if( g_restConnector.checkNameTaken( m_pSession->newCharName ) )
    {
      sendError( sequence, 3074, 13004, tmpId );
      return true;
    }

    auto charCreatePacket = makeLobbyPacket< FFXIVIpcCharCreate >( tmpId );
    charCreatePacket->data().content_id = newContentId;
    strcpy( charCreatePacket->data().name, name.c_str() );
    strcpy( charCreatePacket->data().world, g_serverLobby.getConfig().worldName.c_str() );
    charCreatePacket->data().type = 1;
    charCreatePacket->data().seq = sequence;
    charCreatePacket->data().unknown = 1;
    charCreatePacket->data().unknown_2 = 1;
    charCreatePacket->data().unknown_7 = 1;
    charCreatePacket->data().unknown_8 = 1;
    pRP.addPacket( charCreatePacket );
    sendPacket( pRP );
  }
  else if( type == 2 ) //Character creation finalize
  {
    std::string charDetails( ( char* ) &packet.data[ 0 ] + 0x4C );
    g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] Type 2: " + charDetails );

    if( g_restConnector.createCharacter( ( char* ) m_pSession->getSessionId(), m_pSession->newCharName, charDetails ) !=
        -1 )
    {
      Packets::LobbyPacketContainer pRP( m_encKey );

      auto charCreatePacket = makeLobbyPacket< FFXIVIpcCharCreate >( tmpId );
      charCreatePacket->data().content_id = newContentId;
      strcpy( charCreatePacket->data().name, name.c_str() );
      strcpy( charCreatePacket->data().world, g_serverLobby.getConfig().worldName.c_str() );
      strcpy( charCreatePacket->data().world2, g_serverLobby.getConfig().worldName.c_str() );
      charCreatePacket->data().type = 2;
      charCreatePacket->data().seq = sequence;
      charCreatePacket->data().unknown = 1;
      charCreatePacket->data().unknown_2 = 1;
      charCreatePacket->data().unknown_7 = 1;
      charCreatePacket->data().unknown_8 = 1;
      pRP.addPacket( charCreatePacket );
      sendPacket( pRP );
    }
    else
    {
      sendError( sequence, 5006, 13001, tmpId );
    }
  }
  else if( type == 4 ) //Character delete
  {
    name = std::string( ( char* ) &packet.data[ 0 ] + 0x2C );
    g_log.info( "[" + std::to_string( m_pSession->getAccountID() ) + "] Type 4: " + name );


    if( g_restConnector.deleteCharacter( ( char* ) m_pSession->getSessionId(), name ) )
    {

      auto charCreatePacket = makeLobbyPacket< FFXIVIpcCharCreate >( tmpId );
      //charCreatePacket->data().content_id = deletePlayer.getContentId();
      charCreatePacket->data().content_id = 0;
      strcpy( charCreatePacket->data().name, name.c_str() );
      strcpy( charCreatePacket->data().world, g_serverLobby.getConfig().worldName.c_str() );
      charCreatePacket->data().type = 4;
      charCreatePacket->data().seq = sequence;
      charCreatePacket->data().unknown = 1;
      charCreatePacket->data().unknown_2 = 1;
      charCreatePacket->data().unknown_7 = 1;
      charCreatePacket->data().unknown_8 = 1;

      Packets::LobbyPacketContainer pRP( m_encKey );
      pRP.addPacket( charCreatePacket );
      sendPacket( pRP );
    }
    else
    {
      sendError( sequence, 5006, 13001, tmpId );
    }
  }
  else
  {
    g_log.error( "[" + std::to_string( m_pSession->getAccountID() ) + "] Unknown Character Creation Type: " +
                 std::to_string( type ) );
  }
  return false;
}

void Sapphire::Network::GameConnection::handleGamePacket( Packets::FFXIVARR_PACKET_RAW& packet )
{

  uint32_t tmpId = packet.segHdr.target_actor;

  g_log.info( "OpCode [" + std::to_string( *reinterpret_cast< uint16_t* >( &packet.data[ 2 ] ) ) + "]" );

  switch( *reinterpret_cast< uint16_t* >( &packet.data[ 2 ] ) )
  {
    case ClientVersionInfo:
    {
      // todo: validate client version based on sha1 or gamever/bootver
      sendServiceAccountList( packet, tmpId );
    }
      break;

    case ReqCharList:
    {
      getCharList( packet, tmpId );
    }
      break;

    case ReqEnterWorld:
    {
      enterWorld( packet, tmpId );
    }
      break;

    case ReqCharCreate:
    {
      createOrModifyChar( packet, tmpId );
    }
      break;

  }

}

void Sapphire::Network::GameConnection::sendPacket( Packets::LobbyPacketContainer& pLpc )
{
  uint16_t size = pLpc.getSize();
  uint8_t* dataPtr = pLpc.getRawData( false );
  std::vector< uint8_t > sendBuffer;
  sendBuffer.assign( dataPtr, dataPtr + size );
  Send( sendBuffer );
}

void Sapphire::Network::GameConnection::sendPackets( Packets::PacketContainer* pPacket )
{
  //g_log.Log(LoggingSeverity::info, pPacket->toString());
  std::vector< uint8_t > sendBuffer;

  pPacket->fillSendBuffer( sendBuffer );
  Send( sendBuffer );
}

void Sapphire::Network::GameConnection::sendSinglePacket( FFXIVPacketBasePtr pPacket )
{
  PacketContainer pRP = PacketContainer();
  pRP.addPacket( pPacket );
  sendPackets( &pRP );
}

void Sapphire::Network::GameConnection::generateEncryptionKey( uint32_t key, const std::string& keyPhrase )
{
  memset( m_baseKey, 0, 0x2C );
  m_baseKey[ 0 ] = 0x78;
  m_baseKey[ 1 ] = 0x56;
  m_baseKey[ 2 ] = 0x34;
  m_baseKey[ 3 ] = 0x12;
  memcpy( m_baseKey + 0x04, &key, 4 );
  m_baseKey[ 8 ] = 0x30;
  m_baseKey[ 9 ] = 0x11;
  memcpy( ( char* ) m_baseKey + 0x0C, keyPhrase.c_str(), keyPhrase.size() );
  Sapphire::Util::md5( m_baseKey, m_encKey, 0x2C );
}

void Sapphire::Network::GameConnection::handlePackets( const Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                                                       const std::vector< Sapphire::Network::Packets::FFXIVARR_PACKET_RAW >& packetData )
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
        g_log.info( "GamePacket [" + std::to_string( inPacket.segHdr.type ) + "]" );
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
