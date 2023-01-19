#include "ItemAction.h"

#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include <Actor/Player.h>
#include <Network/PacketWrappers/EffectPacket.h>

#include "Manager/PlayerMgr.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

ItemAction::ItemAction( Sapphire::Entity::CharaPtr source, uint32_t itemId,
                        std::shared_ptr< Excel::ExcelStruct< Excel::ItemAction > > itemActionData, uint16_t itemSourceSlot,
                        uint16_t itemSourceContainer ) :
  m_itemAction( std::move( itemActionData ) ),
  m_itemSourceSlot( itemSourceSlot ),
  m_itemSourceContainer( itemSourceContainer )
{
  m_id = itemId;
  m_pSource = std::move( source );
}

void ItemAction::start()
{
  if( !m_pSource->isPlayer() )
    return;

  // todo: check inv slot for item

  // todo: can we just do this?
  execute();
}

void ItemAction::execute()
{
  switch( m_itemAction->data().Action )
  {
    default:
    {
      Manager::PlayerMgr::sendDebug( *getSourceChara()->getAsPlayer(), "ItemAction type {0} not supported.", m_itemAction->data().Action );
      break;
    }

    case Common::ItemActionType::ItemActionVFX:
    case Common::ItemActionType::ItemActionVFX2:
    {
      handleVFXItem();

      break;
    }

    case Common::ItemActionType::ItemActionMount:
    {
      handleMountItem();

      break;
    }
  }
}

void ItemAction::interrupt()
{

}

void ItemAction::handleVFXItem()
{
  Common::CalcResultParam effect{};
  effect.Type = Common::ActionEffectType::CALC_RESULT_TYPE_CHECK_BARRIER;
  effect.Value = m_itemAction->data().Calcu0Arg[ 0 ];

  auto effectPacket = std::make_shared< EffectPacket >( getSourceChara()->getId(), getId() );
  effectPacket->setTargetActor( getSourceChara()->getId() );
  effectPacket->setAnimationId( Common::ItemActionType::ItemActionVFX );
  effectPacket->setDisplayType( Common::ActionEffectDisplayType::ShowItemName );
  effectPacket->addTargetEffect( effect, static_cast< uint64_t >( getSourceChara()->getId() ) );

  m_pSource->sendToInRangeSet( effectPacket, true );
}

void ItemAction::handleMountItem()
{
  auto player = getSourceChara()->getAsPlayer();

  player->unlockMount( m_itemAction->data().Calcu0Arg[ 0 ] );
  player->dropInventoryItem( static_cast< Common::InventoryType >( m_itemSourceContainer ), static_cast< uint8_t >( m_itemSourceSlot ) );
}