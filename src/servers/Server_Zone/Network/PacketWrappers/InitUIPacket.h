#ifndef _CORE_NETWORK_PACKETS_INITUIPACKET_H
#define _CORE_NETWORK_PACKETS_INITUIPACKET_H

#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The Client UI Initialization packet. This must be sent to the client
* once upon connection to configure the UI.
*/
class InitUIPacket : public ZoneChannelPacket< FFXIVIpcInitUI >
{
public:
   InitUIPacket( Entity::Player& player ) :
      ZoneChannelPacket< FFXIVIpcInitUI >( player.getId(), player.getId() )
   {
      initialize( player );
   };

private:
   void initialize( Entity::Player& player )
   {
      m_data.contentId = player.getContentId();

      // TODO: Support rested experience.
      m_data.restedExp = 0;
      //m_data.padding = 0x100;
      m_data.charId = player.getId();
      m_data.race = player.getLookAt( Common::CharaLook::Race );
      m_data.tribe = player.getLookAt( Common::CharaLook::Tribe );
      m_data.gender = player.getLookAt( Common::CharaLook::Gender );
      m_data.currentClass = static_cast< uint8_t >( player.getClass() );
      m_data.currentJob = static_cast< uint8_t >( player.getClass() );
      m_data.deity = static_cast< uint8_t >( player.getGuardianDeity() );
      m_data.namedayMonth = player.getBirthMonth();
      m_data.namedayDay = player.getBirthDay();
      // TODO: Support grand company status.
      m_data.cityState = player.getStartTown();
      //m_data.gcRank = GCRank::None;

      m_data.homepoint = player.getHomepoint();

      memset( &m_data.name[0], 0, sizeof( m_data.name ) );

      strcpy( &m_data.name[0], player.getName().c_str() );

      memcpy( m_data.aetheryte, player.getAetheryteArray(), sizeof ( m_data.aetheryte ) );

      // Set the class levels and exp.
      for( uint8_t i = 0; i < 25; i++ )
      {
         m_data.levels[i] = player.getClassArray()[i];
         m_data.exp[i] = player.getExpArray()[i];
      }

      memcpy( m_data.orchestrionMask, player.getOrchestrionBitmask(), sizeof( m_data.orchestrionMask ) );

      memcpy( m_data.mountGuideMask, player.getMountGuideBitmask(), sizeof( m_data.mountGuideMask) );

      memcpy( m_data.unlockBitmask, player.getUnlockBitmask(), sizeof( m_data.unlockBitmask ) );

      memcpy( m_data.discovery, player.getDiscoveryBitmask(), sizeof( m_data.discovery ) );

      memcpy( m_data.howto, player.getHowToArray(), sizeof( m_data.howto ) );

      // possibly max level or current level
      m_data.maxLevel = 0x46;
      m_data.expansion = 2;

   };
};

}
}
}
}

#endif /*_CORE_NETWORK_PACKETS_CINITUIPACKET_H*/
