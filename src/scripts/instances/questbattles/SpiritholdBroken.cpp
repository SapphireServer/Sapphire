#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SpiritholdBroken : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 3869528;
  static constexpr auto LOC_POS_ACTOR0 = 3884691;
  static constexpr auto LOC_POS_ACTOR1 = 3884694;
  static constexpr auto LOC_ACTOR0 = 1003064;
  static constexpr auto BNPC_NAME_01 = 750;
  static constexpr auto DEF_ACTION_SAND_BREATH = 445;
  static constexpr auto DEF_BLIND = 15;
  static constexpr auto CUT_SCENE_01 = 69;
  static constexpr auto LOC_TALKSHAPE1 = 8;

  enum vars
  {
    SUCCESS_CALLED,
  };

public:
  SpiritholdBroken() : Sapphire::ScriptAPI::QuestBattleScript( 15 )
  {}

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    //Manually set, may be off
    player.setRot( -1.08634f );
    player.setPos( { 257.876f, 24.f, 194.734f } );
  }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f );
  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

    auto successCalled = instance.getDirectorVar( SUCCESS_CALLED );

    auto boss = instance.getActiveBNpcByInstanceId( INIT_POP_BOSS );
    auto pPlayer = instance.getPlayerPtr();

    uint32_t bossHpPercent = 0;
    if( boss )
      bossHpPercent = boss->getHpPercent();

    if( pPlayer && !pPlayer->isAlive() )
    {
      instance.fail();
      return;
    }

    if( bossHpPercent <= 10 )
    {
      //TODO: Show "Impossible! Never has the golem been so sorely tested!" text.
    }

    if( instance.getCountEnemyBNpc() == 0 && successCalled == 0 )
    {
      instance.setDirectorVar( SUCCESS_CALLED, 1 );
      instance.success();
      return;
    }
  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
    eventMgr().playScene( player, instance.getDirectorId(), 1,
                          NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                                  HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                  DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                  // todo: wtf is 0x00100000
                                  DISABLE_CANCEL_EMOTE,
                          [ & ]( Entity::Player& player, const Event::SceneResult& result ) {
                            player.setOnEnterEventDone( true );
                          } );
  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
    eventMgr().playScene( player, instance.getDirectorId(), 9,
                          NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                                  HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                  DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                  // todo: wtf is 0x00100000
                                  DISABLE_CANCEL_EMOTE,
                          [ & ]( Entity::Player& player, const Event::SceneResult& result ) {
                            auto idx = player.getQuestIndex( instance.getQuestId() );
                            if( idx == -1 )
                              return;
                            auto& quest = player.getQuestByIndex( idx );
                            quest.setSeq( 4 );
                          } );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    auto boss = instance.createBNpcFromInstanceId( INIT_POP_BOSS, 5000 /*TODO: Find right HP*/, Common::BNpcType::Enemy, player.getId() );
    boss->setFlag( Entity::NoDeaggro );
    boss->hateListAdd( player.getAsPlayer(), 1 );
  }
};

EXPOSE_SCRIPT( SpiritholdBroken );