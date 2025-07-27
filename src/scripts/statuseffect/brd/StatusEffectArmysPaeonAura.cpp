#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

#include <Network/Util/PacketUtil.h>

#include "Manager/PartyMgr.h"

#include <Math/CalcStats.h>
#include "Util/UtilMath.h"
#include <algorithm>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectArmysPaeonAura : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectArmysPaeonAura() : Sapphire::ScriptAPI::StatusEffectScript( ArmysPaeonAura )
  {
  }

  static constexpr auto DrainPotency = 60;
  static constexpr auto Potency = 30;

  void onApply( Entity::Chara& actor )
  {
    actor.removeSingleStatusEffectById( ArmysPaeonStatus );
    actor.removeSingleStatusEffectById( MagesBalladAura );
    actor.removeSingleStatusEffectById( FoeRequiemAura );
  }

  void onTick( Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    uint32_t mp = actor.getMp();
    uint32_t mpDrained = Math::CalcStats::calcMpRefresh( DrainPotency, actor.getLevel() );
    if( mp <= mpDrained )
    {
      actor.setMp( 0 );
      actor.removeSingleStatusEffectById( ArmysPaeonAura );
      // We refresh the buff on other players one last time. The caster also gets one last tick
    }
    else
    {
      actor.setMp( mp - mpDrained );
    }

    actor.setTp( actor.getTp() + Potency );
    auto partyPotency = Potency;

    if( actor.hasStatusEffect( BattleVoiceStatus ) )
    {
      partyPotency *= 2;
    }

    auto pPlayer = actor.getAsPlayer();
    if( !pPlayer )
      return;

    if( pPlayer->getPartyId() == 0 )
      return;

    auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();
    auto pParty = partyMgr.getParty( pPlayer->getPartyId() );
    auto membersIds = pParty->MemberId;
    for( auto& target : actor.getInRangeActors( false ) )
    {
      if( std::find( membersIds.begin(), membersIds.end(), target->getId() ) != membersIds.end() )
      {
        auto distance = Sapphire::Common::Util::distance( actor.getPos(), target->getPos() );
        if( distance <= 20.0f )
        {
          auto targetChara = target->getAsChara();
          if( targetChara->hasStatusEffect( ArmysPaeonAura ) )
          {
            continue;
          }
          else if( targetChara->hasStatusEffect( ArmysPaeonStatus ) )
          {
            auto effect = targetChara->getStatusEffectById( ArmysPaeonStatus );
            effect->setModifier( Common::ParamModifier::TpRefresh, partyPotency );
            effect->refresh( 5000 );
          }
          else
          {
            auto effect = Sapphire::StatusEffect::make_StatusEffect( ArmysPaeonStatus, actor.getAsChara(), targetChara, 5000, 3000 );
            effect->setFlag( 5 );
            effect->setModifier( Common::ParamModifier::TpRefresh, partyPotency );
            targetChara->addStatusEffect( effect );
            Network::Util::Packet::sendHudParam( *targetChara );
          }
        }
      }
    }


  }
};

EXPOSE_SCRIPT( StatusEffectArmysPaeonAura );