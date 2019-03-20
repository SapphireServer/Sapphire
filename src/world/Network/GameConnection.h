#ifndef GAMECONNECTION_H
#define GAMECONNECTION_H

#include <Network/Connection.h>

#include <Network/CommonNetwork.h>
#include <Util/LockedQueue.h>
#include <map>

#include "ForwardsZone.h"

#define DECLARE_HANDLER( x ) void x( FrameworkPtr pFw, const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )

namespace Sapphire::Network::Packets
{
  class GamePacket;
  class PacketContainer;
}

namespace Sapphire::Network
{

  enum ConnectionType : uint8_t
  {
    Zone = 1,
    Chat = 2,
    Lobby = 3,
    None
  };

  class GameConnection : public Connection
  {

  private:
    typedef void ( GameConnection::* Handler )( FrameworkPtr pFw,
                                                const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
                                                Entity::Player& player );

    using HandlerMap = std::map< uint16_t, Handler >;
    using HandlerStrMap = std::map< uint16_t, std::string >;

    AcceptorPtr m_pAcceptor;

    // handler for game packets ( main type 0x03, connection type 1 )
    HandlerMap m_zoneHandlerMap;
    HandlerStrMap m_zoneHandlerStrMap;

    // handler for game packets ( main type 0x03, connection type 2 )
    HandlerMap m_chatHandlerMap;
    HandlerStrMap m_chatHandlerStrMap;

    World::SessionPtr m_pSession;

    LockedQueue< Sapphire::Network::Packets::FFXIVARR_PACKET_RAW > m_inQueue;
    LockedQueue< Packets::FFXIVPacketBasePtr > m_outQueue;
    std::vector< uint8_t > m_packets;

  public:
    ConnectionType m_conType;

    GameConnection( HivePtr pHive, AcceptorPtr pAcceptor, FrameworkPtr pFw );

    ~GameConnection();

    // overwrite the parents onConnect for our game socket needs
    void onAccept( const std::string& host, uint16_t port ) override;

    void onDisconnect() override;

    void onRecv( std::vector< uint8_t >& buffer ) override;

    void onError( const asio::error_code& error ) override;

    void handlePackets( const Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                        const std::vector< Packets::FFXIVARR_PACKET_RAW >& packetData );

    void queueInPacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW inPacket );

    void queueOutPacket( Packets::FFXIVPacketBasePtr outPacket );

    void processInQueue();

    void processOutQueue();

    void handlePacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void handleZonePacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void handleChatPacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void sendPackets( Packets::PacketContainer* pPacket );

    void sendSinglePacket( Sapphire::Network::Packets::FFXIVPacketBasePtr pPacket );

    void injectPacket( const std::string& packetpath, Entity::Player& player );

    DECLARE_HANDLER( initHandler );

    DECLARE_HANDLER( finishLoadingHandler );

    DECLARE_HANDLER( blackListHandler );

    DECLARE_HANDLER( socialListHandler );

    DECLARE_HANDLER( linkshellListHandler );

    DECLARE_HANDLER( playTimeHandler );

    DECLARE_HANDLER( pingHandler );

    DECLARE_HANDLER( fcInfoReqHandler );

    DECLARE_HANDLER( setSearchInfoHandler );

    DECLARE_HANDLER( reqSearchInfoHandler );

    DECLARE_HANDLER( reqExamineSearchCommentHandler );

    DECLARE_HANDLER( reqExamineFcInfo );

    DECLARE_HANDLER( updatePositionHandler );

    DECLARE_HANDLER( chatHandler );

    DECLARE_HANDLER( zoneLineHandler );

    DECLARE_HANDLER( clientTriggerHandler );

    DECLARE_HANDLER( inventoryModifyHandler );

    DECLARE_HANDLER( discoveryHandler );

    DECLARE_HANDLER( eventHandlerTalk );

    DECLARE_HANDLER( eventHandlerEmote );

    DECLARE_HANDLER( eventHandlerWithinRange );

    DECLARE_HANDLER( eventHandlerOutsideRange );

    DECLARE_HANDLER( eventHandlerEnterTerritory );

    DECLARE_HANDLER( eventHandlerReturn );

    DECLARE_HANDLER( eventHandlerShop );

    DECLARE_HANDLER( eventHandlerLinkshell );

    DECLARE_HANDLER( logoutHandler );

    DECLARE_HANDLER( cfDutyInfoRequest );

    DECLARE_HANDLER( cfRegisterDuty );

    DECLARE_HANDLER( cfRegisterRoulette );

    DECLARE_HANDLER( cfDutyAccepted );

    DECLARE_HANDLER( actionHandler );
    
    DECLARE_HANDLER( aoeActionHandler );

    DECLARE_HANDLER( gm1Handler );

    DECLARE_HANDLER( gm2Handler );

    DECLARE_HANDLER( reqEquipDisplayFlagsHandler );

    DECLARE_HANDLER( performNoteHandler );

    DECLARE_HANDLER( landRenameHandler );

    DECLARE_HANDLER( housingUpdateGreetingHandler );

    DECLARE_HANDLER( buildPresetHandler );

    DECLARE_HANDLER( tellHandler );

    DECLARE_HANDLER( reqPlaceHousingItem );

    DECLARE_HANDLER( reqMoveHousingItem );

    DECLARE_HANDLER( marketBoardSearch );

    DECLARE_HANDLER( marketBoardRequestItemInfo );

    DECLARE_HANDLER( marketBoardRequestItemListings );

  };

}

#endif
