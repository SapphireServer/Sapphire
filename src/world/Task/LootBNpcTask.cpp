#include "LootBNpcTask.h"

#include <Actor/Player.h>
#include <Logging/Logger.h>
#include <Manager/PlayerMgr.h>
#include <Manager/LootTableMgr.h>
#include <Manager/MgrUtil.h>
#include "WorldServer.h"
#include <Service.h>

using namespace Sapphire::World;
using namespace Sapphire::World::Manager;

LootBNpcTask::LootBNpcTask( Entity::Player& player, std::string lootTable, uint64_t delayTime ) : Task( delayTime )
{
  m_playerId = player.getId();
  m_lootTable = lootTable;
}

void LootBNpcTask::onQueue()
{
  Logger::debug( { __FUNCTION__ } );
}

void LootBNpcTask::execute()
{
  auto& server = Common::Service< WorldServer >::ref();
  auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
  auto& lootTableMgr = Common::Service< World::Manager::LootTableMgr >::ref();

  auto pPlayer = playerMgr.getPlayer( m_playerId );
  if( !pPlayer )
    return;

  auto lootResult = lootTableMgr.rollLoot( m_lootTable );
  // todo: make this a task? it's too fast and good to be retail-like
  for( auto resultItem : lootResult.items )
  {
    auto item = pPlayer->addItem( resultItem.id, resultItem.quantity, resultItem.isHq, false, true );
  }
}

std::string LootBNpcTask::toString()
{
  return fmt::format( "LootBNpcTask: PlayerId#{}, LootTable {}, ElapsedTimeMs: {}", m_playerId, m_lootTable, getDelayTimeMs() );
}


