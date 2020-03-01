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
  }
}

void ItemAction::interrupt( Common::ActionInterruptType type )
{

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