#ifndef _CORE_NETWORK_PACKETS_INITUIPACKET_H
#define _CORE_NETWORK_PACKETS_INITUIPACKET_H

#include <Network/GamePacket.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Client Player Initialization packet. This must be sent to the client
  * once upon connection to configure the UI.
  */
  class PlayerSetupPacket : public ZoneChannelPacket< FFXIVIpcPlayerStatus >
  {
  public:
    PlayerSetupPacket( Entity::Player& player ) :
      ZoneChannelPacket< FFXIVIpcPlayerStatus >( player.getId(), player.getId() )
    {
      initialize( player );
    };

  private:
    void initialize( Entity::Player& player )
    {
      m_data.CharaId = player.getCharacterId();

      // TODO: Support rested experience.
      //m_data.restedExp = 0;
      //m_data.padding = 0x100;
      m_data.EntityId = player.getId();
      m_data.Race = player.getLookAt( Common::CharaLook::Race );
      m_data.Tribe = player.getLookAt( Common::CharaLook::Tribe );
      m_data.Sex = player.getLookAt( Common::CharaLook::Gender );
      m_data.ClassJob = static_cast< uint8_t >( player.getClass() );
      m_data.FirstClass = static_cast< uint8_t >( player.getClass() );
      //m_data.maxLevel = player.getLevel();
      m_data.GuardianDeity = static_cast< uint8_t >( player.getGuardianDeity() );
      m_data.BirthMonth = player.getBirthMonth();
      m_data.Birthday = player.getBirthDay();
      m_data.StartTown = player.getStartTown();
      m_data.HomePoint = player.getHomepoint();
      //m_data.pose = player.getPose();

      memset( &m_data.Name[ 0 ], 0, sizeof( m_data.Name ) );
      strcpy( reinterpret_cast< char* >( m_data.Name ), player.getName().c_str() );

      memcpy( m_data.Aetheryte, player.getAetheryteArray().data(), sizeof( m_data.Aetheryte ) );

      // Set the class levels and exp.
      for( uint8_t i = 0; i < 23; i++ )
      {
        m_data.Lv[ i ] = player.getClassArray()[ i ];
        m_data.Exp[ i ] = player.getExpArray()[ i ];
      }

    //  memcpy( m_data.orchestrionMask, player.getOrchestrionBitmask(), sizeof( m_data.orchestrionMask ) );

      memcpy( m_data.MountList, player.getMountGuideBitmask().data(), sizeof( m_data.MountList ) );

      memcpy( m_data.Reward, player.getUnlockBitmask().data(), sizeof( m_data.Reward ) );

      memcpy( m_data.Discovery16, player.getDiscoveryBitmask().data(), sizeof( m_data.Discovery16 ) + sizeof( m_data.Discovery32 ) );

      memcpy( m_data.HowTo, player.getHowToArray().data(), sizeof( m_data.HowTo ) );

      // possibly max level or current level
   //   m_data.maxLevel = Common::MAX_PLAYER_LEVEL;
      m_data.ExpansionLevel = Common::CURRENT_EXPANSION_ID;

      // df stuff
      // todo: actually do this properly
  //      m_data.unknown70[4] = 1; // enable df

      // enable all raids/guildhests/dungeons
     /* memset( m_data.unlockedDungeons, 0xFF, sizeof( m_data.unlockedDungeons ) );
      memset( m_data.unlockedGuildhests, 0xFF, sizeof( m_data.unlockedGuildhests ) );
      memset( m_data.unlockedPvp, 0xFF, sizeof( m_data.unlockedPvp ) );
      memset( m_data.unlockedRaids, 0xFF, sizeof( m_data.unlockedRaids ) );
      memset( m_data.unlockedTrials, 0xFF, sizeof( m_data.unlockedTrials ) );*/
    };
  };
  template< typename... Args >
  std::shared_ptr< PlayerSetupPacket > makePlayerSetup( Args... args )
  {
    return std::make_shared< PlayerSetupPacket >( args... );
  }
}

#endif /*_CORE_NETWORK_PACKETS_CINITUIPACKET_H*/
