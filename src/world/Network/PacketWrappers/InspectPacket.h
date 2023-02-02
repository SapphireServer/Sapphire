#pragma once

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacket.h>
#include <Util/Util.h>
#include "Actor/Player.h"
#include "Forwards.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The Examine response packet.
  */
  class InspectPacket : public ZoneChannelPacket< FFXIVIpcInspect >
  {
  public:
    InspectPacket( Entity::Player& player, Entity::PlayerPtr pTarget ) :
      ZoneChannelPacket< FFXIVIpcInspect >( pTarget->getId(), player.getId() )
    {
      initialize( player, pTarget );
    };

  private:
    void initialize( Entity::Player& player, Entity::PlayerPtr pTarget )
    {
      assert( pTarget );
      {
        // todo: this packet needs mapping out
        strcpy( m_data.Name, pTarget->getName().c_str() );
        m_data.ClassJob = static_cast< uint8_t >( pTarget->getClass() );
        m_data.Lv = pTarget->getLevel();

//        m_data.unkFlag1 = 4;
//        m_data.unkFlag2 = 1;

        m_data.Title = pTarget->getTitle();
        m_data.GrandCompany = pTarget->getGc();

        // gc id 0 is no gc, but we only store ranks for 3
        // gc id 3 is immortal flames, but they're at index 2 not 3, so we need to correct for that if we have a gc set
        if( m_data.GrandCompany > 0 )
          m_data.GrandCompanyRank = pTarget->getGcRankArray()[ m_data.GrandCompany - 1 ];

        m_data.MainWeaponModelId = pTarget->getModelMainWeapon();
        m_data.SubWeaponModelId = pTarget->getModelSubWeapon();

//        m_data.worldId = 67; // TODO: world id from server

        memcpy( m_data.Customize, pTarget->getLookArray(), sizeof( m_data.Customize ) );

        m_data.ModelId[ Common::GearModelSlot::ModelHead ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelHead );
        m_data.ModelId[ Common::GearModelSlot::ModelBody ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelBody );
        m_data.ModelId[ Common::GearModelSlot::ModelHands ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelHands );
        m_data.ModelId[ Common::GearModelSlot::ModelLegs ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelLegs );
        m_data.ModelId[ Common::GearModelSlot::ModelFeet ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelFeet );
        m_data.ModelId[ Common::GearModelSlot::ModelNeck ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelNeck );
        m_data.ModelId[ Common::GearModelSlot::ModelEar ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelEar );
        m_data.ModelId[ Common::GearModelSlot::ModelRing1 ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelRing1 );
        m_data.ModelId[ Common::GearModelSlot::ModelRing2 ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelRing2 );
        m_data.ModelId[ Common::GearModelSlot::ModelWrist ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelWrist );

        // todo: main/sub/other stuff too

        for( auto i = 0; i < Common::GearSetSlot::SoulCrystal + 1; ++i )
        {
          auto pItem = pTarget->getItemAt( Common::InventoryType::GearSet0, i );
          if( pItem )
          {
            auto& entry = m_data.Equipment[i];
            entry.CatalogId = pItem->getId();
            entry.HQ = pItem->isHq();
            entry.Stain = static_cast< uint8_t >( pItem->getStain() );

            entry.Materia[0].Grade = 1;
            entry.Materia[0].Type = 1;
            //entry.appearanceCatalogId = pItem->getGlamourId()
            // todo: glamour/materia etc.
          }
        }
      }
    };
  };

}