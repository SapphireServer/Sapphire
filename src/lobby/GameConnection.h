#ifndef GAMECONNECTION_H
#define GAMECONNECTION_H

#include <Network/Connection.h>
#include <Network/Acceptor.h>
#include <Network/CommonNetwork.h>

#include <Network/PacketContainer.h>
#include <Util/LockedQueue.h>

#include <asio.hpp>
#include <map>
#include "LobbyPacketContainer.h"

#include "Forwards.h"

#define DECLARE_HANDLER( x ) void x( Packets::GamePacketPtr pInPacket, Entity::PlayerPtr pPlayer )

namespace Sapphire::Network
{

  class GameConnection : public Connection
  {

  private:
    // TODO move the next three params to the session, makes more sense there
    // encryption key
    uint8_t m_encKey[0x10];

    // base key, the encryption key is generated from this
    uint8_t m_baseKey[0x2C];

    bool m_bEncryptionInitialized;

    AcceptorPtr m_pAcceptor;

    LobbySessionPtr m_pSession;

    LockedQueue< Packets::GamePacketPtr > m_inQueue;
    LockedQueue< Packets::GamePacketPtr > m_outQueue;

  public:
    GameConnection( HivePtr pHive, AcceptorPtr pAcceptor, FrameworkPtr pFw );

    ~GameConnection();

    void generateEncryptionKey( uint32_t key, const std::string& keyPhrase );

    // overwrite the parents onConnect for our game socket needs
    void onAccept( const std::string& host, uint16_t port ) override;

    void onDisconnect() override;

    void onRecv( std::vector< uint8_t >& buffer ) override;

    void onError( const asio::error_code& error ) override;

    void sendError( uint64_t sequence, uint32_t errorcode, uint16_t messageId, uint32_t tmpId );

    void getCharList( Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    void enterWorld( Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    bool sendServiceAccountList( Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    bool createOrModifyChar( Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    void handlePackets( const Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                        const std::vector< Packets::FFXIVARR_PACKET_RAW >& packetData );

    void handleGamePacket( Packets::FFXIVARR_PACKET_RAW& pPacket );

    void handlePacket( Packets::FFXIVPacketBasePtr pPacket );

    void sendPackets( Packets::PacketContainer* pPacket );

    void sendPacket( Packets::LobbyPacketContainer& pLpc );

    void sendSinglePacket( Packets::FFXIVPacketBasePtr pPacket );


  };

}


#endif
