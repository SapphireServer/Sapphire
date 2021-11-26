#ifndef _MODELEQUIPPACKET_H
#define _MODELEQUIPPACKET_H

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The update model packet.
  */
  class ModelEquipPacket : public ZoneChannelPacket< FFXIVIpcEquip >
  {
  public:
    ModelEquipPacket( Entity::Player& player ) :
      ZoneChannelPacket< FFXIVIpcEquip >( player.getId(), player.getId() )
    {
      initialize( player );
    };

  private:
    void initialize( Entity::Player& player )
    {
      m_data.MainWeapon = player.getModelMainWeapon();
      m_data.SubWeapon = player.getModelSubWeapon();
//      m_data.ClassJob = static_cast< uint8_t >( player.getClass() );
//      m_data.Lv = player.getLevel();
      m_data.Equipment[ Common::GearModelSlot::ModelHead ] = player.getModelForSlot( Common::GearModelSlot::ModelHead );
      m_data.Equipment[ Common::GearModelSlot::ModelBody ] = player.getModelForSlot( Common::GearModelSlot::ModelBody );
      m_data.Equipment[ Common::GearModelSlot::ModelHands ] = player.getModelForSlot( Common::GearModelSlot::ModelHands );
      m_data.Equipment[ Common::GearModelSlot::ModelLegs ] = player.getModelForSlot( Common::GearModelSlot::ModelLegs );
      m_data.Equipment[ Common::GearModelSlot::ModelFeet ] = player.getModelForSlot( Common::GearModelSlot::ModelFeet );
      m_data.Equipment[ Common::GearModelSlot::ModelNeck ] = player.getModelForSlot( Common::GearModelSlot::ModelNeck );
      m_data.Equipment[ Common::GearModelSlot::ModelEar ] = player.getModelForSlot( Common::GearModelSlot::ModelEar );
      m_data.Equipment[ Common::GearModelSlot::ModelRing1 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing1 );
      m_data.Equipment[ Common::GearModelSlot::ModelRing2 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing2 );
      m_data.Equipment[ Common::GearModelSlot::ModelWrist ] = player.getModelForSlot( Common::GearModelSlot::ModelWrist );
    };
  };

}

#endif /*_MODELEQUIPPACKET_H*/
