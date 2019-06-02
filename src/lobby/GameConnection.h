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

namespace Sapphire::Lobby::Network
{

  class GameConnection : public Sapphire::Network::Connection
  {

  private:
    // TODO move the next three params to the session, makes more sense there
    // encryption key
    uint8_t m_encKey[0x10];

    // base key, the encryption key is generated from this
    uint8_t m_baseKey[0x2C];

    bool m_bEncryptionInitialized;

    Sapphire::Network::AcceptorPtr m_pAcceptor;

    LobbySessionPtr m_pSession;

    Common::Util::LockedQueue< Sapphire::Network::Packets::GamePacketPtr > m_inQueue;
    Common::Util::LockedQueue< Sapphire::Network::Packets::GamePacketPtr > m_outQueue;
    std::vector< uint8_t > m_packets;

  public:
    GameConnection( Sapphire::Network::HivePtr pHive, Sapphire::Network::AcceptorPtr pAcceptor, FrameworkPtr pFw );

    ~GameConnection();

    void generateEncryptionKey( uint32_t key, const std::string& keyPhrase );

    // overwrite the parents onConnect for our game socket needs
    void onAccept( const std::string& host, uint16_t port ) override;

    void onDisconnect() override;

    void onRecv( std::vector< uint8_t >& buffer ) override;

    void onError( const asio::error_code& error ) override;

    void sendError( uint64_t sequence, uint32_t errorcode, uint16_t messageId, uint32_t tmpId );

    void getCharList( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    void enterWorld( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    bool sendServiceAccountList( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    bool createOrModifyChar( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& packet, uint32_t tmpId );

    void handlePackets( const Sapphire::Network::Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                        const std::vector< Sapphire::Network::Packets::FFXIVARR_PACKET_RAW >& packetData );

    void handleGamePacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void handlePacket( Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );

    void sendPackets( Sapphire::Network::Packets::PacketContainer* pPacket );

    void sendPacket( Packets::LobbyPacketContainer& pLpc );

    void sendSinglePacket( Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );


  };

}


#endif
