#include "ForwardsZone.h"
#include "SpawnGroup.h"

Sapphire::Entity::SpawnGroup::SpawnGroup( uint32_t id, uint32_t bNpcTemplateId, uint32_t level, uint32_t maxHp ) :
  m_id( id ),
  m_bNpcTemplateId( bNpcTemplateId ),
  m_level( level ),
  m_maxHp( maxHp )
{

}

uint32_t Sapphire::Entity::SpawnGroup::getId() const
{
  return m_id;
}

uint32_t Sapphire::Entity::SpawnGroup::getTemplateId() const
{
  return m_bNpcTemplateId;
}

uint32_t Sapphire::Entity::SpawnGroup::getLevel() const
{
  return m_level;
}

uint32_t Sapphire::Entity::SpawnGroup::getMaxHp() const
{
  return m_maxHp;
}

Sapphire::Entity::SpawnGroup::SpawnPointList& Sapphire::Entity::SpawnGroup::getSpawnPointList()
{
  return m_spawnPoints;
}