#include "ItemAction.h"

#include <Exd/ExdDataGenerated.h>

#include <Actor/Player.h>
#include <Network/PacketWrappers/EffectPacket.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

ItemAction::ItemAction( Sapphire::Entity::CharaPtr source, uint32_t itemId,
                        Sapphire::Data::ItemActionPtr itemActionData, uint16_t itemSourceSlot,
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
  switch( m_itemAction->type )
  {
    default:
    {
      getSourceChara()->getAsPlayer()->sendDebug( "ItemAction type {0} not supported.", m_itemAction->type );
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

    case Common::ItemActionType::ItemActionOrchestrion:
    {
      handleOrchestrionItem();

      break;
    }
  }
}

void ItemAction::interrupt( Common::ActionInterruptType type )
{

}

void ItemAction::handleMountItem()
{
  auto player = getSourceChara()->getAsPlayer();
  player->unlockMount( m_itemAction->data[ 0 ] );
  player->dropInventoryItem ( static_cast< Common::InventoryType >( m_itemSourceContainer ), m_itemSourceSlot, false );
}

void ItemAction::handleOrchestrionItem()
{
  auto player = getSourceChara()->getAsPlayer();
  //player->learnSong( m_itemAction->data[ 0 ], m_itemAction->data[ 1 ] );
  //player->dropInventoryItem ( static_cast< Common::InventoryType >( m_itemSourceContainer ), m_itemSourceSlot, false );
  player->sendUrgent( "orchestrion is not aligned correctly, handleOrchestrionItem() disabled until PlayerSetup fully fixed." );
}

void ItemAction::handleVFXItem()
{
  Common::EffectEntry effect{};
  effect.effectType = Common::ActionEffectType::VFX;
  effect.value = m_itemAction->data[ 0 ];

  auto effectPacket = std::make_shared< Network::Packets::Server::EffectPacket >( getSourceChara()->getId(),
                                                                                  getSourceChara()->getId(), getId() );
  effectPacket->setTargetActor( getSourceChara()->getId() );
  effectPacket->setAnimationId( Common::ItemActionType::ItemActionVFX );
  effectPacket->setDisplayType( Common::ActionEffectDisplayType::ShowItemName );
  effectPacket->addEffect( effect );

  m_pSource->sendToInRangeSet( effectPacket, true );
}