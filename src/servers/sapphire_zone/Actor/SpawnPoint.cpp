#include "SpawnPoint.h"
#include "BNpc.h"

Core::Entity::SpawnPoint::SpawnPoint()
{

}

Core::Entity::SpawnPoint::SpawnPoint( float x, float y, float z, float rot, uint32_t gimmickId ) :
  m_posX( x ),
  m_posY( y ),
  m_posZ( z ),
  m_rotation( rot ),
  m_gimmickId( gimmickId )
{
}

float Core::Entity::SpawnPoint::getPosX() const
{
  return m_posX;
}

float Core::Entity::SpawnPoint::getPosY() const
{
  return m_posY;
}

float Core::Entity::SpawnPoint::getPosZ() const
{
  return m_posZ;
}

float Core::Entity::SpawnPoint::getRotation() const
{
  return m_rotation;
}

uint32_t Core::Entity::SpawnPoint::getGimmickId() const
{
  return m_gimmickId;
}

Core::Entity::BNpcPtr Core::Entity::SpawnPoint::getLinkedBNpc()
{
  return m_pLinkedBnpc;
}

void Core::Entity::SpawnPoint::setLinkedBNpc( BNpcPtr pBnpc )
{
  m_pLinkedBnpc = pBnpc;
}