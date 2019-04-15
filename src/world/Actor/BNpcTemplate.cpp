#include "BNpcTemplate.h"
#include <string>
#include <cstring>

Sapphire::Entity::BNpcTemplate::BNpcTemplate( uint32_t id, uint32_t baseId, uint32_t nameId, uint64_t weaponMain, uint64_t weaponSub,
                                              uint8_t aggressionMode, uint8_t enemyType, uint8_t onlineStatus, uint8_t pose,
                                              uint16_t modelChara, uint32_t displayFlags, uint32_t* modelEquip,
                                              uint8_t* customize ) :
  m_id( id ),
  m_bNpcBaseId( baseId ),
  m_bNpcNameId( nameId ),
  m_weaponMain( weaponMain ),
  m_weaponSub( weaponSub ),
  m_aggressionMode( aggressionMode ),
  m_enemyType( enemyType ),
  m_onlineStatus( onlineStatus ),
  m_pose( pose ),
  m_modelChara( modelChara ),
  m_displayFlags( displayFlags )
{

  if( modelEquip )
    std::memcpy( m_modelEquip, modelEquip, sizeof( m_modelEquip ) );

  if( customize )
    std::memcpy( m_customize, customize, sizeof( m_customize ) );

}

Sapphire::Entity::BNpcTemplate::~BNpcTemplate()
{

}

uint32_t Sapphire::Entity::BNpcTemplate::getId() const
{
  return m_id;
}

void Sapphire::Entity::BNpcTemplate::setId( uint32_t id )
{
  m_id = id;
}

uint32_t Sapphire::Entity::BNpcTemplate::getBNpcBaseId() const
{
  return m_bNpcBaseId;
}

void Sapphire::Entity::BNpcTemplate::setBNpcBaseId( uint32_t bNpcBaseId )
{
  m_bNpcBaseId = bNpcBaseId;
}

uint32_t Sapphire::Entity::BNpcTemplate::getBNpcNameId() const
{
  return m_bNpcNameId;
}

void Sapphire::Entity::BNpcTemplate::setBNpcNameId( uint32_t bNpcNameId )
{
  m_bNpcNameId = bNpcNameId;
}

uint64_t Sapphire::Entity::BNpcTemplate::getWeaponMain() const
{
  return m_weaponMain;
}

void Sapphire::Entity::BNpcTemplate::setWeaponMain( uint64_t weaponMain )
{
  m_weaponMain = weaponMain;
}

uint64_t Sapphire::Entity::BNpcTemplate::getWeaponSub() const
{
  return m_weaponSub;
}

void Sapphire::Entity::BNpcTemplate::setWeaponSub( uint64_t weaponSub )
{
  m_weaponSub = weaponSub;
}

uint8_t Sapphire::Entity::BNpcTemplate::getAggressionMode() const
{
  return m_aggressionMode;
}

void Sapphire::Entity::BNpcTemplate::setAggressionMode( uint8_t aggressionMode )
{
  m_aggressionMode = aggressionMode;
}

uint8_t Sapphire::Entity::BNpcTemplate::getEnemyType() const
{
  return m_enemyType;
}

void Sapphire::Entity::BNpcTemplate::setEnemyType( uint8_t enemyType )
{
  m_enemyType = enemyType;
}

uint8_t Sapphire::Entity::BNpcTemplate::getOnlineStatus() const
{
  return m_onlineStatus;
}

void Sapphire::Entity::BNpcTemplate::setOnlineStatus( uint8_t onlineStatus )
{
  m_onlineStatus = onlineStatus;
}

uint8_t Sapphire::Entity::BNpcTemplate::getPose() const
{
  return m_pose;
}

void Sapphire::Entity::BNpcTemplate::setPose( uint8_t pose )
{
  m_pose = pose;
}

uint16_t Sapphire::Entity::BNpcTemplate::getModelChara() const
{
  return m_modelChara;
}

void Sapphire::Entity::BNpcTemplate::setModelChara( uint16_t modelChara )
{
  m_modelChara = modelChara;
}

uint32_t Sapphire::Entity::BNpcTemplate::getDisplayFlags() const
{
  return m_displayFlags;
}

void Sapphire::Entity::BNpcTemplate::setDisplayFlags( uint32_t displayFlags )
{
  m_displayFlags = displayFlags;
}

const uint32_t* Sapphire::Entity::BNpcTemplate::getModelEquip() const
{
  return m_modelEquip;
}

const uint8_t* Sapphire::Entity::BNpcTemplate::getCustomize() const
{
  return m_customize;
}
