#ifndef SAPPHIRE_BNPCTEMPLATE_H
#define SAPPHIRE_BNPCTEMPLATE_H

#include <stdint.h>

namespace Core {
namespace Entity {


class BNpcTemplate
{

private:
  uint32_t m_id;
  uint32_t m_bNpcBaseId;
  uint32_t m_bNpcNameId;
  uint64_t m_weaponMain;
  uint64_t m_weaponSub;
  uint8_t m_aggressionMode;
  uint8_t m_enemyType;
  uint8_t m_onlineStatus;
  uint8_t m_pose;
  uint16_t m_modelChara;
  uint32_t m_displayFlags;
  uint32_t m_modelEquip[10];
  uint8_t m_customize[26];

public:
  BNpcTemplate() {};

  BNpcTemplate( uint32_t id, uint32_t baseId, uint32_t nameId, uint64_t weaponMain, uint64_t weaponSub, uint8_t aggressionMode,
                uint8_t enemyType, uint8_t onlineStatus, uint8_t pose, uint16_t modelChara,
                uint32_t displayFlags = 0,
                uint32_t* modelEquip = nullptr, uint8_t* customize = nullptr );

  virtual ~BNpcTemplate();

  uint32_t getId() const;

  void setId( uint32_t id );

  uint32_t getBNpcBaseId() const;

  void setBNpcBaseId( uint32_t bNpcBaseId );

  uint32_t getBNpcNameId() const;

  void setBNpcNameId( uint32_t bNpcNameId );

  uint64_t getWeaponMain() const;

  void setWeaponMain( uint64_t weaponMain );

  uint64_t getWeaponSub() const;

  void setWeaponSub( uint64_t weaponSub );

  uint8_t getAggressionMode() const;

  void setAggressionMode( uint8_t aggressionMode );

  uint8_t getEnemyType() const;

  void setEnemyType( uint8_t enemyType );

  uint8_t getOnlineStatus() const;

  void setOnlineStatus( uint8_t m_onlineStatus );

  uint8_t getPose() const;

  void setPose( uint8_t m_pose );

  uint16_t getModelChara() const;

  void setModelChara( uint16_t modelChara );

  uint32_t getDisplayFlags() const;

  void setDisplayFlags( uint32_t displayFlags );

  const uint32_t* getModelEquip() const;

  const uint8_t* getCustomize() const;
};


}
}

#endif //SAPPHIRE_BNPCTEMPLATE_H
