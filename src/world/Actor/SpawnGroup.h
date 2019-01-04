#ifndef SAPPHIRE_SPAWNGROUP_H
#define SAPPHIRE_SPAWNGROUP_H

#include "ForwardsZone.h"

namespace Sapphire::Entity
{

  class SpawnGroup
  {
  private:
    BNpcTemplatePtr m_bNpcTemplate;

    uint32_t m_level;
    uint32_t m_spawnCount;

    std::vector< SpawnPointPtr > m_spawnPoints;

  public:
    SpawnGroup( uint32_t bNpcTemplateId, uint32_t level );

  };

}

#endif //SAPPHIRE_SPAWNGROUP_H
