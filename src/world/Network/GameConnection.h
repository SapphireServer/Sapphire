#ifndef GAMECONNECTION_H
#define GAMECONNECTION_H

#include <Network/Connection.h>

#include <Network/CommonNetwork.h>
#include <Util/LockedQueue.h>
#include <map>

#include "ForwardsZone.h"

#define DECLARE_HANDLER( x ) void x( const Sapphire::Network::Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )

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

  class GameConnection : public Network::Connection
  {

  private:
    typedef void ( GameConnection::* Handler )( const Network::Packets::FFXIVARR_PACKET_RAW& inPacket,
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

    Common::Util::LockedQueue< Network::Packets::FFXIVARR_PACKET_RAW > m_inQueue;
    Common::Util::LockedQueue< Packets::FFXIVPacketBasePtr > m_outQueue;
    std::vector< uint8_t > m_packets;

  public:
    ConnectionType m_conType;

    GameConnection( HivePtr pHive, AcceptorPtr pAcceptor );

    ~GameConnection() override;

    // overwrite the parents onConnect for our game socket needs
    void onAccept( const std::string& host, uint16_t port ) override;

    void onDisconnect() override;

    void onRecv( std::vector< uint8_t >& buffer ) override;

    void onError( const asio::error_code& error ) override;

    void handlePackets( const Packets::FFXIVARR_PACKET_HEADER& ipcHeader,
                        const std::vector< Packets::FFXIVARR_PACKET_RAW >& packetData );

    void queueInPacket( Sapphire::Network::Packets::FFXIVARR_PACKET_RAW inPacket );

    void queueOutPacket( Packets::FFXIVPacketBasePtr outPacket );
    void queueOutPacket( std::vector< Packets::FFXIVPacketBasePtr > vector );

    void processInQueue();

    void processOutQueue();

    void handlePacket( Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void handleZonePacket( Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void handleChatPacket( Network::Packets::FFXIVARR_PACKET_RAW& pPacket );

    void sendPackets( Packets::PacketContainer* pPacket );

    void sendSinglePacket( Network::Packets::FFXIVPacketBasePtr pPacket );

    void injectPacket( const std::string& packetpath, Entity::Player& player );

    static const char* zonePacketToString( uint32_t opcode );

    DECLARE_HANDLER( loginHandler );

    DECLARE_HANDLER( setLanguageHandler );

    DECLARE_HANDLER( getBlacklistHandler );

    DECLARE_HANDLER( getCommonlistHandler );

    DECLARE_HANDLER( getCommonlistDetailHandler );

    DECLARE_HANDLER( pcSearchHandler );

    DECLARE_HANDLER( joinChatChannelHandler );

    DECLARE_HANDLER( linkshellListHandler );

    DECLARE_HANDLER( linkshellJoinHandler );

    DECLARE_HANDLER( syncHandler );

    DECLARE_HANDLER( setProfileHandler );

    DECLARE_HANDLER( getProfileHandler );

    DECLARE_HANDLER( getSearchCommentHandler );

    DECLARE_HANDLER( reqExamineFcInfo );

    DECLARE_HANDLER( moveHandler );

    DECLARE_HANDLER( chatHandler );

    DECLARE_HANDLER( zoneJumpHandler );

    DECLARE_HANDLER( commandHandler );

    DECLARE_HANDLER( itemOperation );

    DECLARE_HANDLER( newDiscoveryHandler );

    DECLARE_HANDLER( eventHandlerTalk );

    DECLARE_HANDLER( eventHandlerEmote );

    DECLARE_HANDLER( eventHandlerWithinRange );

    DECLARE_HANDLER( eventHandlerOutsideRange );

    DECLARE_HANDLER( eventHandlerEnterTerritory );

    DECLARE_HANDLER( returnEventSceneHeader );
    DECLARE_HANDLER( returnEventScene2 );
    DECLARE_HANDLER( returnEventScene4 );
    DECLARE_HANDLER( returnEventScene8 );
    DECLARE_HANDLER( returnEventScene16 );
    DECLARE_HANDLER( returnEventScene32 );
    DECLARE_HANDLER( returnEventScene64 );
    DECLARE_HANDLER( returnEventScene128 );
    DECLARE_HANDLER( returnEventScene255 );

    DECLARE_HANDLER( startUiEvent );

    DECLARE_HANDLER( eventHandlerLinkshell );

    DECLARE_HANDLER( logoutHandler );

    DECLARE_HANDLER( cfRequestPenalties );

    DECLARE_HANDLER( findContent );
    DECLARE_HANDLER( find5Contents );
    DECLARE_HANDLER( findContentAsRandom );

    DECLARE_HANDLER( cfDutyAccepted );

    DECLARE_HANDLER( actionRequest );

    DECLARE_HANDLER( selectGroundActionRequest );

    DECLARE_HANDLER( gmCommandHandler );

    DECLARE_HANDLER( gmCommandNameHandler );

    DECLARE_HANDLER( configHandler );

    DECLARE_HANDLER( landRenameHandler );

    DECLARE_HANDLER( housingUpdateGreetingHandler );

    DECLARE_HANDLER( buildPresetHandler );

    DECLARE_HANDLER( tellHandler );

    DECLARE_HANDLER( chatToChannelHandler );

    DECLARE_HANDLER( reqPlaceHousingItem );

    DECLARE_HANDLER( reqMoveHousingItem );

    DECLARE_HANDLER( catalogSearch );

    DECLARE_HANDLER( marketBoardRequestItemInfo );

    DECLARE_HANDLER( marketBoardRequestItemListings );

    DECLARE_HANDLER( getFcStatus );

    DECLARE_HANDLER( getFcProfile );

    DECLARE_HANDLER( getRequestItemListHandler );

    DECLARE_HANDLER( cancelFindContent );
    DECLARE_HANDLER( acceptContent );

    DECLARE_HANDLER( inviteHandler );
    DECLARE_HANDLER( inviteReplyHandler );

    DECLARE_HANDLER( pcPartyLeaveHandler );
    DECLARE_HANDLER( pcPartyDisbandHandler );
    DECLARE_HANDLER( pcPartyKickHandler );
    DECLARE_HANDLER( pcPartyChangeLeaderHandler );

    DECLARE_HANDLER( friendlistRemoveHandler );
    DECLARE_HANDLER( setFriendlistGroupHandler );
  };

}

#endif
