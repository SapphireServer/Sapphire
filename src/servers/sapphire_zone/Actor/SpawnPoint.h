#ifndef SAPPHIRE_SPAWNPOINT_H
#define SAPPHIRE_SPAWNPOINT_H

#include "ForwardsZone.h"

namespace Core {
namespace Entity {

class SpawnPoint
{
private:
  float m_posX;
  float m_posY;
  float m_posZ;
  float m_rotation;
  uint32_t m_gimmickId;

  uint32_t m_lastSpawn;
  BNpcPtr m_pLinkedBnpc;

public:
  SpawnPoint();
  SpawnPoint( float x, float y, float z, float rot, uint32_t gimmickId );

  float getPosX() const;
  float getPosY() const;
  float getPosZ() const;
  float getRotation() const;

  uint32_t getGimmickId() const;

  BNpcPtr getLinkedBNpc();
  void setLinkedBNpc( BNpcPtr pBnpc );

};

}
}


#endif //SAPPHIRE_SPAWNPOINT_H
