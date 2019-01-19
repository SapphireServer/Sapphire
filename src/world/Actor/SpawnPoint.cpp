#include "SpawnPoint.h"
#include "BNpc.h"

Sapphire::Entity::SpawnPoint::SpawnPoint()
{

}

Sapphire::Entity::SpawnPoint::SpawnPoint( float x, float y, float z, float rot, uint32_t gimmickId ) :
  m_posX( x ),
  m_posY( y ),
  m_posZ( z ),
  m_rotation( rot ),
  m_gimmickId( gimmickId ),
  m_lastSpawn( 0 ),
  m_timeOfDeath( 0 )
{
}

uint32_t Sapphire::Entity::SpawnPoint::getTimeOfDeath() const
{
  return m_timeOfDeath;
}

void Sapphire::Entity::SpawnPoint::setTimeOfDeath( uint32_t timeOfDeath )
{
  m_timeOfDeath = timeOfDeath;
}

float Sapphire::Entity::SpawnPoint::getPosX() const
{
  return m_posX;
}

float Sapphire::Entity::SpawnPoint::getPosY() const
{
  return m_posY;
}

float Sapphire::Entity::SpawnPoint::getPosZ() const
{
  return m_posZ;
}

float Sapphire::Entity::SpawnPoint::getRotation() const
{
  return m_rotation;
}

uint32_t Sapphire::Entity::SpawnPoint::getGimmickId() const
{
  return m_gimmickId;
}

Sapphire::Entity::BNpcPtr Sapphire::Entity::SpawnPoint::getLinkedBNpc()
{
  return m_pLinkedBnpc;
}

void Sapphire::Entity::SpawnPoint::setLinkedBNpc( BNpcPtr pBnpc )
{
  m_pLinkedBnpc = pBnpc;
}