#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

#include "Util/UtilMath.h"

#include <Network/CommonActorControl.h>
#include <Network/Util/PacketUtil.h>

#include "Manager/PartyMgr.h"
#include <algorithm>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectSwiftsongAura : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectSwiftsongAura() : Sapphire::ScriptAPI::StatusEffectScript( SwiftsongAura )
  {
  }

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    if (!actor.isAlive())
    {
      actor.removeSingleStatusEffectById( SwiftsongAura );
      return;
    }

    auto pPlayer = actor.getAsPlayer();
    if( !pPlayer )
      return;

    if (pPlayer->isInCombat())
    {
      pPlayer->removeSingleStatusEffectById( SwiftsongAura );
      return;
    }

    

    if( pPlayer->getPartyId() == 0 )
      return;

    auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();
    auto pParty = partyMgr.getParty( pPlayer->getPartyId() );
    auto membersIds = pParty->MemberId;
    for( auto& target : actor.getInRangeActors(false) )
    {
      if( std::find(membersIds.begin(), membersIds.end(), target->getId()) != membersIds.end() )
      {
        if ( ( target->isPlayer() && target->getAsPlayer()->isInCombat() ) ||
          ( target->isBattleNpc() && target->getAsBNpc()->getState() == Sapphire::Entity::BNpcState::Combat) )
        {
          continue;
        }


        auto distance = Sapphire::Common::Util::distance( actor.getPos(), target->getPos() );
        if( distance <= 20.0f )
        {
          auto targetChara = target->getAsChara();
          if (targetChara->hasStatusEffect(SwiftsongBuff))
          {
            auto effect = targetChara->getStatusEffectById( SwiftsongBuff );
            effect->refresh( 5000 );
          }
          else
          {
            auto effect = StatusEffect::make_StatusEffect( SwiftsongBuff, actor.getAsChara(), targetChara, 5000, 3000 );
            effect->setFlag( 5 );
            effect->setParam( 20 );
            targetChara->addStatusEffect( effect );
            Network::Util::Packet::sendHudParam( *targetChara );
          }
        }
      }
    }


    
  }
};

EXPOSE_SCRIPT( StatusEffectSwiftsongAura );