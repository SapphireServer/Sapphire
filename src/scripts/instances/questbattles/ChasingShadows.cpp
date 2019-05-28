#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/Actor.h>
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

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player )
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
    auto pair1Spawnd = instance.getCustomVar( SET_1_SPAWNED );
    auto pair2Spawnd = instance.getCustomVar( SET_2_SPAWNED );
    auto pair3Spawnd = instance.getCustomVar( SET_3_SPAWNED );
    auto successCalled = instance.getCustomVar( SUCCESS_CALLED );

    auto boss = instance.getActiveBNpcByLevelId( INIT_POP_BOSS );
    auto ida = instance.getActiveBNpcByLevelId( INIT_P_POP_IDA );
    auto papa = instance.getActiveBNpcByLevelId( INIT_P_POP_PAPARIMO );
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
      instance.setCustomVar( SET_1_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_B_03, 10, 0, 1440, 938,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_B_04, 10, 0, 1440, 938,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      a2->hateListAdd( ida, 10000 );
      a3->hateListAdd( ida, 10000 );
      a2->hateListAdd( papa, 10000 );
      a3->hateListAdd( papa, 10000 );


      auto a4 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_A_01, 5, 0, 300, 937,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_A_02, 5, 0, 300, 937,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
    }

    if( pair2Spawnd == 0 && bossHpPercent <= 50 )
    {
      instance.setCustomVar( SET_2_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_B_05, 10, 0, 1440, 938,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_B_06, 10, 0, 1440, 938,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      a2->hateListAdd( ida, 10000 );
      a3->hateListAdd( ida, 10000 );
      a2->hateListAdd( papa, 10000 );
      a3->hateListAdd( papa, 10000 );

      auto a4 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_A_03, 5, 0, 300, 937,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_A_04, 5, 0, 300, 937,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );

    }

    if( pair3Spawnd == 0 && bossHpPercent <= 25 )
    {
      instance.setCustomVar( SET_3_SPAWNED, 1 );

      auto a4 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_A_05, 5, 0, 300, 937,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_A_06, 5, 0, 300, 937,
                                                   instance.getDirectorId(), Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
    }

    if( instance.getCountEnemyBNpc() == 0 && successCalled == 0 )
    {
      instance.setCustomVar( SUCCESS_CALLED, 1 );
      instance.success();
      return;
    }
  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
    player.playScene( instance.getDirectorId(), 1,
                      NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                      HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                      DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                      // todo: wtf is 0x00100000
                      DISABLE_CANCEL_EMOTE, 0 );

  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
    player.updateQuest( instance.getQuestId(), 2 );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    auto a1 = instance.createBNpcFromLevelEntry( INIT_POP_BOSS, 12, 0, 21141, 939,
                                                 instance.getDirectorId(), Common::BNpcType::Enemy );
    auto a2 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_B_01, 10, 0, 1440, 938,
                                                 instance.getDirectorId(), Common::BNpcType::Enemy );
    auto a3 = instance.createBNpcFromLevelEntry( INIT_POP_ENEMY_B_02, 10, 0, 1440, 938,
                                                 instance.getDirectorId(), Common::BNpcType::Enemy );

    auto a4 = instance.createBNpcFromLevelEntry( INIT_P_POP_IDA, 50, 0, 27780, 1375,
                                                 instance.getDirectorId(), Common::BNpcType::Friendly );
    auto a5 = instance.createBNpcFromLevelEntry( INIT_P_POP_PAPARIMO, 50, 0, 27780, 1376,
                                                 instance.getDirectorId(), Common::BNpcType::Friendly );
    a1->setFlag( Entity::NoDeaggro );
    a2->setFlag( Entity::NoDeaggro );
    a3->setFlag( Entity::NoDeaggro );
    a4->setFlag( Entity::NoDeaggro );
    a5->setFlag( Entity::NoDeaggro );
    a1->hateListAdd( a4, 10000 );
    a1->hateListAdd( a5, 10000 );

    a2->hateListAdd( player.getAsPlayer(), 1 );
    a2->hateListAdd( a4, 10000 );
    a2->hateListAdd( a5, 10000 );

    a3->hateListAdd( player.getAsPlayer(), 1 );
    a3->hateListAdd( a4, 10000 );
    a3->hateListAdd( a5, 10000 );

    a4->hateListAdd( a1, 10000 );
    a4->hateListAdd( a2, 9999 );
    a4->hateListAdd( a3, 9999 );

    a5->hateListAdd( a1, 10000 );
    a5->hateListAdd( a2, 9999 );
    a5->hateListAdd( a3, 9999 );
  }

};

EXPOSE_SCRIPT( ChasingShadows );
