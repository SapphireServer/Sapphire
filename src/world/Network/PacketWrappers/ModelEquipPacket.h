#ifndef _MODELEQUIPPACKET_H
#define _MODELEQUIPPACKET_H

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The update model packet.
  */
  class ModelEquipPacket : public ZoneChannelPacket< FFXIVIpcModelEquip >
  {
  public:
    ModelEquipPacket( Entity::Player& player ) :
      ZoneChannelPacket< FFXIVIpcModelEquip >( player.getId(), player.getId() )
    {
      initialize( player );
    };

  private:
    void initialize( Entity::Player& player )
    {
      m_data.mainWeapon = player.getModelMainWeapon();
      m_data.offWeapon = player.getModelSubWeapon();
      m_data.classJobId = static_cast< uint8_t >( player.getClass() );
      m_data.level = player.getLevel();
      m_data.models[ Common::GearModelSlot::ModelHead ] = player.getModelForSlot( Common::GearModelSlot::ModelHead );
      m_data.models[ Common::GearModelSlot::ModelBody ] = player.getModelForSlot( Common::GearModelSlot::ModelBody );
      m_data.models[ Common::GearModelSlot::ModelHands ] = player.getModelForSlot( Common::GearModelSlot::ModelHands );
      m_data.models[ Common::GearModelSlot::ModelLegs ] = player.getModelForSlot( Common::GearModelSlot::ModelLegs );
      m_data.models[ Common::GearModelSlot::ModelFeet ] = player.getModelForSlot( Common::GearModelSlot::ModelFeet );
      m_data.models[ Common::GearModelSlot::ModelNeck ] = player.getModelForSlot( Common::GearModelSlot::ModelNeck );
      m_data.models[ Common::GearModelSlot::ModelEar ] = player.getModelForSlot( Common::GearModelSlot::ModelEar );
      m_data.models[ Common::GearModelSlot::ModelRing1 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing1 );
      m_data.models[ Common::GearModelSlot::ModelRing2 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing2 );
      m_data.models[ Common::GearModelSlot::ModelWrist ] = player.getModelForSlot( Common::GearModelSlot::ModelWrist );
    };
  };

}

#endif /*_MODELEQUIPPACKET_H*/
