#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class IfritNormal : public Sapphire::ScriptAPI::InstanceArenaScript
{
public:
  IfritNormal() : Sapphire::ScriptAPI::InstanceArenaScript( 20001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    auto boss = instance.createBNpcFromLayoutId( 4126276, 13884, Common::BNpcType::Enemy );
    boss->setFlag( Entity::NoDeaggro );

    //instance.sendForward();
  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {
    auto boss = instance.getActiveBNpcByLayoutId( 4126276 );

    if( boss; boss->hateListGetHighestValue() != 0 )
    {
      if( instance.getDirectorVar( 0 ) == 0 )
        onBattleStart( instance );

      boss->setRot( boss->getRot() + 0.5f );
      boss->setPos( boss->getPos() );

      boss->sendPositionUpdate();

      playerMgr().sendDebug( *boss->hateListGetHighest()->getAsPlayer(), std::to_string( boss->getRot() ) );

      if( boss->getRot() >= 4.f && instance.getDirectorVar( 0 ) == 1 )
      {
        instance.setDirectorVar( 0, 0 );
        boss->hateListGetHighest()->die();
        boss->hateListClear();
        onReset( instance );

      }
        
    }
  }

  void onReset( InstanceContent& instance ) override
  {
    auto boss = instance.getActiveBNpcByLayoutId( 4126276 );
    instance.removeActor( boss );

    onInit( instance );
  }

  void onBattleStart( InstanceContent& instance ) override
  {
    auto boss = instance.getActiveBNpcByLayoutId( 4126276 );

    instance.setDirectorVar( 0, 1 );

    auto pPlayer = boss->hateListGetHighest()->getAsPlayer();

    instance.sendEventLogMessage( *pPlayer, instance, 4847, { 0, 0 } );
    instance.sendEventLogMessage( *pPlayer, instance, 170, { 0, boss->getId() } );
  }
};

EXPOSE_SCRIPT( IfritNormal );