#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class ChasingShadows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 3802315;
  static constexpr auto INIT_P_POP_IDA = 3802271;
  static constexpr auto INIT_P_POP_PAPARIMO = 3802272;
  static constexpr auto INIT_POP_ENEMY_B_01 = 4094218;
  static constexpr auto INIT_POP_ENEMY_B_02 = 4094220;
  static constexpr auto INIT_POP_ENEMY_B_03 = 4094232;
  static constexpr auto INIT_POP_ENEMY_B_04 = 4094233;
  static constexpr auto INIT_POP_ENEMY_B_05 = 4094474;
  static constexpr auto INIT_POP_ENEMY_B_06 = 4094475;
  static constexpr auto INIT_POP_ENEMY_A_01 = 4094238;
  static constexpr auto INIT_POP_ENEMY_A_02 = 4094239;
  static constexpr auto INIT_POP_ENEMY_A_03 = 4094240;
  static constexpr auto INIT_POP_ENEMY_A_04 = 4094471;
  static constexpr auto INIT_POP_ENEMY_A_05 = 4094472;
  static constexpr auto INIT_POP_ENEMY_A_06 = 4094473;
  static constexpr auto CUT_SCENE_01 = 54;
  static constexpr auto HOW_TO_QIB = 79;

  enum vars
  {
    SET_1_SPAWNED,
    SET_2_SPAWNED,
    SET_3_SPAWNED,
    SUCCESS_CALLED,
  };

public:
  ChasingShadows() : Sapphire::ScriptAPI::QuestBattleScript( 11 ) {}

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    player.setRot( 3.f );
    player.setPos( { 323.f, -1.28f, -320.f } );
  }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f );
  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {
    auto pair1Spawnd = instance.getDirectorVar( SET_1_SPAWNED );
    auto pair2Spawnd = instance.getDirectorVar( SET_2_SPAWNED );
    auto pair3Spawnd = instance.getDirectorVar( SET_3_SPAWNED );
    auto successCalled = instance.getDirectorVar( SUCCESS_CALLED );

    auto boss = instance.getActiveBNpcByInstanceId( INIT_POP_BOSS );
    auto ida = instance.getActiveBNpcByInstanceId( INIT_P_POP_IDA );
    auto papa = instance.getActiveBNpcByInstanceId( INIT_P_POP_PAPARIMO );
    auto pPlayer = instance.getPlayerPtr();

    uint32_t bossHpPercent = 0;
    if( boss )
      bossHpPercent = boss->getHpPercent();

    if( pPlayer && !pPlayer->isAlive() )
    {
      instance.fail();
      return;
    }

    if( !ida || !papa )
      return;

    if( pair1Spawnd == 0 && bossHpPercent <= 75 )
    {
      instance.setDirectorVar( SET_1_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_B_03, 1440, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_B_04, 1440, Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      a2->hateListAdd( ida, 10000 );
      a3->hateListAdd( ida, 10000 );
      a2->hateListAdd( papa, 10000 );
      a3->hateListAdd( papa, 10000 );

      auto a4 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_A_01, 300, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_A_02, 300, Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
    }

    if( pair2Spawnd == 0 && bossHpPercent <= 50 )
    {
      instance.setDirectorVar( SET_2_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_B_05, 1440, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_B_06, 1440, Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      a2->hateListAdd( ida, 10000 );
      a3->hateListAdd( ida, 10000 );
      a2->hateListAdd( papa, 10000 );
      a3->hateListAdd( papa, 10000 );

      auto a4 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_A_03, 300, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_A_04, 300, Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );

    }

    if( pair3Spawnd == 0 && bossHpPercent <= 25 )
    {
      instance.setDirectorVar( SET_3_SPAWNED, 1 );

      auto a4 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_A_05, 300, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_A_06, 300, Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
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
                      DISABLE_CANCEL_EMOTE, [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.setOnEnterEventDone( true );
                      } );

  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
    auto idx = player.getQuestIndex( instance.getQuestId() );
    if( idx == -1 )
      return;
    auto& quest = player.getQuestByIndex( idx );
    quest.setSeq( 2 );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    auto boss = instance.createBNpcFromInstanceId( INIT_POP_BOSS, 21141, Common::BNpcType::Enemy );
    auto a2 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_B_01, 1440, Common::BNpcType::Enemy );
    auto a3 = instance.createBNpcFromInstanceId( INIT_POP_ENEMY_B_02, 1440, Common::BNpcType::Enemy );

    auto ida = instance.createBNpcFromInstanceId( INIT_P_POP_IDA, 27780, Common::BNpcType::Friendly );
    auto papa = instance.createBNpcFromInstanceId( INIT_P_POP_PAPARIMO, 27780, Common::BNpcType::Friendly );
    boss->setFlag( Entity::NoDeaggro );
    a2->setFlag( Entity::NoDeaggro );
    a3->setFlag( Entity::NoDeaggro );
    ida->setFlag( Entity::NoDeaggro );
    papa->setFlag( Entity::NoDeaggro );
    boss->hateListAdd( ida, 10000 );
    boss->hateListAdd( papa, 10000 );
    boss->hateListAdd( player.getAsPlayer(), 1 );

    a2->hateListAdd( player.getAsPlayer(), 1 );
    a2->hateListAdd( ida, 10000 );
    a2->hateListAdd( papa, 10000 );

    a3->hateListAdd( player.getAsPlayer(), 1 );
    a3->hateListAdd( ida, 10000 );
    a3->hateListAdd( papa, 10000 );

    ida->hateListAdd( boss, 10000 );
    ida->hateListAdd( a2, 9999 );
    ida->hateListAdd( a3, 9999 );

    papa->hateListAdd( boss, 10000 );
    papa->hateListAdd( a2, 9999 );
    papa->hateListAdd( a3, 9999 );
  }

};

EXPOSE_SCRIPT( ChasingShadows );
