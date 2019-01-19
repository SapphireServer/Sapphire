#ifndef SAPPHIRE_SPAWNGROUP_H
#define SAPPHIRE_SPAWNGROUP_H

#include "ForwardsZone.h"

namespace Sapphire::Entity
{

  class SpawnGroup
  {
  private:
    BNpcTemplatePtr m_bNpcTemplate;

    uint32_t m_id;
    uint32_t m_bNpcTemplateId;
    uint32_t m_level;
    uint32_t m_maxHp;

    std::vector< SpawnPointPtr > m_spawnPoints;

  public:
    using SpawnPointList = std::vector< SpawnPointPtr >;
    SpawnGroup( uint32_t id, uint32_t bNpcTemplateId, uint32_t level, uint32_t maxHp );

    uint32_t getId() const;
    uint32_t getTemplateId() const;
    uint32_t getLevel() const;
    uint32_t getMaxHp() const;

    SpawnPointList& getSpawnPointList();


  };

}

#endif //SAPPHIRE_SPAWNGROUP_H
